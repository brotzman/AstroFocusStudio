#!/usr/bin/env python3
"""Generate a deterministic Microsoft .res file with icon, manifest and version metadata."""
from __future__ import annotations

import argparse
import struct
from pathlib import Path

from generate_version import read_version

LANGUAGE = 0x0407  # de-DE
CODEPAGE = 1200


def pad4(data: bytes) -> bytes:
    return data + b"\0" * ((-len(data)) & 3)


def ordinal(value: int) -> bytes:
    return struct.pack("<HH", 0xFFFF, value)


def resource_record(resource_type: int, name: int, data: bytes, language: int = LANGUAGE) -> bytes:
    variable = ordinal(resource_type) + ordinal(name)
    header = pad4(struct.pack("<II", len(data), 0) + variable)
    header += struct.pack("<IHHII", 0, 0x1030, language, 0, 0)
    header = struct.pack("<II", len(data), len(header)) + header[8:]
    return pad4(header) + pad4(data)


def null_record() -> bytes:
    result = struct.pack("<II", 0, 32) + ordinal(0) + ordinal(0)
    result = pad4(result) + struct.pack("<IHHII", 0, 0, 0, 0, 0)
    if len(result) != 32:
        raise AssertionError("invalid null resource header")
    return result


def utf16z(text: str) -> bytes:
    return (text + "\0").encode("utf-16le")


def version_block(key: str, value: bytes = b"", children: tuple[bytes, ...] = (), *, text: bool = False, value_length: int | None = None) -> bytes:
    header = struct.pack("<HHH", 0, len(value) // 2 if text else len(value), 1 if text else 0)
    body = pad4(header + utf16z(key)) + value
    body = pad4(body)
    for child in children:
        body += child
    length = len(body)
    if length > 0xFFFF:
        raise ValueError(f"version resource block is too large: {key}")
    actual_value_length = (len(value) // 2 if text else len(value)) if value_length is None else value_length
    return struct.pack("<HHH", length, actual_value_length, 1 if text else 0) + body[6:]


def string_block(key: str, value: str) -> bytes:
    return version_block(key, utf16z(value), text=True)


def build_version_info(version: tuple[int, int, int], original_filename: str, description: str) -> bytes:
    major, minor, patch = version
    high = (major << 16) | minor
    low = patch << 16
    fixed = struct.pack(
        "<13I",
        0xFEEF04BD,  # VS_FFI_SIGNATURE
        0x00010000,  # VS_FFI_STRUCVERSION
        high,
        low,
        high,
        low,
        0x0000003F,  # VS_FFI_FILEFLAGSMASK
        0,
        0x00040004,  # VOS_NT_WINDOWS32
        0x00000001,  # VFT_APP
        0,
        0,
        0,
    )
    text = f"{major}.{minor}.{patch}"
    strings = (
        string_block("CompanyName", "AstroFocus Studio"),
        string_block("FileDescription", description),
        string_block("FileVersion", text),
        string_block("InternalName", Path(original_filename).stem),
        string_block("LegalCopyright", "Copyright (c) 2026 Thomas Brotze"),
        string_block("OriginalFilename", original_filename),
        string_block("ProductName", "AstroFocus Studio"),
        string_block("ProductVersion", text),
    )
    table = version_block(f"{LANGUAGE:04X}{CODEPAGE:04X}", children=strings, text=True)
    string_file_info = version_block("StringFileInfo", children=(table,), text=True)
    translation = struct.pack("<HH", LANGUAGE, CODEPAGE)
    var = version_block("Translation", translation)
    var_file_info = version_block("VarFileInfo", children=(var,), text=True)
    return version_block("VS_VERSION_INFO", fixed, (string_file_info, var_file_info), value_length=len(fixed))


def build_manifest(version: tuple[int, int, int], executable_name: str) -> bytes:
    version_quad = f"{version[0]}.{version[1]}.{version[2]}.0"
    xml = f'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
  <assemblyIdentity version="{version_quad}" processorArchitecture="amd64" name="AstroFocusStudio.{Path(executable_name).stem}" type="win32"/>
  <description>AstroFocus Studio</description>
  <trustInfo xmlns="urn:schemas-microsoft-com:asm.v3">
    <security><requestedPrivileges><requestedExecutionLevel level="asInvoker" uiAccess="false"/></requestedPrivileges></security>
  </trustInfo>
  <compatibility xmlns="urn:schemas-microsoft-com:compatibility.v1">
    <application>
      <supportedOS Id="{{e2011457-1546-43c5-a5fe-008deee3d3f0}}"/>
      <supportedOS Id="{{35138b9a-5d96-4fbd-8e2d-a2440225f93a}}"/>
      <supportedOS Id="{{4a2f28e3-53b9-4441-ba9c-d69d4a4a6e38}}"/>
      <supportedOS Id="{{1f676c76-80e1-4239-95bb-83d0f6d0da78}}"/>
      <supportedOS Id="{{8e0f7a12-bfb3-4fe8-b9a5-48fd50a15a9a}}"/>
    </application>
  </compatibility>
  <application xmlns="urn:schemas-microsoft-com:asm.v3">
    <windowsSettings>
      <dpiAware xmlns="http://schemas.microsoft.com/SMI/2005/WindowsSettings">false</dpiAware>
      <gdiScaling xmlns="http://schemas.microsoft.com/SMI/2017/WindowsSettings">true</gdiScaling>
      <longPathAware xmlns="http://schemas.microsoft.com/SMI/2016/WindowsSettings">true</longPathAware>
    </windowsSettings>
  </application>
</assembly>
'''
    return xml.encode("utf-8")


def read_icon(icon_path: Path) -> tuple[list[tuple[int, bytes]], bytes]:
    source = icon_path.read_bytes()
    reserved, icon_type, count = struct.unpack_from("<HHH", source, 0)
    if reserved != 0 or icon_type != 1 or count < 1:
        raise ValueError(f"{icon_path} is not a valid Windows icon")
    entries = []
    group = bytearray(struct.pack("<HHH", 0, 1, count))
    for index in range(count):
        entry = struct.unpack_from("<BBBBHHII", source, 6 + index * 16)
        size, offset = entry[6], entry[7]
        if offset + size > len(source):
            raise ValueError("icon image points outside the file")
        resource_id = index + 1
        entries.append((resource_id, source[offset : offset + size]))
        group += struct.pack("<BBBBHHIH", *entry[:7], resource_id)
    return entries, bytes(group)


def generate(icon_path: Path, version_path: Path, output_path: Path, executable_name: str, description: str) -> None:
    version = read_version(version_path)
    icon_entries, group = read_icon(icon_path)
    output = bytearray(null_record())
    for resource_id, image in icon_entries:
        output += resource_record(3, resource_id, image)
    output += resource_record(14, 101, group)
    output += resource_record(16, 1, build_version_info(version, executable_name, description))
    output += resource_record(24, 1, build_manifest(version, executable_name), language=0)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_bytes(output)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--icon", type=Path, required=True)
    parser.add_argument("--version-file", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--exe", required=True)
    parser.add_argument("--description", required=True)
    args = parser.parse_args()
    generate(args.icon, args.version_file, args.output, args.exe, args.description)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
