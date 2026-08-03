# Security policy

## Reporting a vulnerability

Please do not publish exploitable details in a public issue. Report the affected
version, a minimal reproduction, expected impact, and relevant logs privately to
the repository owner. Remove camera credentials, device identifiers, file-system
paths, and other personal data before sharing diagnostics.

## Supported code

Security fixes target the current version in `VERSION`. Historical source and
unsigned development packages are not supported production releases.

## Security boundaries

- Frontend and engine communicate only over the IPv4 loopback interface.
- Device drivers run in isolated host processes where supported.
- Focus movement is blocked when the engine cannot prove a safe device state.
- Production packages require Authenticode signing and a protected update key.
- The bundled development build is intentionally unsigned and must not be used
  for unattended production operation without local validation.
