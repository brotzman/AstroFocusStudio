// AstroFocus Studio 3.9.0 isolated ASCOM device host.
// Built twice as AstroFocusCameraHost.exe and AstroFocusFocuserHost.exe.

extern "C" {
int _fltused=0;
typedef unsigned char BYTE; typedef unsigned short WORD; typedef unsigned int UINT; typedef unsigned long DWORD;
typedef long LONG; typedef unsigned long ULONG; typedef long HRESULT; typedef int BOOL; typedef unsigned long long ULONGLONG;
typedef unsigned long long SIZE_T; typedef long long LONG_PTR; typedef void* HANDLE; typedef HANDLE HMODULE; typedef void* LPVOID;
typedef const void* LPCVOID; typedef const wchar_t* LPCWSTR; typedef wchar_t* LPWSTR; typedef wchar_t* BSTR; typedef wchar_t* LPOLESTR;
typedef unsigned short VARTYPE; typedef short VARIANT_BOOL; typedef unsigned long LCID; typedef void* FARPROC;
#ifdef _MSC_VER
#define WINAPI __stdcall
#else
#define WINAPI __attribute__((stdcall))
#endif
#define STDMETHODCALLTYPE __attribute__((stdcall))
#define TRUE 1
#define FALSE 0
#define NULL 0
#define S_OK ((HRESULT)0)
#define E_FAIL ((HRESULT)0x80004005L)
#define E_INVALIDARG ((HRESULT)0x80070057L)
#define E_POINTER ((HRESULT)0x80004003L)
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define E_ACCESSDENIED ((HRESULT)0x80070005L)
#define ERROR_TIMEOUT_HR ((HRESULT)0x800705B4L)
#define SUCCEEDED(hr) ((HRESULT)(hr)>=0)
#define FAILED(hr) ((HRESULT)(hr)<0)

struct GUID{DWORD Data1;WORD Data2;WORD Data3;BYTE Data4[8];}; typedef const GUID& REFIID; typedef GUID CLSID;
struct SAFEARRAY; struct IDispatch;
struct VARIANT{VARTYPE vt;WORD wReserved1,wReserved2,wReserved3;union{signed char cVal;BYTE bVal;short iVal;WORD uiVal;LONG lVal;ULONG ulVal;long long llVal;unsigned long long ullVal;float fltVal;double dblVal;VARIANT_BOOL boolVal;BSTR bstrVal;IDispatch* pdispVal;SAFEARRAY* parray;void* byref;struct{void* pvRecord;void* pRecInfo;}record;}data;};
typedef VARIANT VARIANTARG;
struct DISPPARAMS{VARIANTARG* rgvarg;LONG* rgdispidNamedArgs;UINT cArgs,cNamedArgs;};
static_assert(sizeof(void*)!=8||sizeof(VARIANT)==24,"Windows x64 VARIANT ABI mismatch");
static_assert(sizeof(void*)!=8||sizeof(DISPPARAMS)==24,"Windows x64 DISPPARAMS ABI mismatch");
struct EXCEPINFO{WORD wCode,wReserved;BSTR bstrSource,bstrDescription,bstrHelpFile;DWORD dwHelpContext;void* pvReserved;HRESULT(STDMETHODCALLTYPE*pfnDeferredFillIn)(EXCEPINFO*);HRESULT scode;};
struct IDispatchVtbl{HRESULT(STDMETHODCALLTYPE*QueryInterface)(IDispatch*,REFIID,void**);ULONG(STDMETHODCALLTYPE*AddRef)(IDispatch*);ULONG(STDMETHODCALLTYPE*Release)(IDispatch*);HRESULT(STDMETHODCALLTYPE*GetTypeInfoCount)(IDispatch*,UINT*);HRESULT(STDMETHODCALLTYPE*GetTypeInfo)(IDispatch*,UINT,LCID,void**);HRESULT(STDMETHODCALLTYPE*GetIDsOfNames)(IDispatch*,REFIID,LPOLESTR*,UINT,LCID,LONG*);HRESULT(STDMETHODCALLTYPE*Invoke)(IDispatch*,LONG,REFIID,LCID,WORD,DISPPARAMS*,VARIANT*,EXCEPINFO*,UINT*);};
struct IDispatch{IDispatchVtbl* lpVtbl;};
struct SECURITY_ATTRIBUTES{DWORD nLength;LPVOID lpSecurityDescriptor;BOOL bInheritHandle;};

void WINAPI ExitProcess(UINT);
DWORD WINAPI GetLastError(void);
LPCWSTR WINAPI GetCommandLineW(void);
ULONGLONG WINAPI GetTickCount64(void);
DWORD WINAPI GetCurrentProcessId(void);
HANDLE WINAPI GetProcessHeap(void);
LPVOID WINAPI HeapAlloc(HANDLE,DWORD,SIZE_T);
BOOL WINAPI HeapFree(HANDLE,DWORD,LPVOID);
HANDLE WINAPI CreateNamedPipeW(LPCWSTR,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,SECURITY_ATTRIBUTES*);
BOOL WINAPI ConnectNamedPipe(HANDLE,void*);
BOOL WINAPI DisconnectNamedPipe(HANDLE);
BOOL WINAPI ReadFile(HANDLE,LPVOID,DWORD,DWORD*,void*);
BOOL WINAPI WriteFile(HANDLE,LPCVOID,DWORD,DWORD*,void*);
BOOL WINAPI FlushFileBuffers(HANDLE);
BOOL WINAPI CloseHandle(HANDLE);
void WINAPI Sleep(DWORD);
HRESULT WINAPI CoInitializeEx(LPVOID,DWORD);
void WINAPI CoUninitialize(void);
HRESULT WINAPI CLSIDFromProgID(LPCWSTR,CLSID*);
HRESULT WINAPI CoCreateInstance(REFIID,void*,DWORD,REFIID,void**);
BSTR WINAPI SysAllocString(LPCWSTR);
void WINAPI SysFreeString(BSTR);
void WINAPI VariantInit(VARIANT*);
HRESULT WINAPI VariantClear(VARIANT*);
UINT WINAPI SafeArrayGetDim(SAFEARRAY*);
HRESULT WINAPI SafeArrayGetLBound(SAFEARRAY*,UINT,LONG*);
HRESULT WINAPI SafeArrayGetUBound(SAFEARRAY*,UINT,LONG*);
HRESULT WINAPI SafeArrayAccessData(SAFEARRAY*,void**);
HRESULT WINAPI SafeArrayUnaccessData(SAFEARRAY*);

void* memset(void* d,int v,SIZE_T n){BYTE* p=(BYTE*)d;while(n--)*p++=(BYTE)v;return d;}
void* memcpy(void* d,const void* s,SIZE_T n){BYTE* a=(BYTE*)d;const BYTE* b=(const BYTE*)s;while(n--)*a++=*b++;return d;}
}

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define PIPE_ACCESS_DUPLEX 0x00000003UL
#define FILE_FLAG_FIRST_PIPE_INSTANCE 0x00080000UL
#define PIPE_TYPE_BYTE 0x00000000UL
#define PIPE_READMODE_BYTE 0x00000000UL
#define PIPE_WAIT 0x00000000UL
#define PIPE_REJECT_REMOTE_CLIENTS 0x00000008UL
#define PIPE_UNLIMITED_INSTANCES 255
#define ERROR_PIPE_CONNECTED 535UL
#define HEAP_ZERO_MEMORY 0x00000008UL
#define COINIT_APARTMENTTHREADED 0x2UL
#define CLSCTX_INPROC_SERVER 0x1UL
#define CLSCTX_LOCAL_SERVER 0x4UL
#define LOCALE_USER_DEFAULT 0x0400UL
#define DISPATCH_METHOD 0x1
#define DISPATCH_PROPERTYGET 0x2
#define DISPATCH_PROPERTYPUT 0x4
#define DISPID_PROPERTYPUT ((LONG)-3)
#define VT_EMPTY 0
#define VT_I2 2
#define VT_I4 3
#define VT_R4 4
#define VT_R8 5
#define VT_BSTR 8
#define VT_BOOL 11
#define VT_UI2 18
#define VT_UI4 19
#define VT_ARRAY 0x2000
#define VARIANT_TRUE ((VARIANT_BOOL)-1)
#define VARIANT_FALSE ((VARIANT_BOOL)0)

#include "device_host_protocol.inc"
#include "../common/command_line_args.inc"

static const GUID IID_NULL_GUID={0,0,0,{0,0,0,0,0,0,0,0}};
static const GUID IID_IDispatch_GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
static IDispatch* g_object=0;

static BOOL ParsePipeName(LPCWSTR cmd,LPWSTR out,int cap){return AfGetCommandLineOption(cmd,L"--pipe",out,cap);}
static void ClearEx(EXCEPINFO* ex){if(ex->bstrSource)SysFreeString(ex->bstrSource);if(ex->bstrDescription)SysFreeString(ex->bstrDescription);if(ex->bstrHelpFile)SysFreeString(ex->bstrHelpFile);}
static HRESULT DispId(IDispatch* o,LPCWSTR name,LONG* id){LPOLESTR names[1];names[0]=(LPOLESTR)name;return o->lpVtbl->GetIDsOfNames(o,IID_NULL_GUID,names,1,LOCALE_USER_DEFAULT,id);}
static HRESULT Invoke(IDispatch* o,LPCWSTR name,WORD flags,VARIANTARG* args,UINT argCount,LONG* named,UINT namedCount,VARIANT* result){
    if(!o)return E_POINTER;LONG id=0;HRESULT hr=DispId(o,name,&id);if(FAILED(hr))return hr;DISPPARAMS dp;dp.rgvarg=args;dp.rgdispidNamedArgs=named;dp.cArgs=argCount;dp.cNamedArgs=namedCount;EXCEPINFO ex;memset(&ex,0,sizeof(ex));UINT argErr=0;if(result)VariantInit(result);hr=o->lpVtbl->Invoke(o,id,IID_NULL_GUID,LOCALE_USER_DEFAULT,flags,&dp,result,&ex,&argErr);ClearEx(&ex);return hr;
}
static HRESULT GetProp(IDispatch* o,LPCWSTR n,VARIANT* r){return Invoke(o,n,DISPATCH_PROPERTYGET,0,0,0,0,r);}
static HRESULT SetBoolProp(IDispatch* o,LPCWSTR n,BOOL v){VARIANT a;VariantInit(&a);a.vt=VT_BOOL;a.data.boolVal=v?VARIANT_TRUE:VARIANT_FALSE;LONG named=DISPID_PROPERTYPUT;return Invoke(o,n,DISPATCH_PROPERTYPUT,&a,1,&named,1,0);}
static HRESULT SetIntProp(IDispatch* o,LPCWSTR n,LONG v){VARIANT a;VariantInit(&a);a.vt=VT_I4;a.data.lVal=v;LONG named=DISPID_PROPERTYPUT;return Invoke(o,n,DISPATCH_PROPERTYPUT,&a,1,&named,1,0);}
static HRESULT CallInt(IDispatch* o,LPCWSTR n,LONG v){VARIANT a;VariantInit(&a);a.vt=VT_I4;a.data.lVal=v;return Invoke(o,n,DISPATCH_METHOD,&a,1,0,0,0);}
static HRESULT CallNoArgs(IDispatch* o,LPCWSTR n){return Invoke(o,n,DISPATCH_METHOD,0,0,0,0,0);}
static HRESULT StartExposure(IDispatch* o,double seconds,BOOL light){VARIANT a[2];VariantInit(&a[0]);VariantInit(&a[1]);a[0].vt=VT_BOOL;a[0].data.boolVal=light?VARIANT_TRUE:VARIANT_FALSE;a[1].vt=VT_R8;a[1].data.dblVal=seconds;return Invoke(o,L"StartExposure",DISPATCH_METHOD,a,2,0,0,0);}
static BOOL VariantBool(const VARIANT* v,BOOL fallback){if(!v)return fallback;if(v->vt==VT_BOOL)return v->data.boolVal!=VARIANT_FALSE;if(v->vt==VT_I4)return v->data.lVal!=0;if(v->vt==VT_UI4)return v->data.ulVal!=0;return fallback;}
static LONG VariantInt(const VARIANT* v,LONG fallback){if(!v)return fallback;if(v->vt==VT_I4)return v->data.lVal;if(v->vt==VT_UI4)return (LONG)v->data.ulVal;if(v->vt==VT_I2)return (LONG)v->data.iVal;if(v->vt==VT_UI2)return (LONG)v->data.uiVal;return fallback;}
static double VariantDouble(const VARIANT* v,double fallback){if(!v)return fallback;if(v->vt==VT_R8)return v->data.dblVal;if(v->vt==VT_R4)return (double)v->data.fltVal;if(v->vt==VT_I4)return (double)v->data.lVal;if(v->vt==VT_UI4)return (double)v->data.ulVal;return fallback;}
static HRESULT GetBool(LPCWSTR n,BOOL fallback,BOOL* out){VARIANT v;VariantInit(&v);HRESULT hr=GetProp(g_object,n,&v);if(SUCCEEDED(hr)&&out)*out=VariantBool(&v,fallback);VariantClear(&v);return hr;}
static HRESULT GetInt(LPCWSTR n,LONG fallback,LONG* out){VARIANT v;VariantInit(&v);HRESULT hr=GetProp(g_object,n,&v);if(SUCCEEDED(hr)&&out)*out=VariantInt(&v,fallback);VariantClear(&v);return hr;}
static HRESULT GetDouble(LPCWSTR n,double fallback,double* out){VARIANT v;VariantInit(&v);HRESULT hr=GetProp(g_object,n,&v);if(SUCCEEDED(hr)&&out)*out=VariantDouble(&v,fallback);VariantClear(&v);return hr;}
static void ReleaseObject(){if(g_object){
#if ASTROFOCUS_HOST_CAMERA
        SetBoolProp(g_object,L"Connected",FALSE);
#else
        CallNoArgs(g_object,L"Halt");SetBoolProp(g_object,L"Connected",FALSE);
#endif
        g_object->lpVtbl->Release(g_object);g_object=0;}}
static HRESULT ConnectObject(LPCWSTR progId,BOOL camera,AfHostResponse* response){
    ReleaseObject();CLSID clsid;HRESULT hr=CLSIDFromProgID(progId,&clsid);if(FAILED(hr))return hr;hr=CoCreateInstance(clsid,0,CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER,IID_IDispatch_GUID,(void**)&g_object);if(FAILED(hr)||!g_object)return FAILED(hr)?hr:E_FAIL;
    hr=SetBoolProp(g_object,L"Connected",TRUE);if(FAILED(hr)){ReleaseObject();return hr;}
    if(camera){LONG x=0,y=0,maxAdu=65535;GetInt(L"CameraXSize",0,&x);GetInt(L"CameraYSize",0,&y);GetInt(L"MaxADU",65535,&maxAdu);response->width=x;response->height=y;response->maxAdu=maxAdu;
        if(x>0&&y>0){SetIntProp(g_object,L"BinX",1);SetIntProp(g_object,L"BinY",1);SetIntProp(g_object,L"StartX",0);SetIntProp(g_object,L"StartY",0);SetIntProp(g_object,L"NumX",x);SetIntProp(g_object,L"NumY",y);}}

    else{BOOL absolute=FALSE;hr=GetBool(L"Absolute",FALSE,&absolute);if(FAILED(hr)||!absolute){ReleaseObject();return E_FAIL;}}
    return S_OK;
}
static int CommandLineArgumentCount(LPCWSTR token){return AfCommandLineArgumentCount(GetCommandLineW(),token);}
static BOOL CommandLineContains(LPCWSTR token){return AfCommandLineHasArgument(GetCommandLineW(),token);}
static BOOL ReadAll(HANDLE h,void* buffer,DWORD bytes){BYTE* p=(BYTE*)buffer;while(bytes){DWORD got=0;if(!ReadFile(h,p,bytes,&got,0)||got==0)return FALSE;p+=got;bytes-=got;}return TRUE;}
static BOOL WriteAll(HANDLE h,const void* buffer,DWORD bytes){const BYTE* p=(const BYTE*)buffer;while(bytes){DWORD sent=0;if(!WriteFile(h,p,bytes,&sent,0)||sent==0)return FALSE;p+=sent;bytes-=sent;}return TRUE;}
static UINT ArrayValue(const void* data,VARTYPE base,SIZE_T idx){if(base==VT_I4){LONG v=((const LONG*)data)[idx];return v<0?0U:(UINT)v;}if(base==VT_UI4)return ((const ULONG*)data)[idx];if(base==VT_I2){short v=((const short*)data)[idx];return v<0?0U:(UINT)v;}if(base==VT_UI2)return ((const WORD*)data)[idx];return 0U;}
static BOOL Extent(LONG l,LONG u,int max,int* out){long long n=(long long)u-(long long)l+1;if(!out||n<=0||n>max)return FALSE;*out=(int)n;return TRUE;}
static HRESULT BuildImagePayload(UINT** pixels,DWORD* bytes,LONG* width,LONG* height,LONG* maxAdu){
    if(!pixels||!bytes||!width||!height||!maxAdu)return E_POINTER;*pixels=0;*bytes=0;*width=*height=0;
    VARIANT v;VariantInit(&v);HRESULT hr=GetProp(g_object,L"ImageArray",&v);if(FAILED(hr))return hr;if(!(v.vt&VT_ARRAY)||!v.data.parray){VariantClear(&v);return E_FAIL;}
    SAFEARRAY* sa=v.data.parray;UINT dims=SafeArrayGetDim(sa);if(dims<2||dims>3){VariantClear(&v);return E_INVALIDARG;}
    LONG l1=0,u1=-1,l2=0,u2=-1,l3=0,u3=0;if(FAILED(SafeArrayGetLBound(sa,1,&l1))||FAILED(SafeArrayGetUBound(sa,1,&u1))||FAILED(SafeArrayGetLBound(sa,2,&l2))||FAILED(SafeArrayGetUBound(sa,2,&u2))||(dims==3&&(FAILED(SafeArrayGetLBound(sa,3,&l3))||FAILED(SafeArrayGetUBound(sa,3,&u3))))){VariantClear(&v);return E_FAIL;}
    int w=0,h=0,planes=1;if(!Extent(l1,u1,10000,&w)||!Extent(l2,u2,10000,&h)||(dims==3&&!Extent(l3,u3,4,&planes))){VariantClear(&v);return E_INVALIDARG;}
    VARTYPE base=(VARTYPE)(v.vt&0x0fff);if(base!=VT_I2&&base!=VT_UI2&&base!=VT_I4&&base!=VT_UI4){VariantClear(&v);return E_INVALIDARG;}
    unsigned long long count=(unsigned long long)(unsigned)w*(unsigned long long)(unsigned)h,need=count*4ULL;if(need==0||need>AF_HOST_MAX_IMAGE_BYTES){VariantClear(&v);return E_OUTOFMEMORY;}
    UINT* out=(UINT*)HeapAlloc(GetProcessHeap(),0,(SIZE_T)need);if(!out){VariantClear(&v);return E_OUTOFMEMORY;}void* raw=0;hr=SafeArrayAccessData(sa,&raw);if(FAILED(hr)||!raw){HeapFree(GetProcessHeap(),0,out);VariantClear(&v);return FAILED(hr)?hr:E_FAIL;}
    UINT seen=0;for(int y=0;y<h;y++)for(int x=0;x<w;x++){unsigned long long sum=0;for(int c=0;c<planes;c++){SIZE_T idx=dims==2?((SIZE_T)x*(SIZE_T)h+(SIZE_T)y):(((SIZE_T)x*(SIZE_T)h+(SIZE_T)y)*(SIZE_T)planes+(SIZE_T)c);sum+=ArrayValue(raw,base,idx);}UINT q=(UINT)(sum/(unsigned)planes);out[(SIZE_T)y*(SIZE_T)w+(SIZE_T)x]=q;if(q>seen)seen=q;}
    SafeArrayUnaccessData(sa);VariantClear(&v);*pixels=out;*bytes=(DWORD)need;*width=w;*height=h;*maxAdu=(LONG)seen;return S_OK;
}

extern "C" void AstroFocusApplicationMain(){
    int healthCheckCount=CommandLineArgumentCount(L"--health-check");if(healthCheckCount<0||healthCheckCount>1){ExitProcess(2);return;}
    if(CommandLineContains(L"--health-check")){ExitProcess(AF_HOST_PROTOCOL_VERSION==1?0:20);return;}
    wchar_t pipeName[320];if(!ParsePipeName(GetCommandLineW(),pipeName,320)){ExitProcess(2);return;}
    HRESULT init=CoInitializeEx(0,COINIT_APARTMENTTHREADED);if(FAILED(init))ExitProcess(3);
    HANDLE pipe=CreateNamedPipeW(pipeName,PIPE_ACCESS_DUPLEX|FILE_FLAG_FIRST_PIPE_INSTANCE,PIPE_TYPE_BYTE|PIPE_READMODE_BYTE|PIPE_WAIT|PIPE_REJECT_REMOTE_CLIENTS,1,65536,65536,0,0);if(pipe==INVALID_HANDLE_VALUE){CoUninitialize();ExitProcess(4);}
    if(!ConnectNamedPipe(pipe,0)&&GetLastError()!=ERROR_PIPE_CONNECTED){CloseHandle(pipe);CoUninitialize();ExitProcess(5);}
    BOOL running=TRUE;
    while(running){
        AfHostRequest req;memset(&req,0,sizeof(req));if(!ReadAll(pipe,&req,sizeof(req)))break;
        /* Fixed-size pipe strings are untrusted until explicitly terminated. */
        req.progId[(sizeof(req.progId)/sizeof(req.progId[0]))-1]=0;
        req.member[(sizeof(req.member)/sizeof(req.member[0]))-1]=0;
        AfHostResponse res;memset(&res,0,sizeof(res));res.magic=AF_HOST_MAGIC;res.protocolVersion=AF_HOST_PROTOCOL_VERSION;res.structBytes=sizeof(res);res.command=req.command;res.requestId=req.requestId;res.hostPid=GetCurrentProcessId();res.hr=E_INVALIDARG;
        UINT* payload=0;DWORD payloadBytes=0;
        if(req.magic!=AF_HOST_MAGIC||req.protocolVersion!=AF_HOST_PROTOCOL_VERSION||req.structBytes!=sizeof(req)){res.hr=E_INVALIDARG;}
        else if(req.deadlineTick&&GetTickCount64()>req.deadlineTick){res.hr=ERROR_TIMEOUT_HR;}
#if ASTROFOCUS_HOST_CAMERA
        else if(req.command==AFHC_CONNECT_CAMERA){res.hr=req.progId[0]?ConnectObject(req.progId,TRUE,&res):E_INVALIDARG;}
        else if(req.command==AFHC_CONNECT_FOCUSER){res.hr=E_ACCESSDENIED;}
#else
        else if(req.command==AFHC_CONNECT_CAMERA){res.hr=E_ACCESSDENIED;}
        else if(req.command==AFHC_CONNECT_FOCUSER){res.hr=req.progId[0]?ConnectObject(req.progId,FALSE,&res):E_INVALIDARG;}
#endif
        else if(req.command==AFHC_DISCONNECT){ReleaseObject();res.hr=S_OK;}
        else if(req.command==AFHC_GET_BOOL){BOOL v=req.boolArg?TRUE:FALSE;res.hr=GetBool(req.member,v,&v);res.boolValue=v?1UL:0UL;}
        else if(req.command==AFHC_GET_INT){LONG v=req.intArg;res.hr=GetInt(req.member,v,&v);res.intValue=v;}
        else if(req.command==AFHC_GET_DOUBLE){double v=req.doubleArg;res.hr=GetDouble(req.member,v,&v);res.doubleValue=v;}
        else if(req.command==AFHC_SET_INT){res.hr=g_object?SetIntProp(g_object,req.member,req.intArg):E_POINTER;}
        else if(req.command==AFHC_CALL_INT){res.hr=g_object?CallInt(g_object,req.member,req.intArg):E_POINTER;}
        else if(req.command==AFHC_CALL_NOARGS){res.hr=g_object?CallNoArgs(g_object,req.member):E_POINTER;}
        else if(req.command==AFHC_START_EXPOSURE){res.hr=g_object?StartExposure(g_object,req.doubleArg,req.boolArg!=0):E_POINTER;}
        else if(req.command==AFHC_GET_IMAGE){res.hr=g_object?BuildImagePayload(&payload,&payloadBytes,&res.width,&res.height,&res.maxAdu):E_POINTER;if(SUCCEEDED(res.hr)){res.payloadFormat=AFHP_U32_IMAGE;res.payloadBytes=payloadBytes;}}
        else if(req.command==AFHC_PING){res.hr=S_OK;res.boolValue=g_object?1UL:0UL;}
        else if(req.command==AFHC_TEST_BLOCK){for(;;)Sleep(1000);}
        else if(req.command==AFHC_TEST_CRASH){ExitProcess(91);}
        else if(req.command==AFHC_SHUTDOWN){ReleaseObject();res.hr=S_OK;running=FALSE;}
        res.completedTick=GetTickCount64();
        if(!WriteAll(pipe,&res,sizeof(res))){if(payload)HeapFree(GetProcessHeap(),0,payload);break;}
        if(payloadBytes&&!WriteAll(pipe,payload,payloadBytes)){HeapFree(GetProcessHeap(),0,payload);break;}
        if(payload)HeapFree(GetProcessHeap(),0,payload);FlushFileBuffers(pipe);
    }
    ReleaseObject();DisconnectNamedPipe(pipe);CloseHandle(pipe);CoUninitialize();ExitProcess(0);
}
