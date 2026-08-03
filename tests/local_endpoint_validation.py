from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
header = (ROOT / "common" / "local_endpoint.h").read_text(encoding="utf-8")
front = (ROOT / "frontend" / "frontend.cpp").read_text(encoding="utf-8")
back = (ROOT / "backend" / "backend.cpp").read_text(encoding="utf-8")
checks = []

def check(name: str, ok: bool) -> None:
    checks.append(ok)
    print(f"{name}: {'PASS' if ok else 'FAIL'}")

check("loopback port has one central numeric definition", "#define AFS_LOCAL_HTTP_PORT 8873" in header)
check("frontend and backend include the endpoint header", '../common/local_endpoint.h' in front and '../common/local_endpoint.h' in back)
check("both sockets use the central port constant", "p_htons(AFS_LOCAL_HTTP_PORT)" in front and "g_httpPort=AFS_LOCAL_HTTP_PORT" in back)
check("engine listener binds only to loopback", "p_htonl(INADDR_LOOPBACK_MIN)" in back)
check("browser URL uses the central loopback base", "AFS_LOCAL_HTTP_BASE_W" in back)
check("foreign browser origins remain blocked", "BrowserMutationAllowed" in back and "Browser-Anfrage von fremder Herkunft blockiert" in back)
check("duplicate mutation keys remain fail-closed", "mutationRoute&&QueryHasDuplicateKeys" in back)
check("active frontend/backend code has no independent numeric port literal", "8873" not in front and "8873" not in back)

print(f"SUMMARY {sum(checks)}/{len(checks)}")
raise SystemExit(0 if all(checks) else 1)
