#pragma once

// Single source of truth for the loopback-only frontend/engine endpoint.
// Keep this private to the local machine; the public read-only Observatory API
// is served by the same process but is never bound to a non-loopback address.
#define AFS_LOCAL_HTTP_PORT 8873
#define AFS_LOCAL_HTTP_PORT_TEXT_A "8873"
#define AFS_LOCAL_HTTP_PORT_TEXT_W L"8873"
#define AFS_LOCAL_HTTP_BASE_A "http://127.0.0.1:" AFS_LOCAL_HTTP_PORT_TEXT_A
#define AFS_LOCAL_HTTP_BASE_W L"http://127.0.0.1:" AFS_LOCAL_HTTP_PORT_TEXT_W
