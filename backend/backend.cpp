// AstroFocus Studio 3.9.0 Engine
// Native Win32 x64 autofocus application using native ToupTek SDK or ASCOM Camera and ASCOM Focuser.
// Designed for the ToupTek GPCMOS02000KPA / Sony IMX291 class camera and the
// Celestron Focus Motor, but intentionally uses generic ASCOM interfaces.
// No separate redistributable runtime package; only Windows system DLLs and installed ASCOM drivers.

#include "../common/continuous_focus_logic.h"

extern "C" {

int _fltused = 0;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;
#ifdef ASTROFOCUS_NATIVE_TEST
typedef unsigned int DWORD;
typedef int LONG;
typedef unsigned int ULONG;
typedef int HRESULT;
#else
typedef unsigned long DWORD;
typedef long LONG;
typedef unsigned long ULONG;
typedef long HRESULT;
#endif
typedef int BOOL;
typedef unsigned long long ULONG_PTR;
typedef long long LONG_PTR;
typedef unsigned long long ULONGLONG;
typedef ULONG_PTR UINT_PTR;
typedef ULONG_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;
typedef unsigned short VARTYPE;
typedef short VARIANT_BOOL;
typedef wchar_t* BSTR;
typedef wchar_t* LPOLESTR;
typedef unsigned long LCID;
typedef unsigned short ATOM;
typedef void* HANDLE;
typedef HANDLE HINSTANCE;
typedef HANDLE HMODULE;
typedef HANDLE HWND;
typedef HANDLE HMENU;
typedef HANDLE HICON;
typedef HANDLE HCURSOR;
typedef HANDLE HBRUSH;
typedef HANDLE HGDIOBJ;
typedef HANDLE HFONT;
typedef HANDLE HPEN;
typedef HANDLE HDC;
typedef HANDLE HLOCAL;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef unsigned long long SIZE_T;
typedef unsigned short COLOR16;
typedef void* FARPROC;


typedef struct _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;

#ifdef _MSC_VER
#define WINAPI __stdcall
#else
#define WINAPI __attribute__((stdcall))
#endif
#define CALLBACK __attribute__((stdcall))
#define STDMETHODCALLTYPE __attribute__((stdcall))
#define NULL 0
#define TRUE 1
#define FALSE 0
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif
#include "../common/command_line_args.inc"
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#define S_OK ((HRESULT)0)
#define SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define FAILED(hr) ((HRESULT)(hr) < 0)

struct GUID { DWORD Data1; WORD Data2; WORD Data3; BYTE Data4[8]; };
typedef const GUID& REFIID;
typedef GUID CLSID;

struct POINT { LONG x; LONG y; };
struct RECT { LONG left,top,right,bottom; };
struct MSG { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; DWORD lPrivate; };
struct PAINTSTRUCT { HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32]; };
struct SYSTEMTIME { WORD wYear,wMonth,wDayOfWeek,wDay,wHour,wMinute,wSecond,wMilliseconds; };
struct EXCEPTION_RECORD_MIN{DWORD ExceptionCode,ExceptionFlags;EXCEPTION_RECORD_MIN* ExceptionRecord;void* ExceptionAddress;DWORD NumberParameters;ULONG_PTR ExceptionInformation[15];};
struct EXCEPTION_POINTERS_MIN{EXCEPTION_RECORD_MIN* ExceptionRecord;void* ContextRecord;};
typedef LONG (WINAPI *TOP_LEVEL_EXCEPTION_FILTER_MIN)(EXCEPTION_POINTERS_MIN*);
typedef TOP_LEVEL_EXCEPTION_FILTER_MIN (WINAPI *PFN_SetUnhandledExceptionFilter_MIN)(TOP_LEVEL_EXCEPTION_FILTER_MIN);
typedef LRESULT (CALLBACK *WNDPROC)(HWND,UINT,WPARAM,LPARAM);
struct WNDCLASSEXW {
    UINT cbSize; UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra;
    HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground;
    LPCWSTR lpszMenuName; LPCWSTR lpszClassName; HICON hIconSm;
};
struct NOTIFYICONDATAW_MIN { DWORD cbSize; HWND hWnd; UINT uID; UINT uFlags; UINT uCallbackMessage; HICON hIcon; wchar_t szTip[128]; DWORD dwState,dwStateMask; wchar_t szInfo[256]; union { UINT uTimeout; UINT uVersion; }; wchar_t szInfoTitle[64]; DWORD dwInfoFlags; GUID guidItem; HICON hBalloonIcon; };

struct BITMAPINFOHEADER {
    DWORD biSize; LONG biWidth; LONG biHeight; WORD biPlanes; WORD biBitCount;
    DWORD biCompression; DWORD biSizeImage; LONG biXPelsPerMeter; LONG biYPelsPerMeter;
    DWORD biClrUsed; DWORD biClrImportant;
};
struct RGBQUAD { BYTE rgbBlue,rgbGreen,rgbRed,rgbReserved; };
struct BITMAPINFO { BITMAPINFOHEADER bmiHeader; RGBQUAD bmiColors[1]; };

struct SAFEARRAY;
struct IDispatch;
struct VARIANT {
    VARTYPE vt; WORD wReserved1,wReserved2,wReserved3;
    union {
        signed char cVal; BYTE bVal; short iVal; WORD uiVal; LONG lVal; ULONG ulVal;
        long long llVal; unsigned long long ullVal; float fltVal; double dblVal;
        VARIANT_BOOL boolVal; BSTR bstrVal; IDispatch* pdispVal; SAFEARRAY* parray; void* byref;
        // The Windows x64 VARIANT union also contains two-pointer members. Without this member
        // the hand-written structure is only 16 bytes instead of 24 and COM writes past it.
        struct { void* pvRecord; void* pRecInfo; } record;
    } data;
};
typedef VARIANT VARIANTARG;
struct DISPPARAMS { VARIANTARG* rgvarg; LONG* rgdispidNamedArgs; UINT cArgs,cNamedArgs; };
struct EXCEPINFO {
    WORD wCode,wReserved; BSTR bstrSource,bstrDescription,bstrHelpFile; DWORD dwHelpContext;
    void* pvReserved; HRESULT (STDMETHODCALLTYPE *pfnDeferredFillIn)(EXCEPINFO*); HRESULT scode;
};
struct IDispatchVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IDispatch*,REFIID,void**);
    ULONG (STDMETHODCALLTYPE *AddRef)(IDispatch*);
    ULONG (STDMETHODCALLTYPE *Release)(IDispatch*);
    HRESULT (STDMETHODCALLTYPE *GetTypeInfoCount)(IDispatch*,UINT*);
    HRESULT (STDMETHODCALLTYPE *GetTypeInfo)(IDispatch*,UINT,LCID,void**);
    HRESULT (STDMETHODCALLTYPE *GetIDsOfNames)(IDispatch*,REFIID,LPOLESTR*,UINT,LCID,LONG*);
    HRESULT (STDMETHODCALLTYPE *Invoke)(IDispatch*,LONG,REFIID,LCID,WORD,DISPPARAMS*,VARIANT*,EXCEPINFO*,UINT*);
};
struct IDispatch { IDispatchVtbl* lpVtbl; };

struct STARTUPINFOW_MIN {
    DWORD cb; LPWSTR lpReserved; LPWSTR lpDesktop; LPWSTR lpTitle; DWORD dwX,dwY,dwXSize,dwYSize;
    DWORD dwXCountChars,dwYCountChars,dwFillAttribute,dwFlags; WORD wShowWindow,cbReserved2;
    BYTE* lpReserved2; HANDLE hStdInput,hStdOutput,hStdError;
};
struct PROCESS_INFORMATION_MIN { HANDLE hProcess; HANDLE hThread; DWORD dwProcessId; DWORD dwThreadId; };
struct LARGE_INTEGER_MIN { long long QuadPart; };
struct JOBOBJECT_BASIC_LIMIT_INFORMATION_MIN {
    LARGE_INTEGER_MIN PerProcessUserTimeLimit,PerJobUserTimeLimit; DWORD LimitFlags; SIZE_T MinimumWorkingSetSize,MaximumWorkingSetSize;
    DWORD ActiveProcessLimit; ULONG_PTR Affinity; DWORD PriorityClass,SchedulingClass;
};
struct IO_COUNTERS_MIN { ULONGLONG ReadOperationCount,WriteOperationCount,OtherOperationCount,ReadTransferCount,WriteTransferCount,OtherTransferCount; };
struct JOBOBJECT_EXTENDED_LIMIT_INFORMATION_MIN {
    JOBOBJECT_BASIC_LIMIT_INFORMATION_MIN BasicLimitInformation; IO_COUNTERS_MIN IoInfo;
    SIZE_T ProcessMemoryLimit,JobMemoryLimit,PeakProcessMemoryUsed,PeakJobMemoryUsed;
};

#ifndef ASTROFOCUS_NATIVE_TEST
static_assert(sizeof(DWORD)==4,"Windows ABI: DWORD must be 32-bit");
static_assert(sizeof(LONG)==4,"Windows ABI: LONG must be 32-bit");
static_assert(sizeof(HRESULT)==4,"Windows ABI: HRESULT must be 32-bit");
static_assert(sizeof(POINT)==8,"Windows ABI: POINT layout mismatch");
static_assert(sizeof(RECT)==16,"Windows ABI: RECT layout mismatch");
static_assert(sizeof(MSG)==48,"Windows x64 ABI: MSG layout mismatch");
static_assert(sizeof(PAINTSTRUCT)==72,"Windows x64 ABI: PAINTSTRUCT layout mismatch");
static_assert(sizeof(WNDCLASSEXW)==80,"Windows x64 ABI: WNDCLASSEXW layout mismatch");
static_assert(sizeof(NOTIFYICONDATAW_MIN)==976,"Windows x64 ABI: NOTIFYICONDATAW layout mismatch");
static_assert(sizeof(BITMAPINFOHEADER)==40,"Windows ABI: BITMAPINFOHEADER layout mismatch");
static_assert(sizeof(VARIANT)==24,"Windows x64 ABI: VARIANT must be 24 bytes");
static_assert(__builtin_offsetof(VARIANT,data)==8,"Windows ABI: VARIANT payload offset mismatch");
static_assert(sizeof(DISPPARAMS)==24,"Windows x64 ABI: DISPPARAMS layout mismatch");
static_assert(sizeof(EXCEPINFO)==64,"Windows x64 ABI: EXCEPINFO layout mismatch");
static_assert(sizeof(STARTUPINFOW_MIN)==104,"Windows x64 ABI: STARTUPINFO layout mismatch");
static_assert(sizeof(PROCESS_INFORMATION_MIN)==24,"Windows x64 ABI: PROCESS_INFORMATION layout mismatch");
static_assert(sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION_MIN)==144,"Windows x64 ABI: job information layout mismatch");

#endif

// kernel32
HMODULE WINAPI GetModuleHandleW(LPCWSTR);
void WINAPI ExitProcess(UINT);
DWORD WINAPI GetLastError(void);
DWORD WINAPI FormatMessageW(DWORD,LPCVOID,DWORD,DWORD,LPWSTR,DWORD,void*);
HLOCAL WINAPI LocalFree(HLOCAL);
int WINAPI lstrlenW(LPCWSTR);
LPWSTR WINAPI lstrcpyW(LPWSTR,LPCWSTR);
LPWSTR WINAPI lstrcatW(LPWSTR,LPCWSTR);
DWORD WINAPI GetModuleFileNameW(HMODULE,LPWSTR,DWORD);
LPCWSTR WINAPI GetCommandLineW(void);
DWORD WINAPI GetEnvironmentVariableW(LPCWSTR,LPWSTR,DWORD);
DWORD WINAPI GetFileAttributesW(LPCWSTR);
BOOL WINAPI CopyFileW(LPCWSTR,LPCWSTR,BOOL);
DWORD WINAPI GetPrivateProfileStringW(LPCWSTR,LPCWSTR,LPCWSTR,LPWSTR,DWORD,LPCWSTR);
BOOL WINAPI WritePrivateProfileStringW(LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR);
HANDLE WINAPI GetProcessHeap(void);
LPVOID WINAPI HeapAlloc(HANDLE,DWORD,SIZE_T);
BOOL WINAPI HeapFree(HANDLE,DWORD,LPVOID);
ULONGLONG WINAPI GetTickCount64(void);
HMODULE WINAPI LoadLibraryW(LPCWSTR);
BOOL WINAPI FreeLibrary(HMODULE);
FARPROC WINAPI GetProcAddress(HMODULE,const char*);
BOOL WINAPI CreateDirectoryW(LPCWSTR,const SECURITY_ATTRIBUTES*);
BOOL WINAPI DeleteFileW(LPCWSTR);
BOOL WINAPI MoveFileExW(LPCWSTR,LPCWSTR,DWORD);
HANDLE WINAPI CreateFileW(LPCWSTR,DWORD,DWORD,SECURITY_ATTRIBUTES*,DWORD,DWORD,HANDLE);
BOOL WINAPI WriteFile(HANDLE,LPCVOID,DWORD,DWORD*,void*);
BOOL WINAPI ReadFile(HANDLE,LPVOID,DWORD,DWORD*,void*);
DWORD WINAPI GetFileSize(HANDLE,DWORD*);
DWORD WINAPI SetFilePointer(HANDLE,LONG,LONG*,DWORD);
BOOL WINAPI CloseHandle(HANDLE);
void WINAPI GetLocalTime(SYSTEMTIME*);
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID);
HANDLE WINAPI CreateThread(SECURITY_ATTRIBUTES*,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,DWORD*);
HANDLE WINAPI CreateEventW(SECURITY_ATTRIBUTES*,BOOL,BOOL,LPCWSTR);
BOOL WINAPI SetEvent(HANDLE);
BOOL WINAPI ResetEvent(HANDLE);
DWORD WINAPI WaitForSingleObject(HANDLE,DWORD);
void WINAPI Sleep(DWORD);
typedef BOOL (WINAPI *PFN_CreateProcessW_MIN)(LPCWSTR,LPWSTR,SECURITY_ATTRIBUTES*,SECURITY_ATTRIBUTES*,BOOL,DWORD,LPVOID,LPCWSTR,STARTUPINFOW_MIN*,PROCESS_INFORMATION_MIN*);
typedef BOOL (WINAPI *PFN_TerminateProcess_MIN)(HANDLE,UINT);
typedef BOOL (WINAPI *PFN_GetExitCodeProcess_MIN)(HANDLE,DWORD*);
typedef DWORD (WINAPI *PFN_GetCurrentProcessId_MIN)(void);
typedef void (WINAPI *PFN_Sleep_MIN)(DWORD);
typedef HANDLE (WINAPI *PFN_CreateJobObjectW_MIN)(SECURITY_ATTRIBUTES*,LPCWSTR);
typedef BOOL (WINAPI *PFN_SetInformationJobObject_MIN)(HANDLE,int,LPVOID,DWORD);
typedef BOOL (WINAPI *PFN_AssignProcessToJobObject_MIN)(HANDLE,HANDLE);

// user32
ATOM WINAPI RegisterClassExW(const WNDCLASSEXW*);
HWND WINAPI CreateWindowExW(DWORD,LPCWSTR,LPCWSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID);
LRESULT WINAPI DefWindowProcW(HWND,UINT,WPARAM,LPARAM);
BOOL WINAPI ShowWindow(HWND,int);
BOOL WINAPI UpdateWindow(HWND);
BOOL WINAPI GetMessageW(MSG*,HWND,UINT,UINT);
BOOL WINAPI PeekMessageW(MSG*,HWND,UINT,UINT,UINT);
BOOL WINAPI TranslateMessage(const MSG*);
LRESULT WINAPI DispatchMessageW(const MSG*);
void WINAPI PostQuitMessage(int);
BOOL WINAPI SetWindowTextW(HWND,LPCWSTR);
int WINAPI GetWindowTextW(HWND,LPWSTR,int);
int WINAPI MessageBoxW(HWND,LPCWSTR,LPCWSTR,UINT);
LRESULT WINAPI SendMessageW(HWND,UINT,WPARAM,LPARAM);
HCURSOR WINAPI LoadCursorW(HINSTANCE,LPCWSTR);
HICON WINAPI LoadIconW(HINSTANCE,LPCWSTR); HANDLE WINAPI LoadImageW(HINSTANCE,LPCWSTR,UINT,int,int,UINT);
int WINAPI wsprintfW(LPWSTR,LPCWSTR,...);
UINT_PTR WINAPI SetTimer(HWND,UINT_PTR,UINT,void*);
BOOL WINAPI KillTimer(HWND,UINT_PTR);
BOOL WINAPI EnableWindow(HWND,BOOL);
BOOL WINAPI InvalidateRect(HWND,const RECT*,BOOL);
HDC WINAPI BeginPaint(HWND,PAINTSTRUCT*);
BOOL WINAPI EndPaint(HWND,const PAINTSTRUCT*);
BOOL WINAPI DestroyWindow(HWND);
BOOL WINAPI IsWindowVisible(HWND);
BOOL WINAPI GetClientRect(HWND,RECT*);
int WINAPI FillRect(HDC,const RECT*,HBRUSH);

// gdi32
HFONT WINAPI CreateFontW(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCWSTR);
BOOL WINAPI DeleteObject(HGDIOBJ);
HBRUSH WINAPI CreateSolidBrush(DWORD);
HPEN WINAPI CreatePen(int,int,DWORD);
HGDIOBJ WINAPI SelectObject(HDC,HGDIOBJ);
DWORD WINAPI SetTextColor(HDC,DWORD);
int WINAPI SetBkMode(HDC,int);
BOOL WINAPI TextOutW(HDC,int,int,LPCWSTR,int);
int WINAPI StretchDIBits(HDC,int,int,int,int,int,int,int,int,const void*,const BITMAPINFO*,UINT,DWORD);
BOOL WINAPI MoveToEx(HDC,int,int,POINT*);
BOOL WINAPI LineTo(HDC,int,int);
BOOL WINAPI Ellipse(HDC,int,int,int,int);
BOOL WINAPI Rectangle(HDC,int,int,int,int);
HGDIOBJ WINAPI GetStockObject(int);

// ole32 / oleaut32
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

// msvcrt mathematical helpers
 double __cdecl sqrt(double);
 double __cdecl fabs(double);
 double __cdecl sin(double);
 double __cdecl cos(double);
 int __cdecl sprintf(char*,const char*,...);

void* memset(void* dst,int value,SIZE_T count){BYTE* p=(BYTE*)dst;while(count--)*p++=(BYTE)value;return dst;}
void* memcpy(void* dst,const void* src,SIZE_T count){BYTE* d=(BYTE*)dst;const BYTE* s=(const BYTE*)src;while(count--)*d++=*s++;return dst;}

}

#define RGB(r,g,b) ((DWORD)(((BYTE)(r))|((WORD)((BYTE)(g))<<8)|(((DWORD)(BYTE)(b))<<16)))
#define LOWORD(l) ((WORD)((ULONG_PTR)(l)&0xffff))
#define HIWORD(l) ((WORD)(((ULONG_PTR)(l)>>16)&0xffff))

// Window constants
#define CS_HREDRAW 0x0002
#define CS_VREDRAW 0x0001
#define WS_OVERLAPPED 0x00000000L
#define WS_CAPTION 0x00C00000L
#define WS_SYSMENU 0x00080000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_VISIBLE 0x10000000L
#define WS_CHILD 0x40000000L
#define WS_BORDER 0x00800000L
#define WS_TABSTOP 0x00010000L
#define WS_GROUP 0x00020000L
#define WS_CLIPCHILDREN 0x02000000L
#define ES_READONLY 0x0800L
#define ES_AUTOHSCROLL 0x0080L
#define BS_PUSHBUTTON 0x00000000L
#define BS_AUTOCHECKBOX 0x00000003L
#define SS_LEFT 0x00000000L
#define SS_CENTERIMAGE 0x00000200L
#define SW_HIDE 0
#define SW_SHOW 5
#define CW_USEDEFAULT ((int)0x80000000)
#define COLOR_WINDOW 5
#define IDC_ARROW ((LPCWSTR)32512)
#define IDI_APPLICATION ((LPCWSTR)32512)
#define IMAGE_ICON 1
#define LR_LOADFROMFILE 0x0010
#define WM_SETICON 0x0080
#define ICON_SMALL 0
#define ICON_BIG 1
#define WM_DESTROY 0x0002
#define WM_CLOSE 0x0010
#define WM_SIZE 0x0005
#define WM_USER 0x0400
#define WM_PAINT 0x000F
#define WM_COMMAND 0x0111
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONDBLCLK 0x0203
#define SIZE_MINIMIZED 1
#define WM_APP 0x8000
#define WM_TIMER 0x0113
#define WM_DEVICECHANGE 0x0219
#define WM_POWERBROADCAST 0x0218
#define DBT_DEVNODES_CHANGED 0x0007
#define DBT_DEVICEARRIVAL 0x8000
#define DBT_DEVICEREMOVECOMPLETE 0x8004
#define PBT_APMSUSPEND 0x0004
#define PBT_APMRESUMEAUTOMATIC 0x0012
#define PBT_APMRESUMESUSPEND 0x0007
#define WM_SETFONT 0x0030
#define PM_REMOVE 0x0001
#define WAIT_OBJECT_0 0x00000000L
#define WAIT_TIMEOUT 0x00000102L
#define INFINITE 0xffffffffUL
#define BM_GETCHECK 0x00F0
#define BM_SETCHECK 0x00F1
#define BST_CHECKED 1
#define MB_OK 0x00000000L
#define MB_YESNO 0x00000004L
#define IDYES 6
#define MB_ICONERROR 0x00000010L
#define MB_ICONINFORMATION 0x00000040L
#define MB_ICONWARNING 0x00000030L
#define FW_NORMAL 400
#define FW_SEMIBOLD 600
#define FW_BOLD 700
#define DEFAULT_CHARSET 1
#define OUT_DEFAULT_PRECIS 0
#define CLIP_DEFAULT_PRECIS 0
#define CLEARTYPE_QUALITY 5
#define DEFAULT_PITCH 0
#define FF_DONTCARE 0
#define COINIT_APARTMENTTHREADED 0x2
#define CLSCTX_INPROC_SERVER 0x1
#define CLSCTX_LOCAL_SERVER 0x4
#define LOCALE_USER_DEFAULT 0x0400
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
#define BI_RGB 0
#define DIB_RGB_COLORS 0
#define SRCCOPY 0x00CC0020
#define TRANSPARENT 1
#define PS_SOLID 0
#define DT_LEFT 0x00000000
#define DT_TOP 0x00000000
#define DT_SINGLELINE 0x00000020
#define DT_VCENTER 0x00000004
#define DT_RIGHT 0x00000002
#define DT_NOPREFIX 0x00000800
#define DT_END_ELLIPSIS 0x00008000
#define HEAP_ZERO_MEMORY 0x00000008
#define GENERIC_READ 0x80000000L
#define GENERIC_WRITE 0x40000000L
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define FILE_BEGIN 0
#define FILE_END 2
#define FILE_ATTRIBUTE_NORMAL 0x00000080L
#define MOVEFILE_REPLACE_EXISTING 0x00000001L
#define MOVEFILE_WRITE_THROUGH 0x00000008L
#define FILE_SHARE_READ 0x00000001L
#define FILE_SHARE_WRITE 0x00000002L
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define CREATE_NO_WINDOW 0x08000000UL
#define STILL_ACTIVE 259UL
#define ERROR_FILE_NOT_FOUND 2UL
#define ERROR_PIPE_BUSY 231UL
#define ERROR_BROKEN_PIPE 109UL
#define ERROR_NO_DATA 232UL
#define INVALID_FILE_ATTRIBUTES 0xffffffffUL
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010UL

// Control IDs
#define ID_CAMERA_SELECT 1001
#define ID_CAMERA_CONNECT 1002
#define ID_FOCUSER_SELECT 1011
#define ID_FOCUSER_CONNECT 1012
#define ID_LIVE 1020
#define ID_EXPOSURE 1021
#define ID_GAIN 1022
#define ID_AUTO_STRETCH 1030
#define ID_OVERLAY_STARS 1031
#define ID_OVERLAY_LABELS 1032
#define ID_OVERLAY_SAT 1033
#define ID_MOVE_IN 1040
#define ID_MOVE_OUT 1041
#define ID_HALT 1042
#define ID_MANUAL_STEP 1043
#define ID_AF_START 1050
#define ID_AF_POINTS 1051
#define ID_AF_STEP 1052
#define ID_AF_BACKLASH 1053
#define ID_AF_SAMPLES 1054
#define ID_DEMO 1060
#define ID_NATIVE_CAMERA 1061
#define ID_OVERLAY_ZONES 1062
#define ID_BAHTINOV 1063
#define ID_PROFILE_NAME 1064
#define ID_FOCAL_LENGTH 1065
#define ID_PIXEL_SIZE 1066
#define ID_EXPORT_LOG 1067
#define ID_PREFERRED_DIR 1068
#define ID_RECONNECT 1069
#define ID_STEP_ASSIST 1070
#define ID_AUTO_REFOCUS 1071
#define ID_REFOCUS_MINUTES 1072
#define ID_REFOCUS_TEMP 1073
#define ID_DIAGNOSTICS 1074
#define ID_OVERLAY_PRESET 1075
#define ID_HTTP_TOGGLE 1076
#define WM_TRAYICON (WM_APP+18)
#define TIMER_MAIN 1
#define WM_TOUPCAM (WM_APP+17)



#ifndef FILE_SHARE_READ
#define FILE_SHARE_READ 0x00000001u
#define FILE_SHARE_WRITE 0x00000002u
#endif
// Minimal ToupTek SDK declarations loaded dynamically from toupcam.dll.
typedef void* HToupcam;
struct ToupcamResolution { unsigned width,height; };
struct ToupcamModelV2 { const wchar_t* name; unsigned long long flag; unsigned maxspeed,preview,still,maxfanspeed,ioctrol; float xpixsz,ypixsz; ToupcamResolution res[16]; };
struct ToupcamDeviceV2 { wchar_t displayname[64]; wchar_t id[64]; const ToupcamModelV2* model; };
struct ToupcamFrameInfoV2 { unsigned width,height,flag,seq; unsigned long long timestamp; };
typedef const wchar_t* (WINAPI *PFN_Toupcam_Version)(void);
typedef unsigned (WINAPI *PFN_Toupcam_EnumV2)(ToupcamDeviceV2*);
typedef HToupcam (WINAPI *PFN_Toupcam_Open)(const wchar_t*);
typedef void (WINAPI *PFN_Toupcam_Close)(HToupcam);
typedef HRESULT (WINAPI *PFN_Toupcam_StartPullModeWithWndMsg)(HToupcam,HWND,unsigned);
typedef HRESULT (WINAPI *PFN_Toupcam_Stop)(HToupcam);
typedef HRESULT (WINAPI *PFN_Toupcam_get_Size)(HToupcam,int*,int*);
typedef HRESULT (WINAPI *PFN_Toupcam_PullImageV2)(HToupcam,void*,int,ToupcamFrameInfoV2*);
typedef HRESULT (WINAPI *PFN_Toupcam_PullImageWithRowPitchV2)(HToupcam,void*,int,int,ToupcamFrameInfoV2*);
typedef HRESULT (WINAPI *PFN_Toupcam_put_ExpoTime)(HToupcam,unsigned);
typedef HRESULT (WINAPI *PFN_Toupcam_put_ExpoAGain)(HToupcam,unsigned short);
typedef HRESULT (WINAPI *PFN_Toupcam_put_RealTime)(HToupcam,int);

static const GUID IID_NULL_GUID={0,0,0,{0,0,0,0,0,0,0,0}};
static const GUID IID_IDispatch_GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

struct StarMetric {
    double x,y,fwhm,hfr,snr,ecc;
    UINT peak;
    BOOL saturated,used;
    int zone;
};

#define MAX_STARS 160
#define MAX_AF_POINTS 15
#define MAX_AF_SAMPLES 5

#include "device_host_protocol.inc"

enum DeviceWorkerCommand {
    DW_NONE=0,DW_CONNECT_CAMERA=1,DW_CONNECT_FOCUSER=2,DW_DISCONNECT=3,DW_GET_BOOL=4,DW_GET_INT=5,DW_GET_DOUBLE=6,
    DW_SET_BOOL=7,DW_SET_INT=8,DW_CALL_INT=9,DW_CALL_NOARGS=10,DW_START_EXPOSURE=11,DW_GET_VARIANT=12,DW_SHUTDOWN=13,DW_GET_IMAGE=14,DW_PING=15,DW_TEST_BLOCK=90,DW_TEST_CRASH=91
};
struct DeviceWorker {
    HANDLE thread,requestEvent,doneEvent;
    HANDLE hostProcess,hostThread,hostPipe;
    DWORD hostPid;
    BOOL hostJobAssigned;
    volatile LONG command;
    volatile LONG abandoned;
    BOOL camera;
    wchar_t progId[256];
    wchar_t member[64];
    wchar_t pipeName[320];
    BOOL boolArg;
    LONG intArg;
    double doubleArg;
    HRESULT hr;
    VARIANT result;
    BOOL boolResult;
    LONG intResult;
    double doubleResult;
    LONG cameraX,cameraY,maxAdu;
    IDispatch* object;
    UINT* imageData;
    DWORD imageBytes;
    LONG imageWidth,imageHeight,imageMaxAdu;
    ULONGLONG commandStarted,commandFinished,requestId,lastHeartbeat;
    DWORD commandTimeoutMs;
};

static HINSTANCE g_instance=0; static HICON g_appIcon=0,g_appIconSmall=0;
static HWND g_main=0;
static HFONT g_font=0,g_smallFont=0,g_titleFont=0,g_monoFont=0;
static HWND g_cameraEdit=0,g_cameraConnect=0,g_focuserEdit=0,g_focuserConnect=0;
static HWND g_liveButton=0,g_exposureEdit=0,g_gainEdit=0;
static HWND g_autoStretch=0,g_overlayStars=0,g_overlayLabels=0,g_overlaySat=0;
static HWND g_positionText=0,g_manualStepEdit=0,g_inButton=0,g_outButton=0,g_haltButton=0;
static HWND g_afButton=0,g_afPointsEdit=0,g_afStepEdit=0,g_afBacklashEdit=0,g_afSamplesEdit=0;
static HWND g_demoCheck=0,g_status=0,g_nativeCheck=0,g_zoneCheck=0,g_bahtinovCheck=0,g_profileEdit=0,g_focalEdit=0,g_pixelEdit=0,g_preferredDirCheck=0,g_reconnectCheck=0;
static HWND g_stepAssistButton=0,g_autoRefocusCheck=0,g_refocusMinutesEdit=0,g_refocusTempEdit=0;
static HWND g_diagnosticsButton=0,g_overlayPresetButton=0,g_httpCheck=0;
static DeviceWorker* g_cameraWorker=0;
static DeviceWorker* g_focuserWorker=0;
static HANDLE g_deviceHostJob=0;
static DeviceWorker* g_orphanWorkers[8];
static int g_orphanWorkerCount=0;
static BOOL g_cameraWorkerFaultPending=FALSE,g_focuserWorkerFaultPending=FALSE;
static wchar_t g_cameraWorkerFaultOperation[96]=L"–",g_focuserWorkerFaultOperation[96]=L"–";
static ULONGLONG g_cameraWorkerRetryAfter=0,g_focuserWorkerRetryAfter=0;
static int g_cameraWorkerRecoveryAttempt=0,g_focuserWorkerRecoveryAttempt=0;
static BOOL g_cameraWorkerBlocked=FALSE,g_focuserWorkerBlocked=FALSE;

enum DeviceRuntimePhase { DEV_DISCONNECTED=0,DEV_CONNECTING=1,DEV_READY=2,DEV_BUSY=3,DEV_RECOVERING=4,DEV_FAULTED=5,DEV_POSITION_UNKNOWN=6 };
struct DeviceRuntimeState {
    DeviceRuntimePhase phase;
    ULONGLONG operationId,startedTick,deadlineTick,lastSuccessTick,lastHeartbeatTick;
    int retryCount;
    HRESULT lastError;
    BOOL removalDetected,positionKnown;
    wchar_t operation[96];
};
static DeviceRuntimeState g_cameraRuntime={DEV_DISCONNECTED,0,0,0,0,0,0,S_OK,FALSE,TRUE,L"idle"};
static DeviceRuntimeState g_focuserRuntime={DEV_DISCONNECTED,0,0,0,0,0,0,S_OK,FALSE,FALSE,L"idle"};
static wchar_t g_dataDir[520]=L"",g_logDir[560]=L"",g_updateDir[560]=L"",g_hardwareLogPath[700]=L"";
static ULONGLONG g_nextDeviceOperationId=1;

static BOOL g_cameraConnected=FALSE,g_focuserConnected=FALSE,g_live=FALSE,g_exposing=FALSE,g_demo=FALSE,g_resumeLiveAfterAf=FALSE,g_resumeLiveAfterCameraRecovery=FALSE;
static BOOL g_simulatorMode=FALSE;
static BOOL g_faultCameraNoFrames=FALSE,g_faultCameraCorruptNext=FALSE,g_faultFocuserStall=FALSE,g_resumeRecoveryPending=FALSE;
static BOOL g_externalCameraMode=FALSE;
static wchar_t g_externalCameraName[256]=L"USB/UVC-Kamera";
enum SimulatorProfile { SIM_NORMAL=0, SIM_FEW_STARS=1, SIM_DEFOCUSED=2, SIM_POOR_SEEING=3, SIM_VARIABLE_SEEING=4, SIM_THIN_CLOUDS=5, SIM_ELONGATED=6, SIM_DIFFICULT=7, SIM_RANDOM=8 };
static int g_simPosition=24540,g_simOpticalPosition=24540,g_simBestFocus=24180,g_simMaxStep=60000,g_simLastDirection=0,g_simBacklashSteps=250,g_simBacklashRemaining=0;
static double g_simTemperature=12.0,g_simTiltX=0.0,g_simTiltY=0.0;
static int g_simStarCount=48,g_simProfileMode=SIM_RANDOM,g_simActiveProfile=SIM_NORMAL;
static wchar_t g_simProfileName[96]=L"Normal / Referenz";
static LPCWSTR SimulatorProfileName(int profile);
static void SelectSimulatorProfile();
static unsigned g_simFrameSequence=0,g_simProfileSelectionSequence=0,g_frameSequence=0;
static unsigned g_simRandomSeed=0xA57F3301U;
static ULONGLONG g_lastFrameCompleted=0;
static BOOL g_simDeterministicTest=FALSE;
static int g_selfTestPassed=0,g_selfTestFailed=0,g_selfTestTotal=0;
static BOOL g_syntheticSelfTestActive=FALSE;
static char g_selfTestSummary[2048]="Noch nicht ausgeführt";
static wchar_t g_selfTestHtmlPath[700]=L"",g_selfTestJsonPath[700]=L"";
static BOOL g_nativeRequested=TRUE,g_nativeActive=FALSE,g_nativeStreaming=FALSE,g_autoReconnect=TRUE,g_silentConnect=FALSE,g_cameraWanted=FALSE,g_focuserWanted=FALSE;
static wchar_t g_cameraId[256]=L"";
static wchar_t g_focuserId[256]=L"";
static wchar_t g_savedCameraId[256]=L"",g_savedFocuserId[256]=L"";
static wchar_t g_iniPath[520]=L"AstroFocusStudio.ini";
static wchar_t g_appDir[520]=L"";
static wchar_t g_toupTekDllPath[700]=L"";
static wchar_t g_toupTekLoadedPath[700]=L"";
static wchar_t g_lastCameraActionMessage[512]=L"";
static wchar_t g_lastFocuserActionMessage[512]=L"";
static UINT* g_raw=0;
static BYTE* g_nativeRgb=0;
static int g_nativeStride=0;
static SIZE_T g_nativeRgbBytes=0;
static DWORD* g_display=0;
static int g_width=0,g_height=0;
static UINT g_maxAdu=4095;
static UINT g_lowAdu=0,g_highAdu=4095,g_background=0;
static double g_noise=0.0;
static StarMetric g_stars[MAX_STARS];
static int g_starCount=0;
static double g_medianFwhm=0.0,g_medianHfr=0.0,g_medianSnr=0.0,g_medianEcc=0.0;
static int g_saturatedCount=0,g_usedCount=0,g_rejectWeak=0,g_rejectHot=0,g_rejectEdge=0,g_rejectElongated=0;
static double g_zoneFwhm[9]; static int g_zoneCount[9];
static double g_trendFwhm[120],g_trendHfr[120]; static int g_trendStars[120]; static int g_trendCount=0,g_trendHead=0;
static int g_selectedStar=-1; static BOOL g_manualStarLocked=FALSE,g_afUseSelectedStar=FALSE; static double g_selectedTargetNx=0.5,g_selectedTargetNy=0.5; static int g_selectedStarMisses=0; static double g_bahtinovScore=0.0,g_bahtinovOffset=0.0,g_bahtinovConfidence=0.0; static BOOL g_bahtinovValid=FALSE;
static double g_tiltMagnitude=0.0,g_tiltDx=0.0,g_tiltDy=0.0;static BOOL g_tiltValid=FALSE;static wchar_t g_tiltDirection[48]=L"–";
static RECT g_previewRect={306,70,1176,602};
static RECT g_curveRect={684,662,1176,900};
static RECT g_imageRect={306,70,1176,602};
static BITMAPINFO g_bmi;
static ULONGLONG g_exposureStarted=0;
static int g_capturePurpose=0; // 0 none, 1 live, 2 autofocus, 3 verification, 4 step assistant, 5 backlash
static int g_lastCompletedPurpose=0;
static double g_lastExposureSeconds=1.0;
static BOOL g_frameReady=FALSE;
static ULONGLONG g_lastNativeProcessed=0,g_lastCameraReconnect=0,g_lastFocuserReconnect=0;
static ULONGLONG g_lastFocuserWorkerPoll=0,g_lastCameraWorkerPoll=0,g_lastFocuserTemperaturePoll=0;
static int g_cachedFocuserPosition=-1,g_cachedFocuserMaxStep=200000;static BOOL g_cachedFocuserMoving=FALSE,g_focuserSetupReserved=FALSE;
static double g_focuserTemperature=0.0; static BOOL g_hasFocuserTemperature=FALSE;
#define MAX_TEMP_PROFILE 64
static double g_tempProfileT[MAX_TEMP_PROFILE];static int g_tempProfileP[MAX_TEMP_PROFILE],g_tempProfileCount=0;static double g_tempSlope=0.0,g_tempIntercept=0.0;static BOOL g_tempFitValid=FALSE;
// 3.1 focus intelligence: profile model, temperature compensation, seeing/quality, filters and event automation.
static BOOL g_tempCompEnabled=FALSE,g_autoStartPositionEnabled=FALSE,g_autoStartPending=FALSE;static int g_tempCompDeadbandSteps=20,g_tempCompMaxStep=120;static ULONGLONG g_lastTempCompMove=0;static int g_lastTempCompTarget=-1;
// Expert continuous-focus tracking. Corrections are made only between
// completed regular exposures; the main camera is never moved during an exposure.
enum ContinuousFocusMode{CF_PREDICTIVE=0,CF_IMAGE=1,CF_HYBRID=2};
enum ContinuousFocusPhase{CF_IDLE=0,CF_MOVING=1,CF_SETTLING=2,CF_VERIFYING=3};
enum ContinuousFocusMoveKind{CF_MOVE_NONE=0,CF_MOVE_PREDICTIVE=1,CF_MOVE_IMAGE_PROBE=2,CF_MOVE_ROLLBACK=3};
static BOOL g_continuousFocusEnabled=FALSE,g_continuousFocusFallback=TRUE,g_continuousFocusPaused=FALSE,g_continuousFocusFallbackPending=FALSE;
static int g_continuousFocusMode=CF_HYBRID,g_continuousFocusMinFrames=4,g_continuousFocusDeadband=3,g_continuousFocusMaxStep=12,g_continuousFocusMinConfidence=75,g_continuousFocusSettleMs=700;
static double g_continuousFocusMinImprovement=1.5,g_continuousFocusReferenceMetric=0.0,g_continuousFocusBeforeMetric=0.0,g_continuousFocusConfidence=0.0,g_continuousFocusEstimatedError=0.0,g_continuousFocusDriftStepsPerMinute=0.0;
static int g_continuousFocusPhase=CF_IDLE,g_continuousFocusMoveKind=CF_MOVE_NONE,g_continuousFocusOrigin=-1,g_continuousFocusTarget=-1,g_continuousFocusLastCorrection=0,g_continuousFocusLastDirection=1,g_continuousFocusAccepted=0,g_continuousFocusRejected=0;
static double g_continuousFocusSamples[16];static int g_continuousFocusSampleCount=0;
static ULONGLONG g_continuousFocusSettleUntil=0,g_continuousFocusLastActionTick=0,g_continuousFocusLastAcceptedTick=0;
static wchar_t g_continuousFocusState[96]=L"Deaktiviert",g_continuousFocusReason[320]=L"Kontinuierliche Fokusnachführung ist deaktiviert.";
static int g_profileSuccessfulRuns=0,g_profileTypicalPosition=-1,g_profileRecommendedStep=120,g_profileBacklash=250;static double g_profileTypicalFwhm=0.0,g_profileTypicalHfr=0.0,g_profileQualityMean=0.0;static BOOL g_profileModelValid=FALSE;
static double g_seeingIndex=0.0,g_transparencyIndex=100.0;static wchar_t g_seeingState[80]=L"noch keine Daten";
static int g_focusQualityScore=0;static wchar_t g_focusQualityLabel[80]=L"noch nicht bewertet";static int g_focusNeedScore=0;static wchar_t g_focusNeedLabel[96]=L"noch keine Referenz";static wchar_t g_focusNeedReason[240]=L"Noch keine belastbare Fokusreferenz vorhanden.";
static double g_fieldCurvature=0.0,g_fieldAsymmetry=0.0,g_fieldQualityScore=0.0,g_tiltConfidence=0.0;static wchar_t g_fieldAdvice[240]=L"Noch keine ausreichende Bildfeldmessung.";
#define MAX_FILTER_OFFSETS 12
struct FilterOffsetEntry{wchar_t name[32];int offset;BOOL valid;};static FilterOffsetEntry g_filterOffsets[MAX_FILTER_OFFSETS];static int g_filterOffsetCount=0;static wchar_t g_currentFilter[32]=L"";static int g_filterReferencePosition=-1;
#define MAX_NAMED_PROFILES 24
struct ProfileSnapshot{
    wchar_t name[96],cameraId[256],focuserId[256],currentFilter[32];
    double exposureMs,refocusMinutes,refocusTemp,refocusFwhmPercent,refocusStability,refocusCooldown,focalLength,pixelSize;
    int gain,manualStep,afPoints,afStep,afBacklash,afSamples,safeMin,safeMax;
    BOOL autoStretch,overlayStars,overlayLabels,overlaySat,zones,bahtinov,preferredOut,reconnect,nativeToupTek;
    BOOL autoRefocus,tempComp,autoStartPosition,refocusOnMeridian,refocusOnReconnect,refocusOnFilter;
    int refocusBadFrames,refocusMinStars,tempCompDeadband,tempCompMaxStep,refocusEveryCaptures;
    int simulatorProfile,simulatorBacklash;unsigned simulatorSeed;
    int modelSuccessfulRuns,modelTypicalPosition,modelRecommendedStep,modelBacklash;double modelTypicalFwhm,modelTypicalHfr,modelQualityMean;
    int filterReferencePosition,filterCount;FilterOffsetEntry filters[MAX_FILTER_OFFSETS];
    int tempCount;double tempT[MAX_TEMP_PROFILE];int tempP[MAX_TEMP_PROFILE];
};
static wchar_t g_activeProfileName[96]=L"Standardprofil";
static int g_profileRevision=0;

static BOOL g_refocusOnMeridian=TRUE,g_refocusOnReconnect=TRUE,g_refocusOnFilter=TRUE,g_filterRefocusPending=FALSE;static int g_refocusEveryCaptures=0,g_captureEventCounter=0;
static wchar_t g_lastExternalEvent[160]=L"–";
static wchar_t g_sessionPath[700]=L"";static BOOL g_sessionHeaderWritten=FALSE;
// 3.2 reliability/session analytics. These values describe the current engine session only.
static ULONGLONG g_sessionStartTick=0;
static int g_sessionAfAttempts=0,g_sessionAfSuccess=0,g_sessionAfFailed=0,g_sessionAfRollbacks=0;
static double g_sessionBestFwhm=0.0,g_sessionWorstFwhm=0.0;
static int g_sessionStartPosition=-1,g_sessionLastPosition=-1;
static double g_sessionStartTemperature=0.0,g_sessionLastTemperature=0.0;static BOOL g_sessionHasTemperature=FALSE;
static BOOL g_afValidationPassed=FALSE,g_afRollbackPerformed=FALSE;
static wchar_t g_afValidationState[96]=L"Noch kein Fokuslauf validiert";
static wchar_t g_afValidationReason[320]=L"Noch keine Abschluss-Kontrollmessung vorhanden.";
static ULONGLONG g_lastAfCompleted=0;static double g_lastAfTemperature=0.0;static BOOL g_hasLastAfTemperature=FALSE;
static ULONGLONG g_autoRefocusRetryAfter=0;static BOOL g_autoRefocusEnabled=FALSE,g_afAutomaticRun=FALSE,g_afAutomaticRequest=FALSE,g_afRequestConfirmed=FALSE;static wchar_t g_lastAutoRefocusReason[240]=L"–";
static BOOL g_autoRefocusReferenceReady=FALSE;
static int g_autoRefocusFailureCount=0;
static BOOL g_autoRefocusPaused=FALSE;
static int g_refocusMinStars=4,g_refocusBadFramesRequired=3,g_refocusBadFrameStreak=0;
static double g_refocusFwhmThresholdPercent=30.0,g_refocusStabilityLimit=0.45,g_refocusCooldownMinutes=10.0;
static unsigned g_lastRefocusEvaluatedFrameSequence=0;
static wchar_t g_lastAfErrorCode[64]=L"NONE",g_lastAfErrorTitle[160]=L"Kein Autofokusfehler",g_lastAfErrorDetail[512]=L"";
static BOOL g_lastAfErrorAutomatic=FALSE;static ULONGLONG g_lastAfErrorTick=0;
static BOOL g_stepAssistActive=FALSE,g_resumeLiveAfterStep=FALSE;static int g_stepAssistState=0,g_stepAssistIndex=0,g_stepAssistStart=0,g_stepAssistProbe=0;static int g_stepAssistPositions[3];static double g_stepAssistMetrics[3];static ULONGLONG g_stepAssistSettle=0;static wchar_t g_stepAssistResult[180]=L"";
static BOOL g_backlashCalActive=FALSE,g_resumeLiveAfterBacklash=FALSE;static int g_backlashCalState=0,g_backlashCalStart=0,g_backlashCalFar=0,g_backlashCalDirection=1,g_backlashCalIncrement=20,g_backlashCalCumulative=0,g_backlashCalMaxReverse=2000,g_backlashCalSamples=0,g_backlashCalEstimated=-1;static double g_backlashCalBaseline[3],g_backlashCalCurrent[3];static ULONGLONG g_backlashCalSettle=0;static wchar_t g_backlashCalResult[220]=L"";
static wchar_t g_toupVersion[96]=L"nicht geladen";
static HMODULE g_toupDll=0; static HToupcam g_tcam=0;
static PFN_Toupcam_Version pToupcam_Version=0; static PFN_Toupcam_EnumV2 pToupcam_EnumV2=0; static PFN_Toupcam_Open pToupcam_Open=0; static PFN_Toupcam_Close pToupcam_Close=0; static PFN_Toupcam_StartPullModeWithWndMsg pToupcam_StartPullModeWithWndMsg=0; static PFN_Toupcam_Stop pToupcam_Stop=0; static PFN_Toupcam_get_Size pToupcam_get_Size=0; static PFN_Toupcam_PullImageV2 pToupcam_PullImageV2=0; static PFN_Toupcam_PullImageWithRowPitchV2 pToupcam_PullImageWithRowPitchV2=0; static PFN_Toupcam_put_ExpoTime pToupcam_put_ExpoTime=0; static PFN_Toupcam_put_ExpoAGain pToupcam_put_ExpoAGain=0; static PFN_Toupcam_put_RealTime pToupcam_put_RealTime=0;

// Autofocus state
static BOOL g_afActive=FALSE;
static BOOL g_afRunUsesSelectedStar=FALSE;
static int g_afState=0;
static int g_afPointCount=0,g_afPointIndex=0,g_afSamples=1,g_afSampleIndex=0;
static int g_afPositions[MAX_AF_POINTS];
static double g_afMetrics[MAX_AF_POINTS],g_afFwhmMetrics[MAX_AF_POINTS];
static double g_afMetricSigma[MAX_AF_POINTS],g_afFwhmSigma[MAX_AF_POINTS];
static double g_afResiduals[MAX_AF_POINTS],g_afFwhmResiduals[MAX_AF_POINTS];
static BOOL g_afOutliers[MAX_AF_POINTS];
static int g_afUsedMetrics[MAX_AF_POINTS],g_afSamplesPerPoint[MAX_AF_POINTS];
static double g_afSampleMetrics[MAX_AF_SAMPLES],g_afFwhmSampleMetrics[MAX_AF_SAMPLES];
static int g_afUsedSampleMetrics[MAX_AF_SAMPLES];
static int g_afAdaptiveSamplesAdded=0;
static int g_afStartPosition=0,g_afBestPosition=0,g_afStep=100,g_afBacklash=0,g_afRecenterCount=0,g_afExpansionCount=0;
static int g_moveTarget=0,g_moveFinalTarget=0,g_moveContinuation=0;
static ULONGLONG g_moveStartedTick=0,g_moveDeadlineTick=0;
static int g_moveStartPosition=-1;
static ULONGLONG g_settleUntil=0;
static double g_fitA=0.0,g_fitB=0.0,g_fitC=0.0,g_fitR2=0.0;
static double g_fitFwhmA=0.0,g_fitFwhmB=0.0,g_fitFwhmC=0.0,g_fitFwhmR2=0.0;
static double g_fitCenterPosition=0.0,g_fitScale=1.0;
static double g_afExpectedHfr=0.0,g_afExpectedFwhm=0.0;
static BOOL g_fitValid=FALSE,g_fitFwhmValid=FALSE;
static int g_fitModel=0,g_fitFwhmModel=0;static double g_fitParams[5],g_fitFwhmParams[5];
static double g_fitFocusSigma=0.0,g_fitFocusSigmaLoo=0.0,g_fitReducedChi2=0.0,g_fitResidualRms=0.0,g_fitAicc=0.0;
static int g_fitInliers=0,g_fitOutliers=0;
static int g_vBestPosition=0; static double g_fitConfidence=0.0; static wchar_t g_fitMethod[128]=L"–";
static double g_afVerificationHfr[MAX_AF_SAMPLES],g_afVerificationFwhm[MAX_AF_SAMPLES];
static int g_afVerificationCount=0,g_afVerificationTarget=3,g_afVerificationRetryCount=0;
static BOOL g_afFinalValid=FALSE;static double g_afFinalHfr=0.0,g_afFinalFwhm=0.0;static int g_afFinalPosition=-1;
static UINT g_histogram[128];

// Version 1.3 operational safeguards and automation.
static int g_safeMinPosition=0,g_safeMaxPosition=200000;
static BOOL g_autoExposureEnabled=TRUE,g_degradationRefocusEnabled=TRUE,g_httpEnabled=TRUE;
static double g_beforeFwhm=0.0,g_beforeHfr=0.0,g_lastGoodFwhm=0.0,g_focusDegradeFactor=1.30;
static int g_afRetryCount=0,g_overlayPreset=1;
static wchar_t g_lastDiagnosticPath[520]=L"";

// Minimal dynamically loaded Winsock server. It is polled by the UI timer, so no worker thread is required.
typedef unsigned long long SOCKET;
struct SOCKADDR { unsigned short sa_family; char sa_data[14]; };
struct IN_ADDR { unsigned long s_addr; };
struct SOCKADDR_IN { short sin_family; unsigned short sin_port; IN_ADDR sin_addr; char sin_zero[8]; };
// Opaque, oversized storage for WSAStartup; avoids reproducing an SDK-dependent WSADATA layout.
struct alignas(16) WSADATA_STORAGE { BYTE bytes[512]; };
static_assert(sizeof(WSADATA_STORAGE)>=408,"Windows x64 ABI: WSA startup storage too small");
typedef int (WINAPI *PFN_WSAStartup)(WORD,void*); typedef int (WINAPI *PFN_WSACleanup)(void);
typedef SOCKET (WINAPI *PFN_socket)(int,int,int); typedef int (WINAPI *PFN_bind)(SOCKET,const SOCKADDR*,int);
typedef int (WINAPI *PFN_listen)(SOCKET,int); typedef SOCKET (WINAPI *PFN_accept)(SOCKET,SOCKADDR*,int*);
typedef int (WINAPI *PFN_recv)(SOCKET,char*,int,int); typedef int (WINAPI *PFN_send)(SOCKET,const char*,int,int);
typedef int (WINAPI *PFN_closesocket)(SOCKET); typedef int (WINAPI *PFN_setsockopt)(SOCKET,int,int,const char*,int); typedef int (WINAPI *PFN_ioctlsocket)(SOCKET,long,unsigned long*);
typedef unsigned short (WINAPI *PFN_htons)(unsigned short); typedef unsigned long (WINAPI *PFN_htonl)(unsigned long);
static HMODULE g_ws2=0; static SOCKET g_httpListen=(SOCKET)(~0ULL); static int g_httpPort=8873; static BOOL g_shutdownRequested=FALSE;
static PFN_WSAStartup pWSAStartup=0;static PFN_WSACleanup pWSACleanup=0;static PFN_socket p_socket=0;static PFN_bind p_bind=0;static PFN_listen p_listen=0;static PFN_accept p_accept=0;static PFN_recv p_recv=0;static PFN_send p_send=0;static PFN_closesocket p_closesocket=0;static PFN_setsockopt p_setsockopt=0;static PFN_ioctlsocket p_ioctlsocket=0;static PFN_htons p_htons=0;static PFN_htonl p_htonl=0;
#define INVALID_SOCKET_VALUE ((SOCKET)(~0ULL))
#define AF_INET_MIN 2
#define SOCK_STREAM_MIN 1
#define IPPROTO_TCP_MIN 6
#define SOL_SOCKET_MIN 0xffff
#define SO_SNDTIMEO_MIN 0x1005
#define SO_RCVTIMEO_MIN 0x1006
#define FIONBIO_MIN 0x8004667eL
#define INADDR_LOOPBACK_MIN 0x7f000001UL

typedef BOOL (WINAPI *PFN_Shell_NotifyIconW)(DWORD,NOTIFYICONDATAW_MIN*);
typedef HANDLE (WINAPI *PFN_ShellExecuteW)(HWND,LPCWSTR,LPCWSTR,LPCWSTR,LPCWSTR,int);
static HMODULE g_shell32=0;static PFN_Shell_NotifyIconW pShell_NotifyIconW=0;static PFN_ShellExecuteW pShellExecuteW=0;static BOOL g_trayAdded=FALSE;
#define NIM_ADD_MIN 0x00000000
#define NIM_DELETE_MIN 0x00000002
#define NIF_MESSAGE_MIN 0x00000001
#define NIF_ICON_MIN 0x00000002
#define NIF_TIP_MIN 0x00000004


static void StartAutofocus();
static BOOL SelectManualStarAt(int,int);
static void ClearManualStarSelection();
static BOOL RunSimulatorWorkflowRegression(char*,int);
static BOOL RunSimulatorSelectedStarRegression(char*,int);
static void StopAutofocus(BOOL,LPCWSTR);
static int FocuserPosition();
static void BuildPath(LPCWSTR,LPWSTR,int);
static void BuildDataPath(LPCWSTR,LPWSTR,int);
static void WToAscii(LPCWSTR,char*,int);
static void WToJsonUtf8(LPCWSTR,char*,int);
static LPCWSTR DevicePhaseNameW(DeviceRuntimePhase);
static BOOL SubmitWorker(DeviceWorker*,LONG,DWORD,LPCWSTR);
static void CopyWBounded(LPWSTR,int,LPCWSTR);
static void CatWBounded(LPWSTR,int,LPCWSTR);
static void FormatFixed(double,int,LPWSTR);
static BOOL ParseStrictDoubleW(LPCWSTR,double*);
static double ParseAsciiDouble(const char*,double);
static int ALen(const char*);
static void PutLe16(BYTE*,UINT);
static void PutLe32(BYTE*,UINT);
static void* Alloc(SIZE_T);
static void Free(void*);
static BOOL IsChecked(HWND);
static void SetChecked(HWND,BOOL);
static UINT ParseUIntW(LPCWSTR,UINT);
static BOOL ParseStrictUIntW(LPCWSTR,UINT*);
static void SetAutofocusError(LPCWSTR,LPCWSTR,LPCWSTR,BOOL);
static void SaveSettings();
static BOOL SelectDriver(BOOL);
static BOOL LoadToupTek();
static void UnloadToupTek();
static void SetCameraActionMessage(LPCWSTR);
static void SetFocuserActionMessage(LPCWSTR);
static BOOL IsSafeToupTekDllPath(LPCWSTR);
static void WriteIni(LPCWSTR,LPCWSTR);
static BOOL ConnectCamera();
static void DisconnectCamera();
static void SetStatus(LPCWSTR);
static BOOL ConnectFocuser();
static BOOL FocuserMoving();
static void StartLive();
static BOOL ManualMove(int);
static void HaltFocuser();
static void StartStepAssistant();
static void StopStepAssistant(BOOL,LPCWSTR);
static BOOL ExportReport(LPCWSTR);
static void BuildDisplay();
static BOOL RefreshSelectedStarAnalysis();
static BOOL FiniteD(double);
static double Median(double*,int);
static double ClampD(double,double,double);
static double JsonNumber(double,double fallback=0.0);
static BOOL IsTrackableFocusStar(const StarMetric*,BOOL);
static void AppendRuntimeTrace(const char* stage);
static void SetRuntimeOperation(const char* operation);
static void ComputeBahtinov(int cx,int cy);
static BOOL GenerateSyntheticFrame(int,double,double,double,int,BOOL,BOOL,BOOL);
static void SetSimulatorMode(BOOL);
static void RunSyntheticSelfTests();
static BOOL RunSimulatorLiveRegression(char*,int);
static BOOL RunStepAssistantRegression(char*,int);
static BOOL FitAutofocus();
static void AddTemperaturePoint(double,int);
static void UpdateTempRegression();
static BOOL WriteTextFile(LPCWSTR,const char*);
static BOOL WriteAllHandle(HANDLE,const char*,DWORD);
static void WriteSimulatorStage(const char*);
static void StopLive();
static BOOL MoveFocuser(int);
static BOOL StartExposure(int);
static BOOL StartLiveExposureOrStop(LPCWSTR);
static void ProcessCompletedFrame(int);
static void FinishStepAssistant(LPCWSTR);
static void AbortExposure();
static void MarkCameraDisconnected(LPCWSTR);
static void MarkFocuserDisconnected(LPCWSTR);
static void PrepareHardwareForSuspend();
static void EnsureAutoRefocusMeasurementReference();
static DeviceWorker* CreateDeviceWorker(BOOL camera);
static void DestroyDeviceWorker(DeviceWorker**,BOOL);
static void CleanupOrphanWorkers();
static BOOL WorkerConnect(DeviceWorker*,LPCWSTR,DWORD);
static BOOL WorkerDisconnect(DeviceWorker*,DWORD);
static BOOL WorkerGetBool(DeviceWorker*,LPCWSTR,BOOL,BOOL*,DWORD);
static BOOL WorkerGetInt(DeviceWorker*,LPCWSTR,LONG,LONG*,DWORD);
static BOOL WorkerGetDouble(DeviceWorker*,LPCWSTR,double,double*,DWORD);
static BOOL WorkerSetInt(DeviceWorker*,LPCWSTR,LONG,DWORD);
static BOOL WorkerCallInt(DeviceWorker*,LPCWSTR,LONG,DWORD);
static BOOL WorkerCallNoArgs(DeviceWorker*,LPCWSTR,DWORD);
static BOOL WorkerStartExposure(DeviceWorker*,double,BOOL,DWORD);
static BOOL WorkerGetImage(DeviceWorker*,UINT**,int*,int*,int*,DWORD);
static void ApplyDeviceWorkerFaults();
static void UpdateRefocusDegradationState();
static void ScheduleAutoRefocusRetry(LPCWSTR);
static void ResumeAutoRefocusAfterPause();
static void UpdateSeeingAndFocusRecommendation();
static int CalculateAutofocusQualityScore(double,double,int,double);
static void LoadFocusProfileModel();
static void SaveFocusProfileModel();
static void UpdateFocusProfileModelAfterSuccess();
static void ApplyTemperatureCompensation(ULONGLONG);
static BOOL TriggerAutomaticRefocus(LPCWSTR);
static BOOL ContinuousFocusOnLiveFrame();
static void ContinuousFocusTick(ULONGLONG);
static void ContinuousFocusResetReference(LPCWSTR);
static void ContinuousFocusSuspendForAutofocus();
static void TryAutomaticStartPosition();
static void StartBacklashCalibration();
static void StopBacklashCalibration(BOOL,LPCWSTR);
static void HandleBacklashCalibrationFrame();
static void AppendSessionEvent(LPCWSTR,LPCWSTR);
static BOOL HandleExternalRefocusEvent(LPCWSTR);
static BOOL LearnCurrentFilterOffset(LPCWSTR);
static BOOL ApplyFilterOffset(LPCWSTR);
static void EnsureProfileLibrary();
static BOOL SaveNamedProfile(LPCWSTR,BOOL,LPWSTR,int);
static BOOL LoadNamedProfile(LPCWSTR,LPWSTR,int);
static BOOL DeleteNamedProfile(LPCWSTR,LPWSTR,int);
static BOOL ImportNamedProfile(LPCWSTR,LPWSTR,int);
static BOOL ExportNamedProfile(LPCWSTR,LPCWSTR,LPWSTR,int);
static void SendProfileList(SOCKET);
static void SendProfilePreview(SOCKET,const char*);


static HBRUSH g_brushWindow=0,g_brushPanel=0,g_brushBlack=0,g_brushPlot=0;
static HPEN g_penGrid=0,g_penCurve=0,g_penPoint=0,g_penGood=0,g_penBad=0,g_penBest=0;

static int NotifyUser(LPCWSTR text,LPCWSTR title,UINT flags){
    (void)title;
    // The engine is intentionally headless. Never open modal dialogs from it:
    // they would block the local API and make the visible frontend appear crashed.
    SetStatus(text);
    return (flags&MB_YESNO)?IDYES:1;
}


static void RemoveTrayIcon(){if(g_trayAdded&&pShell_NotifyIconW){NOTIFYICONDATAW_MIN n;memset(&n,0,sizeof(n));n.cbSize=sizeof(n);n.hWnd=g_main;n.uID=1;pShell_NotifyIconW(NIM_DELETE_MIN,&n);}g_trayAdded=FALSE;if(g_shell32)FreeLibrary(g_shell32);g_shell32=0;pShell_NotifyIconW=0;}
static double FocusStability(){
    if(g_trendCount<4)return 0.0;int n=g_trendCount<12?g_trendCount:12;double mean=0.0;
    for(int i=0;i<n;i++){int idx=(g_trendHead-1-i+120)%120;mean+=g_trendFwhm[idx];}mean/=n;
    double v=0.0;for(int i=0;i<n;i++){int idx=(g_trendHead-1-i+120)%120;double d=g_trendFwhm[idx]-mean;v+=d*d;}return sqrt(v/n);
}
static void UpdateSeeingAndFocusRecommendation(){
    if(g_trendCount<5){g_seeingIndex=0.0;g_transparencyIndex=100.0;CopyWBounded(g_seeingState,80,L"noch zu wenige Messungen");}
    else{
        int n=g_trendCount<12?g_trendCount:12;double fw[12];double stars[12];for(int i=0;i<n;i++){int idx=(g_trendHead-1-i+120)%120;fw[i]=g_trendFwhm[idx];stars[i]=(double)g_trendStars[idx];}
        double medF=Median(fw,n),medStars=Median(stars,n),mad[12];for(int i=0;i<n;i++)mad[i]=fabs(fw[i]-medF);double m=Median(mad,n);double robustCv=medF>0.0?1.4826*m/medF:1.0;double starRatio=medStars>0.0?(double)g_usedCount/medStars:1.0;if(starRatio>1.0)starRatio=1.0;if(starRatio<0.0)starRatio=0.0;g_transparencyIndex=ClampD(starRatio*100.0,0.0,100.0);g_seeingIndex=ClampD(100.0-robustCv*900.0-(1.0-starRatio)*45.0,0.0,100.0);
        if(medStars>=6.0&&starRatio<0.52)CopyWBounded(g_seeingState,80,L"Wolken/Dunst oder starke Transparenzänderung");else if(g_seeingIndex>=78.0)CopyWBounded(g_seeingState,80,L"sehr stabil");else if(g_seeingIndex>=58.0)CopyWBounded(g_seeingState,80,L"stabil");else if(g_seeingIndex>=38.0)CopyWBounded(g_seeingState,80,L"wechselhaft");else CopyWBounded(g_seeingState,80,L"sehr unruhig");
    }
    double fwhmDegradePct=(g_lastGoodFwhm>0.0&&FiniteD(g_medianFwhm))?((g_medianFwhm/g_lastGoodFwhm)-1.0)*100.0:0.0;
    double fwhmNeed=0.0;if(g_lastGoodFwhm>0.0&&FiniteD(g_medianFwhm))fwhmNeed=ClampD(fwhmDegradePct/(g_refocusFwhmThresholdPercent>0.0?g_refocusFwhmThresholdPercent:30.0)*100.0,0.0,100.0);
    wchar_t v[64];double minutes=0.0,tempDelta=0.0;GetWindowTextW(g_refocusMinutesEdit,v,64);if(!ParseStrictDoubleW(v,&minutes)||minutes<0.0)minutes=0.0;GetWindowTextW(g_refocusTempEdit,v,64);if(!ParseStrictDoubleW(v,&tempDelta)||tempDelta<0.0)tempDelta=0.0;ULONGLONG now=GetTickCount64();double elapsed=g_lastAfCompleted?(double)(now-g_lastAfCompleted)/60000.0:0.0;double timeNeed=minutes>0.0?ClampD(elapsed/minutes*100.0,0.0,100.0):0.0;double td=(g_hasFocuserTemperature&&g_hasLastAfTemperature)?fabs(g_focuserTemperature-g_lastAfTemperature):0.0;double tempNeed=tempDelta>0.0?ClampD(td/tempDelta*100.0,0.0,100.0):0.0;double need=fwhmNeed;if(timeNeed>need)need=timeNeed;if(tempNeed>need)need=tempNeed;
    int recent=g_trendCount<5?g_trendCount:5,worse=0;if(g_lastGoodFwhm>0.0){for(int i=0;i<recent;i++){int idx=(g_trendHead-1-i+120)%120;if(FiniteD(g_trendFwhm[idx])&&g_trendFwhm[idx]>g_lastGoodFwhm)worse++;}}
    wchar_t pct[32],signedPct[40],base[180];FormatFixed(fwhmDegradePct,1,pct);signedPct[0]=0;if(fwhmDegradePct>=0.0)CatWBounded(signedPct,40,L"+");CatWBounded(signedPct,40,pct);
    base[0]=0;if(g_lastGoodFwhm>0.0&&recent>0){wchar_t counts[72];wsprintfW(counts,L"%d von %d Messungen schlechter.",worse,recent);CatWBounded(base,180,L"FWHM seit Referenz ");CatWBounded(base,180,signedPct);CatWBounded(base,180,L" %; ");CatWBounded(base,180,counts);}else CopyWBounded(base,180,L"Noch keine belastbare FWHM-Referenz vorhanden.");
    wchar_t reason[420];reason[0]=0;
    if(g_trendCount>=5&&(g_seeingIndex<38.0||g_transparencyIndex<55.0)&&fwhmNeed>=75.0){need=need>60.0?60.0:need;CopyWBounded(reason,420,base);CatWBounded(reason,420,L" Seeing/Transparenz instabil; Refokus zur Vermeidung eines Fehltriggers zurückgestellt.");}
    else if(fwhmNeed>=60.0){CopyWBounded(reason,420,base);CatWBounded(reason,420,L" Nachhaltige Verschlechterung nähert sich der Refokusgrenze oder hat sie erreicht.");}
    else if(tempNeed>=75.0){wchar_t tdw[32];FormatFixed(td,1,tdw);CopyWBounded(reason,420,L"Temperatur seit Referenz ");CatWBounded(reason,420,tdw);CatWBounded(reason,420,L" °C. ");CatWBounded(reason,420,base);}
    else if(timeNeed>=75.0){wchar_t ew[32];FormatFixed(elapsed,1,ew);CopyWBounded(reason,420,L"Seit letztem Autofokus ");CatWBounded(reason,420,ew);CatWBounded(reason,420,L" min. ");CatWBounded(reason,420,base);}
    else if(fwhmNeed>=30.0){CopyWBounded(reason,420,base);CatWBounded(reason,420,L" Leichte, noch nicht kritische Fokusverschlechterung erkannt.");}
    else {CopyWBounded(reason,420,base);CatWBounded(reason,420,L" Fokuswerte liegen innerhalb der Referenz- und Stabilitätsgrenzen.");}
    CopyWBounded(g_focusNeedReason,240,reason);
    g_focusNeedScore=(int)(ClampD(need,0.0,100.0)+0.5);if(g_focusNeedScore>=85)CopyWBounded(g_focusNeedLabel,96,L"Refokus erforderlich");else if(g_focusNeedScore>=60)CopyWBounded(g_focusNeedLabel,96,L"Refokus empfohlen");else if(g_focusNeedScore>=30)CopyWBounded(g_focusNeedLabel,96,L"leichte Verschlechterung");else CopyWBounded(g_focusNeedLabel,96,L"Fokus stabil");
}
static int CalculateAutofocusQualityScore(double finalFwhm,double finalHfr,int used,double stability){
    double fit=ClampD(g_fitConfidence,0.0,1.0);double r2=ClampD((g_fitR2+g_fitFwhmR2)*0.5,0.0,1.0);double starScore=g_afRunUsesSelectedStar?1.0:ClampD((double)used/20.0,0.0,1.0);double stableScore=ClampD(1.0-stability/0.8,0.0,1.0);double agree=1.0;if(g_afExpectedFwhm>0.0&&finalFwhm>0.0)agree=ClampD(1.0-fabs(finalFwhm-g_afExpectedFwhm)/(g_afExpectedFwhm*0.30),0.0,1.0);double hAgree=1.0;if(g_afExpectedHfr>0.0&&finalHfr>0.0)hAgree=ClampD(1.0-fabs(finalHfr-g_afExpectedHfr)/(g_afExpectedHfr*0.30),0.0,1.0);double score=100.0*(0.36*fit+0.18*r2+0.16*starScore+0.14*stableScore+0.10*agree+0.06*hAgree);int q=(int)(ClampD(score,0.0,100.0)+0.5);if(q>=90)CopyWBounded(g_focusQualityLabel,80,L"sehr gut");else if(q>=78)CopyWBounded(g_focusQualityLabel,80,L"gut");else if(q>=65)CopyWBounded(g_focusQualityLabel,80,L"brauchbar");else if(q>=50)CopyWBounded(g_focusQualityLabel,80,L"niedrig · Kontrolllauf empfohlen");else CopyWBounded(g_focusQualityLabel,80,L"unzureichend");g_focusQualityScore=q;return q;
}
static void EnsureAutoRefocusTemperatureReference(){if(g_autoRefocusEnabled&&g_hasFocuserTemperature&&!g_hasLastAfTemperature){g_lastAfTemperature=g_focuserTemperature;g_hasLastAfTemperature=TRUE;if(g_autoRefocusReferenceReady)lstrcpyW(g_lastAutoRefocusReason,L"Temperaturreferenz übernommen");}}
static void SetAutoRefocusEnabled(BOOL on,BOOL controlAlreadyChanged=FALSE){
    (void)controlAlreadyChanged;
    BOOL was=g_autoRefocusEnabled;g_autoRefocusEnabled=on?TRUE:FALSE;SetChecked(g_autoRefocusCheck,g_autoRefocusEnabled);
    if(g_autoRefocusEnabled&&!was){
        ULONGLONG now=GetTickCount64();g_lastAfCompleted=now;g_autoRefocusRetryAfter=0;g_autoRefocusReferenceReady=FALSE;g_autoRefocusFailureCount=0;g_autoRefocusPaused=FALSE;g_refocusBadFrameStreak=0;
        if(g_hasFocuserTemperature){g_lastAfTemperature=g_focuserTemperature;g_hasLastAfTemperature=TRUE;}else g_hasLastAfTemperature=FALSE;
        EnsureAutoRefocusMeasurementReference();
        if(g_autoRefocusReferenceReady){lstrcpyW(g_lastAutoRefocusReason,L"aktiviert · Referenzmessung übernommen");SetStatus(L"Auto-Refokus aktiviert und bereit");}
        else{lstrcpyW(g_lastAutoRefocusReason,L"wartet auf erste Referenzmessung");SetStatus(L"Auto-Refokus aktiviert · wartet auf erstes geeignetes analysiertes Bild");}
    }else if(!g_autoRefocusEnabled&&was){
        g_autoRefocusRetryAfter=0;g_autoRefocusReferenceReady=FALSE;g_autoRefocusFailureCount=0;g_autoRefocusPaused=FALSE;g_refocusBadFrameStreak=0;lstrcpyW(g_lastAutoRefocusReason,L"deaktiviert");if(!g_afActive)SetStatus(L"Auto-Refokus deaktiviert");
    }
}
static void AutoTuneExposure(){
    if(!g_autoExposureEnabled||!g_frameReady)return;wchar_t v[64];GetWindowTextW(g_exposureEdit,v,64);double ms=800.0;if(!ParseStrictDoubleW(v,&ms)||ms<1.0||ms>60000.0)ms=800.0;
    if(g_usedCount<12&&g_saturatedCount<3)ms*=1.55;else if(g_saturatedCount>g_starCount/8&&g_saturatedCount>2)ms*=0.65;else if(g_usedCount>120)ms*=0.82;
    if(ms<20)ms=20;if(ms>10000)ms=10000;wchar_t out[32];FormatFixed(ms,0,out);SetWindowTextW(g_exposureEdit,out);
}
static BOOL CheckSafeTarget(int target){return target>=g_safeMinPosition&&target<=g_safeMaxPosition;}
static BOOL SaveDiagnostics(){
    BuildDataPath(L"AstroFocusStudio_Diagnostics.txt",g_lastDiagnosticPath,520);
    HANDLE f=CreateFileW(g_lastDiagnosticPath,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if(f==INVALID_HANDLE_VALUE){SetStatus(L"Diagnosebericht konnte nicht angelegt werden");return FALSE;}
    char* b=(char*)Alloc(32768);if(!b){CloseHandle(f);SetStatus(L"Diagnosebericht: nicht genügend Speicher");return FALSE;}
    char sdk[128],cam[300],foc[300],errCode[96],errTitle[320],errDetail[1024],refReason[320],camOp[256],focOp[256];
    WToAscii(g_toupVersion,sdk,128);WToAscii(g_cameraId,cam,300);WToAscii(g_focuserId,foc,300);
    WToAscii(g_lastAfErrorCode,errCode,96);WToAscii(g_lastAfErrorTitle,errTitle,320);WToAscii(g_lastAfErrorDetail,errDetail,1024);
    WToAscii(g_lastAutoRefocusReason,refReason,320);WToAscii(g_cameraWorkerFaultOperation,camOp,256);WToAscii(g_focuserWorkerFaultOperation,focOp,256);
    wchar_t value[64];double timeMinutes=0.0,tempDeltaSetting=0.0;
    GetWindowTextW(g_refocusMinutesEdit,value,64);if(!ParseStrictDoubleW(value,&timeMinutes)||timeMinutes<0.0)timeMinutes=0.0;
    GetWindowTextW(g_refocusTempEdit,value,64);if(!ParseStrictDoubleW(value,&tempDeltaSetting)||tempDeltaSetting<0.0)tempDeltaSetting=0.0;
    ULONGLONG now=GetTickCount64();
    double errorAgeMinutes=g_lastAfErrorTick?(double)(now-g_lastAfErrorTick)/60000.0:0.0;
    double fwhmDegrade=g_lastGoodFwhm>0.0?((g_medianFwhm/g_lastGoodFwhm)-1.0)*100.0:0.0;
    double elapsed=g_lastAfCompleted?(double)(now-g_lastAfCompleted)/60000.0:0.0;
    double nextTime=timeMinutes>0.0?timeMinutes-elapsed:-1.0;if(timeMinutes>0.0&&nextTime<0.0)nextTime=0.0;
    double tempChange=(g_hasFocuserTemperature&&g_hasLastAfTemperature)?fabs(g_focuserTemperature-g_lastAfTemperature):0.0;
    double cooldownRemaining=0.0;if(g_lastAfCompleted&&g_refocusCooldownMinutes>0.0&&elapsed<g_refocusCooldownMinutes)cooldownRemaining=g_refocusCooldownMinutes-elapsed;
    int retrySeconds=now<g_autoRefocusRetryAfter?(int)((g_autoRefocusRetryAfter-now+999)/1000):0;
    int camRetry=now<g_cameraWorkerRetryAfter?(int)((g_cameraWorkerRetryAfter-now+999)/1000):0;
    int focRetry=now<g_focuserWorkerRetryAfter?(int)((g_focuserWorkerRetryAfter-now+999)/1000):0;
    int n=sprintf(b,
        "AstroFocus Studio 3.9.0 Engine\r\n"
        "Kamera=%s\r\nFokussierer=%s\r\nToupTekSDK=%s\r\nSimulator=%d\r\nExternal=%d\r\nNative=%d\r\n"
        "KameraVerbunden=%d\r\nFokussiererVerbunden=%d\r\nBild=%dx%d\r\nFWHM=%.3f\r\nHFR=%.3f\r\n"
        "Sterne=%d/%d\r\nStabilitaet=%.3f\r\nSichereZone=%d..%d\r\nSynthetischeTests=%d/%d\r\n"
        "SimulatorMotorposition=%d\r\nSimulatorOptischePosition=%d\r\nHTTP=%d Port=%d\r\n\r\n"
        "[AutoRefokus]\r\nAktiv=%d\r\nPausiert=%d\r\nFehlversuche=%d\r\nReferenzmessungVorhanden=%d\r\n"
        "Mindeststerne=%d\r\nAktuellVerwendeteSterne=%d\r\n"
        "ZeittriggerAktiv=%d\r\nZeitintervallMinuten=%.3f\r\nNaechsterZeitRefokusMinuten=%.3f\r\n"
        "TemperaturtriggerAktiv=%d\r\nTemperaturSchwelleC=%.3f\r\nTemperaturVerfuegbar=%d\r\nTemperaturreferenzVorhanden=%d\r\nTemperaturAenderungC=%.3f\r\n"
        "FWHMTriggerAktiv=%d\r\nFWHMGrenzwertProzent=%.3f\r\nFWHMReferenz=%.4f\r\nFWHMVerschlechterungProzent=%.2f\r\n"
        "SchlechteBilderSerie=%d/%d\r\nStabilitaetsgrenzePx=%.4f\r\nAktuelleStabilitaetPx=%.4f\r\n"
        "SperrzeitMinuten=%.3f\r\nVerbleibendeSperrzeitMinuten=%.3f\r\nAutomatischerLauf=%d\r\n"
        "LivebildWirdNachFokusFortgesetzt=%d\r\nLivebildWirdNachKamerawiederherstellungFortgesetzt=%d\r\n"
        "LetzterAutoRefokusStatus=%s\r\nRetrySekunden=%d\r\n\r\n"
        "[ASCOM-Geräte-Worker]\r\nKameraWorkerVorhanden=%d\r\nKameraWorkerBlockiert=%d\r\nKameraOperation=%s\r\nKameraWiederherstellungVersuch=%d\r\nKameraRetrySekunden=%d\r\n"
        "FokussiererWorkerVorhanden=%d\r\nFokussiererWorkerBlockiert=%d\r\nFokussiererOperation=%s\r\nFokussiererWiederherstellungVersuch=%d\r\nFokussiererRetrySekunden=%d\r\n"
        "QuarantaenierteWorker=%d\r\nHinweis=ASCOM-Aufrufe laufen in isolierten Gerätehost-Prozessen. Blockiert ein Treiber, wird nur der betroffene Host nach Ablauf seiner Deadline beendet und kontrolliert neu gestartet.\r\n\r\n"
        "[LetzterAutofokusfehler]\r\nCode=%s\r\nTitel=%s\r\nDetail=%s\r\nAutomatischerLauf=%d\r\nAlterMinuten=%.2f\r\n",
        cam,foc,sdk,g_simulatorMode,g_externalCameraMode,g_nativeActive,g_cameraConnected,g_focuserConnected,g_width,g_height,
        g_medianFwhm,g_medianHfr,g_usedCount,g_starCount,FocusStability(),g_safeMinPosition,g_safeMaxPosition,g_selfTestPassed,g_selfTestTotal,
        g_simPosition,g_simOpticalPosition,g_httpEnabled,g_httpPort,
        g_autoRefocusEnabled,g_autoRefocusPaused,g_autoRefocusFailureCount,g_autoRefocusReferenceReady,g_refocusMinStars,g_usedCount,
        timeMinutes>0.0,timeMinutes,nextTime,tempDeltaSetting>0.0,tempDeltaSetting,g_hasFocuserTemperature,g_hasLastAfTemperature,tempChange,
        g_refocusFwhmThresholdPercent>0.0,g_refocusFwhmThresholdPercent,g_lastGoodFwhm,fwhmDegrade,g_refocusBadFrameStreak,g_refocusBadFramesRequired,
        g_refocusStabilityLimit,FocusStability(),g_refocusCooldownMinutes,cooldownRemaining,g_afAutomaticRun,g_resumeLiveAfterAf,g_resumeLiveAfterCameraRecovery,
        refReason,retrySeconds,g_cameraWorker!=0,g_cameraWorkerBlocked,camOp,g_cameraWorkerRecoveryAttempt,camRetry,
        g_focuserWorker!=0,g_focuserWorkerBlocked,focOp,g_focuserWorkerRecoveryAttempt,focRetry,g_orphanWorkerCount,
        errCode,errTitle,errDetail,g_lastAfErrorAutomatic,errorAgeMinutes);
    char seeingA[160],needLabelA[192],needReasonA[512],qualityA[160],fieldA[512],tiltA[128],filterA[96],backlashA[320],sessionA[760],externalA[320];
    WToAscii(g_seeingState,seeingA,160);WToAscii(g_focusNeedLabel,needLabelA,192);WToAscii(g_focusNeedReason,needReasonA,512);WToAscii(g_focusQualityLabel,qualityA,160);WToAscii(g_fieldAdvice,fieldA,512);WToAscii(g_tiltDirection,tiltA,128);WToAscii(g_currentFilter,filterA,96);WToAscii(g_backlashCalResult,backlashA,320);WToAscii(g_sessionPath,sessionA,760);WToAscii(g_lastExternalEvent,externalA,320);
    n+=sprintf(b+n,"\r\n[3.2 Fokusintelligenz]\r\nSeeingIndex=%.2f\r\nSeeingStatus=%s\r\nTransparenzIndex=%.2f\r\nRefokusAmpel=%d/100 %s\r\nRefokusGrund=%s\r\nAutofokusQualitaet=%d/100 %s\r\nTiltKonfidenz=%.2f\r\nTiltRichtung=%s\r\nFeldkruemmungPx=%.4f\r\nFeldAsymmetriePx=%.4f\r\nFeldqualitaet=%.2f\r\nFeldHinweis=%s\r\n\r\n[Profilmodell]\r\nGueltig=%d\r\nErfolgreicheLaeufe=%d\r\nTypischePosition=%d\r\nTypischeFWHM=%.4f\r\nTypischeHFR=%.4f\r\nMittlereQualitaet=%.2f\r\nEmpfohleneSchrittweite=%d\r\nBacklash=%d\r\n\r\n[Temperaturkompensation]\r\nAktiv=%d\r\nAutoStartPosition=%d\r\nDeadbandSchritte=%d\r\nMaxSchritt=%d\r\nVorhersagePosition=%d\r\nTemperaturmodellGueltig=%d\r\nSteigungSchritteProC=%.5f\r\n\r\n[FilterUndEreignisse]\r\nAktuellerFilter=%s\r\nFilterOffsets=%d\r\nFilterRefokusAusstehend=%d\r\nRefokusMeridian=%d\r\nRefokusReconnect=%d\r\nRefokusFilter=%d\r\nRefokusAlleAufnahmen=%d\r\nAufnahmeZaehler=%d\r\nLetztesExternesEreignis=%s\r\n\r\n[BacklashKalibrierung]\r\nAktiv=%d\r\nGeschaetzteSchritte=%d\r\nErgebnis=%s\r\n\r\n[Session]\r\nDatei=%s\r\n",
        g_seeingIndex,seeingA,g_transparencyIndex,g_focusNeedScore,needLabelA,needReasonA,g_focusQualityScore,qualityA,g_tiltConfidence,tiltA,g_fieldCurvature,g_fieldAsymmetry,g_fieldQualityScore,fieldA,g_profileModelValid,g_profileSuccessfulRuns,g_profileTypicalPosition,g_profileTypicalFwhm,g_profileTypicalHfr,g_profileQualityMean,g_profileRecommendedStep,g_profileBacklash,g_tempCompEnabled,g_autoStartPositionEnabled,g_tempCompDeadbandSteps,g_tempCompMaxStep,g_lastTempCompTarget,g_tempFitValid,g_tempSlope,filterA,g_filterOffsetCount,g_filterRefocusPending,g_refocusOnMeridian,g_refocusOnReconnect,g_refocusOnFilter,g_refocusEveryCaptures,g_captureEventCounter,externalA,g_backlashCalActive,g_backlashCalEstimated,backlashA,sessionA);
    BOOL ok=n>0&&n<32768&&WriteAllHandle(f,b,(DWORD)n);
    Free(b);CloseHandle(f);SetStatus(ok?L"Diagnosebericht gespeichert":L"Diagnosebericht konnte nicht vollständig geschrieben werden");return ok;
}
static const char g_webUi[] = R"CAFHTML(<!doctype html><html lang="de"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>AstroFocus Studio 3.9.0 Engine</title><style>
:root{color-scheme:dark;--bg:#08111d;--panel:#101c2b;--panel2:#142236;--line:#263a55;--text:#eef4ff;--muted:#93a5be;--accent:#54a4ff;--good:#66dda3;--warn:#ffc85a;--bad:#ff6b77}*{box-sizing:border-box}body{margin:0;background:radial-gradient(circle at 50% -20%,#17345a 0,#08111d 42%);color:var(--text);font:14px/1.35 Segoe UI,Arial,sans-serif;min-width:1180px}button,input,select{font:inherit}header{height:62px;display:flex;align-items:center;gap:18px;padding:0 20px;border-bottom:1px solid var(--line);background:#0c1725e8;position:sticky;top:0;z-index:20;backdrop-filter:blur(12px)}h1{font-size:21px;margin:0;white-space:nowrap}.pill{padding:7px 11px;border:1px solid var(--line);border-radius:999px;color:var(--muted);background:#101b2a}.pill.on{color:#cffff0;border-color:#276449;background:#123527}.spacer{flex:1}.profile{width:320px}.app{display:grid;grid-template-columns:285px minmax(600px,1fr) 365px;gap:14px;padding:14px;height:calc(100vh - 62px)}.col{min-height:0;overflow:auto}.card{background:linear-gradient(180deg,#132238,#0e1928);border:1px solid var(--line);border-radius:12px;padding:14px;margin-bottom:12px;box-shadow:0 14px 28px #0004}.card h2{font-size:12px;letter-spacing:.09em;margin:0 0 12px;color:#c3d2e7}.row{display:flex;align-items:center;gap:8px;margin:8px 0}.row label{color:var(--muted);min-width:94px}.grow{flex:1}input,select{width:100%;background:#0a1523;border:1px solid #304766;color:var(--text);border-radius:7px;padding:8px 10px;outline:none}input:focus,select:focus{border-color:var(--accent);box-shadow:0 0 0 2px #54a4ff22}button{border:1px solid #365779;color:#eef6ff;background:linear-gradient(#214b78,#17395d);border-radius:8px;padding:9px 12px;cursor:pointer;white-space:nowrap}button:hover{filter:brightness(1.12)}button:disabled{opacity:.42;cursor:not-allowed;filter:none}button.secondary{background:#14243a}button.danger{background:#5d2630;border-color:#89414d}button.primary{background:linear-gradient(#2b79c8,#205e9f);font-weight:650}.checks{display:grid;grid-template-columns:1fr 1fr;gap:8px;color:#c4d1e4}.checks label{display:flex;align-items:center;gap:7px}.checks input{width:auto}.viewer{height:55vh;min-height:410px;background:#02070d;border:1px solid #2b4160;border-radius:12px;display:grid;place-items:center;position:relative;overflow:hidden}.viewer img{width:100%;height:100%;object-fit:contain;image-rendering:auto}.viewer .empty{color:#6f829c}.overlay{position:absolute;top:12px;right:12px}.tabs{display:flex;gap:6px;margin-top:12px;border-bottom:1px solid var(--line)}.tab{background:transparent;border:0;border-radius:7px 7px 0 0;color:#92a7c2;padding:11px 14px}.tab.active{color:#fff;background:#14253a;border-bottom:2px solid var(--accent)}.pane{display:none;padding-top:12px}.pane.active{display:block}.autogrid{display:grid;grid-template-columns:210px 210px minmax(300px,1fr);gap:12px}.chart{height:250px;background:#07111d;border:1px solid var(--line);border-radius:10px;width:100%}.metric{display:grid;grid-template-columns:1fr auto;gap:6px 12px;color:var(--muted)}.metric b{color:#fff}.starbox{height:115px;border:1px solid var(--line);border-radius:9px;background:#060d17;display:grid;place-items:center;color:#71839c}.zones{display:grid;grid-template-columns:repeat(3,1fr);gap:5px}.zone{height:48px;border:1px solid var(--line);border-radius:6px;display:grid;place-items:center;color:#ffd77d;background:#0b1624}.statusbar{position:fixed;bottom:0;left:0;right:0;height:28px;background:#0b1522;border-top:1px solid var(--line);padding:5px 16px;color:#9db0c8;z-index:30}.log{height:210px;overflow:auto;background:#07111d;border:1px solid var(--line);padding:10px;border-radius:8px;color:#a9bad0;font-family:Consolas,monospace}.small{font-size:12px;color:var(--muted)}@media(max-width:1450px){body{min-width:1050px}.app{grid-template-columns:260px minmax(520px,1fr) 320px}.profile{width:240px}.autogrid{grid-template-columns:190px 190px minmax(220px,1fr)}}
</style></head><body><header><h1>AstroFocus Studio <span style="color:#77baff">3.9.0 Engine</span></h1><span id="camPill" class="pill">○ Kamera</span><span id="focPill" class="pill">○ Fokussierer</span><span id="afPill" class="pill">Autofokus bereit</span><div class="spacer"></div><input id="profile" class="profile" value="Standardprofil"><button class="secondary" onclick="applyProfile()">Profil speichern</button></header>
<div class="app"><aside class="col">
<section class="card"><h2>GERÄTE</h2><div class="row"><label>Kamera</label><input id="cameraName" readonly placeholder="Nicht ausgewählt"></div><div class="row"><button onclick="act('camera-select')">Auswählen / erkennen</button><button id="camBtn" class="primary grow" onclick="act('camera-connect')">Verbinden</button></div><div class="row"><label>Fokussierer</label><input id="focuserName" readonly placeholder="Nicht ausgewählt"></div><div class="row"><button onclick="act('focuser-select')">Auswählen …</button><button id="focBtn" class="primary grow" onclick="act('focuser-connect')">Verbinden</button></div><div class="checks"><label><input id="native" type="checkbox" onchange="toggle('native',this.checked)">ToupTek direkt</label><label><input id="reconnect" type="checkbox" onchange="toggle('reconnect',this.checked)">Auto-Wiederverbinden</label><label><input id="simulator" type="checkbox" onchange="toggle('simulator',this.checked)">Vollständiger Simulator</label></div><div class="small">Simuliert Kamera, absoluten Fokussierer und Fokusdrift.</div></section>
<section class="card"><h2>AUFNAHME</h2><div class="row"><label>Belichtung [ms]</label><input id="exposure" type="number" min="1" max="60000" step="1" required></div><div class="row"><label>Gain</label><input id="gain" type="number" min="0" max="65535" step="1" required></div><button class="primary" style="width:100%" onclick="liveAction()" id="liveBtn">Live-Fokus starten</button><div class="checks" style="margin-top:12px"><label><input id="demo" type="checkbox" onchange="toggle('demo',this.checked)">Demo-Bildquelle</label><label><input id="stretch" type="checkbox" onchange="toggle('stretch',this.checked)">Auto-Stretch</label><label><input id="stars" type="checkbox" onchange="toggle('stars',this.checked)">Sterne</label><label><input id="values" type="checkbox" onchange="toggle('values',this.checked)">Werte</label><label><input id="saturation" type="checkbox" onchange="toggle('saturation',this.checked)">Sättigung</label><label><input id="zones" type="checkbox" onchange="toggle('zones',this.checked)">9-Zonen</label></div></section>
<section class="card"><h2>FOKUSSIERER</h2><div class="metric"><span>Position</span><b id="position">–</b><span>Temperatur</span><b id="temperature">–</b></div><div class="row"><label>Schrittweite</label><input id="manualStep" type="number" min="1"></div><div class="row"><button onclick="moveAction('move-in')">◀ Innen</button><button onclick="moveAction('move-out')">Außen ▶</button><button class="danger" onclick="act('halt')">■ Stopp</button></div><label class="row"><input id="bahtinov" style="width:auto" type="checkbox" onchange="toggle('bahtinov',this.checked)">Bahtinov-Auswertung aktivieren</label></section>
</aside>
<main class="col"><div class="viewer"><img id="frame" alt="Livebild"><div id="empty" class="empty">Livebild starten oder Demo-Bildquelle aktivieren</div><button class="secondary overlay" onclick="cycleOverlay()" id="overlayBtn">Overlay: Analyse</button></div>
<nav class="tabs"><button class="tab active" data-pane="live">Live-Fokus</button><button class="tab" data-pane="auto">Autofokus</button><button class="tab" data-pane="baht">Bahtinov</button><button class="tab" data-pane="logs">Protokoll</button><button class="tab" data-pane="advanced">Erweitert</button></nav>
<section id="live" class="pane active"><div class="card"><h2>LIVE-FOKUS-TREND</h2><canvas id="trend" class="chart"></canvas></div></section>
<section id="auto" class="pane"><div class="autogrid"><div class="card"><h2>AUTOFOKUS-PARAMETER</h2><div class="row"><label>Punkte</label><select id="afPoints"><option>5</option><option>7</option><option selected>9</option><option>11</option><option>13</option><option>15</option></select></div><div class="row"><label>Schritt</label><input id="afStep" type="number" min="5" max="1000000" step="1" required></div><div class="row"><label>Samples</label><select id="afSamples"><option>1</option><option>2</option><option selected>3</option><option>4</option><option>5</option></select></div><div class="row"><label>Backlash</label><input id="backlash" type="number" min="0" max="1000000" step="1" required></div><div id="afValidationWeb" class="small">Parameter werden geprüft …</div><label class="row"><input id="preferredOut" style="width:auto" type="checkbox" onchange="toggle('preferredOut',this.checked)">Finale Richtung nach außen</label></div><div class="card"><h2>AKTIONEN</h2><button style="width:100%;margin-bottom:10px" onclick="afAction('step-assist')">Schritt-Assistent</button><button style="width:100%;margin-bottom:10px" onclick="afAction('backlash-calibrate')">Backlash automatisch kalibrieren</button><button id="afStartWeb" class="primary" style="width:100%;margin-bottom:10px" onclick="afAction('autofocus-start')">Autofokus starten</button><button class="danger" style="width:100%" onclick="act('autofocus-stop')">Autofokus abbrechen</button></div><div class="card"><h2>AUTOFOKUSKURVE</h2><canvas id="afChart" class="chart"></canvas><div id="afStatsWeb" class="small" style="margin-top:9px;min-height:34px;white-space:normal">Noch keine statistische Kurvenauswertung.</div></div><div class="card"><h2>AUTOFOKUSDIAGNOSE</h2><div id="afDiagnosisWeb" class="small">Kein Autofokusfehler gespeichert.</div></div></div></section>
<section id="baht" class="pane"><div class="card"><h2>BAHTINOV-FOKUSHILFE</h2><div class="metric"><span>Offset</span><b id="bahtOffset">–</b><span>Konfidenz</span><b id="bahtConf">–</b><span>Schärfescore</span><b id="sharpness">–</b></div><p class="small">Einen hellen Stern im Livebild auswählen und die Bahtinov-Auswertung aktivieren.</p></div></section>
<section id="logs" class="pane"><div class="card"><h2>PROTOKOLL, DIAGNOSE UND SYNTHETISCHE TESTS</h2><div class="row"><button onclick="act('diagnostics')">Diagnosebericht speichern</button><button onclick="act('export')">CSV/SVG-Bericht speichern</button><button class="primary" onclick="runSelfTest()">Synthetische Tests ausführen</button></div><div class="metric" style="margin:12px 0"><span>Letzter Testlauf</span><b id="selfTestCount">Noch nicht ausgeführt</b><span>Ergebnis</span><b id="selfTestSummary">–</b></div><div id="log" class="log">Bereit.</div></div></section>
<section id="advanced" class="pane"><div class="card"><h2>AUTO-REFOKUS UND SICHERHEIT</h2><div class="checks"><label><input id="autoRefocus" type="checkbox" onchange="toggle('autoRefocus',this.checked)">Auto-Refokus</label><label><input id="httpEnabled" type="checkbox" checked disabled>Lokale API aktiv</label></div><div class="row"><label>Zeit [min]</label><input id="refocusMinutes" type="number" min="0" step="0.1"><label>Temperatur ΔT [°C]</label><input id="refocusTemp" type="number" min="0" step="0.1"></div><div class="row"><label>FWHM-Grenze [%]</label><input id="refocusFwhmPercent" type="number" min="0" max="500" step="0.1"><label>Schlechte Bilder</label><input id="refocusBadFrames" type="number" min="1" max="100" step="1"></div><div class="row"><label>Mindeststerne</label><input id="refocusMinStars" type="number" min="1" max="160" step="1"><label>Stabilität [px]</label><input id="refocusStability" type="number" min="0.01" max="20" step="0.01"></div><div class="row"><label>Sperrzeit [min]</label><input id="refocusCooldown" type="number" min="0" max="1440" step="0.1"><label>Sichere Zone</label><input id="safeMin" type="number"><span>bis</span><input id="safeMax" type="number"></div><div class="row"><button onclick="saveAdvanced()">Einstellungen speichern</button><button id="autoRefocusResumeWeb" class="secondary" onclick="act('auto-refocus-resume')" disabled>Auto-Refokus freigeben</button><button class="danger" onclick="shutdownApp()">Programm beenden</button></div><div id="autoRefocusStatusWeb" class="log" style="height:auto;min-height:220px;margin-top:12px;white-space:pre-wrap">Auto-Refokus-Status wird geladen …</div><h2 style="margin-top:18px">FOKUSINTELLIGENZ 3.1</h2><div class="checks"><label><input id="tempComp" type="checkbox" onchange="toggle('tempComp',this.checked)">Temperaturkompensation</label><label><input id="autoStartPosition" type="checkbox" onchange="toggle('autoStartPosition',this.checked)">Automatische Startposition</label><label><input id="refocusOnMeridian" type="checkbox" onchange="toggle('refocusOnMeridian',this.checked)">Refokus nach Meridian-Flip</label><label><input id="refocusOnReconnect" type="checkbox" onchange="toggle('refocusOnReconnect',this.checked)">Refokus nach Reconnect</label><label><input id="refocusOnFilter" type="checkbox" onchange="toggle('refocusOnFilter',this.checked)">Refokus bei Filterwechsel</label></div><div class="row"><label>Temp.-Totzone</label><input id="tempCompDeadband" type="number" min="1" max="5000" step="1"><label>Max. Temp.-Schritt</label><input id="tempCompMaxStep" type="number" min="1" max="10000" step="1"></div><div class="row"><label>Refokus alle Aufn.</label><input id="refocusEveryCaptures" type="number" min="0" max="100000" step="1"><label>Filter</label><input id="filterName" maxlength="31" placeholder="z. B. Ha"></div><div class="row"><button onclick="filterAction('filter-learn')">Filteroffset lernen</button><button onclick="filterAction('filter-apply')">Filteroffset anwenden</button><button onclick="act('event-meridian')">Meridian-Ereignis</button><button onclick="act('capture-complete')">Aufnahmeereignis</button></div><div id="focusIntelligenceWeb" class="log" style="height:auto;min-height:180px;margin-top:12px;white-space:pre-wrap">Fokusintelligenz wird geladen …</div><p class="small">Filteroffsets werden derzeit über Filtername/API verwaltet; eine direkte ASCOM-Filterrad-Anbindung ist nicht Bestandteil dieser Version. Die Oberfläche und API sind nur über 127.0.0.1 erreichbar. Ein blockierender ASCOM-Treiber wird in einem isolierten Geräte-Worker erkannt und mit Zeitüberschreitung aus dem Hauptablauf entfernt.</p></div></section>
</main>
<aside class="col"><section class="card"><h2>AKTUELLE ANALYSE</h2><div class="metric"><span>Median-FWHM</span><b id="fwhm">–</b><span>Median-HFR</span><b id="hfr">–</b><span>Verwendete Sterne</span><b id="usedStars">–</b><span>SNR (Median)</span><b id="snr">–</b><span>Exzentrizität</span><b id="ecc">–</b><span>Stabilität</span><b id="stability">–</b></div></section><section class="card"><h2>AUSGEWÄHLTER FOKUSSTERN</h2><div class="starbox">Stern im Livebild anklicken</div><div class="metric" style="margin-top:10px"><span>FWHM</span><b id="starFwhm">–</b><span>HFR</span><b id="starHfr">–</b><span>SNR</span><b id="starSnr">–</b><span>Exz.</span><b id="starEcc">–</b></div></section><section class="card"><h2>BILDFELD · MEDIAN FWHM</h2><div id="miniZones" class="zones"></div><p class="small" id="tiltText">Tilt: noch keine Daten</p></section></aside></div><div class="statusbar" id="status">Bereit</div>
<script>
const $=id=>document.getElementById(id);let initialized=false,trend=[],af=[],lastState={},lastTrendFrame=-1;function log(t){$('log').textContent=new Date().toLocaleTimeString()+'  '+t+'\n'+$('log').textContent.slice(0,6000)}async function api(path){try{let r=await fetch(path,{cache:'no-store'});if(!r.ok)throw new Error('HTTP '+r.status);return await r.json()}catch(e){$('status').textContent='Verbindung zum lokalen Dienst unterbrochen';log('Fehler: '+e.message);return null}}async function act(name){let j=await api('/api/action?name='+encodeURIComponent(name));if(!j)return false;log((j.ok?'':'Fehler: ')+(j.message||name));await refresh();return !!j.ok}async function filterAction(name){let f=$('filterName').value.trim();if(!f){log('Fehler: Filtername fehlt');return false}let j=await api('/api/action?name='+encodeURIComponent(name)+'&filterName='+encodeURIComponent(f));if(!j)return false;log((j.ok?'':'Fehler: ')+(j.message||name));await refresh();return !!j.ok}async function runSelfTest(){log('Synthetische Tests laufen …');await act('selftest')}async function toggle(name,val){let j=await api('/api/toggle?name='+encodeURIComponent(name)+'&value='+(val?1:0));if(!j||!j.ok)log('Fehler: '+((j&&j.message)||'Einstellung nicht übernommen'));await refresh();return !!(j&&j.ok)}async function setv(name,val){let j=await api('/api/set?name='+encodeURIComponent(name)+'&value='+encodeURIComponent(val));if(!j||!j.ok)log('Fehler: '+((j&&j.message)||('Wert '+name+' nicht übernommen')));return !!(j&&j.ok)}function afInputError(){let exposure=Number($('exposure').value),gain=Number($('gain').value),points=Number($('afPoints').value),step=Number($('afStep').value),samples=Number($('afSamples').value),backlash=Number($('backlash').value);if(!Number.isFinite(exposure)||exposure<1||exposure>60000)return 'Belichtung muss zwischen 1 und 60000 ms liegen.';if(!Number.isInteger(gain)||gain<0||gain>65535)return 'Gain muss eine ganze Zahl zwischen 0 und 65535 sein.';if(![5,7,9,11,13,15].includes(points))return 'Messpunkte müssen 5, 7, 9, 11, 13 oder 15 sein.';if(!Number.isInteger(step)||step<5||step>1000000)return 'Schrittweite muss eine ganze Zahl zwischen 5 und 1000000 sein.';if(!Number.isInteger(samples)||samples<1||samples>5)return 'Samples müssen eine ganze Zahl zwischen 1 und 5 sein.';if(!Number.isInteger(backlash)||backlash<0||backlash>1000000)return 'Backlash muss eine ganze Zahl zwischen 0 und 1000000 sein.';return ''}function validateAfInputs(){let err=afInputError(),v=$('afValidationWeb'),b=$('afStartWeb');if(v)v.textContent=err?'Parameterfehler: '+err:'Parameter gültig.';if(b)b.disabled=!!err||!!lastState.autofocus;return !err}async function saveCapture(){return await setv('exposure',$('exposure').value)&&await setv('gain',$('gain').value)}async function saveManual(){return await setv('manualStep',$('manualStep').value)}async function saveAf(){if(!validateAfInputs())return false;for(const n of ['afPoints','afStep','afSamples','backlash'])if(!await setv(n,$(n).value))return false;return true}async function liveAction(){if(await saveCapture())await act('live')}async function moveAction(name){if(await saveManual())await act(name)}async function afAction(name){if(name==='autofocus-start'){if(!validateAfInputs()){log('Fehler: '+afInputError());return}if(!confirm('Autofokus mit den eingestellten Messpunkten jetzt starten?'))return;let q='/api/action?name=autofocus-start&confirmed=1&exposure='+encodeURIComponent($('exposure').value)+'&gain='+encodeURIComponent($('gain').value)+'&afPoints='+encodeURIComponent($('afPoints').value)+'&afStep='+encodeURIComponent($('afStep').value)+'&afSamples='+encodeURIComponent($('afSamples').value)+'&backlash='+encodeURIComponent($('backlash').value)+'&preferredOut='+($('preferredOut').checked?1:0)+'&afSelectedStar='+(lastState.afUseSelectedStar?1:0);let j=await api(q);if(j)log((j.ok?'':'Fehler: ')+(j.message||name));await refresh();return}if(await saveCapture()&&await saveAf())await act(name)}async function saveAdvanced(){let mn=Number($('safeMin').value),mx=Number($('safeMax').value);if(!Number.isInteger(mn)||!Number.isInteger(mx)||mn<0||mx<=mn){log('Fehler: sichere Fokuszone ist ungültig');return false}for(const n of ['refocusMinutes','refocusTemp','refocusFwhmPercent','refocusBadFrames','refocusMinStars','refocusStability','refocusCooldown','tempCompDeadband','tempCompMaxStep','refocusEveryCaptures'])if(!await setv(n,$(n).value))return false;let ok;if(mn>=(lastState.safeMax??0))ok=await setv('safeMax',$('safeMax').value)&&await setv('safeMin',$('safeMin').value);else ok=await setv('safeMin',$('safeMin').value)&&await setv('safeMax',$('safeMax').value);log(ok?'Erweiterte Einstellungen gespeichert':'Fehler: erweiterte Einstellungen nicht vollständig gespeichert');await refresh();return ok}async function applyProfile(){let n=$('profile').value.trim();if(!n){log('Fehler: Profilname fehlt');return}let j=await api('/api/action?name=profile-save&profileName='+encodeURIComponent(n));if(j)log((j.ok?'':'Fehler: ')+(j.message||'Profil speichern'));await refresh()}async function cycleOverlay(){await act('overlay-cycle')}async function shutdownApp(){if(await act('shutdown'))setTimeout(()=>window.close(),250)}
function chart(canvas,data,label){let dpr=devicePixelRatio||1,w=canvas.clientWidth,h=canvas.clientHeight;canvas.width=w*dpr;canvas.height=h*dpr;let c=canvas.getContext('2d');c.scale(dpr,dpr);c.clearRect(0,0,w,h);c.strokeStyle='#233a58';c.lineWidth=1;for(let i=1;i<5;i++){let y=i*h/5;c.beginPath();c.moveTo(0,y);c.lineTo(w,y);c.stroke()}c.fillStyle='#91a6bf';c.font='12px Segoe UI';c.fillText(label,10,18);if(data.length<2)return;let vals=data.map(x=>x.y).filter(Number.isFinite),mn=Math.min(...vals),mx=Math.max(...vals);if(mx<=mn)mx=mn+1;c.strokeStyle='#58a8ff';c.lineWidth=2;c.beginPath();data.forEach((p,i)=>{let x=12+i*(w-24)/(data.length-1),y=h-18-(p.y-mn)*(h-42)/(mx-mn);i?c.lineTo(x,y):c.moveTo(x,y)});c.stroke()}
function retryClock(seconds){let d=new Date(Date.now()+Math.max(0,seconds||0)*1000);return d.toLocaleTimeString([], {hour:'2-digit',minute:'2-digit',second:'2-digit'})}
function autoRefocusText(j){
 const lines=[];
 if(!j.autoRefocus){lines.push('Status: Auto-Refokus deaktiviert','Die Automatik löst keine Fokusläufe aus.');return lines.join('\n')}
 if(j.autoRefocusAutomaticRun)lines.push('Status: Refokus wird gerade ausgeführt','Auslöser: '+(j.autoRefocusLastReason||'automatische Bedingung'),j.autoRefocusLiveWillResume?'Livebild wird anschließend fortgesetzt.':'Livebild war vor dem Lauf nicht aktiv.');
 else if(j.autoRefocusPaused)lines.push('Status: Nach wiederholten Fehlern pausiert','Retryfolge 30 / 60 / 120 / 300 s ausgeschöpft.','Eine sichtbare Benutzerfreigabe ist erforderlich.');
 else if(j.autoRefocusRetrySeconds>0)lines.push('Status: Letzter Versuch fehlgeschlagen','Fehlversuch '+Number(j.autoRefocusFailureCount||0)+' von 4','Erneuter Versuch um '+retryClock(j.autoRefocusRetrySeconds)+' Uhr ('+j.autoRefocusRetrySeconds+' s).','Grund: '+(j.autofocusErrorTitle||j.autoRefocusLastReason||'unbekannt'));
 else if(!j.autoRefocusTimeEnabled&&!j.autoRefocusTemperatureEnabled&&!j.autoRefocusFwhmEnabled)lines.push('Status: Aktiv, aber ohne Auslöser','Aktiviere mindestens Zeit-, Temperatur- oder FWHM-Trigger.');
 else if(!j.autoRefocusReferenceReady)lines.push('Status: Aktiv · wartet auf erste Referenzmessung','Benötigt wird ein analysiertes Bild mit mindestens '+Number(j.refocusMinStars||4)+' geeigneten Sternen.');
 else if(!j.camera||!j.focuser)lines.push('Status: Aktiv, aber nicht bereit',(!j.camera?'Kamera nicht verbunden. ': '')+(!j.focuser?'Fokussierer nicht verbunden.':''));
 else lines.push('Status: Aktiv und bereit');
 lines.push('');
 lines.push(j.autoRefocusTimeEnabled?'Zeittrigger: aktiv · nächster Refokus in '+Number(j.autoRefocusNextMinutes||0).toFixed(1)+' min':'Zeittrigger: deaktiviert');
 if(!j.autoRefocusTemperatureEnabled)lines.push('Temperaturtrigger: deaktiviert');
 else if(!j.hasTemperature)lines.push('Temperaturtrigger: aktiv, aber keine Temperatur verfügbar');
 else lines.push('Temperaturtrigger: aktiv · Änderung seit Referenz '+Number(j.autoRefocusTempDelta||0).toFixed(1)+' °C');
 if(!j.autoRefocusFwhmEnabled)lines.push('FWHM-Trigger: deaktiviert');
 else lines.push('FWHM-Trigger: aktiv · Grenze '+Number(j.refocusFwhmPercent||0).toFixed(1)+' % · Verschlechterung '+Number(j.autoRefocusFwhmDegradePercent||0).toFixed(1)+' % · Serie '+Number(j.autoRefocusBadFrameStreak||0)+'/'+Number(j.refocusBadFrames||0));
 lines.push('Mindeststerne: '+Number(j.refocusMinStars||0)+' · Stabilitätsgrenze: '+Number(j.refocusStability||0).toFixed(2)+' px');
 lines.push(j.autoRefocusCooldownRemainingMinutes>0?'Sperrzeit: noch '+Number(j.autoRefocusCooldownRemainingMinutes).toFixed(1)+' min':'Sperrzeit: frei');
 if(j.cameraWorkerBlocked)lines.push('Kamera-Worker blockiert bei „'+(j.cameraWorkerOperation||'unbekannt')+'“ · wartet auf Freigabe des Treibers');
 if(j.focuserWorkerBlocked)lines.push('Fokussierer-Worker blockiert bei „'+(j.focuserWorkerOperation||'unbekannt')+'“ · wartet auf Freigabe des Treibers');
 return lines.join('\n')
}
function autofocusChart(canvas,j){
 let dpr=devicePixelRatio||1,w=Math.max(320,canvas.clientWidth),h=Math.max(190,canvas.clientHeight);canvas.width=w*dpr;canvas.height=h*dpr;let c=canvas.getContext('2d');c.setTransform(dpr,0,0,dpr,0,0);c.clearRect(0,0,w,h);
 let xs=j.afPositions||[],hm=j.afMetrics||[],fm=j.afFwhmMetrics||[],hs=j.afMetricSigma||[],fs=j.afFwhmSigma||[],out=j.afOutliers||[],res=j.afResiduals||[];let n=Math.min(xs.length,hm.length,j.afMeasuredCount||xs.length);if(n<1){c.fillStyle='#91a6bf';c.font='12px Segoe UI';c.fillText('Noch keine Autofokusmessung',16,28);return}
 let pmin=Math.min(...xs),pmax=Math.max(...xs);if(!(pmax>pmin))pmax=pmin+1;let detailed=h>=255,rb=detailed?48:0,L=48,R=16,T=38,B=30+rb,pb=h-B;
 function clamp(v,lo,hi){return Math.max(lo,Math.min(hi,v))}
 function evalModel(model,p,pos,qa,qb,qc){let scale=Number(j.afFitScale)||1,x=(pos-(Number(j.afFitCenter)||0))/scale;if(model===2||model===3){let width=Math.max(.000001,Math.abs(Number(p?.[3])||0)),dx=x-(Number(p?.[2])||0),base=Math.sqrt(dx*dx+width*width)-width;if(model===3)base+=(Number(p?.[4])||0)*dx;return (Number(p?.[0])||0)+(Number(p?.[1])||0)*base}return model===1?(Number(p?.[0])||0)*x*x+(Number(p?.[1])||0)*x+(Number(p?.[2])||0):(Number(qa)||0)*x*x+(Number(qb)||0)*x+(Number(qc)||0)}
 let vals=[];for(let k=0;k<n;k++){if(hm[k]>0){vals.push(hm[k]-(hs[k]||0),hm[k]+(hs[k]||0))}if(fm[k]>0){vals.push(fm[k]-(fs[k]||0),fm[k]+(fs[k]||0))}}for(let k=0;k<=100;k++){let pos=pmin+(pmax-pmin)*k/100;if(j.afFitValid)vals.push(evalModel(j.afFitModel,j.afFitParams,pos,j.afFitA,j.afFitB,j.afFitC));if(j.afFitFwhmValid)vals.push(evalModel(j.afFitFwhmModel,j.afFitFwhmParams,pos,j.afFitFwhmA,j.afFitFwhmB,j.afFitFwhmC))}
 vals=vals.filter(v=>Number.isFinite(v)&&v>0);let mn=vals.length?Math.min(...vals):0,mx=vals.length?Math.max(...vals):1;if(!(mx>mn))mx=mn+1;let pad=(mx-mn)*.14;mn=Math.max(0,mn-pad);mx+=pad;
 let X=v=>L+(v-pmin)*(w-L-R)/(pmax-pmin),Y=v=>pb-(v-mn)*(pb-T)/(mx-mn);
 if(j.afFitValid&&Number(j.afFocusSigma)>0){let lo=clamp(X((j.afBestPosition||0)-j.afFocusSigma),L,w-R),hi=clamp(X((j.afBestPosition||0)+j.afFocusSigma),L,w-R);if(hi<lo)[lo,hi]=[hi,lo];c.fillStyle='rgba(255,200,90,.10)';c.fillRect(lo,T,Math.max(1,hi-lo),pb-T);c.save();c.setLineDash([4,4]);c.strokeStyle='#ffc85a';for(const xx of [lo,hi]){c.beginPath();c.moveTo(xx,T);c.lineTo(xx,pb);c.stroke()}c.restore()}
 c.strokeStyle='#233a58';c.lineWidth=1;for(let k=0;k<=4;k++){let yy=T+k*(pb-T)/4;c.beginPath();c.moveTo(L,yy);c.lineTo(w-R,yy);c.stroke();let xx=L+k*(w-L-R)/4;c.beginPath();c.moveTo(xx,T);c.lineTo(xx,pb);c.stroke()}
 c.fillStyle='#91a6bf';c.font='11px Segoe UI';c.fillText('HFR grün · FWHM blau · ±1σ-Fehlerbalken · rotes × Ausreißer · □ Kontrollmedian',L,16);c.fillText(mx.toFixed(2),4,T+4);c.fillText(mn.toFixed(2),4,pb);c.fillText(String(pmin),L,pb+18);let tx=String(pmax);c.fillText(tx,w-R-c.measureText(tx).width,pb+18);
 function curve(model,p,qa,qb,qc,color){c.strokeStyle=color;c.lineWidth=2;c.beginPath();for(let k=0;k<=150;k++){let pos=pmin+(pmax-pmin)*k/150,xx=X(pos),yy=clamp(Y(evalModel(model,p,pos,qa,qb,qc)),T,pb);k?c.lineTo(xx,yy):c.moveTo(xx,yy)}c.stroke()}
 if(j.afFitValid)curve(j.afFitModel,j.afFitParams,j.afFitA,j.afFitB,j.afFitC,'#66dda3');if(j.afFitFwhmValid)curve(j.afFitFwhmModel,j.afFitFwhmParams,j.afFitFwhmA,j.afFitFwhmB,j.afFitFwhmC,'#54a4ff');
 function point(x,y,sigma,color,isOut,r,xOffset){if(!(y>0))return;let xx=clamp(X(x)+xOffset,L+r+2,w-R-r-2),yy=clamp(Y(y),T+1,pb-1),rawSigma=Math.max(0,Number(sigma)||0),sy=rawSigma>0?Math.abs(Y(y+rawSigma)-Y(y)):0;if(sy>0)sy=Math.max(sy,r+3);sy=Math.min(sy,(pb-T)/3);c.strokeStyle=isOut?'#ff6b77':color;c.lineWidth=isOut?2.2:1.8;if(sy>0){let y1=clamp(yy-sy,T,pb),y2=clamp(yy+sy,T,pb);c.beginPath();c.moveTo(xx,y1);c.lineTo(xx,y2);c.moveTo(xx-4,y1);c.lineTo(xx+4,y1);c.moveTo(xx-4,y2);c.lineTo(xx+4,y2);c.stroke()}c.beginPath();if(isOut){let cr=r+3;c.moveTo(xx-cr,yy-cr);c.lineTo(xx+cr,yy+cr);c.moveTo(xx-cr,yy+cr);c.lineTo(xx+cr,yy-cr)}else c.arc(xx,yy,r,0,Math.PI*2);c.stroke()}
 for(let k=0;k<n;k++){point(xs[k],hm[k],hs[k],'#66dda3',!!out[k],4,-3);point(xs[k],fm[k],fs[k],'#54a4ff',!!out[k],5,3)}
 if(j.afFitValid){let bx=clamp(X(j.afBestPosition||0),L,w-R);c.strokeStyle='#ff6b77';c.beginPath();c.moveTo(bx,T);c.lineTo(bx,pb);c.stroke()}
 if(detailed){let rt=pb+26,rbot=h-4,zero=(rt+rbot)/2,rm=Math.max(.25,...res.slice(0,n).map(v=>Math.abs(Number(v)||0)));c.strokeStyle='#233a58';c.beginPath();c.moveTo(L,zero);c.lineTo(w-R,zero);c.stroke();for(let k=0;k<n;k++){let xx=clamp(X(xs[k]),L,w-R),yy=clamp(zero-(Number(res[k])||0)*(rbot-rt-5)/2/rm,rt,rbot);c.strokeStyle=out[k]?'#ff6b77':'#93a5be';c.beginPath();c.moveTo(xx,zero);c.lineTo(xx,yy);c.stroke()}c.fillStyle='#91a6bf';c.fillText('Standardisierte HFR-Residuen',w-R-158,rt+11)}
}
function focusIntelligenceText(j){const p=[];p.push('Refokus-Ampel: '+(j.focusNeedLabel||'–')+' ('+(j.focusNeedScore??0)+'/100)',j.focusNeedReason||'');p.push('Seeing: '+(j.seeingState||'–')+' · Index '+Number(j.seeingIndex||0).toFixed(0)+'/100 · Transparenz '+Number(j.transparencyIndex||0).toFixed(0)+'/100');p.push('Letzter Autofokus: '+(j.afQualityLabel||'–')+' · '+(j.afQualityScore??0)+'/100');p.push('Bildfeld: '+Number(j.fieldQualityScore||0).toFixed(0)+'/100 · Krümmung '+Number(j.fieldCurvature||0).toFixed(2)+' px · Asymmetrie '+Number(j.fieldAsymmetry||0).toFixed(2)+' px',j.fieldAdvice||'');p.push('Profilmodell: '+(j.profileModelValid?((j.profileSuccessfulRuns||0)+' Läufe · Pos '+j.profileTypicalPosition+' · FWHM '+Number(j.profileTypicalFwhm||0).toFixed(2)+' px · Schritt '+j.profileRecommendedStep+' · Backlash '+j.profileBacklash):'noch nicht gelernt'));p.push('Temperaturmodell: '+((j.tempProfileCount||0)+' Punkte')+(j.tempSlope?(' · '+Number(j.tempSlope).toFixed(2)+' Schritte/°C'):'')+' · Modellziel '+(j.tempCompPredictedPosition>=0?j.tempCompPredictedPosition:'–'));p.push('Filter: '+(j.currentFilter||'–')+' · '+(j.filterOffsetCount||0)+' Offset(s) · letztes Ereignis '+(j.lastExternalEvent||'–'));if(j.backlashCalibrationActive)p.push('Backlash-Kalibrierung läuft …');else if(j.backlashCalibrationResult)p.push(j.backlashCalibrationResult);return p.filter(Boolean).join('\n')}function autofocusDiagnosisText(j){if(j.autofocus)return 'Der Fokuslauf ist aktiv. Messpunkte, Fit und Kontrollaufnahme werden fortlaufend geprüft.';if(j.autofocusErrorCode&&j.autofocusErrorCode!=='NONE')return (j.autofocusErrorTitle||'Autofokus fehlgeschlagen')+(j.autofocusErrorAutomatic?' (automatischer Lauf)':'')+'\nCode: '+j.autofocusErrorCode+(j.autofocusErrorDetail?'\nDetails: '+j.autofocusErrorDetail:'');return 'Kein Autofokusfehler gespeichert.'}function setCheck(id,v){if($(id))$(id).checked=!!v}function fill(j){lastState=j;$('camPill').className='pill '+(j.camera?'on':'');$('camPill').textContent=(j.camera?'● ':'○ ')+'Kamera';$('focPill').className='pill '+(j.focuser?'on':'');$('focPill').textContent=(j.focuser?'● ':'○ ')+'Fokussierer';$('afPill').className='pill '+(j.autofocus?'on':'');$('afPill').textContent=j.autofocus?'Autofokus läuft':'Autofokus bereit';$('cameraName').value=j.cameraName||'';$('focuserName').value=j.focuserName||'';$('position').textContent=j.position>=0?j.position:'–';$('temperature').textContent=j.hasTemperature?j.temperature.toFixed(1)+' °C':'–';$('fwhm').textContent=j.fwhm?j.fwhm.toFixed(2)+' px':'–';$('hfr').textContent=j.hfr?j.hfr.toFixed(2)+' px':'–';$('usedStars').textContent=j.usedStars+' / '+j.starCount;$('snr').textContent=j.snr?j.snr.toFixed(1):'–';$('ecc').textContent=j.ecc?j.ecc.toFixed(2):'–';$('stability').textContent=j.stability?j.stability.toFixed(3):'–';$('status').textContent=j.status||'Bereit';$('overlayBtn').textContent='Overlay: '+j.overlayName;$('bahtOffset').textContent=j.bahtValid?j.bahtOffset.toFixed(2)+' px':'–';$('bahtConf').textContent=j.bahtValid?j.bahtConfidence.toFixed(2):'–';$('sharpness').textContent=j.sharpness?j.sharpness.toFixed(1):'–';$('starFwhm').textContent=j.selectedFwhm?j.selectedFwhm.toFixed(2)+' px':'–';$('starHfr').textContent=j.selectedHfr?j.selectedHfr.toFixed(2)+' px':'–';$('starSnr').textContent=j.selectedSnr?j.selectedSnr.toFixed(1):'–';$('starEcc').textContent=j.selectedEcc?j.selectedEcc.toFixed(2):'–';$('tiltText').textContent=j.tiltValid?'Tilt Δ '+j.tilt.toFixed(2)+' px · '+j.tiltDirection+' · Feld '+Number(j.fieldQualityScore||0).toFixed(0)+'/100':'Tilt: nicht genügend Zonen';if($('selfTestCount'))$('selfTestCount').textContent=j.selfTestTotal?(j.selfTestPassed+' / '+j.selfTestTotal+' bestanden'):'Noch nicht ausgeführt';if($('selfTestSummary'))$('selfTestSummary').textContent=j.selfTestSummary||'–';if($('autoRefocusStatusWeb'))$('autoRefocusStatusWeb').textContent=autoRefocusText(j);if($('focusIntelligenceWeb'))$('focusIntelligenceWeb').textContent=focusIntelligenceText(j);if($('filterName')&&document.activeElement!==$('filterName')&&j.currentFilter)$('filterName').value=j.currentFilter;if($('autoRefocusResumeWeb'))$('autoRefocusResumeWeb').disabled=!j.autoRefocusPaused;if($('afDiagnosisWeb'))$('afDiagnosisWeb').textContent=autofocusDiagnosisText(j);if(!initialized){for(const n of ['profile','exposure','gain','manualStep','afPoints','afStep','afSamples','backlash','refocusMinutes','refocusTemp','refocusFwhmPercent','refocusBadFrames','refocusMinStars','refocusStability','refocusCooldown','tempCompDeadband','tempCompMaxStep','refocusEveryCaptures','safeMin','safeMax'])if(j[n]!==undefined)$(n).value=j[n];initialized=true}for(const n of ['native','reconnect','simulator','demo','stretch','stars','values','saturation','zones','bahtinov','preferredOut','autoRefocus','tempComp','autoStartPosition','refocusOnMeridian','refocusOnReconnect','refocusOnFilter'])setCheck(n,j[n]);validateAfInputs();let mg=$('miniZones');mg.innerHTML='';for(let i=0;i<9;i++){let z=document.createElement('div');z.className='zone';z.textContent=j.zoneCounts[i]?j.zoneFwhm[i].toFixed(2)+' px':'–';mg.appendChild(z)}if(j.frameReady&&j.live&&!j.autofocus&&j.usedStars>0&&j.fwhm&&j.frameSequence!==lastTrendFrame){lastTrendFrame=j.frameSequence;trend.push({y:j.fwhm,hfr:j.hfr,stars:j.usedStars,frame:j.frameSequence});if(trend.length>120)trend.shift();chart($('trend'),trend,'FWHM-Verlauf')}autofocusChart($('afChart'),j);if($('afStatsWeb')){let sig=Number(j.afFocusSigma||0).toFixed(1),loo=Number(j.afFocusSigmaLoo||0).toFixed(1),qual=Number(j.afCurveQuality||j.afFitConfidence||0).toFixed(2),chi=Number(j.afReducedChi2||0).toFixed(2);$('afStatsWeb').textContent=j.afFitValid?('Bestposition '+j.afBestPosition+' ± '+sig+' Schritte · '+(j.afFitMethod||'robuste Kurve')+' · Kurvenqualität '+qual+' · χ²red '+chi+' · Leave-one-out ± '+loo+' · Inlier/Ausreißer '+(j.afFitInliers||0)+'/'+(j.afFitOutliers||0)+' · Zusatzaufnahmen '+(j.afAdaptiveSamplesAdded||0)):'Noch keine gültige statistische Kurvenauswertung.'}}async function refresh(){let j=await api('/api/status');if(j)fill(j);$('frame').src='/frame.bmp?t='+Date.now();$('frame').onload=()=>{$('empty').style.display='none'};$('frame').onerror=()=>{$('empty').style.display='block'}}
['exposure','gain','afPoints','afStep','afSamples','backlash'].forEach(id=>{let e=$(id);if(e){e.addEventListener('input',validateAfInputs);e.addEventListener('change',validateAfInputs)}});document.querySelectorAll('.tab').forEach(b=>b.onclick=()=>{document.querySelectorAll('.tab,.pane').forEach(x=>x.classList.remove('active'));b.classList.add('active');$(b.dataset.pane).classList.add('active')});setInterval(refresh,700);refresh();
</script></body></html>
)CAFHTML";

static BOOL AContains(const char* s,const char* p){if(!s||!p)return FALSE;for(int i=0;s[i];i++){int j=0;while(p[j]&&s[i+j]&&s[i+j]==p[j])j++;if(!p[j])return TRUE;}return FALSE;}
static BOOL RequestPathEquals(const char* request,const char* path){if(!request||!path||request[0]!='G'||request[1]!='E'||request[2]!='T'||request[3]!=' ')return FALSE;const char* p=request+4;int i=0;while(path[i]&&p[i]==path[i])i++;if(path[i])return FALSE;char c=p[i];return c==0||c==' '||c=='?'||c=='\r'||c=='\n';}
static const char* AFind(const char* s,const char* p){if(!s||!p)return 0;for(int i=0;s[i];i++){int j=0;while(p[j]&&s[i+j]&&s[i+j]==p[j])j++;if(!p[j])return s+i;}return 0;}
static char AsciiLower(char c){return c>='A'&&c<='Z'?(char)(c-'A'+'a'):c;}
static const char* AFindInsensitive(const char* s,const char* p){
    if(!s||!p)return 0;
    for(int i=0;s[i];i++){
        int j=0;
        while(p[j]&&s[i+j]&&AsciiLower(s[i+j])==AsciiLower(p[j]))j++;
        if(!p[j])return s+i;
    }
    return 0;
}
static BOOL LocalUrlPrefix(const char* p,const char* prefix){
    if(AFindInsensitive(p,prefix)!=p)return FALSE;
    char next=p[ALen(prefix)];
    return next==0||next=='/'||next=='\r'||next=='\n';
}
static BOOL HeaderValueIsLocal(const char* request,const char* header){
    const char* p=AFindInsensitive(request,header);
    if(!p)return TRUE;
    p+=ALen(header);
    while(*p==' '||*p=='\t')p++;
    return LocalUrlPrefix(p,"http://127.0.0.1:8873")||
           LocalUrlPrefix(p,"http://localhost:8873");
}
static BOOL BrowserMutationAllowed(const char* request){
    const char* site=AFindInsensitive(request,"\r\nSec-Fetch-Site:");
    if(site){
        site+=2+ALen("Sec-Fetch-Site:");
        while(*site==' '||*site=='\t')site++;
        if(AFindInsensitive(site,"cross-site")==site||AFindInsensitive(site,"same-site")==site)return FALSE;
    }
    if(!HeaderValueIsLocal(request,"\r\nOrigin:"))return FALSE;
    if(!HeaderValueIsLocal(request,"\r\nReferer:"))return FALSE;
    return TRUE;
}
static BOOL QueryHasDuplicateKeys(const char* request){
    if(!request)return FALSE;const char* query=AFind(request,"?");if(!query)return FALSE;query++;
    const char* end=query;while(*end&&*end!=' '&&*end!='\r'&&*end!='\n'&&*end!='#')end++;
    for(const char* a=query;a<end;){
        const char* aEnd=a;while(aEnd<end&&*aEnd!='&')aEnd++;const char* aEq=a;while(aEq<aEnd&&*aEq!='=')aEq++;int aLen=(int)(aEq-a);if(aLen<=0)return TRUE;
        for(const char* b=query;b<a;){
            const char* bEnd=b;while(bEnd<end&&*bEnd!='&')bEnd++;const char* bEq=b;while(bEq<bEnd&&*bEq!='=')bEq++;int bLen=(int)(bEq-b);
            if(aLen==bLen){int i=0;while(i<aLen&&a[i]==b[i])i++;if(i==aLen)return TRUE;}
            b=bEnd<end?bEnd+1:end;
        }
        a=aEnd<end?aEnd+1:end;
    }
    return FALSE;
}
static const char* FindQueryValue(const char* request,const char* key){
    if(!request||!key||!key[0])return 0;
    const char* query=AFind(request,"?");if(!query)return 0;query++;
    const char* end=query;while(*end&&*end!=' '&&*end!='\r'&&*end!='\n'&&*end!='#')end++;
    int keyLen=ALen(key);const char* p=query;
    while(p<end){
        const char* valueEnd=p;while(valueEnd<end&&*valueEnd!='&')valueEnd++;
        if(valueEnd-p>=keyLen){int i=0;while(i<keyLen&&p[i]==key[i])i++;if(i==keyLen)return p+keyLen;}
        p=valueEnd<end?valueEnd+1:end;
    }
    return 0;
}
static BOOL QueryValueEquals(const char* request,const char* key,const char* expected){const char* p=FindQueryValue(request,key);if(!p)return FALSE;while(*expected&&*p==*expected){p++;expected++;}return !*expected&&(!*p||*p=='&'||*p==' '||*p=='\r'||*p=='\n'||*p=='#');}
static int QueryInt(const char* req,const char* key,int def){
    const char* p=FindQueryValue(req,key);if(!p)return def;BOOL neg=FALSE;if(*p=='-'){neg=TRUE;p++;}else if(*p=='+')p++;
    if(*p<'0'||*p>'9')return def;unsigned long long limit=neg?2147483648ULL:2147483647ULL,v=0;
    while(*p>='0'&&*p<='9'){unsigned digit=(unsigned)(*p-'0');if(v>(limit-digit)/10ULL)return def;v=v*10ULL+digit;p++;}
    if(*p&&*p!='&'&&*p!=' '&&*p!='\r'&&*p!='\n')return def;
    if(neg)return v==2147483648ULL?(-2147483647-1):-(int)v;return (int)v;
}
static int HexValue(char c){if(c>='0'&&c<='9')return c-'0';if(c>='A'&&c<='F')return c-'A'+10;if(c>='a'&&c<='f')return c-'a'+10;return -1;}
static BOOL Utf8ToWide(const char* src,int len,wchar_t* out,int max){
    int i=0,o=0;if(!src||len<0||!out||max<=0)return FALSE;out[0]=0;
    while(i<len){unsigned char c=(unsigned char)src[i++];unsigned cp=0;
        if(c<0x80)cp=c;
        else if((c&0xe0)==0xc0){
            if(i>=len){out[0]=0;return FALSE;}unsigned char c2=(unsigned char)src[i++];
            if((c2&0xc0)!=0x80){out[0]=0;return FALSE;}cp=((unsigned)(c&0x1f)<<6)|(unsigned)(c2&0x3f);
            if(cp<0x80){out[0]=0;return FALSE;}
        }
        else if((c&0xf0)==0xe0){
            if(i+1>=len){out[0]=0;return FALSE;}unsigned char c2=(unsigned char)src[i++],c3=(unsigned char)src[i++];
            if((c2&0xc0)!=0x80||(c3&0xc0)!=0x80){out[0]=0;return FALSE;}cp=((unsigned)(c&0x0f)<<12)|((unsigned)(c2&0x3f)<<6)|(unsigned)(c3&0x3f);
            if(cp<0x800||(cp>=0xd800&&cp<=0xdfff)){out[0]=0;return FALSE;}
        }
        else if((c&0xf8)==0xf0){
            if(i+2>=len){out[0]=0;return FALSE;}unsigned char c2=(unsigned char)src[i++],c3=(unsigned char)src[i++],c4=(unsigned char)src[i++];
            if((c2&0xc0)!=0x80||(c3&0xc0)!=0x80||(c4&0xc0)!=0x80){out[0]=0;return FALSE;}cp=((unsigned)(c&7)<<18)|((unsigned)(c2&0x3f)<<12)|((unsigned)(c3&0x3f)<<6)|(unsigned)(c4&0x3f);
            if(cp<0x10000||cp>0x10ffff){out[0]=0;return FALSE;}
        }
        else{out[0]=0;return FALSE;}
        if(cp<=0xffff){if(o>=max-1){out[0]=0;return FALSE;}out[o++]=(wchar_t)cp;}
        else{if(o+1>=max-1){out[0]=0;return FALSE;}cp-=0x10000;out[o++]=(wchar_t)(0xd800+(cp>>10));out[o++]=(wchar_t)(0xdc00+(cp&0x3ff));}
    }
    out[o]=0;return TRUE;
}
static void QueryText(const char* req,const char* key,wchar_t* out,int max){
    if(!out||max<=0)return;out[0]=0;const char* p=FindQueryValue(req,key);char bytes[2048];int n=0;if(!p)return;
    while(*p&&*p!=' '&&*p!='&'&&*p!='#'&&*p!='\r'&&*p!='\n'){
        if(n>=(int)sizeof(bytes)-1){out[0]=0;return;}
        unsigned char c=(unsigned char)*p++;
        if(c=='+')c=' ';
        else if(c=='%'){
            if(!p[0]||!p[1]){out[0]=0;return;}int a=HexValue(p[0]),b=HexValue(p[1]);
            if(a<0||b<0){out[0]=0;return;}c=(unsigned char)(a*16+b);p+=2;
        }
        if(c<0x20||c==0x7f){out[0]=0;return;}
        bytes[n++]=(char)c;
    }
    bytes[n]=0;if(!Utf8ToWide(bytes,n,out,max))out[0]=0;
}
static BOOL QueryHas(const char* req,const char* key){return FindQueryValue(req,key)!=0;}
static BOOL BeginFocuserSetupReservation(char* message,int messageCap){
    if(g_focuserSetupReserved){if(message&&messageCap>0)sprintf(message,"Fokussierer-Treiberdialog ist bereits reserviert");return FALSE;}
    if(g_simulatorMode){if(message&&messageCap>0)sprintf(message,"Treiberdialog ist im Simulator nicht verfügbar");return FALSE;}
    if(g_focuserConnected||g_focuserWanted||g_focuserWorker||g_focuserWorkerBlocked||g_afActive||g_stepAssistActive||g_backlashCalActive||g_cachedFocuserMoving||g_focuserRuntime.phase==DEV_CONNECTING||g_focuserRuntime.phase==DEV_BUSY||g_focuserRuntime.phase==DEV_RECOVERING){if(message&&messageCap>0)sprintf(message,"Fokussierer ist nicht sicher getrennt oder eine Fokusoperation läuft");return FALSE;}
    if(g_focuserRuntime.phase!=DEV_DISCONNECTED){if(message&&messageCap>0)sprintf(message,"Fokussierer muss vor dem Treiberdialog vollständig getrennt sein");return FALSE;}
    g_focuserSetupReserved=TRUE;g_autoStartPending=FALSE;SetStatus(L"ASCOM-Treiberdialog reserviert · Fokusbewegungen gesperrt");if(message&&messageCap>0)sprintf(message,"Fokussierer-Treiberdialog reserviert");return TRUE;
}
static void EndFocuserSetupReservation(){if(!g_focuserSetupReserved)return;g_focuserSetupReserved=FALSE;SetStatus(L"ASCOM-Treiberdialog beendet · Fokussierer kann wieder verbunden werden");}
static BOOL ApplyAutofocusStartBundle(const char* req,char* message,int messageCap){
    BOOL hasBundle=QueryHas(req,"afPoints=")||QueryHas(req,"afStep=")||QueryHas(req,"afSamples=")||QueryHas(req,"backlash=")||QueryHas(req,"exposure=")||QueryHas(req,"gain=")||QueryHas(req,"preferredOut=")||QueryHas(req,"afSelectedStar=");
    if(!hasBundle)return TRUE;
    wchar_t exposure[64],gain[64],points[64],step[64],samples[64],backlash[64],preferred[16],selected[16];
    QueryText(req,"exposure=",exposure,64);QueryText(req,"gain=",gain,64);QueryText(req,"afPoints=",points,64);QueryText(req,"afStep=",step,64);QueryText(req,"afSamples=",samples,64);QueryText(req,"backlash=",backlash,64);QueryText(req,"preferredOut=",preferred,16);QueryText(req,"afSelectedStar=",selected,16);
    double d=0.0;UINT u=0,preferredValue=0,selectedValue=0;
    if(!ParseStrictDoubleW(exposure,&d)||d<1.0||d>60000.0){SetAutofocusError(L"AF_INVALID_EXPOSURE",L"Ungültige Belichtungszeit",L"Die Belichtungszeit muss zwischen 1 und 60000 ms liegen.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültige Belichtungszeit");return FALSE;}
    if(!ParseStrictUIntW(gain,&u)||u>65535U){SetAutofocusError(L"AF_INVALID_GAIN",L"Ungültiger Gain",L"Der Gain muss zwischen 0 und 65535 liegen.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültiger Gain");return FALSE;}
    if(!ParseStrictUIntW(points,&u)||u<5U||u>MAX_AF_POINTS||!(u&1U)){SetAutofocusError(L"AF_INVALID_POINT_COUNT",L"Ungültige Messpunktzahl",L"Die Messpunktzahl muss ungerade sein und zwischen 5 und 15 liegen.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültige Messpunktzahl");return FALSE;}
    if(!ParseStrictUIntW(step,&u)||u<5U||u>1000000U){SetAutofocusError(L"AF_INVALID_STEP",L"Ungültige Autofokus-Schrittweite",L"Die Autofokus-Schrittweite muss zwischen 5 und 1000000 liegen.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültige Autofokus-Schrittweite");return FALSE;}
    if(!ParseStrictUIntW(samples,&u)||u<1U||u>MAX_AF_SAMPLES){SetAutofocusError(L"AF_INVALID_SAMPLE_COUNT",L"Ungültige Sample-Anzahl",L"Die Anzahl Aufnahmen pro Messpunkt muss zwischen 1 und 5 liegen.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültige Sample-Anzahl");return FALSE;}
    if(!ParseStrictUIntW(backlash,&u)||u>1000000U){SetAutofocusError(L"AF_INVALID_BACKLASH",L"Ungültige Backlash-Kompensation",L"Die Backlash-Kompensation muss zwischen 0 und 1000000 liegen.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültige Backlash-Kompensation");return FALSE;}
    if(!ParseStrictUIntW(preferred,&preferredValue)||preferredValue>1U){SetAutofocusError(L"AF_INVALID_PREFERRED_DIRECTION",L"Ungültige Annäherungsrichtung",L"Die finale Annäherungsrichtung konnte nicht eindeutig übertragen werden.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültige Annäherungsrichtung");return FALSE;}
    if(!ParseStrictUIntW(selected,&selectedValue)||selectedValue>1U){SetAutofocusError(L"AF_INVALID_STAR_MODE",L"Ungültiger Fokussternmodus",L"Der Fokussternmodus konnte nicht eindeutig übertragen werden.",FALSE);if(message&&messageCap>0)sprintf(message,"Ungültiger Fokussternmodus");return FALSE;}
    SetWindowTextW(g_exposureEdit,exposure);SetWindowTextW(g_gainEdit,gain);SetWindowTextW(g_afPointsEdit,points);SetWindowTextW(g_afStepEdit,step);SetWindowTextW(g_afSamplesEdit,samples);SetWindowTextW(g_afBacklashEdit,backlash);SetChecked(g_preferredDirCheck,preferredValue!=0);g_afUseSelectedStar=selectedValue!=0;
    SaveSettings();AppendRuntimeTrace("autofocus parameter bundle accepted");return TRUE;
}
static BOOL SendAll(SOCKET c,const char* data,int len){
    if(!data||len<0)return FALSE;
    int sent=0;
    while(sent<len){
        int remaining=len-sent;
        int chunk=remaining>65536?65536:remaining;
        int n=p_send(c,data+sent,chunk,0);
        if(n<=0)return FALSE;
        sent+=n;
    }
    return TRUE;
}
static void SendHttp(SOCKET c,const char* type,const char* body,int len){
    char h[320];
    int hn=sprintf(h,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nCache-Control: no-store\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",type,len);
    if(!SendAll(c,h,hn))return;
    if(len>0&&body)SendAll(c,body,len);
}
static void SendJsonResult(SOCKET c,BOOL ok,const char* message){
    char body[1400];int o=0;o+=sprintf(body+o,"{\"ok\":%s,\"message\":\"",ok?"true":"false");
    for(int i=0;message&&message[i]&&o<(int)sizeof(body)-8;i++){char ch=message[i];if(ch=='\\'||ch=='"')body[o++]='\\';if((unsigned char)ch>=32)body[o++]=ch;}
    body[o++]='"';body[o++]='}';body[o]=0;SendHttp(c,"application/json",body,o);
}
static void SendBmp(SOCKET c){
    if(!g_frameReady||!g_display||g_width<=0||g_height<=0){const char* b="no frame";SendHttp(c,"text/plain",b,8);return;}
    unsigned long long data64=(unsigned long long)g_width*(unsigned long long)g_height*4ULL,total64=54ULL+data64;
    if(data64>0x7ffffff0ULL||total64>0x7fffffffULL){const char* b="frame too large";SendHttp(c,"text/plain",b,15);return;}
    int dataSize=(int)data64,total=(int)total64;BYTE* b=(BYTE*)Alloc((SIZE_T)total);if(!b)return;memset(b,0,(SIZE_T)total);b[0]='B';b[1]='M';PutLe32(b+2,(UINT)total);PutLe32(b+10,54U);PutLe32(b+14,40U);PutLe32(b+18,(UINT)g_width);PutLe32(b+22,(UINT)(-g_height));PutLe16(b+26,1U);PutLe16(b+28,32U);PutLe32(b+34,(UINT)dataSize);memcpy(b+54,g_display,(SIZE_T)dataSize);SendHttp(c,"image/bmp",(const char*)b,total);Free(b);
}
static void OpenWebUi(){if(!g_shell32)g_shell32=LoadLibraryW(L"shell32.dll");if(!g_shell32)return;if(!pShellExecuteW)pShellExecuteW=(PFN_ShellExecuteW)GetProcAddress(g_shell32,"ShellExecuteW");if(pShellExecuteW)pShellExecuteW(0,L"open",L"msedge.exe",L"--app=http://127.0.0.1:8873/ --start-maximized --no-first-run --disable-extensions",0,1);}
static BOOL StartHttpServer(){
    if(g_httpListen!=INVALID_SOCKET_VALUE)return TRUE;g_ws2=LoadLibraryW(L"ws2_32.dll");if(!g_ws2)return FALSE;
    pWSAStartup=(PFN_WSAStartup)GetProcAddress(g_ws2,"WSAStartup");pWSACleanup=(PFN_WSACleanup)GetProcAddress(g_ws2,"WSACleanup");p_socket=(PFN_socket)GetProcAddress(g_ws2,"socket");p_bind=(PFN_bind)GetProcAddress(g_ws2,"bind");p_listen=(PFN_listen)GetProcAddress(g_ws2,"listen");p_accept=(PFN_accept)GetProcAddress(g_ws2,"accept");p_recv=(PFN_recv)GetProcAddress(g_ws2,"recv");p_send=(PFN_send)GetProcAddress(g_ws2,"send");p_closesocket=(PFN_closesocket)GetProcAddress(g_ws2,"closesocket");p_setsockopt=(PFN_setsockopt)GetProcAddress(g_ws2,"setsockopt");p_ioctlsocket=(PFN_ioctlsocket)GetProcAddress(g_ws2,"ioctlsocket");p_htons=(PFN_htons)GetProcAddress(g_ws2,"htons");p_htonl=(PFN_htonl)GetProcAddress(g_ws2,"htonl");
    if(!pWSAStartup||!p_socket||!p_bind||!p_listen||!p_accept||!p_recv||!p_send||!p_closesocket||!p_setsockopt||!p_ioctlsocket||!p_htons||!p_htonl){FreeLibrary(g_ws2);g_ws2=0;return FALSE;}WSADATA_STORAGE wd;memset(&wd,0,sizeof(wd));if(pWSAStartup(0x0202,&wd)){FreeLibrary(g_ws2);g_ws2=0;return FALSE;}
    g_httpListen=p_socket(AF_INET_MIN,SOCK_STREAM_MIN,IPPROTO_TCP_MIN);if(g_httpListen==INVALID_SOCKET_VALUE){if(pWSACleanup)pWSACleanup();FreeLibrary(g_ws2);g_ws2=0;return FALSE;}SOCKADDR_IN a;memset(&a,0,sizeof(a));a.sin_family=AF_INET_MIN;a.sin_port=p_htons((unsigned short)g_httpPort);a.sin_addr.s_addr=p_htonl(INADDR_LOOPBACK_MIN);if(p_bind(g_httpListen,(SOCKADDR*)&a,sizeof(a))||p_listen(g_httpListen,4)){p_closesocket(g_httpListen);g_httpListen=INVALID_SOCKET_VALUE;if(pWSACleanup)pWSACleanup();FreeLibrary(g_ws2);g_ws2=0;return FALSE;}unsigned long nb=1;p_ioctlsocket(g_httpListen,FIONBIO_MIN,&nb);return TRUE;
}
static void StopHttpServer(){if(g_httpListen!=INVALID_SOCKET_VALUE&&p_closesocket)p_closesocket(g_httpListen);g_httpListen=INVALID_SOCKET_VALUE;if(pWSACleanup)pWSACleanup();if(g_ws2)FreeLibrary(g_ws2);g_ws2=0;}
static void SendObservatoryStatus(SOCKET c){
    char cam[720],foc[720],focusLabel[260],focusReason[700],validationState[260],validationReason[900],autoReason[700],simProfileName[320],fitMethod[420];
    WToJsonUtf8(g_cameraId,cam,720);WToJsonUtf8(g_focuserId,foc,720);WToJsonUtf8(g_focusNeedLabel,focusLabel,260);WToJsonUtf8(g_focusNeedReason,focusReason,700);WToJsonUtf8(g_afValidationState,validationState,260);WToJsonUtf8(g_afValidationReason,validationReason,900);WToJsonUtf8(g_simProfileName,simProfileName,320);WToJsonUtf8(g_fitMethod,fitMethod,420);WToJsonUtf8(g_lastAutoRefocusReason,autoReason,700);
    ULONGLONG now=GetTickCount64();double minutes=g_sessionStartTick?(double)(now-g_sessionStartTick)/60000.0:0.0;int pos=g_focuserConnected?FocuserPosition():-1;
    char body[8192];int n=sprintf(body,
        "{\"apiVersion\":1,\"app\":\"AstroFocus Studio\",\"version\":\"3.9.0\","
        "\"camera\":{\"connected\":%s,\"name\":\"%s\"},\"focuser\":{\"connected\":%s,\"name\":\"%s\",\"position\":%d,\"hasTemperature\":%s,\"temperatureC\":%.3f},"
        "\"focus\":{\"fwhmPx\":%.4f,\"hfrPx\":%.4f,\"usedStars\":%d,\"stabilityPx\":%.4f,\"status\":\"%s\",\"score\":%d,\"reason\":\"%s\"},"
        "\"autofocus\":{\"running\":%s,\"automatic\":%s,\"qualityScore\":%d,\"finalValid\":%s,\"validationPassed\":%s,\"rollbackPerformed\":%s,\"validationState\":\"%s\",\"validationReason\":\"%s\",\"lastPosition\":%d,\"lastFwhmPx\":%.4f,\"lastHfrPx\":%.4f,\"fitModel\":\"%s\",\"curveQuality\":%.4f,\"focusSigmaSteps\":%.3f,\"looSigmaSteps\":%.3f,\"reducedChi2\":%.4f,\"inliers\":%d,\"outliers\":%d,\"adaptiveSamplesAdded\":%d},"
        "\"autoRefocus\":{\"enabled\":%s,\"paused\":%s,\"reason\":\"%s\"},"
        "\"simulator\":{\"enabled\":%s,\"profileMode\":%d,\"activeProfile\":%d,\"profileName\":\"%s\",\"backlashSteps\":%d,\"randomSeed\":%u,\"backlashRemaining\":%d,\"motorPosition\":%d,\"opticalPosition\":%d},"
        "\"session\":{\"minutes\":%.3f,\"afAttempts\":%d,\"afSuccess\":%d,\"afFailed\":%d,\"afRollbacks\":%d,\"bestFwhmPx\":%.4f,\"worstFwhmPx\":%.4f}}",
        g_cameraConnected?"true":"false",cam,g_focuserConnected?"true":"false",foc,pos,(g_focuserConnected&&g_hasFocuserTemperature)?"true":"false",JsonNumber(g_focuserTemperature),JsonNumber(g_medianFwhm),JsonNumber(g_medianHfr),g_usedCount,JsonNumber(FocusStability()),focusLabel,g_focusNeedScore,focusReason,g_afActive?"true":"false",g_afAutomaticRun?"true":"false",g_focusQualityScore,g_afFinalValid?"true":"false",g_afValidationPassed?"true":"false",g_afRollbackPerformed?"true":"false",validationState,validationReason,g_afFinalValid?g_afFinalPosition:-1,JsonNumber(g_afFinalFwhm),JsonNumber(g_afFinalHfr),fitMethod,JsonNumber(g_fitConfidence),JsonNumber(g_fitFocusSigma),JsonNumber(g_fitFocusSigmaLoo),JsonNumber(g_fitReducedChi2),g_fitInliers,g_fitOutliers,g_afAdaptiveSamplesAdded,g_autoRefocusEnabled?"true":"false",g_autoRefocusPaused?"true":"false",autoReason,g_simulatorMode?"true":"false",g_simProfileMode,g_simActiveProfile,simProfileName,g_simBacklashSteps,g_simRandomSeed,g_simBacklashRemaining,g_simPosition,g_simOpticalPosition,JsonNumber(minutes),g_sessionAfAttempts,g_sessionAfSuccess,g_sessionAfFailed,g_sessionAfRollbacks,JsonNumber(g_sessionBestFwhm),JsonNumber(g_sessionWorstFwhm));
    if(n<=0||n>=(int)sizeof(body))SendJsonResult(c,FALSE,"Statusantwort zu groß");else SendHttp(c,"application/json",body,n);
}
static void SendFocusModelStatus(SOCKET c){
    char body[8192];int n=sprintf(body,"{\"apiVersion\":1,\"version\":\"3.9.0\",\"valid\":%s,\"slopeStepsPerC\":%.6f,\"intercept\":%.3f,\"count\":%d,\"temperatureC\":[",g_tempFitValid?"true":"false",JsonNumber(g_tempSlope),JsonNumber(g_tempIntercept),g_tempProfileCount);
    for(int i=0;i<g_tempProfileCount&&n<(int)sizeof(body)-128;i++)n+=sprintf(body+n,i?",%.4f":"%.4f",JsonNumber(g_tempProfileT[i]));
    n+=sprintf(body+n,"],\"position\":[");for(int i=0;i<g_tempProfileCount&&n<(int)sizeof(body)-128;i++)n+=sprintf(body+n,i?",%d":"%d",g_tempProfileP[i]);n+=sprintf(body+n,"]}");
    if(n<=0||n>=(int)sizeof(body))SendJsonResult(c,FALSE,"Modellantwort zu groß");else SendHttp(c,"application/json",body,n);
}
static BOOL IsSafeAscomProgIdText(LPCWSTR value){if(!value||!value[0])return FALSE;BOOL dot=FALSE;int n=0;for(;value[n];n++){wchar_t c=value[n];if(n>=255||c<=L' '||c==L'\\'||c==L'/'||c==L'"'||c==L'?'||c==L'#'||c==L'&')return FALSE;if(c==L'.')dot=TRUE;}return n>=3&&dot;}
static void PollHttpServer(){
    if(!g_httpEnabled||g_httpListen==INVALID_SOCKET_VALUE)return;
    SOCKET c=p_accept(g_httpListen,0,0);
    if(c==INVALID_SOCKET_VALUE)return;
    // The listening socket is non-blocking so that the Win32 message loop remains responsive.
    // Accepted sockets can inherit that mode. Large BMP responses would then be truncated as
    // soon as send() reports WSAEWOULDBLOCK. Switch every connected client explicitly back
    // to blocking mode before reading the request or sending multi-megabyte image data.
    unsigned long clientNonBlocking=0;
    if(!p_ioctlsocket||p_ioctlsocket(c,FIONBIO_MIN,&clientNonBlocking)!=0){p_closesocket(c);return;}
    DWORD sendTimeoutMs=5000,receiveTimeoutMs=1000;
    p_setsockopt(c,SOL_SOCKET_MIN,SO_SNDTIMEO_MIN,(const char*)&sendTimeoutMs,sizeof(sendTimeoutMs));
    p_setsockopt(c,SOL_SOCKET_MIN,SO_RCVTIMEO_MIN,(const char*)&receiveTimeoutMs,sizeof(receiveTimeoutMs));
    char req[8192];int r=0;while(r<8191){int q=p_recv(c,req+r,8191-r,0);if(q<=0)break;r+=q;req[r]=0;if(AContains(req,"\r\n\r\n"))break;}req[r]=0;
    if(RequestPathEquals(req,"/frame.bmp")){SendBmp(c);p_closesocket(c);return;}
    if(RequestPathEquals(req,"/")||RequestPathEquals(req,"/index.html")){SendHttp(c,"text/html; charset=utf-8",g_webUi,ALen(g_webUi));p_closesocket(c);return;}
    if(RequestPathEquals(req,"/api/v1/profiles")){SendProfileList(c);p_closesocket(c);return;}
    if(RequestPathEquals(req,"/api/v1/profile-preview")){SendProfilePreview(c,req);p_closesocket(c);return;}
    if(RequestPathEquals(req,"/api/v1/status")){SendObservatoryStatus(c);p_closesocket(c);return;}
    if(RequestPathEquals(req,"/api/v1/focus-model")){SendFocusModelStatus(c);p_closesocket(c);return;}
    wchar_t val[768];char message[768]="OK";
    BOOL mutationRoute=RequestPathEquals(req,"/api/action")||RequestPathEquals(req,"/api/toggle")||RequestPathEquals(req,"/api/set");
    if(mutationRoute&&QueryHasDuplicateKeys(req)){SendJsonResult(c,FALSE,"Doppelte Abfrageparameter sind nicht zulässig");p_closesocket(c);return;}
    if(mutationRoute&&!BrowserMutationAllowed(req)){SendJsonResult(c,FALSE,"Browser-Anfrage von fremder Herkunft blockiert");p_closesocket(c);return;}
    if(RequestPathEquals(req,"/api/action")){
        BOOL ok=TRUE,handled=TRUE;
        if(QueryValueEquals(req,"name=","camera-select")){
            if(g_externalCameraMode)sprintf(message,"USB/UVC-Kamera wird von der Win32-Oberfläche ausgewählt");
            else if(g_simulatorMode)sprintf(message,"Synthetische Kamera ist ausgewählt");
            else if(IsChecked(g_nativeCheck)){ToupcamDeviceV2 dev[16];memset(dev,0,sizeof(dev));if(!LoadToupTek()){ok=FALSE;sprintf(message,"64-Bit-toupcam.dll fehlt oder ist inkompatibel");SetCameraActionMessage(L"Die 64-Bit-toupcam.dll wurde nicht gefunden oder ist inkompatibel. Wähle die DLL in der sichtbaren Oberfläche über 'SDK/Kamera suchen' aus.");}else{unsigned n=pToupcam_EnumV2(dev);if(n>0){lstrcpyW(g_cameraId,dev[0].displayname);SetWindowTextW(g_cameraEdit,g_cameraId);sprintf(message,"ToupTek-Kamera erkannt");SetCameraActionMessage(L"ToupTek-Kamera erkannt · bereit zum Verbinden");}else{UnloadToupTek();ok=FALSE;sprintf(message,"ToupTek-SDK geladen, aber keine Kamera erkannt");SetCameraActionMessage(L"Das ToupTek-SDK wurde geladen, aber keine kompatible Kamera erkannt. Prüfe USB-Verbindung und Treiber.");}}}
            else{ok=FALSE;sprintf(message,"ASCOM-Kameraauswahl ist nur in der sichtbaren Desktopoberfläche verfügbar");SetCameraActionMessage(L"Öffne die ASCOM-Kameraauswahl in AstroFocus Studio. Die versteckte Engine öffnet aus Sicherheitsgründen keinen modalen ASCOM-Dialog.");}
        }
        else if(QueryValueEquals(req,"name=","external-on")){
            if(!g_externalCameraName[0]){ok=FALSE;sprintf(message,"Kein USB/UVC-Gerätename gesetzt");}
            else{if(g_simulatorMode)SetSimulatorMode(FALSE);if(g_cameraConnected)DisconnectCamera();g_externalCameraMode=TRUE;g_cameraConnected=TRUE;g_cameraWanted=FALSE;g_nativeActive=FALSE;lstrcpyW(g_cameraId,g_externalCameraName);SetWindowTextW(g_cameraEdit,g_cameraId);SetWindowTextW(g_cameraConnect,L"Trennen");SetStatus(L"USB/UVC-Kamera verbunden · DirectShow/FFmpeg");sprintf(message,"USB/UVC-Kamera verbunden");}
        }
        else if(QueryValueEquals(req,"name=","external-off")){StopLive();if(g_externalCameraMode)DisconnectCamera();sprintf(message,"USB/UVC-Kamera getrennt");}
        else if(QueryValueEquals(req,"name=","camera-connect")){
            BOOL before=g_cameraConnected;
            if(g_externalCameraMode){if(g_cameraConnected)DisconnectCamera();else{g_externalCameraMode=TRUE;g_cameraConnected=TRUE;lstrcpyW(g_cameraId,g_externalCameraName);}sprintf(message,"USB/UVC-Kameraverbindung umgeschaltet");}
            else if(g_simulatorMode){WriteSimulatorStage("10 camera connect requested");if(g_cameraConnected){if(g_afActive)StopAutofocus(FALSE,L"Synthetische Kamera getrennt · Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"Synthetische Kamera getrennt · Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Synthetische Kamera getrennt · Backlash-Kalibrierung abgebrochen");StopLive();AbortExposure();g_cameraConnected=FALSE;SetWindowTextW(g_cameraConnect,L"Verbinden");SetStatus(L"Synthetische Kamera getrennt");WriteSimulatorStage("12 camera disconnected");sprintf(message,"Synthetische Kamera getrennt");}else{g_cameraConnected=TRUE;SetWindowTextW(g_cameraConnect,L"Trennen");{wchar_t sm[220];wsprintfW(sm,L"Synthetische Kamera verbunden · Profil: %s",g_simProfileName);SetStatus(sm);}WriteSimulatorStage("11 camera connected; frame generation deferred");sprintf(message,"Synthetische Kamera verbunden");}}
            else{ok=ConnectCamera();if(g_lastCameraActionMessage[0])WToAscii(g_lastCameraActionMessage,message,768);else sprintf(message,ok?"Kameraverbindung umgeschaltet":"Kameraverbindung konnte nicht umgeschaltet werden");}
            if(g_externalCameraMode||g_simulatorMode){ok=before!=g_cameraConnected;if(!ok)sprintf(message,"Kameraverbindung konnte nicht umgeschaltet werden");}
        }
        else if(QueryValueEquals(req,"name=","focuser-select")){if(g_simulatorMode)sprintf(message,"Synthetischer Fokussierer ist ausgewählt");else{ok=FALSE;sprintf(message,"ASCOM-Fokussiererauswahl ist nur in der sichtbaren Desktopoberfläche verfügbar");SetFocuserActionMessage(L"Öffne die ASCOM-Fokussiererauswahl in AstroFocus Studio. Die versteckte Engine öffnet aus Sicherheitsgründen keinen modalen ASCOM-Dialog.");}}
        else if(QueryValueEquals(req,"name=","focuser-setup-begin")){ok=BeginFocuserSetupReservation(message,768);}
        else if(QueryValueEquals(req,"name=","focuser-setup-end")){EndFocuserSetupReservation();ok=TRUE;sprintf(message,"Fokussierer-Treiberdialog freigegeben");}
        else if(QueryValueEquals(req,"name=","focuser-connect")){
            if(g_focuserSetupReserved){ok=FALSE;sprintf(message,"Fokussiererverbindung ist während des Treiberdialogs gesperrt");}
            else{BOOL before=g_focuserConnected;
            if(g_simulatorMode){WriteSimulatorStage("20 focuser connect requested");if(g_focuserConnected){if(g_afActive)StopAutofocus(FALSE,L"Synthetischer Fokussierer getrennt · Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"Synthetischer Fokussierer getrennt · Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Synthetischer Fokussierer getrennt · Backlash-Kalibrierung abgebrochen");g_focuserConnected=FALSE;g_cachedFocuserPosition=-1;g_cachedFocuserMoving=FALSE;g_hasFocuserTemperature=FALSE;}else{g_focuserConnected=TRUE;g_cachedFocuserPosition=g_simPosition;g_cachedFocuserMoving=FALSE;g_focuserTemperature=g_simTemperature;g_hasFocuserTemperature=TRUE;}SetWindowTextW(g_focuserConnect,g_focuserConnected?L"Trennen":L"Verbinden");if(g_focuserConnected){g_autoStartPending=TRUE;wchar_t p[32];wsprintfW(p,L"%d",g_simPosition);SetWindowTextW(g_positionText,p);SetStatus(L"Synthetischer Fokussierer verbunden");WriteSimulatorStage("21 focuser connected");}else{SetWindowTextW(g_positionText,L"–");SetStatus(L"Synthetischer Fokussierer getrennt");WriteSimulatorStage("22 focuser disconnected");}sprintf(message,g_focuserConnected?"Synthetischer Fokussierer verbunden":"Synthetischer Fokussierer getrennt");}
            else{ok=ConnectFocuser();if(g_lastFocuserActionMessage[0])WToAscii(g_lastFocuserActionMessage,message,768);else sprintf(message,ok?"Fokussiererverbindung umgeschaltet":"Fokussiererverbindung konnte nicht umgeschaltet werden");}
            if(g_simulatorMode){ok=before!=g_focuserConnected;if(!ok)sprintf(message,"Fokussiererverbindung konnte nicht umgeschaltet werden");}}
        }
        else if(QueryValueEquals(req,"name=","live")){BOOL before=g_live;StartLive();ok=before!=g_live;sprintf(message,ok?"Live-Fokus umgeschaltet":"Live-Fokus konnte nicht umgeschaltet werden");}
        else if(QueryValueEquals(req,"name=","move-in")){ok=!g_focuserSetupReserved&&ManualMove(-1);sprintf(message,ok?"Fokussierer nach innen bewegt":(g_focuserSetupReserved?"Fokusbewegung während des Treiberdialogs gesperrt":"Fokusbewegung nach innen nicht ausgeführt"));}
        else if(QueryValueEquals(req,"name=","move-out")){ok=!g_focuserSetupReserved&&ManualMove(1);sprintf(message,ok?"Fokussierer nach außen bewegt":(g_focuserSetupReserved?"Fokusbewegung während des Treiberdialogs gesperrt":"Fokusbewegung nach außen nicht ausgeführt"));}
        else if(QueryValueEquals(req,"name=","halt")){ok=g_focuserConnected||g_afActive||g_stepAssistActive||g_backlashCalActive;HaltFocuser();sprintf(message,ok?"Fokussierer gestoppt":"Kein verbundener oder aktiver Fokussierer");}
        else if(QueryValueEquals(req,"name=","autofocus-start")){if(g_focuserSetupReserved){ok=FALSE;sprintf(message,"Autofokus ist während des Treiberdialogs gesperrt");}else if(g_afActive){ok=TRUE;sprintf(message,"Autofokus läuft bereits");}else if(!ApplyAutofocusStartBundle(req,message,160)){ok=FALSE;}else{BOOL confirmed=QueryInt(req,"confirmed=",0)==1;BOOL oldConfirmed=g_afRequestConfirmed;g_afRequestConfirmed=confirmed;StartAutofocus();g_afRequestConfirmed=oldConfirmed;ok=g_afActive;if(ok)sprintf(message,"Autofokus gestartet");else if(g_lastAfErrorTitle[0])WToAscii(g_lastAfErrorTitle,message,160);else sprintf(message,"Autofokus nicht gestartet");}}
        else if(QueryValueEquals(req,"name=","autofocus-stop")){ok=g_afActive;if(ok)StopAutofocus(TRUE,L"Autofokus über Oberfläche abgebrochen");sprintf(message,ok?"Autofokus abgebrochen":"Kein Autofokuslauf aktiv");}
        else if(QueryValueEquals(req,"name=","step-assist")){if(g_focuserSetupReserved){ok=FALSE;sprintf(message,"Schritt-Assistent ist während des Treiberdialogs gesperrt");}else{BOOL before=g_stepAssistActive;StartStepAssistant();ok=before!=g_stepAssistActive;sprintf(message,ok?(g_stepAssistActive?"Schritt-Assistent gestartet":"Schritt-Assistent abgebrochen"):"Schritt-Assistent nicht gestartet · Statusmeldung prüfen");}}
        else if(QueryValueEquals(req,"name=","backlash-calibrate")){if(g_focuserSetupReserved){ok=FALSE;sprintf(message,"Backlash-Kalibrierung ist während des Treiberdialogs gesperrt");}else{BOOL before=g_backlashCalActive;StartBacklashCalibration();ok=before!=g_backlashCalActive;sprintf(message,ok?(g_backlashCalActive?"Backlash-Kalibrierung gestartet":"Backlash-Kalibrierung beendet"):"Backlash-Kalibrierung nicht gestartet · Statusmeldung prüfen");}}
        else if(QueryValueEquals(req,"name=","filter-learn")){wchar_t fn[32];QueryText(req,"filterName=",fn,32);ok=LearnCurrentFilterOffset(fn);sprintf(message,ok?"Filteroffset gelernt":"Filteroffset konnte nicht gelernt werden");}
        else if(QueryValueEquals(req,"name=","filter-apply")){wchar_t fn[32];QueryText(req,"filterName=",fn,32);ok=ApplyFilterOffset(fn);sprintf(message,ok?"Filteroffset angewendet":"Filteroffset unbekannt oder nicht anwendbar");}
        else if(QueryValueEquals(req,"name=","event-meridian")){ok=HandleExternalRefocusEvent(L"Meridian-Flip");sprintf(message,ok?"Meridian-Refokus gestartet":"Meridian-Ereignis registriert");}
        else if(QueryValueEquals(req,"name=","event-reconnect")){ok=HandleExternalRefocusEvent(L"Wiederverbindung");sprintf(message,ok?"Refokus nach Wiederverbindung gestartet":"Wiederverbindungsereignis registriert");}
        else if(QueryValueEquals(req,"name=","capture-complete")){g_captureEventCounter++;if(g_refocusEveryCaptures>0&&g_captureEventCounter>=g_refocusEveryCaptures){g_captureEventCounter=0;ok=HandleExternalRefocusEvent(L"Aufnahmeintervall erreicht");sprintf(message,ok?"Aufnahmeintervall-Refokus gestartet":"Aufnahmeintervall erreicht");}else{ok=TRUE;sprintf(message,"Aufnahmeereignis registriert");}}
        else if(QueryValueEquals(req,"name=","diagnostics")){ok=SaveDiagnostics();sprintf(message,ok?"Diagnosebericht gespeichert":"Diagnosebericht konnte nicht gespeichert werden");}
        else if(QueryValueEquals(req,"name=","auto-refocus-resume")){if(!g_autoRefocusEnabled){ok=FALSE;sprintf(message,"Auto-Refokus ist deaktiviert");}else if(!g_autoRefocusPaused){ok=FALSE;sprintf(message,"Auto-Refokus ist nicht pausiert");}else{ResumeAutoRefocusAfterPause();sprintf(message,"Auto-Refokus wieder freigegeben");}}
        else if(QueryValueEquals(req,"name=","export")){ok=ExportReport(L"Win32-Oberfläche");sprintf(message,ok?"CSV/SVG-Bericht gespeichert":"CSV/SVG-Bericht konnte nicht vollständig gespeichert werden");}
        else if(QueryValueEquals(req,"name=","select-star")){int sx=QueryInt(req,"x=",-1),sy=QueryInt(req,"y=",-1);SetRuntimeOperation("select-star api");AppendRuntimeTrace("select-star api begin");if(g_afActive){ok=FALSE;sprintf(message,"Auswahl kann während des Autofokus nicht geändert werden");}else if(sx>=0&&sy>=0&&SelectManualStarAt(sx,sy)){// The click path is metadata-only. Never scan or redraw the large image buffer from an HTTP selection request.
            g_bahtinovScore=0.0;g_bahtinovValid=FALSE;SetStatus(L"Fokusstern manuell gewählt · blaues Fadenkreuz · Autofokus verwendet diesen Stern");sprintf(message,"Fokusstern ausgewählt und für Autofokus fixiert");
        }else{ok=FALSE;ClearManualStarSelection();SetStatus(L"Kein geeigneter ungesättigter Stern nahe der Klickposition");sprintf(message,"Kein geeigneter ungesättigter Stern nahe der Klickposition");}AppendRuntimeTrace(ok?"select-star api complete":"select-star api rejected");SetRuntimeOperation("idle");}
        else if(QueryValueEquals(req,"name=","clear-star")){if(g_afActive){ok=FALSE;sprintf(message,"Auswahl kann während des Autofokus nicht geändert werden");}else{ClearManualStarSelection();SetStatus(L"Manuelle Fokussternauswahl aufgehoben · Autofokus verwendet Feldmedian");sprintf(message,"Manuelle Fokussternauswahl aufgehoben");}}
        else if(QueryValueEquals(req,"name=","fault-camera-disconnect")){if(!g_simulatorMode){ok=FALSE;sprintf(message,"Fehlerprovokation ist nur im Simulator zulässig");}else{g_cameraConnected=FALSE;g_cameraRuntime.phase=DEV_RECOVERING;g_cameraRuntime.removalDetected=TRUE;if(g_afActive)StopAutofocus(FALSE,L"Synthetische Kamera getrennt · Autofokus sicher abgebrochen");SetStatus(L"Fehlerprovokation: synthetische Kamera getrennt");sprintf(message,"Synthetische Kameratrennung ausgelöst");}}
        else if(QueryValueEquals(req,"name=","fault-camera-no-frames")){if(!g_simulatorMode){ok=FALSE;sprintf(message,"Fehlerprovokation ist nur im Simulator zulässig");}else{g_faultCameraNoFrames=!g_faultCameraNoFrames;sprintf(message,g_faultCameraNoFrames?"Frame-Timeout aktiviert":"Frame-Timeout deaktiviert");}}
        else if(QueryValueEquals(req,"name=","fault-camera-corrupt-next")){if(!g_simulatorMode){ok=FALSE;sprintf(message,"Fehlerprovokation ist nur im Simulator zulässig");}else{g_faultCameraCorruptNext=TRUE;sprintf(message,"Nächstes Simulatorbild wird verworfen");}}
        else if(QueryValueEquals(req,"name=","fault-focuser-stall")){if(!g_simulatorMode){ok=FALSE;sprintf(message,"Fehlerprovokation ist nur im Simulator zulässig");}else{g_faultFocuserStall=!g_faultFocuserStall;sprintf(message,g_faultFocuserStall?"Fokussierer-Stall aktiviert":"Fokussierer-Stall deaktiviert");}}
        else if(QueryValueEquals(req,"name=","fault-camera-host-crash")){if(g_simulatorMode||!g_cameraWorker){ok=FALSE;sprintf(message,"Kein ASCOM-Kamera-Host aktiv");}else{ok=SubmitWorker(g_cameraWorker,DW_TEST_CRASH,1200,L"Kamera-Host-Absturztest");ApplyDeviceWorkerFaults();sprintf(message,"Kamera-Host-Absturztest ausgelöst");}}
        else if(QueryValueEquals(req,"name=","fault-focuser-host-crash")){if(g_simulatorMode||!g_focuserWorker){ok=FALSE;sprintf(message,"Kein ASCOM-Fokussierer-Host aktiv");}else{ok=SubmitWorker(g_focuserWorker,DW_TEST_CRASH,1200,L"Fokussierer-Host-Absturztest");ApplyDeviceWorkerFaults();sprintf(message,"Fokussierer-Host-Absturztest ausgelöst");}}
        else if(QueryValueEquals(req,"name=","selftest")){if(!g_simulatorMode||!g_cameraConnected||!g_focuserConnected||g_afActive||g_stepAssistActive||g_backlashCalActive||g_exposing){ok=FALSE;SetStatus(L"Synthetische Tests benötigen verbundenen Simulator und einen ruhenden Zustand");sprintf(message,"Tests nicht gestartet: Simulator vollständig verbinden und laufende Aktionen beenden");}else{RunSyntheticSelfTests();ok=g_selfTestFailed==0;sprintf(message,"Synthetische Tests: %d von %d bestanden",g_selfTestPassed,g_selfTestTotal);}}
        else if(QueryValueEquals(req,"name=","continuous-focus-reset")){ContinuousFocusResetReference(L"Referenz wurde vom Benutzer zurückgesetzt");sprintf(message,"Nachführungsreferenz zurückgesetzt");}
        else if(QueryValueEquals(req,"name=","continuous-focus-resume")){g_continuousFocusPaused=FALSE;g_continuousFocusRejected=0;g_continuousFocusFallbackPending=FALSE;g_continuousFocusSampleCount=0;CopyWBounded(g_continuousFocusState,96,g_continuousFocusEnabled?L"Wartet":L"Deaktiviert");CopyWBounded(g_continuousFocusReason,320,L"Kontinuierliche Fokusnachführung wurde freigegeben.");sprintf(message,"Kontinuierliche Fokusnachführung freigegeben");}
        else if(QueryValueEquals(req,"name=","sim-randomize")){if(!g_simulatorMode||g_afActive||g_stepAssistActive||g_backlashCalActive){ok=FALSE;sprintf(message,"Simulatorprofil kann im aktuellen Zustand nicht gewechselt werden");}else{int oldProfile=g_simActiveProfile;g_simProfileMode=SIM_RANDOM;for(int guard=0;guard<4&&g_simActiveProfile==oldProfile;guard++)SelectSimulatorProfile();SaveSettings();char pn[128];WToAscii(g_simProfileName,pn,128);sprintf(message,"Zufälliges Simulatorprofil: %s",pn);wchar_t ws[180];wsprintfW(ws,L"Simulatorprofil geladen: %s",g_simProfileName);SetStatus(ws);}}
        else if(QueryValueEquals(req,"name=","profile-save")){wchar_t pn[96],detail[256];QueryText(req,"profileName=",pn,96);ok=SaveNamedProfile(pn,TRUE,detail,256);WToAscii(detail,message,160);}
        else if(QueryValueEquals(req,"name=","profile-load")){wchar_t pn[96],detail[256];QueryText(req,"profileName=",pn,96);ok=LoadNamedProfile(pn,detail,256);WToAscii(detail,message,160);}
        else if(QueryValueEquals(req,"name=","profile-delete")){wchar_t pn[96],detail[256];QueryText(req,"profileName=",pn,96);ok=DeleteNamedProfile(pn,detail,256);WToAscii(detail,message,160);}
        else if(QueryValueEquals(req,"name=","profile-import")){wchar_t path[700],detail[256];QueryText(req,"path=",path,700);ok=ImportNamedProfile(path,detail,256);WToAscii(detail,message,160);}
        else if(QueryValueEquals(req,"name=","profile-export")){wchar_t pn[96],path[700],detail[256];QueryText(req,"profileName=",pn,96);QueryText(req,"path=",path,700);ok=ExportNamedProfile(pn,path,detail,256);WToAscii(detail,message,160);}
        else if(QueryValueEquals(req,"name=","shutdown")){g_shutdownRequested=TRUE;sprintf(message,"Programm wird beendet");}
        else if(QueryValueEquals(req,"name=","overlay-cycle")){g_overlayPreset=(g_overlayPreset+1)%4;if(g_overlayPreset==0){SetChecked(g_overlayStars,FALSE);SetChecked(g_overlayLabels,FALSE);SetChecked(g_zoneCheck,FALSE);}else if(g_overlayPreset==1){SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,FALSE);SetChecked(g_zoneCheck,FALSE);}else if(g_overlayPreset==2){SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,TRUE);SetChecked(g_zoneCheck,FALSE);}else{SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,FALSE);SetChecked(g_zoneCheck,TRUE);}sprintf(message,"Overlay gewechselt");}
        else{handled=FALSE;ok=FALSE;sprintf(message,"Unbekannte Aktion");}
        SendJsonResult(c,ok&&handled,message);p_closesocket(c);return;
    }
    if(RequestPathEquals(req,"/api/toggle")){
        QueryText(req,"value=",val,256);UINT toggleValue=0;if(!ParseStrictUIntW(val,&toggleValue)||toggleValue>1U){SetStatus(L"Ungültiger Schalterwert verworfen · zulässig: 0 oder 1");SendJsonResult(c,FALSE,"Ungültiger Schalterwert");p_closesocket(c);return;}BOOL on=toggleValue!=0,ok=TRUE,known=TRUE;
        if(QueryValueEquals(req,"name=","native")){if(g_cameraConnected){ok=FALSE;SetStatus(L"Kamera-Backend kann nur bei getrennter Kamera geändert werden");}else SetChecked(g_nativeCheck,on);}
        else if(QueryValueEquals(req,"name=","reconnect"))SetChecked(g_reconnectCheck,on);
        else if(QueryValueEquals(req,"name=","simulator")){if(g_focuserSetupReserved){ok=FALSE;SetStatus(L"Simulatorwechsel ist während des ASCOM-Treiberdialogs gesperrt");}else SetSimulatorMode(on);}
        else if(QueryValueEquals(req,"name=","demo")){SetChecked(g_demoCheck,on);g_demo=on;}
        else if(QueryValueEquals(req,"name=","stretch"))SetChecked(g_autoStretch,on);
        else if(QueryValueEquals(req,"name=","stars"))SetChecked(g_overlayStars,on);
        else if(QueryValueEquals(req,"name=","values"))SetChecked(g_overlayLabels,on);
        else if(QueryValueEquals(req,"name=","saturation"))SetChecked(g_overlaySat,on);
        else if(QueryValueEquals(req,"name=","zones"))SetChecked(g_zoneCheck,on);
        else if(QueryValueEquals(req,"name=","bahtinov"))SetChecked(g_bahtinovCheck,on);
        else if(QueryValueEquals(req,"name=","preferredOut"))SetChecked(g_preferredDirCheck,on);
        else if(QueryValueEquals(req,"name=","afSelectedStar")){if(g_afActive){ok=FALSE;SetStatus(L"Autofokus-Metrik kann während eines Laufs nicht geändert werden");}else if(on&&(!g_manualStarLocked||g_selectedStar<0)){ok=FALSE;g_afUseSelectedStar=FALSE;SetStatus(L"Bitte zuerst einen geeigneten Stern im Livebild anklicken");}else g_afUseSelectedStar=on;}
        else if(QueryValueEquals(req,"name=","autoRefocus"))SetAutoRefocusEnabled(on);
        else if(QueryValueEquals(req,"name=","tempComp"))g_tempCompEnabled=on;
        else if(QueryValueEquals(req,"name=","continuousFocus")){g_continuousFocusEnabled=on;g_continuousFocusPaused=FALSE;g_continuousFocusPhase=CF_IDLE;g_continuousFocusSampleCount=0;CopyWBounded(g_continuousFocusState,96,on?L"Wartet":L"Deaktiviert");CopyWBounded(g_continuousFocusReason,320,on?L"Wartet auf stabile Live-Messungen.":L"Kontinuierliche Fokusnachführung ist deaktiviert.");}
        else if(QueryValueEquals(req,"name=","continuousFocusFallback"))g_continuousFocusFallback=on;
        else if(QueryValueEquals(req,"name=","autoStartPosition")){g_autoStartPositionEnabled=on;if(on&&g_focuserConnected)g_autoStartPending=TRUE;}
        else if(QueryValueEquals(req,"name=","refocusOnMeridian"))g_refocusOnMeridian=on;
        else if(QueryValueEquals(req,"name=","refocusOnReconnect"))g_refocusOnReconnect=on;
        else if(QueryValueEquals(req,"name=","refocusOnFilter"))g_refocusOnFilter=on;
        else{known=FALSE;ok=FALSE;}
        if(ok&&known){SaveSettings();if(g_frameReady&&QueryValueEquals(req,"name=","stretch"))BuildDisplay();}
        SendJsonResult(c,ok&&known,ok?"Einstellung übernommen":"Einstellung abgelehnt oder unbekannt");p_closesocket(c);return;
    }
    if(RequestPathEquals(req,"/api/set")){
        QueryText(req,"value=",val,256);BOOL ok=TRUE,known=TRUE;UINT u=0;double d=0.0;
        if(QueryValueEquals(req,"name=","exposure")){if(ParseStrictDoubleW(val,&d)&&d>=1.0&&d<=60000.0)SetWindowTextW(g_exposureEdit,val);else{ok=FALSE;SetStatus(L"Ungültige Belichtungszeit verworfen · zulässig: 1 bis 60000 ms");}}
        else if(QueryValueEquals(req,"name=","gain")){if(ParseStrictUIntW(val,&u)&&u<=65535U)SetWindowTextW(g_gainEdit,val);else{ok=FALSE;SetStatus(L"Ungültiger Gain verworfen · zulässig: 0 bis 65535");}}
        else if(QueryValueEquals(req,"name=","manualStep")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=1000000U)SetWindowTextW(g_manualStepEdit,val);else{ok=FALSE;SetStatus(L"Ungültige manuelle Schrittweite verworfen");}}
        else if(QueryValueEquals(req,"name=","afPoints")){if(ParseStrictUIntW(val,&u)&&u>=5U&&u<=MAX_AF_POINTS&&(u&1U))SetWindowTextW(g_afPointsEdit,val);else{ok=FALSE;SetStatus(L"Ungültige Messpunktzahl verworfen · nur ungerade Werte von 5 bis 15");}}
        else if(QueryValueEquals(req,"name=","afStep")){if(ParseStrictUIntW(val,&u)&&u>=5U&&u<=1000000U)SetWindowTextW(g_afStepEdit,val);else{ok=FALSE;SetStatus(L"Ungültige Autofokus-Schrittweite verworfen");}}
        else if(QueryValueEquals(req,"name=","afSamples")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=MAX_AF_SAMPLES)SetWindowTextW(g_afSamplesEdit,val);else{ok=FALSE;SetStatus(L"Ungültige Anzahl Aufnahmen pro Messpunkt verworfen");}}
        else if(QueryValueEquals(req,"name=","backlash")){if(ParseStrictUIntW(val,&u)&&u<=1000000U)SetWindowTextW(g_afBacklashEdit,val);else{ok=FALSE;SetStatus(L"Ungültige Backlash-Kompensation verworfen");}}
        else if(QueryValueEquals(req,"name=","simBacklashSteps")){if(g_afActive||g_stepAssistActive||g_backlashCalActive){ok=FALSE;SetStatus(L"Simulator-Backlash kann während eines Fokusvorgangs nicht geändert werden");}else if(ParseStrictUIntW(val,&u)&&u<=5000U){g_simBacklashSteps=(int)u;g_simBacklashRemaining=0;g_simLastDirection=0;if(g_simulatorMode)g_simOpticalPosition=g_simPosition;}else{ok=FALSE;SetStatus(L"Ungültiges Simulator-Backlash verworfen · zulässig: 0 bis 5000 Schritte");}}
        else if(QueryValueEquals(req,"name=","simProfileMode")){if(g_afActive||g_stepAssistActive||g_backlashCalActive){ok=FALSE;SetStatus(L"Simulatorprofil kann während eines Fokusvorgangs nicht geändert werden");}else if(ParseStrictUIntW(val,&u)&&u<=SIM_RANDOM){g_simProfileMode=(int)u;SelectSimulatorProfile();wchar_t msg[180];wsprintfW(msg,L"Simulatorprofil: %s",g_simProfileName);SetStatus(msg);}else{ok=FALSE;SetStatus(L"Unbekanntes Simulatorprofil verworfen");}}
        else if(QueryValueEquals(req,"name=","continuousFocusMode")){if(ParseStrictUIntW(val,&u)&&u<=2U){g_continuousFocusMode=(int)u;g_continuousFocusSampleCount=0;}else{ok=FALSE;SetStatus(L"Ungültiger Modus der kontinuierlichen Fokusnachführung");}}
        else if(QueryValueEquals(req,"name=","continuousFocusMinFrames")){if(ParseStrictUIntW(val,&u)&&u>=3U&&u<=12U){g_continuousFocusMinFrames=(int)u;g_continuousFocusSampleCount=0;}else{ok=FALSE;SetStatus(L"Messfenster muss zwischen 3 und 12 Bildern liegen");}}
        else if(QueryValueEquals(req,"name=","continuousFocusDeadband")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=1000U){g_continuousFocusDeadband=(int)u;if(g_continuousFocusMaxStep<g_continuousFocusDeadband)g_continuousFocusMaxStep=g_continuousFocusDeadband;}else{ok=FALSE;SetStatus(L"Ungültige Nachführungs-Totzone");}}
        else if(QueryValueEquals(req,"name=","continuousFocusMaxStep")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=5000U&&(int)u>=g_continuousFocusDeadband)g_continuousFocusMaxStep=(int)u;else{ok=FALSE;SetStatus(L"Maximale Nachführungskorrektur muss mindestens der Totzone entsprechen");}}
        else if(QueryValueEquals(req,"name=","continuousFocusConfidence")){if(ParseStrictUIntW(val,&u)&&u>=30U&&u<=100U)g_continuousFocusMinConfidence=(int)u;else{ok=FALSE;SetStatus(L"Mindest-Regelqualität muss zwischen 30 und 100 Prozent liegen");}}
        else if(QueryValueEquals(req,"name=","continuousFocusImprovement")){if(ParseStrictDoubleW(val,&d)&&d>=0.1&&d<=25.0)g_continuousFocusMinImprovement=d;else{ok=FALSE;SetStatus(L"Mindestverbesserung muss zwischen 0,1 und 25 Prozent liegen");}}
        else if(QueryValueEquals(req,"name=","continuousFocusSettleMs")){if(ParseStrictUIntW(val,&u)&&u>=100U&&u<=30000U)g_continuousFocusSettleMs=(int)u;else{ok=FALSE;SetStatus(L"Beruhigungszeit muss zwischen 100 und 30000 ms liegen");}}
        else if(QueryValueEquals(req,"name=","refocusMinutes")){if(ParseStrictDoubleW(val,&d)&&d>=0.0&&d<=100000.0)SetWindowTextW(g_refocusMinutesEdit,val);else{ok=FALSE;SetStatus(L"Ungültiges Auto-Refokus-Intervall verworfen");}}
        else if(QueryValueEquals(req,"name=","refocusTemp")){if(ParseStrictDoubleW(val,&d)&&d>=0.0&&d<=100.0)SetWindowTextW(g_refocusTempEdit,val);else{ok=FALSE;SetStatus(L"Ungültige Auto-Refokus-Temperaturdifferenz verworfen");}}
        else if(QueryValueEquals(req,"name=","refocusFwhmPercent")){if(ParseStrictDoubleW(val,&d)&&d>=0.0&&d<=500.0){g_refocusFwhmThresholdPercent=d;g_focusDegradeFactor=1.0+d/100.0;g_degradationRefocusEnabled=d>0.0;g_refocusBadFrameStreak=0;}else{ok=FALSE;SetStatus(L"Ungültiger FWHM-Grenzwert verworfen · zulässig: 0 bis 500 Prozent");}}
        else if(QueryValueEquals(req,"name=","refocusBadFrames")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=100U){g_refocusBadFramesRequired=(int)u;g_refocusBadFrameStreak=0;}else{ok=FALSE;SetStatus(L"Ungültige Anzahl aufeinanderfolgender schlechter Bilder verworfen");}}
        else if(QueryValueEquals(req,"name=","refocusMinStars")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=160U){g_refocusMinStars=(int)u;g_refocusBadFrameStreak=0;if(g_autoRefocusReferenceReady&&g_usedCount<g_refocusMinStars){g_autoRefocusReferenceReady=FALSE;CopyWBounded(g_lastAutoRefocusReason,240,L"wartet auf Referenzbild mit konfigurierter Mindeststernzahl");}EnsureAutoRefocusMeasurementReference();}else{ok=FALSE;SetStatus(L"Ungültige Mindeststernzahl verworfen · zulässig: 1 bis 160");}}
        else if(QueryValueEquals(req,"name=","refocusStability")){if(ParseStrictDoubleW(val,&d)&&d>=0.01&&d<=20.0){g_refocusStabilityLimit=d;g_refocusBadFrameStreak=0;}else{ok=FALSE;SetStatus(L"Ungültige Stabilitätsgrenze verworfen · zulässig: 0,01 bis 20 Pixel");}}
        else if(QueryValueEquals(req,"name=","refocusCooldown")){if(ParseStrictDoubleW(val,&d)&&d>=0.0&&d<=1440.0)g_refocusCooldownMinutes=d;else{ok=FALSE;SetStatus(L"Ungültige Sperrzeit verworfen · zulässig: 0 bis 1440 Minuten");}}
        else if(QueryValueEquals(req,"name=","tempCompDeadband")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=5000U)g_tempCompDeadbandSteps=(int)u;else{ok=FALSE;SetStatus(L"Ungültige Totzone der Temperaturkompensation");}}
        else if(QueryValueEquals(req,"name=","tempCompMaxStep")){if(ParseStrictUIntW(val,&u)&&u>=1U&&u<=10000U)g_tempCompMaxStep=(int)u;else{ok=FALSE;SetStatus(L"Ungültige maximale Temperaturkorrektur");}}
        else if(QueryValueEquals(req,"name=","refocusEveryCaptures")){if(ParseStrictUIntW(val,&u)&&u<=100000U){g_refocusEveryCaptures=(int)u;g_captureEventCounter=0;}else{ok=FALSE;SetStatus(L"Ungültiges Aufnahmeintervall für Auto-Refokus");}}
        else if(QueryValueEquals(req,"name=","profile")){SetWindowTextW(g_profileEdit,val);}
        else if(QueryValueEquals(req,"name=","cameraId")){if(g_cameraConnected||g_afActive||g_stepAssistActive||g_backlashCalActive){ok=FALSE;SetStatus(L"ASCOM-Kamera kann während einer Verbindung oder Fokusoperation nicht gewechselt werden");}else if(!IsSafeAscomProgIdText(val)){ok=FALSE;SetStatus(L"Ungültige ASCOM-Kamera-ID verworfen");}else{CopyWBounded(g_cameraId,256,val);CopyWBounded(g_savedCameraId,256,val);g_externalCameraMode=FALSE;SetChecked(g_nativeCheck,FALSE);SetWindowTextW(g_cameraEdit,g_cameraId);SetStatus(L"ASCOM-Kamera ausgewählt · bereit zum Verbinden");}}
        else if(QueryValueEquals(req,"name=","focuserId")){if(g_focuserSetupReserved||g_focuserConnected||g_afActive||g_stepAssistActive||g_backlashCalActive){ok=FALSE;SetStatus(L"ASCOM-Fokussierer kann während einer Verbindung oder Fokusoperation nicht gewechselt werden");}else if(!IsSafeAscomProgIdText(val)){ok=FALSE;SetStatus(L"Ungültige ASCOM-Fokussierer-ID verworfen");}else{CopyWBounded(g_focuserId,256,val);CopyWBounded(g_savedFocuserId,256,val);SetWindowTextW(g_focuserEdit,g_focuserId);SetStatus(L"ASCOM-Fokussierer ausgewählt · bereit zum Verbinden");}}
        else if(QueryValueEquals(req,"name=","touptekDllPath")){if(g_cameraConnected||g_afActive||g_stepAssistActive||g_backlashCalActive){ok=FALSE;SetCameraActionMessage(L"Der ToupTek-SDK-Pfad kann nur bei getrennter Kamera und ohne laufende Fokusoperation geändert werden.");}else if(!IsSafeToupTekDllPath(val)){ok=FALSE;SetCameraActionMessage(L"Die ausgewählte Datei ist keine vorhandene absolute 64-Bit-toupcam.dll.");}else{if(g_toupDll)UnloadToupTek();CopyWBounded(g_toupTekDllPath,700,val);WriteIni(L"ToupTekDllPath",g_toupTekDllPath);SetCameraActionMessage(L"ToupTek-SDK-Pfad übernommen · Kamera kann jetzt erkannt oder verbunden werden.");}WToAscii(g_lastCameraActionMessage,message,768);}
        else if(QueryValueEquals(req,"name=","externalName")){if(!val[0]){ok=FALSE;SetStatus(L"Leerer USB/UVC-Gerätename verworfen");}else{lstrcpyW(g_externalCameraName,val);if(g_externalCameraMode){lstrcpyW(g_cameraId,val);SetWindowTextW(g_cameraEdit,g_cameraId);}}}
        else if(QueryValueEquals(req,"name=","safeMin")){if(ParseStrictUIntW(val,&u)&&u<=2147483647U&&(int)u<g_safeMaxPosition)g_safeMinPosition=(int)u;else{ok=FALSE;SetStatus(L"Ungültiges sicheres Minimum verworfen");}}
        else if(QueryValueEquals(req,"name=","safeMax")){if(ParseStrictUIntW(val,&u)&&u<=2147483647U&&(int)u>g_safeMinPosition)g_safeMaxPosition=(int)u;else{ok=FALSE;SetStatus(L"Ungültiges sicheres Maximum verworfen");}}
        else{known=FALSE;ok=FALSE;}
        if(ok&&known)SaveSettings();if(!QueryValueEquals(req,"name=","touptekDllPath"))sprintf(message,ok?"Wert übernommen":"Wert abgelehnt oder unbekannt");SendJsonResult(c,ok&&known,message);p_closesocket(c);return;
    }
    if(!RequestPathEquals(req,"/api/status")){SendJsonResult(c,FALSE,"Unbekannter API-Pfad");p_closesocket(c);return;}
    char cam[900],foc[900],profile[600],status[1200];WToJsonUtf8(g_cameraId,cam,900);WToJsonUtf8(g_focuserId,foc,900);GetWindowTextW(g_profileEdit,val,256);WToJsonUtf8(val,profile,600);GetWindowTextW(g_status,val,256);WToJsonUtf8(val,status,1200);
    wchar_t w[64];double refocusMinutesSetting=0.0,refocusTempSetting=0.0;char exposure[64],gain[64],manual[64],afPts[32],afStep[32],samples[32],backlash[32],refMin[32],refTemp[32];GetWindowTextW(g_exposureEdit,w,64);WToAscii(w,exposure,64);GetWindowTextW(g_gainEdit,w,64);WToAscii(w,gain,64);GetWindowTextW(g_manualStepEdit,w,64);WToAscii(w,manual,64);GetWindowTextW(g_afPointsEdit,w,64);WToAscii(w,afPts,32);GetWindowTextW(g_afStepEdit,w,64);WToAscii(w,afStep,32);GetWindowTextW(g_afSamplesEdit,w,64);WToAscii(w,samples,32);GetWindowTextW(g_afBacklashEdit,w,64);WToAscii(w,backlash,32);GetWindowTextW(g_refocusMinutesEdit,w,64);ParseStrictDoubleW(w,&refocusMinutesSetting);WToAscii(w,refMin,32);GetWindowTextW(g_refocusTempEdit,w,64);ParseStrictDoubleW(w,&refocusTempSetting);WToAscii(w,refTemp,32);
    int statusStarCount=g_starCount;if(statusStarCount<0)statusStarCount=0;if(statusStarCount>MAX_STARS)statusStarCount=MAX_STARS;int statusAfCount=g_afPointCount;if(statusAfCount<0)statusAfCount=0;if(statusAfCount>MAX_AF_POINTS)statusAfCount=MAX_AF_POINTS;
    int sel=g_selectedStar>=0&&g_selectedStar<statusStarCount&&IsTrackableFocusStar(&g_stars[g_selectedStar],FALSE)?g_selectedStar:-1;double sf=sel>=0?JsonNumber(g_stars[sel].fwhm):0,sh=sel>=0?JsonNumber(g_stars[sel].hfr):0,ss=sel>=0?JsonNumber(g_stars[sel].snr):0,se=sel>=0?JsonNumber(g_stars[sel].ecc):0;
    ULONGLONG statusNow=GetTickCount64();double refocusElapsed=g_lastAfCompleted?(double)(statusNow-g_lastAfCompleted)/60000.0:0.0;double refocusTempDelta=(g_hasFocuserTemperature&&g_hasLastAfTemperature)?fabs(g_focuserTemperature-g_lastAfTemperature):0.0;BOOL refocusTimeEnabled=FiniteD(refocusMinutesSetting)&&refocusMinutesSetting>0.0,refocusTemperatureEnabled=FiniteD(refocusTempSetting)&&refocusTempSetting>0.0,refocusFwhmEnabled=FiniteD(g_refocusFwhmThresholdPercent)&&g_refocusFwhmThresholdPercent>0.0;double refocusNextMinutes=refocusTimeEnabled?refocusMinutesSetting-refocusElapsed:-1.0;if(refocusTimeEnabled&&refocusNextMinutes<0.0)refocusNextMinutes=0.0;double refocusFwhmDegrade=(FiniteD(g_lastGoodFwhm)&&g_lastGoodFwhm>0.0&&FiniteD(g_medianFwhm))?((g_medianFwhm/g_lastGoodFwhm)-1.0)*100.0:0.0;int refocusRetrySeconds=statusNow<g_autoRefocusRetryAfter?(int)((g_autoRefocusRetryAfter-statusNow+999)/1000):0;double refocusCooldownRemaining=0.0;if(g_lastAfCompleted&&FiniteD(g_refocusCooldownMinutes)&&g_refocusCooldownMinutes>0.0){double elapsed=(double)(statusNow-g_lastAfCompleted)/60000.0;if(elapsed<g_refocusCooldownMinutes)refocusCooldownRemaining=g_refocusCooldownMinutes-elapsed;}int cameraWorkerRetrySeconds=statusNow<g_cameraWorkerRetryAfter?(int)((g_cameraWorkerRetryAfter-statusNow+999)/1000):0;int focuserWorkerRetrySeconds=statusNow<g_focuserWorkerRetryAfter?(int)((g_focuserWorkerRetryAfter-statusNow+999)/1000):0;char continuousFocusState[240],continuousFocusReason[900],refocusReason[480],afErrCode[160],afErrTitle[480],afErrDetail[1400],cameraWorkerOperation[256],focuserWorkerOperation[256],cameraRuntimeOperation[256],focuserRuntimeOperation[256],cameraRuntimePhase[64],focuserRuntimePhase[64],seeingState[320],focusNeedLabel[320],focusNeedReason[800],qualityLabel[320],fieldAdvice[800],currentFilter[160],lastExternalEvent[480],backlashResult[480],validationState[320],validationReason[900],simProfileName[320],fitMethod[420];WToJsonUtf8(g_continuousFocusState,continuousFocusState,240);WToJsonUtf8(g_continuousFocusReason,continuousFocusReason,900);WToJsonUtf8(g_lastAutoRefocusReason,refocusReason,480);WToJsonUtf8(g_lastAfErrorCode,afErrCode,160);WToJsonUtf8(g_lastAfErrorTitle,afErrTitle,480);WToJsonUtf8(g_lastAfErrorDetail,afErrDetail,1400);WToJsonUtf8(g_cameraWorkerFaultOperation,cameraWorkerOperation,256);WToJsonUtf8(g_focuserWorkerFaultOperation,focuserWorkerOperation,256);WToJsonUtf8(g_cameraRuntime.operation,cameraRuntimeOperation,256);WToJsonUtf8(g_focuserRuntime.operation,focuserRuntimeOperation,256);WToJsonUtf8(DevicePhaseNameW(g_cameraRuntime.phase),cameraRuntimePhase,64);WToJsonUtf8(DevicePhaseNameW(g_focuserRuntime.phase),focuserRuntimePhase,64);WToJsonUtf8(g_seeingState,seeingState,320);WToJsonUtf8(g_focusNeedLabel,focusNeedLabel,320);WToJsonUtf8(g_focusNeedReason,focusNeedReason,800);WToJsonUtf8(g_focusQualityLabel,qualityLabel,320);WToJsonUtf8(g_fieldAdvice,fieldAdvice,800);WToJsonUtf8(g_currentFilter,currentFilter,160);WToJsonUtf8(g_lastExternalEvent,lastExternalEvent,480);WToJsonUtf8(g_backlashCalResult,backlashResult,480);WToJsonUtf8(g_afValidationState,validationState,320);WToJsonUtf8(g_afValidationReason,validationReason,900);WToJsonUtf8(g_simProfileName,simProfileName,320);WToJsonUtf8(g_fitMethod,fitMethod,420);
    const int statusCapacity=262144;char* body=(char*)Alloc((SIZE_T)statusCapacity);if(!body){const char* e="{\"ok\":false,\"message\":\"Speicherfehler\"}";SendHttp(c,"application/json",e,ALen(e));p_closesocket(c);return;}int n=0;n+=sprintf(body+n,"{\"version\":\"3.9.0\",\"camera\":%s,\"focuser\":%s,\"focuserMoving\":%s,\"focuserSetupActive\":%s,\"autofocus\":%s,\"live\":%s,\"frameReady\":%s,\"frameSequence\":%u,\"cameraName\":\"%s\",\"focuserName\":\"%s\",\"profile\":\"%s\",\"profileRevision\":%d,\"status\":\"%s\",\"selfTestPassed\":%d,\"selfTestFailed\":%d,\"selfTestTotal\":%d,\"selfTestSummary\":\"%s\",",g_cameraConnected?"true":"false",g_focuserConnected?"true":"false",g_cachedFocuserMoving?"true":"false",g_focuserSetupReserved?"true":"false",g_afActive?"true":"false",g_live?"true":"false",g_frameReady?"true":"false",g_frameSequence,cam,foc,profile,g_profileRevision,status,g_selfTestPassed,g_selfTestFailed,g_selfTestTotal,g_selfTestSummary);
    n+=sprintf(body+n,"\"fwhm\":%.4f,\"hfr\":%.4f,\"snr\":%.4f,\"ecc\":%.4f,\"starCount\":%d,\"usedStars\":%d,\"position\":%d,\"stability\":%.4f,\"frameAgeMs\":%llu,\"hasTemperature\":%s,\"temperature\":%.3f,",JsonNumber(g_medianFwhm),JsonNumber(g_medianHfr),JsonNumber(g_medianSnr),JsonNumber(g_medianEcc),statusStarCount,g_usedCount,FocuserPosition(),JsonNumber(FocusStability()),g_lastFrameCompleted?(unsigned long long)(GetTickCount64()-g_lastFrameCompleted):0ULL,g_focuserConnected&&g_hasFocuserTemperature&&FiniteD(g_focuserTemperature)?"true":"false",JsonNumber(g_focuserTemperature));
    n+=sprintf(body+n,"\"seeingIndex\":%.2f,\"transparencyIndex\":%.2f,\"seeingState\":\"%s\",\"focusNeedScore\":%d,\"focusNeedLabel\":\"%s\",\"focusNeedReason\":\"%s\",\"afQualityScore\":%d,\"afQualityLabel\":\"%s\",",JsonNumber(g_seeingIndex),JsonNumber(g_transparencyIndex),seeingState,g_focusNeedScore,focusNeedLabel,focusNeedReason,g_focusQualityScore,qualityLabel);
    const char* ov=g_overlayPreset==0?"Aus":g_overlayPreset==1?"Minimal":g_overlayPreset==2?"Analyse":"Bildfeld";n+=sprintf(body+n,"\"overlayName\":\"%s\",\"bahtValid\":%s,\"bahtOffset\":%.4f,\"bahtConfidence\":%.4f,\"sharpness\":%.4f,\"selectedFwhm\":%.4f,\"selectedHfr\":%.4f,\"selectedSnr\":%.4f,\"selectedEcc\":%.4f,\"manualStarLocked\":%s,\"afUseSelectedStar\":%s,\"selectedStarMisses\":%d,\"afRecenterCount\":%d,\"afExpansionCount\":%d,",ov,g_bahtinovValid?"true":"false",JsonNumber(g_bahtinovOffset),JsonNumber(g_bahtinovConfidence),JsonNumber(g_bahtinovScore),sf,sh,ss,se,g_manualStarLocked?"true":"false",g_afUseSelectedStar?"true":"false",g_selectedStarMisses,g_afRecenterCount,g_afExpansionCount);
    n+=sprintf(body+n,"\"tiltValid\":%s,\"tilt\":%.4f,\"tiltConfidence\":%.2f,\"fieldCurvature\":%.4f,\"fieldAsymmetry\":%.4f,\"fieldQualityScore\":%.2f,\"fieldAdvice\":\"%s\",\"tiltDirection\":\"",g_tiltValid&&FiniteD(g_tiltMagnitude)?"true":"false",JsonNumber(g_tiltMagnitude),JsonNumber(g_tiltConfidence),JsonNumber(g_fieldCurvature),JsonNumber(g_fieldAsymmetry),JsonNumber(g_fieldQualityScore),fieldAdvice);char td[240];WToJsonUtf8(g_tiltDirection,td,240);n+=sprintf(body+n,"%s\",\"zoneFwhm\":[",td);for(int i=0;i<9;i++)n+=sprintf(body+n,i?",%.4f":"%.4f",JsonNumber(g_zoneFwhm[i]));n+=sprintf(body+n,"],\"zoneCounts\":[");for(int i=0;i<9;i++)n+=sprintf(body+n,i?",%d":"%d",g_zoneCount[i]);n+=sprintf(body+n,"],\"afPositions\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%d":"%d",g_afPositions[i]);n+=sprintf(body+n,"],\"afMetrics\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%.5f":"%.5f",JsonNumber(g_afMetrics[i]));n+=sprintf(body+n,"],\"afFwhmMetrics\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%.5f":"%.5f",JsonNumber(g_afFwhmMetrics[i]));
    n+=sprintf(body+n,"],\"afMetricSigma\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%.6f":"%.6f",JsonNumber(g_afMetricSigma[i]));n+=sprintf(body+n,"],\"afFwhmSigma\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%.6f":"%.6f",JsonNumber(g_afFwhmSigma[i]));n+=sprintf(body+n,"],\"afResiduals\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%.5f":"%.5f",JsonNumber(g_afResiduals[i]));n+=sprintf(body+n,"],\"afFwhmResiduals\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%.5f":"%.5f",JsonNumber(g_afFwhmResiduals[i]));n+=sprintf(body+n,"],\"afOutliers\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%d":"%d",g_afOutliers[i]?1:0);n+=sprintf(body+n,"],\"afSamplesPerPoint\":[");for(int i=0;i<statusAfCount;i++)n+=sprintf(body+n,i?",%d":"%d",g_afSamplesPerPoint[i]);
    n+=sprintf(body+n,"],\"afMeasuredCount\":%d,\"afFitValid\":%s,\"afFitFwhmValid\":%s,\"afFitModel\":%d,\"afFitFwhmModel\":%d,\"afFitMethod\":\"%s\",\"afFitA\":%.8f,\"afFitB\":%.8f,\"afFitC\":%.8f,\"afFitFwhmA\":%.8f,\"afFitFwhmB\":%.8f,\"afFitFwhmC\":%.8f,\"afFitCenter\":%.3f,\"afFitScale\":%.3f,\"afFitR2\":%.5f,\"afFitFwhmR2\":%.5f,\"afFitConfidence\":%.5f,\"afCurveQuality\":%.5f,\"afFocusSigma\":%.5f,\"afFocusSigmaLoo\":%.5f,\"afReducedChi2\":%.5f,\"afResidualRms\":%.5f,\"afAicc\":%.5f,\"afFitInliers\":%d,\"afFitOutliers\":%d,\"afAdaptiveSamplesAdded\":%d,\"afBestPosition\":%d,\"afExpectedHfr\":%.5f,\"afExpectedFwhm\":%.5f,\"afFinalValid\":%s,\"afFinalPosition\":%d,\"afFinalHfr\":%.5f,\"afFinalFwhm\":%.5f,\"afFitParams\":[%.9f,%.9f,%.9f,%.9f,%.9f],\"afFitFwhmParams\":[%.9f,%.9f,%.9f,%.9f,%.9f],",g_afPointIndex,g_fitValid?"true":"false",g_fitFwhmValid?"true":"false",g_fitModel,g_fitFwhmModel,fitMethod,JsonNumber(g_fitA),JsonNumber(g_fitB),JsonNumber(g_fitC),JsonNumber(g_fitFwhmA),JsonNumber(g_fitFwhmB),JsonNumber(g_fitFwhmC),JsonNumber(g_fitCenterPosition),JsonNumber(g_fitScale),JsonNumber(g_fitR2),JsonNumber(g_fitFwhmR2),JsonNumber(g_fitConfidence),JsonNumber(g_fitConfidence),JsonNumber(g_fitFocusSigma),JsonNumber(g_fitFocusSigmaLoo),JsonNumber(g_fitReducedChi2),JsonNumber(g_fitResidualRms),JsonNumber(g_fitAicc),g_fitInliers,g_fitOutliers,g_afAdaptiveSamplesAdded,g_afBestPosition,JsonNumber(g_afExpectedHfr),JsonNumber(g_afExpectedFwhm),g_afFinalValid?"true":"false",g_afFinalPosition,JsonNumber(g_afFinalHfr),JsonNumber(g_afFinalFwhm),JsonNumber(g_fitParams[0]),JsonNumber(g_fitParams[1]),JsonNumber(g_fitParams[2]),JsonNumber(g_fitParams[3]),JsonNumber(g_fitParams[4]),JsonNumber(g_fitFwhmParams[0]),JsonNumber(g_fitFwhmParams[1]),JsonNumber(g_fitFwhmParams[2]),JsonNumber(g_fitFwhmParams[3]),JsonNumber(g_fitFwhmParams[4]));
    n+=sprintf(body+n,"\"starX\":[");for(int i=0;i<statusStarCount;i++)n+=sprintf(body+n,i?",%.3f":"%.3f",JsonNumber(g_stars[i].x));n+=sprintf(body+n,"],\"starY\":[");for(int i=0;i<statusStarCount;i++)n+=sprintf(body+n,i?",%.3f":"%.3f",JsonNumber(g_stars[i].y));n+=sprintf(body+n,"],\"starFwhm\":[");for(int i=0;i<statusStarCount;i++)n+=sprintf(body+n,i?",%.3f":"%.3f",JsonNumber(g_stars[i].fwhm));n+=sprintf(body+n,"],\"starUsed\":[");for(int i=0;i<statusStarCount;i++)n+=sprintf(body+n,i?",%d":"%d",g_stars[i].used?1:0);n+=sprintf(body+n,"],\"starSaturated\":[");for(int i=0;i<statusStarCount;i++)n+=sprintf(body+n,i?",%d":"%d",g_stars[i].saturated?1:0);n+=sprintf(body+n,"],\"selectedStar\":%d",sel);
    n+=sprintf(body+n,",\"exposure\":\"%s\",\"gain\":\"%s\",\"manualStep\":\"%s\",\"afPoints\":\"%s\",\"afStep\":\"%s\",\"afSamples\":\"%s\",\"backlash\":\"%s\",\"refocusMinutes\":\"%s\",\"refocusTemp\":\"%s\",\"refocusFwhmPercent\":%.3f,\"refocusBadFrames\":%d,\"refocusMinStars\":%d,\"refocusStability\":%.4f,\"refocusCooldown\":%.3f,\"safeMin\":%d,\"safeMax\":%d,",exposure,gain,manual,afPts,afStep,samples,backlash,refMin,refTemp,JsonNumber(g_refocusFwhmThresholdPercent),g_refocusBadFramesRequired,g_refocusMinStars,JsonNumber(g_refocusStabilityLimit),JsonNumber(g_refocusCooldownMinutes),g_safeMinPosition,g_safeMaxPosition);
    n+=sprintf(body+n,"\"autoRefocusAutomaticRun\":%s,\"autoRefocusReferenceReady\":%s,\"autoRefocusReferenceFwhm\":%.4f,\"autoRefocusPaused\":%s,\"autoRefocusFailureCount\":%d,\"autoRefocusElapsedMinutes\":%.3f,\"autoRefocusNextMinutes\":%.3f,\"autoRefocusTempDelta\":%.3f,\"autoRefocusFwhmDegradePercent\":%.3f,\"autoRefocusTimeEnabled\":%s,\"autoRefocusTemperatureEnabled\":%s,\"autoRefocusFwhmEnabled\":%s,\"autoRefocusTemperatureRequired\":%s,\"autoRefocusLiveWillResume\":%s,\"autoRefocusRetrySeconds\":%d,\"autoRefocusBadFrameStreak\":%d,\"autoRefocusCooldownRemainingMinutes\":%.3f,\"autoRefocusLastReason\":\"%s\",\"autofocusErrorCode\":\"%s\",\"autofocusErrorTitle\":\"%s\",\"autofocusErrorDetail\":\"%s\",\"autofocusErrorAutomatic\":%s,",g_afAutomaticRun?"true":"false",g_autoRefocusReferenceReady?"true":"false",JsonNumber(g_lastGoodFwhm),g_autoRefocusPaused?"true":"false",g_autoRefocusFailureCount,JsonNumber(refocusElapsed),JsonNumber(refocusNextMinutes,-1.0),JsonNumber(refocusTempDelta),JsonNumber(refocusFwhmDegrade),refocusTimeEnabled?"true":"false",refocusTemperatureEnabled?"true":"false",refocusFwhmEnabled?"true":"false",refocusTemperatureEnabled?"true":"false",g_resumeLiveAfterAf?"true":"false",refocusRetrySeconds,g_refocusBadFrameStreak,JsonNumber(refocusCooldownRemaining),refocusReason,afErrCode,afErrTitle,afErrDetail,g_lastAfErrorAutomatic?"true":"false");
    n+=sprintf(body+n,"\"tempCompEnabled\":%s,\"tempCompDeadband\":%d,\"tempCompMaxStep\":%d,\"tempCompPredictedPosition\":%d,\"tempFitValid\":%s,\"tempSlope\":%.5f,\"tempIntercept\":%.3f,\"tempProfileCount\":%d,\"autoStartPosition\":%s,",g_tempCompEnabled?"true":"false",g_tempCompDeadbandSteps,g_tempCompMaxStep,g_lastTempCompTarget,g_tempFitValid?"true":"false",JsonNumber(g_tempSlope),JsonNumber(g_tempIntercept),g_tempProfileCount,g_autoStartPositionEnabled?"true":"false");
    n+=sprintf(body+n,"\"tempProfileTemperature\":[");for(int i=0;i<g_tempProfileCount;i++)n+=sprintf(body+n,i?",%.4f":"%.4f",JsonNumber(g_tempProfileT[i]));n+=sprintf(body+n,"],\"tempProfilePosition\":[");for(int i=0;i<g_tempProfileCount;i++)n+=sprintf(body+n,i?",%d":"%d",g_tempProfileP[i]);n+=sprintf(body+n,"],");
    {ULONGLONG now=GetTickCount64();double mins=g_sessionStartTick?(double)(now-g_sessionStartTick)/60000.0:0.0;n+=sprintf(body+n,"\"afValidationPassed\":%s,\"afRollbackPerformed\":%s,\"afValidationState\":\"%s\",\"afValidationReason\":\"%s\",\"sessionMinutes\":%.3f,\"sessionAfAttempts\":%d,\"sessionAfSuccess\":%d,\"sessionAfFailed\":%d,\"sessionAfRollbacks\":%d,\"sessionBestFwhm\":%.4f,\"sessionWorstFwhm\":%.4f,\"sessionStartPosition\":%d,\"sessionLastPosition\":%d,\"sessionHasTemperature\":%s,\"sessionStartTemperature\":%.3f,\"sessionLastTemperature\":%.3f,",g_afValidationPassed?"true":"false",g_afRollbackPerformed?"true":"false",validationState,validationReason,JsonNumber(mins),g_sessionAfAttempts,g_sessionAfSuccess,g_sessionAfFailed,g_sessionAfRollbacks,JsonNumber(g_sessionBestFwhm),JsonNumber(g_sessionWorstFwhm),g_sessionStartPosition,g_sessionLastPosition,g_sessionHasTemperature?"true":"false",JsonNumber(g_sessionStartTemperature),JsonNumber(g_sessionLastTemperature));}
    n+=sprintf(body+n,"\"profileModelValid\":%s,\"profileSuccessfulRuns\":%d,\"profileTypicalPosition\":%d,\"profileTypicalFwhm\":%.4f,\"profileTypicalHfr\":%.4f,\"profileQualityMean\":%.2f,\"profileRecommendedStep\":%d,\"profileBacklash\":%d,",g_profileModelValid?"true":"false",g_profileSuccessfulRuns,g_profileTypicalPosition,JsonNumber(g_profileTypicalFwhm),JsonNumber(g_profileTypicalHfr),JsonNumber(g_profileQualityMean),g_profileRecommendedStep,g_profileBacklash);
    n+=sprintf(body+n,"\"stepAssistantActive\":%s,\"backlashCalibrationActive\":%s,\"backlashCalibrationEstimated\":%d,\"backlashCalibrationProgress\":%d,\"backlashCalibrationLimit\":%d,\"backlashCalibrationResult\":\"%s\",\"simProfileMode\":%d,\"simActiveProfile\":%d,\"simProfileName\":\"%s\",\"simBacklashSteps\":%d,\"simRandomSeed\":%u,\"simBacklashRemaining\":%d,\"simMotorPosition\":%d,\"simOpticalPosition\":%d,\"currentFilter\":\"%s\",\"filterOffsetCount\":%d,\"filterRefocusPending\":%s,\"refocusOnMeridian\":%s,\"refocusOnReconnect\":%s,\"refocusOnFilter\":%s,\"refocusEveryCaptures\":%d,\"captureEventCounter\":%d,\"lastExternalEvent\":\"%s\",",g_stepAssistActive?"true":"false",g_backlashCalActive?"true":"false",g_backlashCalEstimated,g_backlashCalCumulative,g_backlashCalMaxReverse,backlashResult,g_simProfileMode,g_simActiveProfile,simProfileName,g_simBacklashSteps,g_simRandomSeed,g_simBacklashRemaining,g_simPosition,g_simOpticalPosition,currentFilter,g_filterOffsetCount,g_filterRefocusPending?"true":"false",g_refocusOnMeridian?"true":"false",g_refocusOnReconnect?"true":"false",g_refocusOnFilter?"true":"false",g_refocusEveryCaptures,g_captureEventCounter,lastExternalEvent);
    n+=sprintf(body+n,"\"cameraWorkerBlocked\":%s,\"cameraWorkerRetrySeconds\":%d,\"cameraWorkerOperation\":\"%s\",\"focuserWorkerBlocked\":%s,\"focuserWorkerRetrySeconds\":%d,\"focuserWorkerOperation\":\"%s\",",g_cameraWorkerBlocked?"true":"false",cameraWorkerRetrySeconds,cameraWorkerOperation,g_focuserWorkerBlocked?"true":"false",focuserWorkerRetrySeconds,focuserWorkerOperation);
    n+=sprintf(body+n,"\"cameraDevicePhase\":\"%s\",\"cameraDeviceOperation\":\"%s\",\"cameraOperationId\":%llu,\"cameraHostPid\":%lu,\"cameraLastSuccessAgeMs\":%llu,\"cameraRemovalDetected\":%s,\"focuserDevicePhase\":\"%s\",\"focuserDeviceOperation\":\"%s\",\"focuserOperationId\":%llu,\"focuserHostPid\":%lu,\"focuserLastSuccessAgeMs\":%llu,\"focuserRemovalDetected\":%s,\"focuserPositionKnown\":%s,",cameraRuntimePhase,cameraRuntimeOperation,(unsigned long long)g_cameraRuntime.operationId,g_cameraWorker?g_cameraWorker->hostPid:0UL,g_cameraRuntime.lastSuccessTick?(unsigned long long)(statusNow-g_cameraRuntime.lastSuccessTick):0ULL,g_cameraRuntime.removalDetected?"true":"false",focuserRuntimePhase,focuserRuntimeOperation,(unsigned long long)g_focuserRuntime.operationId,g_focuserWorker?g_focuserWorker->hostPid:0UL,g_focuserRuntime.lastSuccessTick?(unsigned long long)(statusNow-g_focuserRuntime.lastSuccessTick):0ULL,g_focuserRuntime.removalDetected?"true":"false",g_focuserRuntime.positionKnown?"true":"false");
    n+=sprintf(body+n,"\"native\":%s,\"reconnect\":%s,\"simulator\":%s,\"external\":%s,\"demo\":%s,\"stretch\":%s,\"stars\":%s,\"values\":%s,\"saturation\":%s,\"zones\":%s,\"bahtinov\":%s,\"preferredOut\":%s,\"autoRefocus\":%s,\"tempComp\":%s,\"autoStartPositionEnabled\":%s,\"continuousFocusEnabled\":%s,\"continuousFocusFallback\":%s,\"continuousFocusPaused\":%s,\"continuousFocusMode\":%d,\"continuousFocusPhase\":%d,\"continuousFocusState\":\"%s\",\"continuousFocusReason\":\"%s\",\"continuousFocusMinFrames\":%d,\"continuousFocusDeadband\":%d,\"continuousFocusMaxStep\":%d,\"continuousFocusMinConfidence\":%d,\"continuousFocusMinImprovement\":%.3f,\"continuousFocusSettleMs\":%d,\"continuousFocusConfidence\":%.2f,\"continuousFocusReferenceMetric\":%.5f,\"continuousFocusEstimatedError\":%.2f,\"continuousFocusDriftStepsPerMinute\":%.3f,\"continuousFocusLastCorrection\":%d,\"continuousFocusTarget\":%d,\"continuousFocusAccepted\":%d,\"continuousFocusRejected\":%d}",IsChecked(g_nativeCheck)?"true":"false",IsChecked(g_reconnectCheck)?"true":"false",g_simulatorMode?"true":"false",g_externalCameraMode?"true":"false",g_demo?"true":"false",IsChecked(g_autoStretch)?"true":"false",IsChecked(g_overlayStars)?"true":"false",IsChecked(g_overlayLabels)?"true":"false",IsChecked(g_overlaySat)?"true":"false",IsChecked(g_zoneCheck)?"true":"false",IsChecked(g_bahtinovCheck)?"true":"false",IsChecked(g_preferredDirCheck)?"true":"false",g_autoRefocusEnabled?"true":"false",g_tempCompEnabled?"true":"false",g_autoStartPositionEnabled?"true":"false",g_continuousFocusEnabled?"true":"false",g_continuousFocusFallback?"true":"false",g_continuousFocusPaused?"true":"false",g_continuousFocusMode,g_continuousFocusPhase,continuousFocusState,continuousFocusReason,g_continuousFocusMinFrames,g_continuousFocusDeadband,g_continuousFocusMaxStep,g_continuousFocusMinConfidence,JsonNumber(g_continuousFocusMinImprovement),g_continuousFocusSettleMs,JsonNumber(g_continuousFocusConfidence),JsonNumber(g_continuousFocusReferenceMetric),JsonNumber(g_continuousFocusEstimatedError),JsonNumber(g_continuousFocusDriftStepsPerMinute),g_continuousFocusLastCorrection,g_continuousFocusTarget,g_continuousFocusAccepted,g_continuousFocusRejected);if(n<=0||n>=statusCapacity){const char* e="{\"ok\":false,\"message\":\"Statusantwort zu groß\"}";SendHttp(c,"application/json",e,ALen(e));}else SendHttp(c,"application/json",body,n);Free(body);p_closesocket(c);
}

static void PutLe16(BYTE* p,UINT v){p[0]=(BYTE)(v&255U);p[1]=(BYTE)((v>>8)&255U);}
static void PutLe32(BYTE* p,UINT v){p[0]=(BYTE)(v&255U);p[1]=(BYTE)((v>>8)&255U);p[2]=(BYTE)((v>>16)&255U);p[3]=(BYTE)((v>>24)&255U);}
static void* Alloc(SIZE_T n){return HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,n);}
static void Free(void* p){if(p)HeapFree(GetProcessHeap(),0,p);}
static int WLen(LPCWSTR s){return lstrlenW(s);}
static void SetControlFont(HWND h,HFONT f){SendMessageW(h,WM_SETFONT,(WPARAM)f,TRUE);}
static BOOL IsChecked(HWND h){return SendMessageW(h,BM_GETCHECK,0,0)==BST_CHECKED;}
static void SetChecked(HWND h,BOOL v){SendMessageW(h,BM_SETCHECK,v?BST_CHECKED:0,0);}

static UINT ParseUIntW(LPCWSTR s,UINT fallback){
    if(!s)return fallback;unsigned long long v=0;BOOL any=FALSE;for(int i=0;s[i];i++){if(s[i]>=L'0'&&s[i]<=L'9'){unsigned digit=(unsigned)(s[i]-L'0');if(v>(0xffffffffULL-digit)/10ULL)return fallback;any=TRUE;v=v*10ULL+digit;}else if(s[i]!=L' '&&s[i]!=L'\t')return fallback;}return any?(UINT)v:fallback;
}
static BOOL ParseStrictUIntW(LPCWSTR s,UINT* out){
    if(!s||!out)return FALSE;int i=0;while(s[i]==L' '||s[i]==L'\t')i++;if(s[i]==L'+')i++;if(s[i]<L'0'||s[i]>L'9')return FALSE;
    unsigned long long v=0;for(;s[i]>=L'0'&&s[i]<=L'9';i++){unsigned digit=(unsigned)(s[i]-L'0');if(v>(0xffffffffULL-digit)/10ULL)return FALSE;v=v*10ULL+digit;}
    while(s[i]==L' '||s[i]==L'\t')i++;if(s[i])return FALSE;*out=(UINT)v;return TRUE;
}
static BOOL ParseStrictIntW(LPCWSTR s,int* out){
    if(!s||!out)return FALSE;int i=0;while(s[i]==L' '||s[i]==L'\t')i++;BOOL neg=FALSE;if(s[i]==L'-'){neg=TRUE;i++;}else if(s[i]==L'+')i++;
    if(s[i]<L'0'||s[i]>L'9')return FALSE;unsigned long long limit=neg?2147483648ULL:2147483647ULL,v=0;
    for(;s[i]>=L'0'&&s[i]<=L'9';i++){unsigned digit=(unsigned)(s[i]-L'0');if(v>(limit-digit)/10ULL)return FALSE;v=v*10ULL+digit;}
    while(s[i]==L' '||s[i]==L'\t')i++;if(s[i])return FALSE;*out=neg?(v==2147483648ULL?(-2147483647-1):-(int)v):(int)v;return TRUE;
}
static int RoundedModelPosition(double value,int minimum,int maximum){
    if(!FiniteD(value))return minimum<=0&&maximum>=0?0:minimum;double lo=(double)minimum,hi=(double)maximum;if(value<=lo)return minimum;if(value>=hi)return maximum;
    return (int)(value+(value>=0.0?0.5:-0.5));
}
static UINT NormalizeAfPointCount(UINT v){if(v<5U)v=5U;if(v>MAX_AF_POINTS)v=MAX_AF_POINTS;if(!(v&1U))v--;if(v<5U)v=5U;return v;}
static UINT NormalizeAfPointText(LPCWSTR text){UINT v=9U;if(!ParseStrictUIntW(text,&v))return 9U;return NormalizeAfPointCount(v);}
static BOOL ParseStrictDoubleW(LPCWSTR s,double* out){
    if(!s||!out)return FALSE;int i=0;while(s[i]==L' '||s[i]==L'\t')i++;BOOL neg=FALSE;if(s[i]==L'-'){neg=TRUE;i++;}else if(s[i]==L'+')i++;
    double v=0.0,scale=0.1;BOOL any=FALSE,frac=FALSE;for(;s[i];i++){wchar_t c=s[i];if(c>=L'0'&&c<=L'9'){any=TRUE;if(frac){v+=(double)(c-L'0')*scale;scale*=0.1;}else{v=v*10.0+(double)(c-L'0');if(v>1.0e12)return FALSE;}}else if((c==L'.'||c==L',')&&!frac)frac=TRUE;else break;}
    while(s[i]==L' '||s[i]==L'\t')i++;if(!any||s[i])return FALSE;*out=neg?-v:v;return TRUE;
}
static void U64ToW(unsigned long long v,wchar_t* out){wchar_t t[32];int n=0;do{t[n++]=(wchar_t)(L'0'+(v%10));v/=10;}while(v&&n<31);int j=0;while(n)out[j++]=t[--n];out[j]=0;}
static void FormatFixed(double v,int decimals,wchar_t* out){
    if(!out)return;if(!FiniteD(v)||v<-1.0e12||v>1.0e12||decimals<0||decimals>9){lstrcpyW(out,L"–");return;}
    BOOL neg=v<0.0;double a=neg?-v:v;unsigned long long scale=1;for(int i=0;i<decimals;i++)scale*=10;
    unsigned long long z=(unsigned long long)(a*(double)scale+0.5);unsigned long long whole=z/scale,frac=z%scale;wchar_t w[48];U64ToW(whole,w);int p=0;if(neg)out[p++]=L'-';for(int i=0;w[i]&&p<62;i++)out[p++]=w[i];if(decimals&&p<62){out[p++]=L',';wchar_t f[24];for(int i=decimals-1;i>=0;i--){f[i]=(wchar_t)(L'0'+frac%10);frac/=10;}for(int i=0;i<decimals&&p<63;i++)out[p++]=f[i];}out[p]=0;
}
static void SetStatus(LPCWSTR text){SetWindowTextW(g_status,text);}
static void CopyWBounded(LPWSTR out,int cap,LPCWSTR in);
static void SetCameraActionMessage(LPCWSTR text){CopyWBounded(g_lastCameraActionMessage,512,text&&*text?text:L"Kameraaktion fehlgeschlagen.");if(text&&*text)SetStatus(text);}
static void SetFocuserActionMessage(LPCWSTR text){CopyWBounded(g_lastFocuserActionMessage,512,text&&*text?text:L"Fokussiereraktion fehlgeschlagen.");if(text&&*text)SetStatus(text);}
static BOOL FileExistsW(LPCWSTR path){DWORD a=path&&*path?GetFileAttributesW(path):0xffffffffUL;return a!=0xffffffffUL&&(a&0x10UL)==0;}
static wchar_t LowerAsciiW(wchar_t c){return c>=L'A'&&c<=L'Z'?(wchar_t)(c+32):c;}
static BOOL PathHasToupCamFileName(LPCWSTR path){if(!path||!*path)return FALSE;int n=WLen(path),start=n;while(start>0&&path[start-1]!=L'\\'&&path[start-1]!=L'/')start--;LPCWSTR name=L"toupcam.dll";int m=WLen(name);if(n-start!=m)return FALSE;for(int i=0;i<m;i++)if(LowerAsciiW(path[start+i])!=name[i])return FALSE;return TRUE;}
static BOOL IsSafeToupTekDllPath(LPCWSTR path){if(!path||!PathHasToupCamFileName(path)||!FileExistsW(path))return FALSE;BOOL absolute=(path[0]&&path[1]==L':'&&(path[2]==L'\\'||path[2]==L'/'))||(path[0]==L'\\'&&path[1]==L'\\');return absolute;}
static BOOL WContains(LPCWSTR text,LPCWSTR needle){if(!text||!needle||!*needle)return FALSE;for(int i=0;text[i];i++){int j=0;while(needle[j]&&text[i+j]==needle[j])j++;if(!needle[j])return TRUE;}return FALSE;}
static BOOL WEquals(LPCWSTR a,LPCWSTR b){if(!a||!b)return FALSE;int i=0;while(a[i]&&b[i]&&a[i]==b[i])i++;return a[i]==0&&b[i]==0;}
static void CopyWBounded(LPWSTR out,int cap,LPCWSTR in){if(!out||cap<=0)return;int i=0;for(;in&&in[i]&&i<cap-1;i++)out[i]=in[i];out[i]=0;}
static void CatWBounded(LPWSTR out,int cap,LPCWSTR in){if(!out||cap<=0)return;int n=0;while(n<cap-1&&out[n])n++;int i=0;while(in&&in[i]&&n<cap-1)out[n++]=in[i++];out[n]=0;}
static void SetAutofocusError(LPCWSTR code,LPCWSTR title,LPCWSTR detail,BOOL automatic){
    CopyWBounded(g_lastAfErrorCode,64,code&&*code?code:L"AF_UNKNOWN");CopyWBounded(g_lastAfErrorTitle,160,title&&*title?title:L"Autofokusfehler");CopyWBounded(g_lastAfErrorDetail,512,detail&&*detail?detail:L"Keine weiteren Details verfügbar.");g_lastAfErrorAutomatic=automatic;g_lastAfErrorTick=GetTickCount64();
}
static void ClearAutofocusError(){lstrcpyW(g_lastAfErrorCode,L"NONE");lstrcpyW(g_lastAfErrorTitle,L"Kein Autofokusfehler");g_lastAfErrorDetail[0]=0;g_lastAfErrorAutomatic=FALSE;g_lastAfErrorTick=0;}
static void ClassifyAutofocusFailure(LPCWSTR reason,BOOL automatic){
    if(!reason||!*reason){SetAutofocusError(L"AF_UNKNOWN",L"Autofokus fehlgeschlagen",L"Der Fokuslauf wurde ohne detaillierte Fehlermeldung beendet.",automatic);return;}
    if(WContains(reason,L"abgebrochen")||WContains(reason,L"angehalten")||WContains(reason,L"manuell beendet")){SetAutofocusError(L"AF_CANCELLED",L"Autofokus abgebrochen",reason,automatic);return;}
    if(WContains(reason,L"Fokusstern")&&(WContains(reason,L"verloren")||WContains(reason,L"nicht erkannt"))){SetAutofocusError(L"AF_FOCUS_STAR_LOST",L"Fokusstern verloren",reason,automatic);return;}
    if(WContains(reason,L"weniger als vier")||WContains(reason,L"Zu wenige")||WContains(reason,L"zu wenige")||WContains(reason,L"Messpunkt nach drei")){SetAutofocusError(L"AF_TOO_FEW_STARS",L"Zu wenige geeignete Sterne",reason,automatic);return;}
    if(WContains(reason,L"sichere Fokuszone")||WContains(reason,L"außerhalb der sicheren")){SetAutofocusError(L"AF_TARGET_OUTSIDE_SAFE_ZONE",L"Zielposition außerhalb der sicheren Zone",reason,automatic);return;}
    if(WContains(reason,L"bewegt sich noch")||WContains(reason,L"noch nicht beendet")){SetAutofocusError(L"AF_FOCUSER_BUSY",L"Fokussierer meldet Bewegung noch nicht beendet",reason,automatic);return;}
    if(WContains(reason,L"Position unbekannt")||WContains(reason,L"Fokusposition ist unbekannt")){SetAutofocusError(L"AF_POSITION_UNKNOWN",L"Fokusposition unbekannt",reason,automatic);return;}
    if(WContains(reason,L"Fokussierer-Zeitüberschreitung")||WContains(reason,L"Fokussierer reagiert nicht")||WContains(reason,L"Fokussierer blockiert")){SetAutofocusError(L"AF_FOCUSER_TIMEOUT",L"Fokussierer antwortet nicht",reason,automatic);return;}
    if(WContains(reason,L"Fokussierer getrennt")||WContains(reason,L"Fokussierer verbunden sein")){SetAutofocusError(L"AF_FOCUSER_NOT_CONNECTED",L"Fokussierer nicht verbunden",reason,automatic);return;}
    if(WContains(reason,L"Kamera getrennt")||WContains(reason,L"USB/UVC-Kamera getrennt")||WContains(reason,L"ToupTek-Kamera getrennt")){SetAutofocusError(L"AF_CAMERA_REMOVED",L"Kamera wurde getrennt",reason,automatic);return;}
    if(WContains(reason,L"Kamera")&&WContains(reason,L"verbunden sein")){SetAutofocusError(L"AF_CAMERA_NOT_CONNECTED",L"Kamera nicht verbunden",reason,automatic);return;}
    if(WContains(reason,L"Bildübertragung")||WContains(reason,L"Belichtung")||WContains(reason,L"Kamera-Zeitüberschreitung")||WContains(reason,L"Zeitüberschreitung der Kamera")){SetAutofocusError(L"AF_CAMERA_CAPTURE_FAILED",L"Kameraaufnahme fehlgeschlagen",reason,automatic);return;}
    if(WContains(reason,L"Fokusbewegung fehlgeschlagen")||WContains(reason,L"Position konnte nicht gelesen")||WContains(reason,L"ASCOM")){SetAutofocusError(L"AF_ASCOM_DRIVER_NOT_RESPONDING",L"ASCOM-Treiber antwortet nicht",reason,automatic);return;}
    if(WContains(reason,L"Kontrollmedian bestätigt")||WContains(reason,L"Endposition")||WContains(reason,L"verbessert den Fokus nicht")){SetAutofocusError(L"AF_END_POSITION_NOT_IMPROVED",L"Endposition verbessert den Fokus nicht",reason,automatic);return;}
    if(WContains(reason,L"Fokuskurve")||WContains(reason,L"beidseitig")||WContains(reason,L"Fit")){SetAutofocusError(L"AF_FIT_QUALITY_INSUFFICIENT",L"Fitqualität unzureichend",reason,automatic);return;}
    SetAutofocusError(L"AF_UNKNOWN",L"Autofokus fehlgeschlagen",reason,automatic);
}
static void EnsureAutoRefocusMeasurementReference(){
    if(!g_autoRefocusEnabled||g_autoRefocusReferenceReady)return;
    if(g_frameReady&&g_lastCompletedPurpose==1&&g_medianFwhm>0.0&&g_usedCount>=g_refocusMinStars){g_lastGoodFwhm=g_medianFwhm;g_autoRefocusReferenceReady=TRUE;g_lastAfCompleted=GetTickCount64();lstrcpyW(g_lastAutoRefocusReason,L"erste Live-Referenzmessung übernommen");}
}

static LPCWSTR DevicePhaseNameW(DeviceRuntimePhase phase){
    if(phase==DEV_CONNECTING)return L"CONNECTING";if(phase==DEV_READY)return L"READY";if(phase==DEV_BUSY)return L"BUSY";
    if(phase==DEV_RECOVERING)return L"RECOVERING";if(phase==DEV_FAULTED)return L"FAULTED";if(phase==DEV_POSITION_UNKNOWN)return L"POSITION_UNKNOWN";return L"DISCONNECTED";
}
static void AppendHardwareEvent(BOOL camera,LPCWSTR eventName,const DeviceRuntimeState* state,HRESULT hr){
    if(!g_hardwareLogPath[0]||!state)return;SYSTEMTIME st;GetLocalTime(&st);char eventA[160],opA[320],phaseA[80];WToJsonUtf8(eventName,eventA,160);WToJsonUtf8(state->operation,opA,320);WToJsonUtf8(DevicePhaseNameW(state->phase),phaseA,80);
    char line[1400];int n=sprintf(line,"{\"time\":\"%04u-%02u-%02uT%02u:%02u:%02u.%03u\",\"device\":\"%s\",\"event\":\"%s\",\"phase\":\"%s\",\"operationId\":%llu,\"operation\":\"%s\",\"startedTick\":%llu,\"deadlineTick\":%llu,\"lastSuccessTick\":%llu,\"retryCount\":%d,\"positionKnown\":%s,\"removed\":%s,\"hr\":%ld}\r\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,camera?"camera":"focuser",eventA,phaseA,state->operationId,opA,state->startedTick,state->deadlineTick,state->lastSuccessTick,state->retryCount,state->positionKnown?"true":"false",state->removalDetected?"true":"false",(long)hr);
    if(n<=0||n>=(int)sizeof(line))return;HANDLE h=CreateFileW(g_hardwareLogPath,GENERIC_WRITE,FILE_SHARE_READ,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return;SetFilePointer(h,0,0,FILE_END);WriteAllHandle(h,line,(DWORD)n);CloseHandle(h);
}
static DeviceRuntimeState* WorkerRuntime(DeviceWorker* w){return w?(w->camera?&g_cameraRuntime:&g_focuserRuntime):0;}
static void DeviceRuntimeSetPhase(BOOL camera,DeviceRuntimePhase phase,LPCWSTR operation,HRESULT hr,BOOL logEvent){
    DeviceRuntimeState* s=camera?&g_cameraRuntime:&g_focuserRuntime;s->phase=phase;s->lastError=hr;if(operation)CopyWBounded(s->operation,96,operation);if(logEvent)AppendHardwareEvent(camera,L"phase",s,hr);
}
static void DeviceRuntimeBegin(DeviceWorker* w,LPCWSTR operation,DWORD timeoutMs){
    DeviceRuntimeState* s=WorkerRuntime(w);if(!s)return;s->operationId=g_nextDeviceOperationId++;if(g_nextDeviceOperationId==0)g_nextDeviceOperationId=1;s->startedTick=GetTickCount64();s->deadlineTick=s->startedTick+(ULONGLONG)timeoutMs;s->lastError=S_OK;s->removalDetected=FALSE;CopyWBounded(s->operation,96,operation?operation:L"device operation");s->phase=(w->command==DW_CONNECT_CAMERA||w->command==DW_CONNECT_FOCUSER)?DEV_CONNECTING:DEV_BUSY;AppendHardwareEvent(w->camera,L"begin",s,S_OK);
}
static void DeviceRuntimeComplete(DeviceWorker* w,HRESULT hr){
    DeviceRuntimeState* s=WorkerRuntime(w);if(!s)return;ULONGLONG now=GetTickCount64();s->lastHeartbeatTick=now;s->lastError=hr;
    if(SUCCEEDED(hr)){s->lastSuccessTick=now;s->retryCount=0;if(w->command==DW_DISCONNECT||w->command==DW_SHUTDOWN)s->phase=DEV_DISCONNECTED;else s->phase=DEV_READY;if(!w->camera&&w->command==DW_GET_INT&&WEquals(w->member,L"Position")&&w->intResult>=0)s->positionKnown=TRUE;AppendHardwareEvent(w->camera,L"complete",s,hr);}else{s->phase=DEV_FAULTED;s->retryCount++;if(!w->camera&&(w->command==DW_CALL_INT||w->command==DW_GET_INT))s->positionKnown=FALSE;AppendHardwareEvent(w->camera,L"failed",s,hr);}
}
static void DeviceRuntimeTimeout(DeviceWorker* w,LPCWSTR operation){
    DeviceRuntimeState* s=WorkerRuntime(w);if(!s)return;s->phase=DEV_FAULTED;s->lastError=(HRESULT)0x800705B4L;s->retryCount++;if(operation)CopyWBounded(s->operation,96,operation);if(!w->camera)s->positionKnown=FALSE;AppendHardwareEvent(w->camera,L"timeout",s,s->lastError);
}

static void CopyPathParts(LPCWSTR root,LPCWSTR name,LPWSTR out,int cap){if(!out||cap<=0)return;int o=0;for(int i=0;root&&root[i]&&o<cap-1;i++)out[o++]=root[i];for(int i=0;name&&name[i]&&o<cap-1;i++)out[o++]=name[i];out[o]=0;}
static void BuildIniPath(){
    wchar_t path[520];DWORD n=GetModuleFileNameW(0,path,520);if(n==0||n>=519)return;int slash=-1;for(int i=0;path[i];i++)if(path[i]==L'\\'||path[i]==L'/')slash=i;if(slash<0)return;path[slash+1]=0;lstrcpyW(g_appDir,path);
    wchar_t local[440];DWORD ln=GetEnvironmentVariableW(L"LOCALAPPDATA",local,440);if(ln>0&&ln<438){lstrcpyW(g_dataDir,local);int l=WLen(g_dataDir);if(l>0&&g_dataDir[l-1]!=L'\\')lstrcatW(g_dataDir,L"\\");lstrcatW(g_dataDir,L"AstroFocusStudio\\");wchar_t noSlash[520];lstrcpyW(noSlash,g_dataDir);int dl=WLen(noSlash);if(dl>0&&noSlash[dl-1]==L'\\')noSlash[dl-1]=0;CreateDirectoryW(noSlash,0);}else lstrcpyW(g_dataDir,g_appDir);
    CopyPathParts(g_dataDir,L"Logs",g_logDir,560);CreateDirectoryW(g_logDir,0);lstrcatW(g_logDir,L"\\");
    CopyPathParts(g_dataDir,L"Updates",g_updateDir,560);CreateDirectoryW(g_updateDir,0);lstrcatW(g_updateDir,L"\\");
    CopyPathParts(g_logDir,L"HardwareEvents.jsonl",g_hardwareLogPath,700);
    CopyPathParts(g_dataDir,L"AstroFocusStudio.ini",g_iniPath,520);
    wchar_t legacy[600];CopyPathParts(g_appDir,L"AstroFocusStudio.ini",legacy,600);if(GetFileAttributesW(g_iniPath)==INVALID_FILE_ATTRIBUTES&&GetFileAttributesW(legacy)!=INVALID_FILE_ATTRIBUTES)CopyFileW(legacy,g_iniPath,TRUE);
}
static void BuildPath(LPCWSTR name,LPWSTR out,int cap){CopyPathParts(g_appDir,name,out,cap);}
static void BuildDataPath(LPCWSTR name,LPWSTR out,int cap){CopyPathParts(g_dataDir,name,out,cap);}
static void LoadApplicationIcons(){g_appIcon=(HICON)LoadImageW(g_instance,(LPCWSTR)(ULONG_PTR)101,IMAGE_ICON,32,32,0);g_appIconSmall=(HICON)LoadImageW(g_instance,(LPCWSTR)(ULONG_PTR)101,IMAGE_ICON,16,16,0);if(!g_appIcon||!g_appIconSmall){wchar_t p[700];BuildPath(L"AstroFocusStudio.ico",p,700);if(!g_appIcon)g_appIcon=(HICON)LoadImageW(0,p,IMAGE_ICON,32,32,LR_LOADFROMFILE);if(!g_appIconSmall)g_appIconSmall=(HICON)LoadImageW(0,p,IMAGE_ICON,16,16,LR_LOADFROMFILE);}if(!g_appIcon)g_appIcon=LoadIconW(0,IDI_APPLICATION);if(!g_appIconSmall)g_appIconSmall=g_appIcon;}
static void ReadIni(LPCWSTR key,LPCWSTR def,LPWSTR out,DWORD size){GetPrivateProfileStringW(L"Settings",key,def,out,size,g_iniPath);}
static void WriteIni(LPCWSTR key,LPCWSTR value){WritePrivateProfileStringW(L"Settings",key,value,g_iniPath);}
static void SaveSettings(){
    if(g_syntheticSelfTestActive)return;
    wchar_t v[64];WriteIni(L"Camera",g_simulatorMode?g_savedCameraId:g_cameraId);WriteIni(L"Focuser",g_simulatorMode?g_savedFocuserId:g_focuserId);
    GetWindowTextW(g_exposureEdit,v,64);WriteIni(L"Exposure",v);GetWindowTextW(g_gainEdit,v,64);WriteIni(L"Gain",v);
    GetWindowTextW(g_manualStepEdit,v,64);WriteIni(L"ManualStep",v);GetWindowTextW(g_afPointsEdit,v,64);WriteIni(L"AFPoints",v);
    GetWindowTextW(g_afStepEdit,v,64);WriteIni(L"AFStep",v);GetWindowTextW(g_afBacklashEdit,v,64);WriteIni(L"Backlash",v);GetWindowTextW(g_afSamplesEdit,v,64);WriteIni(L"Samples",v);wchar_t q[32];wsprintfW(q,L"%d",g_safeMinPosition);WriteIni(L"SafeMin",q);wsprintfW(q,L"%d",g_safeMaxPosition);WriteIni(L"SafeMax",q);WriteIni(L"HttpEnabled",g_httpEnabled?L"1":L"0");
    WriteIni(L"AutoStretch",IsChecked(g_autoStretch)?L"1":L"0");WriteIni(L"Stars",IsChecked(g_overlayStars)?L"1":L"0");WriteIni(L"Labels",IsChecked(g_overlayLabels)?L"1":L"0");WriteIni(L"Saturation",IsChecked(g_overlaySat)?L"1":L"0");
    WriteIni(L"NativeToupTek",IsChecked(g_nativeCheck)?L"1":L"0");WriteIni(L"ToupTekDllPath",g_toupTekDllPath);WriteIni(L"Zones",IsChecked(g_zoneCheck)?L"1":L"0");WriteIni(L"Bahtinov",IsChecked(g_bahtinovCheck)?L"1":L"0");WriteIni(L"PreferredOut",IsChecked(g_preferredDirCheck)?L"1":L"0");WriteIni(L"Reconnect",IsChecked(g_reconnectCheck)?L"1":L"0");
    WriteIni(L"AutoRefocus",g_autoRefocusEnabled?L"1":L"0");GetWindowTextW(g_refocusMinutesEdit,v,64);WriteIni(L"RefocusMinutes",v);GetWindowTextW(g_refocusTempEdit,v,64);WriteIni(L"RefocusTemp",v);
    FormatFixed(g_refocusFwhmThresholdPercent,2,v);WriteIni(L"RefocusFwhmPercent",v);wsprintfW(v,L"%d",g_refocusBadFramesRequired);WriteIni(L"RefocusBadFrames",v);wsprintfW(v,L"%d",g_refocusMinStars);WriteIni(L"RefocusMinStars",v);FormatFixed(g_refocusStabilityLimit,3,v);WriteIni(L"RefocusStability",v);FormatFixed(g_refocusCooldownMinutes,2,v);WriteIni(L"RefocusCooldown",v);
    WriteIni(L"TempCompEnabled",g_tempCompEnabled?L"1":L"0");WriteIni(L"AutoStartPosition",g_autoStartPositionEnabled?L"1":L"0");wsprintfW(v,L"%d",g_tempCompDeadbandSteps);WriteIni(L"TempCompDeadband",v);wsprintfW(v,L"%d",g_tempCompMaxStep);WriteIni(L"TempCompMaxStep",v);
    WriteIni(L"ContinuousFocusEnabled",g_continuousFocusEnabled?L"1":L"0");WriteIni(L"ContinuousFocusFallback",g_continuousFocusFallback?L"1":L"0");wsprintfW(v,L"%d",g_continuousFocusMode);WriteIni(L"ContinuousFocusMode",v);wsprintfW(v,L"%d",g_continuousFocusMinFrames);WriteIni(L"ContinuousFocusMinFrames",v);wsprintfW(v,L"%d",g_continuousFocusDeadband);WriteIni(L"ContinuousFocusDeadband",v);wsprintfW(v,L"%d",g_continuousFocusMaxStep);WriteIni(L"ContinuousFocusMaxStep",v);wsprintfW(v,L"%d",g_continuousFocusMinConfidence);WriteIni(L"ContinuousFocusConfidence",v);FormatFixed(g_continuousFocusMinImprovement,2,v);WriteIni(L"ContinuousFocusImprovement",v);wsprintfW(v,L"%d",g_continuousFocusSettleMs);WriteIni(L"ContinuousFocusSettleMs",v);
    WriteIni(L"RefocusOnMeridian",g_refocusOnMeridian?L"1":L"0");WriteIni(L"RefocusOnReconnect",g_refocusOnReconnect?L"1":L"0");WriteIni(L"RefocusOnFilter",g_refocusOnFilter?L"1":L"0");wsprintfW(v,L"%d",g_refocusEveryCaptures);WriteIni(L"RefocusEveryCaptures",v);
    CopyWBounded(v,64,g_activeProfileName);WriteIni(L"Profile",v);GetWindowTextW(g_focalEdit,v,64);WriteIni(L"FocalLength",v);GetWindowTextW(g_pixelEdit,v,64);WriteIni(L"PixelSize",v);WriteIni(L"Simulator",g_simulatorMode?L"1":L"0");wsprintfW(v,L"%d",g_simProfileMode);WriteIni(L"SimulatorProfile",v);wsprintfW(v,L"%d",g_simBacklashSteps);WriteIni(L"SimulatorBacklash",v);wsprintfW(v,L"%u",g_simRandomSeed);WriteIni(L"SimulatorSeed",v);
}

static HRESULT DispId(IDispatch* obj,LPCWSTR name,LONG* id){LPOLESTR names[1];names[0]=(LPOLESTR)name;return obj->lpVtbl->GetIDsOfNames(obj,IID_NULL_GUID,names,1,LOCALE_USER_DEFAULT,id);}
static void ClearEx(EXCEPINFO* ex){if(ex->bstrSource)SysFreeString(ex->bstrSource);if(ex->bstrDescription)SysFreeString(ex->bstrDescription);if(ex->bstrHelpFile)SysFreeString(ex->bstrHelpFile);}
static HRESULT Invoke(IDispatch* obj,LPCWSTR name,WORD flags,VARIANTARG* args,UINT argCount,LONG* named,UINT namedCount,VARIANT* result){
    if(!obj)return (HRESULT)0x80004003L;LONG id=0;HRESULT hr=DispId(obj,name,&id);if(FAILED(hr))return hr;DISPPARAMS dp;dp.rgvarg=args;dp.rgdispidNamedArgs=named;dp.cArgs=argCount;dp.cNamedArgs=namedCount;EXCEPINFO ex;memset(&ex,0,sizeof(ex));UINT argErr=0;if(result)VariantInit(result);hr=obj->lpVtbl->Invoke(obj,id,IID_NULL_GUID,LOCALE_USER_DEFAULT,flags,&dp,result,&ex,&argErr);ClearEx(&ex);return hr;
}
static HRESULT SetBstrProp(IDispatch* obj,LPCWSTR name,LPCWSTR value){VARIANT a;VariantInit(&a);a.vt=VT_BSTR;a.data.bstrVal=SysAllocString(value);if(!a.data.bstrVal)return (HRESULT)0x8007000EL;LONG n=DISPID_PROPERTYPUT;HRESULT hr=Invoke(obj,name,DISPATCH_PROPERTYPUT,&a,1,&n,1,0);SysFreeString(a.data.bstrVal);return hr;}
static HRESULT CallChoose(IDispatch* chooser,LPCWSTR current,VARIANT* result){VARIANT a;VariantInit(&a);a.vt=VT_BSTR;a.data.bstrVal=SysAllocString(current?current:L"");if(!a.data.bstrVal)return (HRESULT)0x8007000EL;HRESULT hr=Invoke(chooser,L"Choose",DISPATCH_METHOD,&a,1,0,0,result);SysFreeString(a.data.bstrVal);return hr;}


static PFN_CreateProcessW_MIN pCreateProcessWMin=0;
static PFN_TerminateProcess_MIN pTerminateProcessMin=0;
static PFN_GetExitCodeProcess_MIN pGetExitCodeProcessMin=0;
static PFN_GetCurrentProcessId_MIN pGetCurrentProcessIdMin=0;
static PFN_Sleep_MIN pSleepMin=0;
static PFN_CreateJobObjectW_MIN pCreateJobObjectWMin=0;
static PFN_SetInformationJobObject_MIN pSetInformationJobObjectMin=0;
static PFN_AssignProcessToJobObject_MIN pAssignProcessToJobObjectMin=0;
static BOOL LoadDeviceHostProcessApi(){
    if(pCreateProcessWMin&&pTerminateProcessMin&&pGetExitCodeProcessMin&&pGetCurrentProcessIdMin&&pSleepMin&&pCreateJobObjectWMin&&pSetInformationJobObjectMin&&pAssignProcessToJobObjectMin)return TRUE;
    HMODULE k=LoadLibraryW(L"kernel32.dll");if(!k)return FALSE;
    pCreateProcessWMin=(PFN_CreateProcessW_MIN)GetProcAddress(k,"CreateProcessW");
    pTerminateProcessMin=(PFN_TerminateProcess_MIN)GetProcAddress(k,"TerminateProcess");
    pGetExitCodeProcessMin=(PFN_GetExitCodeProcess_MIN)GetProcAddress(k,"GetExitCodeProcess");
    pGetCurrentProcessIdMin=(PFN_GetCurrentProcessId_MIN)GetProcAddress(k,"GetCurrentProcessId");
    pSleepMin=(PFN_Sleep_MIN)GetProcAddress(k,"Sleep");
    pCreateJobObjectWMin=(PFN_CreateJobObjectW_MIN)GetProcAddress(k,"CreateJobObjectW");
    pSetInformationJobObjectMin=(PFN_SetInformationJobObject_MIN)GetProcAddress(k,"SetInformationJobObject");
    pAssignProcessToJobObjectMin=(PFN_AssignProcessToJobObject_MIN)GetProcAddress(k,"AssignProcessToJobObject");
    return pCreateProcessWMin&&pTerminateProcessMin&&pGetExitCodeProcessMin&&pGetCurrentProcessIdMin&&pSleepMin&&pCreateJobObjectWMin&&pSetInformationJobObjectMin&&pAssignProcessToJobObjectMin;
}
static BOOL EnsureDeviceHostJob(){
    if(g_deviceHostJob)return TRUE;if(!LoadDeviceHostProcessApi())return FALSE;
    HANDLE job=pCreateJobObjectWMin(0,0);if(!job)return FALSE;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION_MIN info;memset(&info,0,sizeof(info));info.BasicLimitInformation.LimitFlags=0x00002000UL; /* JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE */
    if(!pSetInformationJobObjectMin(job,9,&info,sizeof(info))){CloseHandle(job);return FALSE;} /* JobObjectExtendedLimitInformation */
    g_deviceHostJob=job;return TRUE;
}
static BOOL HostWriteAll(HANDLE h,const void* data,DWORD bytes){const BYTE* p=(const BYTE*)data;while(bytes){DWORD sent=0;if(!WriteFile(h,p,bytes,&sent,0)||sent==0)return FALSE;p+=sent;bytes-=sent;}return TRUE;}
static BOOL HostReadAll(HANDLE h,void* data,DWORD bytes){BYTE* p=(BYTE*)data;while(bytes){DWORD got=0;if(!ReadFile(h,p,bytes,&got,0)||got==0)return FALSE;p+=got;bytes-=got;}return TRUE;}
static void FreeWorkerImage(DeviceWorker* w){if(w&&w->imageData){Free(w->imageData);w->imageData=0;}if(w){w->imageBytes=0;w->imageWidth=0;w->imageHeight=0;w->imageMaxAdu=0;}}
static void CloseWorkerHostHandles(DeviceWorker* w){
    if(!w)return;if(w->hostPipe&&w->hostPipe!=INVALID_HANDLE_VALUE){CloseHandle(w->hostPipe);w->hostPipe=0;}
    if(w->hostThread){CloseHandle(w->hostThread);w->hostThread=0;}if(w->hostProcess){CloseHandle(w->hostProcess);w->hostProcess=0;}w->hostPid=0;w->hostJobAssigned=FALSE;w->pipeName[0]=0;
}
static void TerminateWorkerHost(DeviceWorker* w,UINT exitCode){if(w&&w->hostProcess&&LoadDeviceHostProcessApi())pTerminateProcessMin(w->hostProcess,exitCode);}
static BOOL WorkerHostAlive(DeviceWorker* w){if(!w||!w->hostProcess)return FALSE;DWORD code=0;if(!LoadDeviceHostProcessApi()||!pGetExitCodeProcessMin(w->hostProcess,&code))return FALSE;return code==STILL_ACTIVE;}
static BOOL EnsureWorkerHost(DeviceWorker* w){
    if(!w)return FALSE;if(w->hostPipe&&w->hostPipe!=INVALID_HANDLE_VALUE&&WorkerHostAlive(w))return TRUE;
    CloseWorkerHostHandles(w);if(!LoadDeviceHostProcessApi()){w->hr=(HRESULT)0x80004005L;return FALSE;}
    wchar_t hostPath[700];BuildPath(w->camera?L"AstroFocusCameraHost.exe":L"AstroFocusFocuserHost.exe",hostPath,700);
    static DWORD serial=1;DWORD pid=pGetCurrentProcessIdMin();ULONGLONG tick=GetTickCount64();wsprintfW(w->pipeName,L"\\\\.\\pipe\\AstroFocus-%s-%u-%u-%u",w->camera?L"Camera":L"Focuser",pid,(DWORD)tick,serial++);
    wchar_t cmd[1100];wsprintfW(cmd,L"\"%s\" --pipe \"%s\"",hostPath,w->pipeName);STARTUPINFOW_MIN si;PROCESS_INFORMATION_MIN pi;memset(&si,0,sizeof(si));memset(&pi,0,sizeof(pi));si.cb=sizeof(si);
    if(!pCreateProcessWMin(hostPath,cmd,0,0,FALSE,CREATE_NO_WINDOW,0,g_appDir,&si,&pi)){w->hr=(HRESULT)(0x80070000UL|(GetLastError()&0xffffUL));return FALSE;}
    w->hostJobAssigned=FALSE;if(EnsureDeviceHostJob())w->hostJobAssigned=pAssignProcessToJobObjectMin(g_deviceHostJob,pi.hProcess);
    w->hostProcess=pi.hProcess;w->hostThread=pi.hThread;w->hostPid=pi.dwProcessId;
    ULONGLONG deadline=GetTickCount64()+5000ULL;for(;;){
        HANDLE pipe=CreateFileW(w->pipeName,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(pipe!=INVALID_HANDLE_VALUE){w->hostPipe=pipe;w->lastHeartbeat=GetTickCount64();return TRUE;}
        if(!WorkerHostAlive(w)||GetTickCount64()>=deadline)break;pSleepMin(25);
    }
    TerminateWorkerHost(w,0xAF10);WaitForSingleObject(w->hostProcess,1000);CloseWorkerHostHandles(w);w->hr=(HRESULT)0x800705B4L;return FALSE;
}
static DWORD MapWorkerHostCommand(LONG cmd){
    if(cmd==DW_CONNECT_CAMERA)return AFHC_CONNECT_CAMERA;if(cmd==DW_CONNECT_FOCUSER)return AFHC_CONNECT_FOCUSER;if(cmd==DW_DISCONNECT)return AFHC_DISCONNECT;
    if(cmd==DW_GET_BOOL)return AFHC_GET_BOOL;if(cmd==DW_GET_INT)return AFHC_GET_INT;if(cmd==DW_GET_DOUBLE)return AFHC_GET_DOUBLE;if(cmd==DW_SET_INT)return AFHC_SET_INT;
    if(cmd==DW_CALL_INT)return AFHC_CALL_INT;if(cmd==DW_CALL_NOARGS)return AFHC_CALL_NOARGS;if(cmd==DW_START_EXPOSURE)return AFHC_START_EXPOSURE;if(cmd==DW_GET_IMAGE)return AFHC_GET_IMAGE;
    if(cmd==DW_PING)return AFHC_PING;if(cmd==DW_SHUTDOWN)return AFHC_SHUTDOWN;if(cmd==DW_TEST_BLOCK)return AFHC_TEST_BLOCK;if(cmd==DW_TEST_CRASH)return AFHC_TEST_CRASH;return AFHC_NONE;
}
static HRESULT WorkerHostRpc(DeviceWorker* w,LONG cmd){
    if(!w)return (HRESULT)0x80004003L;if(cmd!=DW_SHUTDOWN&&!EnsureWorkerHost(w))return w->hr;if(cmd==DW_SHUTDOWN&&!w->hostPipe)return S_OK;
    DWORD hostCommand=MapWorkerHostCommand(cmd);if(hostCommand==AFHC_NONE)return (HRESULT)0x80070057L;
    AfHostRequest req;memset(&req,0,sizeof(req));req.magic=AF_HOST_MAGIC;req.protocolVersion=AF_HOST_PROTOCOL_VERSION;req.structBytes=sizeof(req);req.command=hostCommand;req.requestId=++w->requestId;req.deadlineTick=GetTickCount64()+(ULONGLONG)(w->commandTimeoutMs?w->commandTimeoutMs:5000);req.intArg=w->intArg;req.doubleArg=w->doubleArg;req.boolArg=w->boolArg?1UL:0UL;CopyWBounded(req.progId,256,w->progId);CopyWBounded(req.member,64,w->member);
    FreeWorkerImage(w);if(!HostWriteAll(w->hostPipe,&req,sizeof(req))){w->hr=(HRESULT)(0x80070000UL|(GetLastError()&0xffffUL));return w->hr;}
    AfHostResponse res;memset(&res,0,sizeof(res));if(!HostReadAll(w->hostPipe,&res,sizeof(res))){w->hr=(HRESULT)(0x80070000UL|(GetLastError()&0xffffUL));return w->hr;}
    if(res.magic!=AF_HOST_MAGIC||res.protocolVersion!=AF_HOST_PROTOCOL_VERSION||res.structBytes!=sizeof(res)||res.requestId!=req.requestId){w->hr=(HRESULT)0x8007000DL;return w->hr;}
    w->hostPid=res.hostPid;w->hr=(HRESULT)res.hr;w->boolResult=res.boolValue!=0;w->intResult=res.intValue;w->doubleResult=res.doubleValue;w->cameraX=res.width;w->cameraY=res.height;w->maxAdu=res.maxAdu;w->lastHeartbeat=res.completedTick;
    if(res.payloadBytes){
        unsigned long long expected=(unsigned long long)(unsigned)res.width*(unsigned long long)(unsigned)res.height*4ULL;if(res.payloadFormat!=AFHP_U32_IMAGE||res.payloadBytes!=expected||expected==0||expected>AF_HOST_MAX_IMAGE_BYTES){w->hr=(HRESULT)0x8007000DL;return w->hr;}
        w->imageData=(UINT*)Alloc((SIZE_T)res.payloadBytes);if(!w->imageData){w->hr=(HRESULT)0x8007000EL;return w->hr;}w->imageBytes=res.payloadBytes;w->imageWidth=res.width;w->imageHeight=res.height;w->imageMaxAdu=res.maxAdu;
        if(!HostReadAll(w->hostPipe,w->imageData,res.payloadBytes)){FreeWorkerImage(w);w->hr=(HRESULT)(0x80070000UL|(GetLastError()&0xffffUL));return w->hr;}
    }
    return w->hr;
}
static DWORD WINAPI DeviceWorkerProc(LPVOID param){
    DeviceWorker* w=(DeviceWorker*)param;if(!w)return 1;
    for(;;){
        DWORD wait=WaitForSingleObject(w->requestEvent,INFINITE);if(wait!=WAIT_OBJECT_0)break;
        LONG cmd=w->command;w->commandStarted=GetTickCount64();w->commandFinished=0;w->hr=S_OK;w->boolResult=FALSE;w->intResult=0;w->doubleResult=0.0;w->cameraX=w->cameraY=0;w->maxAdu=4095;VariantClear(&w->result);VariantInit(&w->result);
        w->hr=WorkerHostRpc(w,cmd);w->commandFinished=GetTickCount64();
        if(w->abandoned){TerminateWorkerHost(w,0xAF11);if(w->hostProcess)WaitForSingleObject(w->hostProcess,1000);CloseWorkerHostHandles(w);FreeWorkerImage(w);break;}
        SetEvent(w->doneEvent);if(cmd==DW_SHUTDOWN){if(w->hostProcess)WaitForSingleObject(w->hostProcess,1500);CloseWorkerHostHandles(w);FreeWorkerImage(w);break;}
    }
    VariantClear(&w->result);TerminateWorkerHost(w,0xAF12);if(w->hostProcess)WaitForSingleObject(w->hostProcess,500);CloseWorkerHostHandles(w);FreeWorkerImage(w);return 0;
}
static BOOL WaitWorkerResponsive(DeviceWorker* w,DWORD timeoutMs){
    if(!w||!w->doneEvent)return FALSE;ULONGLONG start=GetTickCount64();
    for(;;){DWORD elapsed=(DWORD)(GetTickCount64()-start);if(elapsed>=timeoutMs)return FALSE;DWORD slice=timeoutMs-elapsed;if(slice>25)slice=25;DWORD r=WaitForSingleObject(w->doneEvent,slice);if(r==WAIT_OBJECT_0)return TRUE;
        MSG msg;while(PeekMessageW(&msg,g_main,WM_PAINT,WM_PAINT,PM_REMOVE)){TranslateMessage(&msg);DispatchMessageW(&msg);}if(r!=WAIT_TIMEOUT)return FALSE;
    }
}
static BOOL HasOrphanWorker(BOOL camera){for(int i=0;i<g_orphanWorkerCount;i++)if(g_orphanWorkers[i]&&g_orphanWorkers[i]->camera==camera)return TRUE;return FALSE;}
static BOOL AddOrphanWorker(DeviceWorker* w){
    if(!w)return FALSE;for(int i=0;i<g_orphanWorkerCount;i++)if(g_orphanWorkers[i]==w)return TRUE;
    if(g_orphanWorkerCount>=(int)(sizeof(g_orphanWorkers)/sizeof(g_orphanWorkers[0])))return FALSE;
    g_orphanWorkers[g_orphanWorkerCount++]=w;return TRUE;
}
static void AbandonDeviceWorker(DeviceWorker* w,LPCWSTR operation){
    if(!w)return;w->abandoned=TRUE;TerminateWorkerHost(w,0xAF20);BOOL tracked=AddOrphanWorker(w);
    if(w==g_cameraWorker){g_cameraWorker=0;g_cameraWorkerBlocked=TRUE;g_cameraWorkerFaultPending=TRUE;CopyWBounded(g_cameraWorkerFaultOperation,96,operation);if(!tracked)CopyWBounded(g_cameraWorkerFaultOperation,96,L"Worker-Quarantäne voll");}
    if(w==g_focuserWorker){g_focuserWorker=0;g_focuserWorkerBlocked=TRUE;g_focuserWorkerFaultPending=TRUE;CopyWBounded(g_focuserWorkerFaultOperation,96,operation);if(!tracked)CopyWBounded(g_focuserWorkerFaultOperation,96,L"Worker-Quarantäne voll");}
}
static BOOL SubmitWorker(DeviceWorker* w,LONG command,DWORD timeoutMs,LPCWSTR operation){
    if(!w||!w->thread||w->abandoned)return FALSE;ResetEvent(w->doneEvent);w->command=command;w->commandTimeoutMs=timeoutMs;DeviceRuntimeBegin(w,operation,timeoutMs);if(!SetEvent(w->requestEvent)){DeviceRuntimeComplete(w,(HRESULT)(0x80070000UL|(GetLastError()&0xffffUL)));return FALSE;}
    if(WaitWorkerResponsive(w,timeoutMs)){DeviceRuntimeComplete(w,w->hr);return TRUE;}DeviceRuntimeTimeout(w,operation);AbandonDeviceWorker(w,operation);return FALSE;
}
static DeviceWorker* CreateDeviceWorker(BOOL camera){
    DeviceWorker* w=(DeviceWorker*)Alloc(sizeof(DeviceWorker));if(!w)return 0;w->camera=camera;w->hostPipe=0;VariantInit(&w->result);w->requestEvent=CreateEventW(0,FALSE,FALSE,0);w->doneEvent=CreateEventW(0,TRUE,FALSE,0);if(!w->requestEvent||!w->doneEvent){if(w->requestEvent)CloseHandle(w->requestEvent);if(w->doneEvent)CloseHandle(w->doneEvent);Free(w);return 0;}w->thread=CreateThread(0,0,DeviceWorkerProc,w,0,0);if(!w->thread){CloseHandle(w->requestEvent);CloseHandle(w->doneEvent);Free(w);return 0;}DeviceRuntimeSetPhase(camera,DEV_DISCONNECTED,L"host worker created",S_OK,TRUE);return w;
}
static void CleanupOrphanWorkers(){
    for(int i=0;i<g_orphanWorkerCount;){
        DeviceWorker* w=g_orphanWorkers[i];
        if(w&&WaitForSingleObject(w->thread,0)==WAIT_OBJECT_0){
            BOOL camera=w->camera;VariantClear(&w->result);CloseWorkerHostHandles(w);FreeWorkerImage(w);CloseHandle(w->thread);CloseHandle(w->requestEvent);CloseHandle(w->doneEvent);Free(w);
            for(int j=i+1;j<g_orphanWorkerCount;j++)g_orphanWorkers[j-1]=g_orphanWorkers[j];g_orphanWorkerCount--;
            if(!HasOrphanWorker(camera)){
                ULONGLONG now=GetTickCount64();
                if(camera){g_cameraWorkerBlocked=FALSE;g_cameraWorkerRetryAfter=now+30000ULL;SetStatus(L"ASCOM-Kamera-Worker hat die blockierte Operation beendet · Wiederverbindung in 30 s");}
                else{g_focuserWorkerBlocked=FALSE;g_focuserWorkerRetryAfter=now+30000ULL;SetStatus(L"ASCOM-Fokussierer-Worker hat die blockierte Operation beendet · Wiederverbindung in 30 s");}
            }
            continue;
        }
        i++;
    }
}
static void DestroyDeviceWorker(DeviceWorker** pp,BOOL graceful){
    if(!pp||!*pp)return;DeviceWorker* w=*pp;BOOL camera=w->camera;if(graceful){WorkerDisconnect(w,1200);if(*pp!=w)return;if(SubmitWorker(w,DW_SHUTDOWN,2500,camera?L"ASCOM-Kamera-Host beenden":L"ASCOM-Fokussierer-Host beenden")){WaitForSingleObject(w->thread,1800);VariantClear(&w->result);CloseWorkerHostHandles(w);FreeWorkerImage(w);CloseHandle(w->thread);CloseHandle(w->requestEvent);CloseHandle(w->doneEvent);Free(w);*pp=0;DeviceRuntimeSetPhase(camera,DEV_DISCONNECTED,L"host stopped",S_OK,TRUE);return;}}if(*pp==w){AbandonDeviceWorker(w,camera?L"ASCOM-Kamera-Host beenden":L"ASCOM-Fokussierer-Host beenden");*pp=0;}
}
static void WorkerSetMember(DeviceWorker* w,LPCWSTR member){CopyWBounded(w->member,64,member);}
static BOOL WorkerConnect(DeviceWorker* w,LPCWSTR progId,DWORD timeoutMs){if(!w)return FALSE;CopyWBounded(w->progId,256,progId);return SubmitWorker(w,w->camera?DW_CONNECT_CAMERA:DW_CONNECT_FOCUSER,timeoutMs,w->camera?L"Kamera verbinden":L"Fokussierer verbinden")&&SUCCEEDED(w->hr);}
static BOOL WorkerDisconnect(DeviceWorker* w,DWORD timeoutMs){return w&&SubmitWorker(w,DW_DISCONNECT,timeoutMs,w->camera?L"Kamera trennen":L"Fokussierer trennen")&&SUCCEEDED(w->hr);}
static BOOL WorkerGetBool(DeviceWorker* w,LPCWSTR member,BOOL fallback,BOOL* out,DWORD timeoutMs){if(out)*out=fallback;if(!w)return FALSE;WorkerSetMember(w,member);if(!SubmitWorker(w,DW_GET_BOOL,timeoutMs,member)||FAILED(w->hr))return FALSE;if(out)*out=w->boolResult;return TRUE;}
static BOOL WorkerGetInt(DeviceWorker* w,LPCWSTR member,LONG fallback,LONG* out,DWORD timeoutMs){if(out)*out=fallback;if(!w)return FALSE;WorkerSetMember(w,member);if(!SubmitWorker(w,DW_GET_INT,timeoutMs,member)||FAILED(w->hr))return FALSE;if(out)*out=w->intResult;return TRUE;}
static BOOL WorkerGetDouble(DeviceWorker* w,LPCWSTR member,double fallback,double* out,DWORD timeoutMs){if(out)*out=fallback;if(!w)return FALSE;WorkerSetMember(w,member);if(!SubmitWorker(w,DW_GET_DOUBLE,timeoutMs,member)||FAILED(w->hr))return FALSE;if(out)*out=w->doubleResult;return TRUE;}
static BOOL WorkerSetInt(DeviceWorker* w,LPCWSTR member,LONG value,DWORD timeoutMs){if(!w)return FALSE;WorkerSetMember(w,member);w->intArg=value;return SubmitWorker(w,DW_SET_INT,timeoutMs,member)&&SUCCEEDED(w->hr);}
static BOOL WorkerCallInt(DeviceWorker* w,LPCWSTR member,LONG value,DWORD timeoutMs){if(!w)return FALSE;WorkerSetMember(w,member);w->intArg=value;return SubmitWorker(w,DW_CALL_INT,timeoutMs,member)&&SUCCEEDED(w->hr);}
static BOOL WorkerCallNoArgs(DeviceWorker* w,LPCWSTR member,DWORD timeoutMs){if(!w)return FALSE;WorkerSetMember(w,member);return SubmitWorker(w,DW_CALL_NOARGS,timeoutMs,member)&&SUCCEEDED(w->hr);}
static BOOL WorkerStartExposure(DeviceWorker* w,double seconds,BOOL light,DWORD timeoutMs){if(!w)return FALSE;w->doubleArg=seconds;w->boolArg=light;return SubmitWorker(w,DW_START_EXPOSURE,timeoutMs,L"StartExposure")&&SUCCEEDED(w->hr);}
static BOOL WorkerGetImage(DeviceWorker* w,UINT** pixels,int* width,int* height,int* maxAdu,DWORD timeoutMs){
    if(pixels)*pixels=0;if(width)*width=0;if(height)*height=0;if(maxAdu)*maxAdu=0;if(!w||!pixels||!width||!height||!maxAdu)return FALSE;WorkerSetMember(w,L"ImageArray");if(!SubmitWorker(w,DW_GET_IMAGE,timeoutMs,L"ImageArray herunterladen")||FAILED(w->hr)||!w->imageData)return FALSE;
    *pixels=w->imageData;*width=(int)w->imageWidth;*height=(int)w->imageHeight;*maxAdu=(int)w->imageMaxAdu;w->imageData=0;w->imageBytes=0;w->imageWidth=w->imageHeight=w->imageMaxAdu=0;return TRUE;
}

static ULONGLONG DeviceRecoveryDelayMs(int attempt){static const int seconds[4]={30,60,120,300};int i=attempt<1?0:(attempt>4?3:attempt-1);return (ULONGLONG)seconds[i]*1000ULL;}
static void ApplyDeviceWorkerFaults(){
    if(g_cameraWorkerFaultPending){
        g_cameraWorkerFaultPending=FALSE;if(g_live)g_resumeLiveAfterCameraRecovery=TRUE;g_cameraConnected=FALSE;g_exposing=FALSE;g_capturePurpose=0;g_lastCompletedPurpose=0;g_live=FALSE;SetWindowTextW(g_cameraConnect,L"Verbinden");SetWindowTextW(g_liveButton,L"Live-Fokus starten");g_cameraWorkerRecoveryAttempt++;g_cameraWorkerRetryAfter=0;
        wchar_t reason[360];wsprintfW(reason,L"ASCOM-Kamera-Worker blockiert bei '%s' · Gerät isoliert, Wiederverbindung wartet auf die Freigabe des Treibers",g_cameraWorkerFaultOperation);SetAutofocusError(L"AF_ASCOM_WORKER_TIMEOUT",L"ASCOM-Kamera-Worker reagiert nicht",reason,g_afAutomaticRun||g_afAutomaticRequest);if(g_afActive)StopAutofocus(TRUE,reason);else if(g_stepAssistActive)StopStepAssistant(TRUE,reason);else if(g_backlashCalActive)StopBacklashCalibration(FALSE,reason);else SetStatus(reason);
    }
    if(g_focuserWorkerFaultPending){
        g_focuserWorkerFaultPending=FALSE;g_focuserConnected=FALSE;g_cachedFocuserPosition=-1;g_cachedFocuserMoving=FALSE;g_hasFocuserTemperature=FALSE;SetWindowTextW(g_focuserConnect,L"Verbinden");SetWindowTextW(g_positionText,L"–");g_focuserWorkerRecoveryAttempt++;g_focuserWorkerRetryAfter=0;
        wchar_t reason[360];wsprintfW(reason,L"ASCOM-Fokussierer-Worker blockiert bei '%s' · Gerät isoliert, Wiederverbindung wartet auf die Freigabe des Treibers",g_focuserWorkerFaultOperation);SetAutofocusError(L"AF_ASCOM_WORKER_TIMEOUT",L"ASCOM-Fokussierer-Worker reagiert nicht",reason,g_afAutomaticRun||g_afAutomaticRequest);if(g_afActive)StopAutofocus(FALSE,reason);else if(g_stepAssistActive)StopStepAssistant(FALSE,reason);else if(g_backlashCalActive)StopBacklashCalibration(FALSE,reason);else SetStatus(reason);
    }
}

static void HResultText(HRESULT hr,LPWSTR out,int maxChars){DWORD n=FormatMessageW(0x00001000L|0x00000200L,0,(DWORD)hr,0,out,(DWORD)maxChars,0);if(n==0)wsprintfW(out,L"Fehler 0x%08X",(DWORD)hr);else while(n>0&&(out[n-1]==L'\r'||out[n-1]==L'\n'||out[n-1]==L' '))out[--n]=0;}
static void ShowComError(LPCWSTR action,HRESULT hr){wchar_t d[256],m[600];HResultText(hr,d,256);wsprintfW(m,L"%s ist fehlgeschlagen.\r\n\r\n%s",action,d);NotifyUser(m,L"AstroFocus Studio",MB_OK|MB_ICONERROR);}

static HWND AddControl(LPCWSTR cls,LPCWSTR text,DWORD style,int x,int y,int w,int h,int id,HFONT font){HWND c=CreateWindowExW(0,cls,text,WS_CHILD|WS_VISIBLE|style,x,y,w,h,g_main,(HMENU)(ULONG_PTR)id,g_instance,0);if(c&&font)SetControlFont(c,font);return c;}

static BOOL SelectDriver(BOOL camera){
    CLSID clsid;HRESULT hr=CLSIDFromProgID(L"ASCOM.Utilities.Chooser",&clsid);if(FAILED(hr)){ShowComError(L"Der ASCOM-Treiberauswahldialog",hr);return FALSE;}
    IDispatch* chooser=0;hr=CoCreateInstance(clsid,0,CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER,IID_IDispatch_GUID,(void**)&chooser);if(FAILED(hr)||!chooser){ShowComError(L"Der ASCOM-Treiberauswahldialog",hr);return FALSE;}
    hr=SetBstrProp(chooser,L"DeviceType",camera?L"Camera":L"Focuser");if(FAILED(hr)){chooser->lpVtbl->Release(chooser);ShowComError(L"Die ASCOM-Geräteart",hr);return FALSE;}
    VARIANT result;VariantInit(&result);hr=CallChoose(chooser,camera?g_cameraId:g_focuserId,&result);chooser->lpVtbl->Release(chooser);
    if(FAILED(hr)){ShowComError(L"Die Treiberauswahl",hr);return FALSE;}
    BOOL selected=result.vt==VT_BSTR&&result.data.bstrVal&&result.data.bstrVal[0];
    if(selected){if(camera){CopyWBounded(g_cameraId,256,result.data.bstrVal);SetWindowTextW(g_cameraEdit,g_cameraId);WriteIni(L"Camera",g_cameraId);}else{CopyWBounded(g_focuserId,256,result.data.bstrVal);SetWindowTextW(g_focuserEdit,g_focuserId);WriteIni(L"Focuser",g_focuserId);}}
    VariantClear(&result);return selected;
}

static void StopLive();
static BOOL EnsureImage(int,int);
static void StopAutofocus(BOOL restore,LPCWSTR reason);
static void StopStepAssistant(BOOL restore,LPCWSTR reason);
static void StartStepAssistant();
static void HandleStepAssistantFrame();
static void LoadTemperatureProfile();
static void RecordSuccessfulFocus();
static BOOL TriggerAutomaticRefocus(LPCWSTR);

static void UnloadToupTek(){
    if(g_tcam){if(pToupcam_Stop)pToupcam_Stop(g_tcam);if(pToupcam_Close)pToupcam_Close(g_tcam);g_tcam=0;}
    g_nativeStreaming=FALSE;g_nativeActive=FALSE;Free(g_nativeRgb);g_nativeRgb=0;g_nativeStride=0;g_nativeRgbBytes=0;
    if(g_toupDll){FreeLibrary(g_toupDll);g_toupDll=0;}
    pToupcam_Version=0;pToupcam_EnumV2=0;pToupcam_Open=0;pToupcam_Close=0;pToupcam_StartPullModeWithWndMsg=0;pToupcam_Stop=0;pToupcam_get_Size=0;pToupcam_PullImageV2=0;pToupcam_PullImageWithRowPitchV2=0;pToupcam_put_ExpoTime=0;pToupcam_put_ExpoAGain=0;pToupcam_put_RealTime=0;
}
static BOOL LoadToupTek(){
    if(g_toupDll)return TRUE;
    g_toupTekLoadedPath[0]=0;
    wchar_t localPath[700];BuildPath(L"toupcam.dll",localPath,700);
    if(IsSafeToupTekDllPath(g_toupTekDllPath)){g_toupDll=LoadLibraryW(g_toupTekDllPath);if(g_toupDll)CopyWBounded(g_toupTekLoadedPath,700,g_toupTekDllPath);}
    if(!g_toupDll&&FileExistsW(localPath)){g_toupDll=LoadLibraryW(localPath);if(g_toupDll)CopyWBounded(g_toupTekLoadedPath,700,localPath);}
    if(!g_toupDll){g_toupDll=LoadLibraryW(L"toupcam.dll");if(g_toupDll)CopyWBounded(g_toupTekLoadedPath,700,L"toupcam.dll (Windows-Suchpfad)");}
    if(!g_toupDll)return FALSE;
    pToupcam_Version=(PFN_Toupcam_Version)GetProcAddress(g_toupDll,"Toupcam_Version");pToupcam_EnumV2=(PFN_Toupcam_EnumV2)GetProcAddress(g_toupDll,"Toupcam_EnumV2");pToupcam_Open=(PFN_Toupcam_Open)GetProcAddress(g_toupDll,"Toupcam_Open");pToupcam_Close=(PFN_Toupcam_Close)GetProcAddress(g_toupDll,"Toupcam_Close");pToupcam_StartPullModeWithWndMsg=(PFN_Toupcam_StartPullModeWithWndMsg)GetProcAddress(g_toupDll,"Toupcam_StartPullModeWithWndMsg");pToupcam_Stop=(PFN_Toupcam_Stop)GetProcAddress(g_toupDll,"Toupcam_Stop");pToupcam_get_Size=(PFN_Toupcam_get_Size)GetProcAddress(g_toupDll,"Toupcam_get_Size");pToupcam_PullImageV2=(PFN_Toupcam_PullImageV2)GetProcAddress(g_toupDll,"Toupcam_PullImageV2");pToupcam_PullImageWithRowPitchV2=(PFN_Toupcam_PullImageWithRowPitchV2)GetProcAddress(g_toupDll,"Toupcam_PullImageWithRowPitchV2");pToupcam_put_ExpoTime=(PFN_Toupcam_put_ExpoTime)GetProcAddress(g_toupDll,"Toupcam_put_ExpoTime");pToupcam_put_ExpoAGain=(PFN_Toupcam_put_ExpoAGain)GetProcAddress(g_toupDll,"Toupcam_put_ExpoAGain");pToupcam_put_RealTime=(PFN_Toupcam_put_RealTime)GetProcAddress(g_toupDll,"Toupcam_put_RealTime");
    if(!pToupcam_EnumV2||!pToupcam_Open||!pToupcam_Close||!pToupcam_StartPullModeWithWndMsg||!pToupcam_get_Size||!pToupcam_PullImageV2||!pToupcam_put_ExpoTime||!pToupcam_put_ExpoAGain){UnloadToupTek();g_toupTekLoadedPath[0]=0;return FALSE;}
    if(pToupcam_Version){LPCWSTR v=pToupcam_Version();if(v)CopyWBounded(g_toupVersion,96,v);}return TRUE;
}
static BOOL PrepareNativeBuffers(int w,int h){
    if(w<=0||h<=0||w>10000||h>10000)return FALSE;
    unsigned long long rowBytes=(unsigned long long)(unsigned)w*3ULL;
    unsigned long long stride64=pToupcam_PullImageWithRowPitchV2?rowBytes:((rowBytes+3ULL)&~3ULL);
    unsigned long long bytes64=stride64*(unsigned long long)(unsigned)h;
    if(stride64>2147483647ULL||bytes64==0ULL||bytes64>536870912ULL)return FALSE;
    int stride=(int)stride64;SIZE_T bytes=(SIZE_T)bytes64;
    if(!EnsureImage(w,h))return FALSE;
    if(g_nativeRgb&&g_nativeStride==stride&&g_nativeRgbBytes>=bytes)return TRUE;
    BYTE* replacement=(BYTE*)Alloc(bytes);if(!replacement)return FALSE;
    Free(g_nativeRgb);g_nativeRgb=replacement;g_nativeStride=stride;g_nativeRgbBytes=bytes;return TRUE;
}
static BOOL ConnectNativeCamera(){
    g_lastCameraActionMessage[0]=0;
    if(!LoadToupTek()){SetCameraActionMessage(L"Die 64-Bit-toupcam.dll wurde nicht gefunden oder ist nicht mit der erwarteten ToupTek-SDK-Schnittstelle kompatibel. Wähle über 'SDK/Kamera suchen' die passende 64-Bit-toupcam.dll aus oder installiere das aktuelle ToupTek-Astro-Paket.");return FALSE;}
    ToupcamDeviceV2 dev[16];memset(dev,0,sizeof(dev));unsigned n=pToupcam_EnumV2(dev);if(n==0){UnloadToupTek();SetCameraActionMessage(L"Das ToupTek-SDK wurde geladen, aber es wurde keine kompatible ToupTek-Kamera erkannt. Prüfe USB-Verbindung, Stromversorgung und den 64-Bit-ToupTek-Treiber.");return FALSE;}
    g_tcam=pToupcam_Open(dev[0].id);if(!g_tcam){UnloadToupTek();SetCameraActionMessage(L"Die erkannte ToupTek-Kamera konnte nicht geöffnet werden. Schließe andere Kameraanwendungen und prüfe, ob die Kamera bereits von einem anderen Prozess verwendet wird.");return FALSE;}
    int w=0,h=0;if(FAILED(pToupcam_get_Size(g_tcam,&w,&h))||!PrepareNativeBuffers(w,h)){UnloadToupTek();SetCameraActionMessage(L"Die ToupTek-Bildgröße oder der Bildpuffer konnte nicht sicher initialisiert werden. Prüfe SDK-Version, Kameratreiber und verfügbaren Arbeitsspeicher.");return FALSE;}
    if(pToupcam_put_RealTime)pToupcam_put_RealTime(g_tcam,1);if(FAILED(pToupcam_StartPullModeWithWndMsg(g_tcam,g_main,WM_TOUPCAM))){UnloadToupTek();SetCameraActionMessage(L"Der native ToupTek-Videostream konnte nicht gestartet werden. Trenne die Kamera kurz, schließe andere Kameraanwendungen und versuche es erneut.");return FALSE;}
    g_nativeActive=TRUE;g_nativeStreaming=TRUE;g_cameraConnected=TRUE;g_cameraWanted=TRUE;g_maxAdu=255;g_cameraRuntime.phase=DEV_READY;g_cameraRuntime.removalDetected=FALSE;g_cameraRuntime.lastSuccessTick=GetTickCount64();CopyWBounded(g_cameraRuntime.operation,96,L"native ToupTek ready");AppendHardwareEvent(TRUE,L"connected",&g_cameraRuntime,S_OK);lstrcpyW(g_cameraId,dev[0].displayname);SetWindowTextW(g_cameraEdit,dev[0].displayname);SetWindowTextW(g_cameraConnect,L"Trennen");SetCameraActionMessage(L"ToupTek-Kamera nativ verbunden · SDK-Livebild bereit");return TRUE;
}
static void DisconnectCamera(){
    if(g_externalCameraMode){if(g_afActive)StopAutofocus(FALSE,L"USB/UVC-Kamera getrennt · Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"USB/UVC-Kamera getrennt · Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"USB/UVC-Kamera getrennt · Backlash-Kalibrierung abgebrochen");StopLive();AbortExposure();g_externalCameraMode=FALSE;g_cameraConnected=FALSE;g_cameraWanted=FALSE;SetWindowTextW(g_cameraConnect,L"Verbinden");SetStatus(L"USB/UVC-Kamera getrennt");return;}
    if(g_simulatorMode){if(g_afActive)StopAutofocus(FALSE,L"Synthetische Kamera getrennt · Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"Synthetische Kamera getrennt · Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Synthetische Kamera getrennt · Backlash-Kalibrierung abgebrochen");StopLive();AbortExposure();g_cameraConnected=FALSE;SetWindowTextW(g_cameraConnect,L"Verbinden");return;}
    g_cameraWanted=FALSE;g_resumeLiveAfterCameraRecovery=FALSE;StopLive();if(g_afActive)StopAutofocus(FALSE,L"Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Backlash-Kalibrierung abgebrochen");
    if(g_nativeActive||g_toupDll)UnloadToupTek();
    if(g_cameraWorker)DestroyDeviceWorker(&g_cameraWorker,TRUE);g_cameraConnected=FALSE;g_cameraRuntime.phase=DEV_DISCONNECTED;g_cameraRuntime.removalDetected=FALSE;CopyWBounded(g_cameraRuntime.operation,96,L"camera disconnected by user");g_cameraWorkerBlocked=HasOrphanWorker(TRUE);SetWindowTextW(g_cameraConnect,L"Verbinden");SetStatus(g_cameraWorkerBlocked?L"Kamera getrennt · blockierter ASCOM-Worker bleibt isoliert":L"Kamera getrennt");
}
static void DisconnectFocuser(){
    if(g_simulatorMode){if(g_afActive)StopAutofocus(FALSE,L"Synthetischer Fokussierer getrennt · Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"Synthetischer Fokussierer getrennt · Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Synthetischer Fokussierer getrennt · Backlash-Kalibrierung abgebrochen");g_focuserWanted=FALSE;g_focuserConnected=FALSE;g_cachedFocuserPosition=-1;g_cachedFocuserMoving=FALSE;g_hasFocuserTemperature=FALSE;SetWindowTextW(g_focuserConnect,L"Verbinden");SetWindowTextW(g_positionText,L"–");return;}
    g_focuserWanted=FALSE;if(g_afActive)StopAutofocus(FALSE,L"Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Backlash-Kalibrierung abgebrochen");if(g_focuserWorker)DestroyDeviceWorker(&g_focuserWorker,TRUE);g_focuserConnected=FALSE;g_focuserRuntime.phase=DEV_DISCONNECTED;g_focuserRuntime.positionKnown=FALSE;g_focuserRuntime.removalDetected=FALSE;CopyWBounded(g_focuserRuntime.operation,96,L"focuser disconnected by user");g_cachedFocuserPosition=-1;g_cachedFocuserMoving=FALSE;g_hasFocuserTemperature=FALSE;g_focuserWorkerBlocked=HasOrphanWorker(FALSE);SetWindowTextW(g_focuserConnect,L"Verbinden");SetWindowTextW(g_positionText,L"–");
}
static BOOL ConnectAscomCameraWorker(BOOL silent){
    if(g_cameraWorkerBlocked||HasOrphanWorker(TRUE)){if(!silent)SetCameraActionMessage(L"Der vorherige ASCOM-Kameraaufruf ist noch blockiert. Aus Sicherheitsgründen wird kein zweiter Treiber-Worker gestartet. Warte auf die Freigabe oder starte AstroFocus neu.");return FALSE;}
    if(!g_cameraWorker){g_cameraWorker=CreateDeviceWorker(TRUE);}if(!g_cameraWorker){if(!silent)SetCameraActionMessage(L"Der ASCOM-Kamera-Worker konnte nicht gestartet werden. Prüfe, ob AstroFocusCameraHost.exe vollständig im Programmordner liegt und gestartet werden darf.");return FALSE;}
    DeviceWorker* w=g_cameraWorker;if(!WorkerConnect(w,g_cameraId,8000)){if(g_cameraWorker==w){HRESULT hr=w->hr;wchar_t detail[256],msg[600];HResultText(hr,detail,256);DestroyDeviceWorker(&g_cameraWorker,TRUE);if(!silent){wsprintfW(msg,L"Die Verbindung zur ASCOM-Kamera ist fehlgeschlagen.\r\n\r\n%s\r\n\r\nPrüfe Treiber-ID, ASCOM Platform, Stromversorgung und ob die Kamera bereits von einem anderen Programm verwendet wird.",detail);SetCameraActionMessage(msg);}}ApplyDeviceWorkerFaults();return FALSE;}
    g_cameraConnected=TRUE;g_cameraWanted=TRUE;g_nativeActive=FALSE;g_cameraWorkerBlocked=FALSE;g_cameraWorkerRecoveryAttempt=0;g_cameraWorkerRetryAfter=0;g_maxAdu=(UINT)w->maxAdu;g_cameraRuntime.phase=DEV_READY;g_cameraRuntime.removalDetected=FALSE;g_cameraRuntime.lastSuccessTick=GetTickCount64();CopyWBounded(g_cameraRuntime.operation,96,L"ASCOM camera ready");AppendHardwareEvent(TRUE,L"connected",&g_cameraRuntime,S_OK);SetWindowTextW(g_cameraConnect,L"Trennen");WriteIni(L"Camera",g_cameraId);if(!silent)SetCameraActionMessage(L"ASCOM-Kamera verbunden.");else SetStatus(L"ASCOM-Kamera verbunden · isolierter Geräte-Worker aktiv");return TRUE;
}
static BOOL ConnectAscomFocuserWorker(BOOL silent){
    if(g_focuserSetupReserved){if(!silent)SetFocuserActionMessage(L"Die Fokussiererverbindung ist während des ASCOM-Treiberdialogs gesperrt.");return FALSE;}
    if(g_focuserWorkerBlocked||HasOrphanWorker(FALSE)){if(!silent)SetFocuserActionMessage(L"Der vorherige ASCOM-Fokussiereraufruf ist noch blockiert. Aus Sicherheitsgründen wird kein zweiter Treiber-Worker gestartet. Warte auf die Freigabe oder starte AstroFocus neu.");return FALSE;}
    if(!g_focuserWorker){g_focuserWorker=CreateDeviceWorker(FALSE);}if(!g_focuserWorker){if(!silent)SetFocuserActionMessage(L"Der ASCOM-Fokussierer-Worker konnte nicht gestartet werden. Prüfe, ob AstroFocusFocuserHost.exe vollständig im Programmordner liegt und gestartet werden darf.");return FALSE;}
    DeviceWorker* w=g_focuserWorker;if(!WorkerConnect(w,g_focuserId,8000)){if(g_focuserWorker==w){HRESULT hr=w->hr;wchar_t detail[256],msg[600];HResultText(hr,detail,256);DestroyDeviceWorker(&g_focuserWorker,TRUE);if(!silent){if(hr==(HRESULT)0x80004005L)SetFocuserActionMessage(L"Der ausgewählte Fokussierer meldet keine absolute Position. AstroFocus benötigt einen absoluten ASCOM-Fokussierer.");else{wsprintfW(msg,L"Die Verbindung zum ASCOM-Fokussierer ist fehlgeschlagen.\r\n\r\n%s\r\n\r\nPrüfe Treiber-ID, ASCOM Platform, USB-Verbindung und ob der Fokussierer bereits von einem anderen Programm verwendet wird.",detail);SetFocuserActionMessage(msg);}}}ApplyDeviceWorkerFaults();return FALSE;}
    g_focuserConnected=TRUE;g_focuserWanted=TRUE;g_focuserWorkerBlocked=FALSE;g_focuserWorkerRecoveryAttempt=0;g_focuserWorkerRetryAfter=0;LONG pos=-1,maxStep=200000;BOOL moving=FALSE;WorkerGetInt(w,L"Position",-1,&pos,1200);WorkerGetInt(w,L"MaxStep",200000,&maxStep,1200);WorkerGetBool(w,L"IsMoving",FALSE,&moving,1200);g_cachedFocuserPosition=(int)pos;g_cachedFocuserMaxStep=(int)maxStep;g_cachedFocuserMoving=moving;g_focuserRuntime.positionKnown=pos>=0;g_focuserRuntime.phase=pos>=0?DEV_READY:DEV_POSITION_UNKNOWN;g_focuserRuntime.removalDetected=FALSE;g_focuserRuntime.lastSuccessTick=GetTickCount64();CopyWBounded(g_focuserRuntime.operation,96,pos>=0?L"ASCOM focuser ready":L"position unavailable");AppendHardwareEvent(FALSE,L"connected",&g_focuserRuntime,S_OK);ApplyDeviceWorkerFaults();if(!g_focuserConnected){if(!silent&&!g_lastFocuserActionMessage[0])SetFocuserActionMessage(L"Der ASCOM-Fokussierer wurde unmittelbar nach dem Verbinden wieder getrennt.");return FALSE;}wchar_t positionText[32];if(pos>=0)wsprintfW(positionText,L"%d",(int)pos);else lstrcpyW(positionText,L"–");SetWindowTextW(g_positionText,positionText);SetWindowTextW(g_focuserConnect,L"Trennen");WriteIni(L"Focuser",g_focuserId);g_autoStartPending=TRUE;if(!silent)SetFocuserActionMessage(L"ASCOM-Fokussierer verbunden.");else SetStatus(L"ASCOM-Fokussierer verbunden · isolierter Geräte-Worker aktiv");return TRUE;
}
static BOOL ConnectCamera(){
    g_lastCameraActionMessage[0]=0;
    if(g_cameraConnected){DisconnectCamera();SetCameraActionMessage(L"Kamera getrennt.");return !g_cameraConnected;}
    g_nativeRequested=IsChecked(g_nativeCheck);if(g_nativeRequested)return ConnectNativeCamera();
    GetWindowTextW(g_cameraEdit,g_cameraId,256);if(!g_cameraId[0]){SetCameraActionMessage(L"Bitte zuerst einen ASCOM-Kameratreiber auswählen oder den nativen ToupTek-Modus aktivieren.");return FALSE;}
    BOOL ok=ConnectAscomCameraWorker(FALSE);if(ok&&!g_lastCameraActionMessage[0])SetCameraActionMessage(L"ASCOM-Kamera verbunden.");else if(!ok&&!g_lastCameraActionMessage[0])SetCameraActionMessage(L"Die ASCOM-Kamera konnte nicht verbunden werden. Prüfe Treiber-ID, ASCOM-Installation und Gerätestatus.");return ok;
}
static BOOL ConnectFocuser(){
    g_lastFocuserActionMessage[0]=0;
    if(g_focuserSetupReserved){SetFocuserActionMessage(L"Die Fokussiererverbindung ist während des ASCOM-Treiberdialogs gesperrt.");return FALSE;}
    if(g_focuserConnected){DisconnectFocuser();SetFocuserActionMessage(L"Fokussierer getrennt.");return !g_focuserConnected;}
    GetWindowTextW(g_focuserEdit,g_focuserId,256);if(!g_focuserId[0]){SetFocuserActionMessage(L"Bitte zuerst einen ASCOM-Fokussierertreiber auswählen.");return FALSE;}
    BOOL ok=ConnectAscomFocuserWorker(FALSE);if(ok&&!g_lastFocuserActionMessage[0])SetFocuserActionMessage(L"ASCOM-Fokussierer verbunden.");else if(!ok&&!g_lastFocuserActionMessage[0])SetFocuserActionMessage(L"Der ASCOM-Fokussierer konnte nicht verbunden werden. Prüfe Treiber-ID, ASCOM-Installation und Gerätestatus.");return ok;
}

static void FreeImage(){Free(g_raw);Free(g_display);g_raw=0;g_display=0;g_width=g_height=0;g_frameReady=FALSE;}
static BOOL EnsureImage(int w,int h){
    if(w<=0||h<=0||w>10000||h>10000)return FALSE;if(w==g_width&&h==g_height&&g_raw&&g_display)return TRUE;FreeImage();SIZE_T count=(SIZE_T)w*(SIZE_T)h;g_raw=(UINT*)Alloc(count*sizeof(UINT));g_display=(DWORD*)Alloc(count*sizeof(DWORD));if(!g_raw||!g_display){FreeImage();return FALSE;}g_width=w;g_height=h;memset(&g_bmi,0,sizeof(g_bmi));g_bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);g_bmi.bmiHeader.biWidth=w;g_bmi.bmiHeader.biHeight=-h;g_bmi.bmiHeader.biPlanes=1;g_bmi.bmiHeader.biBitCount=32;g_bmi.bmiHeader.biCompression=BI_RGB;return TRUE;
}

#pragma pack(push,1)
struct ExternalBmpFileHeader { WORD type; DWORD size; WORD r1; WORD r2; DWORD offBits; };
#pragma pack(pop)
static BOOL LoadExternalBmp(){
    wchar_t path[700];lstrcpyW(path,g_appDir);lstrcatW(path,L"UsbCameraFrame.bmp");
    HANDLE f=CreateFileW(path,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return FALSE;
    DWORD fs=GetFileSize(f,0);if(fs<54){CloseHandle(f);return FALSE;}
    ExternalBmpFileHeader fh;BITMAPINFOHEADER ih;DWORD rd=0;if(!ReadFile(f,&fh,sizeof(fh),&rd,0)||rd!=sizeof(fh)||fh.type!=0x4D42){CloseHandle(f);return FALSE;}if(!ReadFile(f,&ih,sizeof(ih),&rd,0)||rd!=sizeof(ih)){CloseHandle(f);return FALSE;}
    long long width64=(long long)ih.biWidth,heightSigned=(long long)ih.biHeight,height64=heightSigned<0?-heightSigned:heightSigned;int bpp=ih.biBitCount;
    if(width64<=0||width64>10000||height64<=0||height64>10000||(bpp!=24&&bpp!=32)||ih.biCompression!=BI_RGB){CloseHandle(f);return FALSE;}
    int w=(int)width64,h=(int)height64,bytesPerPixel=bpp/8;unsigned long long rowBytes=(unsigned long long)w*(unsigned long long)bytesPerPixel;unsigned long long stride64=(rowBytes+3ULL)&~3ULL;
    if(stride64==0||stride64>0xffffffffULL){CloseHandle(f);return FALSE;}DWORD stride=(DWORD)stride64;unsigned long long need=(unsigned long long)fh.offBits+stride64*(unsigned long long)h;if(need>fs){CloseHandle(f);return FALSE;}
    if(!EnsureImage(w,h)){CloseHandle(f);return FALSE;}BYTE* row=(BYTE*)Alloc((SIZE_T)stride);if(!row){CloseHandle(f);return FALSE;}SetFilePointer(f,(LONG)fh.offBits,0,FILE_BEGIN);BOOL bottomUp=ih.biHeight>0;UINT maxSeen=0;
    for(int fy=0;fy<h;fy++){if(!ReadFile(f,row,stride,&rd,0)||rd!=stride){Free(row);CloseHandle(f);return FALSE;}int y=bottomUp?(h-1-fy):fy;for(int x=0;x<w;x++){BYTE b=row[x*bytesPerPixel],g=row[x*bytesPerPixel+1],r=row[x*bytesPerPixel+2];UINT q=(29U*b+150U*g+77U*r)>>8;g_raw[(SIZE_T)y*(SIZE_T)w+(SIZE_T)x]=q;if(q>maxSeen)maxSeen=q;}}
    Free(row);CloseHandle(f);g_maxAdu=maxSeen?255:255;g_frameReady=TRUE;return TRUE;
}

static DWORD CameraImageDownloadTimeoutMs(){
    unsigned long long pixels=0;if(g_cameraWorker&&g_cameraWorker->cameraX>0&&g_cameraWorker->cameraY>0)pixels=(unsigned long long)(unsigned)g_cameraWorker->cameraX*(unsigned long long)(unsigned)g_cameraWorker->cameraY;
    DWORD ms=6000+(DWORD)(pixels/250000ULL)*750;if(ms<6000)ms=6000;if(ms>30000)ms=30000;return ms;
}
static BOOL DownloadImage(){
    UINT* pixels=0;int w=0,h=0,maxAdu=0;DWORD timeout=CameraImageDownloadTimeoutMs();if(!WorkerGetImage(g_cameraWorker,&pixels,&w,&h,&maxAdu,timeout)){ApplyDeviceWorkerFaults();if(g_cameraWorker)ShowComError(L"Das Herunterladen des Kamerabildes",g_cameraWorker->hr);return FALSE;}
    if(!pixels||w<=0||h<=0||w>10000||h>10000){if(pixels)Free(pixels);NotifyUser(L"Der isolierte Kamera-Host hat ungültige Bildabmessungen geliefert.",L"Ungültiges Bild",MB_OK|MB_ICONERROR);return FALSE;}
    unsigned long long bytes=(unsigned long long)(unsigned)w*(unsigned long long)(unsigned)h*sizeof(UINT);if(bytes>AF_HOST_MAX_IMAGE_BYTES||!EnsureImage(w,h)){Free(pixels);NotifyUser(L"Für das Kamerabild konnte nicht genügend Speicher reserviert werden.",L"Speicherfehler",MB_OK|MB_ICONERROR);return FALSE;}
    memcpy(g_raw,pixels,(SIZE_T)bytes);Free(pixels);if(maxAdu>0)g_maxAdu=(UINT)maxAdu;g_frameReady=TRUE;return TRUE;
}

static BOOL DownloadNativeImage(){
    if(!g_nativeActive||!g_tcam||!pToupcam_PullImageV2||!pToupcam_get_Size)return FALSE;
    int expectedW=0,expectedH=0;if(FAILED(pToupcam_get_Size(g_tcam,&expectedW,&expectedH))||!PrepareNativeBuffers(expectedW,expectedH))return FALSE;
    ToupcamFrameInfoV2 info;memset(&info,0,sizeof(info));HRESULT hr;
    if(pToupcam_PullImageWithRowPitchV2)hr=pToupcam_PullImageWithRowPitchV2(g_tcam,g_nativeRgb,24,g_nativeStride,&info);else hr=pToupcam_PullImageV2(g_tcam,g_nativeRgb,24,&info);
    if(FAILED(hr))return FALSE;int w=(int)info.width,h=(int)info.height;if(w<=0||h<=0||w>10000||h>10000)return FALSE;
    if(w!=expectedW||h!=expectedH){PrepareNativeBuffers(w,h);return FALSE;}
    unsigned long long required=(unsigned long long)(unsigned)g_nativeStride*(unsigned long long)(unsigned)h;if(required>(unsigned long long)g_nativeRgbBytes)return FALSE;
    for(int y=0;y<h;y++){BYTE* row=g_nativeRgb+(SIZE_T)y*(SIZE_T)g_nativeStride;for(int x=0;x<w;x++){BYTE b=row[x*3],g=row[x*3+1],r=row[x*3+2];g_raw[(SIZE_T)y*(SIZE_T)w+(SIZE_T)x]=(UINT)((29U*b+150U*g+77U*r)>>8);}}
    g_maxAdu=255;g_frameReady=TRUE;return TRUE;
}
static void SortDoubles(double* a,int n){for(int i=1;i<n;i++){double v=a[i];int j=i-1;while(j>=0&&a[j]>v){a[j+1]=a[j];j--;}a[j+1]=v;}}
static double Median(double* a,int n){if(n<=0)return 0.0;SortDoubles(a,n);return (n&1)?a[n/2]:(a[n/2-1]+a[n/2])*0.5;}
static int ClampI(int v,int a,int b){return v<a?a:(v>b?b:v);}
static double ClampD(double v,double a,double b){return v<a?a:(v>b?b:v);}
static BOOL FiniteD(double v){return v==v&&v>-1.0e300&&v<1.0e300;}
static double JsonNumber(double v,double fallback){return FiniteD(v)?v:fallback;}

struct Candidate{int x,y;UINT peak;};
static void InsertCandidate(Candidate* c,int* count,int maxCount,int x,int y,UINT peak){
    int n=*count;if(n<maxCount)n++;int pos=n-1;while(pos>0&&c[pos-1].peak<peak){if(pos<maxCount)c[pos]=c[pos-1];pos--;}if(pos<maxCount){c[pos].x=x;c[pos].y=y;c[pos].peak=peak;}*count=n;
}

static void AppendTrend(double fwhm,double hfr){if(g_syntheticSelfTestActive||fwhm<=0||hfr<=0)return;g_trendFwhm[g_trendHead]=fwhm;g_trendHfr[g_trendHead]=hfr;g_trendStars[g_trendHead]=g_usedCount;g_trendHead=(g_trendHead+1)%120;if(g_trendCount<120)g_trendCount++;UpdateSeeingAndFocusRecommendation();}
static int AngleDiff180(int a,int b){int d=a-b;if(d<0)d=-d;while(d>=180)d-=180;if(d>90)d=180-d;return d;}
static int MidAngle180(int a,int b){int aa=a,bb=b;if(aa>bb){int t=aa;aa=bb;bb=t;}if(bb-aa>90)aa+=180;int m=(aa+bb)/2;while(m>=180)m-=180;return m;}
static double BahtinovLineScore(int cx,int cy,double cs,double sn,int offset){double sum=0.0;for(int t=-30;t<=30;t++){int x=(int)(cx+t*cs-offset*sn+(cx+t*cs-offset*sn>=0?0.5:-0.5));int y=(int)(cy+t*sn+offset*cs+(cy+t*sn+offset*cs>=0?0.5:-0.5));if(x<1||y<1||x>=g_width-1||y>=g_height-1)continue;double q=(double)g_raw[(SIZE_T)y*g_width+x]-(double)g_background;if(q>0)sum+=q;}return sum;}
static void ComputeBahtinov(int cx,int cy){
    g_bahtinovValid=FALSE;g_bahtinovOffset=0.0;g_bahtinovConfidence=0.0;if(!g_raw||cx<35||cy<35||cx>=g_width-35||cy>=g_height-35)return;
    const int ac=60;double bestScore[ac],angleScore[ac];int bestOffset[ac];for(int a=0;a<ac;a++){double th=(double)(a*3)*3.14159265358979323846/180.0,cs=cos(th),sn=sin(th);double bs=-1;int bo=0;for(int o=-9;o<=9;o++){double sc=BahtinovLineScore(cx,cy,cs,sn,o);if(sc>bs){bs=sc;bo=o;}}bestScore[a]=bs;angleScore[a]=bs;bestOffset[a]=bo;}
    double med[ac];for(int i=0;i<ac;i++)med[i]=angleScore[i];double median=Median(med,ac);int sel[3]={-1,-1,-1};for(int k=0;k<3;k++){double bv=-1;for(int a=0;a<ac;a++){BOOL sep=TRUE;for(int j=0;j<k;j++)if(AngleDiff180(a*3,sel[j]*3)<18){sep=FALSE;break;}if(sep&&bestScore[a]>bv){bv=bestScore[a];sel[k]=a;}}if(sel[k]<0)return;}
    double top=bestScore[sel[0]],third=bestScore[sel[2]];if(median<=0||top/median<1.10||third/top<0.28)return;
    int central=0,bestMid=999;for(int i=0;i<3;i++){int a=sel[(i+1)%3]*3,b=sel[(i+2)%3]*3,m=MidAngle180(a,b),d=AngleDiff180(sel[i]*3,m);if(d<bestMid){bestMid=d;central=i;}}
    int oi=(central+1)%3,oj=(central+2)%3;double ti=sel[oi]*3.0*3.14159265358979323846/180.0,tj=sel[oj]*3.0*3.14159265358979323846/180.0,tc=sel[central]*3.0*3.14159265358979323846/180.0;
    double nix=-sin(ti),niy=cos(ti),njx=-sin(tj),njy=cos(tj),det=nix*njy-niy*njx;if(fabs(det)<0.08)return;double di=bestOffset[sel[oi]],dj=bestOffset[sel[oj]];double ix=(di*njy-niy*dj)/det,iy=(nix*dj-di*njx)/det;if(fabs(ix)>28||fabs(iy)>28)return;double ncx=-sin(tc),ncy=cos(tc),dc=bestOffset[sel[central]];g_bahtinovOffset=ncx*ix+ncy*iy-dc;
    double symmetry=ClampD(1.0-(double)bestMid/22.0,0,1),contrast=ClampD((top/median-1.08)/1.2,0,1),balance=ClampD(third/top,0,1);g_bahtinovConfidence=0.45*symmetry+0.35*contrast+0.20*balance;g_bahtinovValid=g_bahtinovConfidence>=0.30;
}
static void ComputeTilt(){
    g_tiltValid=FALSE;g_tiltMagnitude=g_tiltDx=g_tiltDy=0.0;g_fieldCurvature=g_fieldAsymmetry=0.0;g_fieldQualityScore=0.0;g_tiltConfidence=0.0;lstrcpyW(g_tiltDirection,L"–");CopyWBounded(g_fieldAdvice,240,L"Noch keine ausreichende Bildfeldmessung.");
    double l=0,r=0,t=0,b=0;int ln=0,rn=0,tn=0,bn=0,populated=0;double mn=1e30,mx=0.0;
    for(int z=0;z<9;z++)if(g_zoneCount[z]){int x=z%3,y=z/3;double q=g_zoneFwhm[z];populated++;if(q<mn)mn=q;if(q>mx)mx=q;if(x==0){l+=q;ln++;}if(x==2){r+=q;rn++;}if(y==0){t+=q;tn++;}if(y==2){b+=q;bn++;}}
    if(!ln||!rn||!tn||!bn)return;l/=ln;r/=rn;t/=tn;b/=bn;g_tiltDx=r-l;g_tiltDy=b-t;g_tiltMagnitude=sqrt(g_tiltDx*g_tiltDx+g_tiltDy*g_tiltDy);g_tiltValid=TRUE;g_tiltConfidence=ClampD((double)populated/9.0,0.0,1.0);
    double eps=0.08;BOOL right=g_tiltDx>eps,left=g_tiltDx<-eps,down=g_tiltDy>eps,up=g_tiltDy<-eps;if(right&&down)lstrcpyW(g_tiltDirection,L"rechts unten unschärfer");else if(right&&up)lstrcpyW(g_tiltDirection,L"rechts oben unschärfer");else if(left&&down)lstrcpyW(g_tiltDirection,L"links unten unschärfer");else if(left&&up)lstrcpyW(g_tiltDirection,L"links oben unschärfer");else if(right)lstrcpyW(g_tiltDirection,L"rechts unschärfer");else if(left)lstrcpyW(g_tiltDirection,L"links unschärfer");else if(down)lstrcpyW(g_tiltDirection,L"unten unschärfer");else if(up)lstrcpyW(g_tiltDirection,L"oben unschärfer");else lstrcpyW(g_tiltDirection,L"weitgehend gleichmäßig");
    if(mx>=mn&&mn<1e29)g_fieldAsymmetry=mx-mn;
    if(g_zoneCount[4]){double corners=0.0;int cn=0;const int cidx[4]={0,2,6,8};for(int i=0;i<4;i++){int z=cidx[i];if(g_zoneCount[z]){corners+=g_zoneFwhm[z];cn++;}}if(cn)g_fieldCurvature=corners/(double)cn-g_zoneFwhm[4];}
    double tiltPenalty=ClampD(g_tiltMagnitude/1.2,0.0,1.0),curvePenalty=ClampD(fabs(g_fieldCurvature)/1.2,0.0,1.0),asymPenalty=ClampD(g_fieldAsymmetry/1.8,0.0,1.0);g_fieldQualityScore=ClampD(100.0*(1.0-0.45*tiltPenalty-0.30*curvePenalty-0.25*asymPenalty)*g_tiltConfidence,0.0,100.0);
    wchar_t curv[32],tilt[32],qual[32];FormatFixed(g_fieldCurvature,2,curv);FormatFixed(g_tiltMagnitude,2,tilt);FormatFixed(g_fieldQualityScore,0,qual);
    if(g_tiltConfidence<0.65)CopyWBounded(g_fieldAdvice,240,L"Zu wenige belastbare Zonen für eine sichere Tilt-/Feldkrümmungsdiagnose.");
    else if(g_tiltMagnitude>=0.45){wsprintfW(g_fieldAdvice,L"Tilt auffällig: %s (Δ %s px). Sensor-/Adapterausrichtung prüfen; Feldqualität %s/100.",g_tiltDirection,tilt,qual);}
    else if(g_fieldCurvature>=0.45){wsprintfW(g_fieldAdvice,L"Ecken sind im Mittel %s px unschärfer als das Zentrum; Feldkrümmung/Abstand prüfen. Qualität %s/100.",curv,qual);}
    else if(g_fieldCurvature<=-0.45){wsprintfW(g_fieldAdvice,L"Zentrum ist gegenüber den Ecken auffällig unschärfer (Δ %s px); Fokuslage/Abstand prüfen. Qualität %s/100.",curv,qual);}
    else wsprintfW(g_fieldAdvice,L"Bildfeld weitgehend gleichmäßig · Tilt Δ %s px · Feldqualität %s/100.",tilt,qual);
}
static BOOL IsTrackableFocusStar(const StarMetric* st,BOOL requireFieldQuality){
    if(!st||!FiniteD(st->x)||!FiniteD(st->y)||!FiniteD(st->fwhm)||!FiniteD(st->hfr)||!FiniteD(st->snr)||!FiniteD(st->ecc))return FALSE;
    if(st->saturated||st->x<0.0||st->y<0.0||st->fwhm<=1.10||st->fwhm>1000.0||st->hfr<=0.40||st->hfr>1000.0||st->snr<3.0||st->snr>1.0e9||st->ecc<0.0||st->ecc>0.78)return FALSE;
    return !requireFieldQuality||st->used;
}
static int FindNearestFocusStar(double x,double y,double maxDistance,BOOL requireFieldQuality){
    if(!(x==x)||!(y==y)||!(maxDistance==maxDistance)||maxDistance<=0.0)return -1;int count=g_starCount;if(count<0)count=0;if(count>MAX_STARS)count=MAX_STARS;
    int best=-1;double bestD=maxDistance*maxDistance;
    for(int i=0;i<count;i++){
        StarMetric* st=&g_stars[i];if(!IsTrackableFocusStar(st,requireFieldQuality))continue;
        double dx=st->x-x,dy=st->y-y,d=dx*dx+dy*dy;if(d<=bestD){bestD=d;best=i;}
    }
    return best;
}
static void ResolveSelectedStar(){
    if(g_starCount<0||g_starCount>MAX_STARS||g_width<=0||g_height<=0){g_selectedStar=-1;return;}
    if(g_manualStarLocked){
        double tx=g_selectedTargetNx*(double)g_width,ty=g_selectedTargetNy*(double)g_height;
        // Keep the lock local. A wide search radius could silently jump to a neighbouring star.
        double radius=(double)(g_width<g_height?g_width:g_height)*0.035;if(radius<12.0)radius=12.0;if(radius>30.0)radius=30.0;
        int best=FindNearestFocusStar(tx,ty,radius,FALSE);
        if(best>=0){g_selectedStar=best;g_selectedTargetNx=g_stars[best].x/(double)g_width;g_selectedTargetNy=g_stars[best].y/(double)g_height;g_selectedStarMisses=0;}
        else{g_selectedStar=-1;g_selectedStarMisses++;}
        return;
    }
    g_selectedStar=-1;double bestSnr=-1.0;
    for(int i=0;i<g_starCount;i++)if(IsTrackableFocusStar(&g_stars[i],TRUE)&&g_stars[i].snr>bestSnr){bestSnr=g_stars[i].snr;g_selectedStar=i;}
}
static BOOL SelectManualStarAt(int sx,int sy){
    // Selection needs only the immutable metrics from the last completed analysis. Requiring or
    // reading g_raw here tied a harmless mouse click to a multi-megabyte camera buffer.
    if(!g_frameReady||g_width<=0||g_height<=0||g_width>10000||g_height>10000||g_starCount<=0||g_starCount>MAX_STARS||sx<0||sy<0||sx>=g_width||sy>=g_height)return FALSE;
    double radius=(double)(g_width<g_height?g_width:g_height)*0.09;if(radius<28.0)radius=28.0;if(radius>80.0)radius=80.0;
    int best=FindNearestFocusStar((double)sx,(double)sy,radius,TRUE);if(best<0)return FALSE;
    g_selectedStar=best;g_manualStarLocked=TRUE;g_afUseSelectedStar=TRUE;g_selectedTargetNx=g_stars[best].x/(double)g_width;g_selectedTargetNy=g_stars[best].y/(double)g_height;g_selectedStarMisses=0;return TRUE;
}
static void ClearManualStarSelection(){g_manualStarLocked=FALSE;g_afUseSelectedStar=FALSE;g_selectedStarMisses=0;ResolveSelectedStar();}
static BOOL RefreshSelectedStarAnalysis(){
    g_bahtinovScore=0.0;g_bahtinovValid=FALSE;
    if(!g_frameReady||g_width<=2||g_height<=2||g_width>10000||g_height>10000||g_starCount<=0||g_starCount>MAX_STARS||g_selectedStar<0||g_selectedStar>=g_starCount)return FALSE;
    StarMetric* st=&g_stars[g_selectedStar];if(!IsTrackableFocusStar(st,FALSE)||st->x>=(double)g_width||st->y>=(double)g_height)return FALSE;
    // Normal star selection is deliberately metadata-only. This avoids touching the large
    // camera frame from an API/UI selection request. Raw pixels are read only when the
    // user has explicitly enabled the Bahtinov analysis.
    double denom=st->fwhm*st->hfr;if(FiniteD(denom)&&denom>0.0){double score=st->snr/denom;if(FiniteD(score)&&score>0.0)g_bahtinovScore=score;}
    if(IsChecked(g_bahtinovCheck)&&g_raw){int sx=(int)st->x,sy=(int)st->y;ComputeBahtinov(sx,sy);}return TRUE;
}
static BOOL CurrentAutofocusMetric(BOOL selectedMode,double* hfr,double* fwhm,int* used){
    if(hfr)*hfr=0.0;if(fwhm)*fwhm=0.0;if(used)*used=0;
    if(selectedMode){
        if(!g_manualStarLocked||g_selectedStar<0||g_selectedStar>=g_starCount)return FALSE;
        StarMetric* st=&g_stars[g_selectedStar];if(!IsTrackableFocusStar(st,FALSE))return FALSE;
        if(hfr)*hfr=st->hfr;if(fwhm)*fwhm=st->fwhm;if(used)*used=1;return TRUE;
    }
    if(g_usedCount<g_refocusMinStars||g_medianHfr<=0.0||g_medianFwhm<=0.0)return FALSE;
    if(hfr)*hfr=g_medianHfr;if(fwhm)*fwhm=g_medianFwhm;if(used)*used=g_usedCount;return TRUE;
}

static void AnalyseImage(){
    g_starCount=0;g_usedCount=0;g_saturatedCount=0;g_rejectWeak=g_rejectHot=g_rejectEdge=g_rejectElongated=0;g_medianFwhm=g_medianHfr=g_medianSnr=g_medianEcc=0.0;g_bahtinovScore=0.0;for(int z=0;z<9;z++){g_zoneFwhm[z]=0.0;g_zoneCount[z]=0;}if(!g_raw||g_width<32||g_height<32)return;
    const int bins=4096;UINT hist[bins];memset(hist,0,sizeof(hist));SIZE_T count=(SIZE_T)g_width*g_height;UINT maxAdu=g_maxAdu?g_maxAdu:4095;
    for(SIZE_T i=0;i<count;i++){UINT b=(UINT)(((unsigned long long)g_raw[i]*4095ULL)/maxAdu);if(b>4095)b=4095;hist[b]++;}
    memset(g_histogram,0,sizeof(g_histogram));for(int i=0;i<4096;i++)g_histogram[i/32]+=hist[i];
    unsigned long long total=count,c=0;int p10=0,p50=0,p84=0,p995=4095;BOOL got10=FALSE,got50=FALSE,got84=FALSE;for(int i=0;i<bins;i++){c+=hist[i];if(!got10&&c>=total/10){p10=i;got10=TRUE;}if(!got50&&c>=total/2){p50=i;got50=TRUE;}if(!got84&&c>=total*84/100){p84=i;got84=TRUE;}if(c>=total*995/1000){p995=i;break;}}
    g_background=(UINT)(((unsigned long long)p50*maxAdu)/4095ULL);g_noise=(double)(p84-p50)*(double)maxAdu/4095.0;if(g_noise<0.7)g_noise=0.7;g_lowAdu=(UINT)(((unsigned long long)p10*maxAdu)/4095ULL);g_highAdu=(UINT)(((unsigned long long)p995*maxAdu)/4095ULL);if(g_highAdu<=g_lowAdu+8)g_highAdu=g_lowAdu+8;
    double threshold=(double)g_background+5.5*g_noise;double minThr=(double)g_background+(double)maxAdu*0.003;if(threshold<minThr)threshold=minThr;
    Candidate cand[520];int candCount=0;for(int y=9;y<g_height-9;y++)for(int x=9;x<g_width-9;x++){UINT q=g_raw[(SIZE_T)y*g_width+x];if((double)q<threshold)continue;BOOL local=TRUE;for(int dy=-1;dy<=1&&local;dy++)for(int dx=-1;dx<=1;dx++){if(!dx&&!dy)continue;if(g_raw[(SIZE_T)(y+dy)*g_width+x+dx]>q){local=FALSE;break;}}if(local)InsertCandidate(cand,&candCount,520,x,y,q);}
    for(int ci=0;ci<candCount&&g_starCount<MAX_STARS;ci++){
        int cx0=cand[ci].x,cy0=cand[ci].y;if(cx0<11||cy0<11||cx0>=g_width-11||cy0>=g_height-11){g_rejectEdge++;continue;}BOOL near=FALSE;for(int st=0;st<g_starCount;st++){double dx=g_stars[st].x-cx0,dy=g_stars[st].y-cy0;if(dx*dx+dy*dy<81.0){near=TRUE;break;}}if(near)continue;
        UINT peak=cand[ci].peak;double neigh=0.0;int neighN=0;for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++)if(dx||dy){neigh+=g_raw[(SIZE_T)(cy0+dy)*g_width+cx0+dx];neighN++;}neigh/=neighN;if((double)peak>(double)g_background+12*g_noise&&neigh-(double)g_background<((double)peak-(double)g_background)*0.10){g_rejectHot++;continue;}
        double bgSum=0.0;int bgN=0;for(int dy=-10;dy<=10;dy++)for(int dx=-10;dx<=10;dx++){int r2=dx*dx+dy*dy;if(r2>=64&&r2<=100){bgSum+=g_raw[(SIZE_T)(cy0+dy)*g_width+cx0+dx];bgN++;}}double bg=bgN?bgSum/bgN:(double)g_background;
        double flux=0,sx=0,sy=0;peak=0;for(int dy=-7;dy<=7;dy++)for(int dx=-7;dx<=7;dx++){if(dx*dx+dy*dy>49)continue;UINT q=g_raw[(SIZE_T)(cy0+dy)*g_width+cx0+dx];if(q>peak)peak=q;double w=(double)q-bg;if(w>0){flux+=w;sx+=(cx0+dx)*w;sy+=(cy0+dy)*w;}}if(flux<g_noise*65.0){g_rejectWeak++;continue;}
        double cx=sx/flux,cy=sy/flux;if(cx<9||cy<9||cx>=g_width-9||cy>=g_height-9){g_rejectEdge++;continue;}int icx=(int)(cx+0.5),icy=(int)(cy+0.5);double mxx=0,myy=0,mxy=0,usedFlux=0;double radial[48];memset(radial,0,sizeof(radial));for(int dy=-8;dy<=8;dy++)for(int dx=-8;dx<=8;dx++){double px=(double)(icx+dx)-cx,py=(double)(icy+dy)-cy,r2=px*px+py*py;if(r2>64)continue;double w=(double)g_raw[(SIZE_T)(icy+dy)*g_width+icx+dx]-bg;if(w<=0)continue;usedFlux+=w;mxx+=px*px*w;myy+=py*py*w;mxy+=px*py*w;int rb=(int)(sqrt(r2)*4.0);if(rb<48)radial[rb]+=w;}if(usedFlux<=0){g_rejectWeak++;continue;}
        mxx/=usedFlux;myy/=usedFlux;mxy/=usedFlux;double trace=mxx+myy,disc=sqrt((mxx-myy)*(mxx-myy)+4*mxy*mxy),major=(trace+disc)*0.5,minor=(trace-disc)*0.5;if(minor<0)minor=0;double sigma=sqrt(trace*0.5),fwhm=2.354820045*sigma;if(fwhm<1.15){g_rejectHot++;continue;}if(fwhm>20){g_rejectWeak++;continue;}double half=usedFlux*0.5,cum=0,hfr=0;for(int b=0;b<48;b++){double binFlux=radial[b];if(cum+binFlux>=half){double fraction=binFlux>0.0?(half-cum)/binFlux:0.0;fraction=ClampD(fraction,0.0,1.0);hfr=((double)b+fraction)/4.0;break;}cum+=binFlux;}if(hfr<0.45||hfr>11){g_rejectWeak++;continue;}double ecc=major>0?sqrt(ClampD(1.0-minor/major,0,1)):0;double snr=usedFlux/sqrt(usedFlux+180.0*g_noise*g_noise);BOOL sat=peak>=(UINT)((double)maxAdu*0.95);BOOL used=!sat&&snr>=6.0&&ecc<=0.68;if(ecc>0.78){g_rejectElongated++;continue;}
        StarMetric* sm=&g_stars[g_starCount++];sm->x=cx;sm->y=cy;sm->fwhm=fwhm;sm->hfr=hfr;sm->snr=snr;sm->ecc=ecc;sm->peak=peak;sm->saturated=sat;sm->used=used;int zx=ClampI((int)(cx*3.0/g_width),0,2),zy=ClampI((int)(cy*3.0/g_height),0,2);sm->zone=zy*3+zx;if(sat)g_saturatedCount++;if(used)g_usedCount++;
    }
    double f[MAX_STARS],h[MAX_STARS],sn[MAX_STARS],ec[MAX_STARS];int n=0;for(int i=0;i<g_starCount;i++)if(g_stars[i].used){f[n]=g_stars[i].fwhm;h[n]=g_stars[i].hfr;sn[n]=g_stars[i].snr;ec[n]=g_stars[i].ecc;n++;}if(n<3){n=0;for(int i=0;i<g_starCount;i++)if(!g_stars[i].saturated){f[n]=g_stars[i].fwhm;h[n]=g_stars[i].hfr;sn[n]=g_stars[i].snr;ec[n]=g_stars[i].ecc;n++;}}if(n){g_medianFwhm=Median(f,n);g_medianHfr=Median(h,n);g_medianSnr=Median(sn,n);g_medianEcc=Median(ec,n);}
    for(int z=0;z<9;z++){double zf[MAX_STARS];int zn=0;for(int i=0;i<g_starCount;i++)if(g_stars[i].used&&g_stars[i].zone==z)zf[zn++]=g_stars[i].fwhm;g_zoneCount[z]=zn;if(zn)g_zoneFwhm[z]=Median(zf,zn);}ComputeTilt();
    ResolveSelectedStar();if(g_selectedStar>=0)RefreshSelectedStarAnalysis();else{g_bahtinovScore=0.0;g_bahtinovValid=FALSE;}
}

static void BuildDisplay(){
    if(!g_raw||!g_display)return;UINT low=IsChecked(g_autoStretch)?g_lowAdu:0;UINT high=IsChecked(g_autoStretch)?g_highAdu:g_maxAdu;if(high<=low)high=low+1;SIZE_T n=(SIZE_T)g_width*g_height;
    for(SIZE_T i=0;i<n;i++){UINT q=g_raw[i];int v=q<=low?0:(q>=high?255:(int)(((unsigned long long)(q-low)*255ULL)/(high-low)));if(v<0)v=0;if(v>255)v=255;g_display[i]=RGB(v,v,v);}g_frameSequence++;
}

static BOOL GenerateDemoFrame(){
    int w=1920,h=1080;if(!EnsureImage(w,h))return FALSE;static int phase=0;phase++;UINT bg=260;for(int y=0;y<h;y++)for(int x=0;x<w;x++){UINT noise=(UINT)((x*17+y*31+phase*13+(x*y)%97)%41);g_raw[(SIZE_T)y*w+x]=bg+noise;}
    static const int sx[24]={120,250,370,510,690,840,1000,1160,1320,1510,1680,1810,220,430,620,780,970,1140,1290,1450,1620,1760,340,1380};
    static const int sy[24]={130,210,105,310,180,390,140,260,110,350,190,290,620,730,570,820,650,760,540,700,620,810,450,460};
    double sigma=1.55+0.25*((phase/20)%3);for(int k=0;k<24;k++){int cx=sx[k],cy=sy[k];UINT amp=2200+(k%7)*220;for(int dy=-9;dy<=9;dy++)for(int dx=-9;dx<=9;dx++){double r2=(double)(dx*dx+dy*dy);double t=1.0+r2/(2.0*sigma*sigma);double val=(double)amp/(t*t*t);UINT* q=&g_raw[(SIZE_T)(cy+dy)*w+cx+dx];UINT nv=*q+(UINT)val;if(nv>4095)nv=4095;*q=nv;}}
    g_maxAdu=4095;g_frameReady=TRUE;AnalyseImage();BuildDisplay();InvalidateRect(g_main,0,FALSE);return TRUE;
}


static unsigned SimHash(unsigned x){x^=x>>16;x*=0x7feb352dU;x^=x>>15;x*=0x846ca68bU;x^=x>>16;return x;}
static LPCWSTR SimulatorProfileName(int profile){
    switch(profile){
        case SIM_FEW_STARS:return L"Wenige Sterne";
        case SIM_DEFOCUSED:return L"Stark defokussiert";
        case SIM_POOR_SEEING:return L"Schlechtes Seeing";
        case SIM_VARIABLE_SEEING:return L"Stark schwankendes Seeing";
        case SIM_THIN_CLOUDS:return L"Dünne Wolken / wechselnde Transparenz";
        case SIM_ELONGATED:return L"Elongierte Sterne / Guidingfehler";
        case SIM_DIFFICULT:return L"Schwierige Nacht";
        default:return L"Normal / Referenz";
    }
}
static void SelectSimulatorProfile(){
    int selected=g_simProfileMode;
    g_simProfileSelectionSequence++;
    if(selected==SIM_RANDOM){unsigned seed=SimHash(g_simRandomSeed^g_simFrameSequence^(g_simProfileSelectionSequence*0x9E3779B9U)^0x324A5F11U);selected=(int)(seed%8U);}
    g_simActiveProfile=ClampI(selected,SIM_NORMAL,SIM_DIFFICULT);CopyWBounded(g_simProfileName,96,SimulatorProfileName(g_simActiveProfile));
}
struct SimulatorFrameProfile{
    int starCount;double noiseScale,tiltX,tiltY,defocusOffset,seeingBias,seeingSwing,transparencyBase,transparencySwing,elongation,backgroundSwing,dropout;
    BOOL hotPixels,saturatedStars;
};
static void BuildSimulatorFrameProfile(int purpose,SimulatorFrameProfile* p){
    p->starCount=48;p->noiseScale=1.0;p->tiltX=g_simTiltX;p->tiltY=g_simTiltY;p->defocusOffset=0.0;p->seeingBias=0.0;p->seeingSwing=1.0;p->transparencyBase=0.94;p->transparencySwing=0.06;p->elongation=0.0;p->backgroundSwing=10.0;p->dropout=0.0;p->hotPixels=TRUE;p->saturatedStars=FALSE;
    switch(g_simActiveProfile){
        case SIM_FEW_STARS:p->starCount=9;p->noiseScale=1.15;p->transparencyBase=0.86;p->transparencySwing=0.05;break;
        case SIM_DEFOCUSED:p->starCount=42;p->noiseScale=1.10;p->defocusOffset=780.0;p->seeingBias=0.05;break;
        case SIM_POOR_SEEING:p->starCount=45;p->noiseScale=1.35;p->seeingBias=0.28;p->seeingSwing=1.35;p->transparencyBase=0.88;break;
        case SIM_VARIABLE_SEEING:p->starCount=46;p->noiseScale=1.30;p->seeingBias=0.18;p->seeingSwing=4.20;p->transparencyBase=0.90;p->transparencySwing=0.08;break;
        case SIM_THIN_CLOUDS:p->starCount=52;p->noiseScale=1.65;p->seeingBias=0.08;p->seeingSwing=1.60;p->transparencyBase=0.58;p->transparencySwing=0.34;p->backgroundSwing=65.0;p->dropout=0.30;break;
        case SIM_ELONGATED:p->starCount=48;p->noiseScale=1.15;p->elongation=0.48;p->tiltX=0.20;p->tiltY=-0.12;break;
        case SIM_DIFFICULT:p->starCount=18;p->noiseScale=2.25;p->defocusOffset=520.0;p->seeingBias=0.24;p->seeingSwing=3.40;p->transparencyBase=0.62;p->transparencySwing=0.28;p->backgroundSwing=55.0;p->dropout=0.22;break;
        default:break;
    }
    if(g_simStarCount>=0&&g_simStarCount!=48&&g_simActiveProfile==SIM_NORMAL)p->starCount=g_simStarCount;
    if(purpose==5){
        // Backlash is measured from optical changes caused by the motor only. Freeze the
        // synthetic atmosphere and provide a sufficiently rich, unclipped reference field so
        // that seeing/noise or an intentionally defocused stream profile cannot cause a false
        // zero reading or hide the first real optical movement.
        if(p->starCount<32)p->starCount=32;p->noiseScale=ClampD(p->noiseScale,0.7,1.15);p->defocusOffset=0.0;p->seeingBias=0.0;p->seeingSwing=0.0;p->transparencyBase=0.96;p->transparencySwing=0.0;p->elongation=0.0;p->backgroundSwing=0.0;p->dropout=0.0;
    }
}
static void AddSyntheticStar(int cx,int cy,double sigmaX,double sigmaY,UINT amp,BOOL saturated){
    int rx=ClampI((int)(sigmaX*5.0+3.0),5,22),ry=ClampI((int)(sigmaY*5.0+3.0),5,22);
    for(int dy=-ry;dy<=ry;dy++)for(int dx=-rx;dx<=rx;dx++){
        int x=cx+dx,y=cy+dy;if(x<0||y<0||x>=g_width||y>=g_height)continue;
        double r2=(dx*dx)/(2.0*sigmaX*sigmaX)+(dy*dy)/(2.0*sigmaY*sigmaY);double val=(double)amp/((1.0+r2)*(1.0+r2)*(1.0+r2));
        UINT* q=&g_raw[(SIZE_T)y*g_width+x];UINT nv=*q+(UINT)val;if(saturated&&dx*dx+dy*dy<=1)nv=4095;if(nv>4095)nv=4095;*q=nv;
    }
}
static void AddSyntheticBahtinov(int cx,int cy,double offset){
    const double pi=3.14159265358979323846;double angles[3]={25.0,90.0,155.0};
    for(int a=0;a<3;a++){double th=angles[a]*pi/180.0,cs=cos(th),sn=sin(th);double off=a==1?offset:0.0;for(int t=-55;t<=55;t++)for(int w=-2;w<=2;w++){int x=(int)(cx+t*cs-(w+off)*sn+0.5),y=(int)(cy+t*sn+(w+off)*cs+0.5);if(x<1||y<1||x>=g_width-1||y>=g_height-1)continue;UINT add=(UINT)(1100/(1+w*w));UINT* q=&g_raw[(SIZE_T)y*g_width+x];UINT nv=*q+add;if(nv>4095)nv=4095;*q=nv;}}
}
static BOOL GenerateSyntheticFrameAdvanced(int focusPosition,double noiseScale,double tiltX,double tiltY,int starCount,BOOL hotPixels,BOOL saturatedStars,BOOL bahtinov,double defocusOffset,double seeingBias,double seeingSwing,double transparencyBase,double transparencySwing,double elongation,double backgroundSwing,double dropout,BOOL stableAtmosphere){
    int w=960,h=540;if(!EnsureImage(w,h))return FALSE;
    unsigned frameKey=g_simDeterministicTest?0U:g_simFrameSequence;
    unsigned renderKey=stableAtmosphere?0U:frameKey;
    unsigned atmosphereKey=renderKey;
    double seeing=g_simDeterministicTest?0.0:(seeingBias+seeingSwing*(0.045*sin((double)atmosphereKey*0.71)+0.018*sin((double)atmosphereKey*1.93)));
    seeing=ClampD(seeing,-0.08,0.78);
    double transparency=g_simDeterministicTest?1.0:(transparencyBase+transparencySwing*sin((double)atmosphereKey*0.37+0.8));
    transparency=ClampD(transparency,0.14,1.08);
    double bgValue=220.0+(g_simDeterministicTest?0.0:backgroundSwing*sin((double)atmosphereKey*0.29));if(bgValue<80.0)bgValue=80.0;if(bgValue>900.0)bgValue=900.0;UINT bg=(UINT)bgValue;
    unsigned seed=(unsigned)(focusPosition*31+starCount*101+(int)(noiseScale*100))^(renderKey*2654435761U);
    int noiseAmp=ClampI((int)(28.0*noiseScale),3,220);for(int y=0;y<h;y++)for(int x=0;x<w;x++){unsigned r=SimHash((unsigned)(x+y*w)^seed);int n=(int)(r%(unsigned)(noiseAmp+1));g_raw[(SIZE_T)y*w+x]=bg+(UINT)n;}
    if(starCount<0)starCount=0;if(starCount>90)starCount=90;double d=(double)focusPosition+defocusOffset-(double)g_simBestFocus;double baseSigma=(1.30+0.0000085*d*d)*(1.0+seeing);
    unsigned catalogSeed=0xA5F0310DU^(unsigned)starCount*101U;for(int k=0;k<starCount;k++){unsigned base=SimHash(catalogSeed+(unsigned)k*7919U);if(!g_simDeterministicTest&&dropout>0.0){unsigned visibility=SimHash(base^renderKey^0x61C88647U);double u=(double)(visibility%10000U)/10000.0;if(u<dropout*(1.08-transparency))continue;}int cx=36+(int)(base%(unsigned)(w-72));base=SimHash(base+17);int cy=36+(int)(base%(unsigned)(h-72));double nx=((double)cx/(double)w-0.5)*2.0,ny=((double)cy/(double)h-0.5)*2.0;double local=baseSigma+tiltX*nx+tiltY*ny;if(local<1.05)local=1.05;if(local>8.2)local=8.2;double ell=1.0+elongation+((k%13==0)?0.18:0.0);if(ell>1.85)ell=1.85;UINT amp=(UINT)((1700+(k%11)*170)*transparency);BOOL sat=saturatedStars&&k<4;AddSyntheticStar(cx,cy,local*ell,local,amp,sat);}
    if(hotPixels){for(int i=0;i<18;i++){unsigned r=SimHash(0xD00DFEEDU+(unsigned)i*37U);int x=15+(int)(r%(unsigned)(w-30));r=SimHash(r);int y=15+(int)(r%(unsigned)(h-30));g_raw[(SIZE_T)y*w+x]=4095;}}
    if(bahtinov){int cx=w/2,cy=h/2;AddSyntheticStar(cx,cy,1.4,1.4,2800,FALSE);AddSyntheticBahtinov(cx,cy,2.0);}
    g_maxAdu=4095;g_frameReady=TRUE;AnalyseImage();BuildDisplay();InvalidateRect(g_main,0,FALSE);return TRUE;
}
static BOOL GenerateSyntheticFrame(int focusPosition,double noiseScale,double tiltX,double tiltY,int starCount,BOOL hotPixels,BOOL saturatedStars,BOOL bahtinov){
    return GenerateSyntheticFrameAdvanced(focusPosition,noiseScale,tiltX,tiltY,starCount,hotPixels,saturatedStars,bahtinov,0.0,0.0,1.0,0.94,0.06,0.0,10.0,0.0,FALSE);
}
static BOOL GenerateSimulatorStreamFrame(int purpose){
    SimulatorFrameProfile p;BuildSimulatorFrameProfile(purpose,&p);
    return GenerateSyntheticFrameAdvanced(g_simOpticalPosition,p.noiseScale,p.tiltX,p.tiltY,p.starCount,p.hotPixels,p.saturatedStars,FALSE,p.defocusOffset,p.seeingBias,p.seeingSwing,p.transparencyBase,p.transparencySwing,p.elongation,p.backgroundSwing,p.dropout,purpose==5);
}
static char g_runtimeOperation[160]="idle";
static void SetRuntimeOperation(const char* operation){int i=0;if(!operation)operation="";for(;operation[i]&&i<159;i++)g_runtimeOperation[i]=operation[i];g_runtimeOperation[i]=0;}
static void AppendRuntimeTrace(const char* stage){
    wchar_t p[700];BuildDataPath(L"RuntimeTrace.log",p,700);
    HANDLE h=CreateFileW(p,GENERIC_WRITE,1,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return;
    SetFilePointer(h,0,0,FILE_END);SYSTEMTIME st;GetLocalTime(&st);char line[420];
    int n=sprintf(line,"%04u-%02u-%02u %02u:%02u:%02u.%03u | %s | operation=%s | sim=%d cam=%d foc=%d live=%d af=%d afState=%d exposing=%d purpose=%d pos=%d optical=%d\r\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,stage?stage:"",g_runtimeOperation,g_simulatorMode,g_cameraConnected,g_focuserConnected,g_live,g_afActive,g_afState,g_exposing,g_capturePurpose,g_simPosition,g_simOpticalPosition);
    if(n>0&&(unsigned)n<sizeof(line))WriteAllHandle(h,line,(DWORD)n);CloseHandle(h);
}
static LONG WINAPI BackendUnhandledException(EXCEPTION_POINTERS_MIN* ep){char stage[320];DWORD code=ep&&ep->ExceptionRecord?ep->ExceptionRecord->ExceptionCode:0;void* address=ep&&ep->ExceptionRecord?ep->ExceptionRecord->ExceptionAddress:0;sprintf(stage,"UNHANDLED EXCEPTION code=0x%08X address=%p operation=%s",(UINT)code,address,g_runtimeOperation);AppendRuntimeTrace(stage);return 1;}
static void InstallBackendCrashHandler(){HMODULE k=GetModuleHandleW(L"kernel32.dll");if(!k)return;PFN_SetUnhandledExceptionFilter_MIN setFilter=(PFN_SetUnhandledExceptionFilter_MIN)GetProcAddress(k,"SetUnhandledExceptionFilter");if(setFilter)setFilter(BackendUnhandledException);}
static void WriteSimulatorStage(const char* stage){
    wchar_t p[700];BuildDataPath(L"SimulatorStage.txt",p,700);WriteTextFile(p,stage?stage:"");AppendRuntimeTrace(stage);
}
static void SetSimulatorMode(BOOL on){
    if(on==g_simulatorMode)return;
    WriteSimulatorStage(on?"01 selecting simulator":"90 disabling simulator");
    if(g_afActive)StopAutofocus(FALSE,L"Backendwechsel · Autofokus abgebrochen");
    if(g_stepAssistActive)StopStepAssistant(FALSE,L"Backendwechsel · Schritt-Assistent abgebrochen");
    if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Backendwechsel · Backlash-Kalibrierung abgebrochen");
    AbortExposure();
    if(on){
        lstrcpyW(g_savedCameraId,g_cameraId);lstrcpyW(g_savedFocuserId,g_focuserId);
        if(g_cameraConnected)DisconnectCamera();
        if(g_focuserConnected)DisconnectFocuser();
        StopLive();
        FreeImage();
        g_simulatorMode=TRUE;g_externalCameraMode=FALSE;g_demo=FALSE;SetChecked(g_demoCheck,FALSE);
        g_simPosition=24540;g_simOpticalPosition=24540;g_simTemperature=12.0;g_simLastDirection=0;g_simBacklashRemaining=0;g_simFrameSequence=0;g_frameSequence=0;g_lastFrameCompleted=0;g_lastCompletedPurpose=0;SelectSimulatorProfile();
        SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,TRUE);SetChecked(g_overlaySat,TRUE);SetChecked(g_zoneCheck,TRUE);g_overlayPreset=3;
        g_cameraConnected=FALSE;g_focuserConnected=FALSE;g_cameraWanted=g_focuserWanted=FALSE;
        lstrcpyW(g_cameraId,L"Synthetische Kamera");lstrcpyW(g_focuserId,L"Synthetischer absoluter Fokussierer");
        SetWindowTextW(g_cameraEdit,g_cameraId);SetWindowTextW(g_focuserEdit,g_focuserId);
        SetWindowTextW(g_cameraConnect,L"Verbinden");SetWindowTextW(g_focuserConnect,L"Verbinden");SetWindowTextW(g_positionText,L"–");
        {wchar_t sm[220];wsprintfW(sm,L"Simulator ausgewählt · Profil: %s · Backlash %d Schritte",g_simProfileName,g_simBacklashSteps);SetStatus(sm);}
        WriteSimulatorStage("02 simulator selected; no frame allocated");
    }else{
        StopLive();FreeImage();g_simulatorMode=FALSE;g_cameraConnected=g_focuserConnected=FALSE;
        lstrcpyW(g_cameraId,g_savedCameraId);lstrcpyW(g_focuserId,g_savedFocuserId);
        SetWindowTextW(g_cameraEdit,g_cameraId);SetWindowTextW(g_focuserEdit,g_focuserId);
        SetWindowTextW(g_cameraConnect,L"Verbinden");SetWindowTextW(g_focuserConnect,L"Verbinden");SetWindowTextW(g_positionText,L"–");
        SetStatus(L"Simulator deaktiviert");WriteSimulatorStage("99 simulator disabled");
    }
}
struct SelfTestResult{const char* name;BOOL passed;char detail[220];};
static void AddSelfTest(SelfTestResult* r,int* n,const char* name,BOOL pass,const char* detail){r[*n].name=name;r[*n].passed=pass;int i=0;for(;detail&&detail[i]&&i<218;i++)r[*n].detail[i]=detail[i];r[*n].detail[i]=0;(*n)++;}
static BOOL SaveCurrentBmpFile(LPCWSTR path){
    if(!g_frameReady||!g_display||g_width<=0||g_height<=0)return FALSE;
    unsigned long long data64=(unsigned long long)(UINT)g_width*(unsigned long long)(UINT)g_height*4ULL,total64=54ULL+data64;
    if(data64>0x7fffffffULL||total64>0x7fffffffULL)return FALSE;
    int dataSize=(int)data64,total=(int)total64;BYTE* b=(BYTE*)Alloc((SIZE_T)total);if(!b)return FALSE;memset(b,0,(SIZE_T)total);
    b[0]='B';b[1]='M';PutLe32(b+2,(UINT)total);PutLe32(b+10,54U);PutLe32(b+14,40U);PutLe32(b+18,(UINT)g_width);PutLe32(b+22,(UINT)(-g_height));PutLe16(b+26,1U);PutLe16(b+28,32U);PutLe32(b+34,(UINT)dataSize);memcpy(b+54,g_display,(SIZE_T)dataSize);
    HANDLE h=CreateFileW(path,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE){Free(b);return FALSE;}BOOL ok=WriteAllHandle(h,(const char*)b,(DWORD)total);CloseHandle(h);Free(b);return ok;
}

static void RunSyntheticSelfTests(){
    SelfTestResult r[36];int rn=0;char d[220];int best=g_simBestFocus;BOOL oldBaht=IsChecked(g_bahtinovCheck);BOOL oldDet=g_simDeterministicTest;BOOL oldSelfTestActive=g_syntheticSelfTestActive;g_syntheticSelfTestActive=TRUE;
    ULONGLONG savedLastAfCompleted=g_lastAfCompleted,savedLastAfErrorTick=g_lastAfErrorTick,savedAutoRetry=g_autoRefocusRetryAfter,savedLastFrameCompleted=g_lastFrameCompleted;
    double savedLastGoodFwhm=g_lastGoodFwhm,savedLastAfTemperature=g_lastAfTemperature;BOOL savedHasLastAfTemperature=g_hasLastAfTemperature,savedAutoReferenceReady=g_autoRefocusReferenceReady,savedAutoPaused=g_autoRefocusPaused,savedAutoStartPending=g_autoStartPending;
    int savedAutoFailureCount=g_autoRefocusFailureCount,savedBadStreak=g_refocusBadFrameStreak,savedSessionAttempts=g_sessionAfAttempts,savedSessionSuccess=g_sessionAfSuccess,savedSessionFailed=g_sessionAfFailed,savedSessionRollbacks=g_sessionAfRollbacks,savedFocusQualityScore=g_focusQualityScore,savedLastPurpose=g_lastCompletedPurpose;unsigned savedFrameSequence=g_frameSequence,savedLastRefocusSequence=g_lastRefocusEvaluatedFrameSequence;
    BOOL savedValidationPassed=g_afValidationPassed,savedRollbackPerformed=g_afRollbackPerformed,savedAfErrorAutomatic=g_lastAfErrorAutomatic,savedAfAutomaticRun=g_afAutomaticRun,savedAfAutomaticRequest=g_afAutomaticRequest;
    int savedTempProfileCount=g_tempProfileCount,savedSessionStartPosition=g_sessionStartPosition,savedSessionLastPosition=g_sessionLastPosition,savedAfStartPosition=g_afStartPosition,savedAfRetryCount=g_afRetryCount,savedLastTempCompTarget=g_lastTempCompTarget;
    double savedTempSlope=g_tempSlope,savedTempIntercept=g_tempIntercept,savedSessionBestFwhm=g_sessionBestFwhm,savedSessionWorstFwhm=g_sessionWorstFwhm,savedSessionStartTemperature=g_sessionStartTemperature,savedSessionLastTemperature=g_sessionLastTemperature,savedBeforeFwhm=g_beforeFwhm,savedBeforeHfr=g_beforeHfr;
    BOOL savedTempFitValid=g_tempFitValid,savedSessionHasTemperature=g_sessionHasTemperature,savedResumeLiveAfterAf=g_resumeLiveAfterAf;
    wchar_t savedValidationState[96],savedValidationReason[320],savedAutoReason[240],savedQualityLabel[80],savedErrorCode[64],savedErrorTitle[160],savedErrorDetail[512];
    CopyWBounded(savedValidationState,96,g_afValidationState);CopyWBounded(savedValidationReason,320,g_afValidationReason);CopyWBounded(savedAutoReason,240,g_lastAutoRefocusReason);CopyWBounded(savedQualityLabel,80,g_focusQualityLabel);CopyWBounded(savedErrorCode,64,g_lastAfErrorCode);CopyWBounded(savedErrorTitle,160,g_lastAfErrorTitle);CopyWBounded(savedErrorDetail,512,g_lastAfErrorDetail);
    double savedTempT[MAX_TEMP_PROFILE];int savedTempP[MAX_TEMP_PROFILE];for(int i=0;i<MAX_TEMP_PROFILE;i++){savedTempT[i]=g_tempProfileT[i];savedTempP[i]=g_tempProfileP[i];}
    int savedAfCount=g_afPointCount,savedAfBest=g_afBestPosition,savedVBest=g_vBestPosition,savedAfStep=g_afStep,savedSelected=g_selectedStar,savedSeq=g_simFrameSequence,savedAfRecenter=g_afRecenterCount,savedAfExpansion=g_afExpansionCount,savedSimStarCount=g_simStarCount,savedSelectedMisses=g_selectedStarMisses,savedSimProfileMode=g_simProfileMode,savedSimActiveProfile=g_simActiveProfile,savedSimBacklashConfig=g_simBacklashSteps,savedSimPosition=g_simPosition,savedSimOpticalPosition=g_simOpticalPosition,savedSimLastDirection=g_simLastDirection,savedSimBacklashRemaining=g_simBacklashRemaining;unsigned savedSimProfileSelectionSequence=g_simProfileSelectionSequence;wchar_t savedSimProfileName[96];CopyWBounded(savedSimProfileName,96,g_simProfileName);
    BOOL savedManualLocked=g_manualStarLocked,savedAfUseSelected=g_afUseSelectedStar,savedAfRunSelected=g_afRunUsesSelectedStar;double savedTargetNx=g_selectedTargetNx,savedTargetNy=g_selectedTargetNy;
    int savedAfPositions[MAX_AF_POINTS],savedAfUsed[MAX_AF_POINTS];double savedAfMetrics[MAX_AF_POINTS],savedAfFwhm[MAX_AF_POINTS];
    for(int i=0;i<MAX_AF_POINTS;i++){savedAfPositions[i]=g_afPositions[i];savedAfUsed[i]=g_afUsedMetrics[i];savedAfMetrics[i]=g_afMetrics[i];savedAfFwhm[i]=g_afFwhmMetrics[i];}
    double savedFitA=g_fitA,savedFitB=g_fitB,savedFitC=g_fitC,savedFitR2=g_fitR2,savedFitConfidence=g_fitConfidence;
    double savedFitFwhmA=g_fitFwhmA,savedFitFwhmB=g_fitFwhmB,savedFitFwhmC=g_fitFwhmC,savedFitFwhmR2=g_fitFwhmR2,savedFitCenter=g_fitCenterPosition,savedFitScale=g_fitScale;
    double savedExpectedHfr=g_afExpectedHfr,savedExpectedFwhm=g_afExpectedFwhm,savedFinalHfr=g_afFinalHfr,savedFinalFwhm=g_afFinalFwhm;
    int savedFinalPosition=g_afFinalPosition,savedVerificationCount=g_afVerificationCount,savedVerificationTarget=g_afVerificationTarget,savedVerificationRetry=g_afVerificationRetryCount;
    BOOL savedFitValid=g_fitValid,savedFitFwhmValid=g_fitFwhmValid,savedFinalValid=g_afFinalValid;wchar_t savedFitMethod[128];CopyWBounded(savedFitMethod,128,g_fitMethod);
    g_simDeterministicTest=TRUE;SetChecked(g_bahtinovCheck,FALSE);
    GenerateSyntheticFrame(best,1.0,0,0,48,TRUE,FALSE,FALSE);double sharpF=g_medianFwhm,sharpH=g_medianHfr;int sharpStars=g_usedCount;sprintf(d,"%d verwendete Sterne, FWHM %.3f px, HFR %.3f px",sharpStars,sharpF,sharpH);AddSelfTest(r,&rn,"Sternanalyse im Fokus",sharpStars>=20&&sharpF>1.4&&sharpF<5.5,d);
    wchar_t testDir[650];BuildDataPath(L"SyntheticTests",testDir,650);CreateDirectoryW(testDir,0);wchar_t img[700];lstrcpyW(img,testDir);lstrcatW(img,L"\\01_in_focus.bmp");SaveCurrentBmpFile(img);
    int zoneSum=0;BOOL overlayMeta=g_starCount>0;for(int z=0;z<9;z++)zoneSum+=g_zoneCount[z];for(int i=0;i<g_starCount;i++)if(g_stars[i].x<0||g_stars[i].x>=g_width||g_stars[i].y<0||g_stars[i].y>=g_height||g_stars[i].fwhm<=0)overlayMeta=FALSE;sprintf(d,"%d Sterne, %d verwendete Zonensterne",g_starCount,zoneSum);AddSelfTest(r,&rn,"Overlay-Metadaten",overlayMeta&&zoneSum==g_usedCount,d);
    g_simDeterministicTest=FALSE;g_simFrameSequence=101;GenerateSyntheticFrame(best,1.0,0,0,48,TRUE,FALSE,FALSE);double dynF=g_medianFwhm,dynS=g_medianSnr;UINT dynPixel=g_raw?g_raw[(g_width*g_height)/3]:0;g_simFrameSequence=102;GenerateSyntheticFrame(best,1.0,0,0,48,TRUE,FALSE,FALSE);BOOL dynamic=(g_raw&&g_raw[(g_width*g_height)/3]!=dynPixel)||(fabs(g_medianFwhm-dynF)>1e-6)||(fabs(g_medianSnr-dynS)>1e-6);sprintf(d,"Frame 101/102, FWHM %.3f -> %.3f, SNR %.2f -> %.2f",dynF,g_medianFwhm,dynS,g_medianSnr);AddSelfTest(r,&rn,"Dynamische Simulatorframes",dynamic,d);g_simDeterministicTest=TRUE;
    GenerateSyntheticFrame(best+480,1.0,0,0,48,FALSE,FALSE,FALSE);double blurF=g_medianFwhm;sprintf(d,"Fokus %.3f px, defokussiert %.3f px",sharpF,blurF);AddSelfTest(r,&rn,"Defokus-Reaktion",blurF>sharpF*1.45,d);lstrcpyW(img,testDir);lstrcatW(img,L"\\02_defocused.bmp");SaveCurrentBmpFile(img);
    GenerateSyntheticFrame(best,2.8,0,0,48,TRUE,FALSE,FALSE);sprintf(d,"%d verwendete Sterne bei starkem Rauschen",g_usedCount);AddSelfTest(r,&rn,"Robustheit bei starkem Rauschen",g_usedCount>=10,d);
    GenerateSyntheticFrame(best,1.0,0,0,48,TRUE,TRUE,FALSE);sprintf(d,"%d gesättigt, %d Hotpixel verworfen",g_saturatedCount,g_rejectHot);AddSelfTest(r,&rn,"Sättigungs- und Hotpixel-Erkennung",g_saturatedCount>=2&&g_rejectHot>=5,d);
    GenerateSyntheticFrame(best,1.0,1.10,0.65,60,FALSE,FALSE,FALSE);sprintf(d,"Tilt dx %.3f, dy %.3f, Betrag %.3f",g_tiltDx,g_tiltDy,g_tiltMagnitude);AddSelfTest(r,&rn,"3x3-Bildfeld und Tilt",g_tiltValid&&g_tiltDx>0.18&&g_tiltDy>0.08,d);
    GenerateSyntheticFrame(best,1.0,0,0,3,FALSE,FALSE,FALSE);sprintf(d,"%d verwendete Sterne",g_usedCount);AddSelfTest(r,&rn,"Zu wenige Sterne werden erkannt",g_usedCount<5,d);
    GenerateSyntheticFrame(best+120,1.0,0,0,48,TRUE,FALSE,FALSE);int manualStart=g_selectedStar;double manualX=manualStart>=0?g_stars[manualStart].x:0.0,manualY=manualStart>=0?g_stars[manualStart].y:0.0;BOOL manualPicked=manualStart>=0&&SelectManualStarAt((int)(manualX+0.5),(int)(manualY+0.5));g_simDeterministicTest=FALSE;g_simFrameSequence=501;GenerateSyntheticFrame(best,1.0,0,0,48,TRUE,FALSE,FALSE);double manualDrift=999.0;if(g_selectedStar>=0){double dx=g_stars[g_selectedStar].x-manualX,dy=g_stars[g_selectedStar].y-manualY;manualDrift=sqrt(dx*dx+dy*dy);}sprintf(d,"Auswahl %d, Drift %.3f px, Fehlframes %d",manualPicked,manualDrift,g_selectedStarMisses);AddSelfTest(r,&rn,"Manuelle Fokussternauswahl und Verfolgung",manualPicked&&g_manualStarLocked&&g_selectedStar>=0&&manualDrift<8.0,d);g_simDeterministicTest=TRUE;
    double selectedFocusH=0.0,selectedFocusF=0.0;int selectedUsed=0;BOOL selectedFocusMetric=CurrentAutofocusMetric(TRUE,&selectedFocusH,&selectedFocusF,&selectedUsed);GenerateSyntheticFrame(best+600,1.0,0,0,48,TRUE,FALSE,FALSE);double selectedBlurH=0.0,selectedBlurF=0.0;BOOL selectedBlurMetric=CurrentAutofocusMetric(TRUE,&selectedBlurH,&selectedBlurF,&selectedUsed);sprintf(d,"HFR %.3f -> %.3f, FWHM %.3f -> %.3f",selectedFocusH,selectedBlurH,selectedFocusF,selectedBlurF);AddSelfTest(r,&rn,"Metrik des manuell gewählten Sterns",selectedFocusMetric&&selectedBlurMetric&&selectedBlurH>selectedFocusH*1.6&&selectedBlurF>selectedFocusF*1.4,d);ClearManualStarSelection();
    g_afPointCount=9;g_afStep=120;for(int i=0;i<g_afPointCount;i++){g_afPositions[i]=best+(i-4)*g_afStep;GenerateSyntheticFrame(g_afPositions[i],1.0,0,0,50,FALSE,FALSE,FALSE);g_afMetrics[i]=g_medianHfr;g_afFwhmMetrics[i]=g_medianFwhm;g_afUsedMetrics[i]=g_usedCount;}BOOL fit=FitAutofocus();int diff=g_afBestPosition-best;int err=fit?(diff<0?-diff:diff):99999;sprintf(d,"Soll %d, ermittelt %d, Abweichung %d, R2 %.4f",best,g_afBestPosition,err,g_fitR2);AddSelfTest(r,&rn,"Autofokus Ende-zu-Ende",fit&&err<=90&&g_fitR2>=0.80,d);
    int saveMin=g_safeMinPosition,saveMax=g_safeMaxPosition;g_safeMinPosition=1000;g_safeMaxPosition=5000;BOOL safe=CheckSafeTarget(1000)&&CheckSafeTarget(5000)&&!CheckSafeTarget(999)&&!CheckSafeTarget(5001);AddSelfTest(r,&rn,"Sichere Fokusgrenzen",safe,"Grenzwerte 1000..5000 einschließlich geprüft");g_safeMinPosition=saveMin;g_safeMaxPosition=saveMax;
    int savePos=g_simPosition,saveOpt=g_simOpticalPosition,saveDir=g_simLastDirection,saveBacklash=g_simBacklashSteps,saveBacklashRemaining=g_simBacklashRemaining;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=24540;g_simOpticalPosition=24540;g_simLastDirection=1;g_simBacklashSteps=250;g_simBacklashRemaining=0;BOOL shortReverse=MoveFocuser(24440)&&g_simPosition==24440&&g_simOpticalPosition==24540&&g_simBacklashRemaining==150;BOOL takenUp=MoveFocuser(24000)&&g_simPosition==24000&&g_simOpticalPosition==24250&&g_simBacklashRemaining==0;BOOL followsAfterTakeup=MoveFocuser(23900)&&g_simOpticalPosition==24150;sprintf(d,"Umkehr blockiert=%d, optisch nach Aufnahme=%d, folgt danach=%d",shortReverse,g_simOpticalPosition,followsAfterTakeup);AddSelfTest(r,&rn,"Simulator-Backlash",shortReverse&&takenUp&&followsAfterTakeup,d);g_simPosition=savePos;g_simOpticalPosition=saveOpt;g_simLastDirection=saveDir;g_simBacklashSteps=saveBacklash;g_simBacklashRemaining=saveBacklashRemaining;g_safeMinPosition=saveMin;g_safeMaxPosition=saveMax;
    g_simDeterministicTest=FALSE;g_simActiveProfile=SIM_NORMAL;g_simFrameSequence=701;GenerateSimulatorStreamFrame(1);double profileNormalFwhm=g_medianFwhm;int profileNormalStars=g_usedCount;g_simActiveProfile=SIM_FEW_STARS;g_simFrameSequence=702;GenerateSimulatorStreamFrame(1);int profileFewStars=g_usedCount;g_simActiveProfile=SIM_DEFOCUSED;g_simFrameSequence=703;GenerateSimulatorStreamFrame(1);double profileDefocusedFwhm=g_medianFwhm;sprintf(d,"normal %d Sterne/%.3f px, wenige %d, defokussiert %.3f px",profileNormalStars,profileNormalFwhm,profileFewStars,profileDefocusedFwhm);AddSelfTest(r,&rn,"Simulatorprofile: Sterne und Defokus",profileNormalStars>=20&&profileFewStars<profileNormalStars&&profileDefocusedFwhm>profileNormalFwhm*1.35,d);
    g_simActiveProfile=SIM_VARIABLE_SEEING;g_simFrameSequence=710;GenerateSimulatorStreamFrame(1);double variableA=g_medianFwhm;g_simFrameSequence=713;GenerateSimulatorStreamFrame(1);double variableB=g_medianFwhm;sprintf(d,"FWHM %.3f -> %.3f",variableA,variableB);AddSelfTest(r,&rn,"Simulatorprofil: schwankendes Seeing",fabs(variableA-variableB)>0.08,d);
    g_simActiveProfile=SIM_DIFFICULT;g_simFrameSequence=720;GenerateSimulatorStreamFrame(5);double stableA=g_medianHfr;int stableStarsA=g_usedCount;g_simFrameSequence=721;GenerateSimulatorStreamFrame(5);double stableB=g_medianHfr;int stableStarsB=g_usedCount;sprintf(d,"HFR %.5f/%.5f, Sterne %d/%d",stableA,stableB,stableStarsA,stableStarsB);AddSelfTest(r,&rn,"Backlash-Kalibrierungsstream ist stabil",stableStarsA>=g_refocusMinStars&&stableStarsA==stableStarsB&&fabs(stableA-stableB)<0.0001,d);g_simDeterministicTest=TRUE;
    int saveCount=g_tempProfileCount;double saveSlope=g_tempSlope,saveInt=g_tempIntercept;BOOL saveFit=g_tempFitValid;g_tempProfileCount=0;g_tempFitValid=FALSE;AddTemperaturePoint(5.0,20000);AddTemperaturePoint(10.0,20250);AddTemperaturePoint(15.0,20500);sprintf(d,"ermittelter Koeffizient %.3f Schritte/C",g_tempSlope);AddSelfTest(r,&rn,"Temperatur-Fokusmodell",g_tempFitValid&&fabs(g_tempSlope-50.0)<0.05,d);g_tempProfileCount=saveCount;g_tempSlope=saveSlope;g_tempIntercept=saveInt;g_tempFitValid=saveFit;
    SetChecked(g_bahtinovCheck,TRUE);GenerateSyntheticFrame(best,0.6,0,0,24,FALSE,FALSE,TRUE);ComputeBahtinov(g_width/2,g_height/2);sprintf(d,"gültig %d, Offset %.3f, Konfidenz %.3f",g_bahtinovValid,g_bahtinovOffset,g_bahtinovConfidence);AddSelfTest(r,&rn,"Bahtinov-Auswertung",g_bahtinovValid&&fabs(g_bahtinovOffset)<6.0,d);SetChecked(g_bahtinovCheck,oldBaht);
    BOOL liveFlow=RunSimulatorLiveRegression(d,220);AddSelfTest(r,&rn,"Simulator-Livebild Zustandsmaschine",liveFlow,d);
    BOOL stepFlow=RunStepAssistantRegression(d,220);AddSelfTest(r,&rn,"Schritt-Assistent Zustandsmaschine",stepFlow,d);
    BOOL flow=RunSimulatorWorkflowRegression(d,220);AddSelfTest(r,&rn,"Simulator-Autofokus Zustandsmaschine (Feldmedian)",flow,d);
    BOOL selectedFlow=RunSimulatorSelectedStarRegression(d,220);AddSelfTest(r,&rn,"Simulator-Autofokus Zustandsmaschine (Fokusstern)",selectedFlow,d);
    g_selfTestPassed=g_selfTestFailed=0;g_selfTestTotal=rn;for(int i=0;i<rn;i++)if(r[i].passed)g_selfTestPassed++;else g_selfTestFailed++;sprintf(g_selfTestSummary,"%d von %d bestanden; %d fehlgeschlagen",g_selfTestPassed,g_selfTestTotal,g_selfTestFailed);
    lstrcpyW(g_selfTestHtmlPath,testDir);lstrcatW(g_selfTestHtmlPath,L"\\TestReport.html");lstrcpyW(g_selfTestJsonPath,testDir);lstrcatW(g_selfTestJsonPath,L"\\TestResults.json");
    char* html=(char*)Alloc(65536);char* json=(char*)Alloc(32768);if(html&&json){int hn=0,jn=0;hn+=sprintf(html+hn,"<!doctype html><html lang='de'><meta charset='utf-8'><title>Synthetischer Testbericht</title><style>body{font:15px Segoe UI;background:#08111d;color:#eef4ff;max-width:1000px;margin:40px auto}h1{color:#77baff}.ok{color:#66dda3}.bad{color:#ff6b77}table{width:100%%;border-collapse:collapse;background:#101c2b}td,th{border:1px solid #263a55;padding:10px;text-align:left}</style><h1>AstroFocus Studio 3.9.0 Engine</h1><p>%s</p><table><tr><th>Test</th><th>Ergebnis</th><th>Details</th></tr>",g_selfTestSummary);jn+=sprintf(json+jn,"{\"version\":\"3.9.0\",\"passed\":%d,\"failed\":%d,\"total\":%d,\"tests\":[",g_selfTestPassed,g_selfTestFailed,g_selfTestTotal);for(int i=0;i<rn;i++){hn+=sprintf(html+hn,"<tr><td>%s</td><td class='%s'>%s</td><td>%s</td></tr>",r[i].name,r[i].passed?"ok":"bad",r[i].passed?"BESTANDEN":"FEHLGESCHLAGEN",r[i].detail);jn+=sprintf(json+jn,"%s{\"name\":\"%s\",\"passed\":%s,\"detail\":\"%s\"}",i?",":"",r[i].name,r[i].passed?"true":"false",r[i].detail);}sprintf(html+hn,"</table><p>Die Tests prüfen Sternanalyse, dynamische Frames, Overlaydaten, Tilt, Kurvenfit, Grenzen, Backlash, Livebild, Schritt-Assistent, Temperaturmodell und die produktive Autofokus-Zustandsmaschine. ToupTek, ASCOM und reale Mechanik sind nicht enthalten.</p></html>");sprintf(json+jn,"]}");WriteTextFile(g_selfTestHtmlPath,html);WriteTextFile(g_selfTestJsonPath,json);}Free(html);Free(json);
    g_afPointCount=savedAfCount;g_afBestPosition=savedAfBest;g_vBestPosition=savedVBest;g_afStep=savedAfStep;for(int i=0;i<MAX_AF_POINTS;i++){g_afPositions[i]=savedAfPositions[i];g_afUsedMetrics[i]=savedAfUsed[i];g_afMetrics[i]=savedAfMetrics[i];g_afFwhmMetrics[i]=savedAfFwhm[i];}
    g_fitA=savedFitA;g_fitB=savedFitB;g_fitC=savedFitC;g_fitR2=savedFitR2;g_fitConfidence=savedFitConfidence;g_fitValid=savedFitValid;
    g_fitFwhmA=savedFitFwhmA;g_fitFwhmB=savedFitFwhmB;g_fitFwhmC=savedFitFwhmC;g_fitFwhmR2=savedFitFwhmR2;g_fitFwhmValid=savedFitFwhmValid;g_fitCenterPosition=savedFitCenter;g_fitScale=savedFitScale;
    g_afExpectedHfr=savedExpectedHfr;g_afExpectedFwhm=savedExpectedFwhm;g_afFinalValid=savedFinalValid;g_afFinalHfr=savedFinalHfr;g_afFinalFwhm=savedFinalFwhm;g_afFinalPosition=savedFinalPosition;g_afVerificationCount=savedVerificationCount;g_afVerificationTarget=savedVerificationTarget;g_afVerificationRetryCount=savedVerificationRetry;
    CopyWBounded(g_fitMethod,128,savedFitMethod);g_simFrameSequence=savedSeq;g_simDeterministicTest=oldDet;g_afRecenterCount=savedAfRecenter;g_afExpansionCount=savedAfExpansion;g_simStarCount=savedSimStarCount;g_simProfileMode=savedSimProfileMode;g_simActiveProfile=savedSimActiveProfile;g_simBacklashSteps=savedSimBacklashConfig;g_simPosition=savedSimPosition;g_simOpticalPosition=savedSimOpticalPosition;g_simLastDirection=savedSimLastDirection;g_simBacklashRemaining=savedSimBacklashRemaining;g_simProfileSelectionSequence=savedSimProfileSelectionSequence;CopyWBounded(g_simProfileName,96,savedSimProfileName);
    g_manualStarLocked=savedManualLocked;g_afUseSelectedStar=savedAfUseSelected;g_afRunUsesSelectedStar=savedAfRunSelected;g_selectedTargetNx=savedTargetNx;g_selectedTargetNy=savedTargetNy;g_selectedStarMisses=savedSelectedMisses;GenerateSimulatorStreamFrame(1);if(!savedManualLocked&&savedSelected>=0&&savedSelected<g_starCount)g_selectedStar=savedSelected;
    for(int i=0;i<MAX_TEMP_PROFILE;i++){g_tempProfileT[i]=savedTempT[i];g_tempProfileP[i]=savedTempP[i];}g_tempProfileCount=savedTempProfileCount;g_tempSlope=savedTempSlope;g_tempIntercept=savedTempIntercept;g_tempFitValid=savedTempFitValid;
    g_lastAfCompleted=savedLastAfCompleted;g_lastGoodFwhm=savedLastGoodFwhm;g_lastAfTemperature=savedLastAfTemperature;g_hasLastAfTemperature=savedHasLastAfTemperature;g_autoRefocusReferenceReady=savedAutoReferenceReady;g_autoRefocusPaused=savedAutoPaused;g_autoRefocusRetryAfter=savedAutoRetry;g_autoRefocusFailureCount=savedAutoFailureCount;g_refocusBadFrameStreak=savedBadStreak;g_autoStartPending=savedAutoStartPending;g_lastRefocusEvaluatedFrameSequence=savedLastRefocusSequence;
    g_sessionBestFwhm=savedSessionBestFwhm;g_sessionWorstFwhm=savedSessionWorstFwhm;g_sessionStartPosition=savedSessionStartPosition;g_sessionLastPosition=savedSessionLastPosition;g_sessionStartTemperature=savedSessionStartTemperature;g_sessionLastTemperature=savedSessionLastTemperature;g_sessionHasTemperature=savedSessionHasTemperature;
    g_afStartPosition=savedAfStartPosition;g_afRetryCount=savedAfRetryCount;g_beforeFwhm=savedBeforeFwhm;g_beforeHfr=savedBeforeHfr;g_resumeLiveAfterAf=savedResumeLiveAfterAf;g_lastTempCompTarget=savedLastTempCompTarget;
    g_sessionAfAttempts=savedSessionAttempts;g_sessionAfSuccess=savedSessionSuccess;g_sessionAfFailed=savedSessionFailed;g_sessionAfRollbacks=savedSessionRollbacks;g_focusQualityScore=savedFocusQualityScore;CopyWBounded(g_focusQualityLabel,80,savedQualityLabel);g_afValidationPassed=savedValidationPassed;g_afRollbackPerformed=savedRollbackPerformed;CopyWBounded(g_afValidationState,96,savedValidationState);CopyWBounded(g_afValidationReason,320,savedValidationReason);CopyWBounded(g_lastAutoRefocusReason,240,savedAutoReason);
    CopyWBounded(g_lastAfErrorCode,64,savedErrorCode);CopyWBounded(g_lastAfErrorTitle,160,savedErrorTitle);CopyWBounded(g_lastAfErrorDetail,512,savedErrorDetail);g_lastAfErrorAutomatic=savedAfErrorAutomatic;g_lastAfErrorTick=savedLastAfErrorTick;g_afAutomaticRun=savedAfAutomaticRun;g_afAutomaticRequest=savedAfAutomaticRequest;g_frameSequence=savedFrameSequence;g_lastFrameCompleted=savedLastFrameCompleted;g_lastCompletedPurpose=savedLastPurpose;g_syntheticSelfTestActive=oldSelfTestActive;
    SetStatus(g_selfTestFailed?L"Synthetische Tests beendet · Fehler im Bericht":L"Synthetische Tests vollständig bestanden");
}

static double CurrentExposureSeconds(){wchar_t v[64];GetWindowTextW(g_exposureEdit,v,64);double ms=1000.0;if(!ParseStrictDoubleW(v,&ms))ms=1000.0;if(ms<1.0)ms=1.0;if(ms>60000.0)ms=60000.0;return ms/1000.0;}
static void ApplyGain(){wchar_t v[64];GetWindowTextW(g_gainEdit,v,64);UINT gainValue=100;if(!ParseStrictUIntW(v,&gainValue)||gainValue>65535U)gainValue=100;LONG gain=(LONG)gainValue;if(g_nativeActive&&g_tcam&&pToupcam_put_ExpoAGain){if(gain<100)gain=100;if(gain>5000)gain=5000;pToupcam_put_ExpoAGain(g_tcam,(unsigned short)gain);return;}if(g_cameraConnected&&g_cameraWorker)WorkerSetInt(g_cameraWorker,L"Gain",gain,2500);}
static BOOL StartExposure(int purpose){
    if(g_exposing)return FALSE;g_capturePurpose=purpose;g_lastExposureSeconds=CurrentExposureSeconds();
    if(g_demo){g_exposing=TRUE;g_exposureStarted=GetTickCount64();return TRUE;}
    if(g_simulatorMode||g_externalCameraMode){if(!g_cameraConnected){g_capturePurpose=0;return FALSE;}g_exposing=TRUE;g_exposureStarted=GetTickCount64();return TRUE;}
    if(!g_cameraConnected){g_capturePurpose=0;return FALSE;}ApplyGain();if(g_nativeActive){
        if(!g_tcam||!pToupcam_put_ExpoTime||FAILED(pToupcam_put_ExpoTime(g_tcam,(unsigned)(g_lastExposureSeconds*1000000.0)))){
            g_capturePurpose=0;UnloadToupTek();MarkCameraDisconnected(L"Native Kamera konnte die Belichtungszeit nicht übernehmen · sichere Wiederverbindung wird versucht");return FALSE;
        }
        g_exposing=TRUE;g_exposureStarted=GetTickCount64();return TRUE;
    }
    if(!WorkerStartExposure(g_cameraWorker,g_lastExposureSeconds,TRUE,5000)){ApplyDeviceWorkerFaults();if(g_cameraWorker)ShowComError(L"Das Starten der Belichtung",g_cameraWorker->hr);g_capturePurpose=0;return FALSE;}g_exposing=TRUE;g_exposureStarted=GetTickCount64();return TRUE;
}
static void AbortExposure(){
    if(!g_exposing){g_capturePurpose=0;return;}
    if(!g_demo&&!g_simulatorMode&&!g_externalCameraMode&&!g_nativeActive&&g_cameraConnected&&g_cameraWorker){
        DeviceWorker* w=g_cameraWorker;BOOL canAbort=FALSE;
        if(!WorkerGetBool(w,L"CanAbortExposure",FALSE,&canAbort,1500)){
            ApplyDeviceWorkerFaults();g_exposing=FALSE;g_capturePurpose=0;
            if(g_cameraWorker==w&&w)DestroyDeviceWorker(&g_cameraWorker,TRUE);
            g_cameraWorkerRecoveryAttempt++;g_cameraWorkerRetryAfter=GetTickCount64()+DeviceRecoveryDelayMs(g_cameraWorkerRecoveryAttempt);
            MarkCameraDisconnected(L"Kameraantwort beim Abbruch fehlgeschlagen · Gerätehost wurde sicher isoliert");return;
        }
        if(canAbort){
            if(!WorkerCallNoArgs(w,L"AbortExposure",3000)){
                ApplyDeviceWorkerFaults();g_exposing=FALSE;g_capturePurpose=0;
                if(g_cameraWorker==w&&w)DestroyDeviceWorker(&g_cameraWorker,TRUE);
                g_cameraWorkerRecoveryAttempt++;g_cameraWorkerRetryAfter=GetTickCount64()+DeviceRecoveryDelayMs(g_cameraWorkerRecoveryAttempt);
                MarkCameraDisconnected(L"Kamerabelichtung ließ sich nicht sicher abbrechen · Gerätehost wurde neu gestartet");return;
            }
        }else{
            g_capturePurpose=0;SetStatus(L"Kamera unterstützt keinen Belichtungsabbruch · laufendes Bild wird verworfen");return;
        }
    }
    g_exposing=FALSE;g_capturePurpose=0;
}

static BOOL StartLiveExposureOrStop(LPCWSTR failureStatus){if(StartExposure(1))return TRUE;g_live=FALSE;SetWindowTextW(g_liveButton,L"Live-Fokus starten");SetStatus(failureStatus);return FALSE;}
static void StartLive(){
    if(g_live){StopLive();return;}g_demo=IsChecked(g_demoCheck);if(!g_demo&&!g_cameraConnected){NotifyUser(L"Bitte zuerst die Kamera verbinden oder den Demo-Modus aktivieren.",L"Keine Kamera",MB_OK|MB_ICONINFORMATION);return;}if(g_afActive||g_stepAssistActive||g_backlashCalActive){SetStatus(L"Live-Fokus kann während Autofokus, Schritt-Assistent oder Backlash-Kalibrierung nicht gestartet werden");return;}g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");if(g_simulatorMode)WriteSimulatorStage("25 simulator live started");SetStatus(g_simulatorMode?L"Simulator-Live-Fokus aktiv":(g_externalCameraMode?L"USB/UVC-Live-Fokus aktiv":(g_demo?L"Demo-Live-Fokus aktiv":L"Live-Fokus aktiv")));StartLiveExposureOrStop(L"Live-Fokus konnte keine Belichtung starten");
}
static void StopLive(){g_live=FALSE;SetWindowTextW(g_liveButton,L"Live-Fokus starten");if(g_capturePurpose==1)AbortExposure();}

static int FocuserMaxStep(){
    if(g_simulatorMode)return g_simMaxStep;
    return g_focuserConnected?(g_cachedFocuserMaxStep>0?g_cachedFocuserMaxStep:200000):200000;
}
static int FocuserPosition(){
    if(g_simulatorMode)return g_focuserConnected?g_simPosition:-1;
    return g_focuserConnected?g_cachedFocuserPosition:-1;
}
static BOOL FocuserMoving(){
    if(g_simulatorMode)return FALSE;
    return g_focuserConnected?g_cachedFocuserMoving:FALSE;
}
static DWORD FocuserMovementDeadlineMs(int current,int target){long long distance=(long long)target-(long long)current;if(distance<0)distance=-distance;unsigned long long ms=8000ULL+(unsigned long long)distance*20ULL;if(ms<12000ULL)ms=12000ULL;if(ms>300000ULL)ms=300000ULL;return (DWORD)ms;}
static BOOL MoveFocuser(int target){if(g_focuserSetupReserved){SetStatus(L"Fokusbewegung während des ASCOM-Treiberdialogs gesperrt");return FALSE;}
    if(g_simulatorMode){
        if(!g_focuserConnected){SetStatus(L"Simulator: Fokussierer nicht verbunden");return FALSE;}
        target=ClampI(target,0,g_simMaxStep);
        if(!CheckSafeTarget(target)){SetStatus(L"Simulator: Bewegung außerhalb der sicheren Fokuszone blockiert");return FALSE;}
        int oldCommand=g_simPosition;
        if(g_faultFocuserStall){g_cachedFocuserMoving=TRUE;g_moveStartedTick=GetTickCount64();g_moveDeadlineTick=g_moveStartedTick+1500ULL;g_moveStartPosition=oldCommand;SetStatus(L"Fehlerprovokation: synthetischer Fokussierer blockiert");return TRUE;}
        int dir=target>oldCommand?1:(target<oldCommand?-1:0);
        int distance=target-oldCommand;if(distance<0)distance=-distance;
        if(dir){
            if(!g_simLastDirection)g_simBacklashRemaining=0;
            else if(dir!=g_simLastDirection)g_simBacklashRemaining=g_simBacklashSteps;
            int remainingBefore=g_simBacklashRemaining;int consumed=distance<remainingBefore?distance:remainingBefore;int effective=distance-consumed;g_simBacklashRemaining=remainingBefore-consumed;
            if(effective>0){long long optical=(long long)g_simOpticalPosition+(long long)dir*(long long)effective;if(optical<0)optical=0;if(optical>g_simMaxStep)optical=g_simMaxStep;g_simOpticalPosition=(int)optical;}
            g_simLastDirection=dir;
        }
        g_simPosition=target;g_moveStartedTick=GetTickCount64();g_moveDeadlineTick=g_moveStartedTick+FocuserMovementDeadlineMs(oldCommand,target);g_moveStartPosition=oldCommand;
        wchar_t p[32];wsprintfW(p,L"%d",g_simPosition);SetWindowTextW(g_positionText,p);g_moveDeadlineTick=0;return TRUE;
    }
    if(!g_focuserConnected||!g_focuserWorker)return FALSE;if(!g_focuserRuntime.positionKnown||g_cachedFocuserPosition<0){DeviceRuntimeSetPhase(FALSE,DEV_POSITION_UNKNOWN,L"move blocked: position unknown",(HRESULT)0x80004005L,TRUE);SetStatus(L"Fokusposition ist unbekannt · automatische Bewegung bis zur Wiederverbindung gesperrt");return FALSE;}
    int current=g_cachedFocuserPosition,maxStep=FocuserMaxStep();target=ClampI(target,0,maxStep);if(!CheckSafeTarget(target)){SetStatus(L"Bewegung außerhalb der sicheren Fokuszone blockiert");return FALSE;}DWORD movementDeadline=FocuserMovementDeadlineMs(current,target),commandTimeout=movementDeadline;if(commandTimeout<5000)commandTimeout=5000;if(commandTimeout>30000)commandTimeout=30000;if(!WorkerCallInt(g_focuserWorker,L"Move",target,commandTimeout)){ApplyDeviceWorkerFaults();if(g_focuserWorker)ShowComError(L"Die Fokusbewegung",g_focuserWorker->hr);g_focuserRuntime.positionKnown=FALSE;g_focuserRuntime.phase=DEV_POSITION_UNKNOWN;return FALSE;}g_cachedFocuserMoving=TRUE;g_moveStartPosition=current;g_moveStartedTick=GetTickCount64();g_moveDeadlineTick=g_moveStartedTick+movementDeadline;return TRUE;
}
static BOOL ManualMove(int direction){if(g_continuousFocusPhase==CF_MOVING||g_continuousFocusPhase==CF_SETTLING){SetStatus(L"Manuelle Bewegung während einer Nachführungskorrektur gesperrt");return FALSE;}if(g_continuousFocusPhase==CF_VERIFYING)ContinuousFocusResetReference(L"Manuelle Fokusbewegung hat die Kontrollmessung zurückgesetzt");if(g_focuserSetupReserved){SetStatus(L"Fokusbewegung während des ASCOM-Treiberdialogs gesperrt");return FALSE;}
    if(!g_focuserConnected){NotifyUser(L"Bitte zuerst einen Fokussierer verbinden.",L"Fokussierer nicht verbunden",MB_OK|MB_ICONINFORMATION);return FALSE;}if(g_afActive||g_stepAssistActive||g_backlashCalActive){SetStatus(L"Manuelle Fokusbewegung während eines Fokus- oder Kalibrierungslaufs blockiert");return FALSE;}wchar_t v[64];GetWindowTextW(g_manualStepEdit,v,64);UINT stepValue=0;if(!ParseStrictUIntW(v,&stepValue)||stepValue<1U||stepValue>1000000U){SetStatus(L"Ungültige manuelle Schrittweite");return FALSE;}int p=FocuserPosition(),maxStep=FocuserMaxStep();if(p<0){SetStatus(L"Aktuelle Fokusposition konnte nicht gelesen werden");return FALSE;}long long requested=(long long)p+(long long)direction*(long long)stepValue;if(requested<0)requested=0;if(requested>maxStep)requested=maxStep;if(MoveFocuser((int)requested)){g_afFinalValid=FALSE;ContinuousFocusResetReference(L"Manuelle Fokusbewegung · Nachführungsreferenz wird neu aufgebaut");SetStatus(direction<0?L"Fokus nach innen bewegt · Autofokus-Bestätigung verworfen":L"Fokus nach außen bewegt · Autofokus-Bestätigung verworfen");InvalidateRect(g_main,0,FALSE);return TRUE;}return FALSE;
}
static void HaltFocuser(){
    BOOL confirmed=TRUE,moving=FALSE;LONG position=-1;DeviceWorker* w=g_focuserWorker;
    if(g_focuserConnected&&!g_simulatorMode){
        if(!w||!WorkerCallNoArgs(w,L"Halt",3000)){confirmed=FALSE;ApplyDeviceWorkerFaults();}
        else if(!WorkerGetBool(w,L"IsMoving",TRUE,&moving,1800)||!WorkerGetInt(w,L"Position",-1,&position,1800)){confirmed=FALSE;ApplyDeviceWorkerFaults();}
        else if(moving){g_cachedFocuserMoving=TRUE;g_moveDeadlineTick=GetTickCount64()+5000ULL;SetStatus(L"Halt angefordert · Stillstand wird noch überwacht");}
        else{g_cachedFocuserMoving=FALSE;g_cachedFocuserPosition=(int)position;g_focuserRuntime.positionKnown=position>=0;g_moveDeadlineTick=0;}
    }else{g_cachedFocuserMoving=FALSE;g_moveDeadlineTick=0;}
    if(g_afActive)StopAutofocus(FALSE,confirmed?L"Autofokus angehalten":L"Autofokus beendet · Fokussiererstatus unbekannt");
    if(g_stepAssistActive)StopStepAssistant(FALSE,confirmed?L"Schritt-Assistent angehalten":L"Schritt-Assistent beendet · Fokussiererstatus unbekannt");
    if(g_backlashCalActive)StopBacklashCalibration(FALSE,confirmed?L"Backlash-Kalibrierung angehalten":L"Backlash-Kalibrierung beendet · Fokussiererstatus unbekannt");
    if(!confirmed){g_focuserRuntime.positionKnown=FALSE;g_focuserRuntime.phase=DEV_POSITION_UNKNOWN;if(g_focuserWorker==w&&w)DestroyDeviceWorker(&g_focuserWorker,TRUE);g_focuserWorkerRecoveryAttempt++;g_focuserWorkerRetryAfter=GetTickCount64()+DeviceRecoveryDelayMs(g_focuserWorkerRecoveryAttempt);MarkFocuserDisconnected(L"Fokussierer konnte nicht sicher angehalten werden · Position unbekannt");}
    else if(!moving)SetStatus(L"Fokusbewegung angehalten und Position bestätigt");
}

#include "autofocus_statistics.inc"
static void BeginMoveSequence(int target,int continuation){
    WriteSimulatorStage("43 begin move sequence");
    int current=FocuserPosition();g_moveFinalTarget=target;g_moveContinuation=continuation;BOOL preferOut=IsChecked(g_preferredDirCheck);int approach=preferOut?1:-1;
    if(g_afBacklash>0&&((approach>0&&target<current)||(approach<0&&target>current))){int maxStep=FocuserMaxStep();long long preTarget=(long long)target-(long long)approach*(long long)g_afBacklash;if(preTarget<0)preTarget=0;if(preTarget>maxStep)preTarget=maxStep;g_moveTarget=(int)preTarget;if(g_moveTarget!=target&&MoveFocuser(g_moveTarget)){g_afState=10;return;}}
    if(MoveFocuser(target))g_afState=11;else StopAutofocus(TRUE,L"Fokusbewegung fehlgeschlagen");
}
static int ALen(const char* s){int n=0;while(s&&s[n])n++;return n;}
static void WToAscii(LPCWSTR w,char* a,int cap){int i=0;if(cap<=0)return;for(;w&&w[i]&&i<cap-1;i++){wchar_t c=w[i];a[i]=(c>=32&&c<127)?(char)c:'_';}a[i]=0;}
static void CsvSafeAscii(LPCWSTR w,char* out,int cap){
    WToAscii(w,out,cap);for(int i=0;out&&out[i];i++)if(out[i]==';'||out[i]=='\r'||out[i]=='\n')out[i]=' ';
}
static BOOL WriteAllHandle(HANDLE h,const char* data,DWORD length){
    if(h==INVALID_HANDLE_VALUE||(!data&&length))return FALSE;DWORD done=0;
    while(done<length){DWORD written=0;if(!WriteFile(h,data+done,length-done,&written,0)||written==0)return FALSE;done+=written;}
    return TRUE;
}
static void JsonByte(char c,char* out,int* o,int cap){if(*o<cap-1)out[(*o)++]=c;}
static void WToJsonUtf8(LPCWSTR w,char* out,int cap){
    int o=0;if(!out||cap<=0)return;
    for(int i=0;w&&w[i]&&o<cap-1;i++){unsigned cp=(unsigned)w[i];if(cp>=0xd800&&cp<=0xdbff&&w[i+1]>=0xdc00&&w[i+1]<=0xdfff){cp=0x10000+((cp-0xd800)<<10)+((unsigned)w[++i]-0xdc00);}else if(cp>=0xd800&&cp<=0xdfff)cp=0xfffd;
        if(cp=='"'||cp=='\\'){JsonByte('\\',out,&o,cap);JsonByte((char)cp,out,&o,cap);continue;}if(cp<32){JsonByte(' ',out,&o,cap);continue;}
        if(cp<0x80)JsonByte((char)cp,out,&o,cap);else if(cp<0x800){JsonByte((char)(0xc0|(cp>>6)),out,&o,cap);JsonByte((char)(0x80|(cp&63)),out,&o,cap);}else if(cp<0x10000){JsonByte((char)(0xe0|(cp>>12)),out,&o,cap);JsonByte((char)(0x80|((cp>>6)&63)),out,&o,cap);JsonByte((char)(0x80|(cp&63)),out,&o,cap);}else{JsonByte((char)(0xf0|(cp>>18)),out,&o,cap);JsonByte((char)(0x80|((cp>>12)&63)),out,&o,cap);JsonByte((char)(0x80|((cp>>6)&63)),out,&o,cap);JsonByte((char)(0x80|(cp&63)),out,&o,cap);}
    }out[o]=0;
}
static BOOL WriteTextFile(LPCWSTR path,const char* text){HANDLE h=CreateFileW(path,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return FALSE;DWORD length=(DWORD)ALen(text);BOOL ok=WriteAllHandle(h,text,length);CloseHandle(h);return ok;}

// 3.3 named equipment/acquisition profiles. Profiles contain configuration only;
// loading never connects devices, starts an exposure, or moves the focuser.
static void ProfileSetMessage(LPWSTR out,int cap,LPCWSTR text){if(out&&cap>0)CopyWBounded(out,cap,text?text:L"");}
static BOOL ProfileNameValid(LPCWSTR in,LPWSTR normalized,int cap){
    if(!in||!normalized||cap<2)return FALSE;int start=0;while(in[start]==L' '||in[start]==L'\t')start++;int end=start;while(in[end])end++;while(end>start&&(in[end-1]==L' '||in[end-1]==L'\t'))end--;int n=0;
    for(int i=start;i<end&&n<cap-1;i++){wchar_t c=in[i];if(c<32||c==L'<'||c==L'>'||c==L':'||c==L'"'||c==L'/'||c==L'\\'||c==L'|'||c==L'?'||c==L'*')return FALSE;normalized[n++]=c;}
    normalized[n]=0;return n>0&&n<80;
}
static void ProfileDirectory(LPWSTR out,int cap){BuildDataPath(L"Profiles",out,cap);CreateDirectoryW(out,0);}
static void ProfileIndexPath(LPWSTR out,int cap){wchar_t dir[620];ProfileDirectory(dir,620);wsprintfW(out,L"%s\\profiles.ini",dir);if(cap>0)out[cap-1]=0;}
static void ProfileSlotPath(int slot,LPWSTR out,int cap){wchar_t dir[620];ProfileDirectory(dir,620);wsprintfW(out,L"%s\\Profile_%02d.afprofile.json",dir,slot);if(cap>0)out[cap-1]=0;}
static void ProfileSlotKey(int slot,LPWSTR out){wsprintfW(out,L"Slot%02d",slot);}
static void ReadProfileSlotName(int slot,LPWSTR out,int cap){wchar_t index[700],key[32];ProfileIndexPath(index,700);ProfileSlotKey(slot,key);GetPrivateProfileStringW(L"Profiles",key,L"",out,(DWORD)cap,index);}
static BOOL WriteProfileSlotName(int slot,LPCWSTR name){wchar_t index[700],key[32];ProfileIndexPath(index,700);ProfileSlotKey(slot,key);return WritePrivateProfileStringW(L"Profiles",key,name,index);}
static int FindProfileSlot(LPCWSTR name){wchar_t n[96];for(int i=0;i<MAX_NAMED_PROFILES;i++){ReadProfileSlotName(i,n,96);if(n[0]&&WEquals(n,name))return i;}return -1;}
static int FindFreeProfileSlot(){wchar_t n[96];for(int i=1;i<MAX_NAMED_PROFILES;i++){ReadProfileSlotName(i,n,96);if(!n[0])return i;}return -1;}
static BOOL ProfileOperationBusy(){return g_afActive||g_stepAssistActive||g_backlashCalActive||g_exposing||g_live||g_cachedFocuserMoving;}
static BOOL ReadWholeTextFile(LPCWSTR path,char** out,DWORD* sizeOut){
    if(out)*out=0;if(sizeOut)*sizeOut=0;HANDLE h=CreateFileW(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return FALSE;DWORD size=GetFileSize(h,0);if(size==0xffffffffU||size<2U||size>262144U){CloseHandle(h);return FALSE;}char* b=(char*)Alloc((SIZE_T)size+1U);if(!b){CloseHandle(h);return FALSE;}DWORD done=0;while(done<size){DWORD got=0;if(!ReadFile(h,b+done,size-done,&got,0)||got==0){CloseHandle(h);Free(b);return FALSE;}done+=got;}CloseHandle(h);b[size]=0;if(out)*out=b;else Free(b);if(sizeOut)*sizeOut=size;return TRUE;
}
typedef BOOL (WINAPI *PFN_ProfileDeleteFileW)(LPCWSTR);typedef BOOL (WINAPI *PFN_ProfileMoveFileExW)(LPCWSTR,LPCWSTR,DWORD);
static BOOL ProfileDeleteFile(LPCWSTR path){static PFN_ProfileDeleteFileW fn=0;if(!fn){HMODULE k=GetModuleHandleW(L"kernel32.dll");if(k)fn=(PFN_ProfileDeleteFileW)GetProcAddress(k,"DeleteFileW");}return fn?fn(path):FALSE;}
static BOOL ProfileMoveFile(LPCWSTR from,LPCWSTR to,DWORD flags){static PFN_ProfileMoveFileExW fn=0;if(!fn){HMODULE k=GetModuleHandleW(L"kernel32.dll");if(k)fn=(PFN_ProfileMoveFileExW)GetProcAddress(k,"MoveFileExW");}return fn?fn(from,to,flags):FALSE;}
static BOOL WriteTextFileAtomic(LPCWSTR path,const char* text){
    wchar_t tmp[760];CopyWBounded(tmp,760,path);CatWBounded(tmp,760,L".tmp");ProfileDeleteFile(tmp);if(!WriteTextFile(tmp,text)){ProfileDeleteFile(tmp);return FALSE;}if(!ProfileMoveFile(tmp,path,MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)){ProfileDeleteFile(tmp);return FALSE;}return TRUE;
}
static unsigned ProfileHash(const char* text){unsigned h=2166136261U;for(int i=0;text&&text[i];i++){h^=(unsigned char)text[i];h*=16777619U;}return h;}
static BOOL ProfileAppend(char* out,int cap,int* used,const char* text){if(!out||!used||!text)return FALSE;int n=ALen(text);if(*used<0||n<0||*used+n>=cap)return FALSE;memcpy(out+*used,text,(SIZE_T)n);*used+=n;out[*used]=0;return TRUE;}
#ifdef ASTROFOCUS_NATIVE_TEST
extern "C" int vsprintf(char*,const char*,__builtin_va_list);
#endif
typedef int (__cdecl *PFN_ProfileVsprintf)(char*,const char*,__builtin_va_list);
static int ProfileVsprintf(char* out,const char* fmt,__builtin_va_list ap){
#ifdef ASTROFOCUS_NATIVE_TEST
    return vsprintf(out,fmt,ap);
#else
    static PFN_ProfileVsprintf fn=0;static HMODULE mod=0;if(!fn){if(!mod)mod=LoadLibraryW(L"msvcrt.dll");if(mod)fn=(PFN_ProfileVsprintf)GetProcAddress(mod,"vsprintf");}return fn?fn(out,fmt,ap):-1;
#endif
}
static BOOL ProfileAppendFormat(char* out,int cap,int* used,const char* fmt,...){char t[8192];__builtin_va_list ap;__builtin_va_start(ap,fmt);int n=ProfileVsprintf(t,fmt,ap);__builtin_va_end(ap);if(n<0||n>=(int)sizeof(t))return FALSE;return ProfileAppend(out,cap,used,t);}
static void ProfileControlText(HWND h,LPWSTR out,int cap){if(!h||!out||cap<=0){if(out&&cap>0)out[0]=0;return;}GetWindowTextW(h,out,cap);out[cap-1]=0;}
static double ProfileControlDouble(HWND h,double fallback){wchar_t v[80];double d=0.0;ProfileControlText(h,v,80);return ParseStrictDoubleW(v,&d)?d:fallback;}
static int ProfileControlUInt(HWND h,int fallback){wchar_t v[80];UINT u=0;ProfileControlText(h,v,80);return ParseStrictUIntW(v,&u)&&u<=2147483647U?(int)u:fallback;}
static void CaptureProfileSnapshot(ProfileSnapshot* p,LPCWSTR name){
    memset(p,0,sizeof(*p));CopyWBounded(p->name,96,name);CopyWBounded(p->cameraId,256,g_simulatorMode?g_savedCameraId:g_cameraId);CopyWBounded(p->focuserId,256,g_simulatorMode?g_savedFocuserId:g_focuserId);CopyWBounded(p->currentFilter,32,g_currentFilter);
    p->exposureMs=ProfileControlDouble(g_exposureEdit,1000.0);p->gain=ProfileControlUInt(g_gainEdit,180);p->manualStep=ProfileControlUInt(g_manualStepEdit,100);p->afPoints=ProfileControlUInt(g_afPointsEdit,9);p->afStep=ProfileControlUInt(g_afStepEdit,120);p->afBacklash=ProfileControlUInt(g_afBacklashEdit,250);p->afSamples=ProfileControlUInt(g_afSamplesEdit,2);p->safeMin=g_safeMinPosition;p->safeMax=g_safeMaxPosition;
    p->autoStretch=IsChecked(g_autoStretch);p->overlayStars=IsChecked(g_overlayStars);p->overlayLabels=IsChecked(g_overlayLabels);p->overlaySat=IsChecked(g_overlaySat);p->zones=IsChecked(g_zoneCheck);p->bahtinov=IsChecked(g_bahtinovCheck);p->preferredOut=IsChecked(g_preferredDirCheck);p->reconnect=IsChecked(g_reconnectCheck);p->nativeToupTek=IsChecked(g_nativeCheck);
    p->autoRefocus=g_autoRefocusEnabled;p->refocusMinutes=ProfileControlDouble(g_refocusMinutesEdit,60.0);p->refocusTemp=ProfileControlDouble(g_refocusTempEdit,1.5);p->refocusFwhmPercent=g_refocusFwhmThresholdPercent;p->refocusBadFrames=g_refocusBadFramesRequired;p->refocusMinStars=g_refocusMinStars;p->refocusStability=g_refocusStabilityLimit;p->refocusCooldown=g_refocusCooldownMinutes;
    p->tempComp=g_tempCompEnabled;p->autoStartPosition=g_autoStartPositionEnabled;p->tempCompDeadband=g_tempCompDeadbandSteps;p->tempCompMaxStep=g_tempCompMaxStep;p->refocusOnMeridian=g_refocusOnMeridian;p->refocusOnReconnect=g_refocusOnReconnect;p->refocusOnFilter=g_refocusOnFilter;p->refocusEveryCaptures=g_refocusEveryCaptures;
    p->focalLength=ProfileControlDouble(g_focalEdit,2032.0);p->pixelSize=ProfileControlDouble(g_pixelEdit,2.9);p->simulatorProfile=g_simProfileMode;p->simulatorBacklash=g_simBacklashSteps;p->simulatorSeed=g_simRandomSeed?g_simRandomSeed:0xA57F3301U;
    p->modelSuccessfulRuns=g_profileSuccessfulRuns;p->modelTypicalPosition=g_profileTypicalPosition;p->modelRecommendedStep=g_profileRecommendedStep;p->modelBacklash=g_profileBacklash;p->modelTypicalFwhm=g_profileTypicalFwhm;p->modelTypicalHfr=g_profileTypicalHfr;p->modelQualityMean=g_profileQualityMean;
    p->filterReferencePosition=g_filterReferencePosition;p->filterCount=g_filterOffsetCount;if(p->filterCount<0)p->filterCount=0;if(p->filterCount>MAX_FILTER_OFFSETS)p->filterCount=MAX_FILTER_OFFSETS;for(int i=0;i<p->filterCount;i++)p->filters[i]=g_filterOffsets[i];
    p->tempCount=g_tempProfileCount;if(p->tempCount<0)p->tempCount=0;if(p->tempCount>MAX_TEMP_PROFILE)p->tempCount=MAX_TEMP_PROFILE;for(int i=0;i<p->tempCount;i++){p->tempT[i]=g_tempProfileT[i];p->tempP[i]=g_tempProfileP[i];}
}
static BOOL ValidateProfileSnapshot(const ProfileSnapshot* p,LPWSTR error,int cap){
    wchar_t normalized[96];if(!ProfileNameValid(p->name,normalized,96)){ProfileSetMessage(error,cap,L"Profilname ist leer oder enthält unzulässige Zeichen.");return FALSE;}
    if(!FiniteD(p->exposureMs)||p->exposureMs<1.0||p->exposureMs>60000.0||p->gain<0||p->gain>65535||p->manualStep<1||p->manualStep>1000000||p->afPoints<5||p->afPoints>15||(p->afPoints&1)==0||p->afStep<5||p->afStep>1000000||p->afBacklash<0||p->afBacklash>1000000||p->afSamples<1||p->afSamples>5){ProfileSetMessage(error,cap,L"Aufnahme- oder Autofokusparameter des Profils liegen außerhalb der zulässigen Grenzen.");return FALSE;}
    if(p->safeMin<0||p->safeMax<=p->safeMin||p->safeMax>2000000000){ProfileSetMessage(error,cap,L"Die sichere Fokuszone des Profils ist ungültig.");return FALSE;}
    if(!FiniteD(p->refocusMinutes)||p->refocusMinutes<0||p->refocusMinutes>100000||!FiniteD(p->refocusTemp)||p->refocusTemp<0||p->refocusTemp>100||!FiniteD(p->refocusFwhmPercent)||p->refocusFwhmPercent<0||p->refocusFwhmPercent>500||p->refocusBadFrames<1||p->refocusBadFrames>100||p->refocusMinStars<1||p->refocusMinStars>160||!FiniteD(p->refocusStability)||p->refocusStability<0.01||p->refocusStability>20||!FiniteD(p->refocusCooldown)||p->refocusCooldown<0||p->refocusCooldown>1440){ProfileSetMessage(error,cap,L"Auto-Refokus-Parameter des Profils sind ungültig.");return FALSE;}
    if(p->tempCompDeadband<1||p->tempCompDeadband>5000||p->tempCompMaxStep<1||p->tempCompMaxStep>10000||p->refocusEveryCaptures<0||p->refocusEveryCaptures>100000||!FiniteD(p->focalLength)||p->focalLength<1||p->focalLength>100000||!FiniteD(p->pixelSize)||p->pixelSize<=0||p->pixelSize>1000||p->simulatorProfile<0||p->simulatorProfile>SIM_RANDOM||p->simulatorBacklash<0||p->simulatorBacklash>5000||p->simulatorSeed==0){ProfileSetMessage(error,cap,L"Erweiterte Profil- oder Simulatorparameter sind ungültig.");return FALSE;}
    if(p->modelSuccessfulRuns<0||p->modelSuccessfulRuns>1000000||p->modelTypicalPosition<-1||p->modelTypicalPosition>2000000000||p->modelRecommendedStep<5||p->modelRecommendedStep>1000000||p->modelBacklash<0||p->modelBacklash>1000000||!FiniteD(p->modelTypicalFwhm)||p->modelTypicalFwhm<0.0||p->modelTypicalFwhm>1000000.0||!FiniteD(p->modelTypicalHfr)||p->modelTypicalHfr<0.0||p->modelTypicalHfr>1000000.0||!FiniteD(p->modelQualityMean)||p->modelQualityMean<0.0||p->modelQualityMean>100.0||p->filterReferencePosition<-1||p->filterReferencePosition>2000000000||p->filterCount<0||p->filterCount>MAX_FILTER_OFFSETS||p->tempCount<0||p->tempCount>MAX_TEMP_PROFILE){ProfileSetMessage(error,cap,L"Fokusmodell oder Profildaten sind beschädigt.");return FALSE;}
    for(int i=0;i<p->filterCount;i++)if(!p->filters[i].valid||!p->filters[i].name[0]||p->filters[i].offset<-1000000||p->filters[i].offset>1000000){ProfileSetMessage(error,cap,L"Ein Filteroffset des Profils ist ungültig.");return FALSE;}
    for(int i=0;i<p->tempCount;i++)if(!FiniteD(p->tempT[i])||p->tempT[i]<=-100||p->tempT[i]>=100||p->tempP[i]<0||p->tempP[i]>2000000000){ProfileSetMessage(error,cap,L"Ein Temperaturmodellpunkt des Profils ist ungültig.");return FALSE;}
    ProfileSetMessage(error,cap,L"");return TRUE;
}
static BOOL SerializeProfileCore(const ProfileSnapshot* p,char* out,int cap){
    int o=0;char name[512],cam[1400],foc[1400],filter[256];WToJsonUtf8(p->name,name,512);WToJsonUtf8(p->cameraId,cam,1400);WToJsonUtf8(p->focuserId,foc,1400);WToJsonUtf8(p->currentFilter,filter,256);
    if(!ProfileAppend(out,cap,&o,"{\n  \"format\":\"AstroFocusProfile\",\n  \"profileVersion\":1,\n"))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"name\":\"%s\",\n  \"cameraId\":\"%s\",\n  \"focuserId\":\"%s\",\n",name,cam,foc))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"exposureMs\":%.6f,\n  \"gain\":%d,\n  \"manualStep\":%d,\n  \"afPoints\":%d,\n  \"afStep\":%d,\n  \"afBacklash\":%d,\n  \"afSamples\":%d,\n  \"safeMin\":%d,\n  \"safeMax\":%d,\n",p->exposureMs,p->gain,p->manualStep,p->afPoints,p->afStep,p->afBacklash,p->afSamples,p->safeMin,p->safeMax))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"autoStretch\":%d,\n  \"overlayStars\":%d,\n  \"overlayLabels\":%d,\n  \"overlaySat\":%d,\n  \"zones\":%d,\n  \"bahtinov\":%d,\n  \"preferredOut\":%d,\n  \"reconnect\":%d,\n  \"nativeToupTek\":%d,\n",p->autoStretch,p->overlayStars,p->overlayLabels,p->overlaySat,p->zones,p->bahtinov,p->preferredOut,p->reconnect,p->nativeToupTek))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"autoRefocus\":%d,\n  \"refocusMinutes\":%.6f,\n  \"refocusTemp\":%.6f,\n  \"refocusFwhmPercent\":%.6f,\n  \"refocusBadFrames\":%d,\n  \"refocusMinStars\":%d,\n  \"refocusStability\":%.6f,\n  \"refocusCooldown\":%.6f,\n",p->autoRefocus,p->refocusMinutes,p->refocusTemp,p->refocusFwhmPercent,p->refocusBadFrames,p->refocusMinStars,p->refocusStability,p->refocusCooldown))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"tempComp\":%d,\n  \"autoStartPosition\":%d,\n  \"tempCompDeadband\":%d,\n  \"tempCompMaxStep\":%d,\n  \"refocusOnMeridian\":%d,\n  \"refocusOnReconnect\":%d,\n  \"refocusOnFilter\":%d,\n  \"refocusEveryCaptures\":%d,\n",p->tempComp,p->autoStartPosition,p->tempCompDeadband,p->tempCompMaxStep,p->refocusOnMeridian,p->refocusOnReconnect,p->refocusOnFilter,p->refocusEveryCaptures))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"focalLength\":%.6f,\n  \"pixelSize\":%.6f,\n  \"simulatorProfile\":%d,\n  \"simulatorBacklash\":%d,\n  \"simulatorSeed\":%u,\n",p->focalLength,p->pixelSize,p->simulatorProfile,p->simulatorBacklash,p->simulatorSeed))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"modelSuccessfulRuns\":%d,\n  \"modelTypicalPosition\":%d,\n  \"modelRecommendedStep\":%d,\n  \"modelBacklash\":%d,\n  \"modelTypicalFwhm\":%.8f,\n  \"modelTypicalHfr\":%.8f,\n  \"modelQualityMean\":%.8f,\n",p->modelSuccessfulRuns,p->modelTypicalPosition,p->modelRecommendedStep,p->modelBacklash,p->modelTypicalFwhm,p->modelTypicalHfr,p->modelQualityMean))return FALSE;
    if(!ProfileAppendFormat(out,cap,&o,"  \"currentFilter\":\"%s\",\n  \"filterReferencePosition\":%d,\n  \"filterCount\":%d,\n  \"filterOffsets\":[",filter,p->filterReferencePosition,p->filterCount))return FALSE;
    for(int i=0;i<p->filterCount;i++){char fn[192];WToJsonUtf8(p->filters[i].name,fn,192);if(!ProfileAppendFormat(out,cap,&o,"%s{\"name\":\"%s\",\"offset\":%d}",i?",":"",fn,p->filters[i].offset))return FALSE;}
    if(!ProfileAppendFormat(out,cap,&o,"],\n  \"temperatureCount\":%d,\n  \"temperaturePoints\":[",p->tempCount))return FALSE;
    for(int i=0;i<p->tempCount;i++)if(!ProfileAppendFormat(out,cap,&o,"%s{\"temperatureC\":%.8f,\"position\":%d}",i?",":"",p->tempT[i],p->tempP[i]))return FALSE;
    return ProfileAppend(out,cap,&o,"],\n");
}
static BOOL SerializeProfile(const ProfileSnapshot* p,char* out,int cap){char* core=(char*)Alloc(65536);if(!core)return FALSE;BOOL ok=SerializeProfileCore(p,core,65536);if(!ok){Free(core);return FALSE;}unsigned hash=ProfileHash(core);int n=sprintf(out,"%s  \"checksum\":\"%08X\"\n}\n",core,hash);Free(core);return n>0&&n<cap;}
static const char* JsonProfileSkipWs(const char* p){while(p&&(*p==' '||*p=='\t'||*p=='\r'||*p=='\n'))p++;return p;}
static const char* JsonProfileStringEnd(const char* p){if(!p||*p!='"')return 0;p++;BOOL escaped=FALSE;for(;*p;p++){if(escaped){escaped=FALSE;continue;}if(*p=='\\'){escaped=TRUE;continue;}if(*p=='"')return p;}return 0;}
static BOOL JsonProfileKeyEquals(const char* begin,const char* end,const char* key){int n=ALen(key);if(!end||end-begin!=n)return FALSE;for(int i=0;i<n;i++)if(begin[i]!=key[i])return FALSE;return TRUE;}
static const char* JsonProfileField(const char* j,const char* key){
    if(!j||!key)return 0;const char* p=JsonProfileSkipWs(j);if(*p!='{')return 0;int depth=0;
    for(;*p;p++){
        if(*p=='"'){
            const char* end=JsonProfileStringEnd(p);if(!end)return 0;
            if(depth==1){const char* after=JsonProfileSkipWs(end+1);if(*after==':'&&JsonProfileKeyEquals(p+1,end,key))return JsonProfileSkipWs(after+1);}
            p=end;continue;
        }
        if(*p=='{')depth++;else if(*p=='}'){depth--;if(depth<=0)return 0;}
    }
    return 0;
}
static const char* JsonProfileObjectEnd(const char* start){if(!start||*start!='{')return 0;int depth=0;for(const char* p=start;*p;p++){if(*p=='"'){const char* end=JsonProfileStringEnd(p);if(!end)return 0;p=end;continue;}if(*p=='{')depth++;else if(*p=='}'){depth--;if(depth==0)return p;if(depth<0)return 0;}}return 0;}
static BOOL JsonProfileString(const char* j,const char* key,LPWSTR out,int cap){const char* p=JsonProfileField(j,key);if(!p||*p!='"')return FALSE;p++;char utf[2048];int n=0;while(*p&&*p!='"'&&n<(int)sizeof(utf)-1){char c=*p++;if(c=='\\'){char e=*p++;if(e=='"'||e=='\\'||e=='/')c=e;else if(e=='n'||e=='r'||e=='t')c=' ';else return FALSE;}utf[n++]=c;}if(*p!='"')return FALSE;utf[n]=0;return Utf8ToWide(utf,n,out,cap);}
static BOOL JsonProfileNumber(const char* j,const char* key,double* out){const char* p=JsonProfileField(j,key);if(!p)return FALSE;char t[96];int n=0;while(*p&&*p!=','&&*p!='}'&&*p!=']'&&*p!='\r'&&*p!='\n'&&n<(int)sizeof(t)-1)t[n++]=*p++;while(n>0&&(t[n-1]==' '||t[n-1]=='\t'))n--;t[n]=0;if(n==0)return FALSE;double v=ParseAsciiDouble(t,1.0e308);if(v==1.0e308||!FiniteD(v))return FALSE;*out=v;return TRUE;}
static BOOL JsonProfileInt(const char* j,const char* key,int* out){double d=0;if(!JsonProfileNumber(j,key,&d)||d<-2147483648.0||d>2147483647.0)return FALSE;int v=(int)d;if((double)v!=d)return FALSE;*out=v;return TRUE;}
static BOOL JsonProfileUInt(const char* j,const char* key,unsigned* out){double d=0;if(!JsonProfileNumber(j,key,&d)||d<0||d>4294967295.0)return FALSE;unsigned v=(unsigned)d;if((double)v!=d)return FALSE;*out=v;return TRUE;}
static BOOL JsonProfileBoolInt(const char* j,const char* key,BOOL* out){int v=0;if(!JsonProfileInt(j,key,&v)||v<0||v>1)return FALSE;*out=v?TRUE:FALSE;return TRUE;}
static BOOL ParseProfileJson(const char* j,ProfileSnapshot* p,LPWSTR error,int cap){
    memset(p,0,sizeof(*p));wchar_t format[64],checksumW[32];int version=0;if(!JsonProfileString(j,"format",format,64)||!WEquals(format,L"AstroFocusProfile")||!JsonProfileInt(j,"profileVersion",&version)||version!=1){ProfileSetMessage(error,cap,L"Datei ist kein unterstütztes AstroFocus-Profil.");return FALSE;}
    if(!JsonProfileString(j,"name",p->name,96)||!JsonProfileString(j,"cameraId",p->cameraId,256)||!JsonProfileString(j,"focuserId",p->focuserId,256)){ProfileSetMessage(error,cap,L"Profilname oder Gerätefelder fehlen.");return FALSE;}
#define JP_D(k,f) if(!JsonProfileNumber(j,k,&p->f)){ProfileSetMessage(error,cap,L"Profilfeld fehlt oder ist ungültig: " L##k);return FALSE;}
#define JP_I(k,f) if(!JsonProfileInt(j,k,&p->f)){ProfileSetMessage(error,cap,L"Profilfeld fehlt oder ist ungültig: " L##k);return FALSE;}
#define JP_B(k,f) if(!JsonProfileBoolInt(j,k,&p->f)){ProfileSetMessage(error,cap,L"Profilfeld fehlt oder ist ungültig: " L##k);return FALSE;}
    JP_D("exposureMs",exposureMs);JP_I("gain",gain);JP_I("manualStep",manualStep);JP_I("afPoints",afPoints);JP_I("afStep",afStep);JP_I("afBacklash",afBacklash);JP_I("afSamples",afSamples);JP_I("safeMin",safeMin);JP_I("safeMax",safeMax);
    JP_B("autoStretch",autoStretch);JP_B("overlayStars",overlayStars);JP_B("overlayLabels",overlayLabels);JP_B("overlaySat",overlaySat);JP_B("zones",zones);JP_B("bahtinov",bahtinov);JP_B("preferredOut",preferredOut);JP_B("reconnect",reconnect);JP_B("nativeToupTek",nativeToupTek);
    JP_B("autoRefocus",autoRefocus);JP_D("refocusMinutes",refocusMinutes);JP_D("refocusTemp",refocusTemp);JP_D("refocusFwhmPercent",refocusFwhmPercent);JP_I("refocusBadFrames",refocusBadFrames);JP_I("refocusMinStars",refocusMinStars);JP_D("refocusStability",refocusStability);JP_D("refocusCooldown",refocusCooldown);
    JP_B("tempComp",tempComp);JP_B("autoStartPosition",autoStartPosition);JP_I("tempCompDeadband",tempCompDeadband);JP_I("tempCompMaxStep",tempCompMaxStep);JP_B("refocusOnMeridian",refocusOnMeridian);JP_B("refocusOnReconnect",refocusOnReconnect);JP_B("refocusOnFilter",refocusOnFilter);JP_I("refocusEveryCaptures",refocusEveryCaptures);
    JP_D("focalLength",focalLength);JP_D("pixelSize",pixelSize);JP_I("simulatorProfile",simulatorProfile);JP_I("simulatorBacklash",simulatorBacklash);if(!JsonProfileUInt(j,"simulatorSeed",&p->simulatorSeed)){ProfileSetMessage(error,cap,L"Simulator-Zufallsseed fehlt oder ist ungültig.");return FALSE;}
    JP_I("modelSuccessfulRuns",modelSuccessfulRuns);JP_I("modelTypicalPosition",modelTypicalPosition);JP_I("modelRecommendedStep",modelRecommendedStep);JP_I("modelBacklash",modelBacklash);JP_D("modelTypicalFwhm",modelTypicalFwhm);JP_D("modelTypicalHfr",modelTypicalHfr);JP_D("modelQualityMean",modelQualityMean);
    if(!JsonProfileString(j,"currentFilter",p->currentFilter,32)){ProfileSetMessage(error,cap,L"Aktueller Filter fehlt.");return FALSE;}JP_I("filterReferencePosition",filterReferencePosition);JP_I("filterCount",filterCount);JP_I("temperatureCount",tempCount);if(p->filterCount<0||p->filterCount>MAX_FILTER_OFFSETS){ProfileSetMessage(error,cap,L"Filteranzahl liegt außerhalb der zulässigen Grenzen.");return FALSE;}if(p->tempCount<0||p->tempCount>MAX_TEMP_PROFILE){ProfileSetMessage(error,cap,L"Anzahl der Temperaturmodellpunkte liegt außerhalb der zulässigen Grenzen.");return FALSE;}
#undef JP_D
#undef JP_I
#undef JP_B
    const char* fp=JsonProfileField(j,"filterOffsets");if(!fp||*fp!='['){ProfileSetMessage(error,cap,L"Filteroffset-Liste fehlt.");return FALSE;}fp++;for(int i=0;i<p->filterCount;i++){while(*fp&&*fp!='{')fp++;if(!*fp){ProfileSetMessage(error,cap,L"Filteroffset-Liste ist unvollständig.");return FALSE;}const char* end=JsonProfileObjectEnd(fp);if(!end){ProfileSetMessage(error,cap,L"Filteroffset-Eintrag ist beschädigt.");return FALSE;}char item[512];int len=(int)(end-fp+1);if(len<=0||len>=(int)sizeof(item)){ProfileSetMessage(error,cap,L"Filteroffset-Eintrag ist zu lang.");return FALSE;}memcpy(item,fp,(SIZE_T)len);item[len]=0;if(!JsonProfileString(item,"name",p->filters[i].name,32)||!JsonProfileInt(item,"offset",&p->filters[i].offset)){ProfileSetMessage(error,cap,L"Filteroffset-Eintrag ist ungültig.");return FALSE;}p->filters[i].valid=TRUE;fp=end+1;}
    const char* tp=JsonProfileField(j,"temperaturePoints");if(!tp||*tp!='['){ProfileSetMessage(error,cap,L"Temperaturmodell-Liste fehlt.");return FALSE;}tp++;for(int i=0;i<p->tempCount;i++){while(*tp&&*tp!='{')tp++;if(!*tp){ProfileSetMessage(error,cap,L"Temperaturmodell ist unvollständig.");return FALSE;}const char* end=JsonProfileObjectEnd(tp);if(!end){ProfileSetMessage(error,cap,L"Temperaturmodellpunkt ist beschädigt.");return FALSE;}char item[512];int len=(int)(end-tp+1);if(len<=0||len>=(int)sizeof(item)){ProfileSetMessage(error,cap,L"Temperaturmodellpunkt ist zu lang.");return FALSE;}memcpy(item,tp,(SIZE_T)len);item[len]=0;if(!JsonProfileNumber(item,"temperatureC",&p->tempT[i])||!JsonProfileInt(item,"position",&p->tempP[i])){ProfileSetMessage(error,cap,L"Temperaturmodellpunkt ist ungültig.");return FALSE;}tp=end+1;}
    if(!JsonProfileString(j,"checksum",checksumW,32)){ProfileSetMessage(error,cap,L"Integritätsprüfsumme fehlt.");return FALSE;}unsigned expected=0;for(int i=0;i<8;i++){int h=HexValue((char)checksumW[i]);if(h<0){ProfileSetMessage(error,cap,L"Integritätsprüfsumme ist ungültig.");return FALSE;}expected=(expected<<4)|(unsigned)h;}if(checksumW[8]){ProfileSetMessage(error,cap,L"Integritätsprüfsumme hat eine falsche Länge.");return FALSE;}
    if(!ValidateProfileSnapshot(p,error,cap))return FALSE;char* core=(char*)Alloc(65536);if(!core){ProfileSetMessage(error,cap,L"Nicht genügend Speicher zum Prüfen des Profils.");return FALSE;}BOOL serialized=SerializeProfileCore(p,core,65536);unsigned actual=serialized?ProfileHash(core):0;Free(core);if(!serialized||actual!=expected){ProfileSetMessage(error,cap,L"Profil wurde verändert oder ist beschädigt (Prüfsumme stimmt nicht).");return FALSE;}return TRUE;
}
static BOOL ReadProfileSlot(int slot,ProfileSnapshot* p,LPWSTR error,int cap){wchar_t path[700];ProfileSlotPath(slot,path,700);char* text=0;DWORD size=0;if(!ReadWholeTextFile(path,&text,&size)){ProfileSetMessage(error,cap,L"Profildatei konnte nicht gelesen werden.");return FALSE;}BOOL ok=ParseProfileJson(text,p,error,cap);Free(text);return ok;}
static BOOL WriteProfileSlot(int slot,const ProfileSnapshot* p){char* text=(char*)Alloc(65536);if(!text)return FALSE;BOOL ok=SerializeProfile(p,text,65536);if(ok){wchar_t path[700];ProfileSlotPath(slot,path,700);ok=WriteTextFileAtomic(path,text);}Free(text);return ok;}
static void ApplyProfileSnapshot(const ProfileSnapshot* p){
    wchar_t v[96];FormatFixed(p->exposureMs,2,v);SetWindowTextW(g_exposureEdit,v);wsprintfW(v,L"%d",p->gain);SetWindowTextW(g_gainEdit,v);wsprintfW(v,L"%d",p->manualStep);SetWindowTextW(g_manualStepEdit,v);wsprintfW(v,L"%d",p->afPoints);SetWindowTextW(g_afPointsEdit,v);wsprintfW(v,L"%d",p->afStep);SetWindowTextW(g_afStepEdit,v);wsprintfW(v,L"%d",p->afBacklash);SetWindowTextW(g_afBacklashEdit,v);wsprintfW(v,L"%d",p->afSamples);SetWindowTextW(g_afSamplesEdit,v);
    g_safeMinPosition=p->safeMin;g_safeMaxPosition=p->safeMax;SetChecked(g_autoStretch,p->autoStretch);SetChecked(g_overlayStars,p->overlayStars);SetChecked(g_overlayLabels,p->overlayLabels);SetChecked(g_overlaySat,p->overlaySat);SetChecked(g_zoneCheck,p->zones);SetChecked(g_bahtinovCheck,p->bahtinov);SetChecked(g_preferredDirCheck,p->preferredOut);SetChecked(g_reconnectCheck,p->reconnect);
    if(!g_cameraConnected){SetChecked(g_nativeCheck,p->nativeToupTek);CopyWBounded(g_savedCameraId,256,p->cameraId);CopyWBounded(g_cameraId,256,p->cameraId);SetWindowTextW(g_cameraEdit,g_cameraId);}if(!g_focuserConnected){CopyWBounded(g_savedFocuserId,256,p->focuserId);CopyWBounded(g_focuserId,256,p->focuserId);SetWindowTextW(g_focuserEdit,g_focuserId);}
    FormatFixed(p->refocusMinutes,2,v);SetWindowTextW(g_refocusMinutesEdit,v);FormatFixed(p->refocusTemp,2,v);SetWindowTextW(g_refocusTempEdit,v);g_refocusFwhmThresholdPercent=p->refocusFwhmPercent;g_focusDegradeFactor=1.0+p->refocusFwhmPercent/100.0;g_degradationRefocusEnabled=p->refocusFwhmPercent>0;g_refocusBadFramesRequired=p->refocusBadFrames;g_refocusMinStars=p->refocusMinStars;g_refocusStabilityLimit=p->refocusStability;g_refocusCooldownMinutes=p->refocusCooldown;g_autoRefocusEnabled=p->autoRefocus?FALSE:TRUE;SetAutoRefocusEnabled(p->autoRefocus);
    g_tempCompEnabled=p->tempComp;g_autoStartPositionEnabled=p->autoStartPosition;g_autoStartPending=FALSE;g_tempCompDeadbandSteps=p->tempCompDeadband;g_tempCompMaxStep=p->tempCompMaxStep;g_refocusOnMeridian=p->refocusOnMeridian;g_refocusOnReconnect=p->refocusOnReconnect;g_refocusOnFilter=p->refocusOnFilter;g_refocusEveryCaptures=p->refocusEveryCaptures;g_captureEventCounter=0;
    FormatFixed(p->focalLength,2,v);SetWindowTextW(g_focalEdit,v);FormatFixed(p->pixelSize,3,v);SetWindowTextW(g_pixelEdit,v);g_simProfileMode=p->simulatorProfile;g_simBacklashSteps=p->simulatorBacklash;g_simRandomSeed=p->simulatorSeed;g_simProfileSelectionSequence=0;g_simBacklashRemaining=0;g_simLastDirection=0;SelectSimulatorProfile();
    g_profileSuccessfulRuns=p->modelSuccessfulRuns;g_profileTypicalPosition=p->modelTypicalPosition;g_profileRecommendedStep=p->modelRecommendedStep;g_profileBacklash=p->modelBacklash;g_profileTypicalFwhm=p->modelTypicalFwhm;g_profileTypicalHfr=p->modelTypicalHfr;g_profileQualityMean=p->modelQualityMean;g_profileModelValid=g_profileSuccessfulRuns>0&&g_profileTypicalPosition>=0;
    g_filterReferencePosition=p->filterReferencePosition;g_filterOffsetCount=p->filterCount;CopyWBounded(g_currentFilter,32,p->currentFilter);for(int i=0;i<MAX_FILTER_OFFSETS;i++){memset(&g_filterOffsets[i],0,sizeof(g_filterOffsets[i]));if(i<p->filterCount)g_filterOffsets[i]=p->filters[i];}
    g_tempProfileCount=p->tempCount;for(int i=0;i<p->tempCount;i++){g_tempProfileT[i]=p->tempT[i];g_tempProfileP[i]=p->tempP[i];}UpdateTempRegression();g_lastTempCompTarget=-1;g_filterRefocusPending=FALSE;g_afAutomaticRequest=FALSE;g_afRequestConfirmed=FALSE;
    CopyWBounded(g_activeProfileName,96,p->name);SetWindowTextW(g_profileEdit,g_activeProfileName);if(g_profileRevision>=2147483647)g_profileRevision=1;else g_profileRevision++;SaveSettings();InvalidateRect(g_main,0,FALSE);
}
static BOOL SaveNamedProfile(LPCWSTR rawName,BOOL setActive,LPWSTR detail,int cap){
    if(g_afActive||g_stepAssistActive||g_backlashCalActive){ProfileSetMessage(detail,cap,L"Profil kann während eines Fokusvorgangs nicht gespeichert werden.");return FALSE;}wchar_t name[96];if(!ProfileNameValid(rawName,name,96)){ProfileSetMessage(detail,cap,L"Bitte einen gültigen Profilnamen eingeben.");return FALSE;}int slot=FindProfileSlot(name);BOOL isNew=slot<0;if(isNew)slot=FindFreeProfileSlot();if(slot<0){ProfileSetMessage(detail,cap,L"Maximal 24 Profile sind möglich.");return FALSE;}ProfileSnapshot p;CaptureProfileSnapshot(&p,name);if(!ValidateProfileSnapshot(&p,detail,cap))return FALSE;if(!WriteProfileSlot(slot,&p)){ProfileSetMessage(detail,cap,L"Profil konnte nicht sicher gespeichert werden.");return FALSE;}if(isNew&&!WriteProfileSlotName(slot,name)){wchar_t orphan[700];ProfileSlotPath(slot,orphan,700);ProfileDeleteFile(orphan);ProfileSetMessage(detail,cap,L"Profilindex konnte nicht gespeichert werden; die unvollständige Profildatei wurde entfernt.");return FALSE;}if(setActive){CopyWBounded(g_activeProfileName,96,name);SetWindowTextW(g_profileEdit,g_activeProfileName);SaveSettings();}ProfileSetMessage(detail,cap,L"Profil wurde vollständig gespeichert.");return TRUE;
}
static BOOL LoadNamedProfile(LPCWSTR rawName,LPWSTR detail,int cap){
    if(ProfileOperationBusy()){ProfileSetMessage(detail,cap,L"Profil kann erst nach Ende von Livebild, Belichtung, Motorbewegung oder Fokusvorgang geladen werden.");return FALSE;}wchar_t name[96];if(!ProfileNameValid(rawName,name,96)){ProfileSetMessage(detail,cap,L"Ungültiger Profilname.");return FALSE;}int slot=FindProfileSlot(name);if(slot<0){ProfileSetMessage(detail,cap,L"Profil wurde nicht gefunden.");return FALSE;}ProfileSnapshot p;if(!ReadProfileSlot(slot,&p,detail,cap))return FALSE;ApplyProfileSnapshot(&p);ProfileSetMessage(detail,cap,(g_cameraConnected||g_focuserConnected)?L"Profil geladen; verbundene Geräte blieben unverändert und es wurde keine Bewegung gestartet.":L"Profil geladen; es wurden keine Geräte verbunden und keine Bewegungen gestartet.");return TRUE;
}
static BOOL DeleteNamedProfile(LPCWSTR rawName,LPWSTR detail,int cap){wchar_t name[96];if(!ProfileNameValid(rawName,name,96)){ProfileSetMessage(detail,cap,L"Ungültiger Profilname.");return FALSE;}if(WEquals(name,L"Standardprofil")){ProfileSetMessage(detail,cap,L"Das Standardprofil kann nicht gelöscht werden.");return FALSE;}if(WEquals(name,g_activeProfileName)){ProfileSetMessage(detail,cap,L"Das aktive Profil kann nicht gelöscht werden. Zuerst ein anderes Profil laden.");return FALSE;}int slot=FindProfileSlot(name);if(slot<0){ProfileSetMessage(detail,cap,L"Profil wurde nicht gefunden.");return FALSE;}wchar_t path[700];ProfileSlotPath(slot,path,700);if(!WriteProfileSlotName(slot,L"")){ProfileSetMessage(detail,cap,L"Profilindex konnte nicht aktualisiert werden.");return FALSE;}if(!ProfileDeleteFile(path)){BOOL restored=WriteProfileSlotName(slot,name);ProfileSetMessage(detail,cap,restored?L"Profildatei konnte nicht gelöscht werden; der Profileintrag wurde wiederhergestellt.":L"Profildatei konnte nicht gelöscht werden und der Profileintrag ließ sich nicht wiederherstellen. Die Profildatei bleibt im Profiles-Ordner erhalten.");return FALSE;}ProfileSetMessage(detail,cap,L"Profil wurde gelöscht.");return TRUE;}
static void MakeUniqueImportedName(LPWSTR name,int cap){
    if(!name||cap<2||FindProfileSlot(name)<0)return;wchar_t base[64];int n=0;while(name[n]&&n<55){base[n]=name[n];n++;}base[n]=0;
    for(int i=1;i<100;i++){wchar_t suffix[32];suffix[0]=0;if(i==1)CopyWBounded(suffix,32,L" (importiert)");else wsprintfW(suffix,L" (importiert %d)",i);CopyWBounded(name,cap,base);CatWBounded(name,cap,suffix);if(FindProfileSlot(name)<0)return;}name[0]=0;
}
static BOOL ImportNamedProfile(LPCWSTR path,LPWSTR detail,int cap){if(!path||!path[0]){ProfileSetMessage(detail,cap,L"Keine Importdatei ausgewählt.");return FALSE;}char* text=0;DWORD size=0;if(!ReadWholeTextFile(path,&text,&size)){ProfileSetMessage(detail,cap,L"Importdatei konnte nicht gelesen werden.");return FALSE;}ProfileSnapshot p;BOOL ok=ParseProfileJson(text,&p,detail,cap);Free(text);if(!ok)return FALSE;MakeUniqueImportedName(p.name,96);if(!p.name[0]){ProfileSetMessage(detail,cap,L"Für das importierte Profil konnte kein eindeutiger Name erzeugt werden.");return FALSE;}int slot=FindFreeProfileSlot();if(slot<0){ProfileSetMessage(detail,cap,L"Maximal 24 Profile sind möglich.");return FALSE;}if(!WriteProfileSlot(slot,&p)){ProfileSetMessage(detail,cap,L"Importiertes Profil konnte nicht gespeichert werden.");return FALSE;}if(!WriteProfileSlotName(slot,p.name)){wchar_t orphan[700];ProfileSlotPath(slot,orphan,700);ProfileDeleteFile(orphan);ProfileSetMessage(detail,cap,L"Importindex konnte nicht gespeichert werden; die unvollständige Profildatei wurde entfernt.");return FALSE;}ProfileSetMessage(detail,cap,L"Profil wurde geprüft und importiert; es wurde nicht automatisch geladen.");return TRUE;}
static BOOL ExportNamedProfile(LPCWSTR rawName,LPCWSTR path,LPWSTR detail,int cap){wchar_t name[96];if(!ProfileNameValid(rawName,name,96)||!path||!path[0]){ProfileSetMessage(detail,cap,L"Profilname oder Exportpfad fehlt.");return FALSE;}int slot=FindProfileSlot(name);if(slot<0){ProfileSetMessage(detail,cap,L"Profil wurde nicht gefunden.");return FALSE;}ProfileSnapshot p;if(!ReadProfileSlot(slot,&p,detail,cap))return FALSE;char* text=(char*)Alloc(65536);if(!text){ProfileSetMessage(detail,cap,L"Nicht genügend Speicher für den Export.");return FALSE;}BOOL ok=SerializeProfile(&p,text,65536)&&WriteTextFileAtomic(path,text);Free(text);ProfileSetMessage(detail,cap,ok?L"Profil wurde als geprüfte JSON-Datei exportiert.":L"Profil konnte nicht exportiert werden.");return ok;}
static void EnsureProfileLibrary(){
    wchar_t slot0[96],error[256],legacy[96];ProfileSnapshot stored;ReadProfileSlotName(0,slot0,96);BOOL standardHealthy=WEquals(slot0,L"Standardprofil")&&ReadProfileSlot(0,&stored,error,256);if(!standardHealthy){CopyWBounded(legacy,96,g_activeProfileName);ProfileSnapshot p;CaptureProfileSnapshot(&p,L"Standardprofil");if(WriteProfileSlot(0,&p))WriteProfileSlotName(0,L"Standardprofil");if(legacy[0]&&!WEquals(legacy,L"Standardprofil")&&FindProfileSlot(legacy)<0){int slot=FindFreeProfileSlot();if(slot>=0){CopyWBounded(p.name,96,legacy);if(WriteProfileSlot(slot,&p))WriteProfileSlotName(slot,legacy);}}}
    int active=FindProfileSlot(g_activeProfileName);if(active<0){CopyWBounded(g_activeProfileName,96,L"Standardprofil");active=FindProfileSlot(g_activeProfileName);}if(active>=0&&!ProfileOperationBusy()){ProfileSnapshot p;if(ReadProfileSlot(active,&p,error,256))ApplyProfileSnapshot(&p);else{CopyWBounded(g_activeProfileName,96,L"Standardprofil");int standard=FindProfileSlot(g_activeProfileName);if(standard>=0&&ReadProfileSlot(standard,&p,error,256))ApplyProfileSnapshot(&p);else SetWindowTextW(g_profileEdit,g_activeProfileName);}}
}
static void SendProfileList(SOCKET c){char body[16384];int o=0;char active[512];WToJsonUtf8(g_activeProfileName,active,512);o+=sprintf(body+o,"{\"ok\":true,\"active\":\"%s\",\"profiles\":[",active);BOOL first=TRUE;for(int i=0;i<MAX_NAMED_PROFILES;i++){wchar_t n[96];ReadProfileSlotName(i,n,96);if(!n[0])continue;char e[512];WToJsonUtf8(n,e,512);int add=sprintf(body+o,"%s\"%s\"",first?"":",",e);if(add<=0||o+add>=(int)sizeof(body)-32){SendJsonResult(c,FALSE,"Profilliste zu groß");return;}o+=add;first=FALSE;}o+=sprintf(body+o,"]}");SendHttp(c,"application/json",body,o);}
static void SendProfilePreview(SOCKET c,const char* req){wchar_t name[96],error[256];QueryText(req,"profileName=",name,96);int slot=FindProfileSlot(name);if(slot<0){SendJsonResult(c,FALSE,"Profil nicht gefunden");return;}ProfileSnapshot p;if(!ReadProfileSlot(slot,&p,error,256)){char e[320];WToAscii(error,e,320);SendJsonResult(c,FALSE,e);return;}ProfileSnapshot current;CaptureProfileSnapshot(&current,g_activeProfileName);int changes=0;changes+=current.afPoints!=p.afPoints;changes+=current.afStep!=p.afStep;changes+=current.afBacklash!=p.afBacklash;changes+=current.afSamples!=p.afSamples;changes+=fabs(current.exposureMs-p.exposureMs)>0.001;changes+=current.gain!=p.gain;changes+=current.safeMin!=p.safeMin||current.safeMax!=p.safeMax;changes+=current.autoRefocus!=p.autoRefocus;changes+=fabs(current.refocusMinutes-p.refocusMinutes)>0.001;changes+=fabs(current.refocusTemp-p.refocusTemp)>0.001;changes+=current.simulatorProfile!=p.simulatorProfile||current.simulatorBacklash!=p.simulatorBacklash||current.simulatorSeed!=p.simulatorSeed;changes+=!WEquals(current.cameraId,p.cameraId);changes+=!WEquals(current.focuserId,p.focuserId);char pn[512],cam[1400],foc[1400];WToJsonUtf8(p.name,pn,512);WToJsonUtf8(p.cameraId,cam,1400);WToJsonUtf8(p.focuserId,foc,1400);char body[4096];int n=sprintf(body,"{\"ok\":true,\"profile\":\"%s\",\"changes\":%d,\"summary\":\"Aufnahme %.0f ms / Gain %d · Autofokus %d Punkte, Schritt %d, Backlash %d · Refokus %s, %.1f min / %.2f °C · Simulatorprofil %d, Backlash %d, Seed %u · Fokusmodell %d Läufe · %d Filteroffsets / %d Temperaturpunkte. Beim Laden werden keine Geräte verbunden, keine Aufnahme gestartet und keine Fokusposition angefahren.\",\"cameraId\":\"%s\",\"focuserId\":\"%s\"}",pn,changes,p.exposureMs,p.gain,p.afPoints,p.afStep,p.afBacklash,p.autoRefocus?"aktiv":"aus",p.refocusMinutes,p.refocusTemp,p.simulatorProfile,p.simulatorBacklash,p.simulatorSeed,p.modelSuccessfulRuns,p.filterCount,p.tempCount,cam,foc);if(n<=0||n>=(int)sizeof(body))SendJsonResult(c,FALSE,"Profilvorschau zu groß");else SendHttp(c,"application/json",body,n);}
static BOOL IsAsciiDigit(char c){return c>='0'&&c<='9';}
static double ParseAsciiDouble(const char* s,double fallback){
    if(!s)return fallback;int i=0;while(s[i]==' '||s[i]=='\t')i++;BOOL neg=FALSE;if(s[i]=='-'){neg=TRUE;i++;}else if(s[i]=='+')i++;
    double v=0.0,scale=0.1;BOOL any=FALSE,frac=FALSE;for(;s[i]&&s[i]!=';'&&s[i]!='\r'&&s[i]!='\n';i++){char c=s[i];if(IsAsciiDigit(c)){any=TRUE;if(frac){if(scale>1.0e-15){v+=(double)(c-'0')*scale;scale*=0.1;}}else{if(v>1.0e300/10.0)return fallback;v=v*10.0+(double)(c-'0');}}else if((c=='.'||c==',')&&!frac)frac=TRUE;else if(c!=' '&&c!='\t')return fallback;}
    v=neg?-v:v;return any&&FiniteD(v)?v:fallback;
}
static int ParseAsciiInt(const char* s,int fallback){double v=ParseAsciiDouble(s,(double)fallback);if(!FiniteD(v)||v>2147483647.0||v<-2147483648.0)return fallback;return (int)(v+(v>=0?0.5:-0.5));}
static void ProfilePath(LPWSTR path){wchar_t profile[96],safe[96],dir[600];GetWindowTextW(g_profileEdit,profile,96);int n=0;for(int i=0;profile[i]&&n<70;i++){wchar_t c=profile[i];if((c>=L'a'&&c<=L'z')||(c>=L'A'&&c<=L'Z')||(c>=L'0'&&c<=L'9')||c==L'-'||c==L'_')safe[n++]=c;else if(c==L' '||c==L'.')safe[n++]=L'_';}if(n==0){lstrcpyW(safe,L"Standard");n=WLen(safe);}safe[n]=0;lstrcpyW(dir,g_logDir);wsprintfW(path,L"%s\\FocusTemperature_%s.csv",dir,safe);}

static void ProfileModelPath(LPWSTR path){
    wchar_t profile[96],safe[96],dir[600];GetWindowTextW(g_profileEdit,profile,96);int n=0;for(int i=0;profile[i]&&n<70;i++){wchar_t c=profile[i];if((c>=L'a'&&c<=L'z')||(c>=L'A'&&c<=L'Z')||(c>=L'0'&&c<=L'9')||c==L'-'||c==L'_')safe[n++]=c;else if(c==L' '||c==L'.')safe[n++]=L'_';}if(n==0){lstrcpyW(safe,L"Standard");n=WLen(safe);}safe[n]=0;lstrcpyW(dir,g_logDir);wsprintfW(path,L"%s\\FocusModel_%s.ini",dir,safe);
}
static void SaveFocusProfileModel(){
    wchar_t path[700],v[96];ProfileModelPath(path);wsprintfW(v,L"%d",g_profileSuccessfulRuns);WritePrivateProfileStringW(L"Model",L"SuccessfulRuns",v,path);wsprintfW(v,L"%d",g_profileTypicalPosition);WritePrivateProfileStringW(L"Model",L"TypicalPosition",v,path);FormatFixed(g_profileTypicalFwhm,4,v);WritePrivateProfileStringW(L"Model",L"TypicalFwhm",v,path);FormatFixed(g_profileTypicalHfr,4,v);WritePrivateProfileStringW(L"Model",L"TypicalHfr",v,path);FormatFixed(g_profileQualityMean,2,v);WritePrivateProfileStringW(L"Model",L"QualityMean",v,path);wsprintfW(v,L"%d",g_profileRecommendedStep);WritePrivateProfileStringW(L"Model",L"RecommendedStep",v,path);wsprintfW(v,L"%d",g_profileBacklash);WritePrivateProfileStringW(L"Model",L"Backlash",v,path);wsprintfW(v,L"%d",g_filterReferencePosition);WritePrivateProfileStringW(L"Filters",L"ReferencePosition",v,path);GetPrivateProfileStringW(L"Filters",L"CurrentFilter",L"",v,96,path);WritePrivateProfileStringW(L"Filters",L"CurrentFilter",g_currentFilter,path);for(int i=0;i<MAX_FILTER_OFFSETS;i++){wchar_t key[48];wsprintfW(key,L"Name%d",i);WritePrivateProfileStringW(L"Filters",key,i<g_filterOffsetCount&&g_filterOffsets[i].valid?g_filterOffsets[i].name:L"",path);wsprintfW(key,L"Offset%d",i);wsprintfW(v,L"%d",i<g_filterOffsetCount?g_filterOffsets[i].offset:0);WritePrivateProfileStringW(L"Filters",key,v,path);}
}
static void LoadFocusProfileModel(){
    wchar_t path[700],v[128];ProfileModelPath(path);g_profileSuccessfulRuns=0;g_profileTypicalPosition=-1;g_profileTypicalFwhm=g_profileTypicalHfr=g_profileQualityMean=0.0;g_profileRecommendedStep=120;g_profileBacklash=250;g_profileModelValid=FALSE;g_filterOffsetCount=0;g_filterReferencePosition=-1;g_currentFilter[0]=0;
    GetPrivateProfileStringW(L"Model",L"SuccessfulRuns",L"0",v,128,path);UINT u=0;if(ParseStrictUIntW(v,&u)&&u<1000000U)g_profileSuccessfulRuns=(int)u;GetPrivateProfileStringW(L"Model",L"TypicalPosition",L"-1",v,128,path);int parsedInt=-1;if(ParseStrictIntW(v,&parsedInt)&&parsedInt>=-1)g_profileTypicalPosition=parsedInt;GetPrivateProfileStringW(L"Model",L"TypicalFwhm",L"0",v,128,path);if(!ParseStrictDoubleW(v,&g_profileTypicalFwhm))g_profileTypicalFwhm=0.0;GetPrivateProfileStringW(L"Model",L"TypicalHfr",L"0",v,128,path);if(!ParseStrictDoubleW(v,&g_profileTypicalHfr))g_profileTypicalHfr=0.0;GetPrivateProfileStringW(L"Model",L"QualityMean",L"0",v,128,path);if(!ParseStrictDoubleW(v,&g_profileQualityMean))g_profileQualityMean=0.0;GetPrivateProfileStringW(L"Model",L"RecommendedStep",L"120",v,128,path);if(ParseStrictUIntW(v,&u)&&u>=5U&&u<=5000U)g_profileRecommendedStep=(int)u;GetPrivateProfileStringW(L"Model",L"Backlash",L"250",v,128,path);if(ParseStrictUIntW(v,&u)&&u<=1000000U)g_profileBacklash=(int)u;g_profileModelValid=g_profileSuccessfulRuns>0&&g_profileTypicalPosition>=0;
    GetPrivateProfileStringW(L"Filters",L"ReferencePosition",L"-1",v,128,path);parsedInt=-1;if(ParseStrictIntW(v,&parsedInt)&&parsedInt>=-1)g_filterReferencePosition=parsedInt;GetPrivateProfileStringW(L"Filters",L"CurrentFilter",L"",g_currentFilter,32,path);for(int i=0;i<MAX_FILTER_OFFSETS;i++){wchar_t key[48],name[32];wsprintfW(key,L"Name%d",i);GetPrivateProfileStringW(L"Filters",key,L"",name,32,path);if(!name[0])continue;wsprintfW(key,L"Offset%d",i);GetPrivateProfileStringW(L"Filters",key,L"0",v,128,path);int off=0;if(!ParseStrictIntW(v,&off))off=0;CopyWBounded(g_filterOffsets[g_filterOffsetCount].name,32,name);g_filterOffsets[g_filterOffsetCount].offset=off;g_filterOffsets[g_filterOffsetCount].valid=TRUE;g_filterOffsetCount++;if(g_filterOffsetCount>=MAX_FILTER_OFFSETS)break;}
    if(g_profileModelValid){wchar_t q[32];wsprintfW(q,L"%d",g_profileRecommendedStep);SetWindowTextW(g_afStepEdit,q);wsprintfW(q,L"%d",g_profileBacklash);SetWindowTextW(g_afBacklashEdit,q);}LoadTemperatureProfile();
}
static void UpdateFocusProfileModelAfterSuccess(){
    if(g_syntheticSelfTestActive||!g_afFinalValid||g_afFinalPosition<0)return;int old=g_profileSuccessfulRuns;int now=old+1;double wOld=old>0?(double)old:0.0;g_profileTypicalPosition=old>0?(int)(((double)g_profileTypicalPosition*wOld+(double)g_afFinalPosition)/(double)now+0.5):g_afFinalPosition;g_profileTypicalFwhm=old>0?(g_profileTypicalFwhm*wOld+g_afFinalFwhm)/(double)now:g_afFinalFwhm;g_profileTypicalHfr=old>0?(g_profileTypicalHfr*wOld+g_afFinalHfr)/(double)now:g_afFinalHfr;g_profileQualityMean=old>0?(g_profileQualityMean*wOld+(double)g_focusQualityScore)/(double)now:(double)g_focusQualityScore;g_profileSuccessfulRuns=now;g_profileModelValid=TRUE;wchar_t v[64];GetWindowTextW(g_afStepEdit,v,64);UINT u=0;if(ParseStrictUIntW(v,&u)&&u>=5U&&u<=5000U)g_profileRecommendedStep=(int)u;GetWindowTextW(g_afBacklashEdit,v,64);if(ParseStrictUIntW(v,&u)&&u<=1000000U)g_profileBacklash=(int)u;SaveFocusProfileModel();
}
static void AppendSessionEvent(LPCWSTR eventName,LPCWSTR detail){
    if(g_syntheticSelfTestActive)return;
    wchar_t dir[600];lstrcpyW(dir,g_logDir);SYSTEMTIME st;GetLocalTime(&st);wchar_t path[700];wsprintfW(path,L"%s\\Session_%04u%02u%02u.csv",dir,st.wYear,st.wMonth,st.wDay);if(!g_sessionPath[0]||!WEquals(g_sessionPath,path)){CopyWBounded(g_sessionPath,700,path);g_sessionHeaderWritten=FALSE;}
    HANDLE h=CreateFileW(path,GENERIC_WRITE,1,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return;DWORD existingSize=GetFileSize(h,0);if(existingSize!=0xffffffffU&&existingSize>0)g_sessionHeaderWritten=TRUE;SetFilePointer(h,0,0,FILE_END);
    if(!g_sessionHeaderWritten){const char* header="Timestamp;Event;Detail;Position;Temperature_C;FWHM;HFR;Quality;SeeingIndex;Filter\r\n";if(!WriteAllHandle(h,header,(DWORD)ALen(header))){CloseHandle(h);return;}g_sessionHeaderWritten=TRUE;}
    char ev[160],de[420],fi[80];CsvSafeAscii(eventName,ev,160);CsvSafeAscii(detail,de,420);CsvSafeAscii(g_currentFilter,fi,80);char line[1200];int n=sprintf(line,"%04u-%02u-%02u %02u:%02u:%02u;%s;%s;%d;%.3f;%.4f;%.4f;%d;%.1f;%s\r\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,ev,de,FocuserPosition(),g_hasFocuserTemperature?g_focuserTemperature:-999.0,g_medianFwhm,g_medianHfr,g_focusQualityScore,g_seeingIndex,fi);
    if(n>0&&(unsigned)n<sizeof(line))WriteAllHandle(h,line,(DWORD)n);CloseHandle(h);
}
static int FindFilterOffsetIndex(LPCWSTR name){for(int i=0;i<g_filterOffsetCount;i++)if(g_filterOffsets[i].valid&&WEquals(g_filterOffsets[i].name,name))return i;return -1;}
static BOOL LearnCurrentFilterOffset(LPCWSTR name){if(!name||!name[0]||!g_focuserConnected)return FALSE;if(g_afActive||g_stepAssistActive||g_backlashCalActive||FocuserMoving()){SetStatus(L"Filteroffset kann während eines Fokus- oder Kalibrierungslaufs nicht gelernt werden");return FALSE;}int p=FocuserPosition();if(p<0)return FALSE;if(g_filterReferencePosition<0)g_filterReferencePosition=p;long long offset=(long long)p-(long long)g_filterReferencePosition;if(offset<-2147483648LL||offset>2147483647LL){SetStatus(L"Filteroffset liegt außerhalb des unterstützten Zahlenbereichs");return FALSE;}int idx=FindFilterOffsetIndex(name);if(idx<0){if(g_filterOffsetCount>=MAX_FILTER_OFFSETS)return FALSE;idx=g_filterOffsetCount++;g_filterOffsets[idx].valid=TRUE;CopyWBounded(g_filterOffsets[idx].name,32,name);}g_filterOffsets[idx].offset=(int)offset;CopyWBounded(g_currentFilter,32,name);SaveFocusProfileModel();AppendSessionEvent(L"Filteroffset gelernt",name);return TRUE;}
static BOOL ApplyFilterOffset(LPCWSTR name){if(!name||!name[0]||!g_focuserConnected)return FALSE;if(g_afActive||g_stepAssistActive||g_backlashCalActive||g_continuousFocusPhase==CF_MOVING||g_continuousFocusPhase==CF_SETTLING||FocuserMoving()){SetStatus(L"Filteroffset kann während eines Fokus-, Nachführungs- oder Kalibrierungslaufs nicht angewendet werden");return FALSE;}int idx=FindFilterOffsetIndex(name);if(idx<0){CopyWBounded(g_currentFilter,32,name);SaveFocusProfileModel();if(g_refocusOnFilter)HandleExternalRefocusEvent(L"Filterwechsel ohne bekannten Offset");return FALSE;}int current=FocuserPosition();if(current<0)return FALSE;int currentOffset=0;int old=FindFilterOffsetIndex(g_currentFilter);if(old>=0)currentOffset=g_filterOffsets[old].offset;long long delta=(long long)g_filterOffsets[idx].offset-(long long)currentOffset;long long requested=(long long)current+delta;int target=requested<(long long)g_safeMinPosition?g_safeMinPosition:(requested>(long long)g_safeMaxPosition?g_safeMaxPosition:(int)requested);BOOL ok=delta==0||MoveFocuser(target);if(ok){CopyWBounded(g_currentFilter,32,name);if(delta!=0)ContinuousFocusResetReference(L"Filteroffset angewendet · Nachführungsreferenz wird neu aufgebaut");SaveFocusProfileModel();AppendSessionEvent(L"Filteroffset angewendet",name);if(g_refocusOnFilter){if(delta!=0)g_filterRefocusPending=TRUE;else HandleExternalRefocusEvent(L"Filterwechsel");}}return ok;}
static BOOL HandleExternalRefocusEvent(LPCWSTR eventName){CopyWBounded(g_lastExternalEvent,160,eventName?eventName:L"Externes Ereignis");AppendSessionEvent(L"Externes Ereignis",g_lastExternalEvent);BOOL enabled=FALSE;if(WContains(g_lastExternalEvent,L"Meridian"))enabled=g_refocusOnMeridian;else if(WContains(g_lastExternalEvent,L"Reconnect")||WContains(g_lastExternalEvent,L"Wiederverbindung"))enabled=g_refocusOnReconnect;else if(WContains(g_lastExternalEvent,L"Filter"))enabled=g_refocusOnFilter;else if(WContains(g_lastExternalEvent,L"Aufnahme"))enabled=g_refocusEveryCaptures>0;else enabled=TRUE;if(!enabled)return FALSE;if(!g_autoRefocusEnabled){SetStatus(L"Externes Refokusereignis registriert · Auto-Refokus ist deaktiviert");return FALSE;}return TriggerAutomaticRefocus(eventName?eventName:L"Auto-Refokus nach externem Ereignis");}
static void TryAutomaticStartPosition(){if(!g_autoStartPositionEnabled||!g_focuserConnected||!g_profileModelValid)return;int target=ClampI(g_profileTypicalPosition,g_safeMinPosition,g_safeMaxPosition);if(g_tempFitValid&&g_tempProfileCount>=3&&g_hasFocuserTemperature)target=RoundedModelPosition(g_tempSlope*g_focuserTemperature+g_tempIntercept,g_safeMinPosition,g_safeMaxPosition);int current=FocuserPosition();if(current<0)return;long long distance=(long long)target-(long long)current;if(distance<0)distance=-distance;if(distance<=(long long)g_tempCompDeadbandSteps){g_lastTempCompTarget=target;return;}if(MoveFocuser(target)){g_lastTempCompTarget=target;wchar_t d[180];wsprintfW(d,L"Automatische Startposition aus Profilmodell: %d",target);SetStatus(d);AppendSessionEvent(L"Startposition",d);}}

static void ContinuousFocusSetStatus(LPCWSTR state,LPCWSTR reason){CopyWBounded(g_continuousFocusState,96,state?state:L"–");CopyWBounded(g_continuousFocusReason,320,reason?reason:L"–");}
static void ContinuousFocusClearSamples(){g_continuousFocusSampleCount=0;for(int i=0;i<16;i++)g_continuousFocusSamples[i]=0.0;}
static void ContinuousFocusResetReference(LPCWSTR reason){
    if(g_continuousFocusPhase==CF_MOVING||g_continuousFocusPhase==CF_SETTLING){g_continuousFocusPaused=TRUE;ContinuousFocusSetStatus(L"Pausiert",L"Referenzänderung während einer laufenden Motorfahrt blockiert; Nachführung bleibt bis zur Freigabe pausiert.");return;}
    int position=g_focuserConnected?FocuserPosition():-1;
    g_continuousFocusReferenceMetric=0.0;g_continuousFocusBeforeMetric=0.0;g_continuousFocusEstimatedError=0.0;g_continuousFocusDriftStepsPerMinute=0.0;g_continuousFocusLastAcceptedTick=0;g_continuousFocusFallbackPending=FALSE;g_continuousFocusPhase=CF_IDLE;g_continuousFocusMoveKind=CF_MOVE_NONE;g_continuousFocusOrigin=position;g_continuousFocusTarget=position;g_continuousFocusLastCorrection=0;g_continuousFocusRejected=0;ContinuousFocusClearSamples();ContinuousFocusSetStatus(g_continuousFocusEnabled?L"Referenz wird aufgebaut":L"Deaktiviert",reason&&*reason?reason:L"Wartet auf stabile Live-Messungen.");
}
static void ContinuousFocusSuspendForAutofocus(){
    g_continuousFocusFallbackPending=FALSE;g_continuousFocusPhase=CF_IDLE;g_continuousFocusMoveKind=CF_MOVE_NONE;ContinuousFocusClearSamples();
    if(g_continuousFocusEnabled)ContinuousFocusSetStatus(L"Autofokus hat Vorrang",L"Kontinuierliche Nachführung wartet bis zum Abschluss des vollständigen Autofokuslaufs.");
}
static BOOL ContinuousFocusReadyForFrame(){
    return g_continuousFocusEnabled&&!g_continuousFocusPaused&&g_live&&g_cameraConnected&&g_focuserConnected&&!g_focuserSetupReserved&&!g_afActive&&!g_stepAssistActive&&!g_backlashCalActive&&!g_cameraWorkerBlocked&&!g_focuserWorkerBlocked&&!FocuserMoving()&&FocuserPosition()>=0;
}
static BOOL ContinuousFocusBeginMove(int target,int kind,LPCWSTR reason){
    if(g_exposing||FocuserMoving()||g_afActive||g_stepAssistActive||g_backlashCalActive||g_focuserSetupReserved)return FALSE;
    int current=FocuserPosition();if(current<0)return FALSE;target=AfsCfClampInt(target,g_safeMinPosition,g_safeMaxPosition);if(target==current)return FALSE;
    if(!MoveFocuser(target)){g_continuousFocusPaused=TRUE;ContinuousFocusSetStatus(L"Pausiert",L"Mikrokorrektur konnte nicht sicher gestartet werden. Fokussierer und sichere Zone prüfen.");return FALSE;}
    g_continuousFocusOrigin=current;g_continuousFocusTarget=target;if(kind!=CF_MOVE_ROLLBACK){g_continuousFocusLastCorrection=target-current;g_continuousFocusLastDirection=g_continuousFocusLastCorrection>=0?1:-1;}g_continuousFocusMoveKind=kind;g_continuousFocusPhase=CF_MOVING;g_continuousFocusLastActionTick=GetTickCount64();ContinuousFocusClearSamples();ContinuousFocusSetStatus(kind==CF_MOVE_ROLLBACK?L"Rückkehr":L"Mikrokorrektur",reason);AppendSessionEvent(L"Kontinuierliche Fokusnachführung",reason);return TRUE;
}
static BOOL ContinuousFocusRequestFallback(){
    if(!g_continuousFocusFallback||!g_autoRefocusEnabled||g_autoRefocusPaused)return FALSE;
    g_continuousFocusFallbackPending=TRUE;return TRUE;
}
static BOOL ContinuousFocusOnLiveFrame(){
    if(!g_continuousFocusEnabled){g_continuousFocusPhase=CF_IDLE;g_continuousFocusMoveKind=CF_MOVE_NONE;ContinuousFocusClearSamples();ContinuousFocusSetStatus(L"Deaktiviert",L"Kontinuierliche Fokusnachführung ist deaktiviert.");return FALSE;}
    if(g_continuousFocusPaused){ContinuousFocusSetStatus(L"Pausiert",g_continuousFocusReason);return FALSE;}
    if(g_continuousFocusPhase==CF_MOVING||g_continuousFocusPhase==CF_SETTLING)return TRUE;
    if(!ContinuousFocusReadyForFrame()){ContinuousFocusClearSamples();ContinuousFocusSetStatus(L"Nicht bereit",L"Livebild, Kamera und Fokussierer müssen verbunden und alle anderen Fokusoperationen beendet sein.");return FALSE;}
    double metric=AfsCfMetric(g_medianFwhm,g_medianHfr);double stability=FocusStability();int confidence=AfsCfConfidence(g_usedCount,g_refocusMinStars,stability,g_refocusStabilityLimit,g_medianSnr);g_continuousFocusConfidence=(double)confidence;
    if(metric<=0.0||g_usedCount<g_refocusMinStars||confidence<g_continuousFocusMinConfidence){
        ContinuousFocusClearSamples();wchar_t reason[300];wsprintfW(reason,L"Messung verworfen: %d Sterne, Regelqualität %d/100, Stabilität außerhalb der Freigabe.",g_usedCount,confidence);ContinuousFocusSetStatus(L"Wartet auf belastbare Messung",reason);return FALSE;
    }
    if(g_continuousFocusSampleCount<16)g_continuousFocusSamples[g_continuousFocusSampleCount++]=metric;
    if(g_continuousFocusSampleCount<g_continuousFocusMinFrames){wchar_t reason[220];wsprintfW(reason,L"Sammelt stabile Live-Bilder: %d/%d · keine Bewegung während Belichtung.",g_continuousFocusSampleCount,g_continuousFocusMinFrames);ContinuousFocusSetStatus(g_continuousFocusPhase==CF_VERIFYING?L"Kontrollmessung":L"Messfenster",reason);return FALSE;}
    double current=AfsCfMedian(g_continuousFocusSamples,g_continuousFocusSampleCount);ContinuousFocusClearSamples();
    if(g_continuousFocusPhase==CF_VERIFYING){
        double improvement=AfsCfImprovementPercent(g_continuousFocusBeforeMetric,current);
        if(improvement>=g_continuousFocusMinImprovement||current<=g_continuousFocusReferenceMetric*1.01){
            g_continuousFocusAccepted++;g_continuousFocusRejected=0;g_continuousFocusPhase=CF_IDLE;g_continuousFocusMoveKind=CF_MOVE_NONE;g_continuousFocusReferenceMetric=g_continuousFocusReferenceMetric>0.0?(g_continuousFocusReferenceMetric*0.80+current*0.20):current;g_continuousFocusEstimatedError=0.0;g_continuousFocusTarget=FocuserPosition();{ULONGLONG acceptedNow=GetTickCount64();if(g_continuousFocusLastAcceptedTick&&acceptedNow>g_continuousFocusLastAcceptedTick){double minutes=(double)(acceptedNow-g_continuousFocusLastAcceptedTick)/60000.0;if(minutes>0.01){double rate=(double)g_continuousFocusLastCorrection/minutes;g_continuousFocusDriftStepsPerMinute=g_continuousFocusDriftStepsPerMinute==0.0?rate:(g_continuousFocusDriftStepsPerMinute*0.70+rate*0.30);}}g_continuousFocusLastAcceptedTick=acceptedNow;}wchar_t reason[260];wchar_t imp[32];FormatFixed(improvement,2,imp);wsprintfW(reason,L"Korrektur %d Schritte bestätigt · Verbesserung %s %% · Referenz wird robust nachgeführt.",g_continuousFocusLastCorrection,imp);ContinuousFocusSetStatus(L"Korrektur bestätigt",reason);return FALSE;
        }
        int rejectedMoveKind=g_continuousFocusMoveKind;if(rejectedMoveKind==CF_MOVE_IMAGE_PROBE)g_continuousFocusLastDirection=-g_continuousFocusLastDirection;
        g_continuousFocusRejected++;BOOL wantsFallback=g_continuousFocusRejected>=2&&ContinuousFocusRequestFallback();wchar_t reason[300];wchar_t imp[32];FormatFixed(improvement,2,imp);wsprintfW(reason,L"Korrektur nicht bestätigt (%s %%) · Rückkehr zu Position %d%s.",imp,g_continuousFocusOrigin,wantsFallback?L"; danach vollständiger Autofokus":L"");
        if(ContinuousFocusBeginMove(g_continuousFocusOrigin,CF_MOVE_ROLLBACK,reason))return TRUE;
        g_continuousFocusPaused=TRUE;ContinuousFocusSetStatus(L"Pausiert",L"Nicht bestätigte Mikrokorrektur konnte nicht sicher zurückgenommen werden.");return FALSE;
    }
    if(g_continuousFocusReferenceMetric<=0.0){int referencePosition=FocuserPosition();g_continuousFocusReferenceMetric=current;g_continuousFocusRejected=0;g_continuousFocusOrigin=referencePosition;g_continuousFocusTarget=referencePosition;g_continuousFocusLastCorrection=0;ContinuousFocusSetStatus(L"Referenz bereit",L"Stabiles Messfenster wurde als Ausgangsreferenz übernommen.");return FALSE;}
    if(g_continuousFocusLastActionTick&&GetTickCount64()-g_continuousFocusLastActionTick<8000ULL){ContinuousFocusSetStatus(L"Überwacht",L"Kurze Sperrzeit nach der letzten Motorbewegung; Bildserie läuft ohne Zusatzaufnahme weiter.");return FALSE;}
    int position=FocuserPosition();int predicted=position;BOOL predictiveAvailable=(g_continuousFocusMode==CF_PREDICTIVE||g_continuousFocusMode==CF_HYBRID)&&g_tempFitValid&&g_tempProfileCount>=3&&g_hasFocuserTemperature;
    if(predictiveAvailable){predicted=RoundedModelPosition(g_tempSlope*g_focuserTemperature+g_tempIntercept,g_safeMinPosition,g_safeMaxPosition);int delta=predicted-position;g_continuousFocusEstimatedError=(double)delta;if(delta<0?-delta>g_continuousFocusDeadband:delta>g_continuousFocusDeadband){int correction=AfsCfClampInt(delta,-g_continuousFocusMaxStep,g_continuousFocusMaxStep);g_continuousFocusBeforeMetric=current;wchar_t reason[300];wsprintfW(reason,L"Temperaturmodell: Ist %d · Modellziel %d · Mikrokorrektur %d Schritte zwischen zwei Bildern.",position,predicted,correction);if(ContinuousFocusBeginMove(position+correction,CF_MOVE_PREDICTIVE,reason))return TRUE;}}
    if(g_continuousFocusMode==CF_PREDICTIVE){ContinuousFocusSetStatus(L"Prädiktiv stabil",predictiveAvailable?L"Temperaturmodell liegt innerhalb der Totzone.":L"Noch kein belastbares Temperaturmodell verfügbar.");return FALSE;}
    double degradation=AfsCfDegradationPercent(g_continuousFocusReferenceMetric,current);
    double trigger=g_continuousFocusMinImprovement*2.0;if(trigger<3.0)trigger=3.0;
    if(degradation<trigger){g_continuousFocusEstimatedError=0.0;g_continuousFocusTarget=position;if(current<g_continuousFocusReferenceMetric)g_continuousFocusReferenceMetric=g_continuousFocusReferenceMetric*0.92+current*0.08;wchar_t reason[280],deg[32];FormatFixed(degradation,2,deg);wsprintfW(reason,L"Bildserie stabil · Abweichung %s %% · Regelqualität %d/100 · keine Korrektur nötig.",deg,confidence);ContinuousFocusSetStatus(L"Überwacht",reason);return FALSE;}
    int direction=g_continuousFocusLastDirection;if(g_continuousFocusMode==CF_HYBRID&&predictiveAvailable&&predicted!=position)direction=predicted>position?1:-1;else if(g_continuousFocusAccepted==0)direction=IsChecked(g_preferredDirCheck)?1:-1;
    int step=AfsCfStepFromDegradation(degradation,g_continuousFocusDeadband,g_continuousFocusMaxStep);g_continuousFocusEstimatedError=(double)(direction*step);int target=position+direction*step;if(target<g_safeMinPosition||target>g_safeMaxPosition){direction=-direction;target=position+direction*step;}
    if(target<g_safeMinPosition||target>g_safeMaxPosition){g_continuousFocusPaused=TRUE;ContinuousFocusSetStatus(L"Pausiert",L"Beide Korrekturrichtungen würden die sichere Fokuszone verlassen.");return FALSE;}
    g_continuousFocusBeforeMetric=current;wchar_t reason[320],deg[32];FormatFixed(degradation,2,deg);wsprintfW(reason,L"Nachhaltige Verschlechterung %s %% · Probe %d Schritte %s zwischen den Belichtungen.",deg,step,direction>0?L"nach außen":L"nach innen");return ContinuousFocusBeginMove(target,CF_MOVE_IMAGE_PROBE,reason);
}
static void ContinuousFocusTick(ULONGLONG now){
    if(!g_continuousFocusEnabled||g_continuousFocusPhase==CF_IDLE||g_continuousFocusPhase==CF_VERIFYING)return;
    if(!g_focuserConnected){g_continuousFocusPaused=TRUE;g_continuousFocusPhase=CF_IDLE;ContinuousFocusSetStatus(L"Pausiert",L"Fokussierer während der Nachführung getrennt.");return;}
    if(g_continuousFocusPhase==CF_MOVING){if(FocuserMoving())return;g_continuousFocusPhase=CF_SETTLING;g_continuousFocusSettleUntil=now+(ULONGLONG)g_continuousFocusSettleMs;ContinuousFocusSetStatus(L"Beruhigungszeit",L"Motorfahrt beendet; nächste normale Belichtung startet nach der konfigurierten Beruhigungszeit.");return;}
    if(g_continuousFocusPhase!=CF_SETTLING||now<g_continuousFocusSettleUntil)return;
    if(g_continuousFocusMoveKind==CF_MOVE_ROLLBACK){g_continuousFocusPhase=CF_IDLE;g_continuousFocusMoveKind=CF_MOVE_NONE;g_continuousFocusTarget=FocuserPosition();ContinuousFocusClearSamples();if(g_continuousFocusFallbackPending){g_continuousFocusFallbackPending=FALSE;ContinuousFocusSetStatus(L"Vollständiger Autofokus",L"Mikrokorrekturen waren nicht eindeutig; ein vollständiger Autofokus wird als sicherer Fallback gestartet.");if(TriggerAutomaticRefocus(L"Kontinuierliche Nachführung fordert vollständigen Autofokus an"))return;}if(g_continuousFocusRejected>=3){g_continuousFocusPaused=TRUE;ContinuousFocusSetStatus(L"Pausiert",L"Drei Mikrokorrekturen wurden nicht bestätigt. Benutzerfreigabe oder vollständiger Autofokus erforderlich.");return;}if(g_live&&!g_exposing)StartLiveExposureOrStop(L"Live-Fokus konnte nach der Rückkehr nicht fortgesetzt werden");return;}
    g_continuousFocusPhase=CF_VERIFYING;ContinuousFocusClearSamples();ContinuousFocusSetStatus(L"Kontrollmessung",L"Die nächsten normalen Bilder prüfen die Mikrokorrektur; es wird keine separate Fokusserie aufgenommen.");if(g_live&&!g_exposing)StartLiveExposureOrStop(L"Live-Fokus konnte nach der Mikrokorrektur nicht fortgesetzt werden");
}

static void ApplyTemperatureCompensation(ULONGLONG now){if(g_continuousFocusEnabled&&!g_continuousFocusPaused&&(g_continuousFocusMode==CF_PREDICTIVE||g_continuousFocusMode==CF_HYBRID))return;if(!g_tempCompEnabled||!g_tempFitValid||g_tempProfileCount<3||!g_hasFocuserTemperature||!g_focuserConnected||g_afActive||g_stepAssistActive||g_backlashCalActive||g_exposing||FocuserMoving()||now-g_lastTempCompMove<30000ULL)return;int current=FocuserPosition();if(current<0)return;int predicted=RoundedModelPosition(g_tempSlope*g_focuserTemperature+g_tempIntercept,g_safeMinPosition,g_safeMaxPosition);long long delta64=(long long)predicted-(long long)current;if(delta64<0&&-delta64<=(long long)g_tempCompDeadbandSteps)return;if(delta64>0&&delta64<=(long long)g_tempCompDeadbandSteps)return;if(delta64>(long long)g_tempCompMaxStep)delta64=g_tempCompMaxStep;if(delta64<-(long long)g_tempCompMaxStep)delta64=-(long long)g_tempCompMaxStep;long long requested=(long long)current+delta64;int target=requested<(long long)g_safeMinPosition?g_safeMinPosition:(requested>(long long)g_safeMaxPosition?g_safeMaxPosition:(int)requested);if(MoveFocuser(target)){g_lastTempCompMove=now;g_lastTempCompTarget=predicted;wchar_t d[220];wsprintfW(d,L"Temperaturkompensation: %d → %d (Modellziel %d)",current,target,predicted);SetStatus(d);AppendSessionEvent(L"Temperaturkompensation",d);}}
static void UpdateTempRegression(){g_tempFitValid=FALSE;g_tempSlope=g_tempIntercept=0.0;if(g_tempProfileCount<2)return;double sx=0,sy=0,sxx=0,sxy=0;for(int i=0;i<g_tempProfileCount;i++){double x=g_tempProfileT[i],y=(double)g_tempProfileP[i];if(!FiniteD(x)||!FiniteD(y))return;sx+=x;sy+=y;sxx+=x*x;sxy+=x*y;if(!FiniteD(sx)||!FiniteD(sy)||!FiniteD(sxx)||!FiniteD(sxy))return;}double n=(double)g_tempProfileCount,d=n*sxx-sx*sx;if(!FiniteD(d)||fabs(d)<1e-9)return;double slope=(n*sxy-sx*sy)/d,intercept=(sy-slope*sx)/n;if(!FiniteD(slope)||!FiniteD(intercept))return;g_tempSlope=slope;g_tempIntercept=intercept;g_tempFitValid=TRUE;}
static void AddTemperaturePoint(double t,int p){if(!FiniteD(t)||t<=-100.0||t>=100.0||p<0)return;if(g_tempProfileCount>=MAX_TEMP_PROFILE){for(int i=1;i<MAX_TEMP_PROFILE;i++){g_tempProfileT[i-1]=g_tempProfileT[i];g_tempProfileP[i-1]=g_tempProfileP[i];}g_tempProfileCount=MAX_TEMP_PROFILE-1;}g_tempProfileT[g_tempProfileCount]=t;g_tempProfileP[g_tempProfileCount]=p;g_tempProfileCount++;UpdateTempRegression();}
static void LoadTemperatureProfile(){g_tempProfileCount=0;g_tempFitValid=FALSE;wchar_t path[700];ProfilePath(path);HANDLE h=CreateFileW(path,GENERIC_READ,1,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return;DWORD size=GetFileSize(h,0);if(size==0xffffffffU||size>262144U){CloseHandle(h);return;}char* b=(char*)Alloc((SIZE_T)size+1);if(!b){CloseHandle(h);return;}DWORD got=0;if(!ReadFile(h,b,size,&got,0)){CloseHandle(h);Free(b);return;}CloseHandle(h);b[got]=0;char* line=b;while(*line){char* end=line;while(*end&&*end!='\n')end++;char save=*end;*end=0;char* s1=line;while(*s1&&*s1!=';')s1++;if(*s1){char* s2=s1+1;while(*s2&&*s2!=';')s2++;if(*s2){double t=ParseAsciiDouble(s1+1,-9999.0);int pos=ParseAsciiInt(s2+1,-1);if(t>-100.0&&t<100.0&&pos>=0)AddTemperaturePoint(t,pos);}}*end=save;if(!save)break;line=end+1;}Free(b);UpdateTempRegression();}
static void AppendTemperatureProfile(double t,int position){if(g_syntheticSelfTestActive||!FiniteD(t)||t<=-100.0||t>=100.0||position<0)return;wchar_t path[700];ProfilePath(path);HANDLE h=CreateFileW(path,GENERIC_WRITE,1,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return;DWORD size=GetFileSize(h,0);SetFilePointer(h,0,0,FILE_END);BOOL ok=TRUE;if(size==0){const char* header="Timestamp;Temperature_C;Position\r\n";ok=WriteAllHandle(h,header,(DWORD)ALen(header));}SYSTEMTIME st;GetLocalTime(&st);char line[160];int n=sprintf(line,"%04u-%02u-%02u %02u:%02u:%02u;%.3f;%d\r\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,t,position);if(n<=0||(unsigned)n>=sizeof(line)||!WriteAllHandle(h,line,(DWORD)n))ok=FALSE;CloseHandle(h);if(ok)AddTemperaturePoint(t,position);}
static void UpdateSessionMeasurement(int purpose){
    if(g_syntheticSelfTestActive)return;
    // Deliberately defocused autofocus, step-assistant and backlash frames must not
    // distort the night's best/worst live-focus statistics.
    if(purpose==1&&g_medianFwhm>0.0&&FiniteD(g_medianFwhm)){
        if(g_sessionBestFwhm<=0.0||g_medianFwhm<g_sessionBestFwhm)g_sessionBestFwhm=g_medianFwhm;
        if(g_sessionWorstFwhm<=0.0||g_medianFwhm>g_sessionWorstFwhm)g_sessionWorstFwhm=g_medianFwhm;
    }
    if(g_focuserConnected){int p=FocuserPosition();if(p>=0){if(g_sessionStartPosition<0)g_sessionStartPosition=p;g_sessionLastPosition=p;}}
    if(g_focuserConnected&&g_hasFocuserTemperature&&FiniteD(g_focuserTemperature)){
        if(!g_sessionHasTemperature){g_sessionStartTemperature=g_focuserTemperature;g_sessionHasTemperature=TRUE;}
        g_sessionLastTemperature=g_focuserTemperature;
    }
}
static void SetAfValidationState(BOOL passed,BOOL rolledBack,LPCWSTR state,LPCWSTR reason){
    g_afValidationPassed=passed;g_afRollbackPerformed=rolledBack;
    CopyWBounded(g_afValidationState,96,state?state:L"–");CopyWBounded(g_afValidationReason,320,reason?reason:L"");
}
static void RecordSuccessfulFocus(){if(!g_syntheticSelfTestActive)g_sessionAfSuccess++;g_lastAfCompleted=GetTickCount64();g_autoRefocusRetryAfter=0;g_autoRefocusFailureCount=0;g_autoRefocusPaused=FALSE;g_refocusBadFrameStreak=0;g_autoRefocusReferenceReady=TRUE;ClearAutofocusError();if(g_afAutomaticRun)lstrcpyW(g_lastAutoRefocusReason,L"automatischer Fokuslauf erfolgreich");if(g_hasFocuserTemperature&&g_afFinalValid&&g_afFinalPosition>=0){g_lastAfTemperature=g_focuserTemperature;g_hasLastAfTemperature=TRUE;AppendTemperatureProfile(g_focuserTemperature,g_afFinalPosition);}UpdateFocusProfileModelAfterSuccess();wchar_t d[220];wsprintfW(d,L"Position %d · Qualität %d/100",g_afFinalPosition,g_focusQualityScore);AppendSessionEvent(L"Autofokus erfolgreich",d);}
static void FinishStepAssistant(LPCWSTR reason){g_stepAssistActive=FALSE;g_stepAssistState=0;g_capturePurpose=0;SetWindowTextW(g_stepAssistButton,L"Schritt-Assistent");SetStatus(reason);if(g_resumeLiveAfterStep){g_resumeLiveAfterStep=FALSE;g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartLiveExposureOrStop(L"Schritt-Assistent beendet · Live-Fokus konnte nicht fortgesetzt werden");}InvalidateRect(g_main,0,FALSE);}
static void StopStepAssistant(BOOL restore,LPCWSTR reason){if(!g_stepAssistActive)return;if(!restore)g_resumeLiveAfterStep=FALSE;if(g_capturePurpose==4)AbortExposure();lstrcpyW(g_stepAssistResult,reason);if(restore&&g_focuserConnected&&FocuserPosition()!=g_stepAssistStart){if(MoveFocuser(g_stepAssistStart)){g_stepAssistState=3;SetStatus(L"Schritt-Assistent beendet · Rückfahrt zur Startposition");return;}}FinishStepAssistant(reason);}
static void StartStepAssistant(){if(g_focuserSetupReserved){NotifyUser(L"Der Schritt-Assistent ist während des ASCOM-Treiberdialogs gesperrt.",L"Treiberdialog aktiv",MB_OK|MB_ICONINFORMATION);return;}if(g_stepAssistActive){StopStepAssistant(TRUE,L"Schritt-Assistent abgebrochen");return;}if(g_afActive||g_backlashCalActive){NotifyUser(g_afActive?L"Während eines Autofokuslaufs kann der Schritt-Assistent nicht gestartet werden.":L"Während der Backlash-Kalibrierung kann der Schritt-Assistent nicht gestartet werden.",g_afActive?L"Autofokus aktiv":L"Backlash-Kalibrierung aktiv",MB_OK|MB_ICONINFORMATION);return;}g_demo=IsChecked(g_demoCheck);if(g_demo||!g_cameraConnected||!g_focuserConnected){NotifyUser(L"Der Schritt-Assistent benötigt eine verbundene Kamera und einen absoluten Fokussierer.",L"Geräte fehlen",MB_OK|MB_ICONINFORMATION);return;}if(FocuserMoving()){NotifyUser(L"Der Fokussierer bewegt sich noch.",L"Bitte warten",MB_OK|MB_ICONINFORMATION);return;}wchar_t v[64];GetWindowTextW(g_afStepEdit,v,64);UINT probeValue=0;if(!ParseStrictUIntW(v,&probeValue)||probeValue<5U||probeValue>1000000U){NotifyUser(L"Die Autofokus-Schrittweite ist ungültig.",L"Schritt-Assistent",MB_OK|MB_ICONWARNING);return;}g_stepAssistProbe=ClampI((int)probeValue,10,5000);g_stepAssistStart=FocuserPosition();int maxStep=FocuserMaxStep();long long probeLow=(long long)g_stepAssistStart-(long long)g_stepAssistProbe,probeHigh=(long long)g_stepAssistStart+(long long)g_stepAssistProbe;if(probeLow<0)probeLow=0;if(probeHigh>maxStep)probeHigh=maxStep;g_stepAssistPositions[0]=(int)probeLow;g_stepAssistPositions[1]=g_stepAssistStart;g_stepAssistPositions[2]=(int)probeHigh;if(g_stepAssistPositions[0]==g_stepAssistPositions[1]||g_stepAssistPositions[1]==g_stepAssistPositions[2]){NotifyUser(L"Die aktuelle Fokusposition liegt zu nah an einer Motorgrenze. Der Assistent benötigt Messpunkte auf beiden Seiten.",L"Motorgrenze",MB_OK|MB_ICONWARNING);return;}g_resumeLiveAfterStep=g_live;if(g_live)StopLive();g_stepAssistActive=TRUE;g_stepAssistState=1;g_stepAssistSettle=GetTickCount64()+250;g_stepAssistIndex=0;for(int i=0;i<3;i++)g_stepAssistMetrics[i]=0;SetWindowTextW(g_stepAssistButton,L"Assistent abbrechen");SetStatus(L"Schritt-Assistent · Messpunkt 1 von 3");if(!MoveFocuser(g_stepAssistPositions[0]))FinishStepAssistant(L"Schritt-Assistent konnte den Fokussierer nicht bewegen");}
static void HandleStepAssistantFrame(){if(!g_stepAssistActive)return;if(g_usedCount<3||g_medianHfr<=0){StopStepAssistant(TRUE,L"Schritt-Assistent: zu wenige geeignete Sterne");return;}g_stepAssistMetrics[g_stepAssistIndex]=g_medianHfr;g_stepAssistIndex++;if(g_stepAssistIndex<3){wchar_t s[120];wsprintfW(s,L"Schritt-Assistent · Messpunkt %d von 3",g_stepAssistIndex+1);SetStatus(s);if(MoveFocuser(g_stepAssistPositions[g_stepAssistIndex])){g_stepAssistState=1;g_stepAssistSettle=GetTickCount64()+250;}else StopStepAssistant(TRUE,L"Schritt-Assistent: Fokusbewegung fehlgeschlagen");return;}double lo=g_stepAssistMetrics[0],hi=lo;for(int i=1;i<3;i++){if(g_stepAssistMetrics[i]<lo)lo=g_stepAssistMetrics[i];if(g_stepAssistMetrics[i]>hi)hi=g_stepAssistMetrics[i];}double ratio=lo>0?hi/lo:1.0;double factor=ratio<=1.03?3.0:sqrt(0.60/(ratio-1.0));factor=ClampD(factor,0.5,3.0);int recommended=ClampI((int)(g_stepAssistProbe*factor+0.5),5,5000);wchar_t r[24],m[24];wsprintfW(r,L"%d",recommended);SetWindowTextW(g_afStepEdit,r);FormatFixed(ratio,2,m);wsprintfW(g_stepAssistResult,L"Schritt-Assistent: empfohlen %d Schritte · Spreizung %s×",recommended,m);SaveSettings();if(MoveFocuser(g_stepAssistStart)){g_stepAssistState=3;SetStatus(L"Schrittweite berechnet · Rückfahrt zur Startposition");}else FinishStepAssistant(g_stepAssistResult);}

static void SetBacklashCalibrationProgressStatus(LPCWSTR phase){wchar_t msg[260];int progress=g_backlashCalCumulative;if(progress<0)progress=0;int limit=g_backlashCalMaxReverse;if(limit<0)limit=0;if(g_simulatorMode)wsprintfW(msg,L"%s · %d von %d Schritten geprüft · Simulatorrest %d",phase?phase:L"Backlash-Kalibrierung",progress,limit,g_simBacklashRemaining);else wsprintfW(msg,L"%s · %d von %d Schritten geprüft",phase?phase:L"Backlash-Kalibrierung",progress,limit);SetStatus(msg);}
static void FinishBacklashCalibration(LPCWSTR reason){
    g_backlashCalActive=FALSE;g_backlashCalState=0;g_capturePurpose=0;CopyWBounded(g_backlashCalResult,220,reason?reason:L"Backlash-Kalibrierung beendet");SetStatus(g_backlashCalResult);AppendSessionEvent(L"Backlash-Kalibrierung",g_backlashCalResult);if(g_resumeLiveAfterBacklash){g_resumeLiveAfterBacklash=FALSE;g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartLiveExposureOrStop(L"Backlash-Kalibrierung beendet · Live-Fokus konnte nicht fortgesetzt werden");}InvalidateRect(g_main,0,FALSE);}
static void StopBacklashCalibration(BOOL restore,LPCWSTR reason){if(!g_backlashCalActive)return;if(!restore)g_resumeLiveAfterBacklash=FALSE;if(g_capturePurpose==5)AbortExposure();if(restore&&g_focuserConnected&&FocuserPosition()!=g_backlashCalStart){CopyWBounded(g_backlashCalResult,220,reason?reason:L"Backlash-Kalibrierung beendet");if(MoveFocuser(g_backlashCalStart)){g_backlashCalState=5;SetStatus(L"Backlash-Kalibrierung beendet · Rückfahrt zur Startposition");return;}}FinishBacklashCalibration(reason);}
static void StartBacklashCalibration(){if(g_focuserSetupReserved){NotifyUser(L"Die Backlash-Kalibrierung ist während des ASCOM-Treiberdialogs gesperrt.",L"Treiberdialog aktiv",MB_OK|MB_ICONINFORMATION);return;}
    if(g_backlashCalActive){StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung abgebrochen");return;}
    if(g_afActive||g_stepAssistActive){SetStatus(L"Backlash-Kalibrierung kann während eines anderen Fokusvorgangs nicht starten");return;}
    if(!g_cameraConnected||!g_focuserConnected){SetStatus(L"Backlash-Kalibrierung benötigt Kamera und absoluten Fokussierer");return;}
    if(FocuserMoving()){SetStatus(L"Backlash-Kalibrierung wartet: Fokussierer bewegt sich noch");return;}
    wchar_t v[64];UINT step=120;GetWindowTextW(g_afStepEdit,v,64);if(!ParseStrictUIntW(v,&step)||step<5U||step>1000000U)step=120;
    int probe=ClampI((int)step,40,1000);
    g_backlashCalIncrement=ClampI(probe/4,5,100);
    // A large configured simulator deadband must still be testable in a reasonable number
    // of measurement positions. This changes only the synthetic calibration resolution;
    // the real-hardware path keeps the user-derived probe increment unchanged.
    if(g_simulatorMode&&g_simBacklashSteps>0){int adaptive=(g_simBacklashSteps+79)/80;if(adaptive>g_backlashCalIncrement)g_backlashCalIncrement=ClampI(adaptive,5,100);}
    g_backlashCalStart=FocuserPosition();if(g_backlashCalStart<0)return;
    int maxStep=FocuserMaxStep();int prefer=IsChecked(g_preferredDirCheck)?1:-1;
    long long far=(long long)g_backlashCalStart+(long long)prefer*(long long)probe*4LL;
    if(far<g_safeMinPosition||far>g_safeMaxPosition){prefer=-prefer;far=(long long)g_backlashCalStart+(long long)prefer*(long long)probe*4LL;}
    if(far<g_safeMinPosition||far>g_safeMaxPosition||far<0||far>maxStep){SetStatus(L"Backlash-Kalibrierung: nicht genügend Weg innerhalb der sicheren Fokuszone");return;}
    g_backlashCalDirection=prefer;g_backlashCalFar=(int)far;g_backlashCalCumulative=0;g_backlashCalSamples=0;g_backlashCalEstimated=-1;
    for(int i=0;i<3;i++)g_backlashCalBaseline[i]=g_backlashCalCurrent[i]=0.0;
    wchar_t b[64];UINT existing=250;GetWindowTextW(g_afBacklashEdit,b,64);if(!ParseStrictUIntW(b,&existing)||existing>1000000U)existing=250;
    long long requested=(long long)existing*2LL+(long long)probe*4LL;long long minimum=(long long)probe*5LL;if(requested<minimum)requested=minimum;
    if(g_simulatorMode){long long simulatorRequired=(long long)g_simBacklashSteps+(long long)g_backlashCalIncrement;if(requested<simulatorRequired)requested=simulatorRequired;}
    long long available=prefer>0?(long long)g_backlashCalFar-(long long)g_safeMinPosition:(long long)g_safeMaxPosition-(long long)g_backlashCalFar;
    long long hardLimit=g_simulatorMode?10000LL:5000LL;if(requested>hardLimit)requested=hardLimit;if(requested>available)requested=available;
    if(requested<g_backlashCalIncrement){SetStatus(L"Backlash-Kalibrierung: sichere Fokuszone ist für die Umkehrmessung zu klein");return;}
    if(g_simulatorMode&&(long long)g_simBacklashSteps+(long long)g_backlashCalIncrement>requested){SetStatus(L"Backlash-Kalibrierung: sichere Fokuszone reicht für das konfigurierte Simulator-Backlash nicht aus");return;}
    g_backlashCalMaxReverse=(int)requested;
    g_resumeLiveAfterBacklash=g_live;if(g_live)StopLive();g_backlashCalActive=TRUE;g_backlashCalState=1;
    SetBacklashCalibrationProgressStatus(L"Backlash-Kalibrierung · Anfahrt der Messseite");
    if(!MoveFocuser(g_backlashCalFar))FinishBacklashCalibration(L"Backlash-Kalibrierung: erste Fokusbewegung fehlgeschlagen");
}
static void HandleBacklashCalibrationFrame(){
    if(!g_backlashCalActive)return;if(g_usedCount<g_refocusMinStars||g_medianHfr<=0.0){StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: zu wenige geeignete Sterne");return;}if(g_backlashCalState==2){g_backlashCalBaseline[g_backlashCalSamples++]=g_medianHfr;if(g_backlashCalSamples<3){if(!StartExposure(5))StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Baseline-Aufnahme fehlgeschlagen");return;}double a[3];for(int i=0;i<3;i++)a[i]=g_backlashCalBaseline[i];double baseline=Median(a,3);g_backlashCalBaseline[0]=baseline;g_backlashCalSamples=0;g_backlashCalCumulative=g_backlashCalIncrement;int target=g_backlashCalFar-g_backlashCalDirection*g_backlashCalCumulative;if(!CheckSafeTarget(target)||!MoveFocuser(target)){StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Umkehrbewegung fehlgeschlagen");return;}g_backlashCalState=3;g_backlashCalSettle=GetTickCount64()+350;SetBacklashCalibrationProgressStatus(L"Backlash-Kalibrierung · Umkehrspiel wird vermessen");return;}
    if(g_backlashCalState==4){g_backlashCalCurrent[g_backlashCalSamples++]=g_medianHfr;if(g_backlashCalSamples<3){if(!StartExposure(5))StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Messaufnahme fehlgeschlagen");return;}double a[3];for(int i=0;i<3;i++)a[i]=g_backlashCalCurrent[i];double cur=Median(a,3),base=g_backlashCalBaseline[0],change=base>0.0?fabs(cur-base)/base:0.0;g_backlashCalSamples=0;if(change>=0.012||fabs(cur-base)>=0.025){g_backlashCalEstimated=g_backlashCalCumulative-g_backlashCalIncrement/2;if(g_backlashCalEstimated<0)g_backlashCalEstimated=0;wchar_t v[32],msg[220];wsprintfW(v,L"%d",g_backlashCalEstimated);SetWindowTextW(g_afBacklashEdit,v);g_profileBacklash=g_backlashCalEstimated;SaveSettings();SaveFocusProfileModel();wsprintfW(msg,L"Backlash kalibriert: %d Schritte · Messauflösung ±%d · optische Änderung nach %d Schritten",g_backlashCalEstimated,g_backlashCalIncrement/2,g_backlashCalCumulative);CopyWBounded(g_backlashCalResult,220,msg);if(MoveFocuser(g_backlashCalStart)){g_backlashCalState=5;SetStatus(L"Backlash ermittelt · Rückfahrt zur Startposition");}else FinishBacklashCalibration(msg);return;}if(g_backlashCalCumulative+g_backlashCalIncrement>g_backlashCalMaxReverse){StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: innerhalb des Prüfbereichs keine eindeutige optische Bewegung erkannt");return;}g_backlashCalCumulative+=g_backlashCalIncrement;int target=g_backlashCalFar-g_backlashCalDirection*g_backlashCalCumulative;if(!CheckSafeTarget(target)||!MoveFocuser(target)){StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Prüfbewegung außerhalb der sicheren Zone");return;}g_backlashCalState=3;g_backlashCalSettle=GetTickCount64()+350;SetBacklashCalibrationProgressStatus(L"Backlash-Kalibrierung · Umkehrspiel wird vermessen");}
}
static void MakeReportBase(LPWSTR base){wchar_t dir[600];lstrcpyW(dir,g_logDir);SYSTEMTIME st;GetLocalTime(&st);wsprintfW(base,L"%s\\AF_%04u%02u%02u_%02u%02u%02u",dir,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);}
static BOOL ExportReport(LPCWSTR result){
    if(g_syntheticSelfTestActive)return TRUE;
    wchar_t base[700],csvPath[730],svgPath[730],profileW[80],gainW[32],tempW[32];
    MakeReportBase(base);lstrcpyW(csvPath,base);lstrcatW(csvPath,L".csv");lstrcpyW(svgPath,base);lstrcatW(svgPath,L".svg");
    GetWindowTextW(g_profileEdit,profileW,80);GetWindowTextW(g_gainEdit,gainW,32);
    if(g_hasFocuserTemperature)FormatFixed(g_focuserTemperature,1,tempW);else lstrcpyW(tempW,L"n/a");
    char profile[96],resultA[160],source[40],gainA[32],fitA[80],tempA[32],sdkA[100],errorCodeA[96],errorTitleA[256],errorDetailA[700],qualityA[128],seeingA[160],needA[192],fieldA[420],tiltA[96],filterA[96];
    WToAscii(profileW,profile,96);WToAscii(result,resultA,160);WToAscii(gainW,gainA,32);WToAscii(g_fitMethod,fitA,80);WToAscii(tempW,tempA,32);WToAscii(g_toupVersion,sdkA,100);WToAscii(g_lastAfErrorCode,errorCodeA,96);WToAscii(g_lastAfErrorTitle,errorTitleA,256);WToAscii(g_lastAfErrorDetail,errorDetailA,700);WToAscii(g_focusQualityLabel,qualityA,128);WToAscii(g_seeingState,seeingA,160);WToAscii(g_focusNeedLabel,needA,192);WToAscii(g_fieldAdvice,fieldA,420);WToAscii(g_tiltDirection,tiltA,96);WToAscii(g_currentFilter,filterA,96);
    WToAscii(g_simulatorMode?L"Simulator":(g_externalCameraMode?L"USB/UVC":(g_demo?L"Demo":(g_nativeActive?L"ToupTek SDK":L"ASCOM"))),source,40);
    char* buf=(char*)Alloc(32768);if(!buf){SetStatus(L"Bericht konnte nicht erstellt werden: Speicherfehler");return FALSE;}int n=0;
    n+=sprintf(buf+n,"AstroFocus Studio;3.9.0\r\nProfil;%s\r\nErgebnis;%s\r\nKameraquelle;%s\r\nToupTek_SDK;%s\r\nBelichtung_ms;%.0f\r\nGain;%s\r\nStartposition;%d\r\nBestposition;%d\r\nFit;%s\r\nR2;%.5f\r\nKurvenqualitaet;%.3f\r\nFokusunsicherheit_Schritte;%.3f\r\nLeaveOneOut_Schritte;%.3f\r\nReduziertes_Chi2;%.5f\r\nFit_Inlier;%d\r\nFit_Ausreisser;%d\r\nAdaptive_Zusatzaufnahmen;%d\r\nAutofokus_Qualitaet_Score;%d\r\nAutofokus_Qualitaet;%s\r\nSeeing_Index;%.2f\r\nSeeing_Status;%s\r\nTransparenz_Index;%.2f\r\nRefokus_Ampel_Score;%d\r\nRefokus_Ampel;%s\r\nTemperatur_C;%s\r\nTemperaturprofil_Punkte;%d\r\nTemperaturkoeffizient_Schritte_pro_C;%.4f\r\nTemperaturkompensation_Aktiv;%d\r\nAutoStartPosition_Aktiv;%d\r\nTilt_Delta_FWHM_px;%.4f\r\nTilt_Konfidenz;%.3f\r\nTilt_Richtung;%s\r\nFeldkruemmung_px;%.4f\r\nFeldasymmetrie_px;%.4f\r\nFeldqualitaet_Score;%.2f\r\nFeldhinweis;%s\r\nProfilmodell_Laeufe;%d\r\nProfilmodell_TypischePosition;%d\r\nProfilmodell_TypischeFWHM;%.4f\r\nProfilmodell_EmpfohleneSchrittweite;%d\r\nProfilmodell_Backlash;%d\r\nAktueller_Filter;%s\r\nFilteroffsets;%d\r\nBahtinov_Offset_px;%.4f\r\nBild_FWHM_px;%.4f\r\nBild_HFR_px;%.4f\r\nVerwendete_Sterne;%d\r\nAutofokus_Metrik;%s\r\nAutofokusFehlerCode=%s\r\nAutofokusFehlerTitel=%s\r\nAutofokusFehlerDetail=%s\r\n\r\nIndex;Position;HFR_Metrik;HFR_Sigma;FWHM_Metrik;FWHM_Sigma;Verwendete_Sterne;Aufnahmen;Standardresiduum;Ausreisser\r\n",profile,resultA,source,sdkA,g_lastExposureSeconds*1000.0,gainA,g_afStartPosition,g_afBestPosition,fitA,g_fitR2,g_fitConfidence,g_fitFocusSigma,g_fitFocusSigmaLoo,g_fitReducedChi2,g_fitInliers,g_fitOutliers,g_afAdaptiveSamplesAdded,g_focusQualityScore,qualityA,g_seeingIndex,seeingA,g_transparencyIndex,g_focusNeedScore,needA,tempA,g_tempProfileCount,g_tempFitValid?g_tempSlope:0.0,g_tempCompEnabled,g_autoStartPositionEnabled,g_tiltValid?g_tiltMagnitude:0.0,g_tiltConfidence,tiltA,g_fieldCurvature,g_fieldAsymmetry,g_fieldQualityScore,fieldA,g_profileSuccessfulRuns,g_profileTypicalPosition,g_profileTypicalFwhm,g_profileRecommendedStep,g_profileBacklash,filterA,g_filterOffsetCount,g_bahtinovValid?g_bahtinovOffset:0.0,g_medianFwhm,g_medianHfr,g_usedCount,g_afRunUsesSelectedStar?"Manuell gewaehlter Fokusstern":"Feldmedian",errorCodeA,errorTitleA,errorDetailA);
    for(int i=0;i<g_afPointCount;i++)n+=sprintf(buf+n,"%d;%d;%.5f;%.5f;%.5f;%.5f;%d;%d;%.5f;%d\r\n",i+1,g_afPositions[i],g_afMetrics[i],g_afMetricSigma[i],g_afFwhmMetrics[i],g_afFwhmSigma[i],g_afUsedMetrics[i],g_afSamplesPerPoint[i],g_afResiduals[i],g_afOutliers[i]?1:0);
    n+=sprintf(buf+n,"\r\nZone;Median_FWHM;Sterne\r\n");for(int z=0;z<9;z++)n+=sprintf(buf+n,"%d;%.5f;%d\r\n",z+1,g_zoneFwhm[z],g_zoneCount[z]);
    BOOL csvOk=WriteTextFile(csvPath,buf);Free(buf);
    char* svg=(char*)Alloc(65536);if(!svg){SetStatus(L"SVG-Bericht konnte nicht erstellt werden: Speicherfehler");return FALSE;}int m=0;
    m+=sprintf(svg+m,"<svg xmlns='http://www.w3.org/2000/svg' width='1000' height='650' viewBox='0 0 1000 650'><rect width='1000' height='650' fill='#171c24'/><text x='40' y='42' fill='#f5f7fa' font-family='Segoe UI' font-size='25'>AstroFocus Studio 3.9.0 Engine</text><text x='40' y='72' fill='#aeb8c6' font-family='Segoe UI' font-size='16'>%s - %s</text><text x='70' y='101' fill='#91a6bf' font-family='Segoe UI' font-size='14'>HFR grün · FWHM blau · ±1σ-Fehlerbalken · rotes × Ausreißer · □ Kontrollmedian</text><rect x='70' y='115' width='860' height='400' fill='#11161d' stroke='#465060'/>",profile,resultA);
    double ymin=1e30,ymax=-1e30;int valid=0;int pmin=0,pmax=1;
    if(g_afPointCount>0){pmin=g_afPositions[0];pmax=g_afPositions[g_afPointCount-1];if(pmax<pmin){int tmp=pmin;pmin=pmax;pmax=tmp;}if(pmax==pmin)pmax++;}
    for(int i=0;i<g_afPointCount;i++){
        if(g_afMetrics[i]>0.0){double lo=g_afMetrics[i]-g_afMetricSigma[i],hi=g_afMetrics[i]+g_afMetricSigma[i];if(lo<ymin)ymin=lo;if(hi>ymax)ymax=hi;valid++;}
        if(g_afFwhmMetrics[i]>0.0){double lo=g_afFwhmMetrics[i]-g_afFwhmSigma[i],hi=g_afFwhmMetrics[i]+g_afFwhmSigma[i];if(lo<ymin)ymin=lo;if(hi>ymax)ymax=hi;valid++;}
    }
    if(valid){
        for(int k=0;k<=100;k++){double pos=pmin+(pmax-pmin)*(double)k/100.0,xn=(pos-g_fitCenterPosition)/(g_fitScale>0.0?g_fitScale:1.0);if(g_fitValid){double y=AfEvalModel(g_fitModel,g_fitParams,xn);if(y>0.0){if(y<ymin)ymin=y;if(y>ymax)ymax=y;}}if(g_fitFwhmValid){double y=AfEvalModel(g_fitFwhmModel,g_fitFwhmParams,xn);if(y>0.0){if(y<ymin)ymin=y;if(y>ymax)ymax=y;}}}
        if(ymax<=ymin)ymax=ymin+1.0;double ypad=(ymax-ymin)*0.14;ymin-=ypad;if(ymin<0.0)ymin=0.0;ymax+=ypad;
        if(g_fitValid&&g_fitFocusSigma>0.0){double lo=(double)g_afBestPosition-g_fitFocusSigma,hi=(double)g_afBestPosition+g_fitFocusSigma;if(lo<pmin)lo=pmin;if(hi>pmax)hi=pmax;double lx=70.0+(lo-pmin)*860.0/(pmax-pmin),hx=70.0+(hi-pmin)*860.0/(pmax-pmin);if(hx<lx){double tmp=lx;lx=hx;hx=tmp;}m+=sprintf(svg+m,"<rect x='%.1f' y='115' width='%.1f' height='400' fill='#ffc85a' fill-opacity='0.10'/><line x1='%.1f' y1='115' x2='%.1f' y2='515' stroke='#ffc85a' stroke-dasharray='5,5'/><line x1='%.1f' y1='115' x2='%.1f' y2='515' stroke='#ffc85a' stroke-dasharray='5,5'/>",lx,hx-lx<1.0?1.0:hx-lx,lx,lx,hx,hx);}
        for(int k=0;k<=4;k++){int y=115+k*100;m+=sprintf(svg+m,"<line x1='70' y1='%d' x2='930' y2='%d' stroke='#303946'/>",y,y);int x=70+k*215;m+=sprintf(svg+m,"<line x1='%d' y1='115' x2='%d' y2='515' stroke='#303946'/>",x,x);}
        if(g_fitValid){m+=sprintf(svg+m,"<path d='");for(int k=0;k<=160;k++){double pos=pmin+(pmax-pmin)*(double)k/160.0,xn=(pos-g_fitCenterPosition)/(g_fitScale>0.0?g_fitScale:1.0),yv=AfEvalModel(g_fitModel,g_fitParams,xn),xx=70.0+(pos-pmin)*860.0/(pmax-pmin),yy=515.0-(yv-ymin)*400.0/(ymax-ymin);if(yy<115.0)yy=115.0;if(yy>515.0)yy=515.0;m+=sprintf(svg+m,k?" L %.1f %.1f":"M %.1f %.1f",xx,yy);}m+=sprintf(svg+m,"' fill='none' stroke='#66dda3' stroke-width='2'/>");}
        if(g_fitFwhmValid){m+=sprintf(svg+m,"<path d='");for(int k=0;k<=160;k++){double pos=pmin+(pmax-pmin)*(double)k/160.0,xn=(pos-g_fitCenterPosition)/(g_fitScale>0.0?g_fitScale:1.0),yv=AfEvalModel(g_fitFwhmModel,g_fitFwhmParams,xn),xx=70.0+(pos-pmin)*860.0/(pmax-pmin),yy=515.0-(yv-ymin)*400.0/(ymax-ymin);if(yy<115.0)yy=115.0;if(yy>515.0)yy=515.0;m+=sprintf(svg+m,k?" L %.1f %.1f":"M %.1f %.1f",xx,yy);}m+=sprintf(svg+m,"' fill='none' stroke='#54a4ff' stroke-width='2'/>");}
        for(int i=0;i<g_afPointCount;i++){
            double baseX=70.0+(g_afPositions[i]-pmin)*860.0/(pmax-pmin);int isOut=g_afOutliers[i]?1:0;
            if(g_afMetrics[i]>0.0){double xx=baseX-3.0,yy=515.0-(g_afMetrics[i]-ymin)*400.0/(ymax-ymin),sy=g_afMetricSigma[i]>0.0?g_afMetricSigma[i]*400.0/(ymax-ymin):0.0;if(sy>0.0&&sy<7.0)sy=7.0;if(sy>133.0)sy=133.0;double y1=yy-sy,y2=yy+sy;if(y1<115.0)y1=115.0;if(y2>515.0)y2=515.0;if(sy>0.0)m+=sprintf(svg+m,"<line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='%s'/><line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='%s'/><line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='%s'/>",xx,y1,xx,y2,isOut?"#ff6b77":"#66dda3",xx-4,y1,xx+4,y1,isOut?"#ff6b77":"#66dda3",xx-4,y2,xx+4,y2,isOut?"#ff6b77":"#66dda3");if(isOut)m+=sprintf(svg+m,"<line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='#ff6b77' stroke-width='2'/><line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='#ff6b77' stroke-width='2'/>",xx-7,yy-7,xx+7,yy+7,xx-7,yy+7,xx+7,yy-7);else m+=sprintf(svg+m,"<circle cx='%.1f' cy='%.1f' r='4' fill='none' stroke='#66dda3' stroke-width='2'/>",xx,yy);}
            if(g_afFwhmMetrics[i]>0.0){double xx=baseX+3.0,yy=515.0-(g_afFwhmMetrics[i]-ymin)*400.0/(ymax-ymin),sy=g_afFwhmSigma[i]>0.0?g_afFwhmSigma[i]*400.0/(ymax-ymin):0.0;if(sy>0.0&&sy<8.0)sy=8.0;if(sy>133.0)sy=133.0;double y1=yy-sy,y2=yy+sy;if(y1<115.0)y1=115.0;if(y2>515.0)y2=515.0;if(sy>0.0)m+=sprintf(svg+m,"<line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='%s'/><line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='%s'/><line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='%s'/>",xx,y1,xx,y2,isOut?"#ff6b77":"#54a4ff",xx-4,y1,xx+4,y1,isOut?"#ff6b77":"#54a4ff",xx-4,y2,xx+4,y2,isOut?"#ff6b77":"#54a4ff");if(isOut)m+=sprintf(svg+m,"<line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='#ff6b77' stroke-width='2'/><line x1='%.1f' y1='%.1f' x2='%.1f' y2='%.1f' stroke='#ff6b77' stroke-width='2'/>",xx-8,yy-8,xx+8,yy+8,xx-8,yy+8,xx+8,yy-8);else m+=sprintf(svg+m,"<circle cx='%.1f' cy='%.1f' r='5' fill='none' stroke='#54a4ff' stroke-width='2'/>",xx,yy);}
        }
        double bx=70.0+(g_afBestPosition-pmin)*860.0/(pmax-pmin);m+=sprintf(svg+m,"<line x1='%.1f' y1='115' x2='%.1f' y2='515' stroke='#ee73ca' stroke-width='2'/><text x='70' y='552' fill='#8fdcf4' font-family='Segoe UI' font-size='16'>Bestposition: %d ± %.1f Schritte · R²: %.3f · Kurvenqualität: %.2f</text><text x='70' y='579' fill='#aeb8c6' font-family='Segoe UI' font-size='15'>Fit: %s · χ²red: %.2f · Leave-one-out: ± %.1f · Inlier/Ausreißer: %d/%d</text>",bx,bx,g_afBestPosition,g_fitFocusSigma,g_fitR2,g_fitConfidence,fitA,g_fitReducedChi2,g_fitFocusSigmaLoo,g_fitInliers,g_fitOutliers);
        m+=sprintf(svg+m,"<text x='70' y='612' fill='#91a6bf' font-family='Segoe UI' font-size='13'>Fokusposition: %d bis %d Schritte · Wertebereich: %.2f bis %.2f px</text>",pmin,pmax,ymin,ymax);
    }else m+=sprintf(svg+m,"<text x='320' y='330' fill='#aeb8c6' font-family='Segoe UI' font-size='22'>Keine Autofokuskurve vorhanden</text>");
    sprintf(svg+m,"</svg>");BOOL svgOk=WriteTextFile(svgPath,svg);Free(svg);BOOL ok=csvOk&&svgOk;SetStatus(ok?L"Diagnosebericht als CSV und SVG im Ordner Logs gespeichert":L"CSV/SVG-Bericht konnte nicht vollständig geschrieben werden");return ok;
}
static void ContinueAfterMove(){g_settleUntil=GetTickCount64()+600;g_afState=12;}
static BOOL AdjustAutofocusScan(){
    if(g_afPointCount<5)return FALSE;
    int minIndex=-1;double minMetric=1e30;for(int i=0;i<g_afPointCount;i++)if(g_afMetrics[i]>0.0&&g_afMetrics[i]<minMetric){minMetric=g_afMetrics[i];minIndex=i;}
    if(minIndex<0)return FALSE;
    int half=g_afPointCount/2,maxStep=FocuserMaxStep();int low=g_safeMinPosition<0?0:g_safeMinPosition,high=g_safeMaxPosition>maxStep?maxStep:g_safeMaxPosition;if(low<0)low=0;if(high>maxStep)high=maxStep;
    BOOL edge=minIndex<=1||minIndex>=g_afPointCount-2;int newStep=g_afStep,newCenter=g_afPositions[minIndex];LPCWSTR action=0;
    if(edge&&g_afRecenterCount<3){g_afRecenterCount++;action=L"Minimum lag am Rand · Messbereich wird neu zentriert";}
    else if(g_afExpansionCount<2){
        int proposed=(g_afStep*3+1)/2;if(proposed<=g_afStep)proposed=g_afStep+1;int maxAllowed=(high-low)/(2*half);if(proposed>maxAllowed)proposed=maxAllowed;if(proposed<=g_afStep)return FALSE;
        newStep=proposed;g_afExpansionCount++;action=L"Fokuskurve war zu flach · Messbereich wird erweitert";
    }else return FALSE;
    int span=half*newStep;if(high-low<span*2)return FALSE;newCenter=ClampI(newCenter,low+span,high-span);
    int oldCenter=g_afPositions[half];if(newCenter==oldCenter&&newStep==g_afStep)return FALSE;g_afStep=newStep;
    for(int i=0;i<g_afPointCount;i++){g_afPositions[i]=newCenter+(i-half)*g_afStep;g_afMetrics[i]=0.0;g_afFwhmMetrics[i]=0.0;g_afMetricSigma[i]=0.0;g_afFwhmSigma[i]=0.0;g_afResiduals[i]=0.0;g_afFwhmResiduals[i]=0.0;g_afOutliers[i]=FALSE;g_afUsedMetrics[i]=0;g_afSamplesPerPoint[i]=0;}
    g_afPointIndex=0;g_afSampleIndex=0;g_afRetryCount=0;g_fitValid=FALSE;g_fitFwhmValid=FALSE;g_fitFwhmA=g_fitFwhmB=g_fitFwhmC=g_fitFwhmR2=0.0;
    wchar_t status[260];wsprintfW(status,L"Autofokus: %s (Zentrierung %d/3, Erweiterung %d/2, Schritt %d)",action,g_afRecenterCount,g_afExpansionCount,g_afStep);SetStatus(status);WriteSimulatorStage(edge?"51 autofocus scan recentered":"52 autofocus scan expanded");BeginMoveSequence(g_afPositions[0],1);return TRUE;
}

static void CompleteAfPoint(){
    double vals[MAX_AF_SAMPLES],fv[MAX_AF_SAMPLES];int n=g_afSampleIndex,used=0;
    for(int i=0;i<n;i++){vals[i]=g_afSampleMetrics[i];fv[i]=g_afFwhmSampleMetrics[i];used+=g_afUsedSampleMetrics[i];}
    double medianH=Median(vals,n),medianF=Median(fv,n);int meanUsed=n?used/n:0;
    double sigmaH=AfRobustStandardError(vals,n,medianH,meanUsed),sigmaF=AfRobustStandardError(fv,n,medianF,meanUsed);
    int adaptiveLimit=g_afSamples+2;if(adaptiveLimit>MAX_AF_SAMPLES)adaptiveLimit=MAX_AF_SAMPLES;
    double relH=medianH>0?sigmaH/medianH:0.0,relF=medianF>0?sigmaF/medianF:0.0;
    BOOL unstable=n>=2&&(relH>0.030||relF>0.035);BOOL sparse=!g_afRunUsesSelectedStar&&meanUsed<6;
    if(n<adaptiveLimit&&(unstable||sparse)){
        g_afAdaptiveSamplesAdded++;wchar_t status[260],a[32],b[32];FormatFixed(relH*100.0,1,a);FormatFixed(relF*100.0,1,b);
        wsprintfW(status,L"Autofokus: Messpunkt %d wird adaptiv nachgemessen · Streuung HFR %s %% / FWHM %s %% · %d Sterne",g_afPointIndex+1,a,b,meanUsed);SetStatus(status);
        if(!StartExposure(2))StopAutofocus(TRUE,L"Autofokus: adaptive Nachmessung konnte nicht gestartet werden");return;
    }
    g_afMetrics[g_afPointIndex]=medianH;g_afFwhmMetrics[g_afPointIndex]=medianF;g_afMetricSigma[g_afPointIndex]=sigmaH;g_afFwhmSigma[g_afPointIndex]=sigmaF;g_afUsedMetrics[g_afPointIndex]=meanUsed;g_afSamplesPerPoint[g_afPointIndex]=n;g_afPointIndex++;g_afSampleIndex=0;
    if(g_afPointIndex<g_afPointCount){BeginMoveSequence(g_afPositions[g_afPointIndex],1);}
    else{
        int minIndex=-1;double minMetric=1e30;for(int i=0;i<g_afPointCount;i++)if(g_afMetrics[i]>0.0&&g_afMetrics[i]<minMetric){minMetric=g_afMetrics[i];minIndex=i;}
        // Do not accept a mathematically plausible fit when the measured minimum lies at the scan edge.
        // First re-centre the entire scan so that the focus minimum is visibly and numerically bracketed.
        if((minIndex<=1||minIndex>=g_afPointCount-2)&&AdjustAutofocusScan())return;
        g_fitValid=FitAutofocus();InvalidateRect(g_main,0,FALSE);if(!g_fitValid){if(AdjustAutofocusScan())return;SetAfValidationState(FALSE,TRUE,L"Kurve abgelehnt",L"Keine beidseitig ausreichende Fokuskurve; Startposition wird wiederhergestellt.");StopAutofocus(TRUE,L"Keine beidseitig ausreichende Fokuskurve · Rückkehr zur Startposition");return;}g_afVerificationCount=0;g_afVerificationRetryCount=0;g_afVerificationTarget=ClampI(g_afSamples,3,MAX_AF_SAMPLES);SetAfValidationState(FALSE,FALSE,L"Kontrollmessung läuft",L"Bestposition wurde angefahren; mehrere Kontrollaufnahmen prüfen das Ergebnis gegen Kurvenmodell und Ausgangsfokus.");BeginMoveSequence(g_afBestPosition,2);
    }
}
static void HandleAutofocusFrame(int purpose){
    double metricH=0.0,metricF=0.0;int metricStars=0;BOOL metricOk=CurrentAutofocusMetric(g_afRunUsesSelectedStar,&metricH,&metricF,&metricStars);
    if(purpose==2){
        if(!metricOk){
            if(g_afRetryCount<2){g_afRetryCount++;AutoTuneExposure();SetStatus(g_afRunUsesSelectedStar?L"Ausgewählter Fokusstern nicht sicher erkannt · Aufnahme wird wiederholt":L"Zu wenige geeignete Sterne · Aufnahme wird wiederholt");if(!StartExposure(2))StopAutofocus(TRUE,L"Autofokus: Wiederholungsbelichtung konnte nicht gestartet werden");return;}
            StopAutofocus(TRUE,g_afRunUsesSelectedStar?L"Ausgewählter Fokusstern nach drei Versuchen nicht erkannt · Rückkehr zur Startposition":L"Messpunkt nach drei Versuchen nicht zuverlässig · Rückkehr zur Startposition");return;
        }
        g_afRetryCount=0;g_afSampleMetrics[g_afSampleIndex]=metricH;g_afFwhmSampleMetrics[g_afSampleIndex]=metricF;g_afUsedSampleMetrics[g_afSampleIndex]=metricStars;g_afSampleIndex++;if(g_afSampleIndex>=g_afSamples)CompleteAfPoint();else if(!StartExposure(2))StopAutofocus(TRUE,L"Autofokus: nächste Messbelichtung konnte nicht gestartet werden");
    }else if(purpose==3){
        if(!metricOk){
            if(g_afVerificationRetryCount<2){g_afVerificationRetryCount++;SetStatus(g_afRunUsesSelectedStar?L"Fokusstern in der Kontrollmessung nicht sicher erkannt · Wiederholung":L"Kontrollmessung enthält zu wenige geeignete Sterne · Wiederholung");if(!StartExposure(3))StopAutofocus(TRUE,L"Autofokus: Kontrollbelichtung konnte nicht wiederholt werden");return;}
            StopAutofocus(TRUE,g_afRunUsesSelectedStar?L"Ausgewählter Fokusstern in der Kontrollmessung verloren · Rückkehr zur Startposition":L"Kontrollmessung enthält zu wenige geeignete Sterne · Rückkehr zur Startposition");return;
        }
        g_afVerificationRetryCount=0;g_afVerificationHfr[g_afVerificationCount]=metricH;g_afVerificationFwhm[g_afVerificationCount]=metricF;g_afVerificationCount++;
        if(g_afVerificationCount<g_afVerificationTarget){wchar_t st[180];wsprintfW(st,L"Autofokus: Kontrollmessung %d von %d an Bestposition %d",g_afVerificationCount,g_afVerificationTarget,g_afBestPosition);SetStatus(st);if(!StartExposure(3))StopAutofocus(TRUE,L"Autofokus: nächste Kontrollbelichtung konnte nicht gestartet werden");return;}
        double h[MAX_AF_SAMPLES],f[MAX_AF_SAMPLES];for(int i=0;i<g_afVerificationCount;i++){h[i]=g_afVerificationHfr[i];f[i]=g_afVerificationFwhm[i];}double finalH=Median(h,g_afVerificationCount),finalF=Median(f,g_afVerificationCount);
        double expectedH=g_afExpectedHfr>0?g_afExpectedHfr:1e30,expectedF=g_afExpectedFwhm>0?g_afExpectedFwhm:1e30;
        BOOL modelOk=finalH<=expectedH*1.30+0.08&&finalF<=expectedF*1.35+0.12;
        double predictedImprovementH=g_beforeHfr>0&&expectedH<1e20?g_beforeHfr/expectedH:1.0,predictedImprovementF=g_beforeFwhm>0&&expectedF<1e20?g_beforeFwhm/expectedF:1.0;
        BOOL startOkH=g_beforeHfr<=0||(predictedImprovementH>1.08?finalH<=g_beforeHfr*0.98:finalH<=g_beforeHfr*1.10);
        BOOL startOkF=g_beforeFwhm<=0||(predictedImprovementF>1.08?finalF<=g_beforeFwhm*0.98:finalF<=g_beforeFwhm*1.12);
        if(modelOk&&startOkH&&startOkF){
            BOOL selectedMode=g_afRunUsesSelectedStar;g_afFinalValid=TRUE;g_afFinalHfr=finalH;g_afFinalFwhm=finalF;g_afFinalPosition=FocuserPosition();CalculateAutofocusQualityScore(finalF,finalH,metricStars,FocusStability());{wchar_t vr[320],vh[32],vf[32],eh[32],ef[32];FormatFixed(finalH,2,vh);FormatFixed(finalF,2,vf);FormatFixed(g_afExpectedHfr,2,eh);FormatFixed(g_afExpectedFwhm,2,ef);wsprintfW(vr,L"Kontrollmedian bestätigt Bestposition %d: HFR %s px (Modell %s), FWHM %s px (Modell %s).",g_afFinalPosition,vh,eh,vf,ef);SetAfValidationState(TRUE,FALSE,L"Bestätigt",vr);}RecordSuccessfulFocus();BOOL reportSaved=ExportReport(L"Autofokus erfolgreich");g_lastGoodFwhm=finalF;g_continuousFocusReferenceMetric=AfsCfMetric(finalF,finalH);g_continuousFocusBeforeMetric=0.0;g_continuousFocusEstimatedError=0.0;g_continuousFocusDriftStepsPerMinute=0.0;g_continuousFocusLastAcceptedTick=0;g_continuousFocusSampleCount=0;g_continuousFocusRejected=0;g_continuousFocusFallbackPending=FALSE;g_continuousFocusPaused=FALSE;g_continuousFocusPhase=CF_IDLE;g_continuousFocusMoveKind=CF_MOVE_NONE;g_continuousFocusOrigin=g_afFinalPosition;g_continuousFocusTarget=g_afFinalPosition;g_continuousFocusLastCorrection=0;CopyWBounded(g_continuousFocusState,96,g_continuousFocusEnabled?L"Referenz übernommen":L"Deaktiviert");CopyWBounded(g_continuousFocusReason,320,L"Bestätigter Autofokus wurde als neue Referenz der kontinuierlichen Nachführung übernommen.");g_afActive=FALSE;g_afState=0;g_afRunUsesSelectedStar=FALSE;g_afAutomaticRun=FALSE;SetWindowTextW(g_afButton,L"Autofokus starten");wchar_t done[1100],a[32],b[32],c[32],d[32],e[32],q[32],su[32],sl[32],chi[32];FormatFixed(g_beforeFwhm,2,a);FormatFixed(finalF,2,b);FormatFixed(g_beforeHfr,2,c);FormatFixed(finalH,2,d);FormatFixed(g_fitR2,3,e);FormatFixed(g_fitConfidence,2,q);FormatFixed(g_fitFocusSigma,1,su);FormatFixed(g_fitFocusSigmaLoo,1,sl);FormatFixed(g_fitReducedChi2,2,chi);wsprintfW(done,L"Autofokus erfolgreich.\n\nMetrik: %s\nVorher: FWHM %s px · HFR %s px\nKontrollmedian (%d Aufnahmen): FWHM %s px · HFR %s px\nBestposition: %d ± %s Schritte\nModell: %s\nKurvenqualität: %s · R² %s · χ²red %s\nLeave-one-out: ± %s Schritte\nInlier/Ausreißer: %d/%d · adaptive Zusatzaufnahmen: %d\nGesamtqualität: %d/100 · %s\nNeuzentrierungen: %d · Bereichserweiterungen: %d\n\n%s",selectedMode?L"manuell gewählter Fokusstern":L"Feldmedian",a,c,g_afVerificationCount,b,d,g_afFinalPosition,su,g_fitMethod,q,e,chi,sl,g_fitInliers,g_fitOutliers,g_afAdaptiveSamplesAdded,g_focusQualityScore,g_focusQualityLabel,g_afRecenterCount,g_afExpansionCount,reportSaved?L"CSV- und SVG-Bericht wurden gespeichert.":L"Der Fokuslauf war erfolgreich, der CSV/SVG-Bericht konnte jedoch nicht vollständig gespeichert werden.");NotifyUser(done,L"Vorher-/Nachher-Vergleich",MB_OK|MB_ICONINFORMATION);SetStatus(L"Autofokus erfolgreich · Minimum beidseitig vermessen · Kontrollmedian bestätigt");InvalidateRect(g_main,0,FALSE);if(g_resumeLiveAfterAf){g_resumeLiveAfterAf=FALSE;g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartLiveExposureOrStop(L"Autofokus erfolgreich · Live-Fokus konnte nicht fortgesetzt werden");}}
        else {wchar_t vr[320],vh[32],vf[32],bh[32],bf[32];FormatFixed(finalH,2,vh);FormatFixed(finalF,2,vf);FormatFixed(g_beforeHfr,2,bh);FormatFixed(g_beforeFwhm,2,bf);wsprintfW(vr,L"Kontrollmedian verworfen: HFR %s px / FWHM %s px; Ausgangswert HFR %s px / FWHM %s px. Startposition wird wiederhergestellt.",vh,vf,bh,bf);SetAfValidationState(FALSE,FALSE,L"Abgelehnt · Rollback ausstehend",vr);StopAutofocus(TRUE,L"Kontrollmedian bestätigt die Fokuskurve nicht · Rückkehr zur Startposition");}
    }
}
static void AutofocusNotice(LPCWSTR message,LPCWSTR title,UINT flags){if(g_afAutomaticRequest)SetStatus(message);else NotifyUser(message,title,flags);}
static void StartAutofocus(){
    WriteSimulatorStage("40 autofocus request received");if(g_focuserSetupReserved){SetAutofocusError(L"AF_FOCUSER_SETUP_ACTIVE",L"ASCOM-Treiberdialog aktiv",L"Beende zuerst den Treiberdialog, bevor ein Autofokuslauf gestartet wird.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONINFORMATION);return;}if(!g_afAutomaticRequest)g_afAutomaticRun=FALSE;
    if(g_afActive){StopAutofocus(TRUE,L"Autofokus abgebrochen · Rückkehr zur Startposition");return;}
    if(g_stepAssistActive){SetAutofocusError(L"AF_ASSISTANT_ACTIVE",L"Schritt-Assistent aktiv",L"Bitte zuerst den Schritt-Assistenten beenden.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONINFORMATION);return;}
    if(g_backlashCalActive){SetAutofocusError(L"AF_BACKLASH_CAL_ACTIVE",L"Backlash-Kalibrierung aktiv",L"Bitte zuerst die Backlash-Kalibrierung beenden.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONINFORMATION);return;}
    LoadTemperatureProfile();g_demo=IsChecked(g_demoCheck);
    if(g_demo){SetAutofocusError(L"AF_DEMO_MODE",L"Demo-Modus ohne Motor",L"Der einfache Demo-Modus simuliert keinen Motor. Aktiviere stattdessen den vollständigen Simulator.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONINFORMATION);return;}
    if(!g_cameraConnected){SetAutofocusError(L"AF_CAMERA_NOT_CONNECTED",L"Kamera nicht verbunden",L"Für den Autofokus muss die Kamera verbunden sein.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONINFORMATION);return;}if(!g_focuserConnected){SetAutofocusError(L"AF_FOCUSER_NOT_CONNECTED",L"Fokussierer nicht verbunden",L"Für den Autofokus muss der Fokussierer verbunden sein.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONINFORMATION);return;}
    if(!g_simulatorMode&&(!g_focuserRuntime.positionKnown||g_cachedFocuserPosition<0)){SetAutofocusError(L"AF_POSITION_UNKNOWN",L"Fokusposition unbekannt",L"Die aktuelle Fokusposition ist nach einer Trennung oder Zeitüberschreitung nicht sicher bekannt. Fokussierer neu verbinden oder referenzieren.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}
    if(FocuserMoving()){SetAutofocusError(L"AF_FOCUSER_BUSY",L"Fokussierer meldet Bewegung noch nicht beendet",L"Der Fokussierer bewegt sich noch. Bitte warten, bis der Treiber IsMoving=false meldet.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONINFORMATION);return;}
    if(!g_frameReady){SetAutofocusError(L"AF_NO_REFERENCE_FRAME",L"Wartet auf erste Referenzmessung",L"Vor dem Autofokus muss mindestens ein analysiertes Kamerabild vorliegen. Bitte Live-Fokus starten.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}
    wchar_t v[64];UINT parsed=0;GetWindowTextW(g_afPointsEdit,v,64);if(!ParseStrictUIntW(v,&parsed)||parsed<5U||parsed>MAX_AF_POINTS||!(parsed&1U)){SetAutofocusError(L"AF_INVALID_POINT_COUNT",L"Ungültige Messpunktzahl",L"Die Messpunktzahl muss ungerade sein und zwischen 5 und 15 liegen.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}g_afPointCount=(int)parsed;
    GetWindowTextW(g_afStepEdit,v,64);if(!ParseStrictUIntW(v,&parsed)||parsed<5U||parsed>1000000U){SetAutofocusError(L"AF_INVALID_STEP",L"Ungültige Autofokus-Schrittweite",L"Die Autofokus-Schrittweite muss zwischen 5 und 1000000 liegen.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}g_afStep=(int)parsed;
    GetWindowTextW(g_afBacklashEdit,v,64);if(!ParseStrictUIntW(v,&parsed)||parsed>1000000U){SetAutofocusError(L"AF_INVALID_BACKLASH",L"Ungültige Backlash-Kompensation",L"Die Backlash-Kompensation muss zwischen 0 und 1000000 liegen.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}g_afBacklash=(int)parsed;
    GetWindowTextW(g_afSamplesEdit,v,64);if(!ParseStrictUIntW(v,&parsed)||parsed<1U||parsed>MAX_AF_SAMPLES){SetAutofocusError(L"AF_INVALID_SAMPLE_COUNT",L"Ungültige Sample-Anzahl",L"Die Anzahl Aufnahmen pro Messpunkt muss zwischen 1 und 5 liegen.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}g_afSamples=(int)parsed;
    BOOL runSelected=g_afUseSelectedStar;double preH=0.0,preF=0.0;int preStars=0;
    if(!CurrentAutofocusMetric(runSelected,&preH,&preF,&preStars)){
        if(runSelected)SetAutofocusError(L"AF_FOCUS_STAR_LOST",L"Fokusstern verloren",L"Der manuell gewählte Fokusstern ist im aktuellen Bild nicht zuverlässig erkannt. Bitte einen ungesättigten Stern mit gutem SNR anklicken oder auf Feldmedian umschalten.",g_afAutomaticRequest);
        else SetAutofocusError(L"AF_TOO_FEW_STARS",L"Zu wenige geeignete Sterne",L"Die konfigurierten Mindestzahl geeigneter Sterne wurde im aktuellen Bild nicht erreicht. Bitte Belichtung, Gain, Bildausschnitt oder Mindestwert anpassen.",g_afAutomaticRequest);
        AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;
    }
    AutoTuneExposure();if(!runSelected&&g_saturatedCount>g_starCount/3&&g_starCount>6){SetAutofocusError(L"AF_TOO_MANY_SATURATED_STARS",L"Zu viele Sterne gesättigt",L"Zu viele Sterne sind gesättigt. Bitte Belichtung oder Gain reduzieren.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}
    g_beforeFwhm=preF;g_beforeHfr=preH;g_afRetryCount=0;
    g_afStartPosition=FocuserPosition();if(g_afStartPosition<0){SetAutofocusError(L"AF_ASCOM_DRIVER_NOT_RESPONDING",L"ASCOM-Treiber antwortet nicht",L"Die aktuelle Fokusposition konnte nicht gelesen werden.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}WriteSimulatorStage("41 autofocus plan created");int half=g_afPointCount/2;int maxStep=FocuserMaxStep();if(g_safeMaxPosition>maxStep)g_safeMaxPosition=maxStep;long long span=(long long)half*(long long)g_afStep;if(span*2LL>(long long)maxStep){g_afStep=maxStep/(2*half);if(g_afStep<1)g_afStep=1;span=(long long)half*(long long)g_afStep;}long long curveCenter=g_afStartPosition;if(curveCenter<span)curveCenter=span;if(curveCenter+span>(long long)maxStep)curveCenter=(long long)maxStep-span;
    for(int i=0;i<g_afPointCount;i++){long long position=curveCenter+(long long)(i-half)*(long long)g_afStep;if(position<0||position>maxStep){SetAutofocusError(L"AF_MOTOR_RANGE_INVALID",L"Messbereich außerhalb des Motorbereichs",L"Der berechnete Messbereich liegt außerhalb des Motorbereichs.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}g_afPositions[i]=(int)position;g_afMetrics[i]=0.0;g_afFwhmMetrics[i]=0.0;g_afMetricSigma[i]=0.0;g_afFwhmSigma[i]=0.0;g_afResiduals[i]=0.0;g_afFwhmResiduals[i]=0.0;g_afOutliers[i]=FALSE;g_afUsedMetrics[i]=0;g_afSamplesPerPoint[i]=0;}
    if(!CheckSafeTarget(g_afPositions[0])||!CheckSafeTarget(g_afPositions[g_afPointCount-1])){SetAutofocusError(L"AF_TARGET_OUTSIDE_SAFE_ZONE",L"Zielposition außerhalb der sicheren Zone",L"Der geplante Messbereich verlässt die sichere Fokuszone. Bitte Schrittweite oder sichere Grenzen anpassen.",g_afAutomaticRequest);AutofocusNotice(g_lastAfErrorDetail,g_lastAfErrorTitle,MB_OK|MB_ICONWARNING);return;}
    wchar_t plan[760];double sec=g_afPointCount*g_afSamples*(CurrentExposureSeconds()+0.8)+8.0;wsprintfW(plan,L"Geplanter Fokuslauf\n\nMetrik: %s\nStartposition: %d\nMessbereich: %d bis %d\nMesspunkte: %d\nAufnahmen pro Punkt: %d\nGeschaetzte Dauer: ca. %d s\nSichere Fokuszone: %d bis %d\n\nAutofokus jetzt starten?",runSelected?L"manuell gewählter Fokusstern":L"Median aller geeigneten Sterne",g_afStartPosition,g_afPositions[0],g_afPositions[g_afPointCount-1],g_afPointCount,g_afSamples,(int)sec,g_safeMinPosition,g_safeMaxPosition);
    if(!g_afAutomaticRequest&&!g_afRequestConfirmed&&NotifyUser(plan,L"Autofokus-Vorschau",MB_YESNO|MB_ICONINFORMATION)!=IDYES)return;
    ClearAutofocusError();if(!g_syntheticSelfTestActive)g_sessionAfAttempts++;g_autoStartPending=FALSE;SetAfValidationState(FALSE,FALSE,L"Fokuslauf aktiv",L"Messkurve wird aufgenommen; Abschluss-Kontrollmessung steht noch aus.");g_afRunUsesSelectedStar=runSelected;g_afPointIndex=0;g_afSampleIndex=0;g_afRecenterCount=0;g_afExpansionCount=0;g_afAdaptiveSamplesAdded=0;g_fitValid=FALSE;g_fitFwhmValid=FALSE;g_fitModel=g_fitFwhmModel=0;g_fitFocusSigma=g_fitFocusSigmaLoo=g_fitReducedChi2=g_fitResidualRms=g_fitAicc=0.0;g_fitInliers=g_fitOutliers=0;g_afExpectedHfr=g_afExpectedFwhm=0.0;g_afVerificationCount=0;g_afVerificationRetryCount=0;g_afFinalValid=FALSE;g_afFinalHfr=g_afFinalFwhm=0.0;g_afFinalPosition=-1;g_afActive=TRUE;SetWindowTextW(g_afButton,L"Autofokus abbrechen");g_resumeLiveAfterAf=g_live;if(g_live)StopLive();SetStatus(runSelected?L"Autofokus startet · manuell gewählter Fokusstern":L"Autofokus startet · Feldmedian");WriteSimulatorStage("42 autofocus first move");BeginMoveSequence(g_afPositions[0],1);SaveSettings();InvalidateRect(g_main,0,FALSE);
}
static void StopAutofocus(BOOL restore,LPCWSTR reason){
    BOOL resumeLive=g_resumeLiveAfterAf,automatic=g_afAutomaticRun,wasActive=g_afActive;if(wasActive&&!g_syntheticSelfTestActive)g_sessionAfFailed++;AbortExposure();BOOL preserveWorkerTimeout=WContains(g_lastAfErrorCode,L"AF_ASCOM_WORKER_TIMEOUT")&&(WContains(reason,L"Worker blockiert")||WContains(reason,L"Worker reagiert nicht"));if(!preserveWorkerTimeout)ClassifyAutofocusFailure(reason,automatic);if(g_afActive&&g_afPointIndex>0)ExportReport(reason);g_afVerificationCount=0;g_afVerificationRetryCount=0;
    BOOL rollbackRequested=g_afActive&&restore;BOOL rollbackStarted=FALSE;
    if(rollbackRequested&&g_focuserConnected)rollbackStarted=MoveFocuser(g_afStartPosition);
    if(rollbackStarted){
        if(!g_syntheticSelfTestActive)g_sessionAfRollbacks++;g_afRollbackPerformed=TRUE;
        if(!g_afValidationPassed){
            if(WContains(g_afValidationState,L"Abgelehnt"))CopyWBounded(g_afValidationState,96,L"Abgelehnt · Rollback");
            else SetAfValidationState(FALSE,TRUE,L"Fehlgeschlagen · Rollback",reason&&reason[0]?reason:L"Fokuslauf wurde verworfen; Startposition wird wiederhergestellt.");
        }
    }else if(rollbackRequested){
        g_afRollbackPerformed=FALSE;SetAfValidationState(FALSE,FALSE,L"Rollback nicht möglich",g_focuserConnected?L"Die Rückfahrt zur Startposition konnte nicht gestartet werden.":L"Der Fokussierer ist getrennt; die Startposition konnte nicht wiederhergestellt werden.");
    }else if(wasActive&&!g_afValidationPassed){
        SetAfValidationState(FALSE,FALSE,L"Abgebrochen",reason&&reason[0]?reason:L"Fokuslauf wurde beendet.");
    }
    if(automatic)ScheduleAutoRefocusRetry(reason);AppendSessionEvent(L"Autofokus fehlgeschlagen",reason);
    g_afActive=FALSE;g_afState=0;g_afRunUsesSelectedStar=FALSE;g_afAutomaticRun=FALSE;g_resumeLiveAfterAf=resumeLive;SetWindowTextW(g_afButton,L"Autofokus starten");SetStatus(reason);InvalidateRect(g_main,0,FALSE);
    if(g_resumeLiveAfterAf&&!FocuserMoving()){
        if(g_demo||g_cameraConnected){g_resumeLiveAfterAf=FALSE;g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartLiveExposureOrStop(L"Autofokus beendet · Live-Fokus konnte nicht fortgesetzt werden");}
        else g_resumeLiveAfterAf=FALSE;
    }
}

static void ProcessCompletedFrame(int purpose){
    BOOL ok=FALSE;if(g_simulatorMode){if(g_faultCameraNoFrames)return;if(g_faultCameraCorruptNext){g_faultCameraCorruptNext=FALSE;g_exposing=FALSE;g_capturePurpose=0;if(g_afActive)StopAutofocus(FALSE,L"Simulator lieferte ein beschädigtes Bild · Autofokus sicher abgebrochen");else SetStatus(L"Simulatorbild beschädigt und verworfen");return;}g_simFrameSequence++;WriteSimulatorStage("30 generating synthetic frame");ok=GenerateSimulatorStreamFrame(purpose);WriteSimulatorStage(ok?"31 synthetic frame generated":"39 synthetic frame failed");}else ok=g_externalCameraMode?LoadExternalBmp():(g_demo?GenerateDemoFrame():(g_nativeActive?DownloadNativeImage():DownloadImage()));if(!ok){g_exposing=FALSE;g_capturePurpose=0;if(g_afActive)StopAutofocus(TRUE,L"Bildübertragung fehlgeschlagen · Rückkehr zur Startposition");else if(g_stepAssistActive)StopStepAssistant(TRUE,L"Schritt-Assistent: Bildübertragung fehlgeschlagen");else if(g_backlashCalActive)StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Bildübertragung fehlgeschlagen");else if(purpose==1&&g_externalCameraMode&&g_live){SetStatus(L"USB/UVC-Bild noch unvollständig · nächster Frame wird versucht");StartLiveExposureOrStop(L"USB/UVC-Live-Fokus konnte die nächste Belichtung nicht starten");}else{if(purpose==1&&g_live){g_live=FALSE;SetWindowTextW(g_liveButton,L"Live-Fokus starten");}SetStatus(L"Bildübertragung fehlgeschlagen");}return;}if(!g_demo&&!g_simulatorMode){AnalyseImage();BuildDisplay();InvalidateRect(g_main,0,FALSE);}g_lastCompletedPurpose=purpose;if(purpose==1){AppendTrend(g_medianFwhm,g_medianHfr);UpdateRefocusDegradationState();}UpdateSessionMeasurement(purpose);g_lastFrameCompleted=GetTickCount64();g_exposing=FALSE;g_capturePurpose=0;
    BOOL continuousFocusHoldsNext=purpose==1?ContinuousFocusOnLiveFrame():FALSE;
    if(purpose==1){if(g_live&&!continuousFocusHoldsNext)StartLiveExposureOrStop(L"Live-Fokus konnte die nächste Belichtung nicht starten");}else if(purpose==4)HandleStepAssistantFrame();else if(purpose==5)HandleBacklashCalibrationFrame();else if(purpose==2||purpose==3)HandleAutofocusFrame(purpose);
}

static BOOL RunSimulatorLiveRegression(char* detail,int cap){
    if(!detail||cap<2)return FALSE;detail[0]=0;
    if(!g_simulatorMode||!g_cameraConnected){sprintf(detail,"nicht ausgeführt: Simulator-Kamera muss verbunden sein");return FALSE;}
    if(g_afActive||g_stepAssistActive){sprintf(detail,"nicht ausgeführt: Fokusvorgang aktiv");return FALSE;}
    BOOL oldLive=g_live,oldDet=g_simDeterministicTest;int oldSeq=g_simFrameSequence;double oldF=g_medianFwhm,oldS=g_medianSnr;
    if(g_live)StopLive();g_simDeterministicTest=FALSE;StartLive();int generated=0;
    for(int i=0;i<4;i++){if(!g_live||!g_exposing)break;ProcessCompletedFrame(1);generated++;}
    int delta=g_simFrameSequence-oldSeq;BOOL changed=fabs(g_medianFwhm-oldF)>1e-6||fabs(g_medianSnr-oldS)>1e-6;
    BOOL pass=g_live&&g_exposing&&g_frameReady&&generated==4&&delta==4&&changed&&g_lastFrameCompleted>0;
    sprintf(detail,"%d Frames, Sequenz +%d, FWHM %.3f, SNR %.2f",generated,delta,g_medianFwhm,g_medianSnr);
    StopLive();g_simDeterministicTest=oldDet;
    if(oldLive){g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartExposure(1);}
    return pass;
}

static BOOL RunStepAssistantRegression(char* detail,int cap){
    if(!detail||cap<2)return FALSE;detail[0]=0;
    if(!g_simulatorMode||!g_cameraConnected||!g_focuserConnected){sprintf(detail,"nicht ausgeführt: Simulator und Geräte müssen verbunden sein");return FALSE;}
    if(g_afActive||g_stepAssistActive){sprintf(detail,"nicht ausgeführt: Fokusvorgang aktiv");return FALSE;}
    wchar_t oldStep[64];GetWindowTextW(g_afStepEdit,oldStep,64);
    int oldPos=g_simPosition,oldOpt=g_simOpticalPosition,oldDir=g_simLastDirection,oldBacklash=g_simBacklashSteps,oldBacklashRemaining=g_simBacklashRemaining,oldMin=g_safeMinPosition,oldMax=g_safeMaxPosition;
    BOOL oldLive=g_live,oldDet=g_simDeterministicTest;
    if(g_live)StopLive();g_simDeterministicTest=TRUE;g_simBacklashSteps=0;
    g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;g_simLastDirection=0;
    int start=g_simPosition;SetWindowTextW(g_afStepEdit,L"120");GenerateSyntheticFrame(g_simOpticalPosition,1.0,0,0,48,FALSE,FALSE,FALSE);
    StartStepAssistant();int guard=0;BOOL unexpected=FALSE;
    while(g_stepAssistActive&&guard++<80){
        if(g_exposing){int purpose=g_capturePurpose;ProcessCompletedFrame(purpose);continue;}
        if(g_stepAssistState==1){g_stepAssistState=2;continue;}
        if(g_stepAssistState==2){StartExposure(4);continue;}
        if(g_stepAssistState==3){FinishStepAssistant(g_stepAssistResult[0]?g_stepAssistResult:L"Schritt-Assistent beendet");continue;}
        unexpected=TRUE;break;
    }
    wchar_t recommendedW[64];GetWindowTextW(g_afStepEdit,recommendedW,64);int recommended=(int)ParseUIntW(recommendedW,0);
    BOOL pass=!unexpected&&!g_stepAssistActive&&guard<80&&g_simPosition==start&&recommended>=5&&recommended<=5000;
    sprintf(detail,"Start %d, Ende %d, Empfehlung %d, Schleifen %d",start,g_simPosition,recommended,guard);
    if(g_stepAssistActive)StopStepAssistant(TRUE,L"Interner Test abgebrochen");AbortExposure();g_stepAssistState=0;
    SetWindowTextW(g_afStepEdit,oldStep);g_simPosition=oldPos;g_simOpticalPosition=oldOpt;g_simLastDirection=oldDir;g_simBacklashSteps=oldBacklash;g_simBacklashRemaining=oldBacklashRemaining;g_safeMinPosition=oldMin;g_safeMaxPosition=oldMax;g_simDeterministicTest=oldDet;
    wchar_t pos[32];wsprintfW(pos,L"%d",g_simPosition);SetWindowTextW(g_positionText,pos);
    if(oldLive){g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartExposure(1);}
    return pass;
}

static BOOL RunSimulatorWorkflowRegressionMode(BOOL selectedMode,int simulatorStars,char* detail,int cap){
    if(!detail||cap<2)return FALSE;detail[0]=0;
    if(!g_simulatorMode||!g_cameraConnected||!g_focuserConnected){sprintf(detail,"nicht ausgeführt: Simulator, Kamera und Fokussierer müssen verbunden sein");return FALSE;}
    if(g_afActive||g_stepAssistActive){sprintf(detail,"nicht ausgeführt: ein Fokusvorgang ist bereits aktiv");return FALSE;}
    wchar_t oldExposure[64],oldPoints[64],oldStep[64],oldSamples[64],oldBacklash[64];
    GetWindowTextW(g_exposureEdit,oldExposure,64);GetWindowTextW(g_afPointsEdit,oldPoints,64);GetWindowTextW(g_afStepEdit,oldStep,64);GetWindowTextW(g_afSamplesEdit,oldSamples,64);GetWindowTextW(g_afBacklashEdit,oldBacklash,64);
    int oldPos=g_simPosition,oldOpticalPos=g_simOpticalPosition,oldMin=g_safeMinPosition,oldMax=g_safeMaxPosition,oldDir=g_simLastDirection,oldBacklashRemaining=g_simBacklashRemaining,oldStars=g_simStarCount,oldSelected=g_selectedStar,oldMisses=g_selectedStarMisses,oldProfileMode=g_simProfileMode,oldActiveProfile=g_simActiveProfile;wchar_t oldProfileName[96];CopyWBounded(oldProfileName,96,g_simProfileName);BOOL oldPref=IsChecked(g_preferredDirCheck),oldTemp=g_hasFocuserTemperature,oldLive=g_live,oldDet=g_simDeterministicTest,oldManual=g_manualStarLocked,oldUseSelected=g_afUseSelectedStar,oldRunSelected=g_afRunUsesSelectedStar;double oldNx=g_selectedTargetNx,oldNy=g_selectedTargetNy;g_simDeterministicTest=TRUE;g_simProfileMode=SIM_NORMAL;g_simActiveProfile=SIM_NORMAL;CopyWBounded(g_simProfileName,96,SimulatorProfileName(SIM_NORMAL));
    if(g_live)StopLive();g_hasFocuserTemperature=FALSE;g_safeMinPosition=0;g_safeMaxPosition=g_simMaxStep;g_simPosition=g_simBestFocus+360;g_simOpticalPosition=g_simPosition;g_simLastDirection=0;g_simStarCount=simulatorStars;
    g_manualStarLocked=FALSE;g_afUseSelectedStar=FALSE;g_afRunUsesSelectedStar=FALSE;g_selectedStar=-1;g_selectedStarMisses=0;
    SetWindowTextW(g_exposureEdit,L"1");SetWindowTextW(g_afPointsEdit,L"9");SetWindowTextW(g_afStepEdit,L"120");SetWindowTextW(g_afSamplesEdit,L"3");SetWindowTextW(g_afBacklashEdit,L"250");SetChecked(g_preferredDirCheck,TRUE);
    GenerateSyntheticFrame(g_simPosition,1.0,0,0,g_simStarCount,TRUE,FALSE,FALSE);
    BOOL selectedReady=TRUE;if(selectedMode){int s=g_selectedStar;selectedReady=s>=0&&SelectManualStarAt((int)(g_stars[s].x+0.5),(int)(g_stars[s].y+0.5));g_afUseSelectedStar=selectedReady;}
    WriteSimulatorStage(selectedMode?"60 selected-star state-machine regression start":"60 field-median state-machine regression start");if(selectedReady)StartAutofocus();
    int guard=0;BOOL unexpected=!selectedReady||!g_afActive;
    while(g_afActive&&guard++<600){
        if(g_exposing){int purpose=g_capturePurpose;ProcessCompletedFrame(purpose);continue;}
        if(g_afState==10){if(MoveFocuser(g_moveFinalTarget))g_afState=11;else{unexpected=TRUE;break;}continue;}
        if(g_afState==11){ContinueAfterMove();continue;}
        if(g_afState==12){int c=g_moveContinuation;g_afState=0;if(c==1){if(!StartExposure(2))StopAutofocus(TRUE,L"Autofokus: Messbelichtung konnte nicht gestartet werden");}else if(c==2){if(!StartExposure(3))StopAutofocus(TRUE,L"Autofokus: Kontrollbelichtung konnte nicht gestartet werden");}else if(c==3){g_afActive=FALSE;SetWindowTextW(g_afButton,L"Autofokus starten");}else{unexpected=TRUE;break;}continue;}
        unexpected=TRUE;break;
    }
    int resultPos=g_simPosition,opticalPos=g_simOpticalPosition,opticalErr=opticalPos-g_simBestFocus;if(opticalErr<0)opticalErr=-opticalErr;int commandOffset=resultPos-opticalPos;if(commandOffset<0)commandOffset=-commandOffset;int tolerance=selectedMode?g_afStep:100;int minIndex=-1;double minMetric=1e30;for(int i=0;i<g_afPointCount;i++)if(g_afMetrics[i]>0&&g_afMetrics[i]<minMetric){minMetric=g_afMetrics[i];minIndex=i;}BOOL bracketed=minIndex>=2&&minIndex<=g_afPointCount-3;BOOL verified=g_afFinalValid&&g_afVerificationCount>=g_afVerificationTarget&&g_afFinalPosition==resultPos&&g_afFinalFwhm>0&&g_afFinalHfr>0&&g_afFinalFwhm<=g_beforeFwhm*0.98&&g_afFinalHfr<=g_beforeHfr*0.98;BOOL backlashConsistent=g_simBacklashSteps<=0||commandOffset<=g_simBacklashSteps+g_afStep;BOOL pass=!unexpected&&!g_afActive&&guard<600&&g_fitValid&&g_fitFwhmValid&&bracketed&&verified&&opticalErr<=tolerance&&backlashConsistent;
    sprintf(detail,"%s, %d Sterne: optisches Soll %d, Motor %d, optisch %d, Abweichung %d, Offset %d, Schleifen %d, R2 %.4f, FWHM %.3f -> %.3f, Kontrollbilder %d, Minimumindex %d",selectedMode?"Fokusstern":"Feldmedian",simulatorStars,g_simBestFocus,resultPos,opticalPos,opticalErr,commandOffset,guard,g_fitR2,g_beforeFwhm,g_afFinalFwhm,g_afVerificationCount,minIndex);
    if(g_afActive)StopAutofocus(TRUE,L"Interner Simulator-Test abgebrochen");AbortExposure();g_afState=0;
    SetWindowTextW(g_exposureEdit,oldExposure);SetWindowTextW(g_afPointsEdit,oldPoints);SetWindowTextW(g_afStepEdit,oldStep);SetWindowTextW(g_afSamplesEdit,oldSamples);SetWindowTextW(g_afBacklashEdit,oldBacklash);SetChecked(g_preferredDirCheck,oldPref);
    g_safeMinPosition=oldMin;g_safeMaxPosition=oldMax;g_simPosition=oldPos;g_simOpticalPosition=oldOpticalPos;g_simLastDirection=oldDir;g_simBacklashRemaining=oldBacklashRemaining;g_hasFocuserTemperature=oldTemp;g_simDeterministicTest=oldDet;g_simStarCount=oldStars;g_simProfileMode=oldProfileMode;g_simActiveProfile=oldActiveProfile;CopyWBounded(g_simProfileName,96,oldProfileName);g_manualStarLocked=oldManual;g_afUseSelectedStar=oldUseSelected;g_afRunUsesSelectedStar=oldRunSelected;g_selectedTargetNx=oldNx;g_selectedTargetNy=oldNy;g_selectedStarMisses=oldMisses;g_selectedStar=oldSelected;wchar_t pos[32];wsprintfW(pos,L"%d",g_simPosition);SetWindowTextW(g_positionText,pos);SaveSettings();
    if(oldLive){g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartExposure(1);}WriteSimulatorStage(pass?"69 state-machine regression passed":"68 state-machine regression failed");return pass;
}
static BOOL RunSimulatorWorkflowRegression(char* detail,int cap){return RunSimulatorWorkflowRegressionMode(FALSE,48,detail,cap);}
static BOOL RunSimulatorSelectedStarRegression(char* detail,int cap){return RunSimulatorWorkflowRegressionMode(TRUE,1,detail,cap);}

static void ScheduleAutoRefocusRetry(LPCWSTR failureReason){
    static const int delaySeconds[4]={30,60,120,300};g_autoRefocusFailureCount++;
    if(g_autoRefocusFailureCount>4){g_autoRefocusPaused=TRUE;g_autoRefocusRetryAfter=0;CopyWBounded(g_lastAutoRefocusReason,240,L"Retryfolge 30/60/120/300 s ausgeschöpft · Benutzerfreigabe erforderlich");return;}
    int delay=delaySeconds[g_autoRefocusFailureCount-1];g_autoRefocusRetryAfter=GetTickCount64()+(ULONGLONG)delay*1000ULL;wchar_t msg[240];wsprintfW(msg,L"Fehlversuch %d/4 · erneuter Versuch in %d s",g_autoRefocusFailureCount,delay);CopyWBounded(g_lastAutoRefocusReason,240,msg);if(failureReason&&*failureReason)SetStatus(failureReason);
}
static void ResumeAutoRefocusAfterPause(){g_autoRefocusPaused=FALSE;g_autoRefocusFailureCount=0;g_autoRefocusRetryAfter=0;g_refocusBadFrameStreak=0;CopyWBounded(g_lastAutoRefocusReason,240,L"vom Benutzer wieder freigegeben · aktiv und bereit");ClearAutofocusError();SetStatus(L"Auto-Refokus wieder freigegeben");}
static BOOL AtmosphereSuitableForFwhmRefocus(){
    /* Fewer than five trend samples are not enough to classify the atmosphere yet.
       Once the robust seeing model has enough history, suppress FWHM-triggered
       refocus while seeing is very unsteady or transparency has collapsed. */
    if(g_trendCount<5)return TRUE;
    return g_seeingIndex>=38.0&&g_transparencyIndex>=55.0;
}
static void UpdateRefocusDegradationState(){
    if(g_syntheticSelfTestActive)return;
    if(g_lastRefocusEvaluatedFrameSequence==g_frameSequence)return;g_lastRefocusEvaluatedFrameSequence=g_frameSequence;
    if(!g_autoRefocusEnabled||!g_autoRefocusReferenceReady||g_refocusFwhmThresholdPercent<=0.0||g_lastGoodFwhm<=0.0){g_refocusBadFrameStreak=0;return;}
    BOOL atmosphereOk=AtmosphereSuitableForFwhmRefocus();BOOL enough=g_usedCount>=g_refocusMinStars;BOOL stable=FocusStability()<=g_refocusStabilityLimit;BOOL degraded=g_medianFwhm>g_lastGoodFwhm*(1.0+g_refocusFwhmThresholdPercent/100.0);
    if(atmosphereOk&&enough&&stable&&degraded){if(g_refocusBadFrameStreak<100000)g_refocusBadFrameStreak++;}else g_refocusBadFrameStreak=0;
}
static BOOL TriggerAutomaticRefocus(LPCWSTR reason){
    ULONGLONG now=GetTickCount64();if(g_continuousFocusPhase==CF_MOVING||g_continuousFocusPhase==CF_SETTLING)return FALSE;
    ContinuousFocusSuspendForAutofocus();if(g_autoRefocusPaused||now<g_autoRefocusRetryAfter||g_afActive||g_stepAssistActive||g_backlashCalActive)return FALSE;
    BOOL oldUseSelected=g_afUseSelectedStar,fallback=FALSE;double h=0.0,f=0.0;int used=0;
    if(oldUseSelected&&!CurrentAutofocusMetric(TRUE,&h,&f,&used)){g_afUseSelectedStar=FALSE;fallback=TRUE;}
    g_afAutomaticRequest=TRUE;g_afAutomaticRun=TRUE;StartAutofocus();g_afAutomaticRequest=FALSE;g_afUseSelectedStar=oldUseSelected;
    if(g_afActive){
        g_autoRefocusRetryAfter=0;
        if(fallback){wchar_t status[280];wsprintfW(status,L"%s · gewählter Fokusstern nicht verfügbar, Feldmedian wird verwendet",reason);SetStatus(status);lstrcpyW(g_lastAutoRefocusReason,L"Feldmedian-Fallback wegen verlorenem Fokusstern");}
        else{SetStatus(reason);lstrcpyW(g_lastAutoRefocusReason,reason);}
        return TRUE;
    }
    g_afAutomaticRun=FALSE;ScheduleAutoRefocusRetry(L"Auto-Refokus konnte nicht gestartet werden");if(!g_lastAfErrorTick)SetAutofocusError(L"AF_START_CONDITION_NOT_MET",L"Auto-Refokus konnte nicht starten",L"Mindestens eine Startbedingung ist noch nicht erfüllt.",TRUE);return FALSE;
}
static BOOL ShouldStartDegradationRefocus(){if(g_continuousFocusEnabled&&!g_continuousFocusPaused)return FALSE;ULONGLONG now=GetTickCount64();BOOL cooldownDone=g_lastAfCompleted==0||now-g_lastAfCompleted>=(ULONGLONG)(g_refocusCooldownMinutes*60000.0);return g_autoRefocusEnabled&&!g_autoRefocusPaused&&g_autoRefocusReferenceReady&&g_degradationRefocusEnabled&&g_refocusFwhmThresholdPercent>0.0&&g_lastGoodFwhm>0.0&&g_refocusBadFrameStreak>=g_refocusBadFramesRequired&&cooldownDone&&AtmosphereSuitableForFwhmRefocus()&&!g_afActive&&!g_stepAssistActive&&!g_backlashCalActive&&g_cameraConnected&&g_focuserConnected&&!FocuserMoving();}
static void MarkCameraDisconnected(LPCWSTR reason){
    if(g_live)g_resumeLiveAfterCameraRecovery=TRUE;g_cameraConnected=FALSE;g_exposing=FALSE;g_capturePurpose=0;g_lastCompletedPurpose=0;g_live=FALSE;g_cameraRuntime.phase=g_cameraWanted?DEV_RECOVERING:DEV_DISCONNECTED;g_cameraRuntime.removalDetected=TRUE;CopyWBounded(g_cameraRuntime.operation,96,reason);AppendHardwareEvent(TRUE,L"disconnected",&g_cameraRuntime,g_cameraRuntime.lastError);SetWindowTextW(g_cameraConnect,L"Verbinden");SetWindowTextW(g_liveButton,L"Live-Fokus starten");
    if(g_afActive)StopAutofocus(FALSE,reason);else if(g_stepAssistActive)StopStepAssistant(FALSE,reason);else if(g_backlashCalActive)StopBacklashCalibration(FALSE,reason);else SetStatus(reason);
}
static void MarkFocuserDisconnected(LPCWSTR reason){
    g_focuserConnected=FALSE;g_cachedFocuserPosition=-1;g_cachedFocuserMoving=FALSE;g_hasFocuserTemperature=FALSE;g_moveDeadlineTick=0;g_focuserRuntime.positionKnown=FALSE;g_focuserRuntime.phase=g_focuserWanted?DEV_RECOVERING:DEV_DISCONNECTED;g_focuserRuntime.removalDetected=TRUE;CopyWBounded(g_focuserRuntime.operation,96,reason);AppendHardwareEvent(FALSE,L"disconnected",&g_focuserRuntime,g_focuserRuntime.lastError);SetWindowTextW(g_focuserConnect,L"Verbinden");SetWindowTextW(g_positionText,L"–");
    if(g_afActive)StopAutofocus(FALSE,reason);else if(g_stepAssistActive)StopStepAssistant(FALSE,reason);else if(g_backlashCalActive)StopBacklashCalibration(FALSE,reason);else SetStatus(reason);
}
static void PollAscomWorkers(ULONGLONG now){
    if(g_focuserConnected&&g_focuserWorker&&!g_simulatorMode&&now-g_lastFocuserWorkerPoll>=1000){
        g_lastFocuserWorkerPoll=now;DeviceWorker* w=g_focuserWorker;BOOL connected=TRUE;
        if(!WorkerGetBool(w,L"Connected",TRUE,&connected,1000)){ApplyDeviceWorkerFaults();if(g_focuserWorker==w&&!g_focuserWorkerBlocked){DestroyDeviceWorker(&g_focuserWorker,TRUE);g_focuserWorkerRecoveryAttempt++;g_focuserWorkerRetryAfter=now+DeviceRecoveryDelayMs(g_focuserWorkerRecoveryAttempt);MarkFocuserDisconnected(L"ASCOM-Fokussierer antwortet nicht · automatische Wiederherstellung wartet");}}
        else if(!connected){DestroyDeviceWorker(&g_focuserWorker,TRUE);g_focuserWorkerRecoveryAttempt++;g_focuserWorkerRetryAfter=now+DeviceRecoveryDelayMs(g_focuserWorkerRecoveryAttempt);MarkFocuserDisconnected(L"Fokussierer getrennt · automatische Wiederverbindung wartet");}
        else if(g_focuserWorker==w){
            LONG pos=g_cachedFocuserPosition,maxStep=g_cachedFocuserMaxStep;BOOL moving=g_cachedFocuserMoving;double temp=-9999.0;
            if(WorkerGetInt(w,L"Position",pos,&pos,1000))g_cachedFocuserPosition=(int)pos;else ApplyDeviceWorkerFaults();
            if(g_focuserWorker==w&&WorkerGetBool(w,L"IsMoving",moving,&moving,1000)){g_cachedFocuserMoving=moving;if(!moving)g_moveDeadlineTick=0;}else if(g_focuserWorker==w)ApplyDeviceWorkerFaults();
            if(g_focuserWorker==w&&g_cachedFocuserMaxStep<=0&&WorkerGetInt(w,L"MaxStep",maxStep,&maxStep,1000))g_cachedFocuserMaxStep=(int)maxStep;
            if(g_focuserWorker==w&&now-g_lastFocuserTemperaturePoll>=10000){g_lastFocuserTemperaturePoll=now;if(WorkerGetDouble(w,L"Temperature",-9999.0,&temp,1200)&&temp>-100.0&&temp<100.0){g_focuserTemperature=temp;g_hasFocuserTemperature=TRUE;}else if(g_focuserWorker==w)g_hasFocuserTemperature=FALSE;}
            ApplyDeviceWorkerFaults();
            if(g_focuserConnected&&g_cachedFocuserPosition>=0){if(g_afFinalValid&&!g_afActive&&g_cachedFocuserPosition!=g_afFinalPosition)g_afFinalValid=FALSE;wchar_t text[64];wsprintfW(text,L"%d",g_cachedFocuserPosition);SetWindowTextW(g_positionText,text);}
        }
    }
    if(g_cameraConnected&&!g_nativeActive&&!g_simulatorMode&&!g_externalCameraMode&&g_cameraWorker&&now-g_lastCameraWorkerPoll>=1000){
        g_lastCameraWorkerPoll=now;DeviceWorker* w=g_cameraWorker;BOOL connected=TRUE;
        if(!WorkerGetBool(w,L"Connected",TRUE,&connected,1000)){ApplyDeviceWorkerFaults();if(g_cameraWorker==w&&!g_cameraWorkerBlocked){DestroyDeviceWorker(&g_cameraWorker,TRUE);g_cameraWorkerRecoveryAttempt++;g_cameraWorkerRetryAfter=now+DeviceRecoveryDelayMs(g_cameraWorkerRecoveryAttempt);MarkCameraDisconnected(L"ASCOM-Kamera antwortet nicht · automatische Wiederherstellung wartet");}}
        else if(!connected){DestroyDeviceWorker(&g_cameraWorker,TRUE);g_cameraWorkerRecoveryAttempt++;g_cameraWorkerRetryAfter=now+DeviceRecoveryDelayMs(g_cameraWorkerRecoveryAttempt);MarkCameraDisconnected(L"ASCOM-Kamera getrennt · automatische Wiederverbindung wartet");}
        ApplyDeviceWorkerFaults();
    }
}
static void AttemptAutomaticReconnect(ULONGLONG now){
    if(!g_autoReconnect||g_simulatorMode||g_afActive||g_stepAssistActive||g_backlashCalActive)return;
    if(g_cameraWanted&&IsChecked(g_nativeCheck)&&!g_cameraConnected&&now-g_lastCameraReconnect>=5000){
        g_lastCameraReconnect=now;BOOL resume=g_resumeLiveAfterCameraRecovery;if(g_toupDll||g_tcam)UnloadToupTek();g_silentConnect=TRUE;BOOL ok=ConnectNativeCamera();g_silentConnect=FALSE;if(ok){g_resumeLiveAfterCameraRecovery=FALSE;if(g_refocusOnReconnect&&g_focuserConnected)HandleExternalRefocusEvent(L"Wiederverbindung der Kamera");if(resume&&!g_exposing)StartLiveExposureOrStop(L"Kamera wiederverbunden, Live-Fokus konnte aber nicht fortgesetzt werden");}
    }
    if(g_cameraWanted&&!IsChecked(g_nativeCheck)&&!g_cameraConnected&&!g_cameraWorkerBlocked&&!HasOrphanWorker(TRUE)&&g_cameraId[0]&&now>=g_cameraWorkerRetryAfter&&now-g_lastCameraReconnect>=1000){
        g_lastCameraReconnect=now;BOOL resume=g_resumeLiveAfterCameraRecovery;if(ConnectAscomCameraWorker(TRUE)){g_cameraWorkerBlocked=FALSE;g_cameraWorkerRecoveryAttempt=0;g_resumeLiveAfterCameraRecovery=FALSE;if(g_refocusOnReconnect&&g_focuserConnected)HandleExternalRefocusEvent(L"Wiederverbindung der Kamera");if(resume&&!g_exposing){g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartLiveExposureOrStop(L"ASCOM-Kamera wiederverbunden, Live-Fokus konnte aber nicht fortgesetzt werden");}}
        else if(!g_cameraWorkerFaultPending&&!g_cameraWorker&&!g_cameraWorkerBlocked){g_cameraWorkerRecoveryAttempt++;g_cameraWorkerRetryAfter=now+DeviceRecoveryDelayMs(g_cameraWorkerRecoveryAttempt);}
    }
    if(!g_focuserSetupReserved&&g_focuserWanted&&!g_focuserConnected&&!g_focuserWorkerBlocked&&!HasOrphanWorker(FALSE)&&g_focuserId[0]&&now>=g_focuserWorkerRetryAfter&&now-g_lastFocuserReconnect>=1000){
        g_lastFocuserReconnect=now;if(ConnectAscomFocuserWorker(TRUE)){g_focuserWorkerBlocked=FALSE;g_focuserWorkerRecoveryAttempt=0;g_autoStartPending=TRUE;if(g_refocusOnReconnect&&g_cameraConnected)HandleExternalRefocusEvent(L"Wiederverbindung des Fokussierers");}
        else if(!g_focuserWorkerFaultPending&&!g_focuserWorker&&!g_focuserWorkerBlocked){g_focuserWorkerRecoveryAttempt++;g_focuserWorkerRetryAfter=now+DeviceRecoveryDelayMs(g_focuserWorkerRecoveryAttempt);}
    }
}
static void CheckFocuserMovementDeadline(ULONGLONG now){
    if(!g_moveDeadlineTick||now<g_moveDeadlineTick)return;if(!g_focuserConnected||!g_cachedFocuserMoving){g_moveDeadlineTick=0;return;}
    if(g_simulatorMode){g_moveDeadlineTick=0;g_cachedFocuserMoving=FALSE;g_faultFocuserStall=FALSE;g_focuserRuntime.positionKnown=FALSE;g_focuserRuntime.phase=DEV_POSITION_UNKNOWN;SetAutofocusError(L"AF_FOCUSER_TIMEOUT",L"Synthetischer Fokussierer blockiert",L"Die Fehlerprovokation hat eine blockierte Bewegung ausgelöst. Die Position wurde absichtlich als unbekannt markiert; es erfolgt kein automatisches Zurückfahren.",g_afAutomaticRun||g_afAutomaticRequest);if(g_afActive)StopAutofocus(FALSE,L"Synthetischer Fokussierer blockiert · Position unbekannt");else SetStatus(L"Fehlerprovokation bestätigt: Fokusposition unbekannt");return;}
    g_moveDeadlineTick=0;g_focuserRuntime.positionKnown=FALSE;g_focuserRuntime.phase=DEV_POSITION_UNKNOWN;g_focuserRuntime.lastError=(HRESULT)0x800705B4L;CopyWBounded(g_focuserRuntime.operation,96,L"Fokussiererbewegung überschritt dynamische Deadline");AppendHardwareEvent(FALSE,L"movement-timeout",&g_focuserRuntime,g_focuserRuntime.lastError);
    SetAutofocusError(L"AF_FOCUSER_TIMEOUT",L"Fokussiererbewegung blockiert",L"Der Fokussierer meldete das Ende der Bewegung nicht innerhalb der aus Fahrweg und Sicherheitsreserve berechneten Frist. Die Position gilt als unbekannt; ein automatisches Zurückfahren wird absichtlich nicht ausgeführt.",g_afAutomaticRun||g_afAutomaticRequest);
    DeviceWorker* w=g_focuserWorker;if(w)WorkerCallNoArgs(w,L"Halt",2500);ApplyDeviceWorkerFaults();if(g_focuserWorker==w&&w)DestroyDeviceWorker(&g_focuserWorker,TRUE);g_focuserWorkerRecoveryAttempt++;g_focuserWorkerRetryAfter=now+DeviceRecoveryDelayMs(g_focuserWorkerRecoveryAttempt);MarkFocuserDisconnected(L"Fokussiererbewegung blockiert · Position unbekannt · sichere Wiederverbindung erforderlich");
}
static void PrepareHardwareForSuspend(){
    g_resumeRecoveryPending=TRUE;if(g_live)g_resumeLiveAfterCameraRecovery=TRUE;
    if(g_afActive)StopAutofocus(FALSE,L"Windows wechselt in den Standby · Autofokus sicher beendet");
    if(g_stepAssistActive)StopStepAssistant(FALSE,L"Windows wechselt in den Standby · Schritt-Assistent beendet");
    if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Windows wechselt in den Standby · Backlash-Kalibrierung beendet");
    AbortExposure();g_live=FALSE;SetWindowTextW(g_liveButton,L"Live-Fokus starten");
    if(g_nativeActive||g_toupDll){UnloadToupTek();if(g_cameraWanted)MarkCameraDisconnected(L"Standby · native Kamera wird nach dem Fortsetzen neu verbunden");}
    else if(g_cameraWorker){DestroyDeviceWorker(&g_cameraWorker,TRUE);if(g_cameraWanted)MarkCameraDisconnected(L"Standby · ASCOM-Kamerahost geschlossen");}
    if(g_focuserWorker){DeviceWorker* w=g_focuserWorker;WorkerCallNoArgs(w,L"Halt",1500);ApplyDeviceWorkerFaults();if(g_focuserWorker==w)DestroyDeviceWorker(&g_focuserWorker,TRUE);if(g_focuserWanted)MarkFocuserDisconnected(L"Standby · Fokussiererhost geschlossen, Position wird neu geprüft");}
    SetStatus(L"Standby erkannt · Gerätehosts geschlossen und Operationen sicher beendet");
}
static void TimerTick(){
    PollHttpServer();if(g_shutdownRequested){g_shutdownRequested=FALSE;SendMessageW(g_main,WM_CLOSE,0,0);return;}
    ULONGLONG now=GetTickCount64();CleanupOrphanWorkers();ApplyDeviceWorkerFaults();
    if(g_simulatorMode){g_hasFocuserTemperature=g_focuserConnected;g_focuserTemperature=g_simTemperature;if(g_afFinalValid&&!g_afActive&&g_simPosition!=g_afFinalPosition)g_afFinalValid=FALSE;wchar_t sp[32];wsprintfW(sp,L"%d",g_simPosition);SetWindowTextW(g_positionText,sp);}
    PollAscomWorkers(now);CheckFocuserMovementDeadline(now);g_autoReconnect=IsChecked(g_reconnectCheck);AttemptAutomaticReconnect(now);ApplyDeviceWorkerFaults();if(g_filterRefocusPending&&!FocuserMoving()&&!g_afActive&&!g_stepAssistActive&&!g_backlashCalActive){g_filterRefocusPending=FALSE;HandleExternalRefocusEvent(L"Filterwechsel");}
    if(g_stepAssistActive){
        if(g_stepAssistState==1&&now>=g_stepAssistSettle&&!FocuserMoving()){g_stepAssistSettle=now+600;g_stepAssistState=2;}
        else if(g_stepAssistState==2&&now>=g_stepAssistSettle&&!g_exposing){if(!StartExposure(4))StopStepAssistant(TRUE,L"Schritt-Assistent: Belichtung konnte nicht gestartet werden");}
        else if(g_stepAssistState==3&&!FocuserMoving())FinishStepAssistant(g_stepAssistResult[0]?g_stepAssistResult:L"Schritt-Assistent beendet");
    }
    if(g_backlashCalActive){
        if(g_backlashCalState==1&&!FocuserMoving()){g_backlashCalSettle=now+600;g_backlashCalState=2;}
        else if(g_backlashCalState==2&&now>=g_backlashCalSettle&&!g_exposing){if(!StartExposure(5))StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Baseline-Belichtung fehlgeschlagen");}
        else if(g_backlashCalState==3&&!FocuserMoving()){g_backlashCalSettle=now+450;g_backlashCalState=4;}
        else if(g_backlashCalState==4&&now>=g_backlashCalSettle&&!g_exposing){if(!StartExposure(5))StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Messbelichtung fehlgeschlagen");}
        else if(g_backlashCalState==5&&!FocuserMoving())FinishBacklashCalibration(g_backlashCalResult[0]?g_backlashCalResult:L"Backlash-Kalibrierung beendet");
    }
    if(g_autoStartPending&&g_focuserConnected&&!FocuserMoving()&&!g_afActive&&!g_stepAssistActive&&!g_backlashCalActive){g_autoStartPending=FALSE;TryAutomaticStartPosition();}
    ContinuousFocusTick(now);
    ApplyTemperatureCompensation(now);
    if(g_resumeLiveAfterAf&&!g_afActive&&!g_stepAssistActive&&!g_backlashCalActive&&!g_live&&!g_exposing&&!FocuserMoving()){
        if(g_demo||g_cameraConnected){g_resumeLiveAfterAf=FALSE;g_live=TRUE;SetWindowTextW(g_liveButton,L"Live-Fokus stoppen");StartLiveExposureOrStop(L"Live-Fokus konnte nach dem Fokuslauf nicht fortgesetzt werden");}else g_resumeLiveAfterAf=FALSE;
    }
    EnsureAutoRefocusMeasurementReference();
    if(ShouldStartDegradationRefocus())TriggerAutomaticRefocus(L"Auto-Refokus startet wegen nachhaltiger Fokusverschlechterung");
    if(g_autoRefocusEnabled&&!g_autoRefocusPaused&&g_autoRefocusReferenceReady&&!g_afActive&&!g_stepAssistActive&&!g_backlashCalActive&&g_cameraConnected&&g_focuserConnected&&!FocuserMoving()){
        wchar_t v[64];double minutes=0.0,deltaT=0.0;GetWindowTextW(g_refocusMinutesEdit,v,64);if(!ParseStrictDoubleW(v,&minutes)||minutes<0.0||minutes>100000.0)minutes=0.0;GetWindowTextW(g_refocusTempEdit,v,64);if(!ParseStrictDoubleW(v,&deltaT)||deltaT<0.0||deltaT>100.0)deltaT=0.0;
        if(g_lastAfCompleted==0)g_lastAfCompleted=now;EnsureAutoRefocusTemperatureReference();BOOL cooldownDone=g_lastAfCompleted==0||now-g_lastAfCompleted>=(ULONGLONG)(g_refocusCooldownMinutes*60000.0);
        BOOL dueTime=cooldownDone&&minutes>0.0&&now-g_lastAfCompleted>=(ULONGLONG)(minutes*60000.0);BOOL dueTemp=cooldownDone&&deltaT>0.0&&g_hasFocuserTemperature&&g_hasLastAfTemperature&&fabs(g_focuserTemperature-g_lastAfTemperature)>=deltaT;
        if(dueTime||dueTemp)TriggerAutomaticRefocus(dueTemp?L"Auto-Refokus startet wegen Temperaturänderung":L"Auto-Refokus startet nach Zeitintervall");
    }
    if(g_afActive){
        if(g_afState==10&&!FocuserMoving()){if(MoveFocuser(g_moveFinalTarget))g_afState=11;else StopAutofocus(TRUE,L"Fokusbewegung fehlgeschlagen");}
        else if(g_afState==11&&!FocuserMoving())ContinueAfterMove();
        else if(g_afState==12&&now>=g_settleUntil){int c=g_moveContinuation;g_afState=0;if(c==1){if(!StartExposure(2))StopAutofocus(TRUE,L"Autofokus: Messbelichtung konnte nicht gestartet werden");}else if(c==2){if(!StartExposure(3))StopAutofocus(TRUE,L"Autofokus: Kontrollbelichtung konnte nicht gestartet werden");}else if(c==3){g_afActive=FALSE;SetWindowTextW(g_afButton,L"Autofokus starten");}}
    }
    if(g_exposing){
        BOOL ready=FALSE;if(g_demo||g_simulatorMode||g_externalCameraMode)ready=now-g_exposureStarted>=(ULONGLONG)(g_lastExposureSeconds*1000.0);else if(g_nativeActive)ready=FALSE;else if(g_cameraConnected&&g_cameraWorker){DeviceWorker* w=g_cameraWorker;if(!WorkerGetBool(w,L"ImageReady",FALSE,&ready,600)){ApplyDeviceWorkerFaults();ready=FALSE;}}
        if(ready){int purpose=g_capturePurpose;ProcessCompletedFrame(purpose);}else if(now-g_exposureStarted>(ULONGLONG)(g_lastExposureSeconds*1000.0+30000.0)){AbortExposure();if(g_afActive)StopAutofocus(TRUE,L"Zeitüberschreitung der Kamera · Rückkehr zur Startposition");else if(g_stepAssistActive)StopStepAssistant(TRUE,L"Schritt-Assistent: Kamera-Zeitüberschreitung");else if(g_backlashCalActive)StopBacklashCalibration(TRUE,L"Backlash-Kalibrierung: Kamera-Zeitüberschreitung");else SetStatus(L"Zeitüberschreitung der Kamera");}
    }
}
static void DrawMetricOverlay(HDC dc){
    if(!g_frameReady)return;
    RECT r={g_previewRect.left+8,g_previewRect.bottom-70,g_previewRect.right-8,g_previewRect.bottom-8};
    FillRect(dc,&r,g_brushPanel);SetBkMode(dc,TRANSPARENT);HFONT old=(HFONT)SelectObject(dc,g_smallFont);
    const wchar_t* labels[6]={L"FWHM",L"HFR",L"Sterne",L"SNR",L"Exzentrizität",L"Fokusposition"};
    wchar_t values[6][48];
    FormatFixed(g_medianFwhm,2,values[0]);lstrcatW(values[0],L" px");
    FormatFixed(g_medianHfr,2,values[1]);lstrcatW(values[1],L" px");
    wsprintfW(values[2],L"%d",g_usedCount);FormatFixed(g_medianSnr,1,values[3]);FormatFixed(g_medianEcc,2,values[4]);
    if(g_focuserConnected)wsprintfW(values[5],L"%d",FocuserPosition());else lstrcpyW(values[5],L"–");
    int w=(r.right-r.left)/6;
    for(int i=0;i<6;i++){int x=r.left+i*w+18;SetTextColor(dc,RGB(155,166,181));TextOutW(dc,x,r.top+10,labels[i],WLen(labels[i]));SetTextColor(dc,RGB(242,246,252));HFONT ov=(HFONT)SelectObject(dc,g_monoFont);TextOutW(dc,x,r.top+31,values[i],WLen(values[i]));SelectObject(dc,ov);}
    SelectObject(dc,old);
}
static void DrawPreview(HDC dc){
    FillRect(dc,&g_previewRect,g_brushBlack);HPEN oldPen=(HPEN)SelectObject(dc,g_penGrid);HGDIOBJ oldBrush=SelectObject(dc,GetStockObject(5));Rectangle(dc,g_previewRect.left,g_previewRect.top,g_previewRect.right,g_previewRect.bottom);SelectObject(dc,oldBrush);SelectObject(dc,oldPen);
    if(!g_frameReady||!g_display||g_width<=0||g_height<=0){SetBkMode(dc,TRANSPARENT);SetTextColor(dc,RGB(145,154,168));HFONT old=(HFONT)SelectObject(dc,g_titleFont);LPCWSTR t=L"Kamera verbinden und Livebild starten";TextOutW(dc,g_previewRect.left+220,g_previewRect.top+245,t,WLen(t));SelectObject(dc,old);return;}
    int pw=g_previewRect.right-g_previewRect.left,ph=g_previewRect.bottom-g_previewRect.top;double s1=(double)pw/g_width,s2=(double)ph/g_height,scale=s1<s2?s1:s2;int dw=(int)(g_width*scale),dh=(int)(g_height*scale);g_imageRect.left=g_previewRect.left+(pw-dw)/2;g_imageRect.top=g_previewRect.top+(ph-dh)/2;g_imageRect.right=g_imageRect.left+dw;g_imageRect.bottom=g_imageRect.top+dh;StretchDIBits(dc,g_imageRect.left,g_imageRect.top,dw,dh,0,0,g_width,g_height,g_display,&g_bmi,DIB_RGB_COLORS,SRCCOPY);
    if(IsChecked(g_zoneCheck)){HGDIOBJ op=SelectObject(dc,g_penGrid);for(int k=1;k<3;k++){int x=g_imageRect.left+dw*k/3,y=g_imageRect.top+dh*k/3;MoveToEx(dc,x,g_imageRect.top,0);LineTo(dc,x,g_imageRect.bottom);MoveToEx(dc,g_imageRect.left,y,0);LineTo(dc,g_imageRect.right,y);}SelectObject(dc,op);SetBkMode(dc,TRANSPARENT);HFONT of=(HFONT)SelectObject(dc,g_smallFont);for(int z=0;z<9;z++)if(g_zoneCount[z]){int zx=z%3,zy=z/3,x=g_imageRect.left+zx*dw/3+8,y=g_imageRect.top+zy*dh/3+8;wchar_t v[48];FormatFixed(g_zoneFwhm[z],2,v);lstrcatW(v,L" px");SetTextColor(dc,RGB(245,220,135));TextOutW(dc,x,y,v,WLen(v));}SelectObject(dc,of);}
    if(IsChecked(g_overlayStars)){HGDIOBJ hollow=GetStockObject(5),oldB=SelectObject(dc,hollow);HFONT oldF=(HFONT)SelectObject(dc,g_smallFont);SetBkMode(dc,TRANSPARENT);int labelCount=0,starCount=g_starCount;if(starCount<0)starCount=0;if(starCount>MAX_STARS)starCount=MAX_STARS;for(int i=0;i<starCount;i++){StarMetric* st=&g_stars[i];if(!IsTrackableFocusStar(st,FALSE)||st->x>=(double)g_width||st->y>=(double)g_height)continue;int x=g_imageRect.left+(int)(st->x*dw/g_width),y=g_imageRect.top+(int)(st->y*dh/g_height);int rr=(int)(st->fwhm*scale*1.7);if(rr<4)rr=4;if(rr>18)rr=18;x=ClampI(x,g_imageRect.left,g_imageRect.right-1);y=ClampI(y,g_imageRect.top,g_imageRect.bottom-1);HPEN pen=st->saturated&&IsChecked(g_overlaySat)?g_penBad:(st->used?g_penGood:g_penPoint);if(i==g_selectedStar)pen=g_penBest;HGDIOBJ oldP=SelectObject(dc,pen);Ellipse(dc,x-rr,y-rr,x+rr,y+rr);if(i==g_selectedStar){MoveToEx(dc,x-rr-5,y,0);LineTo(dc,x+rr+5,y);MoveToEx(dc,x,y-rr-5,0);LineTo(dc,x,y+rr+5);}SelectObject(dc,oldP);if(IsChecked(g_overlayLabels)&&labelCount<40){wchar_t n[32];FormatFixed(st->fwhm,1,n);SetTextColor(dc,st->saturated?RGB(255,115,115):(st->used?RGB(165,235,180):RGB(245,205,110)));TextOutW(dc,x+rr+2,y-8,n,WLen(n));labelCount++;}}SelectObject(dc,oldF);SelectObject(dc,oldB);}
    DrawMetricOverlay(dc);
}
static int DisplayedAfErrorHalfHeight(double sigma,double ymin,double ymax,int plotHeight,int markerRadius){
    if(!(sigma>0.0)||!(ymax>ymin)||plotHeight<=0)return 0;
    int sy=(int)(sigma*(double)plotHeight/(ymax-ymin)+0.5),minimum=markerRadius+3;
    if(sy<minimum)sy=minimum;int maximum=plotHeight/3;if(maximum<minimum)maximum=minimum;if(sy>maximum)sy=maximum;return sy;
}
static void DrawCurve(HDC dc){
    FillRect(dc,&g_curveRect,g_brushPlot);HGDIOBJ oldB=SelectObject(dc,GetStockObject(5));HGDIOBJ oldP=SelectObject(dc,g_penGrid);Rectangle(dc,g_curveRect.left,g_curveRect.top,g_curveRect.right,g_curveRect.bottom);SelectObject(dc,oldP);SelectObject(dc,oldB);SetBkMode(dc,TRANSPARENT);HFONT oldF=(HFONT)SelectObject(dc,g_smallFont);
    SetTextColor(dc,RGB(220,225,232));TextOutW(dc,g_curveRect.left+10,g_curveRect.top+8,L"Autofokuskurve · HFR",20);
    SetTextColor(dc,RGB(150,165,184));TextOutW(dc,g_curveRect.left+10,g_curveRect.top+27,L"±1σ-Fehlerbalken · rotes × Ausreißer · □ Kontrollmedian",WLen(L"±1σ-Fehlerbalken · rotes × Ausreißer · □ Kontrollmedian"));
    if(g_afPointCount<=0){SetTextColor(dc,RGB(140,150,165));TextOutW(dc,g_curveRect.left+270,g_curveRect.top+88,L"Noch keine Autofokusmessung",26);SelectObject(dc,oldF);return;}
    int left=g_curveRect.left+54,right=g_curveRect.right-20,top=g_curveRect.top+58,bottom=g_curveRect.bottom-34;double ymin=1e30,ymax=0;int measured=0;
    for(int i=0;i<g_afPointCount;i++)if(g_afMetrics[i]>0){double lo=g_afMetrics[i]-g_afMetricSigma[i],hi=g_afMetrics[i]+g_afMetricSigma[i];if(lo<ymin)ymin=lo;if(hi>ymax)ymax=hi;measured++;}
    if(!measured){SelectObject(dc,oldF);return;}if(ymin==ymax){ymin*=0.8;ymax*=1.2;}else{double d=ymax-ymin;ymin-=d*0.16;if(ymin<0)ymin=0;ymax+=d*0.20;}
    HGDIOBJ pg=SelectObject(dc,g_penGrid);for(int k=0;k<=4;k++){int y=top+(bottom-top)*k/4;MoveToEx(dc,left,y,0);LineTo(dc,right,y);}SelectObject(dc,pg);
    int pmin=g_afPositions[0],pmax=g_afPositions[g_afPointCount-1];if(pmax==pmin)pmax=pmin+1;
    if(g_fitValid){
        int ux1=left+(int)(((g_afBestPosition-g_fitFocusSigma)-pmin)*(right-left)/(double)(pmax-pmin));int ux2=left+(int)(((g_afBestPosition+g_fitFocusSigma)-pmin)*(right-left)/(double)(pmax-pmin));ux1=ClampI(ux1,left,right);ux2=ClampI(ux2,left,right);
        RECT band={ux1,top,ux2+1,bottom};HBRUSH ub=CreateSolidBrush(RGB(38,58,72));FillRect(dc,&band,ub);DeleteObject(ub);
        HGDIOBJ pc=SelectObject(dc,g_penCurve);BOOL first=TRUE;for(int xx=left;xx<=right;xx++){double pos=pmin+(double)(xx-left)*(pmax-pmin)/(right-left);double xn=(pos-g_fitCenterPosition)/g_fitScale;double yv=AfEvalModel(g_fitModel,g_fitParams,xn);int yy=bottom-(int)((yv-ymin)*(bottom-top)/(ymax-ymin));yy=ClampI(yy,top,bottom);if(first){MoveToEx(dc,xx,yy,0);first=FALSE;}else LineTo(dc,xx,yy);}SelectObject(dc,pc);
        int bx=left+(int)((double)(g_afBestPosition-pmin)*(right-left)/(pmax-pmin));HGDIOBJ pb=SelectObject(dc,g_penBest);MoveToEx(dc,bx,top,0);LineTo(dc,bx,bottom);SelectObject(dc,pb);
    }
    for(int i=0;i<g_afPointCount;i++)if(g_afMetrics[i]>0){
        int x=left+(int)((double)(g_afPositions[i]-pmin)*(right-left)/(pmax-pmin));int y=bottom-(int)((g_afMetrics[i]-ymin)*(bottom-top)/(ymax-ymin));int sy=DisplayedAfErrorHalfHeight(g_afMetricSigma[i],ymin,ymax,bottom-top,4);int yHi=ClampI(y-sy,top,bottom),yLo=ClampI(y+sy,top,bottom);
        HGDIOBJ pe=SelectObject(dc,g_afOutliers[i]?g_penBad:g_penGood);if(sy>0){MoveToEx(dc,x,yHi,0);LineTo(dc,x,yLo);MoveToEx(dc,x-4,yHi,0);LineTo(dc,x+5,yHi);MoveToEx(dc,x-4,yLo,0);LineTo(dc,x+5,yLo);}SelectObject(dc,pe);
        if(g_afOutliers[i]){HGDIOBJ pp=SelectObject(dc,g_penBad);MoveToEx(dc,x-7,y-7,0);LineTo(dc,x+8,y+8);MoveToEx(dc,x-7,y+7,0);LineTo(dc,x+8,y-8);SelectObject(dc,pp);}else{HGDIOBJ pp=SelectObject(dc,g_penPoint);HGDIOBJ hb=SelectObject(dc,g_brushPanel);Ellipse(dc,x-4,y-4,x+5,y+5);SelectObject(dc,hb);SelectObject(dc,pp);}
    }
    wchar_t w[256],n[32],q[24],su[24],chi[24];wsprintfW(w,L"%d",pmin);SetTextColor(dc,RGB(175,185,198));TextOutW(dc,left,bottom+8,w,WLen(w));wsprintfW(w,L"%d",pmax);TextOutW(dc,right-48,bottom+8,w,WLen(w));
    if(g_fitValid){FormatFixed(g_fitR2,3,n);FormatFixed(g_fitConfidence,2,q);FormatFixed(g_fitFocusSigma,1,su);FormatFixed(g_fitReducedChi2,2,chi);wsprintfW(w,L"Best %d ± %s · Qualität %s · R² %s · χ²red %s",g_afBestPosition,su,q,n,chi);SetTextColor(dc,RGB(155,225,245));int tx=g_curveRect.right-500;if(tx<g_curveRect.left+235)tx=g_curveRect.left+235;TextOutW(dc,tx,g_curveRect.top+8,w,WLen(w));}
    SelectObject(dc,oldF);
}
static void DrawRightStats(HDC dc){
    RECT r={1188,70,1548,300};FillRect(dc,&r,g_brushPlot);HGDIOBJ ob=SelectObject(dc,GetStockObject(5)),op=SelectObject(dc,g_penGrid);Rectangle(dc,r.left,r.top,r.right,r.bottom);SelectObject(dc,op);SelectObject(dc,ob);
    SetBkMode(dc,TRANSPARENT);HFONT old=(HFONT)SelectObject(dc,g_smallFont);wchar_t v[128];SetTextColor(dc,RGB(230,235,244));TextOutW(dc,r.left+16,r.top+14,L"AKTUELLE ANALYSE",17);
    int y=r.top+48;int lx=r.left+16,vx=r.right-118;
    #define ROW(lbl,val) SetTextColor(dc,RGB(170,180,194));TextOutW(dc,lx,y,lbl,WLen(lbl));SetTextColor(dc,RGB(245,247,250));TextOutW(dc,vx,y,val,WLen(val));y+=27
    FormatFixed(g_medianFwhm,2,v);lstrcatW(v,L" px");ROW(L"Median-FWHM",v);
    FormatFixed(g_medianHfr,2,v);lstrcatW(v,L" px");ROW(L"Median-HFR",v);
    wsprintfW(v,L"%d / %d",g_usedCount,g_starCount);ROW(L"Verwendete Sterne",v);
    FormatFixed(g_medianSnr,1,v);ROW(L"SNR (Median)",v);
    FormatFixed(g_medianEcc,2,v);ROW(L"Exzentrizität",v);
    wsprintfW(v,L"%d",g_rejectWeak+g_rejectHot+g_rejectEdge+g_rejectElongated);ROW(L"Verworfen",v);
    if(g_focuserConnected||g_simulatorMode)wsprintfW(v,L"%d",FocuserPosition());else lstrcpyW(v,L"–");ROW(L"Fokusposition",v);
    #undef ROW
    SelectObject(dc,old);
}
static void DrawSelectedPanel(HDC dc){
    RECT r={1188,312,1548,500};FillRect(dc,&r,g_brushPlot);HGDIOBJ ob=SelectObject(dc,GetStockObject(5)),op=SelectObject(dc,g_penGrid);Rectangle(dc,r.left,r.top,r.right,r.bottom);SelectObject(dc,op);SelectObject(dc,ob);SetBkMode(dc,TRANSPARENT);HFONT of=(HFONT)SelectObject(dc,g_smallFont);SetTextColor(dc,RGB(220,225,232));TextOutW(dc,r.left+10,r.top+8,L"Ausgewählter Fokus-Stern",24);if(!g_frameReady||!g_display||g_width<=0||g_height<=0||g_width>10000||g_height>10000||g_starCount<=0||g_starCount>MAX_STARS||g_selectedStar<0||g_selectedStar>=g_starCount||!IsTrackableFocusStar(&g_stars[g_selectedStar],FALSE)){SetTextColor(dc,RGB(140,150,165));TextOutW(dc,r.left+38,r.top+105,L"Kein geeigneter Stern",20);SelectObject(dc,of);return;}StarMetric* st=&g_stars[g_selectedStar];int cx=ClampI((int)(st->x+0.5),0,g_width-1),cy=ClampI((int)(st->y+0.5),0,g_height-1),rad=24,sx=ClampI(cx-rad,0,g_width-1),sy=ClampI(cy-rad,0,g_height-1),sw=ClampI(rad*2,1,g_width-sx),sh=ClampI(rad*2,1,g_height-sy);StretchDIBits(dc,r.left+12,r.top+38,112,112,sx,sy,sw,sh,g_display,&g_bmi,DIB_RGB_COLORS,SRCCOPY);HGDIOBJ pp=SelectObject(dc,g_penBest);MoveToEx(dc,r.left+68,r.top+54,0);LineTo(dc,r.left+68,r.top+134);MoveToEx(dc,r.left+28,r.top+94,0);LineTo(dc,r.left+108,r.top+94);SelectObject(dc,pp);wchar_t v[64];int lx=r.left+136,vx=r.left+190,y=r.top+42;SetTextColor(dc,RGB(190,198,210));TextOutW(dc,lx,y,L"FWHM",5);FormatFixed(st->fwhm,2,v);lstrcatW(v,L" px");SetTextColor(dc,RGB(245,247,250));TextOutW(dc,vx,y,v,WLen(v));y+=23;SetTextColor(dc,RGB(190,198,210));TextOutW(dc,lx,y,L"HFR",3);FormatFixed(st->hfr,2,v);lstrcatW(v,L" px");SetTextColor(dc,RGB(245,247,250));TextOutW(dc,vx,y,v,WLen(v));y+=23;SetTextColor(dc,RGB(190,198,210));TextOutW(dc,lx,y,L"SNR",3);FormatFixed(st->snr,1,v);SetTextColor(dc,RGB(245,247,250));TextOutW(dc,vx,y,v,WLen(v));y+=23;SetTextColor(dc,RGB(190,198,210));TextOutW(dc,lx,y,L"Ecc.",4);FormatFixed(st->ecc,2,v);SetTextColor(dc,RGB(245,247,250));TextOutW(dc,vx,y,v,WLen(v));SetTextColor(dc,RGB(170,180,194));TextOutW(dc,r.left+12,r.top+163,L"Bahtinov",9);if(IsChecked(g_bahtinovCheck)){if(g_bahtinovValid){wchar_t o[28],c[28];FormatFixed(g_bahtinovOffset,2,o);FormatFixed(g_bahtinovConfidence,2,c);wsprintfW(v,L"Offset %s px · C %s",o,c);SetTextColor(dc,fabs(g_bahtinovOffset)<=0.5?RGB(100,230,155):RGB(245,195,80));}else{lstrcpyW(v,L"Kein stabiles Spikemuster");SetTextColor(dc,RGB(245,150,100));}}else{lstrcpyW(v,L"inaktiv");SetTextColor(dc,RGB(140,150,165));}TextOutW(dc,r.left+82,r.top+163,v,WLen(v));FormatFixed(g_bahtinovScore,1,v);SetTextColor(dc,RGB(170,180,194));TextOutW(dc,r.left+12,r.top+187,L"Schärfescore",12);SetTextColor(dc,RGB(245,247,250));TextOutW(dc,r.left+102,r.top+187,v,WLen(v));SetTextColor(dc,RGB(155,225,245));TextOutW(dc,r.left+12,r.bottom-24,L"Stern im Livebild anklicken",26);SelectObject(dc,of);
}
static void DrawTrendPanel(HDC dc){
    RECT r={1188,512,1548,680};FillRect(dc,&r,g_brushPlot);HGDIOBJ ob=SelectObject(dc,GetStockObject(5)),op=SelectObject(dc,g_penGrid);Rectangle(dc,r.left,r.top,r.right,r.bottom);SelectObject(dc,op);SelectObject(dc,ob);SetBkMode(dc,TRANSPARENT);HFONT of=(HFONT)SelectObject(dc,g_smallFont);SetTextColor(dc,RGB(220,225,232));TextOutW(dc,r.left+10,r.top+7,L"Live-Fokus-Trend · FWHM",23);if(g_trendCount>1){double lo=1e30,hi=0;for(int i=0;i<g_trendCount;i++){int idx=(g_trendHead-g_trendCount+i+120)%120;double q=g_trendFwhm[idx];if(q<lo)lo=q;if(q>hi)hi=q;}if(hi<=lo)hi=lo+1;HGDIOBJ pc=SelectObject(dc,g_penCurve);for(int i=0;i<g_trendCount;i++){int idx=(g_trendHead-g_trendCount+i+120)%120;int x=r.left+10+i*(r.right-r.left-20)/(g_trendCount-1);int y=r.bottom-12-(int)((g_trendFwhm[idx]-lo)*(r.bottom-r.top-44)/(hi-lo));if(i==0)MoveToEx(dc,x,y,0);else LineTo(dc,x,y);}SelectObject(dc,pc);wchar_t v[64];FormatFixed(lo,2,v);TextOutW(dc,r.left+8,r.bottom-20,v,WLen(v));FormatFixed(hi,2,v);TextOutW(dc,r.left+8,r.top+27,v,WLen(v));}SelectObject(dc,of);
}
static void DrawZonePanel(HDC dc){
    RECT r={1188,692,1548,900};FillRect(dc,&r,g_brushPlot);HGDIOBJ ob=SelectObject(dc,GetStockObject(5)),op=SelectObject(dc,g_penGrid);Rectangle(dc,r.left,r.top,r.right,r.bottom);int gridTop=r.top+42;for(int k=1;k<3;k++){int x=r.left+k*(r.right-r.left)/3,y=gridTop+k*(r.bottom-gridTop)/3;MoveToEx(dc,x,gridTop,0);LineTo(dc,x,r.bottom);MoveToEx(dc,r.left,y,0);LineTo(dc,r.right,y);}SelectObject(dc,op);SelectObject(dc,ob);SetBkMode(dc,TRANSPARENT);HFONT of=(HFONT)SelectObject(dc,g_smallFont);SetTextColor(dc,RGB(220,225,232));TextOutW(dc,r.left+10,r.top+5,L"Bildfeld · Median FWHM",22);wchar_t t[160];if(g_tiltValid){wchar_t d[30];FormatFixed(g_tiltMagnitude,2,d);wsprintfW(t,L"Δ %s px · %s",d,g_tiltDirection);SetTextColor(dc,g_tiltMagnitude<0.35?RGB(100,220,150):RGB(245,190,90));}else{lstrcpyW(t,L"Tilt: nicht genügend Zonen");SetTextColor(dc,RGB(130,140,155));}TextOutW(dc,r.left+10,r.top+22,t,WLen(t));for(int z=0;z<9;z++){int zx=z%3,zy=z/3,x=r.left+zx*(r.right-r.left)/3+7,y=gridTop+8+zy*(r.bottom-gridTop)/3;wchar_t v[48];if(g_zoneCount[z]){FormatFixed(g_zoneFwhm[z],2,v);lstrcatW(v,L" px");SetTextColor(dc,RGB(245,220,135));}else{lstrcpyW(v,L"–");SetTextColor(dc,RGB(120,130,145));}TextOutW(dc,x,y,v,WLen(v));}SelectObject(dc,of);
}
static void PaintMain(HDC dc){
    RECT all={0,0,1565,945};FillRect(dc,&all,g_brushWindow);
    RECT header={0,0,1565,56};FillRect(dc,&header,g_brushPlot);
    RECT left1={16,70,294,375},left2={16,387,294,630},left3={16,642,294,900};
    FillRect(dc,&left1,g_brushPlot);FillRect(dc,&left2,g_brushPlot);FillRect(dc,&left3,g_brushPlot);
    HGDIOBJ ob=SelectObject(dc,GetStockObject(5)),op=SelectObject(dc,g_penGrid);
    Rectangle(dc,left1.left,left1.top,left1.right,left1.bottom);Rectangle(dc,left2.left,left2.top,left2.right,left2.bottom);Rectangle(dc,left3.left,left3.top,left3.right,left3.bottom);
    SelectObject(dc,op);SelectObject(dc,ob);
    SetBkMode(dc,TRANSPARENT);HFONT of=(HFONT)SelectObject(dc,g_titleFont);SetTextColor(dc,RGB(244,247,252));TextOutW(dc,22,17,L"AstroFocus Studio 3.9.0 Engine",27);SelectObject(dc,of);
    HFONT sf=(HFONT)SelectObject(dc,g_smallFont);SetTextColor(dc,RGB(118,225,145));TextOutW(dc,390,22,g_cameraConnected?L"● Kamera verbunden":L"○ Kamera getrennt",g_cameraConnected?18:18);TextOutW(dc,560,22,g_focuserConnected?L"● Fokussierer verbunden":L"○ Fokussierer getrennt",g_focuserConnected?23:23);SetTextColor(dc,RGB(125,175,255));wchar_t pr[100]=L"Profil: ";wchar_t pn[64];GetWindowTextW(g_profileEdit,pn,64);lstrcatW(pr,pn);TextOutW(dc,790,22,pr,WLen(pr));
    SetTextColor(dc,RGB(220,225,235));TextOutW(dc,32,84,L"GERÄTE",6);TextOutW(dc,32,401,L"AUFNAHME",8);TextOutW(dc,32,656,L"FOKUSSIERER",12);
    SetTextColor(dc,RGB(180,190,205));TextOutW(dc,320,620,L"LIVE-FOKUS     AUTOFOKUS     BILDFELD     BAHTINOV     PROTOKOLL     ERWEITERT",78);SetTextColor(dc,RGB(65,145,255));TextOutW(dc,432,620,L"AUTOFOKUS",9);
    SelectObject(dc,sf);
    DrawPreview(dc);DrawCurve(dc);DrawRightStats(dc);DrawSelectedPanel(dc);DrawTrendPanel(dc);DrawZonePanel(dc);
}
static BOOL ParseStoredBool(LPCWSTR value,BOOL fallback){UINT parsed=0;return ParseStrictUIntW(value,&parsed)&&parsed<=1U?(parsed!=0):fallback;}
static void LoadSettings(){
    wchar_t v[256];UINT u=0;double d=0.0;
    ReadIni(L"Camera",L"",g_cameraId,256);SetWindowTextW(g_cameraEdit,g_cameraId);
    ReadIni(L"Focuser",L"",g_focuserId,256);SetWindowTextW(g_focuserEdit,g_focuserId);
    lstrcpyW(g_savedCameraId,g_cameraId);lstrcpyW(g_savedFocuserId,g_focuserId);

    ReadIni(L"Exposure",L"800",v,256);if(!ParseStrictDoubleW(v,&d)||d<1.0||d>60000.0)lstrcpyW(v,L"800");SetWindowTextW(g_exposureEdit,v);
    ReadIni(L"Gain",L"180",v,256);if(!ParseStrictUIntW(v,&u)||u>65535U)lstrcpyW(v,L"180");SetWindowTextW(g_gainEdit,v);
    ReadIni(L"ManualStep",L"100",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>1000000U)lstrcpyW(v,L"100");SetWindowTextW(g_manualStepEdit,v);
    ReadIni(L"AFPoints",L"9",v,256);u=NormalizeAfPointText(v);wsprintfW(v,L"%u",u);SetWindowTextW(g_afPointsEdit,v);
    ReadIni(L"AFStep",L"120",v,256);if(!ParseStrictUIntW(v,&u)||u<5U||u>1000000U)lstrcpyW(v,L"120");SetWindowTextW(g_afStepEdit,v);
    ReadIni(L"Backlash",L"250",v,256);if(!ParseStrictUIntW(v,&u)||u>1000000U)lstrcpyW(v,L"250");SetWindowTextW(g_afBacklashEdit,v);
    ReadIni(L"Samples",L"3",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>MAX_AF_SAMPLES)lstrcpyW(v,L"3");SetWindowTextW(g_afSamplesEdit,v);

    UINT safeMin=0,safeMax=200000;
    ReadIni(L"SafeMin",L"0",v,256);if(!ParseStrictUIntW(v,&safeMin)||safeMin>2147483647U)safeMin=0;
    ReadIni(L"SafeMax",L"200000",v,256);if(!ParseStrictUIntW(v,&safeMax)||safeMax>2147483647U)safeMax=200000;
    if(safeMax<=safeMin){safeMin=0;safeMax=200000;}g_safeMinPosition=(int)safeMin;g_safeMaxPosition=(int)safeMax;

    // Port 8873 is the mandatory local IPC channel used by the visible frontend.
    g_httpEnabled=TRUE;
    ReadIni(L"Simulator",L"0",v,256);BOOL startSimulator=ParseStoredBool(v,FALSE);
    ReadIni(L"SimulatorProfile",L"8",v,256);if(!ParseStrictUIntW(v,&u)||u>SIM_RANDOM)u=SIM_RANDOM;g_simProfileMode=(int)u;
    ReadIni(L"SimulatorBacklash",L"250",v,256);if(!ParseStrictUIntW(v,&u)||u>5000U)u=250;g_simBacklashSteps=(int)u;ReadIni(L"SimulatorSeed",L"2776572673",v,64);if(ParseStrictUIntW(v,&u)&&u>0U)g_simRandomSeed=u;g_simBacklashRemaining=0;SelectSimulatorProfile();
    ReadIni(L"AutoStretch",L"1",v,256);SetChecked(g_autoStretch,ParseStoredBool(v,TRUE));
    ReadIni(L"Stars",L"1",v,256);SetChecked(g_overlayStars,ParseStoredBool(v,TRUE));
    ReadIni(L"Labels",L"0",v,256);SetChecked(g_overlayLabels,ParseStoredBool(v,FALSE));
    ReadIni(L"Saturation",L"1",v,256);SetChecked(g_overlaySat,ParseStoredBool(v,TRUE));
    ReadIni(L"NativeToupTek",L"1",v,256);SetChecked(g_nativeCheck,ParseStoredBool(v,TRUE));ReadIni(L"ToupTekDllPath",L"",g_toupTekDllPath,700);if(g_toupTekDllPath[0]&&!IsSafeToupTekDllPath(g_toupTekDllPath))g_toupTekDllPath[0]=0;
    ReadIni(L"Zones",L"1",v,256);SetChecked(g_zoneCheck,ParseStoredBool(v,TRUE));
    ReadIni(L"Bahtinov",L"0",v,256);SetChecked(g_bahtinovCheck,ParseStoredBool(v,FALSE));
    ReadIni(L"PreferredOut",L"1",v,256);SetChecked(g_preferredDirCheck,ParseStoredBool(v,TRUE));
    ReadIni(L"Reconnect",L"1",v,256);SetChecked(g_reconnectCheck,ParseStoredBool(v,TRUE));

    ReadIni(L"RefocusMinutes",L"60",v,256);if(!ParseStrictDoubleW(v,&d)||d<0.0||d>100000.0)lstrcpyW(v,L"60");SetWindowTextW(g_refocusMinutesEdit,v);
    ReadIni(L"RefocusTemp",L"1,5",v,256);if(!ParseStrictDoubleW(v,&d)||d<0.0||d>100.0)lstrcpyW(v,L"1,5");SetWindowTextW(g_refocusTempEdit,v);
    ReadIni(L"RefocusFwhmPercent",L"30",v,256);if(!ParseStrictDoubleW(v,&d)||d<0.0||d>500.0)d=30.0;g_refocusFwhmThresholdPercent=d;g_focusDegradeFactor=1.0+d/100.0;g_degradationRefocusEnabled=d>0.0;
    ReadIni(L"RefocusBadFrames",L"3",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>100U)u=3;g_refocusBadFramesRequired=(int)u;
    ReadIni(L"RefocusMinStars",L"4",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>160U)u=4;g_refocusMinStars=(int)u;
    ReadIni(L"RefocusStability",L"0,45",v,256);if(!ParseStrictDoubleW(v,&d)||d<0.01||d>20.0)d=0.45;g_refocusStabilityLimit=d;
    ReadIni(L"RefocusCooldown",L"10",v,256);if(!ParseStrictDoubleW(v,&d)||d<0.0||d>1440.0)d=10.0;g_refocusCooldownMinutes=d;
    ReadIni(L"AutoRefocus",L"0",v,256);SetAutoRefocusEnabled(ParseStoredBool(v,FALSE));
    ReadIni(L"TempCompEnabled",L"0",v,256);g_tempCompEnabled=ParseStoredBool(v,FALSE);ReadIni(L"AutoStartPosition",L"0",v,256);g_autoStartPositionEnabled=ParseStoredBool(v,FALSE);
    ReadIni(L"TempCompDeadband",L"20",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>5000U)u=20;g_tempCompDeadbandSteps=(int)u;ReadIni(L"TempCompMaxStep",L"120",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>10000U)u=120;g_tempCompMaxStep=(int)u;
    ReadIni(L"ContinuousFocusEnabled",L"0",v,256);g_continuousFocusEnabled=ParseStoredBool(v,FALSE);ReadIni(L"ContinuousFocusFallback",L"1",v,256);g_continuousFocusFallback=ParseStoredBool(v,TRUE);ReadIni(L"ContinuousFocusMode",L"2",v,256);if(!ParseStrictUIntW(v,&u)||u>2U)u=2;g_continuousFocusMode=(int)u;ReadIni(L"ContinuousFocusMinFrames",L"4",v,256);if(!ParseStrictUIntW(v,&u)||u<3U||u>12U)u=4;g_continuousFocusMinFrames=(int)u;ReadIni(L"ContinuousFocusDeadband",L"3",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>1000U)u=3;g_continuousFocusDeadband=(int)u;ReadIni(L"ContinuousFocusMaxStep",L"12",v,256);if(!ParseStrictUIntW(v,&u)||u<1U||u>5000U)u=12;g_continuousFocusMaxStep=(int)u;if(g_continuousFocusMaxStep<g_continuousFocusDeadband)g_continuousFocusMaxStep=g_continuousFocusDeadband;ReadIni(L"ContinuousFocusConfidence",L"75",v,256);if(!ParseStrictUIntW(v,&u)||u<30U||u>100U)u=75;g_continuousFocusMinConfidence=(int)u;ReadIni(L"ContinuousFocusImprovement",L"1,5",v,256);if(!ParseStrictDoubleW(v,&d)||d<0.1||d>25.0)d=1.5;g_continuousFocusMinImprovement=d;ReadIni(L"ContinuousFocusSettleMs",L"700",v,256);if(!ParseStrictUIntW(v,&u)||u<100U||u>30000U)u=700;g_continuousFocusSettleMs=(int)u;if(g_continuousFocusEnabled){CopyWBounded(g_continuousFocusState,96,L"Wartet");CopyWBounded(g_continuousFocusReason,320,L"Wartet auf stabile Live-Messungen und verbundenen Fokussierer.");}
    ReadIni(L"RefocusOnMeridian",L"1",v,256);g_refocusOnMeridian=ParseStoredBool(v,TRUE);ReadIni(L"RefocusOnReconnect",L"1",v,256);g_refocusOnReconnect=ParseStoredBool(v,TRUE);ReadIni(L"RefocusOnFilter",L"1",v,256);g_refocusOnFilter=ParseStoredBool(v,TRUE);ReadIni(L"RefocusEveryCaptures",L"0",v,256);if(!ParseStrictUIntW(v,&u)||u>100000U)u=0;g_refocusEveryCaptures=(int)u;g_captureEventCounter=0;

    ReadIni(L"Profile",L"Standardprofil",v,64);CopyWBounded(g_activeProfileName,96,v);SetWindowTextW(g_profileEdit,g_activeProfileName);
    ReadIni(L"FocalLength",L"2032",v,256);if(!ParseStrictDoubleW(v,&d)||d<=0.0||d>100000.0)lstrcpyW(v,L"2032");SetWindowTextW(g_focalEdit,v);
    ReadIni(L"PixelSize",L"2,9",v,256);if(!ParseStrictDoubleW(v,&d)||d<=0.0||d>1000.0)lstrcpyW(v,L"2,9");SetWindowTextW(g_pixelEdit,v);
    LoadFocusProfileModel();if(startSimulator)SetSimulatorMode(TRUE);
}

static void CreateControls(){
    // Linke Seitenleiste: Geräte
    AddControl(L"STATIC",L"Kamera",SS_LEFT|SS_CENTERIMAGE,32,112,90,24,0,g_smallFont);
    g_cameraEdit=AddControl(L"EDIT",L"",WS_BORDER|ES_READONLY|ES_AUTOHSCROLL,32,138,246,28,0,g_font);
    AddControl(L"BUTTON",L"Auswählen …",BS_PUSHBUTTON|WS_TABSTOP,32,174,118,30,ID_CAMERA_SELECT,g_font);
    g_cameraConnect=AddControl(L"BUTTON",L"Verbinden",BS_PUSHBUTTON|WS_TABSTOP,158,174,120,30,ID_CAMERA_CONNECT,g_font);
    AddControl(L"STATIC",L"Fokussierer",SS_LEFT|SS_CENTERIMAGE,32,218,90,24,0,g_smallFont);
    g_focuserEdit=AddControl(L"EDIT",L"",WS_BORDER|ES_READONLY|ES_AUTOHSCROLL,32,244,246,28,0,g_font);
    AddControl(L"BUTTON",L"Auswählen …",BS_PUSHBUTTON|WS_TABSTOP,32,280,118,30,ID_FOCUSER_SELECT,g_font);
    g_focuserConnect=AddControl(L"BUTTON",L"Verbinden",BS_PUSHBUTTON|WS_TABSTOP,158,280,120,30,ID_FOCUSER_CONNECT,g_font);
    g_nativeCheck=AddControl(L"BUTTON",L"ToupTek direkt",BS_AUTOCHECKBOX|WS_TABSTOP,32,328,150,25,ID_NATIVE_CAMERA,g_smallFont);

    // Aufnahme
    AddControl(L"STATIC",L"Belichtung",SS_LEFT|SS_CENTERIMAGE,32,432,100,26,0,g_smallFont);g_exposureEdit=AddControl(L"EDIT",L"800",WS_BORDER|ES_AUTOHSCROLL,150,432,128,27,ID_EXPOSURE,g_font);
    AddControl(L"STATIC",L"Gain",SS_LEFT|SS_CENTERIMAGE,32,470,100,26,0,g_smallFont);g_gainEdit=AddControl(L"EDIT",L"180",WS_BORDER|ES_AUTOHSCROLL,150,470,128,27,ID_GAIN,g_font);
    g_liveButton=AddControl(L"BUTTON",L"Live-Fokus starten",BS_PUSHBUTTON|WS_TABSTOP,32,512,246,34,ID_LIVE,g_font);
    g_demoCheck=AddControl(L"BUTTON",L"Demo-Bildquelle",BS_AUTOCHECKBOX|WS_TABSTOP,32,558,145,25,ID_DEMO,g_smallFont);
    g_autoStretch=AddControl(L"BUTTON",L"Auto-Stretch",BS_AUTOCHECKBOX|WS_TABSTOP,32,590,118,25,ID_AUTO_STRETCH,g_smallFont);
    g_overlayStars=AddControl(L"BUTTON",L"Sterne",BS_AUTOCHECKBOX|WS_TABSTOP,158,590,85,25,ID_OVERLAY_STARS,g_smallFont);
    g_overlayLabels=AddControl(L"BUTTON",L"Werte",BS_AUTOCHECKBOX|WS_TABSTOP,32,614,85,25,ID_OVERLAY_LABELS,g_smallFont);
    g_overlaySat=AddControl(L"BUTTON",L"Sättigung",BS_AUTOCHECKBOX|WS_TABSTOP,122,614,100,25,ID_OVERLAY_SAT,g_smallFont);

    // Fokussierer
    AddControl(L"STATIC",L"Position",SS_LEFT|SS_CENTERIMAGE,32,692,95,27,0,g_smallFont);g_positionText=AddControl(L"STATIC",L"–",SS_LEFT|SS_CENTERIMAGE,150,692,128,27,0,g_monoFont);
    AddControl(L"STATIC",L"Schrittweite",SS_LEFT|SS_CENTERIMAGE,32,730,100,27,0,g_smallFont);g_manualStepEdit=AddControl(L"EDIT",L"100",WS_BORDER|ES_AUTOHSCROLL,150,730,128,27,ID_MANUAL_STEP,g_font);
    g_inButton=AddControl(L"BUTTON",L"◀ Innen",BS_PUSHBUTTON|WS_TABSTOP,32,774,74,32,ID_MOVE_IN,g_font);g_outButton=AddControl(L"BUTTON",L"Außen ▶",BS_PUSHBUTTON|WS_TABSTOP,112,774,80,32,ID_MOVE_OUT,g_font);g_haltButton=AddControl(L"BUTTON",L"■ Stopp",BS_PUSHBUTTON|WS_TABSTOP,198,774,80,32,ID_HALT,g_font);
    g_zoneCheck=AddControl(L"BUTTON",L"9-Zonen",BS_AUTOCHECKBOX|WS_TABSTOP,32,826,100,25,ID_OVERLAY_ZONES,g_smallFont);g_bahtinovCheck=AddControl(L"BUTTON",L"Bahtinov",BS_AUTOCHECKBOX|WS_TABSTOP,142,826,110,25,ID_BAHTINOV,g_smallFont);
    g_reconnectCheck=AddControl(L"BUTTON",L"Auto-Wiederverbinden",BS_AUTOCHECKBOX|WS_TABSTOP,32,858,180,25,ID_RECONNECT,g_smallFont);

    // Autofokus-Unterbereich
    AddControl(L"STATIC",L"Punkte",SS_LEFT|SS_CENTERIMAGE,320,680,78,27,0,g_smallFont);g_afPointsEdit=AddControl(L"EDIT",L"9",WS_BORDER|ES_AUTOHSCROLL,410,680,110,27,ID_AF_POINTS,g_font);
    AddControl(L"STATIC",L"Schritt",SS_LEFT|SS_CENTERIMAGE,320,718,78,27,0,g_smallFont);g_afStepEdit=AddControl(L"EDIT",L"120",WS_BORDER|ES_AUTOHSCROLL,410,718,110,27,ID_AF_STEP,g_font);
    AddControl(L"STATIC",L"Samples",SS_LEFT|SS_CENTERIMAGE,320,756,78,27,0,g_smallFont);g_afSamplesEdit=AddControl(L"EDIT",L"3",WS_BORDER|ES_AUTOHSCROLL,410,756,110,27,ID_AF_SAMPLES,g_font);
    AddControl(L"STATIC",L"Backlash",SS_LEFT|SS_CENTERIMAGE,320,794,78,27,0,g_smallFont);g_afBacklashEdit=AddControl(L"EDIT",L"250",WS_BORDER|ES_AUTOHSCROLL,410,794,110,27,ID_AF_BACKLASH,g_font);
    g_preferredDirCheck=AddControl(L"BUTTON",L"Finale Richtung: nach außen",BS_AUTOCHECKBOX|WS_TABSTOP,320,832,205,25,ID_PREFERRED_DIR,g_smallFont);
    g_stepAssistButton=AddControl(L"BUTTON",L"⚙ Schritt-Assistent",BS_PUSHBUTTON|WS_TABSTOP,536,720,136,36,ID_STEP_ASSIST,g_font);g_afButton=AddControl(L"BUTTON",L"◎ Autofokus starten",BS_PUSHBUTTON|WS_TABSTOP,536,766,136,42,ID_AF_START,g_font);
    g_autoRefocusCheck=AddControl(L"BUTTON",L"Auto-Refokus",BS_AUTOCHECKBOX|WS_TABSTOP,536,826,120,25,ID_AUTO_REFOCUS,g_smallFont);g_refocusMinutesEdit=AddControl(L"EDIT",L"60",WS_BORDER|ES_AUTOHSCROLL,536,858,55,25,ID_REFOCUS_MINUTES,g_smallFont);g_refocusTempEdit=AddControl(L"EDIT",L"1,5",WS_BORDER|ES_AUTOHSCROLL,600,858,55,25,ID_REFOCUS_TEMP,g_smallFont);g_diagnosticsButton=AddControl(L"BUTTON",L"Diagnose speichern",BS_PUSHBUTTON|WS_TABSTOP,1256,870,140,28,ID_DIAGNOSTICS,g_smallFont);g_overlayPresetButton=AddControl(L"BUTTON",L"Overlay: Analyse",BS_PUSHBUTTON|WS_TABSTOP,1060,295,150,28,ID_OVERLAY_PRESET,g_smallFont);g_httpCheck=AddControl(L"BUTTON",L"HTTP API :8873",BS_AUTOCHECKBOX|WS_TABSTOP,1400,870,130,28,ID_HTTP_TOGGLE,g_smallFont);SetChecked(g_httpCheck,g_httpEnabled);

    // unsichtbar kompakte Profil-/Teleskopparameter im rechten unteren Rand
    g_profileEdit=AddControl(L"EDIT",L"",WS_BORDER|ES_AUTOHSCROLL,1030,18,300,28,ID_PROFILE_NAME,g_smallFont);
    g_focalEdit=AddControl(L"EDIT",L"2032",WS_BORDER|ES_AUTOHSCROLL,1360,18,70,28,ID_FOCAL_LENGTH,g_smallFont);g_pixelEdit=AddControl(L"EDIT",L"2,9",WS_BORDER|ES_AUTOHSCROLL,1438,18,55,28,ID_PIXEL_SIZE,g_smallFont);
    AddControl(L"BUTTON",L"Bericht",BS_PUSHBUTTON|WS_TABSTOP,1498,18,58,28,ID_EXPORT_LOG,g_smallFont);
    g_status=AddControl(L"STATIC",L"Bereit – Kamera und Fokussierer auswählen",SS_LEFT|SS_CENTERIMAGE,20,914,1525,26,0,g_smallFont);
    LoadSettings();EnsureProfileLibrary();
}
static LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){
    if(msg==WM_TRAYICON&&lParam==WM_LBUTTONDBLCLK){OpenWebUi();return 0;}
    if(msg==WM_SIZE&&wParam==SIZE_MINIMIZED){ShowWindow(hwnd,SW_HIDE);SetStatus(L"Im Infobereich aktiv · Doppelklick zum Wiederherstellen");return 0;}
    if(msg==WM_DEVICECHANGE&&(wParam==DBT_DEVNODES_CHANGED||wParam==DBT_DEVICEARRIVAL||wParam==DBT_DEVICEREMOVECOMPLETE)){ULONGLONG now=GetTickCount64();g_cameraWorkerRetryAfter=now+1000ULL;g_focuserWorkerRetryAfter=now+1000ULL;if(wParam==DBT_DEVICEREMOVECOMPLETE){g_cameraRuntime.removalDetected=TRUE;g_focuserRuntime.removalDetected=TRUE;}SetStatus(L"Windows-Geräteänderung erkannt · Verbindungen werden sicher überprüft");return 1;}
    if(msg==WM_POWERBROADCAST){if(wParam==PBT_APMSUSPEND){PrepareHardwareForSuspend();}else if(wParam==PBT_APMRESUMEAUTOMATIC||wParam==PBT_APMRESUMESUSPEND){ULONGLONG now=GetTickCount64();g_resumeRecoveryPending=FALSE;g_cameraWorkerBlocked=HasOrphanWorker(TRUE);g_focuserWorkerBlocked=HasOrphanWorker(FALSE);g_cameraWorkerRetryAfter=now+2000ULL;g_focuserWorkerRetryAfter=now+2000ULL;g_lastCameraReconnect=0;g_lastFocuserReconnect=0;SetStatus(L"Windows fortgesetzt · Geräte werden vollständig neu verbunden und validiert");}return 1;}
    if(msg==WM_TOUPCAM){unsigned ev=(unsigned)wParam;if(ev==0x0004){if(g_exposing){ULONGLONG now=GetTickCount64();if((g_capturePurpose!=1||now-g_lastNativeProcessed>=180)&&now-g_exposureStarted>=(ULONGLONG)(g_lastExposureSeconds*900.0)){int purpose=g_capturePurpose;g_lastNativeProcessed=now;ProcessCompletedFrame(purpose);}}}else if(ev==0x0081||ev==0x0080||ev==0x0082){AbortExposure();g_lastCompletedPurpose=0;g_cameraConnected=FALSE;g_nativeActive=FALSE;g_cameraWanted=TRUE;SetWindowTextW(g_cameraConnect,L"Verbinden");if(g_afActive)StopAutofocus(FALSE,L"ToupTek-Kamera getrennt · Autofokus abgebrochen");if(g_stepAssistActive)StopStepAssistant(FALSE,L"ToupTek-Kamera getrennt · Schritt-Assistent abgebrochen");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"ToupTek-Kamera getrennt · Backlash-Kalibrierung abgebrochen");SetStatus(L"ToupTek-Kamera getrennt oder SDK-Fehler · Wiederverbindung möglich");}return 0;}
    if(msg==WM_COMMAND){UINT id=LOWORD(wParam);
        if(id==ID_CAMERA_SELECT)SelectDriver(TRUE);else if(id==ID_CAMERA_CONNECT){if(!ConnectCamera()&&g_lastCameraActionMessage[0])NotifyUser(g_lastCameraActionMessage,L"Kameraverbindung",MB_OK|MB_ICONERROR);}else if(id==ID_FOCUSER_SELECT)SelectDriver(FALSE);else if(id==ID_FOCUSER_CONNECT){if(!ConnectFocuser()&&g_lastFocuserActionMessage[0])NotifyUser(g_lastFocuserActionMessage,L"Fokussiererverbindung",MB_OK|MB_ICONERROR);}else if(id==ID_LIVE)StartLive();else if(id==ID_MOVE_IN)ManualMove(-1);else if(id==ID_MOVE_OUT)ManualMove(1);else if(id==ID_HALT)HaltFocuser();else if(id==ID_AF_START)StartAutofocus();else if(id==ID_STEP_ASSIST)StartStepAssistant();else if(id==ID_EXPORT_LOG)ExportReport(L"Manueller Export");else if(id==ID_DIAGNOSTICS){BOOL saved=SaveDiagnostics();NotifyUser(saved?L"Diagnosebericht wurde im Programmordner gespeichert.":L"Diagnosebericht konnte nicht vollständig gespeichert werden.",L"Diagnose",MB_OK|(saved?MB_ICONINFORMATION:MB_ICONWARNING));}else if(id==ID_HTTP_TOGGLE){g_httpEnabled=IsChecked(g_httpCheck);if(g_httpEnabled){if(StartHttpServer())SetStatus(L"HTTP-Schnittstelle aktiv: 127.0.0.1:8873");else SetStatus(L"HTTP-Schnittstelle konnte nicht gestartet werden");}else{StopHttpServer();SetStatus(L"HTTP-Schnittstelle deaktiviert");}}else if(id==ID_OVERLAY_PRESET){g_overlayPreset=(g_overlayPreset+1)%4;if(g_overlayPreset==0){SetChecked(g_overlayStars,FALSE);SetChecked(g_overlayLabels,FALSE);SetChecked(g_zoneCheck,FALSE);SetWindowTextW(g_overlayPresetButton,L"Overlay: Aus");}else if(g_overlayPreset==1){SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,FALSE);SetChecked(g_zoneCheck,FALSE);SetWindowTextW(g_overlayPresetButton,L"Overlay: Minimal");}else if(g_overlayPreset==2){SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,TRUE);SetChecked(g_zoneCheck,FALSE);SetWindowTextW(g_overlayPresetButton,L"Overlay: Analyse");}else{SetChecked(g_overlayStars,TRUE);SetChecked(g_overlayLabels,FALSE);SetChecked(g_zoneCheck,TRUE);SetWindowTextW(g_overlayPresetButton,L"Overlay: Bildfeld");}InvalidateRect(g_main,0,FALSE);}
        else if(id==ID_AUTO_STRETCH||id==ID_OVERLAY_STARS||id==ID_OVERLAY_LABELS||id==ID_OVERLAY_SAT||id==ID_OVERLAY_ZONES||id==ID_BAHTINOV||id==ID_PREFERRED_DIR||id==ID_RECONNECT||id==ID_NATIVE_CAMERA||id==ID_AUTO_REFOCUS){if(id==ID_AUTO_REFOCUS)SetAutoRefocusEnabled(IsChecked(g_autoRefocusCheck),TRUE);if(g_frameReady&&id==ID_BAHTINOV)RefreshSelectedStarAnalysis();if(g_frameReady&&id==ID_AUTO_STRETCH)BuildDisplay();InvalidateRect(g_main,0,FALSE);SaveSettings();}
        else if(id==ID_DEMO){g_demo=IsChecked(g_demoCheck);if(g_live){StopLive();StartLive();}SaveSettings();}
        return 0;
    }
    if(msg==WM_LBUTTONDOWN&&g_frameReady&&g_width>0&&g_height>0){int mx=(short)LOWORD(lParam),my=(short)HIWORD(lParam);int rw=g_imageRect.right-g_imageRect.left,rh=g_imageRect.bottom-g_imageRect.top;if(rw>0&&rh>0&&mx>=g_imageRect.left&&mx<g_imageRect.right&&my>=g_imageRect.top&&my<g_imageRect.bottom&&!g_afActive){int ix=(int)(((long long)(mx-g_imageRect.left)*g_width)/rw);int iy=(int)(((long long)(my-g_imageRect.top)*g_height)/rh);SetRuntimeOperation("engine window select-star");if(SelectManualStarAt(ix,iy)){g_bahtinovScore=0.0;g_bahtinovValid=FALSE;InvalidateRect(g_main,0,FALSE);SetStatus(L"Fokusstern manuell gewählt · Autofokus verwendet diesen Stern");}SetRuntimeOperation("idle");}return 0;}
    if(msg==WM_TIMER){if(wParam==TIMER_MAIN)TimerTick();return 0;}
    if(msg==WM_PAINT){PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);PaintMain(dc);EndPaint(hwnd,&ps);return 0;}
    if(msg==0x0014)return 1;
    if(msg==WM_CLOSE){SaveSettings();RemoveTrayIcon();StopHttpServer();SaveDiagnostics();if(g_afActive)StopAutofocus(FALSE,L"Autofokus beendet");if(g_stepAssistActive)StopStepAssistant(FALSE,L"Schritt-Assistent beendet");if(g_backlashCalActive)StopBacklashCalibration(FALSE,L"Backlash-Kalibrierung beendet");DestroyWindow(hwnd);return 0;}
    if(msg==WM_DESTROY){KillTimer(hwnd,TIMER_MAIN);DisconnectCamera();DisconnectFocuser();if(g_deviceHostJob){CloseHandle(g_deviceHostJob);g_deviceHostJob=0;}FreeImage();if(g_font)DeleteObject(g_font);if(g_smallFont)DeleteObject(g_smallFont);if(g_titleFont)DeleteObject(g_titleFont);if(g_monoFont)DeleteObject(g_monoFont);if(g_brushWindow)DeleteObject(g_brushWindow);if(g_brushPanel)DeleteObject(g_brushPanel);if(g_brushBlack)DeleteObject(g_brushBlack);if(g_brushPlot)DeleteObject(g_brushPlot);if(g_penGrid)DeleteObject(g_penGrid);if(g_penCurve)DeleteObject(g_penCurve);if(g_penPoint)DeleteObject(g_penPoint);if(g_penGood)DeleteObject(g_penGood);if(g_penBad)DeleteObject(g_penBad);if(g_penBest)DeleteObject(g_penBest);PostQuitMessage(0);return 0;}
    return DefWindowProcW(hwnd,msg,wParam,lParam);
}
static UINT RunEngineHealthCheck(){
    if(!g_appDir[0]||!g_dataDir[0])return 21;
    wchar_t cameraHost[1024],focuserHost[1024];lstrcpyW(cameraHost,g_appDir);lstrcatW(cameraHost,L"AstroFocusCameraHost.exe");lstrcpyW(focuserHost,g_appDir);lstrcatW(focuserHost,L"AstroFocusFocuserHost.exe");
    DWORD cameraAttributes=GetFileAttributesW(cameraHost);if(cameraAttributes==INVALID_FILE_ATTRIBUTES||(cameraAttributes&FILE_ATTRIBUTE_DIRECTORY))return 22;
    DWORD focuserAttributes=GetFileAttributesW(focuserHost);if(focuserAttributes==INVALID_FILE_ATTRIBUTES||(focuserAttributes&FILE_ATTRIBUTE_DIRECTORY))return 23;
    wchar_t path[1024];wsprintfW(path,L"%sHealthCheck-%u.tmp",g_dataDir,(DWORD)GetTickCount64());
    HANDLE h=CreateFileW(path,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return 24;
    const char marker[]="AstroFocus Studio 3.9.0 engine health check\r\n";DWORD wrote=0;BOOL ok=WriteFile(h,marker,(DWORD)(sizeof(marker)-1),&wrote,0)&&wrote==(DWORD)(sizeof(marker)-1);CloseHandle(h);DeleteFileW(path);
    return ok?0:25;
}
extern "C" void AstroFocusApplicationMain(){
    g_instance=(HINSTANCE)GetModuleHandleW(0);BuildIniPath();int healthCheckCount=AfCommandLineArgumentCount(GetCommandLineW(),L"--health-check");if(healthCheckCount<0||healthCheckCount>1)ExitProcess(2);if(healthCheckCount==1)ExitProcess(RunEngineHealthCheck());InstallBackendCrashHandler();g_sessionStartTick=GetTickCount64();SetRuntimeOperation("engine startup");ClearAutofocusError();lstrcpyW(g_lastAutoRefocusReason,L"deaktiviert");HRESULT hr=CoInitializeEx(0,COINIT_APARTMENTTHREADED);if(FAILED(hr))ExitProcess(1);
    g_font=CreateFontW(-16,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");g_smallFont=CreateFontW(-14,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");g_titleFont=CreateFontW(-21,0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");g_monoFont=CreateFontW(-17,0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Consolas");
    g_brushWindow=CreateSolidBrush(RGB(10,15,22));g_brushPanel=CreateSolidBrush(RGB(24,34,46));g_brushBlack=CreateSolidBrush(RGB(0,0,0));g_brushPlot=CreateSolidBrush(RGB(17,25,35));g_penGrid=CreatePen(PS_SOLID,1,RGB(49,64,82));g_penCurve=CreatePen(PS_SOLID,2,RGB(54,132,255));g_penPoint=CreatePen(PS_SOLID,2,RGB(245,195,80));g_penGood=CreatePen(PS_SOLID,1,RGB(90,230,145));g_penBad=CreatePen(PS_SOLID,2,RGB(255,85,85));g_penBest=CreatePen(PS_SOLID,1,RGB(245,105,210));
    LoadApplicationIcons();WNDCLASSEXW wc;memset(&wc,0,sizeof(wc));wc.cbSize=sizeof(wc);wc.style=CS_HREDRAW|CS_VREDRAW;wc.lpfnWndProc=WndProc;wc.hInstance=g_instance;wc.hCursor=LoadCursorW(0,IDC_ARROW);wc.hIcon=g_appIcon;wc.hIconSm=g_appIconSmall;wc.hbrBackground=g_brushWindow;wc.lpszClassName=L"AstroFocusEngineWindow";if(!RegisterClassExW(&wc)){CoUninitialize();ExitProcess(2);}
    g_main=CreateWindowExW(0,L"AstroFocusEngineWindow",L"AstroFocus Studio 3.9.0 Engine",WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_CLIPCHILDREN,CW_USEDEFAULT,CW_USEDEFAULT,1585,1000,0,0,g_instance,0);if(!g_main){CoUninitialize();ExitProcess(3);}SendMessageW(g_main,WM_SETICON,ICON_BIG,(LPARAM)g_appIcon);SendMessageW(g_main,WM_SETICON,ICON_SMALL,(LPARAM)g_appIconSmall);CreateControls();WriteSimulatorStage("00 engine initialized");SetRuntimeOperation("idle");g_httpEnabled=TRUE;SetChecked(g_httpCheck,TRUE);if(!StartHttpServer()){NotifyUser(L"Der lokale AstroFocus-Dienst konnte Port 8873 nicht öffnen.",L"AstroFocus Studio",MB_OK|MB_ICONERROR);}SetTimer(g_main,TIMER_MAIN,100,0);ShowWindow(g_main,SW_HIDE);UpdateWindow(g_main);MSG msg;while(GetMessageW(&msg,0,0,0)>0){TranslateMessage(&msg);DispatchMessageW(&msg);}CoUninitialize();ExitProcess(0);
}
