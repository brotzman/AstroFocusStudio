#define ASTROFOCUS_NATIVE_TEST 1
#define WinMainCRTStartup Backend_WinMainCRTStartup
#include "../backend/backend.cpp"

extern "C" {
int printf(const char*,...);
char* strstr(const char*,const char*);
int vswprintf(wchar_t*, unsigned long, const wchar_t*, __builtin_va_list);
LPWSTR WINAPI lstrcpyW(LPWSTR d,LPCWSTR s){LPWSTR r=d;while((*d++=*s++)){}return r;}
LPWSTR WINAPI lstrcatW(LPWSTR d,LPCWSTR s){LPWSTR r=d;while(*d)d++;while((*d++=*s++)){}return r;}
int WINAPI lstrlenW(LPCWSTR s){int n=0;while(s&&s[n])n++;return n;}
int WINAPI wsprintfW(LPWSTR d,LPCWSTR f,...){__builtin_va_list ap;__builtin_va_start(ap,f);int n=vswprintf(d,1024,f,ap);__builtin_va_end(ap);return n;}
HANDLE WINAPI GetProcessHeap(void){ return (HANDLE)1; }
LPVOID WINAPI HeapAlloc(HANDLE,DWORD,SIZE_T n){ return __builtin_malloc(n); }
BOOL WINAPI HeapFree(HANDLE,DWORD,LPVOID p){ __builtin_free(p); return TRUE; }
}

struct FakeCtl { wchar_t text[1024]; int check; };
static FakeCtl controls[64];
static HWND H(int i){return (HWND)(ULONG_PTR)(i+1);} 
static int HI(HWND h){return (int)((ULONG_PTR)h)-1;}
static unsigned long long fakeNow=100000;
static bool fakeThreadFinished=false;
static bool fakeCreateFileFail=false,fakeWriteFail=false,fakePartialWrite=false;
struct FakeFileEntry { wchar_t path[760]; unsigned char data[262145]; DWORD size; bool used; };
struct FakeFileHandle { int file; DWORD pos; bool used; };
struct FakeIniEntry { wchar_t path[760],section[96],key[96],value[1024]; bool used; };
static FakeFileEntry fakeFiles[64];static FakeFileHandle fakeHandles[32];static FakeIniEntry fakeIni[256];
static bool FakeWEq(LPCWSTR a,LPCWSTR b){int i=0;if(!a||!b)return a==b;while(a[i]&&b[i]&&a[i]==b[i])i++;return a[i]==b[i];}
static void FakeWCopy(LPWSTR d,int cap,LPCWSTR s){int i=0;if(!d||cap<=0)return;while(s&&s[i]&&i<cap-1){d[i]=s[i];i++;}d[i]=0;}
static int FakeFindFile(LPCWSTR path){for(int i=0;i<64;i++)if(fakeFiles[i].used&&FakeWEq(fakeFiles[i].path,path))return i;return -1;}
extern "C" DWORD WINAPI GetFileAttributesW(LPCWSTR path){return FakeFindFile(path)>=0?FILE_ATTRIBUTE_NORMAL:0xffffffffUL;}
static int FakeFindFileSuffix(LPCWSTR suffix){if(!suffix)return -1;int sn=0;while(suffix[sn])sn++;for(int i=0;i<64;i++)if(fakeFiles[i].used){int pn=0;while(fakeFiles[i].path[pn])pn++;if(pn>=sn){int j=0;while(j<sn&&fakeFiles[i].path[pn-sn+j]==suffix[j])j++;if(j==sn)return i;}}return -1;}
static bool FakeFileContainsBytes(int file,const char* needle){
    if(file<0||file>=64||!fakeFiles[file].used||!needle)return false;
    int nn=0;while(needle[nn])nn++;if(nn==0)return true;
    for(DWORD i=0;i+(DWORD)nn<=fakeFiles[file].size;i++){int j=0;while(j<nn&&fakeFiles[file].data[i+j]==(unsigned char)needle[j])j++;if(j==nn)return true;}
    return false;
}
static int FakeCsvFirstPointColumns(int file){
    const char* header="Index;Position;HFR_Metrik;HFR_Sigma;FWHM_Metrik;FWHM_Sigma;Verwendete_Sterne;Aufnahmen;Standardresiduum;Ausreisser\r\n";
    if(file<0||file>=64||!fakeFiles[file].used)return 0;int hn=0;while(header[hn])hn++;DWORD start=0;bool found=false;
    for(DWORD i=0;i+(DWORD)hn<=fakeFiles[file].size;i++){int j=0;while(j<hn&&fakeFiles[file].data[i+j]==(unsigned char)header[j])j++;if(j==hn){start=i+(DWORD)hn;found=true;break;}}
    if(!found||start>=fakeFiles[file].size)return 0;int semis=0;for(DWORD i=start;i<fakeFiles[file].size&&fakeFiles[file].data[i]!='\r'&&fakeFiles[file].data[i]!='\n';i++)if(fakeFiles[file].data[i]==';')semis++;return semis+1;
}
static int FakeAllocFile(LPCWSTR path){int i=FakeFindFile(path);if(i>=0)return i;for(i=0;i<64;i++)if(!fakeFiles[i].used){fakeFiles[i].used=true;fakeFiles[i].size=0;FakeWCopy(fakeFiles[i].path,760,path);return i;}return -1;}
static HANDLE FakeAllocHandle(int file,DWORD pos){for(int i=0;i<32;i++)if(!fakeHandles[i].used){fakeHandles[i].used=true;fakeHandles[i].file=file;fakeHandles[i].pos=pos;return (HANDLE)(ULONG_PTR)(0x10000+i);}return INVALID_HANDLE_VALUE;}
static FakeFileHandle* FakeHandleOf(HANDLE h){ULONG_PTR v=(ULONG_PTR)h;if(v<0x10000||v>=0x10020)return 0;int i=(int)(v-0x10000);return fakeHandles[i].used?&fakeHandles[i]:0;}
static int FakeFindIni(LPCWSTR path,LPCWSTR section,LPCWSTR key){for(int i=0;i<256;i++)if(fakeIni[i].used&&FakeWEq(fakeIni[i].path,path)&&FakeWEq(fakeIni[i].section,section)&&FakeWEq(fakeIni[i].key,key))return i;return -1;}
static void ResetFakeProfileStorage(){for(int i=0;i<64;i++)fakeFiles[i].used=false;for(int i=0;i<32;i++)fakeHandles[i].used=false;for(int i=0;i<256;i++)fakeIni[i].used=false;}
static const char* fakeNetRequest=0;static int fakeNetRequestPos=0;static char fakeNetResponse[1048576];static int fakeNetResponseSize=0;static bool fakeNetAccepted=false;
static SOCKET WINAPI FakeAccept(SOCKET,SOCKADDR*,int*){if(fakeNetAccepted||!fakeNetRequest)return INVALID_SOCKET_VALUE;fakeNetAccepted=true;return (SOCKET)77;}
static int WINAPI FakeRecvNet(SOCKET,char* out,int cap,int){if(!fakeNetRequest)return 0;int len=ALen(fakeNetRequest),left=len-fakeNetRequestPos;if(left<=0)return 0;int n=left>17?17:left;if(n>cap)n=cap;for(int i=0;i<n;i++)out[i]=fakeNetRequest[fakeNetRequestPos+i];fakeNetRequestPos+=n;return n;}
static int WINAPI FakeSendNet(SOCKET,const char* in,int n,int){int room=(int)sizeof(fakeNetResponse)-1-fakeNetResponseSize;if(n>room)n=room;if(n<=0)return -1;for(int i=0;i<n;i++)fakeNetResponse[fakeNetResponseSize+i]=in[i];fakeNetResponseSize+=n;fakeNetResponse[fakeNetResponseSize]=0;return n;}
static int WINAPI FakeCloseNet(SOCKET){return 0;}
static int WINAPI FakeSetSockOptNet(SOCKET,int,int,const char*,int){return 0;}
static int WINAPI FakeIoctlNet(SOCKET,long,unsigned long*){return 0;}
static void RunFakeHttp(const char* request){fakeNetRequest=request;fakeNetRequestPos=0;fakeNetResponseSize=0;fakeNetResponse[0]=0;fakeNetAccepted=false;g_httpEnabled=TRUE;g_httpListen=(SOCKET)1;p_accept=FakeAccept;p_recv=FakeRecvNet;p_send=FakeSendNet;p_closesocket=FakeCloseNet;p_setsockopt=FakeSetSockOptNet;p_ioctlsocket=FakeIoctlNet;PollHttpServer();}

extern "C" {
BOOL WINAPI SetWindowTextW(HWND h,LPCWSTR s){int i=HI(h);if(i>=0&&i<64){int n=0;while(s&&s[n]&&n<1023){controls[i].text[n]=s[n];n++;}controls[i].text[n]=0;}return TRUE;}
int WINAPI GetWindowTextW(HWND h,LPWSTR out,int cap){int i=HI(h),n=0;if(cap<=0)return 0;if(i>=0&&i<64){while(controls[i].text[n]&&n<cap-1){out[n]=controls[i].text[n];n++;}}out[n]=0;return n;}
LRESULT WINAPI SendMessageW(HWND h,UINT msg,WPARAM w,LPARAM l){int i=HI(h);if(i<0||i>=64)return 0;if(msg==BM_GETCHECK)return controls[i].check?BST_CHECKED:0;if(msg==BM_SETCHECK){controls[i].check=(w==BST_CHECKED);return 0;}return 0;}
BOOL WINAPI InvalidateRect(HWND,const RECT*,BOOL){return TRUE;}
int WINAPI FillRect(HDC,const RECT*,HBRUSH){return 1;}
HGDIOBJ WINAPI GetStockObject(int i){return (HGDIOBJ)(ULONG_PTR)(0x1000+i);}
HGDIOBJ WINAPI SelectObject(HDC,HGDIOBJ o){return o?(HGDIOBJ)0x2222:(HGDIOBJ)0x3333;}
BOOL WINAPI Rectangle(HDC,int,int,int,int){return TRUE;}
int WINAPI SetBkMode(HDC,int){return 1;}
DWORD WINAPI SetTextColor(HDC,DWORD c){return c;}
BOOL WINAPI TextOutW(HDC,int,int,LPCWSTR,int){return TRUE;}
int WINAPI StretchDIBits(HDC,int,int,int,int,int,int,int,int,const void*,const BITMAPINFO*,UINT,DWORD){return 1;}
BOOL WINAPI MoveToEx(HDC,int,int,POINT*){return TRUE;}
BOOL WINAPI LineTo(HDC,int,int){return TRUE;}
ULONGLONG WINAPI GetTickCount64(void){return fakeNow+=100;}
BOOL WINAPI WritePrivateProfileStringW(LPCWSTR section,LPCWSTR key,LPCWSTR value,LPCWSTR path){if(!section||!key||!path)return FALSE;int i=FakeFindIni(path,section,key);if(!value){if(i>=0)fakeIni[i].used=false;return TRUE;}if(i<0){for(i=0;i<256&&fakeIni[i].used;i++){}if(i>=256)return FALSE;fakeIni[i].used=true;FakeWCopy(fakeIni[i].path,760,path);FakeWCopy(fakeIni[i].section,96,section);FakeWCopy(fakeIni[i].key,96,key);}FakeWCopy(fakeIni[i].value,1024,value);return TRUE;}
DWORD WINAPI GetPrivateProfileStringW(LPCWSTR section,LPCWSTR key,LPCWSTR def,LPWSTR out,DWORD cap,LPCWSTR path){if(!out||cap==0)return 0;int i=FakeFindIni(path,section,key);LPCWSTR src=i>=0?fakeIni[i].value:def;DWORD n=0;while(src&&src[n]&&n+1<cap){out[n]=src[n];n++;}out[n]=0;return n;}
BOOL WINAPI CreateDirectoryW(LPCWSTR,const SECURITY_ATTRIBUTES*){return TRUE;}
HANDLE WINAPI CreateFileW(LPCWSTR path,DWORD,DWORD,SECURITY_ATTRIBUTES*,DWORD creation,DWORD,HANDLE){if(fakeCreateFileFail||!path)return INVALID_HANDLE_VALUE;int f=FakeFindFile(path);if(creation==CREATE_ALWAYS){f=FakeAllocFile(path);if(f<0)return INVALID_HANDLE_VALUE;fakeFiles[f].size=0;}else if(creation==OPEN_EXISTING){if(f<0)return INVALID_HANDLE_VALUE;}else if(creation==OPEN_ALWAYS){if(f<0)f=FakeAllocFile(path);if(f<0)return INVALID_HANDLE_VALUE;}else{if(f<0)f=FakeAllocFile(path);if(f<0)return INVALID_HANDLE_VALUE;}return FakeAllocHandle(f,0);}
BOOL WINAPI WriteFile(HANDLE h,LPCVOID in,DWORD n,DWORD* out,void*){if(out)*out=0;if(fakeWriteFail)return FALSE;FakeFileHandle* fh=FakeHandleOf(h);if(!fh)return FALSE;DWORD writeN=fakePartialWrite&&n?n-1:n;if(fh->pos>262144U||writeN>262144U-fh->pos)return FALSE;const unsigned char* p=(const unsigned char*)in;for(DWORD i=0;i<writeN;i++)fakeFiles[fh->file].data[fh->pos+i]=p[i];fh->pos+=writeN;if(fh->pos>fakeFiles[fh->file].size)fakeFiles[fh->file].size=fh->pos;if(out)*out=writeN;return TRUE;}
BOOL WINAPI ReadFile(HANDLE h,LPVOID out,DWORD n,DWORD* got,void*){if(got)*got=0;FakeFileHandle* fh=FakeHandleOf(h);if(!fh)return FALSE;DWORD left=fakeFiles[fh->file].size-fh->pos;if(n>left)n=left;unsigned char* p=(unsigned char*)out;for(DWORD i=0;i<n;i++)p[i]=fakeFiles[fh->file].data[fh->pos+i];fh->pos+=n;if(got)*got=n;return TRUE;}
DWORD WINAPI GetFileSize(HANDLE h,DWORD*){FakeFileHandle* fh=FakeHandleOf(h);return fh?fakeFiles[fh->file].size:0xffffffffU;}
DWORD WINAPI SetFilePointer(HANDLE h,LONG distance,LONG*,DWORD origin){FakeFileHandle* fh=FakeHandleOf(h);if(!fh)return 0xffffffffU;long long base=origin==FILE_END?fakeFiles[fh->file].size:(origin==1?fh->pos:0);long long pos=base+distance;if(pos<0||pos>262144)return 0xffffffffU;fh->pos=(DWORD)pos;return fh->pos;}
BOOL WINAPI CloseHandle(HANDLE h){FakeFileHandle* fh=FakeHandleOf(h);if(fh)fh->used=false;return TRUE;}
void WINAPI GetLocalTime(SYSTEMTIME* s){s->wYear=2026;s->wMonth=7;s->wDay=30;s->wHour=12;s->wMinute=0;s->wSecond=0;s->wMilliseconds=0;}
BOOL WINAPI DeleteFileW(LPCWSTR path){int f=FakeFindFile(path);if(f<0)return FALSE;fakeFiles[f].used=false;return TRUE;}
BOOL WINAPI MoveFileExW(LPCWSTR from,LPCWSTR to,DWORD){int f=FakeFindFile(from);if(f<0)return FALSE;int dest=FakeFindFile(to);if(dest>=0)fakeFiles[dest].used=false;FakeWCopy(fakeFiles[f].path,760,to);return TRUE;}
HMODULE WINAPI GetModuleHandleW(LPCWSTR){return (HMODULE)1;}
HMODULE WINAPI LoadLibraryW(LPCWSTR){return 0;}
FARPROC WINAPI GetProcAddress(HMODULE,const char* name){if(!name)return 0;const char* a="DeleteFileW";int i=0;while(name[i]&&a[i]&&name[i]==a[i])i++;if(!name[i]&&!a[i])return (FARPROC)(ULONG_PTR)&DeleteFileW;const char* m="MoveFileExW";i=0;while(name[i]&&m[i]&&name[i]==m[i])i++;if(!name[i]&&!m[i])return (FARPROC)(ULONG_PTR)&MoveFileExW;return 0;}
BOOL WINAPI FreeLibrary(HMODULE){return TRUE;}
HRESULT WINAPI CLSIDFromProgID(LPCWSTR,CLSID*){return (HRESULT)0x80004005L;}
HRESULT WINAPI CoCreateInstance(REFIID,void*,DWORD,REFIID,void** out){if(out)*out=0;return (HRESULT)0x80004005L;}
BSTR WINAPI SysAllocString(LPCWSTR){return 0;}
void WINAPI VariantInit(VARIANT* v){ if(v) memset(v,0,sizeof(*v)); }
HRESULT WINAPI VariantClear(VARIANT* v){ if(v) memset(v,0,sizeof(*v)); return 0; }
void WINAPI SysFreeString(BSTR){}
UINT WINAPI SafeArrayGetDim(SAFEARRAY*){return 0;}
HRESULT WINAPI SafeArrayGetLBound(SAFEARRAY*,UINT,LONG*){return (HRESULT)0x80004005L;}
HRESULT WINAPI SafeArrayGetUBound(SAFEARRAY*,UINT,LONG*){return (HRESULT)0x80004005L;}
HRESULT WINAPI SafeArrayAccessData(SAFEARRAY*,void**){return (HRESULT)0x80004005L;}
HRESULT WINAPI SafeArrayUnaccessData(SAFEARRAY*){return 0;}
DWORD WINAPI FormatMessageW(DWORD,LPCVOID,DWORD,DWORD,LPWSTR out,DWORD cap,void*){if(cap){out[0]=0;}return 0;}
void WINAPI SysFreeString(BSTR);
HRESULT WINAPI CoInitializeEx(LPVOID,DWORD){return S_OK;}
void WINAPI CoUninitialize(void){}
HANDLE WINAPI CreateEventW(SECURITY_ATTRIBUTES*,BOOL,BOOL,LPCWSTR){return (HANDLE)456;}
BOOL WINAPI SetEvent(HANDLE){return TRUE;}
BOOL WINAPI ResetEvent(HANDLE){return TRUE;}
HANDLE WINAPI CreateThread(SECURITY_ATTRIBUTES*,SIZE_T,DWORD (WINAPI*)(LPVOID),LPVOID,DWORD,DWORD*){return (HANDLE)789;}
DWORD WINAPI WaitForSingleObject(HANDLE,DWORD timeout){return timeout==0?(fakeThreadFinished?WAIT_OBJECT_0:WAIT_TIMEOUT):WAIT_OBJECT_0;}
BOOL WINAPI PeekMessageW(MSG*,HWND,UINT,UINT,UINT){return FALSE;}
BOOL WINAPI TranslateMessage(const MSG*){return TRUE;}
LRESULT WINAPI DispatchMessageW(const MSG*){return 0;}

}

static void init_controls(){
    g_exposureEdit=H(0);g_afPointsEdit=H(1);g_afStepEdit=H(2);g_afSamplesEdit=H(3);g_afBacklashEdit=H(4);g_preferredDirCheck=H(5);
    g_autoStretch=H(6);g_overlayStars=H(7);g_overlayLabels=H(8);g_overlaySat=H(9);g_zoneCheck=H(10);g_bahtinovCheck=H(11);
    g_demoCheck=H(12);g_liveButton=H(13);g_afButton=H(14);g_positionText=H(15);g_status=H(16);g_profileEdit=H(17);g_gainEdit=H(18);g_manualStepEdit=H(19);g_stepAssistButton=H(20);
    g_refocusMinutesEdit=H(21);g_refocusTempEdit=H(22);g_autoRefocusCheck=H(23);g_reconnectCheck=H(24);g_nativeCheck=H(25);g_cameraConnect=H(26);g_focuserConnect=H(27);g_cameraEdit=H(28);g_focuserEdit=H(29);
    SetWindowTextW(g_exposureEdit,L"1");SetWindowTextW(g_afPointsEdit,L"9");SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afSamplesEdit,L"2");SetWindowTextW(g_afBacklashEdit,L"250");
    SetWindowTextW(g_profileEdit,L"Test");SetWindowTextW(g_gainEdit,L"180");SetWindowTextW(g_manualStepEdit,L"100");SetWindowTextW(g_refocusMinutesEdit,L"60");SetWindowTextW(g_refocusTempEdit,L"1,5");
    SetChecked(g_preferredDirCheck,TRUE);SetChecked(g_autoStretch,TRUE);SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,TRUE);SetChecked(g_overlaySat,TRUE);SetChecked(g_zoneCheck,TRUE);
    g_appDir[0]=0;
}

static int test(bool ok,const char* name){printf("%-42s %s\n",name,ok?"PASS":"FAIL");return ok?1:0;}
static bool RunBacklashCalibrationCase(int configuredBacklash,int* estimated,int* increment,int* limit,int* guardOut){
    g_refocusOnFilter=FALSE;g_live=FALSE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_backlashCalActive=FALSE;g_exposing=FALSE;g_capturePurpose=0;
    g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_simulatorMode=TRUE;g_simDeterministicTest=TRUE;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;
    SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afBacklashEdit,L"250");SetChecked(g_preferredDirCheck,TRUE);
    g_simBacklashSteps=configuredBacklash;g_simPosition=g_simBestFocus-700;g_simOpticalPosition=g_simPosition;g_simLastDirection=0;g_simBacklashRemaining=0;
    GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);StartBacklashCalibration();
    int guard=0;while(g_backlashCalActive&&guard++<6000)TimerTick();
    if(estimated)*estimated=g_backlashCalEstimated;if(increment)*increment=g_backlashCalIncrement;if(limit)*limit=g_backlashCalMaxReverse;if(guardOut)*guardOut=guard;
    return !g_backlashCalActive&&guard<6000&&g_backlashCalEstimated>=0;
}
int main(){
    init_controls(); int passed=0,total=0;
    g_simulatorMode=TRUE;g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_simPosition=g_simBestFocus+360;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simDeterministicTest=TRUE;
    unsigned seq0=g_frameSequence;total++;passed+=test(GenerateSyntheticFrame(g_simBestFocus,1,0,0,48,TRUE,FALSE,FALSE)&&g_usedCount>=20,"Actual core: star analysis");
    UINT minPix=255,maxPix=0;unsigned long long bright=0;for(SIZE_T i=0;i<(SIZE_T)g_width*g_height;i++){UINT v=g_display[i]&255U;if(v<minPix)minPix=v;if(v>maxPix)maxPix=v;if(v>80)bright++;}
    total++;passed+=test(g_frameSequence==seq0+1&&maxPix>=240&&maxPix>minPix+100&&bright>100,"Actual core: visible simulator image buffer");
    double f0=g_medianFwhm;GenerateSyntheticFrame(g_simBestFocus+480,1,0,0,48,FALSE,FALSE,FALSE);total++;passed+=test(g_medianFwhm>f0*1.45,"Actual core: defocus response");
    g_simDeterministicTest=FALSE;g_simFrameSequence=1;BOOL generatedFirst=GenerateSyntheticFrame(g_simBestFocus,1,0,0,48,TRUE,FALSE,FALSE);double a=g_medianFwhm,s=g_medianSnr;UINT px=(generatedFirst&&g_raw)?g_raw[1000]:0;g_simFrameSequence=2;BOOL generatedSecond=GenerateSyntheticFrame(g_simBestFocus,1,0,0,48,TRUE,FALSE,FALSE);total++;passed+=test(generatedFirst&&generatedSecond&&g_raw&&g_raw[1000]!=px && (g_medianFwhm!=a || g_medianSnr!=s),"Actual core: dynamic simulator frames");
    g_simPosition=24540;SetWindowTextW(g_manualStepEdit,L"100");ManualMove(-1);total++;passed+=test(g_simPosition==24440,"Actual core: manual move in");ManualMove(1);total++;passed+=test(g_simPosition==24540,"Actual core: manual move out");
    g_safeMinPosition=24500;g_safeMaxPosition=24600;ManualMove(-1);total++;passed+=test(g_simPosition==24540,"Actual core: safe lower limit blocks move");
    g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;
    g_simPosition=24540;g_simOpticalPosition=24540;g_simLastDirection=1;g_simBacklashSteps=250;g_simBacklashRemaining=0;BOOL rev=MoveFocuser(24440);total++;passed+=test(rev&&g_simPosition==24440&&g_simOpticalPosition==24540&&g_simBacklashRemaining==150,"Actual core: backlash reversal");BOOL take=MoveFocuser(24000);total++;passed+=test(take&&g_simOpticalPosition==24250&&g_simBacklashRemaining==0,"Actual core: backlash taken up cumulatively");
    g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;g_simLastDirection=0;g_simBacklashSteps=250;char liveDetail[256];BOOL liveFlow=RunSimulatorLiveRegression(liveDetail,256);printf("live detail: %s\n",liveDetail);total++;passed+=test(liveFlow,"Actual core: live state machine");char stepDetail[256];BOOL stepFlow=RunStepAssistantRegression(stepDetail,256);printf("step detail: %s\n",stepDetail);total++;passed+=test(stepFlow,"Actual core: step assistant state machine");
    GenerateSyntheticFrame(g_simBestFocus,1,0,0,48,TRUE,FALSE,FALSE);int zsum=0;bool coords=true;for(int z=0;z<9;z++)zsum+=g_zoneCount[z];for(int i=0;i<g_starCount;i++)if(g_stars[i].x<0||g_stars[i].x>=g_width||g_stars[i].y<0||g_stars[i].y>=g_height)coords=false;total++;passed+=test(coords&&zsum==g_usedCount&&g_starCount>0,"Actual core: overlay metadata");
    char detail[256];BOOL flow=RunSimulatorWorkflowRegression(detail,256);printf("workflow detail: %s\n",detail); printf("afCount=%d idx=%d state=%d fit=%d r2=%.4f best=%d pos=%d status=%ls\n",g_afPointCount,g_afPointIndex,g_afState,g_fitValid,g_fitR2,g_afBestPosition,g_simPosition,controls[HI(g_status)].text); for(int i=0;i<g_afPointCount;i++) printf("  p%d=%d hfr=%.4f fwhm=%.4f used=%d\n",i,g_afPositions[i],g_afMetrics[i],g_afFwhmMetrics[i],g_afUsedMetrics[i]); total++;passed+=test(flow,"Actual core: autofocus state machine");
    int measuredMin=-1;double measuredBest=1e30;for(int i=0;i<g_afPointCount;i++)if(g_afMetrics[i]>0&&g_afMetrics[i]<measuredBest){measuredBest=g_afMetrics[i];measuredMin=i;}total++;passed+=test(measuredMin>=2&&measuredMin<=g_afPointCount-3,"Actual core: autofocus minimum bracketed");
    total++;passed+=test(g_fitValid&&g_fitFwhmValid&&g_fitR2>0.95&&g_fitFwhmR2>0.90,"Actual core: HFR and FWHM fits valid");
    total++;passed+=test(g_afFinalValid&&g_afVerificationCount>=3&&g_afFinalFwhm<g_beforeFwhm&&g_afFinalHfr<g_beforeHfr,"Actual core: final verification improves focus");
    g_afFinalValid=TRUE;SetWindowTextW(g_manualStepEdit,L"10");ManualMove(1);total++;passed+=test(!g_afFinalValid,"Actual core: manual move invalidates AF result");
    RunSyntheticSelfTests();total++;passed+=test(g_selfTestFailed==0&&g_selfTestPassed==g_selfTestTotal&&g_selfTestTotal>=16,"Actual core: integrated synthetic suite");
    printf("integrated suite: %d/%d, %s\n",g_selfTestPassed,g_selfTestTotal,g_selfTestSummary);

    g_focuserConnected=FALSE;total++;passed+=test(!MoveFocuser(g_simBestFocus),"Actual core: disconnected sim focuser blocks move");g_focuserConnected=TRUE;
    g_cameraConnected=FALSE;g_exposing=FALSE;total++;passed+=test(!StartExposure(1)&&!g_exposing,"Actual core: disconnected sim camera blocks exposure");g_cameraConnected=TRUE;
    wchar_t decoded[64];QueryText("GET /api/set?name=profile&value=M%C3%BCnchen%20%C3%84 HTTP/1.1","value=",decoded,64);total++;passed+=test(decoded[0]==L'M'&&decoded[1]==0x00fc&&decoded[8]==0x00c4,"Actual core: UTF-8 query decoding");
    char escaped[128];WToJsonUtf8(L"A\"B\\C ä",escaped,128);total++;passed+=test(strstr(escaped,"A\\\"B\\\\C")!=0&&strstr(escaped,"\xc3\xa4")!=0,"Actual core: JSON UTF-8 escaping");
    int preserveMin=1234,preserveMax=54321;g_safeMinPosition=preserveMin;g_safeMaxPosition=preserveMax;g_afPointCount=3;g_afPositions[0]=1;g_afPositions[1]=2;g_afPositions[2]=3;g_afMetrics[0]=7;g_afMetrics[1]=6;g_afMetrics[2]=7;g_fitFwhmValid=TRUE;g_fitFwhmA=1.25;g_fitFwhmB=-2.5;g_fitFwhmC=4.75;g_fitFwhmR2=0.93;g_fitCenterPosition=12345;g_fitScale=77;g_afFinalValid=TRUE;g_afFinalPosition=24680;g_afFinalHfr=1.23;g_afFinalFwhm=2.34;g_afVerificationCount=4;g_afVerificationTarget=4;g_simPosition=33333;g_simOpticalPosition=33222;g_simLastDirection=-1;g_simBacklashRemaining=123;
    g_tempProfileCount=2;g_tempProfileT[0]=4.5;g_tempProfileT[1]=9.5;g_tempProfileP[0]=20001;g_tempProfileP[1]=20251;g_tempSlope=50.0;g_tempIntercept=19776.0;g_tempFitValid=TRUE;g_sessionBestFwhm=2.22;g_sessionWorstFwhm=4.44;g_sessionStartPosition=23000;g_sessionLastPosition=24000;g_sessionHasTemperature=TRUE;g_sessionStartTemperature=11.0;g_sessionLastTemperature=8.0;g_autoStartPending=TRUE;g_afStartPosition=23999;g_beforeFwhm=4.2;g_beforeHfr=2.1;g_afRetryCount=2;g_resumeLiveAfterAf=FALSE;
    RunSyntheticSelfTests();total++;passed+=test(g_safeMinPosition==preserveMin&&g_safeMaxPosition==preserveMax&&g_afPointCount==3&&g_afPositions[1]==2&&g_afMetrics[1]==6&&g_fitFwhmValid&&g_fitFwhmA==1.25&&g_fitCenterPosition==12345&&g_afFinalValid&&g_afFinalPosition==24680&&g_afVerificationCount==4&&g_tempProfileCount==2&&g_tempProfileT[0]==4.5&&g_tempProfileP[1]==20251&&g_tempSlope==50.0&&g_tempFitValid&&g_sessionBestFwhm==2.22&&g_sessionWorstFwhm==4.44&&g_sessionStartPosition==23000&&g_sessionLastPosition==24000&&g_sessionHasTemperature&&g_autoStartPending&&g_afStartPosition==23999&&g_beforeFwhm==4.2&&g_beforeHfr==2.1&&g_afRetryCount==2&&!g_resumeLiveAfterAf&&g_simPosition==33333&&g_simOpticalPosition==33222&&g_simLastDirection==-1&&g_simBacklashRemaining==123,"Actual core: self-tests preserve user, session and simulator mechanics");g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;
    SetAutoRefocusEnabled(FALSE);g_afActive=FALSE;g_stepAssistActive=FALSE;g_exposing=FALSE;g_lastGoodFwhm=2.0;g_medianFwhm=3.0;g_trendCount=8;g_trendHead=8;for(int i=0;i<8;i++)g_trendFwhm[i]=3.0;total++;passed+=test(!ShouldStartDegradationRefocus(),"Actual core: degradation refocus obeys disabled toggle");
    SetAutoRefocusEnabled(TRUE);g_autoRefocusReferenceReady=TRUE;g_lastGoodFwhm=2.0;g_medianFwhm=3.0;g_refocusBadFrameStreak=g_refocusBadFramesRequired;g_lastAfCompleted=0;g_seeingIndex=80.0;g_transparencyIndex=100.0;g_exposing=TRUE;g_capturePurpose=1;total++;passed+=test(ShouldStartDegradationRefocus(),"Actual core: live exposure does not block degradation trigger");g_exposing=FALSE;g_capturePurpose=0;

    SetAutoRefocusEnabled(FALSE);g_lastAfCompleted=0;SetAutoRefocusEnabled(TRUE);total++;passed+=test(g_autoRefocusEnabled&&IsChecked(g_autoRefocusCheck)&&g_lastAfCompleted>0,"Actual core: auto-refocus enable initializes reference");
    RunFakeHttp("GET /api/toggle?name=autoRefocus&value=0 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");total++;passed+=test(!g_autoRefocusEnabled&&!IsChecked(g_autoRefocusCheck)&&strstr(fakeNetResponse,"\"ok\":true")!=0,"Actual core: API disables auto-refocus authoritatively");
    RunFakeHttp("GET /api/toggle?name=autoRefocus&value=1 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");total++;passed+=test(g_autoRefocusEnabled&&IsChecked(g_autoRefocusCheck)&&strstr(fakeNetResponse,"\"ok\":true")!=0,"Actual core: API enables auto-refocus authoritatively");
    RunFakeHttp("GET /api/status HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");total++;passed+=test(strstr(fakeNetResponse,"\"autoRefocus\":true")!=0,"Actual core: status confirms persistent auto-refocus state");
    g_hasFocuserTemperature=TRUE;g_focuserTemperature=11.5;g_hasLastAfTemperature=FALSE;SetWindowTextW(g_refocusMinutesEdit,L"0");SetWindowTextW(g_refocusTempEdit,L"1,5");g_afActive=FALSE;g_stepAssistActive=FALSE;g_live=FALSE;g_exposing=FALSE;g_lastGoodFwhm=0.0;EnsureAutoRefocusTemperatureReference();total++;passed+=test(g_hasLastAfTemperature&&g_lastAfTemperature==g_focuserTemperature&&!g_afActive,"Actual core: delayed focuser temperature initializes auto-refocus baseline");

    // Timer integration: every configured automatic trigger must actually enter autofocus.
    g_httpEnabled=FALSE;g_simulatorMode=TRUE;g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;g_simLastDirection=0;GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);g_lastCompletedPurpose=1;g_backlashCalActive=FALSE;SetWindowTextW(g_afPointsEdit,L"9");SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afSamplesEdit,L"2");SetWindowTextW(g_afBacklashEdit,L"250");g_autoRefocusRetryAfter=0;g_autoRefocusFailureCount=0;g_autoRefocusPaused=FALSE;g_refocusCooldownMinutes=0.0;g_lastGoodFwhm=0.0;SetWindowTextW(g_refocusMinutesEdit,L"0,001");SetWindowTextW(g_refocusTempEdit,L"0");g_lastAfCompleted=1;g_afActive=FALSE;g_stepAssistActive=FALSE;g_live=FALSE;g_exposing=FALSE;TimerTick();total++;passed+=test(g_afActive&&g_afAutomaticRun,"Actual core: timer interval triggers automatic autofocus");if(g_afActive)StopAutofocus(TRUE,L"Intervalltest beendet");g_autoRefocusRetryAfter=0;
    GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);g_lastCompletedPurpose=1;g_backlashCalActive=FALSE;g_autoRefocusFailureCount=0;g_autoRefocusPaused=FALSE;g_refocusCooldownMinutes=0.0;SetWindowTextW(g_refocusMinutesEdit,L"0");SetWindowTextW(g_refocusTempEdit,L"1,0");g_simTemperature=12.0;g_hasLastAfTemperature=TRUE;g_lastAfTemperature=10.0;g_afActive=FALSE;g_stepAssistActive=FALSE;g_live=FALSE;g_exposing=FALSE;TimerTick();total++;passed+=test(g_afActive&&g_afAutomaticRun,"Actual core: temperature delta triggers automatic autofocus");if(g_afActive)StopAutofocus(TRUE,L"Temperaturtest beendet");g_autoRefocusRetryAfter=0;
    GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);g_lastCompletedPurpose=1;g_backlashCalActive=FALSE;SetWindowTextW(g_refocusMinutesEdit,L"0");SetWindowTextW(g_refocusTempEdit,L"0");g_lastGoodFwhm=2.0;g_medianFwhm=3.0;g_trendCount=8;g_trendHead=8;for(int i=0;i<8;i++)g_trendFwhm[i]=3.0;g_seeingIndex=80.0;g_transparencyIndex=100.0;g_refocusBadFrameStreak=g_refocusBadFramesRequired;g_lastAfCompleted=0;g_afActive=FALSE;g_stepAssistActive=FALSE;g_live=FALSE;g_exposing=FALSE;TimerTick();total++;passed+=test(g_afActive&&g_afAutomaticRun,"Actual core: sustained degradation triggers automatic autofocus");if(g_afActive)StopAutofocus(TRUE,L"Degradationstest beendet");g_autoRefocusRetryAfter=0;g_lastGoodFwhm=0.0;
    SetWindowTextW(g_afPointsEdit,L"9");SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afSamplesEdit,L"2");SetWindowTextW(g_afBacklashEdit,L"250");g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;g_afActive=FALSE;g_stepAssistActive=FALSE;g_autoRefocusRetryAfter=0;g_afUseSelectedStar=FALSE;g_manualStarLocked=FALSE;GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);g_live=TRUE;g_exposing=TRUE;g_capturePurpose=1;BOOL autoFromLive=TriggerAutomaticRefocus(L"Test: Zeitintervall");total++;passed+=test(autoFromLive&&g_afActive&&g_afAutomaticRun&&!g_live&&!g_exposing&&g_resumeLiveAfterAf,"Actual core: automatic refocus starts during live capture");
    StopAutofocus(TRUE,L"Testabbruch");total++;passed+=test(!g_afActive&&g_live&&g_exposing&&!g_resumeLiveAfterAf,"Actual core: live capture resumes after auto-refocus abort");StopLive();g_autoRefocusRetryAfter=0;

    // Complete an automatic run through the productive autofocus state machine, including live resume.
    g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;g_simLastDirection=0;g_afActive=FALSE;g_stepAssistActive=FALSE;g_autoRefocusRetryAfter=0;g_afUseSelectedStar=FALSE;g_manualStarLocked=FALSE;g_simDeterministicTest=TRUE;GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);
    g_live=TRUE;g_exposing=TRUE;g_capturePurpose=1;ULONGLONG autoBaseline=g_lastAfCompleted;BOOL autoCompleteStarted=TriggerAutomaticRefocus(L"Test: vollständiger automatischer Lauf");int autoGuard=0;BOOL autoUnexpected=!autoCompleteStarted;
    while(g_afActive&&autoGuard++<700){if(g_exposing){int purpose=g_capturePurpose;ProcessCompletedFrame(purpose);continue;}if(g_afState==10){if(MoveFocuser(g_moveFinalTarget))g_afState=11;else{autoUnexpected=TRUE;break;}continue;}if(g_afState==11){ContinueAfterMove();continue;}if(g_afState==12){int c=g_moveContinuation;g_afState=0;if(c==1){if(!StartExposure(2)){autoUnexpected=TRUE;break;}}else if(c==2){if(!StartExposure(3)){autoUnexpected=TRUE;break;}}else if(c==3){g_afActive=FALSE;SetWindowTextW(g_afButton,L"Autofokus starten");}else{autoUnexpected=TRUE;break;}continue;}autoUnexpected=TRUE;break;}
    int autoErr=g_simOpticalPosition-g_simBestFocus;if(autoErr<0)autoErr=-autoErr;total++;passed+=test(!autoUnexpected&&!g_afActive&&g_afFinalValid&&autoErr<=120&&g_lastAfCompleted>autoBaseline&&g_live&&g_exposing&&!g_afAutomaticRun,"Actual core: automatic refocus completes and resumes live");StopLive();g_autoRefocusRetryAfter=0;g_simDeterministicTest=TRUE;
    g_afActive=TRUE;g_afAutomaticRun=TRUE;g_resumeLiveAfterAf=TRUE;g_live=FALSE;g_exposing=FALSE;g_cameraConnected=FALSE;StopAutofocus(FALSE,L"Test: Kamera getrennt");total++;passed+=test(!g_live&&!g_exposing&&!g_resumeLiveAfterAf,"Actual core: disconnected camera prevents false live resume");g_cameraConnected=TRUE;g_autoRefocusRetryAfter=0;

    GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);g_afUseSelectedStar=TRUE;g_manualStarLocked=TRUE;g_selectedStar=-1;g_live=FALSE;g_exposing=FALSE;BOOL fallbackStart=TriggerAutomaticRefocus(L"Test: Fokusstern verloren");total++;passed+=test(fallbackStart&&g_afActive&&!g_afRunUsesSelectedStar&&g_afUseSelectedStar,"Actual core: automatic selected-star fallback uses field median");StopAutofocus(TRUE,L"Testabbruch");StopLive();g_autoRefocusRetryAfter=0;g_afUseSelectedStar=FALSE;g_manualStarLocked=FALSE;

    ULONGLONG baseline=424242;g_autoRefocusFailureCount=0;g_autoRefocusPaused=FALSE;g_autoRefocusRetryAfter=0;g_lastAfCompleted=baseline;g_frameReady=FALSE;g_afActive=FALSE;g_stepAssistActive=FALSE;BOOL failedStart=TriggerAutomaticRefocus(L"Test: kein Bild");total++;passed+=test(!failedStart&&!g_afActive&&!g_afAutomaticRun&&g_lastAfCompleted==baseline&&g_autoRefocusRetryAfter>0,"Actual core: failed auto-refocus preserves baseline and schedules retry");
    g_frameReady=TRUE;SetAutoRefocusEnabled(FALSE);

    // Failure-path regression tests: these paths previously left the visible state active or reported false success.
    SetAutoRefocusEnabled(FALSE);SetChecked(g_reconnectCheck,FALSE);g_cameraConnected=FALSE;g_focuserConnected=TRUE;g_live=TRUE;g_exposing=FALSE;g_resumeLiveAfterAf=FALSE;g_resumeLiveAfterStep=FALSE;
    total++;passed+=test(!StartLiveExposureOrStop(L"Testfehler")&&!g_live&&!g_exposing,"Actual core: failed live start clears live state");
    g_afActive=TRUE;g_afAutomaticRun=FALSE;g_afState=12;g_moveContinuation=1;g_settleUntil=0;g_afStartPosition=g_simPosition;g_resumeLiveAfterAf=FALSE;g_exposing=FALSE;TimerTick();
    total++;passed+=test(!g_afActive&&!g_exposing&&g_afState==0,"Actual core: failed AF exposure aborts cleanly");
    g_stepAssistActive=TRUE;g_stepAssistState=2;g_stepAssistSettle=0;g_stepAssistStart=g_simPosition;g_resumeLiveAfterStep=FALSE;g_exposing=FALSE;TimerTick();
    total++;passed+=test(!g_stepAssistActive&&!g_exposing&&g_stepAssistState==0,"Actual core: failed step exposure aborts cleanly");
    fakeCreateFileFail=true;total++;passed+=test(!SaveDiagnostics(),"Actual core: diagnostics reports create failure");fakeCreateFileFail=false;
    fakePartialWrite=true;total++;passed+=test(!WriteTextFile(L"partial.txt","abcdef"),"Actual core: partial file write is rejected");total++;passed+=test(!ExportReport(L"Test"),"Actual core: report rejects partial write");fakePartialWrite=false;
    total++;passed+=test(QueryValueEquals("GET /api/action?name=live HTTP/1.1","name=","live")&&!QueryValueEquals("GET /api/action?name=live-extra HTTP/1.1","name=","live"),"Actual core: API names require exact match");
    total++;passed+=test(RequestPathEquals("GET /api/action?name=live HTTP/1.1","/api/action")&&!RequestPathEquals("GET /api/actionevil?name=live HTTP/1.1","/api/action"),"Actual core: API routes require exact path");
    UINT strictU=0;double strictD=0.0;
    total++;passed+=test(ParseStrictUIntW(L"  +123 ",&strictU)&&strictU==123U&&!ParseStrictUIntW(L"12x",&strictU)&&!ParseStrictUIntW(L"1 2",&strictU),"Actual core: strict integer parsing");
    total++;passed+=test(NormalizeAfPointText(L"12")==11U&&NormalizeAfPointText(L"4")==5U&&NormalizeAfPointText(L"16")==15U&&NormalizeAfPointText(L"abc")==9U,"Actual core: legacy AF point count normalized safely");
    total++;passed+=test(!ParseStrictUIntW(L"4294967296",&strictU)&&!ParseStrictUIntW(L"-1",&strictU),"Actual core: strict integer overflow/sign");
    total++;passed+=test(ParseStrictDoubleW(L" -1,5 ",&strictD)&&strictD==-1.5&&!ParseStrictDoubleW(L"1,2,3",&strictD)&&!ParseStrictDoubleW(L"1 2",&strictD),"Actual core: strict decimal parsing");

    // Direct boundary validation for values that previously could wrap or silently fall back.
    g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_exposing=FALSE;g_live=FALSE;g_simMaxStep=60000;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=12345;g_simOpticalPosition=12345;
    SetWindowTextW(g_manualStepEdit,L"12x");int invalidMovePos=g_simPosition;total++;passed+=test(!ManualMove(1)&&g_simPosition==invalidMovePos,"Actual core: invalid manual step rejected");
    g_simMaxStep=2147483647;g_safeMinPosition=0;g_safeMaxPosition=2147483647;g_simPosition=2147483642;g_simOpticalPosition=g_simPosition;SetWindowTextW(g_manualStepEdit,L"1000000");BOOL boundaryMove=ManualMove(1);total++;passed+=test(boundaryMove&&g_simPosition==2147483647,"Actual core: manual move cannot overflow int");

    SetWindowTextW(g_afStepEdit,L"5000");g_simPosition=2147483645;g_simOpticalPosition=g_simPosition;g_stepAssistActive=FALSE;StartStepAssistant();BOOL stepBoundary=g_stepAssistActive&&g_stepAssistPositions[0]==2147478645&&g_stepAssistPositions[1]==2147483645&&g_stepAssistPositions[2]==2147483647;total++;passed+=test(stepBoundary,"Actual core: step assistant boundary planning");if(g_stepAssistActive)FinishStepAssistant(L"Grenztest beendet");

    g_simMaxStep=60000;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,TRUE,FALSE,FALSE);SetWindowTextW(g_afPointsEdit,L"8");SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afSamplesEdit,L"2");SetWindowTextW(g_afBacklashEdit,L"250");g_afAutomaticRequest=TRUE;StartAutofocus();g_afAutomaticRequest=FALSE;total++;passed+=test(!g_afActive,"Actual core: even AF point count rejected");

    g_simMaxStep=2147483647;g_safeMinPosition=0;g_safeMaxPosition=2147483647;g_simPosition=2147482647;g_simOpticalPosition=g_simPosition;SetWindowTextW(g_afPointsEdit,L"15");SetWindowTextW(g_afStepEdit,L"1000000");SetWindowTextW(g_afSamplesEdit,L"1");SetWindowTextW(g_afBacklashEdit,L"1000000");g_afAutomaticRequest=TRUE;StartAutofocus();g_afAutomaticRequest=FALSE;BOOL afBoundary=g_afActive&&g_afPositions[0]>=0&&g_afPositions[14]==2147483647;for(int i=1;i<15;i++)if(g_afPositions[i]<=g_afPositions[i-1])afBoundary=FALSE;total++;passed+=test(afBoundary,"Actual core: AF boundary plan cannot overflow");if(g_afActive)StopAutofocus(TRUE,L"Grenztest beendet");

    g_simMaxStep=60000;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=g_simBestFocus;g_simOpticalPosition=g_simPosition;SetWindowTextW(g_manualStepEdit,L"100");SetWindowTextW(g_afPointsEdit,L"9");SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afSamplesEdit,L"2");SetWindowTextW(g_afBacklashEdit,L"250");g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_frameReady=TRUE;

    // Version 3.9.0: explicit auto-refocus reference lifecycle and detailed failure classification.
    SetAutoRefocusEnabled(FALSE);g_frameReady=FALSE;g_usedCount=0;g_lastGoodFwhm=0.0;SetAutoRefocusEnabled(TRUE);total++;passed+=test(g_autoRefocusEnabled&&IsChecked(g_autoRefocusCheck)&&!g_autoRefocusReferenceReady&&WContains(g_lastAutoRefocusReason,L"wartet auf erste Referenzmessung"),"Actual core: auto-refocus waits for first reference");
    GenerateSyntheticFrame(g_simBestFocus,1.0,0,0,48,TRUE,FALSE,FALSE);g_lastCompletedPurpose=1;EnsureAutoRefocusMeasurementReference();total++;passed+=test(g_autoRefocusReferenceReady&&g_lastGoodFwhm>0.0,"Actual core: suitable frame establishes reference");

    // Version 3.9.0 hardening: one shared star limit is authoritative for the reference and field-median autofocus.
    SetAutoRefocusEnabled(FALSE);g_refocusMinStars=4;g_frameReady=TRUE;g_medianFwhm=3.0;g_medianHfr=1.5;g_usedCount=3;g_lastGoodFwhm=0.0;SetAutoRefocusEnabled(TRUE);double metricH=0.0,metricF=0.0;int metricUsed=0;BOOL metricThree=CurrentAutofocusMetric(FALSE,&metricH,&metricF,&metricUsed);total++;passed+=test(!g_autoRefocusReferenceReady&&!metricThree,"Actual core: reference and AF both reject 3 of 4 stars");
    g_usedCount=4;g_lastCompletedPurpose=1;EnsureAutoRefocusMeasurementReference();BOOL metricFour=CurrentAutofocusMetric(FALSE,&metricH,&metricF,&metricUsed);total++;passed+=test(g_autoRefocusReferenceReady&&metricFour&&metricUsed==4,"Actual core: reference and AF both accept 4 of 4 stars");

    // Retry backoff must be deterministic and end in a visible manual-release pause.
    g_autoRefocusEnabled=TRUE;g_autoRefocusPaused=FALSE;g_autoRefocusFailureCount=0;g_autoRefocusRetryAfter=0;int expectedRetry[4]={30,60,120,300};BOOL retryLadder=TRUE;
    for(int i=0;i<4;i++){ScheduleAutoRefocusRetry(L"Testfehler");ULONGLONG remaining=g_autoRefocusRetryAfter>fakeNow?g_autoRefocusRetryAfter-fakeNow:0;if(g_autoRefocusFailureCount!=i+1||g_autoRefocusPaused||remaining!=(ULONGLONG)expectedRetry[i]*1000ULL)retryLadder=FALSE;}
    total++;passed+=test(retryLadder,"Actual core: retry ladder is 30/60/120/300 seconds");
    ScheduleAutoRefocusRetry(L"Testfehler");total++;passed+=test(g_autoRefocusPaused&&g_autoRefocusFailureCount==5&&g_autoRefocusRetryAfter==0,"Actual core: fifth failure pauses auto-refocus");
    g_refocusBadFrameStreak=7;ResumeAutoRefocusAfterPause();total++;passed+=test(!g_autoRefocusPaused&&g_autoRefocusFailureCount==0&&g_autoRefocusRetryAfter==0&&g_refocusBadFrameStreak==0,"Actual core: manual release resets retry state");

    // FWHM degradation must use unique frames, configurable star/stability limits and a configurable cooldown.
    g_autoRefocusEnabled=TRUE;g_autoRefocusPaused=FALSE;g_autoRefocusReferenceReady=TRUE;g_refocusFwhmThresholdPercent=30.0;g_degradationRefocusEnabled=TRUE;g_refocusBadFramesRequired=3;g_refocusMinStars=4;g_refocusStabilityLimit=0.45;g_lastGoodFwhm=3.0;g_medianFwhm=4.0;g_medianHfr=1.8;g_usedCount=4;g_trendCount=8;g_trendHead=8;for(int i=0;i<8;i++)g_trendFwhm[i]=4.0;g_seeingIndex=80.0;g_transparencyIndex=100.0;g_refocusBadFrameStreak=0;g_lastRefocusEvaluatedFrameSequence=100;g_frameSequence=101;UpdateRefocusDegradationState();UpdateRefocusDegradationState();g_frameSequence=102;UpdateRefocusDegradationState();g_frameSequence=103;UpdateRefocusDegradationState();
    total++;passed+=test(g_refocusBadFrameStreak==3,"Actual core: bad-frame streak counts unique frames only");
    g_usedCount=3;g_frameSequence=104;UpdateRefocusDegradationState();total++;passed+=test(g_refocusBadFrameStreak==0,"Actual core: insufficient stars reset FWHM streak");
    g_usedCount=4;g_refocusBadFrameStreak=g_refocusBadFramesRequired;g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_cachedFocuserMoving=FALSE;g_seeingIndex=80.0;g_transparencyIndex=100.0;g_refocusCooldownMinutes=10.0;g_lastAfCompleted=GetTickCount64();BOOL blockedByCooldown=!ShouldStartDegradationRefocus();g_refocusCooldownMinutes=0.0;BOOL releasedByCooldown=ShouldStartDegradationRefocus();total++;passed+=test(blockedByCooldown&&releasedByCooldown,"Actual core: configurable cooldown gates FWHM trigger");

    // Browser-origin checks must block cross-site mutations while preserving same-origin web UI and desktop IPC.
    g_refocusMinStars=4;RunFakeHttp("GET /api/set?name=refocusMinStars&value=9 HTTP/1.1\r\nHost: 127.0.0.1\r\nSec-Fetch-Site: cross-site\r\nOrigin: https://evil.example\r\nReferer: https://evil.example/page\r\n\r\n");
    total++;passed+=test(g_refocusMinStars==4&&strstr(fakeNetResponse,"\"ok\":false")!=0,"Actual core: cross-site browser mutation is blocked");
    RunFakeHttp("GET /api/set?name=refocusMinStars&value=9 HTTP/1.1\r\nHost: 127.0.0.1\r\nOrigin: http://127.0.0.1:8873.evil\r\nReferer: http://127.0.0.1:8873.evil/page\r\n\r\n");
    total++;passed+=test(g_refocusMinStars==4&&strstr(fakeNetResponse,"\"ok\":false")!=0,"Actual core: forged localhost prefix is rejected");
    RunFakeHttp("GET /api/set?name=refocusMinStars&value=5 HTTP/1.1\r\nHost: 127.0.0.1\r\nSec-Fetch-Site: same-origin\r\nOrigin: http://127.0.0.1:8873\r\nReferer: http://127.0.0.1:8873/\r\n\r\n");
    total++;passed+=test(g_refocusMinStars==5&&strstr(fakeNetResponse,"\"ok\":true")!=0,"Actual core: same-origin local web mutation is allowed");

    // API settings must update the productive values, including fractional thresholds.
    RunFakeHttp("GET /api/set?name=refocusFwhmPercent&value=25.5 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL apiFwhm=g_refocusFwhmThresholdPercent>25.49&&g_refocusFwhmThresholdPercent<25.51;
    RunFakeHttp("GET /api/set?name=refocusBadFrames&value=4 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL apiBad=g_refocusBadFramesRequired==4;
    RunFakeHttp("GET /api/set?name=refocusMinStars&value=5 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL apiStars=g_refocusMinStars==5;
    RunFakeHttp("GET /api/set?name=refocusStability&value=0.35 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL apiStability=g_refocusStabilityLimit>0.349&&g_refocusStabilityLimit<0.351;
    RunFakeHttp("GET /api/set?name=refocusCooldown&value=12.5 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL apiCooldown=g_refocusCooldownMinutes>12.49&&g_refocusCooldownMinutes<12.51;
    total++;passed+=test(apiFwhm&&apiBad&&apiStars&&apiStability&&apiCooldown,"Actual core: configurable refocus values accepted by API");
    g_autoRefocusEnabled=TRUE;g_autoRefocusPaused=TRUE;g_autoRefocusFailureCount=5;g_autoRefocusRetryAfter=fakeNow+300000;RunFakeHttp("GET /api/action?name=auto-refocus-resume HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");total++;passed+=test(!g_autoRefocusPaused&&g_autoRefocusFailureCount==0&&g_autoRefocusRetryAfter==0&&strstr(fakeNetResponse,"\"ok\":true")!=0,"Actual core: API manual release clears paused state");

    // A blocked in-process ASCOM call must be quarantined without keeping the main engine state connected.
    total++;passed+=test(DeviceRecoveryDelayMs(1)==30000ULL&&DeviceRecoveryDelayMs(2)==60000ULL&&DeviceRecoveryDelayMs(3)==120000ULL&&DeviceRecoveryDelayMs(4)==300000ULL&&DeviceRecoveryDelayMs(9)==300000ULL,"Actual core: device recovery uses bounded backoff");
    DeviceWorker* stalled=(DeviceWorker*)Alloc(sizeof(DeviceWorker));memset(stalled,0,sizeof(DeviceWorker));stalled->camera=TRUE;stalled->thread=(HANDLE)11;stalled->requestEvent=(HANDLE)12;stalled->doneEvent=(HANDLE)13;VariantInit(&stalled->result);g_cameraWorker=stalled;g_cameraWorkerBlocked=FALSE;g_cameraWorkerFaultPending=FALSE;BOOL workerReturned=SubmitWorker(stalled,DW_GET_BOOL,50,L"ImageReady");total++;passed+=test(!workerReturned&&g_cameraWorker==0&&g_cameraWorkerBlocked&&g_cameraWorkerFaultPending&&g_orphanWorkerCount==1,"Actual core: timed-out ASCOM worker is quarantined");
    g_cameraConnected=TRUE;g_live=TRUE;g_exposing=TRUE;g_capturePurpose=1;g_resumeLiveAfterCameraRecovery=FALSE;g_cameraWorkerRecoveryAttempt=0;g_afActive=FALSE;g_stepAssistActive=FALSE;g_afAutomaticRun=TRUE;ApplyDeviceWorkerFaults();total++;passed+=test(!g_cameraWorkerFaultPending&&!g_cameraConnected&&!g_live&&!g_exposing&&g_resumeLiveAfterCameraRecovery&&g_cameraWorkerRecoveryAttempt==1&&g_cameraWorkerRetryAfter==0&&g_cameraWorkerBlocked&&WContains(g_lastAfErrorCode,L"AF_ASCOM_WORKER_TIMEOUT"),"Actual core: worker fault disconnects safely and waits for driver release");
    g_autoRefocusEnabled=TRUE;g_autoRefocusPaused=FALSE;g_autoRefocusFailureCount=0;g_autoRefocusRetryAfter=0;g_afActive=TRUE;g_afAutomaticRun=TRUE;g_afPointIndex=0;g_resumeLiveAfterAf=FALSE;g_exposing=FALSE;SetAutofocusError(L"AF_ASCOM_WORKER_TIMEOUT",L"ASCOM-Kamera-Worker reagiert nicht",L"ASCOM-Kamera-Worker blockiert bei ImageReady",TRUE);StopAutofocus(FALSE,L"ASCOM-Kamera-Worker blockiert bei 'ImageReady'");total++;passed+=test(WContains(g_lastAfErrorCode,L"AF_ASCOM_WORKER_TIMEOUT")&&g_autoRefocusFailureCount==1&&g_autoRefocusRetryAfter>fakeNow,"Actual core: exact worker timeout survives AF stop and schedules one retry");
    g_cameraWanted=TRUE;g_autoReconnect=TRUE;g_cameraConnected=FALSE;g_cameraWorkerBlocked=TRUE;g_cameraWorker=0;g_cameraWorkerRetryAfter=0;g_cameraId[0]=L'A';g_cameraId[1]=0;int orphansBefore=g_orphanWorkerCount;AttemptAutomaticReconnect(fakeNow+600000ULL);total++;passed+=test(g_cameraWorker==0&&g_orphanWorkerCount==orphansBefore,"Actual core: blocked ASCOM camera cannot spawn duplicate worker");
    fakeThreadFinished=true;ULONGLONG beforeCleanup=fakeNow;CleanupOrphanWorkers();fakeThreadFinished=false;total++;passed+=test(g_orphanWorkerCount==0&&!g_cameraWorkerBlocked&&g_cameraWorkerRetryAfter>=beforeCleanup+30000ULL,"Actual core: released ASCOM worker is cleaned before delayed reconnect");
    g_cameraWorkerBlocked=FALSE;g_cameraWorkerRetryAfter=0;g_cameraWorkerRecoveryAttempt=0;g_cameraConnected=TRUE;g_live=FALSE;g_exposing=FALSE;g_afAutomaticRun=FALSE;g_refocusMinStars=4;g_refocusBadFramesRequired=3;g_refocusFwhmThresholdPercent=30.0;g_focusDegradeFactor=1.30;g_degradationRefocusEnabled=TRUE;g_refocusStabilityLimit=0.45;g_refocusCooldownMinutes=10.0;
    struct FailureCase{LPCWSTR reason;LPCWSTR code;};FailureCase failures[]={
        {L"Fokusstern verloren",L"AF_FOCUS_STAR_LOST"},{L"Zu wenige geeignete Sterne",L"AF_TOO_FEW_STARS"},{L"Bildübertragung fehlgeschlagen",L"AF_CAMERA_CAPTURE_FAILED"},{L"Fokussierer getrennt",L"AF_FOCUSER_NOT_CONNECTED"},{L"außerhalb der sicheren Fokuszone",L"AF_TARGET_OUTSIDE_SAFE_ZONE"},{L"Fokussierer bewegt sich noch",L"AF_FOCUSER_BUSY"},{L"ASCOM Position konnte nicht gelesen werden",L"AF_ASCOM_DRIVER_NOT_RESPONDING"},{L"Fokuskurve Fit unzureichend",L"AF_FIT_QUALITY_INSUFFICIENT"},{L"Kontrollmedian bestätigt die Endposition nicht",L"AF_END_POSITION_NOT_IMPROVED"}};
    BOOL allClassified=TRUE;for(unsigned i=0;i<sizeof(failures)/sizeof(failures[0]);i++){ClassifyAutofocusFailure(failures[i].reason,TRUE);if(!WContains(g_lastAfErrorCode,failures[i].code)||!g_lastAfErrorAutomatic)allClassified=FALSE;}total++;passed+=test(allClassified,"Actual core: detailed autofocus errors classified");
    SetWindowTextW(g_afPointsEdit,L"8");g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_frameReady=TRUE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_afAutomaticRequest=TRUE;StartAutofocus();g_afAutomaticRequest=FALSE;total++;passed+=test(!g_afActive&&WContains(g_lastAfErrorCode,L"AF_INVALID_POINT_COUNT"),"Actual core: invalid AF parameters get exact error");SetWindowTextW(g_afPointsEdit,L"9");
    // Star selection is a metadata-only operation. It must not touch the raw frame, rebuild the BMP,
    // or emit invalid JSON even under repeated clicks and damaged metrics.
    g_simulatorMode=TRUE;g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_simDeterministicTest=TRUE;GenerateSyntheticFrame(g_simBestFocus,1,0,0,48,TRUE,FALSE,FALSE);int pick=-1;for(int i=0;i<g_starCount;i++)if(g_stars[i].used&&!g_stars[i].saturated){pick=i;break;}unsigned selectionFrameSequence=g_frameSequence;UINT* savedRaw=g_raw;g_raw=0;char selectRequest[256];sprintf(selectRequest,"GET /api/action?name=select-star&x=%d&y=%d HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n",(int)(g_stars[pick].x+0.5),(int)(g_stars[pick].y+0.5));RunFakeHttp(selectRequest);BOOL metadataOnlySelection=pick>=0&&strstr(fakeNetResponse,"\"ok\":true")&&g_manualStarLocked&&g_selectedStar>=0&&g_frameSequence==selectionFrameSequence;g_raw=savedRaw;total++;passed+=test(metadataOnlySelection,"Actual core: star click is metadata-only and preserves frame");
    BOOL selectionStress=TRUE;for(int loop=0;loop<500;loop++){int i=loop%g_starCount;int x=(int)(g_stars[i].x+0.5),y=(int)(g_stars[i].y+0.5);BOOL expected=g_stars[i].used&&!g_stars[i].saturated&&IsTrackableFocusStar(&g_stars[i],TRUE);BOOL got=SelectManualStarAt(x,y);if(expected&&!got){selectionStress=FALSE;break;}if(g_selectedStar>=g_starCount){selectionStress=FALSE;break;}}total++;passed+=test(selectionStress&&g_frameSequence==selectionFrameSequence,"Actual core: 500 repeated star selections remain bounded");
    int validStar=g_selectedStar>=0?g_selectedStar:pick;double oldX=g_stars[validStar].x,oldY=g_stars[validStar].y,oldF=g_stars[validStar].fwhm;g_stars[validStar].x=0.0/0.0;g_stars[validStar].y=1.0e301;g_stars[validStar].fwhm=0.0/0.0;g_selectedStar=validStar;RunFakeHttp("GET /api/status HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL finiteStatus=!strstr(fakeNetResponse,"nan")&&!strstr(fakeNetResponse,"inf")&&strstr(fakeNetResponse,"\"selectedStar\":-1");g_stars[validStar].x=oldX;g_stars[validStar].y=oldY;g_stars[validStar].fwhm=oldF;ResolveSelectedStar();total++;passed+=test(finiteStatus,"Actual core: damaged star metrics cannot poison status JSON");
    char* tiny=(char*)Alloc(2);tiny[0]='a';tiny[1]=0;BOOL suffixSafe=!AContains(tiny,"ab")&&AFind(tiny,"a")==tiny;Free(tiny);total++;passed+=test(suffixSafe,"Actual core: suffix search remains inside NUL terminator");
    g_selectedStar=pick;g_manualStarLocked=TRUE;g_frameReady=TRUE;DrawSelectedPanel((HDC)1);total++;passed+=test(g_selectedStar==pick,"Actual core: selected-star panel renders valid star safely");
    DWORD* displayBefore=g_display;double pickX=g_stars[pick].x;g_display=0;g_stars[pick].x=0.0/0.0;DrawSelectedPanel((HDC)1);g_stars[pick].x=pickX;g_display=displayBefore;ResolveSelectedStar();total++;passed+=test(TRUE,"Actual core: selected-star panel rejects missing image and NaN safely");
    RunFakeHttp("GET /api/action?name=select-star&x=999999999&y=999999999 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");total++;passed+=test(strstr(fakeNetResponse,"\"ok\":false")&&!g_manualStarLocked,"Actual core: invalid star click is rejected and cleared");

    char bundleMessage[160];g_afUseSelectedStar=FALSE;BOOL bundleAccepted=ApplyAutofocusStartBundle("GET /api/action?name=autofocus-start&confirmed=1&exposure=800&gain=180&afPoints=9&afStep=120&afSamples=3&backlash=250&preferredOut=1&afSelectedStar=0 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n",bundleMessage,160);wchar_t bundleValue[64];GetWindowTextW(g_afPointsEdit,bundleValue,64);BOOL bundleValues=bundleAccepted&&WContains(bundleValue,L"9");GetWindowTextW(g_afStepEdit,bundleValue,64);bundleValues=bundleValues&&WContains(bundleValue,L"120");GetWindowTextW(g_afSamplesEdit,bundleValue,64);bundleValues=bundleValues&&WContains(bundleValue,L"3");GetWindowTextW(g_afBacklashEdit,bundleValue,64);bundleValues=bundleValues&&WContains(bundleValue,L"250")&&IsChecked(g_preferredDirCheck)&&!g_afUseSelectedStar;total++;passed+=test(bundleValues,"Actual core: atomic AF parameter bundle accepted");
    BOOL bundleRejected=!ApplyAutofocusStartBundle("GET /api/action?name=autofocus-start&confirmed=1&exposure=800&gain=180&afPoints=8&afStep=120&afSamples=3&backlash=250&preferredOut=1&afSelectedStar=0 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n",bundleMessage,160);total++;passed+=test(bundleRejected&&WContains(g_lastAfErrorCode,L"AF_INVALID_POINT_COUNT"),"Actual core: invalid atomic AF bundle gets exact error");
    // Full desktop-equivalent route: a single confirmed HTTP request must both apply the bundle and enter StartAutofocus.
    g_afActive=FALSE;g_stepAssistActive=FALSE;g_afAutomaticRequest=FALSE;g_afUseSelectedStar=FALSE;g_manualStarLocked=FALSE;g_selectedStar=-1;
    g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_simulatorMode=TRUE;g_frameReady=TRUE;g_live=FALSE;g_exposing=FALSE;
    g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=g_simBestFocus;g_simOpticalPosition=g_simBestFocus;g_simLastDirection=0;
    GenerateSyntheticFrame(g_simBestFocus,1.0,0,0,48,TRUE,FALSE,FALSE);
    RunFakeHttp("GET /api/action?name=autofocus-start&confirmed=1&exposure=800&gain=180&afPoints=9&afStep=120&afSamples=3&backlash=250&preferredOut=1&afSelectedStar=0 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL atomicRouteStarted=strstr(fakeNetResponse,"\"ok\":true")!=0&&g_afActive&&g_afPointCount==9&&g_afStep==120&&g_afSamples==3&&g_afBacklash==250;
    total++;passed+=test(atomicRouteStarted,"Actual core: one confirmed HTTP AF bundle reaches autofocus start");
    if(g_afActive){g_afActive=FALSE;g_afState=0;g_exposing=FALSE;g_capturePurpose=0;g_resumeLiveAfterAf=FALSE;SetWindowTextW(g_afButton,L"Autofokus starten");}

    // 3.1 focus-intelligence regression suite: every new feature is exercised with deterministic synthetic state.
    g_trendCount=0;g_trendHead=0;g_usedCount=42;g_lastGoodFwhm=3.00;g_medianFwhm=3.02;SetWindowTextW(g_refocusMinutesEdit,L"0");SetWindowTextW(g_refocusTempEdit,L"0");
    for(int i=0;i<10;i++){g_usedCount=42;AppendTrend(3.00+((i%3)-1)*0.012,1.50);}double stableSeeing=g_seeingIndex;
    total++;passed+=test(stableSeeing>=70.0&&g_transparencyIndex>=95.0,"3.1 intelligence: stable seeing recognized");
    g_trendCount=0;g_trendHead=0;for(int i=0;i<10;i++){g_usedCount=40;AppendTrend((i&1)?4.30:2.70,1.50);}g_usedCount=14;UpdateSeeingAndFocusRecommendation();double poorSeeing=g_seeingIndex;
    total++;passed+=test(poorSeeing<stableSeeing&&g_transparencyIndex<50.0,"3.1 intelligence: poor seeing/clouds recognized");

    // Poor atmosphere must not merely change the traffic light: it must block the real FWHM auto-refocus gate.
    g_autoRefocusEnabled=TRUE;g_autoRefocusPaused=FALSE;g_autoRefocusReferenceReady=TRUE;g_degradationRefocusEnabled=TRUE;g_refocusFwhmThresholdPercent=30.0;g_lastGoodFwhm=3.0;g_medianFwhm=4.2;g_refocusBadFramesRequired=3;g_refocusBadFrameStreak=3;g_refocusCooldownMinutes=0.0;g_lastAfCompleted=0;g_afActive=FALSE;g_stepAssistActive=FALSE;g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_cachedFocuserMoving=FALSE;
    BOOL poorAtmosphereBlocked=!ShouldStartDegradationRefocus();g_seeingIndex=80.0;g_transparencyIndex=100.0;BOOL stableAtmosphereAllows=ShouldStartDegradationRefocus();
    total++;passed+=test(poorAtmosphereBlocked&&stableAtmosphereAllows,"3.1 intelligence: seeing/transparency gate blocks false FWHM refocus");
    g_seeingIndex=20.0;g_transparencyIndex=40.0;g_refocusBadFrameStreak=2;g_refocusMinStars=4;g_refocusStabilityLimit=10.0;g_usedCount=40;g_lastRefocusEvaluatedFrameSequence=500;g_frameSequence=501;UpdateRefocusDegradationState();
    total++;passed+=test(g_refocusBadFrameStreak==0,"3.1 intelligence: poor atmosphere resets degradation streak");

    g_trendCount=0;g_trendHead=0;for(int i=0;i<10;i++){g_usedCount=40;AppendTrend(3.01+((i%2)?0.01:-0.01),1.50);}g_usedCount=40;g_lastGoodFwhm=3.0;g_medianFwhm=4.05;g_refocusFwhmThresholdPercent=30.0;UpdateSeeingAndFocusRecommendation();
    total++;passed+=test(g_focusNeedScore>=85&&WContains(g_focusNeedLabel,L"Refokus erforderlich")&&WContains(g_focusNeedReason,L"FWHM seit Referenz")&&WContains(g_focusNeedReason,L"Messungen schlechter"),"3.9.0 intelligence: autofocus traffic light turns red with dynamic reason");

    g_fitConfidence=0.96;g_fitR2=0.97;g_fitFwhmR2=0.95;g_afExpectedFwhm=3.0;g_afExpectedHfr=1.50;g_afRunUsesSelectedStar=FALSE;int highQuality=CalculateAutofocusQualityScore(3.02,1.51,35,0.05);
    g_fitConfidence=0.30;g_fitR2=0.40;g_fitFwhmR2=0.35;int lowQuality=CalculateAutofocusQualityScore(3.70,1.90,4,0.70);
    total++;passed+=test(highQuality>=80&&lowQuality<highQuality,"3.1 intelligence: autofocus quality score discriminates");

    for(int z=0;z<9;z++){g_zoneCount[z]=12;g_zoneFwhm[z]=3.35;}g_zoneFwhm[4]=3.00;g_zoneFwhm[0]=3.85;g_zoneFwhm[2]=3.80;g_zoneFwhm[6]=3.90;g_zoneFwhm[8]=3.82;ComputeTilt();
    total++;passed+=test(g_tiltValid&&g_fieldCurvature>0.6&&g_fieldQualityScore<100.0&&g_fieldAdvice[0],"3.1 intelligence: field curvature/tilt diagnostics");

    g_profileSuccessfulRuns=0;g_profileModelValid=FALSE;g_profileTypicalPosition=-1;g_profileTypicalFwhm=g_profileTypicalHfr=g_profileQualityMean=0.0;SetWindowTextW(g_afStepEdit,L"140");SetWindowTextW(g_afBacklashEdit,L"260");
    g_afFinalValid=TRUE;g_afFinalPosition=24500;g_afFinalFwhm=3.10;g_afFinalHfr=1.55;g_focusQualityScore=90;UpdateFocusProfileModelAfterSuccess();
    g_afFinalPosition=24700;g_afFinalFwhm=3.30;g_afFinalHfr=1.65;g_focusQualityScore=80;UpdateFocusProfileModelAfterSuccess();
    total++;passed+=test(g_profileModelValid&&g_profileSuccessfulRuns==2&&g_profileTypicalPosition==24600&&g_profileRecommendedStep==140&&g_profileBacklash==260&&g_profileQualityMean>84.9&&g_profileQualityMean<85.1,"3.1 intelligence: equipment focus model learns runs");

    g_tempProfileCount=0;g_tempFitValid=FALSE;AddTemperaturePoint(10.0,24000);AddTemperaturePoint(11.0,24050);AddTemperaturePoint(12.0,24100);g_hasFocuserTemperature=TRUE;g_focuserTemperature=13.0;g_tempCompEnabled=TRUE;g_tempCompDeadbandSteps=10;g_tempCompMaxStep=120;g_lastTempCompMove=0;g_afActive=g_stepAssistActive=g_backlashCalActive=g_exposing=FALSE;g_simulatorMode=TRUE;g_focuserConnected=TRUE;g_simPosition=24000;g_simOpticalPosition=24000;g_simLastDirection=0;g_simBacklashRemaining=0;ApplyTemperatureCompensation(fakeNow+60000ULL);
    total++;passed+=test(g_tempFitValid&&g_tempSlope>49.9&&g_tempSlope<50.1&&g_lastTempCompTarget==24150&&g_simPosition==24120,"3.1 intelligence: temperature compensation bounded micro-move");

    g_autoStartPositionEnabled=TRUE;g_profileModelValid=TRUE;g_profileTypicalPosition=25000;g_hasFocuserTemperature=FALSE;g_simPosition=24000;g_simOpticalPosition=24000;g_simLastDirection=0;g_simBacklashRemaining=0;TryAutomaticStartPosition();
    total++;passed+=test(g_simPosition==25000&&g_lastTempCompTarget==25000,"3.1 intelligence: automatic start position");

    g_filterOffsetCount=0;g_filterReferencePosition=-1;g_currentFilter[0]=0;g_refocusOnFilter=FALSE;g_simPosition=24000;g_simOpticalPosition=24000;g_simLastDirection=0;g_simBacklashRemaining=0;BOOL learnL=LearnCurrentFilterOffset(L"L");g_simPosition=24120;g_simOpticalPosition=24120;BOOL learnHa=LearnCurrentFilterOffset(L"Ha");g_simPosition=24000;g_simOpticalPosition=24000;CopyWBounded(g_currentFilter,32,L"L");BOOL applyHa=ApplyFilterOffset(L"Ha");
    total++;passed+=test(learnL&&learnHa&&applyHa&&g_filterOffsetCount==2&&g_simPosition==24120&&WEquals(g_currentFilter,L"Ha"),"3.1 intelligence: filter focus offsets learned/applied");

    g_autoRefocusEnabled=FALSE;g_refocusOnMeridian=TRUE;g_refocusOnReconnect=TRUE;g_refocusOnFilter=TRUE;g_refocusEveryCaptures=2;g_captureEventCounter=0;HandleExternalRefocusEvent(L"Meridian-Flip");BOOL eventStored=WContains(g_lastExternalEvent,L"Meridian");RunFakeHttp("GET /api/action?name=capture-complete HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");RunFakeHttp("GET /api/action?name=capture-complete HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    total++;passed+=test(eventStored&&g_captureEventCounter==0&&WContains(g_lastExternalEvent,L"Aufnahme"),"3.1 intelligence: external refocus events/capture cadence");

    g_sessionPath[0]=0;g_sessionHeaderWritten=FALSE;AppendSessionEvent(L"Synthetischer Test",L"Session-Nachtprotokoll");
    total++;passed+=test(g_sessionHeaderWritten&&g_sessionPath[0]!=0,"3.1 intelligence: session/night log initialized");

    // End-to-end synthetic backlash calibration across the complete advertised simulator range.
    int cal0=-1,inc0=0,lim0=0,guard0=0;BOOL ok0=RunBacklashCalibrationCase(0,&cal0,&inc0,&lim0,&guard0);
    int cal250=-1,inc250=0,lim250=0,guard250=0;BOOL ok250=RunBacklashCalibrationCase(250,&cal250,&inc250,&lim250,&guard250);
    int cal1000=-1,inc1000=0,lim1000=0,guard1000=0;BOOL ok1000=RunBacklashCalibrationCase(1000,&cal1000,&inc1000,&lim1000,&guard1000);
    int cal5000=-1,inc5000=0,lim5000=0,guard5000=0;BOOL ok5000=RunBacklashCalibrationCase(5000,&cal5000,&inc5000,&lim5000,&guard5000);
    printf("backlash details: 0=>%d inc=%d limit=%d guard=%d; 250=>%d inc=%d limit=%d guard=%d; 1000=>%d inc=%d limit=%d guard=%d; 5000=>%d inc=%d limit=%d guard=%d\n",cal0,inc0,lim0,guard0,cal250,inc250,lim250,guard250,cal1000,inc1000,lim1000,guard1000,cal5000,inc5000,lim5000,guard5000);
    total++;passed+=test(ok0&&cal0>=0&&cal0<=inc0&&ok250&&((cal250>=250)?(cal250-250):(250-cal250))<=inc250&&ok1000&&((cal1000>=1000)?(cal1000-1000):(1000-cal1000))<=inc1000&&ok5000&&((cal5000>=5000)?(cal5000-5000):(5000-cal5000))<=inc5000&&lim5000>5000,"3.9.0 simulator: backlash calibration covers 0..5000-step range");
    g_backlashCalActive=FALSE;g_simBacklashSteps=5000;g_simPosition=g_simBestFocus;g_simOpticalPosition=g_simPosition;g_simLastDirection=0;g_simBacklashRemaining=0;g_safeMinPosition=g_simBestFocus-2000;g_safeMaxPosition=g_simBestFocus+2000;SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afBacklashEdit,L"250");StartBacklashCalibration();
    total++;passed+=test(!g_backlashCalActive&&WContains(controls[HI(g_status)].text,L"sichere Fokuszone reicht"),"3.9.0 simulator: insufficient safe travel fails before calibration starts");g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;

    // Known filter offset schedules the optional post-filter refocus only after the move has finished.
    g_refocusOnFilter=TRUE;g_autoRefocusEnabled=FALSE;g_filterRefocusPending=FALSE;CopyWBounded(g_currentFilter,32,L"L");g_simPosition=24000;g_simOpticalPosition=24000;g_simLastDirection=0;g_simBacklashRemaining=0;ApplyFilterOffset(L"Ha");BOOL pendingAfterFilter=g_filterRefocusPending;TimerTick();
    total++;passed+=test(pendingAfterFilter&&!g_filterRefocusPending&&WContains(g_lastExternalEvent,L"Filter"),"3.1 intelligence: post-filter refocus is deferred until move completes");

    // 3.9.0 deep-audit regressions: focus-operation isolation and live-only trend/reference input.
    g_backlashCalActive=TRUE;g_live=FALSE;g_exposing=FALSE;StartLive();BOOL liveBlockedByBacklash=!g_live&&!g_exposing;int busyPos=g_simPosition;SetWindowTextW(g_manualStepEdit,L"25");BOOL moveBlockedByBacklash=!ManualMove(1)&&g_simPosition==busyPos;CopyWBounded(g_currentFilter,32,L"L");BOOL learnBlockedByBacklash=!LearnCurrentFilterOffset(L"L");BOOL applyBlockedByBacklash=!ApplyFilterOffset(L"Ha");g_backlashCalActive=FALSE;
    total++;passed+=test(liveBlockedByBacklash&&moveBlockedByBacklash&&learnBlockedByBacklash&&applyBlockedByBacklash,"3.9.0 audit: backlash mode blocks conflicting operations");

    g_trendCount=0;g_trendHead=0;g_autoRefocusReferenceReady=FALSE;g_lastGoodFwhm=0.0;g_autoRefocusEnabled=TRUE;g_refocusMinStars=4;g_usedCount=10;g_medianFwhm=3.2;g_medianHfr=1.6;g_lastCompletedPurpose=2;EnsureAutoRefocusMeasurementReference();BOOL afDoesNotSetReference=!g_autoRefocusReferenceReady;g_lastCompletedPurpose=1;EnsureAutoRefocusMeasurementReference();BOOL liveSetsReference=g_autoRefocusReferenceReady&&g_lastGoodFwhm==3.2;
    total++;passed+=test(afDoesNotSetReference&&liveSetsReference,"3.9.0 audit: only completed live frames establish refocus reference");

    g_autoStartPending=TRUE;g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;g_frameReady=TRUE;g_usedCount=10;g_medianFwhm=3.4;g_medianHfr=1.7;g_afAutomaticRequest=TRUE;g_afRequestConfirmed=TRUE;SetWindowTextW(g_afPointsEdit,L"9");SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afSamplesEdit,L"1");SetWindowTextW(g_afBacklashEdit,L"250");StartAutofocus();g_afAutomaticRequest=FALSE;g_afRequestConfirmed=FALSE;BOOL pendingConsumed=g_afActive&&!g_autoStartPending;if(g_afActive)StopAutofocus(TRUE,L"Auto-Start-Pending-Test beendet");
    total++;passed+=test(pendingConsumed,"3.9.0 audit: accepted autofocus consumes pending auto-start move");

    g_backlashCalActive=TRUE;g_resumeLiveAfterBacklash=TRUE;g_capturePurpose=0;StopBacklashCalibration(FALSE,L"Disconnect-Test");BOOL noBacklashResume=!g_backlashCalActive&&!g_resumeLiveAfterBacklash&&!g_live;g_stepAssistActive=TRUE;g_resumeLiveAfterStep=TRUE;g_capturePurpose=0;StopStepAssistant(FALSE,L"Disconnect-Test");BOOL noStepResume=!g_stepAssistActive&&!g_resumeLiveAfterStep&&!g_live;
    total++;passed+=test(noBacklashResume&&noStepResume,"3.9.0 audit: forced stop never resumes live capture");

    // 3.9.0 audit regressions: stale telemetry, trustworthy rollback state and clean session statistics.
    g_sessionBestFwhm=0.0;g_sessionWorstFwhm=0.0;g_medianFwhm=9.0;UpdateSessionMeasurement(2);
    BOOL afFrameIgnored=g_sessionBestFwhm==0.0&&g_sessionWorstFwhm==0.0;g_medianFwhm=3.0;UpdateSessionMeasurement(1);g_medianFwhm=7.5;UpdateSessionMeasurement(4);g_medianFwhm=3.5;UpdateSessionMeasurement(1);
    total++;passed+=test(afFrameIgnored&&g_sessionBestFwhm==3.0&&g_sessionWorstFwhm==3.5,"3.9.0 audit: only live frames enter session FWHM range");

    g_tempProfileCount=0;g_tempFitValid=FALSE;g_hasFocuserTemperature=TRUE;g_focuserTemperature=8.5;g_focuserConnected=TRUE;g_simulatorMode=TRUE;g_afFinalValid=TRUE;g_afFinalPosition=24680;g_afBestPosition=24000;g_afFinalFwhm=2.9;g_afFinalHfr=1.45;g_focusQualityScore=92;g_afAutomaticRun=FALSE;RecordSuccessfulFocus();
    total++;passed+=test(g_tempProfileCount==1&&g_tempProfileP[0]==24680,"3.9.0 audit: temperature model records confirmed final position");

    g_afActive=FALSE;g_stepAssistActive=FALSE;g_focuserConnected=TRUE;g_hasFocuserTemperature=TRUE;g_focuserTemperature=9.7;DisconnectFocuser();
    total++;passed+=test(!g_focuserConnected&&!g_hasFocuserTemperature&&g_cachedFocuserPosition==-1,"3.9.0 audit: focuser disconnect clears stale telemetry");

    g_afActive=TRUE;g_afState=0;g_afPointIndex=0;g_afAutomaticRun=FALSE;g_resumeLiveAfterAf=FALSE;g_afValidationPassed=FALSE;g_afRollbackPerformed=FALSE;CopyWBounded(g_afValidationState,96,L"Abgelehnt · Rollback ausstehend");g_focuserConnected=FALSE;StopAutofocus(TRUE,L"Kontrollmedian abgelehnt");
    total++;passed+=test(!g_afRollbackPerformed&&WContains(g_afValidationState,L"Rollback nicht möglich"),"3.9.0 audit: failed rollback is never reported as completed");

    g_afActive=TRUE;g_afState=0;g_afPointIndex=0;g_afAutomaticRun=FALSE;g_resumeLiveAfterAf=FALSE;g_afValidationPassed=FALSE;SetAfValidationState(FALSE,FALSE,L"Fokuslauf aktiv",L"Test");StopAutofocus(FALSE,L"Benutzerabbruch");
    total++;passed+=test(!g_afRollbackPerformed&&WContains(g_afValidationState,L"Abgebrochen"),"3.9.0 audit: abort clears active validation state");

    g_afFinalValid=FALSE;g_afFinalPosition=24680;g_hasFocuserTemperature=TRUE;g_focuserConnected=FALSE;RunFakeHttp("GET /api/v1/status HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL invalidApi=strstr(fakeNetResponse,"\"finalValid\":false")&&strstr(fakeNetResponse,"\"lastPosition\":-1")&&strstr(fakeNetResponse,"\"hasTemperature\":false");
    g_afFinalValid=TRUE;g_afFinalPosition=24680;RunFakeHttp("GET /api/v1/status HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL validApi=strstr(fakeNetResponse,"\"finalValid\":true")&&strstr(fakeNetResponse,"\"lastPosition\":24680");
    total++;passed+=test(invalidApi&&validApi,"3.9.0 audit: observatory API marks final result validity explicitly");


    // 3.9.0 numeric, persistence and native-buffer hardening.
    total++;passed+=test(QueryInt("GET /x?v=2147483647 HTTP/1.1","v=",7)==2147483647&&QueryInt("GET /x?v=-2147483648 HTTP/1.1","v=",7)==(-2147483647-1)&&QueryInt("GET /x?v=999999999999999999999999 HTTP/1.1","v=",7)==7,"3.9.0 audit: HTTP integer parsing rejects overflow");
    unsigned parsedUInt=0;int parsedInt=0;
    total++;passed+=test(ParseStrictUIntW(L"4294967295",&parsedUInt)&&parsedUInt==0xffffffffU&&!ParseStrictUIntW(L"42949672960",&parsedUInt)&&ParseStrictIntW(L"-2147483648",&parsedInt)&&parsedInt==(-2147483647-1)&&!ParseStrictIntW(L"2147483648",&parsedInt),"3.9.0 audit: profile integer parsing is range safe");
    total++;passed+=test(ParseAsciiInt("2147483647",5)==2147483647&&ParseAsciiInt("999999999999999999999",5)==5&&ParseAsciiDouble("12345678901234567890.5",12.5)>1.0e18,"3.9.0 audit: CSV number parsing avoids integer UB");
    total++;passed+=test(RoundedModelPosition(1.0e250,0,200000)==200000&&RoundedModelPosition(-1.0e250,0,200000)==0&&RoundedModelPosition(12345.49,0,200000)==12345,"3.9.0 audit: temperature model prediction is bounded before cast");

    g_tempProfileCount=0;g_tempFitValid=FALSE;AddTemperaturePoint(101.0,20000);AddTemperaturePoint(10.0,-1);BOOL invalidTempIgnored=g_tempProfileCount==0;AddTemperaturePoint(10.0,20000);AddTemperaturePoint(11.0,20050);
    total++;passed+=test(invalidTempIgnored&&g_tempFitValid&&g_tempSlope>49.9&&g_tempSlope<50.1,"3.9.0 audit: invalid temperature-profile points are ignored");

    ResetFakeProfileStorage();g_sessionPath[0]=0;g_sessionHeaderWritten=FALSE;fakePartialWrite=true;AppendSessionEvent(L"Bad;Event\r\n",L"Broken;Detail\n");BOOL partialHeaderRejected=!g_sessionHeaderWritten;fakePartialWrite=false;
    char safeCsv[64];CsvSafeAscii(L"A;B\r\nC",safeCsv,64);
    total++;passed+=test(partialHeaderRejected&&strstr(safeCsv,";")==0&&strstr(safeCsv,"\r")==0&&strstr(safeCsv,"\n")==0,"3.9.0 audit: session CSV handles partial writes and separators");

    PFN_Toupcam_PullImageWithRowPitchV2 savedRowPitch=pToupcam_PullImageWithRowPitchV2;pToupcam_PullImageWithRowPitchV2=(PFN_Toupcam_PullImageWithRowPitchV2)(ULONG_PTR)1;
    Free(g_nativeRgb);g_nativeRgb=0;g_nativeStride=0;g_nativeRgbBytes=0;BOOL nativePrepared=PrepareNativeBuffers(640,480);BOOL nativeRejected=!PrepareNativeBuffers(10001,480)&&!PrepareNativeBuffers(640,10001);SIZE_T nativeBytes=g_nativeRgbBytes;Free(g_nativeRgb);g_nativeRgb=0;g_nativeStride=0;g_nativeRgbBytes=0;pToupcam_PullImageWithRowPitchV2=savedRowPitch;
    total++;passed+=test(nativePrepared&&nativeRejected&&nativeBytes>=(SIZE_T)640*480*3,"3.9.0 audit: native camera buffer is preflighted safely");

    // 3.9.0 simulator profiles and calibrated mechanical backlash.
    g_simulatorMode=TRUE;g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_simDeterministicTest=FALSE;g_simOpticalPosition=g_simBestFocus;g_simPosition=g_simBestFocus;
    g_simActiveProfile=SIM_NORMAL;g_simFrameSequence=801;GenerateSimulatorStreamFrame(1);int normalStars=g_usedCount;double normalFwhm=g_medianFwhm;
    g_simActiveProfile=SIM_FEW_STARS;g_simFrameSequence=802;GenerateSimulatorStreamFrame(1);int fewStars=g_usedCount;
    g_simActiveProfile=SIM_DEFOCUSED;g_simFrameSequence=803;GenerateSimulatorStreamFrame(1);double defocusedFwhm=g_medianFwhm;
    total++;passed+=test(normalStars>=20&&fewStars<normalStars&&defocusedFwhm>normalFwhm*1.35,"3.9.0 simulator: distinct star-count and defocus profiles");
    g_simActiveProfile=SIM_POOR_SEEING;g_simFrameSequence=806;GenerateSimulatorStreamFrame(1);double poorSeeingFwhm=g_medianFwhm;
    g_simActiveProfile=SIM_THIN_CLOUDS;g_simFrameSequence=807;GenerateSimulatorStreamFrame(1);int cloudStars=g_usedCount;double cloudSnr=g_medianSnr;
    g_simActiveProfile=SIM_ELONGATED;g_simFrameSequence=808;GenerateSimulatorStreamFrame(1);double elongatedEcc=g_medianEcc;
    total++;passed+=test(poorSeeingFwhm>normalFwhm*1.05&&(cloudStars<normalStars||cloudSnr<s)&&elongatedEcc>0.45,"3.9.0 simulator: poor seeing, thin-cloud and elongated profiles are distinct");
    g_simActiveProfile=SIM_VARIABLE_SEEING;g_simFrameSequence=810;GenerateSimulatorStreamFrame(1);double seeingA=g_medianFwhm;g_simFrameSequence=813;GenerateSimulatorStreamFrame(1);double seeingB=g_medianFwhm;
    total++;passed+=test(fabs(seeingA-seeingB)>0.08,"3.9.0 simulator: variable seeing changes focus metric");
    g_simActiveProfile=SIM_DIFFICULT;g_simFrameSequence=820;GenerateSimulatorStreamFrame(5);double calA=g_medianHfr;int calStarsA=g_usedCount;g_simFrameSequence=821;GenerateSimulatorStreamFrame(5);double calB=g_medianHfr;int calStarsB=g_usedCount;
    total++;passed+=test(calStarsA>=g_refocusMinStars&&calStarsA==calStarsB&&fabs(calA-calB)<0.0001,"3.9.0 simulator: backlash calibration stream is deterministic");
    unsigned randomSeq0=g_simProfileSelectionSequence;g_simProfileMode=SIM_RANDOM;SelectSimulatorProfile();int randomA=g_simActiveProfile;SelectSimulatorProfile();int randomB=g_simActiveProfile;total++;passed+=test(randomA>=SIM_NORMAL&&randomA<=SIM_DIFFICULT&&randomB>=SIM_NORMAL&&randomB<=SIM_DIFFICULT&&g_simProfileSelectionSequence==randomSeq0+2,"3.9.0 simulator: random profile selection is bounded and advances");
    g_simDeterministicTest=TRUE;g_simProfileMode=SIM_NORMAL;g_simActiveProfile=SIM_NORMAL;CopyWBounded(g_simProfileName,96,SimulatorProfileName(g_simActiveProfile));

    // 3.9.0 named-profile serialization, validation, deterministic simulator seed and safe application.
    SetWindowTextW(g_exposureEdit,L"1250");SetWindowTextW(g_gainEdit,L"210");SetWindowTextW(g_manualStepEdit,L"140");SetWindowTextW(g_afPointsEdit,L"11");SetWindowTextW(g_afStepEdit,L"150");SetWindowTextW(g_afBacklashEdit,L"320");SetWindowTextW(g_afSamplesEdit,L"3");
    g_safeMinPosition=100;g_safeMaxPosition=180000;g_simProfileMode=SIM_RANDOM;g_simBacklashSteps=775;g_simRandomSeed=0x1234ABCDU;g_profileSuccessfulRuns=7;g_profileTypicalPosition=24512;g_profileRecommendedStep=145;g_profileBacklash=310;g_profileTypicalFwhm=2.75;g_profileTypicalHfr=1.37;g_profileQualityMean=91.5;
    CopyWBounded(g_cameraId,256,L"Camera.Test.Profile");CopyWBounded(g_focuserId,256,L"Focuser.Test.Profile");CopyWBounded(g_currentFilter,32,L"Ha");g_filterOffsetCount=1;CopyWBounded(g_filterOffsets[0].name,32,L"Ha");g_filterOffsets[0].offset=125;g_filterOffsets[0].valid=TRUE;g_tempProfileCount=2;g_tempProfileT[0]=10.0;g_tempProfileP[0]=24500;g_tempProfileT[1]=9.0;g_tempProfileP[1]=24600;
    ProfileSnapshot profileOriginal,profileParsed;CaptureProfileSnapshot(&profileOriginal,L"C8 + Reducer");char profileJson[65536];wchar_t profileError[256];BOOL profileSerialized=SerializeProfile(&profileOriginal,profileJson,65536);BOOL profileParsedOk=profileSerialized&&ParseProfileJson(profileJson,&profileParsed,profileError,256);
    total++;passed+=test(profileParsedOk&&WEquals(profileParsed.name,L"C8 + Reducer")&&profileParsed.gain==210&&profileParsed.afPoints==11&&profileParsed.afBacklash==320&&profileParsed.simulatorSeed==0x1234ABCDU&&profileParsed.filterCount==1&&profileParsed.tempCount==2,"3.9.0 profiles: JSON round-trip preserves all representative settings");
    char tamperedProfile[65536];memcpy(tamperedProfile,profileJson,(SIZE_T)ALen(profileJson)+1);char* gainField=strstr(tamperedProfile,"\"gain\":210");if(gainField){gainField+=7;gainField[0]='9';}ProfileSnapshot tamperedParsed;BOOL tamperRejected=!ParseProfileJson(tamperedProfile,&tamperedParsed,profileError,256);
    total++;passed+=test(gainField&&tamperRejected,"3.9.0 profiles: checksum rejects modified profile content");
    ProfileSnapshot invalidProfile=profileOriginal;invalidProfile.afPoints=8;total++;passed+=test(!ValidateProfileSnapshot(&invalidProfile,profileError,256),"3.9.0 profiles: invalid autofocus ranges are rejected");
    char excessiveCountProfile[65536];memcpy(excessiveCountProfile,profileJson,(SIZE_T)ALen(profileJson)+1);char* countField=strstr(excessiveCountProfile,"\"filterCount\":1");if(countField){countField+=14;countField[0]='9';countField[1]='9';countField[2]='9';countField[3]='9';countField[4]='9';countField[5]='9';}ProfileSnapshot excessiveParsed;BOOL excessiveRejected=!ParseProfileJson(excessiveCountProfile,&excessiveParsed,profileError,256);total++;passed+=test(countField&&excessiveRejected,"3.9.0 profiles: oversized collection counts are rejected before fixed arrays are accessed");
    ProfileSnapshot specialProfile=profileOriginal;CopyWBounded(specialProfile.cameraId,256,L"Camera \"gain\" detector");CopyWBounded(specialProfile.focuserId,256,L"Focuser \"filterCount\"");CopyWBounded(specialProfile.filters[0].name,32,L"Ha}band");char specialJson[65536];ProfileSnapshot specialParsed;BOOL specialRoundTrip=SerializeProfile(&specialProfile,specialJson,65536)&&ParseProfileJson(specialJson,&specialParsed,profileError,256);total++;passed+=test(specialRoundTrip&&WEquals(specialParsed.cameraId,specialProfile.cameraId)&&WEquals(specialParsed.focuserId,specialProfile.focuserId)&&WEquals(specialParsed.filters[0].name,L"Ha}band"),"3.9.0 profiles: quoted field names and braces inside strings round-trip safely");
    ProfileSnapshot invalidModel=profileOriginal;invalidModel.modelQualityMean=150.0;total++;passed+=test(!ValidateProfileSnapshot(&invalidModel,profileError,256),"3.9.0 profiles: implausible focus-model values are rejected");
    int safeMotor=25123,safeOptical=25001;g_simPosition=safeMotor;g_simOpticalPosition=safeOptical;g_cameraConnected=TRUE;g_focuserConnected=TRUE;CopyWBounded(g_cameraId,256,L"Connected.Camera");CopyWBounded(g_focuserId,256,L"Connected.Focuser");profileParsed.autoRefocus=TRUE;g_autoRefocusEnabled=TRUE;g_autoRefocusPaused=TRUE;g_autoRefocusFailureCount=5;g_autoRefocusRetryAfter=fakeNow+60000;g_refocusBadFrameStreak=4;int revisionBefore=g_profileRevision;ApplyProfileSnapshot(&profileParsed);
    total++;passed+=test(g_simPosition==safeMotor&&g_simOpticalPosition==safeOptical&&WEquals(g_cameraId,L"Connected.Camera")&&WEquals(g_focuserId,L"Connected.Focuser")&&!g_afActive&&!g_exposing,"3.9.0 profiles: loading never moves focus or replaces connected devices");
    total++;passed+=test(!g_autoRefocusPaused&&g_autoRefocusFailureCount==0&&g_autoRefocusRetryAfter==0&&g_refocusBadFrameStreak==0&&g_profileRevision!=revisionBefore,"3.9.0 profiles: loading resets stale auto-refocus lifecycle and advances UI revision");
    g_simFrameSequence=77;g_simRandomSeed=0x10203040U;g_simProfileSelectionSequence=0;g_simProfileMode=SIM_RANDOM;SelectSimulatorProfile();int seededA=g_simActiveProfile;SelectSimulatorProfile();int seededB=g_simActiveProfile;g_simRandomSeed=0x10203040U;g_simProfileSelectionSequence=0;SelectSimulatorProfile();int seededA2=g_simActiveProfile;SelectSimulatorProfile();int seededB2=g_simActiveProfile;
    total++;passed+=test(seededA==seededA2&&seededB==seededB2,"3.9.0 profiles: simulator seed reproduces random profile sequence");
    ResetFakeProfileStorage();g_appDir[0]=0;CopyWBounded(g_activeProfileName,96,L"Standardprofil");SetWindowTextW(g_profileEdit,L"Standardprofil");g_live=FALSE;g_exposing=FALSE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_backlashCalActive=FALSE;g_cachedFocuserMoving=FALSE;g_cameraConnected=FALSE;g_focuserConnected=FALSE;
    SetWindowTextW(g_gainEdit,L"333");wchar_t crudMessage[256];BOOL saveCrud=SaveNamedProfile(L"C8 Deep Sky",TRUE,crudMessage,256);int crudSlot=FindProfileSlot(L"C8 Deep Sky");SetWindowTextW(g_gainEdit,L"99");int beforeLoadMotor=g_simPosition,beforeLoadOptical=g_simOpticalPosition;BOOL loadCrud=LoadNamedProfile(L"C8 Deep Sky",crudMessage,256);wchar_t loadedGain[32];GetWindowTextW(g_gainEdit,loadedGain,32);
    total++;passed+=test(saveCrud&&crudSlot>0&&loadCrud&&WEquals(loadedGain,L"333")&&g_simPosition==beforeLoadMotor&&g_simOpticalPosition==beforeLoadOptical,"3.9.0 profiles: named save and load persist settings without movement");
    SetWindowTextW(g_gainEdit,L"444");BOOL overwriteCrud=SaveNamedProfile(L"C8 Deep Sky",FALSE,crudMessage,256);int overwrittenSlot=FindProfileSlot(L"C8 Deep Sky");SetWindowTextW(g_gainEdit,L"88");BOOL reloadOverwrite=LoadNamedProfile(L"C8 Deep Sky",crudMessage,256);GetWindowTextW(g_gainEdit,loadedGain,32);
    total++;passed+=test(overwriteCrud&&reloadOverwrite&&overwrittenSlot==crudSlot&&WEquals(loadedGain,L"444"),"3.9.0 profiles: overwrite reuses the existing slot and preserves the library index");
    BOOL exportCrud=ExportNamedProfile(L"C8 Deep Sky",L"ExportedProfile.afprofile.json",crudMessage,256);char* exportedText=0;DWORD exportedSize=0;BOOL exportedReadable=ReadWholeTextFile(L"ExportedProfile.afprofile.json",&exportedText,&exportedSize);if(exportedText)Free(exportedText);
    total++;passed+=test(exportCrud&&exportedReadable&&exportedSize>200,"3.9.0 profiles: export creates readable checked JSON");
    BOOL importCrud=ImportNamedProfile(L"ExportedProfile.afprofile.json",crudMessage,256);int importedSlot=FindProfileSlot(L"C8 Deep Sky (importiert)");
    total++;passed+=test(importCrud&&importedSlot>0&&importedSlot!=crudSlot,"3.9.0 profiles: duplicate import gets a unique name and stays unloaded");
    CopyWBounded(g_activeProfileName,96,L"C8 Deep Sky");BOOL standardProtected=!DeleteNamedProfile(L"Standardprofil",crudMessage,256);BOOL activeProtected=!DeleteNamedProfile(L"C8 Deep Sky",crudMessage,256);BOOL deleteImported=DeleteNamedProfile(L"C8 Deep Sky (importiert)",crudMessage,256)&&FindProfileSlot(L"C8 Deep Sky (importiert)")<0;
    total++;passed+=test(standardProtected&&activeProtected&&deleteImported,"3.9.0 profiles: protected and deletable profile rules work end-to-end");
    g_live=TRUE;BOOL busyLoadRejected=!LoadNamedProfile(L"C8 Deep Sky",crudMessage,256);total++;passed+=test(ProfileOperationBusy()&&busyLoadRejected,"3.9.0 profiles: loading is blocked during live capture");g_live=FALSE;

    ResetFakeProfileStorage();CopyWBounded(g_activeProfileName,96,L"Standardprofil");SetWindowTextW(g_profileEdit,L"Standardprofil");SetWindowTextW(g_gainEdit,L"555");WriteProfileSlotName(0,L"Standardprofil");EnsureProfileLibrary();ProfileSnapshot repairedStandard;BOOL repairedStandardOk=ReadProfileSlot(0,&repairedStandard,crudMessage,256);
    total++;passed+=test(repairedStandardOk&&WEquals(repairedStandard.name,L"Standardprofil")&&repairedStandard.gain==555,"3.9.0 profiles: missing standard-profile file is repaired at startup");

    // 3.6.1 runtime export validation: exercise the real CSV/SVG writer with the maximum
    // supported point count, positive sigma values and an explicit outlier. This catches
    // column drift, missing visible error bars/crosses and report buffer overruns under ASan.
    g_afPointCount=15;g_afBestPosition=24180;g_afStartPosition=23620;g_fitValid=TRUE;g_fitFwhmValid=TRUE;g_fitModel=AF_CURVE_TILTED_HYPERBOLA;g_fitFwhmModel=AF_CURVE_HYPERBOLA;g_fitCenterPosition=24180.0;g_fitScale=120.0;
    g_fitParams[0]=1.20;g_fitParams[1]=0.52;g_fitParams[2]=1.30;g_fitParams[3]=0.05;g_fitParams[4]=0.0;g_fitFwhmParams[0]=3.10;g_fitFwhmParams[1]=1.20;g_fitFwhmParams[2]=1.50;g_fitFwhmParams[3]=0.0;g_fitFwhmParams[4]=0.0;
    g_fitFocusSigma=17.5;g_fitFocusSigmaLoo=21.0;g_fitReducedChi2=1.25;g_fitR2=0.987;g_fitConfidence=0.91;g_fitInliers=14;g_fitOutliers=1;CopyWBounded(g_fitMethod,160,L"Geneigte Hyperbel / symmetrische Hyperbel");
    for(int i=0;i<15;i++){double x=(double)(i-7);g_afPositions[i]=24180+(i-7)*80;g_afMetrics[i]=1.20+0.08*(x<0.0?-x:x);g_afFwhmMetrics[i]=3.10+0.18*(x<0.0?-x:x);g_afMetricSigma[i]=0.025+0.002*(i%3);g_afFwhmSigma[i]=0.055+0.003*(i%4);g_afUsedMetrics[i]=40-i;g_afSamplesPerPoint[i]=2+(i%3);g_afResiduals[i]=0.1*(i-7);g_afOutliers[i]=(i==2);}
    BOOL reportOk=ExportReport(L"3.9.0 Laufzeittest");int reportCsv=FakeFindFileSuffix(L"AF_20260730_120000.csv"),reportSvg=FakeFindFileSuffix(L"AF_20260730_120000.svg");
    total++;passed+=test(reportOk&&reportCsv>=0&&reportSvg>=0&&fakeFiles[reportCsv].size<32768&&fakeFiles[reportSvg].size<65536,"3.9.0 report: maximum-size CSV/SVG exports safely");
    total++;passed+=test(FakeCsvFirstPointColumns(reportCsv)==10&&FakeFileContainsBytes(reportCsv,";0.02500;")&&FakeFileContainsBytes(reportCsv,";1\r\n"),"3.9.0 report: CSV rows match ten-column header and export sigma/outlier");
    total++;passed+=test(FakeFileContainsBytes(reportSvg,"fill-opacity='0.10'")&&FakeFileContainsBytes(reportSvg,"stroke='#ff6b77' stroke-width='2'")&&FakeFileContainsBytes(reportSvg,"stroke='#66dda3'")&&FakeFileContainsBytes(reportSvg,"stroke='#54a4ff'"),"3.9.0 report: SVG contains uncertainty band, error-bar colors and red outlier cross");

    total++;passed+=test(IsSafeAscomProgIdText(L"ASCOM.Celestron.Focuser")&&IsSafeAscomProgIdText(L"ASCOM.Simulator.Camera")&&!IsSafeAscomProgIdText(L"Synthetische Kamera")&&!IsSafeAscomProgIdText(L"ASCOM/Bad.Camera"),"3.9.0 ASCOM selection: ProgID validation rejects display names and unsafe paths");
    g_cameraConnected=FALSE;g_focuserConnected=FALSE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_backlashCalActive=FALSE;
    RunFakeHttp("GET /api/set?name=cameraId&value=ASCOM.Test.Camera HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL cameraIdAccepted=strstr(fakeNetResponse,"\"ok\":true")&&WEquals(g_cameraId,L"ASCOM.Test.Camera");
    RunFakeHttp("GET /api/set?name=focuserId&value=ASCOM.Test.Focuser HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL focuserIdAccepted=strstr(fakeNetResponse,"\"ok\":true")&&WEquals(g_focuserId,L"ASCOM.Test.Focuser");
    total++;passed+=test(cameraIdAccepted&&focuserIdAccepted,"3.9.0 ASCOM selection: chooser ProgIDs transfer through the engine API");
    g_cameraConnected=TRUE;RunFakeHttp("GET /api/set?name=cameraId&value=ASCOM.Other.Camera HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL liveSwapRejected=strstr(fakeNetResponse,"\"ok\":false")&&WEquals(g_cameraId,L"ASCOM.Test.Camera");g_cameraConnected=FALSE;
    total++;passed+=test(liveSwapRejected,"3.9.0 ASCOM selection: connected driver cannot be replaced live");


    // 3.9.0 ToupTek runtime path validation and API persistence.
    ResetFakeProfileStorage();FakeAllocFile(L"C:\\SDK\\toupcam.dll");
    total++;passed+=test(IsSafeToupTekDllPath(L"C:\\SDK\\toupcam.dll")&&!IsSafeToupTekDllPath(L"C:\\SDK\\other.dll")&&!IsSafeToupTekDllPath(L"toupcam.dll"),"3.9.0 ToupTek: only an existing absolute toupcam.dll path is accepted");
    g_cameraConnected=FALSE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_backlashCalActive=FALSE;
    RunFakeHttp("GET /api/set?name=touptekDllPath&value=C%3A%5CSDK%5Ctoupcam.dll HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL toupPathAccepted=strstr(fakeNetResponse,"\"ok\":true")&&strstr(fakeNetResponse,"SDK-Pfad")&&WEquals(g_toupTekDllPath,L"C:\\SDK\\toupcam.dll");
    total++;passed+=test(toupPathAccepted,"3.9.0 ToupTek: validated SDK path is persisted with a specific API response");
    g_cameraConnected=TRUE;RunFakeHttp("GET /api/set?name=touptekDllPath&value=C%3A%5CSDK%5Ctoupcam.dll HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    total++;passed+=test(strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"getrennter Kamera"),"3.9.0 ToupTek: SDK path cannot change while the camera is connected");g_cameraConnected=FALSE;

    // 3.9.0 integration regressions: device selection must never open modal ASCOM UI in the hidden engine.
    g_simulatorMode=FALSE;g_externalCameraMode=FALSE;SetChecked(g_nativeCheck,FALSE);g_cameraConnected=FALSE;g_focuserConnected=FALSE;
    RunFakeHttp("GET /api/action?name=camera-select HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL headlessCameraChooserBlocked=strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"sichtbaren Desktopoberfläche");
    RunFakeHttp("GET /api/action?name=focuser-select HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL headlessFocuserChooserBlocked=strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"sichtbaren Desktopoberfläche");
    total++;passed+=test(headlessCameraChooserBlocked&&headlessFocuserChooserBlocked,"3.9.0 integration: hidden engine never opens an ASCOM chooser");

    // Exercise the complete simulator action routes, including both transitions.
    g_simulatorMode=TRUE;g_cameraConnected=FALSE;g_focuserConnected=FALSE;
    RunFakeHttp("GET /api/action?name=camera-connect HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL simCameraOn=g_cameraConnected&&strstr(fakeNetResponse,"\"ok\":true")&&strstr(fakeNetResponse,"verbunden");
    RunFakeHttp("GET /api/action?name=focuser-connect HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL simFocuserOn=g_focuserConnected&&strstr(fakeNetResponse,"\"ok\":true")&&strstr(fakeNetResponse,"verbunden");
    RunFakeHttp("GET /api/action?name=focuser-connect HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL simFocuserOff=!g_focuserConnected&&strstr(fakeNetResponse,"\"ok\":true")&&strstr(fakeNetResponse,"getrennt");
    RunFakeHttp("GET /api/action?name=camera-connect HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL simCameraOff=!g_cameraConnected&&strstr(fakeNetResponse,"\"ok\":true")&&strstr(fakeNetResponse,"getrennt");
    total++;passed+=test(simCameraOn&&simFocuserOn&&simFocuserOff&&simCameraOff,"3.9.0 integration: simulator camera and focuser connect and disconnect through HTTP API");

    // A blocked ASCOM worker must return the concrete reason rather than a generic toggle error.
    g_simulatorMode=FALSE;g_focuserConnected=FALSE;g_focuserWorkerBlocked=TRUE;SetWindowTextW(g_focuserEdit,L"ASCOM.Test.Focuser");
    RunFakeHttp("GET /api/action?name=focuser-connect HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL detailedFocuserFailure=strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"blockiert")&&!strstr(fakeNetResponse,"konnte nicht umgeschaltet werden");
    g_focuserWorkerBlocked=FALSE;
    g_cameraConnected=FALSE;g_cameraWorkerBlocked=TRUE;SetChecked(g_nativeCheck,FALSE);SetWindowTextW(g_cameraEdit,L"ASCOM.Test.Camera");
    RunFakeHttp("GET /api/action?name=camera-connect HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
    BOOL detailedCameraFailure=strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"blockiert")&&!strstr(fakeNetResponse,"konnte nicht umgeschaltet werden");
    g_cameraWorkerBlocked=FALSE;
    total++;passed+=test(detailedFocuserFailure&&detailedCameraFailure,"3.9.0 integration: device worker failures preserve their concrete API reason");

    // 3.9.0 maintenance revision: atomically reserve the focuser setup window in the engine.
    g_simulatorMode=FALSE;g_focuserConnected=FALSE;g_focuserWorker=0;g_focuserWorkerBlocked=FALSE;g_afActive=FALSE;g_stepAssistActive=FALSE;g_backlashCalActive=FALSE;g_cachedFocuserMoving=FALSE;g_focuserRuntime.phase=DEV_DISCONNECTED;g_focuserSetupReserved=FALSE;
    RunFakeHttp("GET /api/action?name=focuser-setup-begin HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL setupReserved=g_focuserSetupReserved&&strstr(fakeNetResponse,"\"ok\":true");
    RunFakeHttp("GET /api/action?name=move-out HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL setupMoveBlocked=g_focuserSetupReserved&&strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"Treiberdialogs gesperrt");
    RunFakeHttp("GET /api/action?name=focuser-connect HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL setupConnectBlocked=!g_focuserConnected&&strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"Treiberdialogs gesperrt");
    RunFakeHttp("GET /api/set?name=focuserId&value=ASCOM.Other.Focuser HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL setupDriverSwapBlocked=strstr(fakeNetResponse,"\"ok\":false")!=0;
    RunFakeHttp("GET /api/status HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL setupStatusVisible=strstr(fakeNetResponse,"\"focuserSetupActive\":true")!=0;
    RunFakeHttp("GET /api/action?name=focuser-setup-end HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL setupReleased=!g_focuserSetupReserved&&strstr(fakeNetResponse,"\"ok\":true");
    total++;passed+=test(setupReserved&&setupMoveBlocked&&setupConnectBlocked&&setupDriverSwapBlocked&&setupStatusVisible&&setupReleased,"3.9.0 revision: engine setup reservation atomically blocks all focuser changes");

    g_focuserRuntime.phase=DEV_FAULTED;char setupMessage[128];BOOL faultedSetupRejected=!BeginFocuserSetupReservation(setupMessage,128)&&!g_focuserSetupReserved;g_focuserRuntime.phase=DEV_DISCONNECTED;g_focuserWorkerBlocked=TRUE;BOOL blockedWorkerRejected=!BeginFocuserSetupReservation(setupMessage,128)&&!g_focuserSetupReserved;g_focuserWorkerBlocked=FALSE;g_focuserWanted=TRUE;BOOL wantedSetupRejected=!BeginFocuserSetupReservation(setupMessage,128)&&!g_focuserSetupReserved;g_focuserWanted=FALSE;
    total++;passed+=test(faultedSetupRejected&&blockedWorkerRejected&&wantedSetupRejected,"3.9.0 revision: setup requires a clean fully disconnected and unwanted worker state");

    g_focuserSetupReserved=TRUE;DeviceWorker* workerBeforeSetupGuard=g_focuserWorker;BOOL directWorkerBlocked=!ConnectAscomFocuserWorker(FALSE)&&g_focuserWorker==workerBeforeSetupGuard;g_focuserSetupReserved=FALSE;
    total++;passed+=test(directWorkerBlocked,"3.9.0 revision: direct ASCOM focuser worker creation is blocked during setup reservation");

    RunFakeHttp("GET /api/action?name=focuser-setup-begin&name=focuser-setup-end HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL duplicateActionRejected=!g_focuserSetupReserved&&strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"Doppelte Abfrageparameter");
    RunFakeHttp("GET /api/set?name=manualStep&value=10&value=20 HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL duplicateValueRejected=strstr(fakeNetResponse,"\"ok\":false")&&strstr(fakeNetResponse,"Doppelte Abfrageparameter");
    BOOL exactDuplicateDetection=QueryHasDuplicateKeys("GET /api/action?name=live&name=shutdown HTTP/1.1")&&!QueryHasDuplicateKeys("GET /api/action?xname=live&name=shutdown HTTP/1.1");
    total++;passed+=test(duplicateActionRejected&&duplicateValueRejected&&exactDuplicateDetection,"3.9.0 revision: duplicate mutation parameters are rejected without ambiguity");

    // Continuous-focus integration: no motor command is allowed during an active
    // exposure, stable regular frames establish a reference, a bounded inter-frame
    // probe is made, and only improved verification frames accept that correction.
    g_simulatorMode=TRUE;g_cameraConnected=TRUE;g_focuserConnected=TRUE;g_cameraWorkerBlocked=FALSE;g_focuserWorkerBlocked=FALSE;g_focuserSetupReserved=FALSE;
    g_afActive=FALSE;g_stepAssistActive=FALSE;g_backlashCalActive=FALSE;g_live=TRUE;g_exposing=FALSE;g_capturePurpose=0;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;
    g_simBacklashSteps=0;g_simBacklashRemaining=0;g_simLastDirection=0;g_simPosition=g_simBestFocus+240;g_simOpticalPosition=g_simPosition;SetChecked(g_preferredDirCheck,TRUE);
    g_continuousFocusEnabled=TRUE;g_continuousFocusFallback=FALSE;g_continuousFocusPaused=FALSE;g_continuousFocusMode=CF_IMAGE;g_continuousFocusMinFrames=3;g_continuousFocusDeadband=3;g_continuousFocusMaxStep=12;g_continuousFocusMinConfidence=50;g_continuousFocusMinImprovement=1.0;g_continuousFocusSettleMs=100;
    g_refocusMinStars=4;g_refocusStabilityLimit=0.45;g_trendCount=0;g_usedCount=12;g_medianSnr=40.0;g_medianFwhm=3.0;g_medianHfr=1.5;ContinuousFocusResetReference(L"Integrationstest");
    int cfExposurePosition=g_simPosition;g_exposing=TRUE;BOOL cfExposureBlocked=!ContinuousFocusBeginMove(cfExposurePosition+5,CF_MOVE_IMAGE_PROBE,L"muss blockiert werden")&&g_simPosition==cfExposurePosition&&g_continuousFocusPhase==CF_IDLE;g_exposing=FALSE;
    for(int i=0;i<3;i++)ContinuousFocusOnLiveFrame();BOOL cfReferenceReady=g_continuousFocusReferenceMetric>0.0&&g_continuousFocusPhase==CF_IDLE;
    g_medianFwhm=4.8;g_medianHfr=2.4;int cfProbeOrigin=g_simPosition;BOOL cfHeld=FALSE;for(int i=0;i<3;i++)cfHeld=ContinuousFocusOnLiveFrame()||cfHeld;int cfProbeDelta=g_simPosition-cfProbeOrigin;if(cfProbeDelta<0)cfProbeDelta=-cfProbeDelta;BOOL cfProbeBounded=cfHeld&&g_continuousFocusPhase==CF_MOVING&&cfProbeDelta>=g_continuousFocusDeadband&&cfProbeDelta<=g_continuousFocusMaxStep;
    ContinuousFocusTick(fakeNow+1000);ContinuousFocusTick(fakeNow+2500);g_exposing=FALSE;g_capturePurpose=0;g_medianFwhm=2.9;g_medianHfr=1.45;for(int i=0;i<3;i++)ContinuousFocusOnLiveFrame();BOOL cfAccepted=g_continuousFocusPhase==CF_IDLE&&g_continuousFocusAccepted==1&&g_continuousFocusRejected==0&&g_continuousFocusEstimatedError==0.0;
    total++;passed+=test(cfExposureBlocked&&cfReferenceReady&&cfProbeBounded&&cfAccepted,"3.9.0 continuous focus: corrections occur only between exposures and require improved verification");
    RunFakeHttp("GET /api/status HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL cfStatusFields=strstr(fakeNetResponse,"\"continuousFocusEnabled\":true")&&strstr(fakeNetResponse,"\"continuousFocusState\"")&&strstr(fakeNetResponse,"\"continuousFocusEstimatedError\"")&&strstr(fakeNetResponse,"\"continuousFocusDriftStepsPerMinute\"");
    total++;passed+=test(cfStatusFields,"3.9.0 continuous focus: status exposes control state and diagnostics");
    g_continuousFocusEnabled=FALSE;g_continuousFocusPaused=FALSE;g_continuousFocusPhase=CF_IDLE;g_continuousFocusMoveKind=CF_MOVE_NONE;g_continuousFocusFallbackPending=FALSE;g_continuousFocusReferenceMetric=0.0;g_continuousFocusAccepted=0;g_continuousFocusRejected=0;g_live=FALSE;g_exposing=FALSE;ContinuousFocusClearSamples();

    SetWindowTextW(g_refocusMinutesEdit,L"0");SetWindowTextW(g_refocusTempEdit,L"0");RunFakeHttp("GET /api/status HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");BOOL statusFields=strstr(fakeNetResponse,"\"version\":\"3.9.0\"")&&strstr(fakeNetResponse,"\"focuserSetupActive\":false")&&strstr(fakeNetResponse,"\"autoRefocusReferenceReady\"")&&strstr(fakeNetResponse,"\"autoRefocusReferenceFwhm\"")&&strstr(fakeNetResponse,"\"autoRefocusPaused\"")&&strstr(fakeNetResponse,"\"autoRefocusTimeEnabled\":false")&&strstr(fakeNetResponse,"\"autoRefocusTemperatureEnabled\":false")&&strstr(fakeNetResponse,"\"autoRefocusNextMinutes\":-1.000")&&strstr(fakeNetResponse,"\"refocusFwhmPercent\"")&&strstr(fakeNetResponse,"\"refocusBadFrames\"")&&strstr(fakeNetResponse,"\"refocusMinStars\"")&&strstr(fakeNetResponse,"\"refocusStability\"")&&strstr(fakeNetResponse,"\"refocusCooldown\"")&&strstr(fakeNetResponse,"\"cameraWorkerBlocked\"")&&strstr(fakeNetResponse,"\"focuserWorkerBlocked\"")&&strstr(fakeNetResponse,"\"autofocusErrorCode\"")&&strstr(fakeNetResponse,"\"autofocusErrorDetail\"")&&strstr(fakeNetResponse,"\"seeingIndex\"")&&strstr(fakeNetResponse,"\"focusNeedScore\"")&&strstr(fakeNetResponse,"\"afQualityScore\"")&&strstr(fakeNetResponse,"\"fieldCurvature\"")&&strstr(fakeNetResponse,"\"profileModelValid\"")&&strstr(fakeNetResponse,"\"tempCompEnabled\"")&&strstr(fakeNetResponse,"\"backlashCalibrationEstimated\"")&&strstr(fakeNetResponse,"\"stepAssistantActive\"")&&strstr(fakeNetResponse,"\"filterOffsetCount\"")&&strstr(fakeNetResponse,"\"refocusEveryCaptures\"")&&strstr(fakeNetResponse,"\"simProfileMode\"")&&strstr(fakeNetResponse,"\"simProfileName\"")&&strstr(fakeNetResponse,"\"simBacklashSteps\"")&&strstr(fakeNetResponse,"\"backlashCalibrationProgress\"")&&strstr(fakeNetResponse,"\"profileRevision\"")&&strstr(fakeNetResponse,"\"continuousFocusEnabled\"")&&strstr(fakeNetResponse,"\"continuousFocusMode\"")&&strstr(fakeNetResponse,"\"continuousFocusState\"")&&strstr(fakeNetResponse,"\"continuousFocusTarget\"");total++;passed+=test(statusFields,"Actual core: status exposes auto-refocus, continuous tracking, device workers and focus intelligence");
    const char* deceptiveQuery="GET /api/action?xname=shutdown&name=live&xvalue=999&value=42&noname=bad HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n";
    total++;passed+=test(QueryValueEquals(deceptiveQuery,"name=","live")&&!QueryValueEquals(deceptiveQuery,"name=","shutdown"),"3.9.0 API: query names match only at parameter boundaries");
    total++;passed+=test(QueryInt(deceptiveQuery,"value=",-1)==42,"3.9.0 API: integer query ignores key substrings");
    wchar_t exactQueryText[32];QueryText(deceptiveQuery,"name=",exactQueryText,32);
    total++;passed+=test(FakeWEq(exactQueryText,L"live")&&QueryHas(deceptiveQuery,"name=")&&!QueryHas(deceptiveQuery,"missing="),"3.9.0 API: text and presence queries use exact parameters");
    wchar_t rejectedText[16];QueryText("GET /api/set?name=focuserId&value=ASCOM.Good%00Hidden HTTP/1.1","value=",rejectedText,16);
    total++;passed+=test(rejectedText[0]==0,"3.9.0 API: percent-encoded NUL is rejected instead of truncated");
    QueryText("GET /api/set?name=profile&value=Good%0dInjected HTTP/1.1","value=",rejectedText,16);
    total++;passed+=test(rejectedText[0]==0,"3.9.0 API: encoded control characters are rejected");
    QueryText("GET /api/set?name=profile&value=ThisValueIsFarTooLong HTTP/1.1","value=",rejectedText,8);
    total++;passed+=test(rejectedText[0]==0,"3.9.0 API: overlong text is rejected instead of silently shortened");
    QueryText("GET /api/set?name=profile&value=Bad%GGValue HTTP/1.1","value=",rejectedText,16);
    total++;passed+=test(rejectedText[0]==0,"3.9.0 API: malformed percent escapes are rejected");
    QueryText("GET /api/set?name=profile&value=Bad% HTTP/1.1","value=",rejectedText,16);
    total++;passed+=test(rejectedText[0]==0,"3.9.0 API: incomplete percent escapes are rejected");
    QueryText("GET /api/set?name=profile&value=%C0%AF HTTP/1.1","value=",rejectedText,16);
    total++;passed+=test(rejectedText[0]==0,"3.9.0 API: overlong UTF-8 encodings are rejected");
    QueryText("GET /api/set?name=profile&value=%E2%82 HTTP/1.1","value=",rejectedText,16);
    total++;passed+=test(rejectedText[0]==0,"3.9.0 API: truncated UTF-8 sequences are rejected");
    printf("SUMMARY %d/%d\n",passed,total);return passed==total?0:1;
}
