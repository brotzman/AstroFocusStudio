#!/usr/bin/env python3
"""Static contract checks for the GitHub Actions and WiX packaging files."""
from __future__ import annotations

import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
passed = 0
total = 0


def check(condition: bool, message: str) -> None:
    global passed, total
    total += 1
    if condition:
        passed += 1
        print(f"PASS: {message}")
    else:
        print(f"FAIL: {message}")


required_text_files = {
    "workflow": ROOT / ".github" / "workflows" / "windows-build.yml",
    "package": ROOT / "installer" / "wix" / "Package.wxs",
    "bundle": ROOT / "installer" / "wix" / "Bundle.wxs",
    "wix_build": ROOT / "installer" / "build-wix.ps1",
    "artifact_build": ROOT / "scripts" / "Build-GitHubArtifacts.ps1",
    "installer_test": ROOT / "scripts" / "Test-GitHubInstaller.ps1",
    "native_script": ROOT / "scripts" / "Run-NativeTests.sh",
}

required_payload_sources = [
    ROOT / "installer" / "AstroFocusSetup.ps1",
    ROOT / "updater" / "AstroFocusUpdater.ps1",
    ROOT / "updater" / "update-public-key.cer",
    ROOT / "release" / "New-ReleaseManifest.ps1",
    ROOT / "README_DE.md",
    ROOT / "KNOWN_LIMITATIONS_3_9_0.txt",
    ROOT / "UNSIGNED_DEVELOPMENT_BUILD.txt",
]
missing_payload_sources = [
    str(path.relative_to(ROOT)) for path in required_payload_sources if not path.is_file()
]

missing = [str(path.relative_to(ROOT)) for path in required_text_files.values() if not path.is_file()]
if missing or missing_payload_sources:
    print("FAIL: required GitHub/WiX or payload source files are missing from the checked-out commit:")
    for relative_path in missing + missing_payload_sources:
        print(f"  - {relative_path}")
    sys.exit(1)

loaded: dict[str, str] = {}
for name, path in required_text_files.items():
    try:
        loaded[name] = path.read_text(encoding="utf-8-sig")
    except (OSError, UnicodeError) as exc:
        print(f"FAIL: cannot read {path.relative_to(ROOT)} as UTF-8: {exc}")
        sys.exit(1)

workflow_path = required_text_files["workflow"]
workflow = loaded["workflow"]
package = loaded["package"]
bundle = loaded["bundle"]
wix_build = loaded["wix_build"]
artifact_build = loaded["artifact_build"]
installer_test = loaded["installer_test"]
native_script = loaded["native_script"]

check("runs-on: windows-2022" in workflow, "Windows build uses a fixed supported runner")
check("actions/checkout@v7" in workflow, "checkout action uses the current v7 major")
check("actions/upload-artifact@v7" in workflow, "artifact upload uses the current v7 major")
check("actions/download-artifact@v8" in workflow, "release download uses the current v8 major")
check("actions/setup-python@v7" in workflow, "Python setup uses the current v7 major")
check("actions/setup-dotnet@v6" in workflow, "dotnet setup uses the current v6 major")
check("Build-GitHubArtifacts.ps1" in workflow, "workflow runs the complete artifact build")
check("Test-GitHubInstaller.ps1" in workflow, "workflow runs the installer smoke test")
check("bash --noprofile --norc ./scripts/Run-NativeTests.sh" in workflow, "workflow invokes native tests through bash without relying on the executable bit")
check("Prepare sanitizer toolchain" in workflow, "workflow resolves a versioned native-test compiler before execution")
check("/usr/bin/clang++-18" in workflow, "workflow prefers the runner's fixed Clang 18 path")
check("CXX=$compiler" in workflow, "resolved compiler is exported explicitly to the native test script")
check("native-sanitizers.log" in workflow, "native sanitizer output is persisted as a diagnostic log")
check("Native-Sanitizer-Logs" in workflow and "if: always()" in workflow, "native logs are uploaded even after a failed test")
check("run: ./scripts/Run-NativeTests.sh" not in workflow, "workflow has no direct executable-bit-dependent native test invocation")
check("$optionalMetadata = @('.gitattributes', '.gitignore')" in workflow, "repository dotfiles are treated as optional metadata")
check("Optional repository metadata is missing and will not block the build" in workflow, "missing dotfiles produce a warning instead of blocking compilation")
check("permissions:\n  contents: read" in workflow, "default workflow permissions are read-only")
check("contents: write" in workflow, "release job explicitly receives write permission")
check("Prepare CI diagnostics" in workflow, "workflow creates the diagnostic directory before the Windows build")
check(workflow.index("Prepare CI diagnostics") < workflow.index("Verify repository build entry points"), "diagnostic directory and preflight log are created before repository validation")
check("preflight.log" in workflow, "repository validation writes a persistent preflight log")
check("Verify repository build entry points" in workflow, "workflow verifies all required build scripts after checkout")
check("$env:GITHUB_WORKSPACE" in workflow, "Windows build paths are anchored to the checked-out GitHub workspace")
check("Required build files are missing from this commit" in workflow, "missing build inputs produce an explicit preflight error")
check("-ExecutionPolicy Bypass" in workflow and "-File $buildScript" in workflow, "artifact build is invoked through an explicit absolute PowerShell script path")
check("& .\\scripts\\Build-GitHubArtifacts.ps1" not in workflow, "workflow no longer relies on a fragile relative build-script invocation")
check("build-package.log" in workflow and "Tee-Object" in workflow, "Windows build output is persisted even when packaging fails")
check("path: artifacts/test-logs/" in workflow and "if-no-files-found: warn" in workflow, "diagnostic upload does not create a second failure when a prior setup step aborts")
check("python-tests.log" in workflow or "python-tests.log" in artifact_build, "Python test output is persisted as a complete diagnostic log")
check("Start-Process" in (ROOT / "scripts" / "Run-PythonTests.ps1").read_text(encoding="utf-8-sig"), "Python runner captures stdout and stderr without PowerShell NativeCommandError truncation")
check("installer\\wix\\Package.wxs" in workflow and "installer\\wix\\Bundle.wxs" in workflow, "checkout preflight verifies both WiX source files")
check("KNOWN_LIMITATIONS_3_9_0.txt" in workflow, "checkout preflight verifies the current known-limitations payload")
check("UNSIGNED_DEVELOPMENT_BUILD.txt" in workflow, "checkout preflight verifies the unsigned-development marker")
check("updater\\update-public-key.cer" in workflow, "checkout preflight verifies the updater public key")
check("common\\security_entry.cpp" in workflow, "checkout preflight verifies the no-CRT security entry")
check("common\\continuous_focus_logic.h" in workflow, "checkout preflight verifies the continuous-focus control helper")
check("tests\\continuous_focus_logic_validation_390.cpp" in workflow, "checkout preflight verifies the continuous-focus native test")
check("tests\\continuous_focus_validation_390.py" in workflow and "tests\\continuous_focus_layout_validation_390.py" in workflow, "checkout preflight verifies continuous-focus integration and layout tests")

preflight_match = re.search(
    r"\$requiredFiles\s*=\s*@\((.*?)\)\s*\n\s*\$optionalMetadata",
    workflow,
    re.DOTALL,
)
preflight_entries = set(re.findall(r"'([^']+)'", preflight_match.group(1))) if preflight_match else set()
for relative_path in (
    r"KNOWN_LIMITATIONS_3_9_0.txt",
    r"UNSIGNED_DEVELOPMENT_BUILD.txt",
    r"updater\update-public-key.cer",
    r"common\security_entry.cpp",
    r"common\continuous_focus_logic.h",
    r"tests\continuous_focus_logic_validation_390.cpp",
    r"tests\continuous_focus_validation_390.py",
    r"tests\continuous_focus_layout_validation_390.py",
):
    check(
        relative_path in preflight_entries,
        f"preflight requiredFiles contains packaging source: {relative_path}",
    )
check("Assert-PackagingInputs" in artifact_build, "artifact build validates packaging inputs before compilation")
check(artifact_build.index("Assert-PackagingInputs") < artifact_build.index("Initialize-LlvmPath"), "packaging inputs are checked before the compiler toolchain is initialized")
check("$LogRoot = Join-Path $ArtifactsRoot 'test-logs'" in artifact_build, "artifact build preserves the CI diagnostic directory")
check("& lld-link.exe --version" in artifact_build, "LLD version probe uses the supported GNU-style long option")
check("lld-link.exe /version" not in artifact_build, "LLD version probe is not passed to the linker as an input path")

for source in (
    "tests/command_line_args_validation_390.cpp",
    "tests/frontend_logic_validation_390.cpp",
    "tests/actual_backend_validation_390.cpp",
    "tests/continuous_focus_logic_validation_390.cpp",
):
    check(source in native_script, f"native test is included: {source}")

check("-static-libsan" in native_script, "Clang sanitizer runtimes are embedded to prevent loader exit 127")
check('command -v "$CXX"' in native_script, "native script validates the selected compiler explicitly")
check("binary diagnostics" in native_script and 'ldd "$binary"' in native_script, "native script records loader diagnostics on test failure")
check('chmod u+x "$binary"' in native_script, "freshly linked test programs are made executable defensively")

try:
    ET.parse(ROOT / "installer" / "wix" / "Package.wxs")
    xml_ok = True
except ET.ParseError:
    xml_ok = False
check(xml_ok, "Package.wxs is well-formed XML")
try:
    ET.parse(ROOT / "installer" / "wix" / "Bundle.wxs")
    bundle_xml_ok = True
except ET.ParseError:
    bundle_xml_ok = False
check(bundle_xml_ok, "Bundle.wxs is well-formed XML")

expected_payload = {
    "AstroFocusStudio.exe",
    "AstroFocusEngine.exe",
    "AstroFocusCameraHost.exe",
    "AstroFocusFocuserHost.exe",
    "AstroFocusFocuserSetup.exe",
    "AstroFocusUpdater.exe",
    "AstroFocusUpdater.ps1",
    "AstroFocusSetup.exe",
    "AstroFocusSetup.ps1",
    "update-public-key.cer",
    "release-manifest.json",
    "README_DE.md",
    "KNOWN_LIMITATIONS_3_9_0.txt",
    "UNSIGNED_DEVELOPMENT_BUILD.txt",
}
found_payload = set(re.findall(r'Source="\$\(var\.Payload\)\\([^"\\]+)"', package))
check(expected_payload == found_payload, "WiX package contains exactly the current 3.9.0 payload")
check("3_8_3" not in package and "3_8_7" not in package, "WiX package has no stale version references")
check(package.count("<Component Id=\"Cmp") >= len(expected_payload), "payload files use independent repair components")
check('IconSourceFile="$(var.IconPath)"' in bundle, "bundle uses the product icon")
check('Compressed="yes"' in bundle, "bundle embeds the MSI")

check("WixVersion = '5.0.2'" in wix_build, "WiX tool version is pinned")
check('WixToolset.BootstrapperApplications.wixext/$WixVersion' in wix_build, "WiX CLI uses the BootstrapperApplications extension name and pinned version")
check('IconPath=$iconPath' in wix_build, "WiX build receives the icon path")
check("dotnet.Source tool install" in artifact_build, "WiX is installed as a local .NET tool")
check("Assert-Pe64" in artifact_build, "all generated binaries are checked as Windows x64 PE files")
check("release-manifest.json" in artifact_build, "release manifest is generated before packaging")
check("/repair" in installer_test and "AstroFocusFocuserHost.exe" in installer_test, "installer test verifies MSI repair of a missing component")
check("/uninstall" in installer_test and "msiexec.exe" in installer_test, "installer test covers bundle and MSI removal")
check("--health-check" in installer_test, "installer test runs installed health checks")
check("bundle-test:" in workflow and "msi-test:" in workflow, "bundle and raw MSI are tested in separate jobs")
check("-Mode Bundle" in workflow and "-Mode Msi" in workflow, "isolated jobs select explicit installer modes")
check("Installer-Test-Input" in workflow, "test jobs consume the exact packages built by the build job")
check("needs: [windows-build, bundle-test, msi-test]" in workflow, "tagged release waits for both installer test jobs")
check("[ValidateSet('Bundle', 'Msi')]" in installer_test, "installer test script prevents mixed transaction modes")
check("'/fa'" in installer_test and "MSI-Reparatur" in installer_test, "raw MSI repair is tested independently")

check("publish_release:" in workflow and "type: boolean" in workflow, "manual workflow dispatch can opt in to publishing a release")
check("release_tag:" in workflow and "default: 'v3.9.0'" in workflow, "manual release dispatch provides the version tag")
check("inputs.publish_release == true" in workflow, "release job is gated by the manual publish switch")
check('expected_tag="v${PRODUCT_VERSION}"' in workflow, "release tag must match the built product version")
check('--target "$GITHUB_SHA"' in workflow, "manual publishing creates a missing tag at the tested commit")
check('GH_REPO: ${{ github.repository }}' in workflow, "release job binds GitHub CLI to the explicit repository")
check('gh release view --repo "$GH_REPO" "$RELEASE_TAG"' in workflow, "release lookup does not depend on a local Git checkout")
check('gh release upload --repo "$GH_REPO" "$RELEASE_TAG" release-files/* --clobber' in workflow, "existing releases are updated without duplicating assets")
check(workflow.count('gh release create --repo "$GH_REPO"') == 2, "both release-creation paths use an explicit repository")
check('gh release view "$RELEASE_TAG"' not in workflow, "release job has no repository-implicit GitHub CLI lookup")

check('StandardDirectory Id="DesktopFolder"' in package and 'Scope="perMachine"' in package, "WiX package uses DesktopFolder in per-machine context for the public desktop")
check('CommonDesktopFolder' not in package, "WiX package avoids unsupported CommonDesktopFolder in WiX 5")
check('Component Id="CmpDesktopShortcut"' in package, "desktop shortcut has its own repairable MSI component")
check('Id="DesktopShortcutLink"' in package and 'Name="AstroFocus Studio"' in package, "desktop shortcut has the expected name")
check('Target="[INSTALLFOLDER]AstroFocusStudio.exe"' in package, "desktop shortcut targets the main executable")
check('WorkingDirectory="INSTALLFOLDER"' in package, "desktop shortcut uses the installation folder as working directory")
check('<ComponentRef Id="CmpDesktopShortcut" />' in package, "desktop shortcut component is included in the main feature")
check('CommonDesktopDirectory' in installer_test and 'AstroFocus Studio.lnk' in installer_test, "installer tests resolve the public desktop shortcut")
check('WScript.Shell' in installer_test and 'TargetPath' in installer_test, "installer tests validate the desktop shortcut target")
check('Nach der Deinstallation ist die Desktopverknüpfung noch vorhanden' in installer_test, "installer tests require desktop shortcut removal")

print(f"GitHub/WiX contract tests: {passed}/{total}")
sys.exit(0 if passed == total else 1)
