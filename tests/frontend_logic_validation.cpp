#define ASTROFOCUS_NATIVE_TEST 1
#define WinMainCRTStartup Frontend_WinMainCRTStartup
#include "../frontend/frontend.cpp"

extern "C" {
int printf(const char*,...);
int vswprintf(wchar_t*, unsigned long, const wchar_t*, __builtin_va_list);
int WINAPI wsprintfW(LPWSTR d,LPCWSTR f,...){__builtin_va_list ap;__builtin_va_start(ap,f);int n=vswprintf(d,1024,f,ap);__builtin_va_end(ap);return n;}
static SIZE_T maxAllocation=0;
HANDLE WINAPI GetProcessHeap(void){return (HANDLE)1;}
LPVOID WINAPI HeapAlloc(HANDLE,DWORD,SIZE_T n){if(n>maxAllocation)maxAllocation=n;return __builtin_malloc(n);}
BOOL WINAPI HeapFree(HANDLE,DWORD,LPVOID p){__builtin_free(p);return TRUE;}
int WINAPI lstrlenW(LPCWSTR s){int n=0;while(s&&s[n])n++;return n;}
LPWSTR WINAPI lstrcpyW(LPWSTR d,LPCWSTR s){LPWSTR r=d;while(1){*d=*s;if(!*s)break;d++;s++;}return r;}
LPWSTR WINAPI lstrcatW(LPWSTR d,LPCWSTR s){LPWSTR r=d;while(*d)d++;while(1){*d=*s;if(!*s)break;d++;s++;}return r;}
int WINAPI MultiByteToWideChar(UINT,DWORD,const char* in,int,wchar_t* out,int cap){if(!out||cap<=0)return 0;int n=0;while(in&&in[n]&&n<cap-1){out[n]=(unsigned char)in[n];n++;}out[n]=0;return n+1;}
int WINAPI WideCharToMultiByte(UINT,DWORD,LPCWSTR in,int,char* out,int cap,const char*,BOOL*){if(!out||cap<=0)return 0;int n=0;while(in&&in[n]&&n<cap-1){out[n]=(char)(in[n]&127);n++;}out[n]=0;return n+1;}
BOOL WINAPI ShowWindow(HWND,int){return TRUE;}
BOOL WINAPI InvalidateRect(HWND,const RECT*,BOOL){return TRUE;}
static HWND lastMovedH=0;static int lastMoveX=0,lastMoveY=0,lastMoveW=0,lastMoveH=0;
BOOL WINAPI MoveWindow(HWND h,int x,int y,int w,int hh,BOOL){lastMovedH=h;lastMoveX=x;lastMoveY=y;lastMoveW=w;lastMoveH=hh;return TRUE;}
static wchar_t fakeText[256][2048];static BOOL fakeEnabled[256];static int fakeComboSel[256];static int fakeNextHandle=0;
BOOL WINAPI SetWindowTextW(HWND h,LPCWSTR str){int i=(int)(ULONG_PTR)h-1;if(i>=0&&i<256){int n=0;while(str&&str[n]&&n<127){fakeText[i][n]=str[n];n++;}fakeText[i][n]=0;}return TRUE;}
int WINAPI GetWindowTextW(HWND h,LPWSTR out,int cap){if(!out||cap<=0)return 0;int i=(int)(ULONG_PTR)h-1,n=0;if(i>=0&&i<256){while(fakeText[i][n]&&n<cap-1){out[n]=fakeText[i][n];n++;}}out[n]=0;return n;}
BOOL WINAPI EnableWindow(HWND h,BOOL on){int i=(int)(ULONG_PTR)h-1;if(i>=0&&i<256)fakeEnabled[i]=on;return TRUE;}
void WINAPI GetLocalTime(SYSTEMTIME* s){s->wYear=2026;s->wMonth=7;s->wDay=31;s->wHour=12;s->wMinute=0;s->wSecond=0;s->wMilliseconds=0;}
static ULONGLONG fakeTick=1000;ULONGLONG WINAPI GetTickCount64(void){return fakeTick;}
static BOOL fakeThemeIo=FALSE;static char fakeThemeTemp[128],fakeThemeFinal[128];static DWORD fakeThemeTempSize=0,fakeThemeFinalSize=0;static int fakeThemeMoveCount=0,fakeThemeFlushCount=0;
static BOOL FakeWContains(LPCWSTR text,LPCWSTR needle){if(!text||!needle||!needle[0])return FALSE;for(int i=0;text[i];i++){int j=0;while(needle[j]&&text[i+j]==needle[j])j++;if(!needle[j])return TRUE;}return FALSE;}
static HANDLE FakeThemeTempHandle(){return (HANDLE)(ULONG_PTR)0x5101;}static HANDLE FakeThemeFinalHandle(){return (HANDLE)(ULONG_PTR)0x5102;}
HANDLE WINAPI CreateFileW(LPCWSTR path,DWORD,DWORD,SECURITY_ATTRIBUTES*,DWORD creation,DWORD,HANDLE){if(!fakeThemeIo||!path)return INVALID_HANDLE_VALUE;BOOL isTemp=FakeWContains(path,L".tmp.");if(creation==CREATE_ALWAYS&&isTemp){fakeThemeTempSize=0;return FakeThemeTempHandle();}if(creation==OPEN_EXISTING&&!isTemp&&fakeThemeFinalSize>0)return FakeThemeFinalHandle();return INVALID_HANDLE_VALUE;}
DWORD WINAPI SetFilePointer(HANDLE,LONG,LONG*,DWORD){return 0;}
BOOL WINAPI ReadFile(HANDLE h,LPVOID out,DWORD n,DWORD* read,LPVOID){if(read)*read=0;if(!fakeThemeIo||h!=FakeThemeFinalHandle()||!out)return FALSE;DWORD take=fakeThemeFinalSize<n?fakeThemeFinalSize:n;for(DWORD i=0;i<take;i++)((char*)out)[i]=fakeThemeFinal[i];if(read)*read=take;return TRUE;}
BOOL WINAPI WriteFile(HANDLE h,LPCVOID in,DWORD n,DWORD* written,LPVOID){if(written)*written=0;if(!fakeThemeIo||h!=FakeThemeTempHandle()||!in||n>sizeof(fakeThemeTemp))return FALSE;for(DWORD i=0;i<n;i++)fakeThemeTemp[i]=((const char*)in)[i];fakeThemeTempSize=n;if(written)*written=n;return TRUE;}
BOOL WINAPI FlushFileBuffers(HANDLE h){if(!fakeThemeIo||h!=FakeThemeTempHandle())return FALSE;fakeThemeFlushCount++;return TRUE;}
BOOL WINAPI MoveFileExW(LPCWSTR from,LPCWSTR to,DWORD flags){if(!fakeThemeIo||!FakeWContains(from,L".tmp.")||FakeWContains(to,L".tmp.")||!(flags&MOVEFILE_REPLACE_EXISTING)||!(flags&MOVEFILE_WRITE_THROUGH))return FALSE;for(DWORD i=0;i<fakeThemeTempSize;i++)fakeThemeFinal[i]=fakeThemeTemp[i];fakeThemeFinalSize=fakeThemeTempSize;fakeThemeTempSize=0;fakeThemeMoveCount++;return TRUE;}
static BOOL fakeProcessSignaled=FALSE;static int fakeCloseCount=0;
BOOL WINAPI CloseHandle(HANDLE){fakeCloseCount++;return TRUE;}
int WINAPI MessageBoxW(HWND,LPCWSTR,LPCWSTR,UINT){return 0;}
DWORD WINAPI GetFileAttributesW(LPCWSTR){return INVALID_FILE_ATTRIBUTES;}
DWORD WINAPI GetTempPathW(DWORD cap,LPWSTR out){if(!out||cap<4)return 0;out[0]=L'C';out[1]=L':';out[2]=L'\\';out[3]=0;return 3;}
DWORD WINAPI GetEnvironmentVariableW(LPCWSTR,LPWSTR out,DWORD cap){const wchar_t* v=L"C:\\Users\\Test\\AppData\\Local";int n=0;while(v[n])n++;if(!out||cap<=(DWORD)n)return (DWORD)(n+1);for(int i=0;i<=n;i++)out[i]=v[i];return (DWORD)n;}
BOOL WINAPI CreateDirectoryW(LPCWSTR,SECURITY_ATTRIBUTES*){return TRUE;}
DWORD WINAPI GetLastError(void){return ERROR_ALREADY_EXISTS;}
DWORD WINAPI GetCurrentProcessId(void){return 42;}
BOOL WINAPI DeleteFileW(LPCWSTR path){if(fakeThemeIo&&path&&FakeWContains(path,L".tmp."))fakeThemeTempSize=0;return TRUE;}
BOOL WINAPI CreateProcessW(LPCWSTR,LPWSTR,SECURITY_ATTRIBUTES*,SECURITY_ATTRIBUTES*,BOOL,DWORD,LPVOID,LPCWSTR,STARTUPINFOW*,PROCESS_INFORMATION*){return FALSE;}
DWORD WINAPI WaitForSingleObject(HANDLE,DWORD){return fakeProcessSignaled?WAIT_OBJECT_0:258U;}
BOOL WINAPI PostMessageW(HWND,UINT,WPARAM,LPARAM){return TRUE;}
static int fakeChecks[256];static int fakeComboMinVisible[256];static HWND FH(int i){return (HWND)(ULONG_PTR)(i+1);}static int FHI(HWND h){return (int)(ULONG_PTR)h-1;}
HWND WINAPI CreateWindowExW(DWORD,LPCWSTR,LPCWSTR text,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID){
    if(fakeNextHandle>=245)return 0; HWND h=FH(fakeNextHandle++); int i=FHI(h); fakeEnabled[i]=TRUE; if(text){int n=0;while(text[n]&&n<2047){fakeText[i][n]=text[n];n++;}fakeText[i][n]=0;} return h;
}

LRESULT WINAPI SendMessageW(HWND h,UINT msg,WPARAM w,LPARAM){int i=FHI(h);if(i>=0&&i<256){if(i<8&&msg==BM_GETCHECK)return fakeChecks[i]?BST_CHECKED:0;if(i<8&&msg==BM_SETCHECK){fakeChecks[i]=(w==BST_CHECKED);return 0;}if(msg==CB_GETCURSEL)return fakeComboSel[i];if(msg==CB_SETCURSEL){fakeComboSel[i]=(int)w;return w;}if(msg==CB_ADDSTRING)return 0;if(msg==CB_SETMINVISIBLE){fakeComboMinVisible[i]=(int)w;return TRUE;}}return 0;}
static char* fakeHttp=0;static int fakeHttpSize=0,fakeHttpPos=0,fakeConnectCount=0;
static SOCKET WINAPI FakeSocket(int,int,int){return 1;}
static int WINAPI FakeConnect(SOCKET,const SOCKADDR*,int){fakeConnectCount++;return 0;}
static int WINAPI FakeSend(SOCKET,const char*,int n,int){return n;}
static int WINAPI FakeRecv(SOCKET,char* out,int cap,int){if(fakeHttpPos>=fakeHttpSize)return 0;int n=fakeHttpSize-fakeHttpPos;if(n>32768)n=32768;if(n>cap)n=cap;for(int i=0;i<n;i++)out[i]=fakeHttp[fakeHttpPos+i];fakeHttpPos+=n;return n;}
static int WINAPI FakeClose(SOCKET){return 0;}
static int WINAPI FakeSetSockOpt(SOCKET,int,int,const char*,int){return 0;}
static unsigned short WINAPI FakeHtons(unsigned short v){return v;}
static unsigned long WINAPI FakeHtonl(unsigned long v){return v;}
}

static int check(bool ok,const char* name){printf("%-42s %s\n",name,ok?"PASS":"FAIL");return ok?1:0;}
int main(){
    int pass=0,total=0;
    g_main=FH(250); g_font=FH(249); g_small=FH(248); g_title=FH(247); g_mono=FH(246);
    CreateControls();
    Layout(1720,1020);
    UpdatePage();
    total++;pass+=check(fakeNextHandle>80,"Frontend startup: all controls created in native harness");
    wchar_t userSettingsPath[700];BOOL userSettingsPathOk=BuildUserDataFilePath(L"AstroFocusUiSettings.ini",userSettingsPath,700);
    total++;pass+=check(userSettingsPathOk&&WEqual(userSettingsPath,L"C:\\Users\\Test\\AppData\\Local\\AstroFocusStudio\\AstroFocusUiSettings.ini"),"3.9.0 frontend: theme settings resolve to per-user LOCALAPPDATA");
    fakeThemeIo=TRUE;fakeThemeTempSize=fakeThemeFinalSize=0;fakeThemeMoveCount=fakeThemeFlushCount=0;g_themeMode=THEME_DARK;BOOL themeSaved=SaveThemeSetting();g_themeMode=THEME_SYSTEM;LoadThemeSetting();
    total++;pass+=check(themeSaved&&g_themeMode==THEME_DARK&&fakeThemeFlushCount==1&&fakeThemeMoveCount==1&&fakeThemeFinalSize>0,"3.9.0 frontend: theme settings save atomically and reload per user");fakeThemeIo=FALSE;
    const char* json="{\"version\":\"3.9.0\",\"camera\":true,\"focuser\":true,\"autofocus\":false,\"stepAssistantActive\":true,\"live\":true,\"frameReady\":true,\"frameSequence\":17,\"frameAgeMs\":240,\"simulator\":true,\"external\":false,\"native\":false,\"stretch\":true,\"stars\":true,\"values\":true,\"saturation\":true,\"zones\":true,\"bahtinov\":false,\"preferredOut\":true,\"autoRefocus\":true,\"autoRefocusAutomaticRun\":true,\"autoRefocusReferenceReady\":true,\"autoRefocusReferenceFwhm\":3.10,\"autoRefocusPaused\":true,\"autoRefocusTimeEnabled\":false,\"autoRefocusTemperatureEnabled\":true,\"autoRefocusFwhmEnabled\":true,\"autoRefocusTemperatureRequired\":true,\"autoRefocusLiveWillResume\":true,\"autofocusErrorAutomatic\":true,\"autoRefocusFailureCount\":2,\"autoRefocusBadFrameStreak\":3,\"autoRefocusElapsedMinutes\":62.5,\"autoRefocusNextMinutes\":-1.0,\"autoRefocusTempDelta\":1.7,\"autoRefocusFwhmDegradePercent\":14.2,\"autoRefocusRetrySeconds\":12,\"autoRefocusCooldownRemainingMinutes\":7.5,\"autoRefocusLastReason\":\"Temperaturänderung\",\"autofocusErrorCode\":\"AF_CAMERA_CAPTURE_FAILED\",\"autofocusErrorTitle\":\"Kameraaufnahme fehlgeschlagen\",\"autofocusErrorDetail\":\"Testdetail\",\"cameraWorkerBlocked\":true,\"cameraWorkerRetrySeconds\":30,\"cameraWorkerOperation\":\"ImageReady\",\"focuserWorkerBlocked\":false,\"focuserWorkerRetrySeconds\":0,\"focuserWorkerOperation\":\"–\",\"manualStarLocked\":true,\"afUseSelectedStar\":true,\"cameraName\":\"Synthetische Kamera\",\"focuserName\":\"Simulator\",\"status\":\"Live\",\"profile\":\"Test\",\"selfTestSummary\":\"19 von 19\",\"tiltDirection\":\"rechts unten\",\"exposure\":\"800\",\"gain\":\"180\",\"manualStep\":\"100\",\"afPoints\":\"9\",\"afStep\":\"120\",\"afSamples\":\"2\",\"backlash\":\"250\",\"refocusMinutes\":\"60\",\"refocusTemp\":\"1,5\",\"refocusFwhmPercent\":25.0,\"refocusBadFrames\":4,\"refocusMinStars\":5,\"refocusStability\":0.4,\"refocusCooldown\":12.0,\"position\":24180,\"starCount\":3,\"usedStars\":2,\"selfTestPassed\":19,\"selfTestTotal\":19,\"safeMin\":0,\"safeMax\":60000,\"fwhm\":3.25,\"hfr\":1.55,\"snr\":42.5,\"ecc\":0.12,\"stability\":0.08,\"temperature\":12.3,\"hasTemperature\":true,\"selectedFwhm\":3.1,\"selectedHfr\":1.5,\"selectedSnr\":50,\"selectedEcc\":0.1,\"bahtOffset\":0,\"bahtConfidence\":0,\"sharpness\":90,\"bahtValid\":false,\"tilt\":0.4,\"tiltValid\":true,\"zoneFwhm\":[3,3.1,3.2,3.1,3,3.2,3.3,3.2,3.4],\"zoneCounts\":[2,2,2,2,2,2,2,2,2],\"afPositions\":[24060,24180,24300],\"afMetrics\":[1.2,1,1.3],\"afFwhmMetrics\":[3.4,3.1,3.5],\"afMeasuredCount\":3,\"afFitValid\":true,\"afFitFwhmValid\":true,\"afFitA\":0.2,\"afFitB\":0,\"afFitC\":1.0,\"afFitFwhmA\":0.4,\"afFitFwhmB\":0,\"afFitFwhmC\":3.1,\"afFitCenter\":24180,\"afFitScale\":120,\"afFitR2\":0.99,\"afFitFwhmR2\":0.98,\"afFitConfidence\":0.95,\"afBestPosition\":24180,\"afExpectedHfr\":1.0,\"afExpectedFwhm\":3.1,\"afFinalValid\":true,\"afFinalPosition\":24180,\"afFinalHfr\":1.02,\"afFinalFwhm\":3.12,\"starX\":[100,200,300],\"starY\":[150,250,350],\"starFwhm\":[3.1,3.2,3.3],\"starUsed\":[1,1,0],\"starSaturated\":[0,1,0],\"selectedStar\":1}";
    ParseStatus(json);
    total++;pass+=check(g_state.camera&&g_state.focuser&&g_state.live&&g_state.simulator&&g_state.stepAssistantActive,"Frontend: Status- und Schritt-Assistent-Bools");
    total++;pass+=check(g_state.stars&&g_state.starsCount==3&&g_state.usedStars==2,"Frontend: Overlay-Schalter/Anzahl getrennt");
    total++;pass+=check(g_state.manualStarLocked&&g_state.afUseSelectedStar,"Frontend: manuelle AF-Sternauswahl geparst");
    total++;pass+=check(g_state.autoRefocus&&g_state.autoRefocusAutomaticRun&&g_state.autoRefocusReferenceReady&&g_state.autoRefocusPaused&&!g_state.autoRefocusTimeEnabled&&g_state.autoRefocusTemperatureEnabled&&g_state.autoRefocusFwhmEnabled&&g_state.autoRefocusTemperatureRequired&&g_state.autoRefocusLiveWillResume&&g_state.autofocusErrorAutomatic&&g_state.autoRefocusRetrySeconds==12&&g_state.autoRefocusFailureCount==2&&g_state.autoRefocusBadFrameStreak==3&&g_state.autoRefocusElapsedMinutes>62.4&&g_state.autoRefocusNextMinutes<0.0&&g_state.autoRefocusTempDelta>1.6&&g_state.autoRefocusFwhmDegradePercent>14.1&&g_state.autoRefocusCooldownRemainingMinutes>7.4&&g_state.autoRefocusLastReason[0]==L'T'&&g_state.autofocusErrorCode[0]==L'A',"Frontend: Auto-Refokus-Status geparst");
    total++;pass+=check(g_state.refocusFwhmPercent>24.9&&g_state.refocusBadFrames==4&&g_state.refocusMinStars==5&&g_state.refocusStability>0.39&&g_state.refocusCooldown>11.9,"Frontend: konfigurierbare Refokus-Grenzen geparst");
    total++;pass+=check(g_state.autoRefocusReferenceFwhm>3.09&&g_state.autoRefocusReferenceFwhm<3.11,"Frontend: FWHM-Referenz für Live-Trend geparst");
    total++;pass+=check(g_state.cameraWorkerBlocked&&!g_state.focuserWorkerBlocked&&g_state.cameraWorkerRetrySeconds==30&&g_state.cameraWorkerOperation[0]==L'I',"Frontend: ASCOM-Worker-Watchdogstatus geparst");
    total++;pass+=check(g_state.starArrayCount==3&&g_state.starX[1]==200&&g_state.starSaturated[1]==1,"Frontend: Overlay-Arrays");
    total++;pass+=check(g_state.afCount==3&&g_state.afMeasuredCount==3&&g_state.afPos[1]==24180&&g_state.afMetric[1]==1.0&&g_state.afFwhm[1]==3.1,"Frontend: HFR/FWHM-Autofokuskurve");
    total++;pass+=check(g_state.afFitValid&&g_state.afFitFwhmValid&&g_state.afBestPosition==24180&&g_state.afFitConfidence>0.9,"Frontend: Autofokus-Fitdaten");
    total++;pass+=check(g_state.afFinalValid&&g_state.afFinalPosition==24180&&g_state.afFinalFwhm>3.11&&g_state.afFinalFwhm<3.13,"Frontend: bestätigter Autofokus-Endwert");
    total++;pass+=check(g_state.zoneCount[8]==2&&g_state.zone[8]>3.39,"Frontend: 3x3-Zonendaten");
    BYTE u[4]={0x78,0x56,0x34,0x12};total++;pass+=check(GetLe32(u)==0x12345678U,"Frontend: ausrichtungsfreies Little-Endian");
    BYTE* bmp=(BYTE*)Alloc(70);memset(bmp,0,70);bmp[0]='B';bmp[1]='M';bmp[2]=70;bmp[10]=54;bmp[14]=40;bmp[18]=2;bmp[22]=2;bmp[26]=1;bmp[28]=32;total++;pass+=check(InstallBmpFrame(bmp,70)&&g_frameW==2&&g_frameH==2&&g_frameBpp==32,"Frontend: gültiges BMP wird übernommen");
    BYTE* bad=(BYTE*)Alloc(60);memset(bad,0,60);bad[0]='B';bad[1]='M';bad[2]=70;bad[10]=54;bad[14]=40;bad[18]=2;bad[22]=2;bad[26]=1;bad[28]=32;total++;pass+=check(!InstallBmpFrame(bad,60),"Frontend: abgeschnittenes BMP wird verworfen");
    Layout(1490,940);
    bool layout=g_preview.left>=330&&g_preview.right<g_rightAnalysis.left&&g_preview.bottom<g_page.top&&g_rightAnalysis.bottom<g_rightStar.top&&g_rightStar.bottom<g_rightTrend.top&&g_rightTrend.bottom<g_rightField.top&&g_rightField.bottom<=954;
    total++;pass+=check(layout,"Frontend: Mindestgrößen-Layout ohne Überlappung");
    Layout(1920,1080);
    total++;pass+=check(g_preview.right<g_rightAnalysis.left&&g_page.right<g_rightAnalysis.left,"Frontend: maximiertes Layout ohne Überlappung");
    total++;pass+=check(WEqual(fakeText[FHI(hSimApply)],L"Simulation übernehmen")&&SimulatorApplyButtonWidth(790)>=190,"3.9.0 frontend: Simulation-übernehmen-Schaltfläche ist vollständig beschriftet und breit genug");
    wchar_t fd[32];FormatD(1.999,2,fd);total++;pass+=check(fd[0]==L'2'&&fd[1]==L','&&fd[2]==L'0'&&fd[3]==L'0',"Frontend: Dezimalrundung mit Übertrag");
    wchar_t signedValue[32];FormatSignedInt(7,signedValue,32);total++;pass+=check(WEqual(signedValue,L"+7"),"Frontend: positives Vorzeichen wird ohne wsprintf-Plusflag formatiert");
    FormatSignedInt(0,signedValue,32);total++;pass+=check(WEqual(signedValue,L"0"),"Frontend: Nullwert bleibt ohne positives Vorzeichen");
    FormatSignedInt(-7,signedValue,32);total++;pass+=check(WEqual(signedValue,L"-7"),"Frontend: negatives Vorzeichen bleibt erhalten");
    total++;pass+=check(WEqual(g_state.version,L"3.9.0"),"Frontend: exakte Engine-Version geparst");
    total++;pass+=check(IsSafeUvcDeviceName(L"USB Camera")&&!IsSafeUvcDeviceName(L"USB \"Camera")&&!IsSafeUvcDeviceName(L"USB\nCamera"),"Frontend: UVC-Gerätenamen gegen Befehlsbruch validiert");
    wchar_t escapedText[64];JString("{\"x\":\"A\\nB\\\"C\"}","x",escapedText,64);total++;pass+=check(escapedText[0]==L'A'&&escapedText[1]==L'\n'&&escapedText[2]==L'B'&&escapedText[3]==L'\"'&&escapedText[4]==L'C',"Frontend: JSON-String-Escapes korrekt");
    FormatD(-0.5,1,fd);total++;pass+=check(fd[0]==L'-'&&fd[1]==L'0'&&fd[2]==L','&&fd[3]==L'5',"Frontend: negatives Dezimalformat nahe null");
    g_ws2=(HMODULE)1;p_socket=FakeSocket;p_connect=FakeConnect;p_send=FakeSend;p_recv=FakeRecv;p_closesocket=FakeClose;p_setsockopt=FakeSetSockOpt;p_htons=FakeHtons;p_htonl=FakeHtonl;
    char responseFalse[256],responseTrue[256];const char* resultFalse="{\"ok\":false,\"message\":\"abgelehnt\"}";const char* resultTrue="{\"ok\":true,\"message\":\"ok\"}";sprintf(responseFalse,"HTTP/1.1 200 OK\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s",(int)strlen(resultFalse),resultFalse);sprintf(responseTrue,"HTTP/1.1 200 OK\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s",(int)strlen(resultTrue),resultTrue);
    fakeHttp=responseFalse;fakeHttpSize=(int)strlen(responseFalse);fakeHttpPos=0;BOOL rejected=!ApiPath("/api/action?name=test");fakeHttp=responseTrue;fakeHttpSize=(int)strlen(responseTrue);fakeHttpPos=0;BOOL accepted=ApiPath("/api/action?name=test");total++;pass+=check(rejected&&accepted,"Frontend: API wertet ok true/false aus");
    char toupErrorResponse[512];const char* toupErrorBody="{\"ok\":false,\"message\":\"Die 64-Bit-toupcam.dll wurde nicht gefunden oder ist inkompatibel.\"}";sprintf(toupErrorResponse,"HTTP/1.1 200 OK\r\nContent-Length: %d\r\nConnection: close\r\n\r\n%s",(int)strlen(toupErrorBody),toupErrorBody);fakeHttp=toupErrorResponse;fakeHttpSize=(int)strlen(toupErrorResponse);fakeHttpPos=0;BOOL toupRejected=!ApiPath("/api/action?name=camera-connect");total++;pass+=check(toupRejected&&!g_lastApiTransportFailure&&WTextContains(g_lastApiMessage,L"toupcam.dll"),"3.9.0 frontend: genaue ToupTek-Engineursache bleibt erhalten");
    hFocBackend=FH(1);fakeComboSel[1]=0;g_ascomChooserProcess=0;fakeConnectCount=0;fakeHttp=responseTrue;fakeHttpSize=(int)strlen(responseTrue);fakeHttpPos=0;FocuserConnect();total++;pass+=check(fakeConnectCount>=1&&g_ascomChooserProcess==0,"3.9.0 frontend: Simulator-Fokussierer verbindet ohne ASCOM-Chooser");
    g_main=(HWND)1;g_pendingStarX=320;g_pendingStarY=240;g_starSelectionQueued=TRUE;g_starSelectionBusy=FALSE;g_commandBusy=FALSE;g_statusRefreshRequested=FALSE;fakeConnectCount=0;fakeHttp=responseTrue;fakeHttpSize=(int)strlen(responseTrue);fakeHttpPos=0;ExecuteQueuedStarSelection();total++;pass+=check(fakeConnectCount==1&&g_statusRefreshRequested&&!g_starSelectionBusy&&!g_starSelectionQueued,"Frontend: Sternauswahl nutzt genau einen entkoppelten API-Aufruf");
    char overflowResponse[]="HTTP/1.1 200 OK\r\nContent-Length: 999999999999999999999999\r\nConnection: close\r\n\r\n";fakeHttp=overflowResponse;fakeHttpSize=(int)strlen(overflowResponse);fakeHttpPos=0;BYTE* overflowBody=0;DWORD overflowSize=0;BOOL overflowRejected=!HttpGet("/api/status",&overflowBody,&overflowSize,65536);total++;pass+=check(overflowRejected&&overflowBody==0,"Frontend: übergroße Content-Length wird verworfen");
    hAutoRefocus=FH(0);hStatus=0;g_state.autoRefocus=FALSE;fakeChecks[0]=0;fakeHttp=responseTrue;fakeHttpSize=(int)strlen(responseTrue);fakeHttpPos=0;BOOL toggleAccepted=ApplyAutoRefocusToggle(TRUE);total++;pass+=check(toggleAccepted&&g_state.autoRefocus&&Checked(hAutoRefocus),"Frontend: bestätigter Auto-Refokus-Haken bleibt gesetzt");
    g_state.autoRefocus=FALSE;fakeChecks[0]=0;fakeHttp=responseFalse;fakeHttpSize=(int)strlen(responseFalse);fakeHttpPos=0;BOOL toggleRejected=!ApplyAutoRefocusToggle(TRUE);total++;pass+=check(toggleRejected&&!g_state.autoRefocus&&!Checked(hAutoRefocus),"Frontend: abgelehnter Auto-Refokus-Haken wird zurückgesetzt");g_ws2=0;fakeHttp=0;
    AppState same=g_state;same.frameAgeMs+=5000;total++;pass+=check(!PreviewStateChanged(&same),"Frontend: Framealter löst kein Repaint aus");
    AppState older=g_state;older.frameSequence=g_state.frameSequence-1;total++;pass+=check(PreviewStateChanged(&older),"Frontend: neue Frame-ID löst Repaint aus");
    g_lastLoadedFrameSequence=g_state.frameSequence;g_frame=(BYTE*)1;total++;pass+=check(g_lastLoadedFrameSequence==g_state.frameSequence,"Frontend: geladene Frame-ID wird gespeichert");g_frame=0;
    const char* hostile="{\"version\":\"3.9.0\",\"frameSequence\":1e300,\"frameAgeMs\":-99,\"selectedStar\":999999999999999999999,\"refocusMinStars\":-5,\"starX\":[nan,1e300,42],\"starY\":[20,30,40],\"starFwhm\":[2,3,4],\"starUsed\":[1,1,1],\"starSaturated\":[0,0,0],\"afPositions\":[1e300,-1e300,5],\"afMeasuredCount\":999999999999999999999}";ParseStatus(hostile);total++;pass+=check(g_state.frameSequence==2147483647&&g_state.frameAgeMs==0&&g_state.selectedStar==-1&&g_state.refocusMinStars==1,"Frontend: extreme Ganzzahlen werden sicher begrenzt");total++;pass+=check(g_state.starArrayCount==3&&g_state.starX[0]==0.0&&g_state.starX[1]==0.0&&g_state.starX[2]==42.0&&g_state.afCount==3&&g_state.afPos[0]==2147483647&&g_state.afPos[1]==(-2147483647-1),"Frontend: NaN und Zahlenüberlauf werden neutralisiert");
    const int payload=2100000;char header[160];int hn=sprintf(header,"HTTP/1.1 200 OK\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",payload);fakeHttpSize=hn+payload;fakeHttp=(char*)__builtin_malloc(fakeHttpSize);for(int i=0;i<hn;i++)fakeHttp[i]=header[i];for(int i=0;i<payload;i++)fakeHttp[hn+i]=(char)(i&255);fakeHttpPos=0;maxAllocation=0;g_ws2=(HMODULE)1;p_socket=FakeSocket;p_connect=FakeConnect;p_send=FakeSend;p_recv=FakeRecv;p_closesocket=FakeClose;p_setsockopt=FakeSetSockOpt;p_htons=FakeHtons;p_htonl=FakeHtonl;BYTE* body=0;DWORD bodySize=0;BOOL httpOk=HttpGet("/frame.bmp",&body,&bodySize,128U*1024U*1024U);total++;pass+=check(httpOk&&bodySize==(DWORD)payload&&body[12345]==(BYTE)(12345&255)&&maxAllocation<16U*1024U*1024U,"Frontend: großer Bildabruf wächst speichereffizient");Free(body);__builtin_free(fakeHttp);fakeHttp=0;g_ws2=0;
    hExposure=FH(0);hGain=FH(1);hAfPoints=FH(2);hAfStep=FH(3);hAfSamples=FH(4);hBacklash=FH(5);hAfStart=FH(6);hAfHint=FH(7);g_state.autofocus=FALSE;g_state.stepAssistantActive=FALSE;g_state.backlashCalibrationActive=FALSE;g_engineOnline=TRUE;
    SetWindowTextW(hExposure,L"800");SetWindowTextW(hGain,L"180");SetWindowTextW(hAfPoints,L"9");SetWindowTextW(hAfStep,L"120");SetWindowTextW(hAfSamples,L"3");SetWindowTextW(hBacklash,L"250");wchar_t afErr[256];
    total++;pass+=check(ValidateAutofocusInputs(afErr,256),"Frontend: gültige AF-Eingaben lokal akzeptiert");
    SetWindowTextW(hAfStep,L"4");total++;pass+=check(!ValidateAutofocusInputs(afErr,256)&&afErr[0]!=0,"Frontend: ungültige Schrittweite lokal blockiert");
    SetWindowTextW(hAfStep,L"120");SetWindowTextW(hAfSamples,L"6");UpdateAutofocusInputState();total++;pass+=check(!fakeEnabled[6]&&fakeText[7][0]==L'P',"Frontend: Startknopf bei Parameterfehler deaktiviert");
    SetWindowTextW(hAfSamples,L"3");UpdateAutofocusInputState();total++;pass+=check(fakeEnabled[6],"Frontend: Startknopf bei gültigen Parametern aktiv");
    g_state.stepAssistantActive=TRUE;UpdateAutofocusInputState();total++;pass+=check(!fakeEnabled[6]&&fakeText[7][0]==L'E',"Frontend: Schritt-Assistent sperrt Autofokusstart");g_state.stepAssistantActive=FALSE;
    g_state.backlashCalibrationActive=TRUE;UpdateAutofocusInputState();total++;pass+=check(!fakeEnabled[6],"Frontend: Backlash-Kalibrierung sperrt Autofokusstart");g_state.backlashCalibrationActive=FALSE;
    SetAfPointComboFromText(L"12");total++;pass+=check(fakeComboSel[2]==3,"Frontend: alter Messpunktwert 12 wird auf 11 normalisiert");
    SetAfSampleComboFromText(L"8");total++;pass+=check(fakeComboSel[4]==4,"Frontend: ungültige Sample-Anzahl wird auf 5 begrenzt");
    lastMovedH=0;lastMoveH=0;PlaceDropDownCombo(hAfPoints,100,200,180,28,6);total++;pass+=check(lastMovedH==hAfPoints&&lastMoveH>=172&&fakeComboMinVisible[2]==6,"Frontend: Messpunkte-Dropdown besitzt sichtbare Auswahlliste");
    lastMovedH=0;lastMoveH=0;PlaceDropDownCombo(hAfSamples,100,200,180,28,5);total++;pass+=check(lastMovedH==hAfSamples&&lastMoveH>=148&&fakeComboMinVisible[4]==5,"Frontend: Samples-Dropdown besitzt sichtbare Auswahlliste");
    fakeComboSel[2]=4;UpdateAutofocusInputState();total++;pass+=check(fakeComboSel[2]==4,"Frontend: Messpunkte-Auswahl bleibt nach Validierung erhalten");
    total++;pass+=check(TabIndexFromId(ID_TAB_LIVE)==0&&TabIndexFromId(ID_TAB_AUTO)==1&&TabIndexFromId(ID_TAB_BAHT)==2&&TabIndexFromId(ID_TAB_LOG)==3&&TabIndexFromId(ID_TAB_AUTOMATION)==4&&TabIndexFromId(ID_TAB_CONTINUOUS)==5&&TabIndexFromId(ID_TAB_ANALYSIS)==6&&TabIndexFromId(ID_TAB_TESTS)==7&&TabIndexFromId(ID_TAB_FIELD)==-1,"Frontend: sichtbare Reiter ohne doppeltes Bildfeld korrekt gemappt");
    hCamBackend=FH(8);hFocBackend=FH(9);hCamRefresh=FH(10);hCamDevice=FH(11);hCamSelect=FH(12);g_cameraBackendSelection=2;g_focuserBackendSelection=1;ApplyBackendSelectors();total++;pass+=check(fakeComboSel[8]==2&&fakeComboSel[9]==1,"Frontend: Backend-Auswahl wird beim ersten lokalen Commit sichtbar gehalten");
    g_cameraBackendSelection=1;ApplyBackendSelectors();total++;pass+=check(fakeComboSel[8]==1&&fakeEnabled[10]&&fakeEnabled[11],"Frontend: UVC-Auswahl aktiviert Gerätesuche ohne zweiten Auswahlvorgang");
    total++;pass+=check(LooksLikeAscomProgId(L"ASCOM.Celestron.Focuser")&&LooksLikeAscomProgId(L"ASCOM.Simulator.Camera"),"3.9.0 frontend: gültige ASCOM-ProgIDs werden erkannt");
    total++;pass+=check(!LooksLikeAscomProgId(L"Synthetische Kamera")&&!LooksLikeAscomProgId(L"ToupTek Camera")&&!LooksLikeAscomProgId(L""),"3.9.0 frontend: Geräteanzeigenamen gelten nicht als ASCOM-Auswahl");
    total++;pass+=check(!LooksLikeAscomProgId(L"ASCOM/Bad.Camera")&&!LooksLikeAscomProgId(L"ASCOM.Bad Camera"),"3.9.0 frontend: unsichere ASCOM-Auswahlwerte werden verworfen");
    wchar_t chooserOut[64];
    const wchar_t validChooserId[]=L"ASCOM.Celestron.Focuser";
    total++;pass+=check(CopyValidatedAscomProgId(validChooserId,lstrlenW(validChooserId),chooserOut,64)&&LooksLikeAscomProgId(chooserOut),"3.9.0 frontend: vollständige Chooser-ProgID wird unverändert übernommen");
    const wchar_t embeddedNul[]={L'A',L'S',L'C',L'O',L'M',L'.',L'X',0,L'Y'};
    total++;pass+=check(!CopyValidatedAscomProgId(embeddedNul,9,chooserOut,64)&&chooserOut[0]==0,"3.9.0 frontend: eingebettetes NUL mit Folgedaten wird verworfen");
    const wchar_t controlId[]={L'A',L'S',L'C',L'O',L'M',L'.',L'X',L'\n',L'Y'};
    total++;pass+=check(!CopyValidatedAscomProgId(controlId,9,chooserOut,64),"3.9.0 frontend: Steuerzeichen im Chooser-Ergebnis werden verworfen");
    total++;pass+=check(!CopyValidatedAscomProgId(validChooserId,lstrlenW(validChooserId),chooserOut,8),"3.9.0 frontend: zu kleine Zielpuffer führen nicht zu Kürzung");
    total++;pass+=check(ClassifyFocuserSetupExitCode(0)==0&&ClassifyFocuserSetupExitCode(10)==1&&ClassifyFocuserSetupExitCode(6)==2&&ClassifyFocuserSetupExitCode(0xffffffffUL)==2,"3.9.0 frontend: Setup-Exitcodes werden als Erfolg, Abbruch oder Fehler klassifiziert");
    // 3.9.0 chooser integration: opening a modal helper freezes all backend-changing controls.
    hCamConnect=FH(13);hFocConnect=FH(14);hFocSelect=FH(15);hFocSetup=FH(16);fakeComboSel[8]=3;fakeComboSel[9]=1;
    SetAscomChooserButtons(TRUE);
    BOOL chooserControlsLocked=!fakeEnabled[8]&&!fakeEnabled[9]&&!fakeEnabled[12]&&!fakeEnabled[13]&&!fakeEnabled[14]&&!fakeEnabled[15]&&!fakeEnabled[16];
    SetAscomChooserButtons(FALSE);
    BOOL chooserControlsRestored=fakeEnabled[8]&&fakeEnabled[9]&&fakeEnabled[13]&&fakeEnabled[14]&&fakeEnabled[12]&&fakeEnabled[15];
    total++;pass+=check(chooserControlsLocked&&chooserControlsRestored,"3.9.0 integration: chooser locks and restores all backend-changing controls");
    fakeComboSel[8]=3;fakeComboSel[9]=1;
    BOOL validChooserState=AscomChooserBackendStillValid(TRUE,3)&&AscomChooserBackendStillValid(FALSE,1);
    fakeComboSel[8]=2;BOOL changedCameraRejected=!AscomChooserBackendStillValid(TRUE,3);fakeComboSel[9]=0;BOOL changedFocuserRejected=!AscomChooserBackendStillValid(FALSE,1);
    total++;pass+=check(validChooserState&&changedCameraRejected&&changedFocuserRejected,"3.9.0 integration: chooser result is discarded after a backend change");

    ResetTrendHistory();memset(&g_state,0,sizeof(g_state));g_state.live=TRUE;g_state.frameReady=TRUE;g_state.usedStars=12;g_state.fwhm=4.50;g_state.hfr=2.05;g_state.frameSequence=1;fakeTick=1000;BOOL trendFirst=UpdateTrendHistory(0);total++;pass+=check(trendFirst&&g_trendCount==1&&g_trend[0].frameSequence==1,"Frontend: Live-Trend übernimmt genau ein gültiges neues Frame");
    g_state.fwhm=9.9;fakeTick=1100;BOOL trendDuplicate=UpdateTrendHistory(0);total++;pass+=check(!trendDuplicate&&g_trendCount==1&&g_trend[0].fwhm<4.51,"Frontend: Statuspoll desselben Frames dupliziert Trendpunkt nicht");
    g_state.frameSequence=2;g_state.usedStars=0;fakeTick=2000;BOOL trendInvalid=UpdateTrendHistory(0);total++;pass+=check(!trendInvalid&&g_trendCount==1,"Frontend: ungültige Messung ohne geeignete Sterne wird verworfen");
    AppState beforeAf=g_state;beforeAf.autofocus=TRUE;g_state.autofocus=FALSE;g_state.afFinalValid=TRUE;g_state.live=TRUE;g_state.frameReady=TRUE;g_state.usedStars=15;g_state.fwhm=4.10;g_state.hfr=1.90;g_state.frameSequence=3;fakeTick=3000;BOOL trendAf=UpdateTrendHistory(&beforeAf);total++;pass+=check(trendAf&&g_trendCount==2&&g_trend[1].autofocusMarker,"Frontend: erfolgreicher Autofokus markiert den nächsten gültigen Trendpunkt");
    for(int seq=4;seq<=70;seq++){g_state.frameSequence=seq;g_state.usedStars=20;g_state.fwhm=4.0+(double)(seq%5)*0.05;g_state.hfr=1.8;fakeTick=(ULONGLONG)seq*1000ULL;UpdateTrendHistory(0);}total++;pass+=check(g_trendCount==TREND_CAPACITY&&g_trend[g_trendCount-1].frameSequence==70,"Frontend: Live-Trend ist auf 60 Messungen begrenzt");
    g_state.autoRefocusReferenceReady=TRUE;g_state.autoRefocusReferenceFwhm=4.0;g_state.autoRefocusFwhmEnabled=TRUE;g_state.refocusFwhmPercent=30.0;double trMin=0,trMax=0;TrendRange(&trMin,&trMax);total++;pass+=check(trMin<4.0&&trMax>5.19,"Frontend: Trendskalierung berücksichtigt Referenz und Refokusgrenze");
    RECT trendRect={100,100,700,400};g_liveTrendPlot=trendRect;g_activeTab=0;UpdateTrendHoverFromMouse(700,200);total++;pass+=check(g_trendHoverIndex==g_trendCount-1,"Frontend: Trend-Hover findet den zeitlich letzten Messpunkt");
    hStatus=FH(13);g_uvcProcess=(HANDLE)777;g_engineOnline=FALSE;fakeProcessSignaled=TRUE;int closesBefore=fakeCloseCount;PollUvcProcess();
    total++;pass+=check(g_uvcProcess==0&&fakeCloseCount==closesBefore+1&&fakeText[13][0]!=0,"3.9.0 frontend: beendeter UVC-Prozess trennt Status sauber");
    fakeProcessSignaled=FALSE;
    hProfile=FH(14);hManualStep=FH(15);hRefocusMin=FH(16);hRefocusTemp=FH(17);hRefocusFwhm=FH(18);hRefocusBadFrames=FH(19);hRefocusMinStars=FH(20);hRefocusStability=FH(21);hRefocusCooldown=FH(22);hRefocusCaptures=FH(23);hFilterName=FH(24);hSafeMin=FH(25);hSafeMax=FH(26);hSimProfile=FH(27);hSimBacklash=FH(28);hTempComp=FH(29);hAutoStartPos=FH(30);hEvtMeridian=FH(31);hEvtReconnect=FH(32);hEvtFilter=FH(33);hLoadProfile=FH(34);hDeleteProfile=FH(35);hSaveProfile=FH(36);hImportProfile=FH(37);hExportProfile=FH(38);
    g_uiInitialized=TRUE;AppState oldProfileState;memset(&oldProfileState,0,sizeof(oldProfileState));oldProfileState.profileRevision=4;memset(&g_state,0,sizeof(g_state));g_state.profileRevision=5;lstrcpyW(g_state.profile,L"Profil B");lstrcpyW(g_state.exposure,L"1600.00");lstrcpyW(g_state.gain,L"321");lstrcpyW(g_state.manualStep,L"222");lstrcpyW(g_state.afPointsText,L"11");lstrcpyW(g_state.afStepText,L"175");lstrcpyW(g_state.afSamplesText,L"4");lstrcpyW(g_state.backlashText,L"410");lstrcpyW(g_state.refocusMinText,L"45.00");lstrcpyW(g_state.refocusTempText,L"1.25");g_state.refocusFwhmPercent=28.0;g_state.refocusBadFrames=4;g_state.refocusMinStars=7;g_state.refocusStability=0.35;g_state.refocusCooldown=12.0;g_state.refocusEveryCaptures=30;lstrcpyW(g_state.currentFilter,L"OIII");g_state.safeMin=120;g_state.safeMax=190000;g_state.simProfileMode=4;g_state.simBacklashSteps=680;UpdateUiFromState(&oldProfileState);
    total++;pass+=check(fakeText[0][0]==L'1'&&fakeText[1][0]==L'3'&&fakeText[15][0]==L'2'&&fakeText[14][0]==L'P'&&fakeText[28][0]==L'6',"3.9.0 frontend: profile revision synchronizes loaded settings into existing controls");
    SetWindowTextW(hGain,L"999");AppState sameRevision=g_state;UpdateUiFromState(&sameRevision);total++;pass+=check(fakeText[1][0]==L'9',"3.9.0 frontend: ordinary polling preserves unsaved control edits without a new profile revision");
    SetWindowTextW(hBacklash,L"250");AppState beforeBacklashCalibration=g_state;beforeBacklashCalibration.backlashCalibrationEstimated=-1;lstrcpyW(beforeBacklashCalibration.backlashText,L"250");g_state.backlashCalibrationEstimated=420;lstrcpyW(g_state.backlashText,L"420");lstrcpyW(g_state.backlashCalibrationResult,L"Backlash kalibriert: 420 Schritte");UpdateUiFromState(&beforeBacklashCalibration);
    total++;pass+=check(WEqual(fakeText[5],L"420")&&fakeText[1][0]==L'9',"3.9.0 frontend: kalibrierter Backlash wird gezielt übernommen, andere ungespeicherte Eingaben bleiben erhalten");
    lstrcpyW(g_state.focusNeedReason,L"FWHM seit Referenz +2,0 %; 1 von 5 Messungen schlechter. Fokuswerte liegen innerhalb der Referenz- und Stabilitätsgrenzen.");
    int narrowLampH=MeasureFocusLampHeight(250,260),wideLampH=MeasureFocusLampHeight(310,260);
    total++;pass+=check(narrowLampH>148&&narrowLampH<=260&&wideLampH>=148&&wideLampH<=narrowLampH,"3.9.0 frontend: lange Automatikbegründung vergrößert Karte ohne Clipping");
    memset(&g_state,0,sizeof(g_state));g_state.focuserMoving=TRUE;
    total++;pass+=check(FocuserOperationBusy(),"3.9.0 frontend: laufende Motorbewegung sperrt Setup und Backendwechsel");
    g_state.focuserMoving=FALSE;g_state.stepAssistantActive=TRUE;
    total++;pass+=check(FocuserOperationBusy(),"3.9.0 frontend: Schritt-Assistent sperrt Treiberkalibrierung");
    g_state.stepAssistantActive=FALSE;g_state.backlashCalibrationActive=TRUE;
    total++;pass+=check(FocuserOperationBusy(),"3.9.0 frontend: Backlash-Kalibrierung sperrt Treiberkalibrierung");
    ParseStatus("{\"version\":\"3.9.0\",\"focuserSetupActive\":true}");
    total++;pass+=check(g_state.focuserSetupActive&&FocuserOperationBusy(),"3.9.0 revision: engine setup reservation is parsed and locks the UI");
    g_state.focuserSetupActive=FALSE;g_focuserSetupEngineLock=TRUE;
    total++;pass+=check(FocuserOperationBusy(),"3.9.0 revision: local setup launch window remains locked before next poll");g_focuserSetupEngineLock=FALSE;
    printf("SUMMARY %d/%d\n",pass,total);return pass==total?0:1;
}
