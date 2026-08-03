# Local API

The engine binds to the IPv4 loopback address only. The default endpoint is
`http://127.0.0.1:8873`; the port constant is defined in
`common/local_endpoint.h`.

Read-only Observatory endpoints include:

- `/api/v1/status`
- `/api/v1/focus-model`

The legacy frontend control routes `/api/action`, `/api/toggle` and `/api/set`
are local mutation routes. They reject duplicate query keys and browser requests
from foreign origins. They are not a network authentication boundary and must
never be exposed through port forwarding or a reverse proxy.

A future API revision should move mutations to authenticated `POST` requests and
separate public read-only HTTP from frontend/engine IPC.
