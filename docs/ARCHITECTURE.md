# Architecture

## Processes

`AstroFocusStudio.exe` is the visible Win32 frontend. It starts the hidden
`AstroFocusEngine.exe`, reads status and frames over the loopback endpoint, and
never communicates directly with ASCOM devices.

The engine owns autofocus, focus safety, session data, simulator logic and the
local API. Potentially blocking ASCOM calls run in isolated camera/focuser host
processes. The setup and updater launchers are separate no-CRT Windows programs.

## Safety boundaries

- The HTTP listener binds to `127.0.0.1` only.
- The endpoint port is defined once in `common/local_endpoint.h`.
- Device movement is rejected during unsafe exposure or reservation states.
- A timed-out or unconfirmed move invalidates the trusted focus position.
- Mutation routes reject duplicate parameters and foreign browser origins.

## Source layout

- `frontend/`: Win32 user interface and local engine client.
- `backend/`: focus engine, API, automation and simulator.
- `device_host/`: isolated device worker executable.
- `focuser_setup/`: isolated ASCOM setup dialog.
- `common/`: shared version, endpoint and process-entry safety code.
- `installer/`, `updater/`, `release/`: packaging and update chain.
- `tests/`: source contracts and native ASan/UBSan tests.

## Planned refactoring

The frontend and backend are intentionally still single translation units.
Splitting them requires behaviour-preserving extraction and Windows hardware
regression testing. A future headless-engine/Named-Pipe migration should be
performed as a separate compatibility project, not mixed into a release cleanup.
