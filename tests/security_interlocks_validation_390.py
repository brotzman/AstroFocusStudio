from pathlib import Path

root = Path(__file__).resolve().parents[1]
backend = (root / 'backend' / 'backend.cpp').read_text(encoding='utf-8')
frontend = (root / 'frontend' / 'frontend.cpp').read_text(encoding='utf-8')
host = (root / 'device_host' / 'device_host.cpp').read_text(encoding='utf-8')
finish_start = frontend.index('static void FinishFocuserSetup')
finish_end = frontend.index('static void PollFocuserSetupProcess', finish_start)
finish = frontend[finish_start:finish_end]
begin_start = frontend.index('static void BeginFocuserSetup')
begin_end = frontend.index('static BOOL IsSafeUvcDeviceName', begin_start)
begin = frontend[begin_start:begin_end]
release_start = frontend.index('static BOOL ReleaseFocuserSetupEngineReservation')
release_end = frontend.index('static void FinishFocuserSetup', release_start)
release = frontend[release_start:release_end]
checks = {
    'frontend acquires engine reservation before helper launch': begin.index('ApiAction("focuser-setup-begin")') < begin.index('CreateProcessW(exe,cmd'),
    'frontend central release helper calls engine and verifies status': 'ApiAction("focuser-setup-end")' in release and 'PollStatus()' in release and '!g_state.focuserSetupActive' in release,
    'frontend releases reservation before reconnect': finish.index('ReleaseFocuserSetupEngineReservation()') < finish.index('ApiAction("focuser-connect")'),
    'frontend launch failure releases before optional reconnect': begin.index('ReleaseFocuserSetupEngineReservation()') < begin.rindex('ApiAction("focuser-connect")'),
    'frontend releases reservation during shutdown': 'ApiActionTimed("focuser-setup-end",500)' in frontend,
    'backend exposes setup state': r'\"focuserSetupActive\":%s' in backend and 'g_focuserSetupReserved?"true":"false"' in backend,
    'backend blocks core movement while reserved': 'static BOOL MoveFocuser(int target){if(g_focuserSetupReserved)' in backend,
    'backend blocks direct ASCOM worker startup while reserved': 'static BOOL ConnectAscomFocuserWorker(BOOL silent){\n    if(g_focuserSetupReserved)' in backend,
    'backend automatic reconnect checks reservation': 'if(!g_focuserSetupReserved&&g_focuserWanted' in backend,
    'backend reservation rejects wanted reconnect state': 'g_focuserConnected||g_focuserWanted||g_focuserWorker' in backend,
    'backend rejects duplicate mutation keys before dispatch': backend.index('mutationRoute&&QueryHasDuplicateKeys') < backend.index('if(RequestPathEquals(req,"/api/action"))'),
    'device host rejects malformed or duplicate health checks': 'healthCheckCount<0||healthCheckCount>1' in host and 'ExitProcess(2)' in host,
}
for name, ok in checks.items():
    print(f'{name}: {"PASS" if ok else "FAIL"}')
print(f'SUMMARY {sum(checks.values())}/{len(checks)}')
raise SystemExit(0 if all(checks.values()) else 1)
