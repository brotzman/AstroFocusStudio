// AstroFocus Studio 3.8.8 - isolated ASCOM chooser and focuser setup helper.
// Default mode opens the selected focuser SetupDialog. With --choose it opens
// the ASCOM Chooser in a visible foreground child process and writes the selected
// ProgID to a caller-supplied UTF-16 result file.

extern "C" void __security_init_cookie();
extern "C" {
int _fltused=0;
typedef unsigned char BYTE; typedef unsigned short WORD; typedef unsigned int UINT; typedef unsigned long DWORD; typedef long LONG; typedef unsigned long ULONG; typedef long HRESULT; typedef int BOOL; typedef unsigned long long ULONG_PTR; typedef long long LONG_PTR; typedef unsigned long long SIZE_T; typedef unsigned short VARTYPE; typedef short VARIANT_BOOL; typedef wchar_t* BSTR; typedef wchar_t* LPOLESTR; typedef unsigned long LCID; typedef void* HANDLE; typedef HANDLE HMODULE; typedef HANDLE HWND; typedef void* LPVOID; typedef const void* LPCVOID; typedef const wchar_t* LPCWSTR; typedef wchar_t* LPWSTR;
#ifdef _MSC_VER
#define WINAPI __stdcall
#define STDMETHODCALLTYPE __stdcall
#else
#define WINAPI __attribute__((stdcall))
#define STDMETHODCALLTYPE __attribute__((stdcall))
#endif
#define TRUE 1
#define FALSE 0
#define NULL 0
#define SUCCEEDED(hr) ((HRESULT)(hr)>=0)
#define FAILED(hr) ((HRESULT)(hr)<0)

struct GUID{DWORD Data1;WORD Data2,Data3;BYTE Data4[8];}; typedef const GUID& REFIID; typedef GUID CLSID;
struct IDispatch;
struct VARIANT{VARTYPE vt;WORD wReserved1,wReserved2,wReserved3;union{LONG lVal;double dblVal;VARIANT_BOOL boolVal;BSTR bstrVal;IDispatch* pdispVal;void* byref;struct{void* pvRecord;void* pRecInfo;}record;}data;}; typedef VARIANT VARIANTARG;
struct DISPPARAMS{VARIANTARG* rgvarg;LONG* rgdispidNamedArgs;UINT cArgs,cNamedArgs;};
static_assert(sizeof(void*)!=8||sizeof(VARIANT)==24,"Windows x64 VARIANT ABI mismatch");
static_assert(sizeof(void*)!=8||sizeof(DISPPARAMS)==24,"Windows x64 DISPPARAMS ABI mismatch");
struct EXCEPINFO{WORD wCode,wReserved;BSTR bstrSource,bstrDescription,bstrHelpFile;DWORD dwHelpContext;void* pvReserved;HRESULT (STDMETHODCALLTYPE *pfnDeferredFillIn)(EXCEPINFO*);HRESULT scode;};
struct IDispatchVtbl{HRESULT (STDMETHODCALLTYPE *QueryInterface)(IDispatch*,REFIID,void**);ULONG (STDMETHODCALLTYPE *AddRef)(IDispatch*);ULONG (STDMETHODCALLTYPE *Release)(IDispatch*);HRESULT (STDMETHODCALLTYPE *GetTypeInfoCount)(IDispatch*,UINT*);HRESULT (STDMETHODCALLTYPE *GetTypeInfo)(IDispatch*,UINT,LCID,void**);HRESULT (STDMETHODCALLTYPE *GetIDsOfNames)(IDispatch*,REFIID,LPOLESTR*,UINT,LCID,LONG*);HRESULT (STDMETHODCALLTYPE *Invoke)(IDispatch*,LONG,REFIID,LCID,WORD,DISPPARAMS*,VARIANT*,EXCEPINFO*,UINT*);};
struct IDispatch{IDispatchVtbl* lpVtbl;};

HMODULE WINAPI GetModuleHandleW(LPCWSTR); void WINAPI ExitProcess(UINT); DWORD WINAPI GetModuleFileNameW(HMODULE,LPWSTR,DWORD); LPCWSTR WINAPI GetCommandLineW(void); int WINAPI lstrlenW(LPCWSTR); LPWSTR WINAPI lstrcpyW(LPWSTR,LPCWSTR); HANDLE WINAPI CreateFileW(LPCWSTR,DWORD,DWORD,void*,DWORD,DWORD,HANDLE); BOOL WINAPI ReadFile(HANDLE,LPVOID,DWORD,DWORD*,LPVOID); BOOL WINAPI WriteFile(HANDLE,LPCVOID,DWORD,DWORD*,LPVOID); DWORD WINAPI GetFileSize(HANDLE,DWORD*); BOOL WINAPI CloseHandle(HANDLE);
int WINAPI MessageBoxW(HWND,LPCWSTR,LPCWSTR,UINT); int WINAPI wsprintfW(LPWSTR,LPCWSTR,...);
HRESULT WINAPI CoInitializeEx(LPVOID,DWORD); void WINAPI CoUninitialize(void); HRESULT WINAPI CLSIDFromProgID(LPCWSTR,CLSID*); HRESULT WINAPI CoCreateInstance(REFIID,void*,DWORD,REFIID,void**);
BSTR WINAPI SysAllocString(LPCWSTR); void WINAPI SysFreeString(BSTR); void WINAPI VariantInit(VARIANT*); HRESULT WINAPI VariantClear(VARIANT*);
void* memset(void*,int,SIZE_T); void* memcpy(void*,const void*,SIZE_T);
}

#define GENERIC_READ 0x80000000UL
#define GENERIC_WRITE 0x40000000UL
#define FILE_SHARE_READ 0x00000001UL
#define OPEN_EXISTING 3
#define CREATE_ALWAYS 2
#define FILE_ATTRIBUTE_NORMAL 0x80
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define MB_OK 0x00000000L
#define MB_ICONERROR 0x00000010L
#define MB_ICONINFORMATION 0x00000040L
#define COINIT_APARTMENTTHREADED 0x2
#define CLSCTX_INPROC_SERVER 0x1
#define CLSCTX_LOCAL_SERVER 0x4
#define DISPATCH_METHOD 0x1
#define DISPATCH_PROPERTYPUT 0x4
#define DISPID_PROPERTYPUT ((LONG)-3)
#define LOCALE_USER_DEFAULT 0x0400
#define VT_BSTR 8

static const GUID IID_NULL_GUID={0,0,0,{0,0,0,0,0,0,0,0}};
static const GUID IID_IDispatch_GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

static BOOL WEqual(LPCWSTR a,LPCWSTR b){if(!a||!b)return FALSE;while(*a&&*b&&*a==*b){a++;b++;}return *a==*b;}
static BOOL IsSpace(wchar_t c){return c==L' '||c==L'\t'||c==L'\r'||c==L'\n';}
static BOOL IsTokenBoundary(wchar_t c){return c==0||IsSpace(c);}
static BOOL LooksLikeAscomProgId(LPCWSTR value){if(!value||!value[0])return FALSE;BOOL dot=FALSE;int n=0;for(;value[n];n++){wchar_t c=value[n];if(n>=255||c<=L' '||c==L'\\'||c==L'/'||c==L'"'||c==L'?'||c==L'#'||c==L'&')return FALSE;if(c==L'.')dot=TRUE;}return n>=3&&dot;}
static BOOL GetArgValue(LPCWSTR cmd,LPCWSTR key,LPWSTR out,int cap){
    if(!cmd||!key||!out||cap<2)return FALSE;out[0]=0;int keyLen=lstrlenW(key);
    for(int i=0;cmd[i];i++){
        if(i>0&&!IsSpace(cmd[i-1]))continue;int j=0;while(j<keyLen&&cmd[i+j]==key[j])j++;if(j!=keyLen||!IsTokenBoundary(cmd[i+j]))continue;
        int p=i+j;while(IsSpace(cmd[p]))p++;BOOL quoted=cmd[p]==L'"';if(quoted)p++;int o=0;
        while(cmd[p]&&o<cap-1){if(quoted){if(cmd[p]==L'"')break;}else if(IsSpace(cmd[p]))break;out[o++]=cmd[p++];}
        BOOL complete=quoted?cmd[p]==L'"':IsTokenBoundary(cmd[p]);out[o]=0;return complete&&out[0]!=0;
    }
    return FALSE;
}
static BOOL HasArg(LPCWSTR cmd,LPCWSTR key){wchar_t value[8];if(GetArgValue(cmd,key,value,8))return TRUE;int k=lstrlenW(key);for(int i=0;cmd&&cmd[i];i++){if(i>0&&!IsSpace(cmd[i-1]))continue;int j=0;while(j<k&&cmd[i+j]==key[j])j++;if(j==k&&IsTokenBoundary(cmd[i+j]))return TRUE;}return FALSE;}
static void ShowHr(LPCWSTR action,HRESULT hr,LPCWSTR title){wchar_t text[700];wsprintfW(text,L"%s ist fehlgeschlagen.\r\n\r\nHRESULT: 0x%08X\r\n\r\nPrüfe, ob die ASCOM Platform und der benötigte Treiber vollständig installiert sind.",action,(UINT)hr);MessageBoxW(0,text,title,MB_OK|MB_ICONERROR);}
static void ClearEx(EXCEPINFO* ex){if(ex->bstrSource)SysFreeString(ex->bstrSource);if(ex->bstrDescription)SysFreeString(ex->bstrDescription);if(ex->bstrHelpFile)SysFreeString(ex->bstrHelpFile);}
static HRESULT DispId(IDispatch* obj,LPCWSTR name,LONG* id){if(!obj||!obj->lpVtbl||!obj->lpVtbl->GetIDsOfNames)return (HRESULT)0x80004003L;LPOLESTR names[1];names[0]=(LPOLESTR)name;return obj->lpVtbl->GetIDsOfNames(obj,IID_NULL_GUID,names,1,LOCALE_USER_DEFAULT,id);}
static HRESULT Invoke(IDispatch* obj,LPCWSTR name,WORD flags,VARIANTARG* args,UINT argCount,LONG* named,UINT namedCount,VARIANT* result){
    if(!obj||!obj->lpVtbl||!obj->lpVtbl->Invoke)return (HRESULT)0x80004003L;LONG id=0;HRESULT hr=DispId(obj,name,&id);if(FAILED(hr))return hr;DISPPARAMS dp;dp.rgvarg=args;dp.rgdispidNamedArgs=named;dp.cArgs=argCount;dp.cNamedArgs=namedCount;EXCEPINFO ex;memset(&ex,0,sizeof(ex));UINT argErr=0;if(result)VariantInit(result);hr=obj->lpVtbl->Invoke(obj,id,IID_NULL_GUID,LOCALE_USER_DEFAULT,flags,&dp,result,&ex,&argErr);ClearEx(&ex);return hr;
}
static HRESULT SetBstrProp(IDispatch* obj,LPCWSTR name,LPCWSTR value){VARIANT a;VariantInit(&a);a.vt=VT_BSTR;a.data.bstrVal=SysAllocString(value);if(!a.data.bstrVal)return (HRESULT)0x8007000EL;LONG named=DISPID_PROPERTYPUT;HRESULT hr=Invoke(obj,name,DISPATCH_PROPERTYPUT,&a,1,&named,1,0);SysFreeString(a.data.bstrVal);return hr;}
static HRESULT CallChoose(IDispatch* chooser,LPCWSTR current,VARIANT* result){VARIANT a;VariantInit(&a);a.vt=VT_BSTR;a.data.bstrVal=SysAllocString(current?current:L"");if(!a.data.bstrVal)return (HRESULT)0x8007000EL;HRESULT hr=Invoke(chooser,L"Choose",DISPATCH_METHOD,&a,1,0,0,result);SysFreeString(a.data.bstrVal);return hr;}

static BOOL WriteUtf16Result(LPCWSTR path,LPCWSTR value){
    if(!path||!path[0]||!value||!value[0])return FALSE;HANDLE f=CreateFileW(path,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return FALSE;
    WORD bom=0xFEFF;DWORD written=0;BOOL ok=WriteFile(f,&bom,sizeof(bom),&written,0)&&written==sizeof(bom);DWORD bytes=(DWORD)(lstrlenW(value)*sizeof(wchar_t));written=0;if(ok)ok=WriteFile(f,value,bytes,&written,0)&&written==bytes;CloseHandle(f);return ok;
}
static UINT RunChooserMode(LPCWSTR cmd){
    wchar_t device[32],resultPath[700],initial[512];initial[0]=0;
    if(!GetArgValue(cmd,L"--device",device,32)||!GetArgValue(cmd,L"--result",resultPath,700)){MessageBoxW(0,L"Der ASCOM-Auswahlhelfer wurde ohne gültige Geräteart oder Ergebnisdatei gestartet.",L"AstroFocus ASCOM-Auswahl",MB_OK|MB_ICONERROR);return 20;}
    (void)GetArgValue(cmd,L"--initial",initial,512);BOOL camera=WEqual(device,L"Camera"),focuser=WEqual(device,L"Focuser");if(!camera&&!focuser){MessageBoxW(0,L"Unbekannte ASCOM-Geräteart.",L"AstroFocus ASCOM-Auswahl",MB_OK|MB_ICONERROR);return 20;}
    HRESULT hr=CoInitializeEx(0,COINIT_APARTMENTTHREADED);if(FAILED(hr)){ShowHr(L"Die COM-/ASCOM-Initialisierung",hr,L"AstroFocus ASCOM-Auswahl");return 21;}
    CLSID clsid;hr=CLSIDFromProgID(L"ASCOM.Utilities.Chooser",&clsid);if(FAILED(hr)){ShowHr(L"Das Laden des ASCOM-Auswahldialogs",hr,L"AstroFocus ASCOM-Auswahl");CoUninitialize();return 22;}
    IDispatch* chooser=0;hr=CoCreateInstance(clsid,0,CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER,IID_IDispatch_GUID,(void**)&chooser);if(FAILED(hr)||!chooser||!chooser->lpVtbl||!chooser->lpVtbl->Release){if(chooser&&chooser->lpVtbl&&chooser->lpVtbl->Release)chooser->lpVtbl->Release(chooser);ShowHr(L"Das Starten des ASCOM-Auswahldialogs",FAILED(hr)?hr:(HRESULT)0x80004003L,L"AstroFocus ASCOM-Auswahl");CoUninitialize();return 23;}
    hr=SetBstrProp(chooser,L"DeviceType",camera?L"Camera":L"Focuser");if(FAILED(hr)){chooser->lpVtbl->Release(chooser);ShowHr(L"Das Festlegen der ASCOM-Geräteart",hr,L"AstroFocus ASCOM-Auswahl");CoUninitialize();return 24;}
    VARIANT selected;VariantInit(&selected);hr=CallChoose(chooser,initial,&selected);chooser->lpVtbl->Release(chooser);if(FAILED(hr)){VariantClear(&selected);ShowHr(L"Die ASCOM-Treiberauswahl",hr,L"AstroFocus ASCOM-Auswahl");CoUninitialize();return 25;}
    BOOL hasSelection=selected.vt==VT_BSTR&&selected.data.bstrVal&&LooksLikeAscomProgId(selected.data.bstrVal);if(!hasSelection){VariantClear(&selected);CoUninitialize();return 10;}
    BOOL written=WriteUtf16Result(resultPath,selected.data.bstrVal);VariantClear(&selected);CoUninitialize();if(!written){MessageBoxW(0,L"Die ausgewählte ASCOM-Treiber-ID konnte nicht sicher an AstroFocus Studio zurückgegeben werden.",L"AstroFocus ASCOM-Auswahl",MB_OK|MB_ICONERROR);return 26;}return 0;
}

static BOOL CopyWideBounded(LPWSTR out,int cap,LPCWSTR value){
    if(!out||cap<2||!value)return FALSE;int i=0;for(;value[i]&&i<cap-1;i++)out[i]=value[i];out[i]=0;return value[i]==0&&i>0;
}
static int ChooseFocuserForSetup(LPWSTR out,int cap){
    CLSID chooserClsid;HRESULT hr=CLSIDFromProgID(L"ASCOM.Utilities.Chooser",&chooserClsid);if(FAILED(hr)){ShowHr(L"Das Laden des ASCOM-Auswahldialogs",hr,L"AstroFocus Fokussierer-Kalibrierung");return 22;}
    IDispatch* chooser=0;hr=CoCreateInstance(chooserClsid,0,CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER,IID_IDispatch_GUID,(void**)&chooser);if(FAILED(hr)||!chooser||!chooser->lpVtbl||!chooser->lpVtbl->Release){if(chooser&&chooser->lpVtbl&&chooser->lpVtbl->Release)chooser->lpVtbl->Release(chooser);ShowHr(L"Das Starten des ASCOM-Auswahldialogs",FAILED(hr)?hr:(HRESULT)0x80004003L,L"AstroFocus Fokussierer-Kalibrierung");return 23;}
    hr=SetBstrProp(chooser,L"DeviceType",L"Focuser");if(FAILED(hr)){chooser->lpVtbl->Release(chooser);ShowHr(L"Das Festlegen der ASCOM-Geräteart",hr,L"AstroFocus Fokussierer-Kalibrierung");return 24;}
    VARIANT selected;VariantInit(&selected);hr=CallChoose(chooser,L"",&selected);chooser->lpVtbl->Release(chooser);if(FAILED(hr)){VariantClear(&selected);ShowHr(L"Die ASCOM-Treiberauswahl",hr,L"AstroFocus Fokussierer-Kalibrierung");return 25;}
    if(selected.vt!=VT_BSTR||!selected.data.bstrVal||!selected.data.bstrVal[0]){VariantClear(&selected);return 10;}
    BOOL copied=LooksLikeAscomProgId(selected.data.bstrVal)&&CopyWideBounded(out,cap,selected.data.bstrVal);VariantClear(&selected);if(!copied){MessageBoxW(0,L"Die ausgewählte ASCOM-Treiber-ID ist zu lang oder ungültig.",L"AstroFocus Fokussierer-Kalibrierung",MB_OK|MB_ICONERROR);return 26;}return 0;
}
static UINT RunSetupMode(LPCWSTR cmd){
    wchar_t progId[512];progId[0]=0;(void)GetArgValue(cmd,L"--driver",progId,512);
    HRESULT hr=CoInitializeEx(0,COINIT_APARTMENTTHREADED);if(FAILED(hr)){ShowHr(L"Die COM-/ASCOM-Initialisierung",hr,L"AstroFocus Fokussierer-Kalibrierung");return 3;}
    if(!progId[0]){int choose=ChooseFocuserForSetup(progId,512);if(choose!=0){CoUninitialize();return (UINT)choose;}}
    if(!LooksLikeAscomProgId(progId)){MessageBoxW(0,L"Die ASCOM-Treiber-ID ist ungültig.",L"AstroFocus Fokussierer-Kalibrierung",MB_OK|MB_ICONERROR);CoUninitialize();return 4;}
    CLSID clsid;hr=CLSIDFromProgID(progId,&clsid);if(FAILED(hr)){ShowHr(L"Das Laden des ausgewählten ASCOM-Treibers",hr,L"AstroFocus Fokussierer-Kalibrierung");CoUninitialize();return 4;}
    IDispatch* focuser=0;hr=CoCreateInstance(clsid,0,CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER,IID_IDispatch_GUID,(void**)&focuser);if(FAILED(hr)||!focuser){ShowHr(L"Das Starten des ausgewählten ASCOM-Treibers",hr,L"AstroFocus Fokussierer-Kalibrierung");CoUninitialize();return 5;}
    IDispatchVtbl* vtbl=focuser->lpVtbl;if(!vtbl||!vtbl->GetIDsOfNames||!vtbl->Invoke||!vtbl->Release){if(vtbl&&vtbl->Release)vtbl->Release(focuser);ShowHr(L"Die ASCOM-Treiberschnittstelle",(HRESULT)0x80004003L,L"AstroFocus Fokussierer-Kalibrierung");CoUninitialize();return 5;}
    LONG id=0;LPOLESTR names[1];names[0]=(LPOLESTR)L"SetupDialog";hr=vtbl->GetIDsOfNames(focuser,IID_NULL_GUID,names,1,LOCALE_USER_DEFAULT,&id);
    if(SUCCEEDED(hr)){DISPPARAMS dp;memset(&dp,0,sizeof(dp));EXCEPINFO ex;memset(&ex,0,sizeof(ex));UINT argErr=0;hr=vtbl->Invoke(focuser,id,IID_NULL_GUID,LOCALE_USER_DEFAULT,DISPATCH_METHOD,&dp,0,&ex,&argErr);ClearEx(&ex);}
    vtbl->Release(focuser);CoUninitialize();if(FAILED(hr)){ShowHr(L"Das Öffnen der Treibereinstellungen (SetupDialog)",hr,L"AstroFocus Fokussierer-Kalibrierung");return 6;}return 0;
}

extern "C" void WinMainCRTStartup(){__security_init_cookie();LPCWSTR cmd=GetCommandLineW();UINT code=HasArg(cmd,L"--choose")?RunChooserMode(cmd):RunSetupMode(cmd);ExitProcess(code);}
