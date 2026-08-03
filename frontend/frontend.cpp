// AstroFocus Studio current version
#include "../common/version.h"
#include "../common/local_endpoint.h"

// Native Win32 user interface with System, Light and Dark designs. The hardware/analysis engine runs as a hidden local process.
// Camera backends: Simulator, generic USB/UVC via FFmpeg DirectShow, ToupTek SDK, ASCOM.

extern "C" {
int _fltused=0;
typedef unsigned char BYTE; typedef unsigned short WORD; typedef unsigned short ATOM; typedef unsigned int UINT;
#ifdef ASTROFOCUS_NATIVE_TEST
typedef unsigned int DWORD; typedef int LONG;
#else
typedef unsigned long DWORD; typedef long LONG;
#endif
typedef long long LONGLONG; typedef unsigned long long ULONGLONG; typedef unsigned long long ULONG_PTR; typedef long long LONG_PTR; typedef ULONG_PTR WPARAM; typedef LONG_PTR LPARAM; typedef LONG_PTR LRESULT; typedef ULONG_PTR UINT_PTR; typedef unsigned long long SIZE_T; typedef SIZE_T size_t; typedef int BOOL; typedef void* HANDLE; typedef HANDLE HINSTANCE; typedef HANDLE HMODULE; typedef HANDLE HWND; typedef HANDLE HMENU; typedef HANDLE HICON; typedef HANDLE HCURSOR; typedef HANDLE HBRUSH; typedef HANDLE HGDIOBJ; typedef HANDLE HFONT; typedef HANDLE HPEN; typedef HANDLE HDC; typedef HANDLE HKEY; typedef const wchar_t* LPCWSTR; typedef wchar_t* LPWSTR; typedef const char* LPCSTR; typedef void* LPVOID; typedef const void* LPCVOID; typedef void* FARPROC;
#ifdef _MSC_VER
#define WINAPI __stdcall
#define CALLBACK __stdcall
#else
#define WINAPI __attribute__((stdcall))
#define CALLBACK __attribute__((stdcall))
#endif
struct POINT{LONG x,y;}; struct RECT{LONG left,top,right,bottom;};
struct MSG{HWND hwnd;UINT message;WPARAM wParam;LPARAM lParam;DWORD time;POINT pt;DWORD lPrivate;};
struct PAINTSTRUCT{HDC hdc;BOOL fErase;RECT rcPaint;BOOL fRestore;BOOL fIncUpdate;BYTE rgbReserved[32];};
struct WNDCLASSEXW{UINT cbSize,style;void* lpfnWndProc;int cbClsExtra,cbWndExtra;HINSTANCE hInstance;HICON hIcon;HCURSOR hCursor;HBRUSH hbrBackground;LPCWSTR lpszMenuName,lpszClassName;HICON hIconSm;};
struct BITMAPINFOHEADER{DWORD biSize;LONG biWidth,biHeight;WORD biPlanes,biBitCount;DWORD biCompression,biSizeImage;LONG biXPelsPerMeter,biYPelsPerMeter;DWORD biClrUsed,biClrImportant;}; struct RGBQUAD{BYTE rgbBlue,rgbGreen,rgbRed,rgbReserved;}; struct BITMAPINFO{BITMAPINFOHEADER bmiHeader;RGBQUAD bmiColors[1];};
struct SECURITY_ATTRIBUTES{DWORD nLength;LPVOID lpSecurityDescriptor;BOOL bInheritHandle;};
struct STARTUPINFOW{DWORD cb;LPWSTR lpReserved,lpDesktop,lpTitle;DWORD dwX,dwY,dwXSize,dwYSize,dwXCountChars,dwYCountChars,dwFillAttribute,dwFlags;WORD wShowWindow,cbReserved2;BYTE* lpReserved2;HANDLE hStdInput,hStdOutput,hStdError;};
struct PROCESS_INFORMATION{HANDLE hProcess,hThread;DWORD dwProcessId,dwThreadId;};
struct MINMAXINFO{POINT ptReserved,ptMaxSize,ptMaxPosition,ptMinTrackSize,ptMaxTrackSize;};
struct HIGHCONTRASTW_MIN{UINT cbSize;DWORD dwFlags;LPWSTR lpszDefaultScheme;};
struct SYSTEMTIME{WORD wYear,wMonth,wDayOfWeek,wDay,wHour,wMinute,wSecond,wMilliseconds;};
struct OPENFILENAMEW_MIN{DWORD lStructSize;HWND hwndOwner;HINSTANCE hInstance;LPCWSTR lpstrFilter;LPWSTR lpstrCustomFilter;DWORD nMaxCustFilter;DWORD nFilterIndex;LPWSTR lpstrFile;DWORD nMaxFile;LPWSTR lpstrFileTitle;DWORD nMaxFileTitle;LPCWSTR lpstrInitialDir;LPCWSTR lpstrTitle;DWORD Flags;WORD nFileOffset,nFileExtension;LPCWSTR lpstrDefExt;LPARAM lCustData;void* lpfnHook;LPCWSTR lpTemplateName;void* pvReserved;DWORD dwReserved;DWORD FlagsEx;};
struct EXCEPTION_RECORD_MIN{DWORD ExceptionCode,ExceptionFlags;EXCEPTION_RECORD_MIN* ExceptionRecord;void* ExceptionAddress;DWORD NumberParameters;ULONG_PTR ExceptionInformation[15];};
struct EXCEPTION_POINTERS_MIN{EXCEPTION_RECORD_MIN* ExceptionRecord;void* ContextRecord;};
struct MEMORY_BASIC_INFORMATION_MIN{void* BaseAddress;void* AllocationBase;DWORD AllocationProtect;DWORD Alignment1;SIZE_T RegionSize;DWORD State;DWORD Protect;DWORD Type;DWORD Alignment2;};
typedef LONG (WINAPI *TOP_LEVEL_EXCEPTION_FILTER_MIN)(EXCEPTION_POINTERS_MIN*);
typedef TOP_LEVEL_EXCEPTION_FILTER_MIN (WINAPI *PFN_SetUnhandledExceptionFilter_MIN)(TOP_LEVEL_EXCEPTION_FILTER_MIN);

HMODULE WINAPI GetModuleHandleW(LPCWSTR); void WINAPI ExitProcess(UINT); DWORD WINAPI GetModuleFileNameW(HMODULE,LPWSTR,DWORD); DWORD WINAPI GetTempPathW(DWORD,LPWSTR); DWORD WINAPI GetEnvironmentVariableW(LPCWSTR,LPWSTR,DWORD); BOOL WINAPI CreateDirectoryW(LPCWSTR,SECURITY_ATTRIBUTES*); DWORD WINAPI GetLastError(void); DWORD WINAPI GetCurrentProcessId(void); SIZE_T WINAPI VirtualQuery(LPCVOID,MEMORY_BASIC_INFORMATION_MIN*,SIZE_T); HMODULE WINAPI LoadLibraryW(LPCWSTR); FARPROC WINAPI GetProcAddress(HMODULE,const char*); BOOL WINAPI FreeLibrary(HMODULE); int WINAPI lstrlenW(LPCWSTR); LPWSTR WINAPI lstrcpyW(LPWSTR,LPCWSTR); LPWSTR WINAPI lstrcatW(LPWSTR,LPCWSTR); HANDLE WINAPI GetProcessHeap(void); LPVOID WINAPI HeapAlloc(HANDLE,DWORD,SIZE_T); BOOL WINAPI HeapFree(HANDLE,DWORD,LPVOID); ULONGLONG WINAPI GetTickCount64(void); void WINAPI GetLocalTime(SYSTEMTIME*); void WINAPI Sleep(DWORD); HANDLE WINAPI CreateFileW(LPCWSTR,DWORD,DWORD,SECURITY_ATTRIBUTES*,DWORD,DWORD,HANDLE); BOOL WINAPI ReadFile(HANDLE,LPVOID,DWORD,DWORD*,LPVOID); BOOL WINAPI WriteFile(HANDLE,LPCVOID,DWORD,DWORD*,LPVOID); BOOL WINAPI FlushFileBuffers(HANDLE); BOOL WINAPI CloseHandle(HANDLE); DWORD WINAPI GetFileSize(HANDLE,DWORD*); DWORD WINAPI SetFilePointer(HANDLE,LONG,LONG*,DWORD); BOOL WINAPI DeleteFileW(LPCWSTR); BOOL WINAPI MoveFileExW(LPCWSTR,LPCWSTR,DWORD); DWORD WINAPI GetFileAttributesW(LPCWSTR); BOOL WINAPI CreateProcessW(LPCWSTR,LPWSTR,SECURITY_ATTRIBUTES*,SECURITY_ATTRIBUTES*,BOOL,DWORD,LPVOID,LPCWSTR,STARTUPINFOW*,PROCESS_INFORMATION*); DWORD WINAPI WaitForSingleObject(HANDLE,DWORD); BOOL WINAPI GetExitCodeProcess(HANDLE,DWORD*); BOOL WINAPI TerminateProcess(HANDLE,UINT); int WINAPI MultiByteToWideChar(UINT,DWORD,LPCSTR,int,LPWSTR,int); int WINAPI WideCharToMultiByte(UINT,DWORD,LPCWSTR,int,char*,int,LPCSTR,BOOL*);
ATOM WINAPI RegisterClassExW(const WNDCLASSEXW*); HWND WINAPI CreateWindowExW(DWORD,LPCWSTR,LPCWSTR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID); LRESULT WINAPI DefWindowProcW(HWND,UINT,WPARAM,LPARAM); BOOL WINAPI ShowWindow(HWND,int); BOOL WINAPI UpdateWindow(HWND); BOOL WINAPI GetMessageW(MSG*,HWND,UINT,UINT); BOOL WINAPI TranslateMessage(const MSG*); LRESULT WINAPI DispatchMessageW(const MSG*); void WINAPI PostQuitMessage(int); BOOL WINAPI PostMessageW(HWND,UINT,WPARAM,LPARAM); BOOL WINAPI SetWindowTextW(HWND,LPCWSTR); int WINAPI GetWindowTextW(HWND,LPWSTR,int); int WINAPI MessageBoxW(HWND,LPCWSTR,LPCWSTR,UINT); LRESULT WINAPI SendMessageW(HWND,UINT,WPARAM,LPARAM); HCURSOR WINAPI LoadCursorW(HINSTANCE,LPCWSTR); HICON WINAPI LoadIconW(HINSTANCE,LPCWSTR); HANDLE WINAPI LoadImageW(HINSTANCE,LPCWSTR,UINT,int,int,UINT); int WINAPI wsprintfW(LPWSTR,LPCWSTR,...); UINT_PTR WINAPI SetTimer(HWND,UINT_PTR,UINT,void*); BOOL WINAPI KillTimer(HWND,UINT_PTR); BOOL WINAPI InvalidateRect(HWND,const RECT*,BOOL); HDC WINAPI BeginPaint(HWND,PAINTSTRUCT*); BOOL WINAPI EndPaint(HWND,const PAINTSTRUCT*); BOOL WINAPI DestroyWindow(HWND); BOOL WINAPI GetClientRect(HWND,RECT*); BOOL WINAPI MoveWindow(HWND,int,int,int,int,BOOL); BOOL WINAPI EnableWindow(HWND,BOOL); int WINAPI FillRect(HDC,const RECT*,HBRUSH); int WINAPI DrawTextW(HDC,LPCWSTR,int,RECT*,UINT); HWND WINAPI SetFocus(HWND);
HFONT WINAPI CreateFontW(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCWSTR); BOOL WINAPI DeleteObject(HGDIOBJ); HBRUSH WINAPI CreateSolidBrush(DWORD); HPEN WINAPI CreatePen(int,int,DWORD); HGDIOBJ WINAPI SelectObject(HDC,HGDIOBJ); DWORD WINAPI SetTextColor(HDC,DWORD); DWORD WINAPI SetBkColor(HDC,DWORD); int WINAPI SetBkMode(HDC,int); BOOL WINAPI TextOutW(HDC,int,int,LPCWSTR,int); int WINAPI StretchDIBits(HDC,int,int,int,int,int,int,int,int,const void*,const BITMAPINFO*,UINT,DWORD); BOOL WINAPI MoveToEx(HDC,int,int,POINT*); BOOL WINAPI LineTo(HDC,int,int); BOOL WINAPI Rectangle(HDC,int,int,int,int); BOOL WINAPI Ellipse(HDC,int,int,int,int); HGDIOBJ WINAPI GetStockObject(int); HDC WINAPI CreateCompatibleDC(HDC); BOOL WINAPI DeleteDC(HDC); HGDIOBJ WINAPI CreateCompatibleBitmap(HDC,int,int); BOOL WINAPI BitBlt(HDC,int,int,int,int,HDC,int,int,DWORD);
void* memset(void*,int,SIZE_T); void* memcpy(void*,const void*,SIZE_T); int sprintf(char*,const char*,...); int sscanf(const char*,const char*,...); char* strstr(const char*,const char*); char* strchr(const char*,int); size_t strlen(const char*); int strcmp(const char*,const char*); int atoi(const char*); double atof(const char*);
}

#define TRUE 1
#define FALSE 0
#define NULL 0
#define RGB(r,g,b) ((DWORD)(((BYTE)(r))|((WORD)((BYTE)(g))<<8)|(((DWORD)(BYTE)(b))<<16)))
#define LOWORD(l) ((WORD)((ULONG_PTR)(l)&0xffff))
#define HIWORD(l) ((WORD)(((ULONG_PTR)(l)>>16)&0xffff))
#define MAKELPARAM(l,h) ((LPARAM)(ULONG_PTR)(((WORD)(l))|((DWORD)((WORD)(h)))<<16))
#define CW_USEDEFAULT ((int)0x80000000)
#define WS_OVERLAPPED 0x00000000L
#define WS_CAPTION 0x00C00000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
#define WS_CHILD 0x40000000L
#define WS_VISIBLE 0x10000000L
#define WS_TABSTOP 0x00010000L
#define WS_BORDER 0x00800000L
#define WS_VSCROLL 0x00200000L
#define WS_CLIPCHILDREN 0x02000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define ES_LEFT 0x0000L
#define ES_AUTOHSCROLL 0x0080L
#define ES_NUMBER 0x2000L
#define ES_READONLY 0x0800L
#define ES_MULTILINE 0x0004L
#define ES_AUTOVSCROLL 0x0040L
#define BS_PUSHBUTTON 0x00000000L
#define BS_DEFPUSHBUTTON 0x00000001L
#define BS_AUTOCHECKBOX 0x00000003L
#define BS_MULTILINE 0x00002000L
#define BS_GROUPBOX 0x00000007L
#define SS_LEFT 0x00000000L
#define SS_CENTERIMAGE 0x00000200L
#define CBS_DROPDOWN 0x0002L
#define CBS_DROPDOWNLIST 0x0003L
#define CBS_AUTOHSCROLL 0x0040L
#define SW_SHOW 5
#define SW_HIDE 0
#define SW_MAXIMIZE 3
#define OFN_OVERWRITEPROMPT 0x00000002
#define OFN_PATHMUSTEXIST 0x00000800
#define OFN_FILEMUSTEXIST 0x00001000
#define OFN_EXPLORER 0x00080000
#define SIZE_MINIMIZED 1
#define WM_DESTROY 0x0002
#define WM_SIZE 0x0005
#define WM_SYSCOLORCHANGE 0x0015
#define WM_SETTINGCHANGE 0x001A
#define WM_THEMECHANGED 0x031A
#define WM_PAINT 0x000F
#define WM_ERASEBKGND 0x0014
#define WM_CLOSE 0x0010
#define WM_COMMAND 0x0111
#define WM_TIMER 0x0113
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_GETMINMAXINFO 0x0024
#define WM_APP 0x8000
#define WM_APP_SELECT_STAR (WM_APP+41)
#define WM_APP_EXECUTE_COMMAND (WM_APP+42)
#define WM_APP_START_ENGINE (WM_APP+43)
#define WM_SETFONT 0x0030
#define WM_CTLCOLOREDIT 0x0133
#define WM_CTLCOLORLISTBOX 0x0134
#define WM_CTLCOLORBTN 0x0135
#define WM_CTLCOLORSTATIC 0x0138
#define BN_CLICKED 0
#define CBN_SELCHANGE 1
#define EN_CHANGE 0x0300
#define EM_SETMARGINS 0x00D3
#define EC_LEFTMARGIN 0x0001
#define EC_RIGHTMARGIN 0x0002
#define BM_GETCHECK 0x00F0
#define BM_SETCHECK 0x00F1
#define BST_CHECKED 1
#define CB_ADDSTRING 0x0143
#define CB_RESETCONTENT 0x014B
#define CB_GETCURSEL 0x0147
#define CB_SETCURSEL 0x014E
#define CB_GETLBTEXT 0x0148
#define CB_RESETCONTENT 0x014B
#define CB_SETMINVISIBLE 0x1701
#define MB_OK 0x00000000L
#define MB_ICONINFORMATION 0x00000040L
#define MB_ICONWARNING 0x00000030L
#define MB_ICONERROR 0x00000010L
#define IDYES 6
#define MB_YESNO 0x00000004L
#define IDC_ARROW ((LPCWSTR)32512)
#define IDI_APPLICATION ((LPCWSTR)32512)
#define IMAGE_ICON 1
#define LR_LOADFROMFILE 0x0010
#define LR_DEFAULTSIZE 0x0040
#define WM_SETICON 0x0080
#define ICON_SMALL 0
#define ICON_BIG 1
#define CS_HREDRAW 0x0002
#define CS_VREDRAW 0x0001
#define FW_NORMAL 400
#define FW_SEMIBOLD 600
#define DEFAULT_CHARSET 1
#define OUT_DEFAULT_PRECIS 0
#define CLIP_DEFAULT_PRECIS 0
#define CLEARTYPE_QUALITY 5
#define DEFAULT_PITCH 0
#define FF_DONTCARE 0
#define TRANSPARENT 1
#define BI_RGB 0
#define DIB_RGB_COLORS 0
#define SRCCOPY 0x00CC0020
#define PS_SOLID 0
#define PS_DASH 1
#define WHITE_BRUSH 0
#define NULL_BRUSH 5
#define GENERIC_READ 0x80000000UL
#define GENERIC_WRITE 0x40000000UL
#define FILE_SHARE_READ 0x00000001UL
#define FILE_SHARE_WRITE 0x00000002UL
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define FILE_END 2
#define FILE_ATTRIBUTE_NORMAL 0x80
#define MOVEFILE_REPLACE_EXISTING 0x00000001UL
#define MOVEFILE_WRITE_THROUGH 0x00000008UL
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define INVALID_FILE_ATTRIBUTES 0xffffffffUL
#define ERROR_ALREADY_EXISTS 183UL
#define ERROR_CLASS_ALREADY_EXISTS 1410UL
#define FILE_BEGIN 0
#define HEAP_ZERO_MEMORY 0x00000008
#define STARTF_USESHOWWINDOW 0x00000001
#define STARTF_USESTDHANDLES 0x00000100
#define SW_HIDE_CONST 0
#define CREATE_NO_WINDOW 0x08000000
#define CREATE_NEW_PROCESS_GROUP 0x00000200
#define INFINITE 0xffffffffUL
#define WAIT_OBJECT_0 0
#define CP_UTF8 65001
#define CP_ACP 0
#define DT_LEFT 0x00000000
#define DT_CENTER 0x00000001
#define DT_RIGHT 0x00000002
#define DT_VCENTER 0x00000004
#define DT_SINGLELINE 0x00000020
#define DT_WORDBREAK 0x00000010
#define DT_END_ELLIPSIS 0x00008000
#define DT_EDITCONTROL 0x00002000
#define DT_CALCRECT 0x00000400
#define DT_NOPREFIX 0x00000800

// Dynamic winsock client.
typedef unsigned long long SOCKET; struct SOCKADDR{unsigned short sa_family;char sa_data[14];}; struct IN_ADDR{unsigned long s_addr;}; struct SOCKADDR_IN{short sin_family;unsigned short sin_port;IN_ADDR sin_addr;char sin_zero[8];};
// WSAStartup writes the complete platform WSADATA structure. Keep this opaque and deliberately
// oversized instead of duplicating a version-sensitive SDK layout by hand.
struct alignas(16) WSADATA_STORAGE{BYTE bytes[512];};
typedef int (WINAPI *PFN_WSAStartup)(WORD,void*); typedef int (WINAPI *PFN_WSACleanup)(void); typedef SOCKET (WINAPI *PFN_socket)(int,int,int); typedef int (WINAPI *PFN_connect)(SOCKET,const SOCKADDR*,int); typedef int (WINAPI *PFN_recv)(SOCKET,char*,int,int); typedef int (WINAPI *PFN_send)(SOCKET,const char*,int,int); typedef int (WINAPI *PFN_closesocket)(SOCKET); typedef int (WINAPI *PFN_setsockopt)(SOCKET,int,int,const char*,int); typedef unsigned short (WINAPI *PFN_htons)(unsigned short); typedef unsigned long (WINAPI *PFN_htonl)(unsigned long);
static HMODULE g_ws2=0; static PFN_WSAStartup pWSAStartup=0; static PFN_WSACleanup pWSACleanup=0; static PFN_socket p_socket=0; static PFN_connect p_connect=0; static PFN_recv p_recv=0; static PFN_send p_send=0; static PFN_closesocket p_closesocket=0; static PFN_setsockopt p_setsockopt=0; static PFN_htons p_htons=0; static PFN_htonl p_htonl=0;
#define INVALID_SOCKET_VALUE ((SOCKET)(~0ULL))
#define AF_INET_MIN 2
#define SOCK_STREAM_MIN 1
#define IPPROTO_TCP_MIN 6
#define INADDR_LOOPBACK_MIN 0x7f000001UL
#define SOL_SOCKET_MIN 0xffff
#define SO_SNDTIMEO_MIN 0x1005
#define SO_RCVTIMEO_MIN 0x1006

#ifndef ASTROFOCUS_NATIVE_TEST
static_assert(sizeof(DWORD)==4,"Windows ABI: DWORD must be 32-bit");
static_assert(sizeof(LONG)==4,"Windows ABI: LONG must be 32-bit");
static_assert(sizeof(POINT)==8,"Windows ABI: POINT layout mismatch");
static_assert(sizeof(RECT)==16,"Windows ABI: RECT layout mismatch");
static_assert(sizeof(MSG)==48,"Windows x64 ABI: MSG layout mismatch");
static_assert(sizeof(PAINTSTRUCT)==72,"Windows x64 ABI: PAINTSTRUCT layout mismatch");
static_assert(sizeof(WNDCLASSEXW)==80,"Windows x64 ABI: WNDCLASSEXW layout mismatch");
static_assert(sizeof(BITMAPINFOHEADER)==40,"Windows ABI: BITMAPINFOHEADER layout mismatch");
static_assert(sizeof(SECURITY_ATTRIBUTES)==24,"Windows x64 ABI: SECURITY_ATTRIBUTES layout mismatch");
static_assert(sizeof(STARTUPINFOW)==104,"Windows x64 ABI: STARTUPINFOW layout mismatch");
static_assert(sizeof(PROCESS_INFORMATION)==24,"Windows x64 ABI: PROCESS_INFORMATION layout mismatch");
static_assert(sizeof(MINMAXINFO)==40,"Windows ABI: MINMAXINFO layout mismatch");
static_assert(sizeof(SOCKADDR_IN)==16,"Windows ABI: SOCKADDR_IN layout mismatch");
static_assert(sizeof(WSADATA_STORAGE)>=408,"Windows x64 ABI: WSA startup storage too small");
static_assert(sizeof(MEMORY_BASIC_INFORMATION_MIN)==48,"Windows x64 ABI: MEMORY_BASIC_INFORMATION layout mismatch");

#endif

#define ID_CAMERA_BACKEND 1001
#define ID_CAMERA_DEVICE 1002
#define ID_CAMERA_REFRESH 1003
#define ID_CAMERA_SELECT 1004
#define ID_CAMERA_CONNECT 1005
#define ID_EXPOSURE 1006
#define ID_GAIN 1007
#define ID_LIVE 1008
#define ID_STRETCH 1009
#define ID_STARS 1010
#define ID_VALUES 1011
#define ID_SATURATION 1012
#define ID_ZONES 1013
#define ID_FOCUSER_BACKEND 1020
#define ID_FOCUSER_DEVICE 1021
#define ID_FOCUSER_SELECT 1022
#define ID_FOCUSER_CONNECT 1023
#define ID_MANUAL_STEP 1024
#define ID_MOVE_IN 1025
#define ID_MOVE_OUT 1026
#define ID_HALT 1027
#define ID_SAFE_MIN 1028
#define ID_SAFE_MAX 1029
#define ID_FOCUSER_SETUP 1030
#define ID_TAB_LIVE 1040
#define ID_TAB_AUTO 1041
#define ID_TAB_FIELD 1042
#define ID_TAB_BAHT 1043
#define ID_TAB_LOG 1044
#define ID_TAB_AUTOMATION 1045
#define ID_TAB_TESTS 1046
#define ID_TAB_ANALYSIS 1047
#define ID_TAB_CONTINUOUS 1048
#define ID_AF_POINTS 1060
#define ID_AF_STEP 1061
#define ID_AF_SAMPLES 1062
#define ID_BACKLASH 1063
#define ID_PREF_OUT 1064
#define ID_STEP_ASSIST 1065
#define ID_AF_START 1066
#define ID_AF_STOP 1067
#define ID_AF_USE_SELECTED 1068
#define ID_AF_CLEAR_SELECTED 1069
#define ID_BAHT_ENABLE 1070
#define ID_DIAGNOSTICS 1080
#define ID_EXPORT 1081
#define ID_AUTO_REFOCUS 1090
#define ID_REFOCUS_MIN 1091
#define ID_REFOCUS_TEMP 1092
#define ID_SAVE_ADV 1093
#define ID_REFOCUS_FWHM 1094
#define ID_REFOCUS_BAD_FRAMES 1095
#define ID_REFOCUS_MIN_STARS 1096
#define ID_REFOCUS_STABILITY 1097
#define ID_REFOCUS_COOLDOWN 1098
#define ID_REFOCUS_RESUME 1099
#define ID_SELFTEST 1100
#define ID_PROFILE 1110
#define ID_SAVE_PROFILE 1111
#define ID_LOAD_PROFILE 1112
#define ID_DELETE_PROFILE 1113
#define ID_IMPORT_PROFILE 1114
#define ID_EXPORT_PROFILE 1115
#define ID_BACKLASH_CAL 1120
#define ID_TEMP_COMP 1121
#define ID_AUTO_START_POS 1122
#define ID_FILTER_NAME 1123
#define ID_FILTER_LEARN 1124
#define ID_FILTER_APPLY 1125
#define ID_EVT_MERIDIAN 1126
#define ID_EVT_RECONNECT 1127
#define ID_EVT_FILTER 1128
#define ID_REFOCUS_CAPTURES 1129
#define ID_AUTOMATION_DETAILS 1130
#define ID_SIM_PROFILE 1131
#define ID_SIM_BACKLASH 1132
#define ID_SIM_APPLY 1133
#define ID_SIM_RANDOMIZE 1134
#define ID_THEME 1135
#define ID_VIEW_MODE 1136
#define ID_CF_ENABLE 1140
#define ID_CF_MODE 1141
#define ID_CF_FALLBACK 1142
#define ID_CF_MIN_FRAMES 1143
#define ID_CF_DEADBAND 1144
#define ID_CF_MAX_STEP 1145
#define ID_CF_CONFIDENCE 1146
#define ID_CF_IMPROVEMENT 1147
#define ID_CF_SETTLE 1148
#define ID_CF_SAVE 1149
#define ID_CF_RESET 1150
#define ID_CF_RESUME 1151
#define TIMER_POLL 1
#define TIMER_FRAME 2

enum ThemeMode{THEME_SYSTEM=0,THEME_LIGHT=1,THEME_DARK=2};
struct ThemePalette{
    DWORD background,panel,input,textPrimary,textSecondary,textMuted,title,border,grid,accent;
    DWORD card,overlayBox,previewMessage,simBadge,simBadgeText,referenceText,thresholdText,markerText;
    DWORD successText,errorText,warningText,cautionText,connectionGood,connectionBad;
};
static ThemePalette g_theme;
static int g_themeMode=THEME_SYSTEM;static BOOL g_darkTheme=FALSE,g_highContrast=FALSE,g_themeRefreshActive=FALSE;
static HINSTANCE g_inst=0; static HWND g_main=0; static HICON g_appIcon=0,g_appIconSmall=0; static BOOL g_uiInitialized=FALSE; static HFONT g_font=0,g_small=0,g_title=0,g_mono=0; static HBRUSH g_bg=0,g_panel=0,g_input=0,g_accentBrush=0; static HPEN g_border=0,g_grid=0,g_curve=0,g_good=0,g_bad=0,g_reference=0,g_threshold=0,g_marker=0;
static wchar_t g_appDir[600]=L"",g_frontendLogPath[700]=L"",g_themeSettingsPath[700]=L""; static DWORD g_themeSettingsLastError=0; static HANDLE g_engineProcess=0,g_uvcProcess=0,g_focuserSetupProcess=0,g_ascomChooserProcess=0; static BOOL g_engineOnline=FALSE,g_engineStartupAttempted=FALSE,g_winsockReady=FALSE,g_focuserSetupReconnect=FALSE,g_focuserSetupEngineLock=FALSE,g_ascomChooserCamera=FALSE; static int g_controlCreationFailures=0; static int g_ascomChooserExpectedBackend=-1; static wchar_t g_ascomChooserResultPath[700]=L""; static int g_activeTab=0; static BOOL g_expertMode=TRUE,g_automationDetailsExpanded=FALSE;
static wchar_t g_lastApiMessage[640]=L""; static BOOL g_lastApiTransportFailure=FALSE; static BOOL g_toupTekPickerCancelled=FALSE;
static int g_cameraBackendSelection=-1,g_focuserBackendSelection=-1,g_lastNonSimulatorCameraBackend=3;
static RECT g_leftCamera={0,0,0,0},g_leftFocuser={0,0,0,0},g_preview={0,0,0,0},g_page={0,0,0,0},g_rightAnalysis={0,0,0,0},g_rightStar={0,0,0,0},g_rightTrend={0,0,0,0},g_rightField={0,0,0,0},g_focusLamp={0,0,0,0},g_afSummary={0,0,0,0},g_afChart={0,0,0,0},g_afLegend={0,0,0,0},g_cfChart={0,0,0,0}; static int g_layoutClientWidth=0,g_layoutClientHeight=0;
static BYTE* g_frame=0; static DWORD g_frameSize=0; static BITMAPINFO g_frameInfo; static BYTE* g_framePixels=0; static int g_frameW=0,g_frameH=0,g_frameBpp=0; static DWORD g_frameOff=0;
static int g_lastLoadedFrameSequence=-1,g_frameFetchFailures=0;
static BOOL g_starSelectionQueued=FALSE,g_starSelectionBusy=FALSE,g_commandQueued=FALSE,g_commandBusy=FALSE,g_pollBusy=FALSE;
static BOOL g_statusRefreshRequested=FALSE,g_shutdownStarted=FALSE;
static const char* g_frontendPhase="startup";
static int g_pendingStarX=-1,g_pendingStarY=-1; static UINT g_pendingCommandId=0,g_pendingCommandCode=0; static HDC g_backDc=0; static HGDIOBJ g_backBitmap=0,g_backOldBitmap=0; static int g_backW=0,g_backH=0;

#define TREND_CAPACITY 60
struct TrendPoint{int frameSequence;ULONGLONG tick;double fwhm,hfr;int stars;BOOL autofocusMarker;};
static TrendPoint g_trend[TREND_CAPACITY];static int g_trendCount=0,g_trendLastFrame=-1,g_trendHoverIndex=-1;static BOOL g_trendPendingAfMarker=FALSE;static RECT g_liveTrendPlot={0,0,0,0};
#define CF_UI_CAPACITY 60
struct ContinuousFocusUiPoint{int frameSequence,position,target,correction;double confidence;};
static ContinuousFocusUiPoint g_cfUi[CF_UI_CAPACITY];static int g_cfUiCount=0,g_cfUiLastFrame=-1,g_cfUiLastCorrection=0;


static HWND hCamGroup,hCamBackend,hCamDevice,hCamRefresh,hCamSelect,hCamConnect,hExposure,hGain,hLive,hStretch,hStars,hValues,hSaturation,hZones;
static HWND hCamLabels[4];
static HWND hFocGroup,hFocBackend,hFocDevice,hFocSelect,hFocConnect,hFocSetup,hPosition,hTemperature,hManualStep,hMoveIn,hMoveOut,hHalt,hSafeMin,hSafeMax;
static HWND hFocLabels[7];
static HWND hTabs[8]; static HWND hStatus,hProfile,hSaveProfile,hLoadProfile,hDeleteProfile,hImportProfile,hExportProfile,hProfileLabel,hViewLabel,hViewMode,hThemeLabel,hTheme;
static BOOL g_profilesLoaded=FALSE;
static HWND hAfLabels[4],hAfPoints,hAfStep,hAfSamples,hBacklash,hPrefOut,hAfUseSelected,hAfClearSelected,hAfHint,hAfDiagnosis,hStepAssist,hAfStart,hAfStop;
static HWND hBahtEnable,hBahtText; static HWND hDiag,hExport,hLog;
static HWND hAutoRefocus,hRefocusMin,hRefocusTemp,hRefocusFwhm,hRefocusBadFrames,hRefocusMinStars,hRefocusStability,hRefocusCooldown,hRefocusResume,hSaveAdv,hAutomationInfo,hAutomationDetailsToggle,hAutoLabels[7];
static HWND hSelfTest,hTestResult,hTestInfo,hSimProfile,hSimBacklash,hSimApply,hSimRandomize,hSimProfileInfo,hSimLabels[2];
static HWND hBacklashCal,hTempComp,hAutoStartPos,hFilterName,hFilterLearn,hFilterApply,hEvtMeridian,hEvtReconnect,hEvtFilter,hRefocusCaptures,hSmartLabel;
static HWND hCfEnable,hCfMode,hCfFallback,hCfMinFrames,hCfDeadband,hCfMaxStep,hCfConfidence,hCfImprovement,hCfSettle,hCfSave,hCfReset,hCfResume,hCfInfo,hCfNote,hCfLabels[6];

#ifdef _MSC_VER
#define AFS_NOINLINE __declspec(noinline)
#else
#define AFS_NOINLINE __attribute__((noinline))
#endif
struct AppState{
    BOOL camera,focuser,focuserMoving,focuserSetupActive,autofocus,stepAssistantActive,live,frameReady,simulator,external,native,stretch,stars,values,saturation,zones,bahtinov,preferredOut,autoRefocus,autoRefocusAutomaticRun,autoRefocusReferenceReady,autoRefocusTemperatureRequired,autoRefocusLiveWillResume,autofocusErrorAutomatic,manualStarLocked,afUseSelectedStar,autoRefocusPaused,autoRefocusTimeEnabled,autoRefocusTemperatureEnabled,autoRefocusFwhmEnabled,cameraWorkerBlocked,focuserWorkerBlocked,continuousFocusEnabled,continuousFocusFallback,continuousFocusPaused;
    wchar_t version[32],cameraName[256],focuserName[256],status[320],profile[160],selfTestSummary[256],simProfileName[128],tiltDirection[80],autoRefocusLastReason[256],autofocusErrorCode[96],autofocusErrorTitle[256],autofocusErrorDetail[640],cameraWorkerOperation[128],focuserWorkerOperation[128],exposure[64],gain[64],manualStep[64],afPointsText[32],afStepText[32],afSamplesText[32],backlashText[32],refocusMinText[32],refocusTempText[32],continuousFocusState[96],continuousFocusReason[320];
    int position,starsCount,usedStars,selfPassed,selfTotal,safeMin,safeMax,frameSequence,profileRevision,selectedStarMisses,afRecenterCount,afExpansionCount,autoRefocusRetrySeconds,autoRefocusFailureCount,autoRefocusBadFrameStreak,refocusBadFrames,refocusMinStars,cameraWorkerRetrySeconds,focuserWorkerRetrySeconds,continuousFocusMode,continuousFocusPhase,continuousFocusMinFrames,continuousFocusDeadband,continuousFocusMaxStep,continuousFocusMinConfidence,continuousFocusSettleMs,continuousFocusLastCorrection,continuousFocusTarget,continuousFocusAccepted,continuousFocusRejected;
    unsigned long long frameAgeMs;
    double fwhm,hfr,snr,ecc,stability,temperature,selectedFwhm,selectedHfr,selectedSnr,selectedEcc,bahtOffset,bahtConfidence,sharpness,tilt,autoRefocusElapsedMinutes,autoRefocusNextMinutes,autoRefocusTempDelta,autoRefocusFwhmDegradePercent,autoRefocusReferenceFwhm,autoRefocusCooldownRemainingMinutes,refocusFwhmPercent,refocusStability,refocusCooldown,continuousFocusMinImprovement,continuousFocusConfidence,continuousFocusReferenceMetric,continuousFocusEstimatedError,continuousFocusDriftStepsPerMinute;
    BOOL hasTemperature,bahtValid,tiltValid,tempCompEnabled,autoStartPositionEnabled,profileModelValid,backlashCalibrationActive,refocusOnMeridian,refocusOnReconnect,refocusOnFilter;
    int seeingIndex,focusNeedScore,afQualityScore,profileSuccessfulRuns,profileTypicalPosition,profileRecommendedStep,profileBacklash,backlashCalibrationEstimated,backlashCalibrationProgress,backlashCalibrationLimit,simProfileMode,simActiveProfile,simBacklashSteps,simBacklashRemaining,simMotorPosition,simOpticalPosition,filterOffsetCount,refocusEveryCaptures,captureEventCounter,tempCompDeadband,tempCompMaxStep,tempCompPredictedPosition,tempProfileCount;
    double transparencyIndex,fieldCurvature,fieldAsymmetry,fieldQualityScore,tiltConfidence,profileTypicalFwhm,profileTypicalHfr,profileQualityMean,tempSlope,tempIntercept;
    double tempProfileTemperature[64];int tempProfilePosition[64],tempProfileArrayCount;
    BOOL tempFitValid,afValidationPassed,afRollbackPerformed,sessionHasTemperature;
    int sessionAfAttempts,sessionAfSuccess,sessionAfFailed,sessionAfRollbacks,sessionStartPosition,sessionLastPosition;
    double sessionMinutes,sessionBestFwhm,sessionWorstFwhm,sessionStartTemperature,sessionLastTemperature;
    wchar_t seeingState[128],focusNeedLabel[128],focusNeedReason[320],afQualityLabel[128],fieldAdvice[320],currentFilter[64],lastExternalEvent[160],backlashCalibrationResult[200],afValidationState[128],afValidationReason[384];
    double zone[9];int zoneCount[9];
    int afPos[15],afOutlier[15],afSamplesPerPoint[15];
    double afMetric[15],afFwhm[15],afMetricSigma[15],afFwhmSigma[15],afResidual[15],afFwhmResidual[15],afFitParams[5],afFitFwhmParams[5];
    int afCount,afMeasuredCount,afFitModel,afFitFwhmModel,afFitInliers,afFitOutliers,afAdaptiveSamplesAdded;
    BOOL afFitValid,afFitFwhmValid,afFinalValid;
    double afFitA,afFitB,afFitC,afFitFwhmA,afFitFwhmB,afFitFwhmC,afFitCenter,afFitScale,afFitR2,afFitFwhmR2,afFitConfidence,afCurveQuality,afFocusSigma,afFocusSigmaLoo,afReducedChi2,afResidualRms,afAicc,afExpectedHfr,afExpectedFwhm,afFinalHfr,afFinalFwhm;
    int afBestPosition,afFinalPosition;wchar_t afFitMethod[160];
    double starX[160],starY[160],starFwhm[160];int starUsed[160],starSaturated[160],starArrayCount,selectedStar;
};
static AppState g_state;
static AppState g_previousState;
struct UiScratch{
    wchar_t w[128],autoInfo[2200],elapsed[32],nextTime[32],tempDelta[32],fwhmDelta[32],retryClock[32],threshold[32],stabilityCurrent[32],stabilityLimit[32],cooldown[32];
    wchar_t timeLine[220],tempLine[240],fwhmLine[320],workerLine[520],workerTemp[300],afDiagnosis[1200];
};
static UiScratch g_uiScratch;

static void* Alloc(SIZE_T n){return HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,n);} static void Free(void* p){if(p)HeapFree(GetProcessHeap(),0,p);} static int WLen(LPCWSTR s){return lstrlenW(s);} static BOOL WEqual(LPCWSTR a,LPCWSTR b){if(a==b)return TRUE;if(!a||!b)return FALSE;while(*a&&*b&&*a==*b){a++;b++;}return *a==*b;} static void Font(HWND h,HFONT f){if(h)SendMessageW(h,WM_SETFONT,(WPARAM)f,TRUE);} static void Place(HWND h,int x,int y,int w,int hh){if(h)MoveWindow(h,x,y,w,hh,TRUE);} static void ShowCtl(HWND h,BOOL show){if(h)ShowWindow(h,show?SW_SHOW:SW_HIDE);} static BOOL Checked(HWND h){return SendMessageW(h,BM_GETCHECK,0,0)==BST_CHECKED;} static void Check(HWND h,BOOL on){BOOL old=Checked(h);if(old!=on)SendMessageW(h,BM_SETCHECK,on?BST_CHECKED:0,0);} static int ComboSel(HWND h){return (int)SendMessageW(h,CB_GETCURSEL,0,0);} static void ComboAdd(HWND h,LPCWSTR s){SendMessageW(h,CB_ADDSTRING,0,(LPARAM)s);} static void ComboSelect(HWND h,int i){if(ComboSel(h)!=i)SendMessageW(h,CB_SETCURSEL,i,0);} static void GetText(HWND h,wchar_t* out,int cap){out[0]=0;GetWindowTextW(h,out,cap);} static void SetText(HWND h,LPCWSTR s){if(!h)return;wchar_t current[2048];GetWindowTextW(h,current,2048);if(!WEqual(current,s?s:L""))SetWindowTextW(h,s?s:L"");} static int ClampI(int v,int a,int b){return v<a?a:(v>b?b:v);}
static BOOL ParseUiUIntText(LPCWSTR s,unsigned* out){if(!s||!out)return FALSE;int i=0;while(s[i]==L' '||s[i]==L'\t')i++;if(s[i]==L'+')i++;if(s[i]<L'0'||s[i]>L'9')return FALSE;unsigned long long v=0;for(;s[i]>=L'0'&&s[i]<=L'9';i++){unsigned digit=(unsigned)(s[i]-L'0');if(v>(0xffffffffULL-digit)/10ULL)return FALSE;v=v*10ULL+digit;}while(s[i]==L' '||s[i]==L'\t')i++;if(s[i])return FALSE;*out=(unsigned)v;return TRUE;}
static BOOL ParseUiDoubleText(LPCWSTR s,double* out){if(!s||!out)return FALSE;int i=0;while(s[i]==L' '||s[i]==L'\t')i++;BOOL neg=FALSE;if(s[i]==L'-'){neg=TRUE;i++;}else if(s[i]==L'+')i++;double v=0.0,scale=0.1;BOOL any=FALSE,frac=FALSE;for(;s[i];i++){wchar_t c=s[i];if(c>=L'0'&&c<=L'9'){any=TRUE;if(frac){v+=(double)(c-L'0')*scale;scale*=0.1;}else{v=v*10.0+(double)(c-L'0');if(v>1.0e12)return FALSE;}}else if((c==L'.'||c==L',')&&!frac)frac=TRUE;else break;}while(s[i]==L' '||s[i]==L'\t')i++;if(!any||s[i])return FALSE;*out=neg?-v:v;return TRUE;}
static BOOL ReadUiUInt(HWND h,unsigned* out){wchar_t v[96];GetText(h,v,96);return ParseUiUIntText(v,out);}
static BOOL ReadUiDouble(HWND h,double* out){wchar_t v[96];GetText(h,v,96);return ParseUiDoubleText(v,out);}
static int NormalizeAfPointCount(int v){if(v<5)v=5;if(v>15)v=15;if(!(v&1))v--;if(v<5)v=5;return v;}
static int NormalizeAfSampleCount(int v){return ClampI(v,1,5);}
static void SetAfPointComboFromText(LPCWSTR text){unsigned u=9;if(!ParseUiUIntText(text,&u))u=9;int v=NormalizeAfPointCount((int)u);ComboSelect(hAfPoints,(v-5)/2);}
static void SetAfSampleComboFromText(LPCWSTR text){unsigned u=3;if(!ParseUiUIntText(text,&u))u=3;ComboSelect(hAfSamples,NormalizeAfSampleCount((int)u)-1);}
static void PlaceDropDownCombo(HWND h,int x,int y,int w,int closedHeight,int visibleRows){if(!h)return;int rows=visibleRows<2?2:visibleRows;MoveWindow(h,x,y,w,closedHeight+rows*24,TRUE);SendMessageW(h,CB_SETMINVISIBLE,(WPARAM)rows,0);}
static BOOL ValidateAutofocusInputs(wchar_t* error,int cap){if(error&&cap>0)error[0]=0;double exposure=0.0;unsigned u=0;if(!ReadUiDouble(hExposure,&exposure)||exposure<1.0||exposure>60000.0){if(error&&cap>0)lstrcpyW(error,L"Belichtung muss zwischen 1 und 60000 ms liegen.");return FALSE;}if(!ReadUiUInt(hGain,&u)||u>65535U){if(error&&cap>0)lstrcpyW(error,L"Gain muss zwischen 0 und 65535 liegen.");return FALSE;}if(!ReadUiUInt(hAfPoints,&u)||u<5U||u>15U||!(u&1U)){if(error&&cap>0)lstrcpyW(error,L"Messpunkte müssen 5, 7, 9, 11, 13 oder 15 sein.");return FALSE;}if(!ReadUiUInt(hAfStep,&u)||u<5U||u>1000000U){if(error&&cap>0)lstrcpyW(error,L"Schrittweite muss zwischen 5 und 1000000 liegen.");return FALSE;}if(!ReadUiUInt(hAfSamples,&u)||u<1U||u>5U){if(error&&cap>0)lstrcpyW(error,L"Samples müssen zwischen 1 und 5 liegen.");return FALSE;}if(!ReadUiUInt(hBacklash,&u)||u>1000000U){if(error&&cap>0)lstrcpyW(error,L"Backlash muss zwischen 0 und 1000000 liegen.");return FALSE;}return TRUE;}
static BOOL FocuserOperationBusy(){return g_state.focuserSetupActive||g_focuserSetupEngineLock||g_state.autofocus||g_state.stepAssistantActive||g_state.backlashCalibrationActive||g_state.focuserMoving;}
static void UpdateAutofocusInputState(){if(!hAfStart||!hAfHint)return;wchar_t error[256];BOOL valid=ValidateAutofocusInputs(error,256);BOOL focusBusy=g_state.autofocus||g_state.stepAssistantActive||g_state.backlashCalibrationActive;EnableWindow(hAfStart,g_engineOnline&&valid&&!focusBusy);if(valid)SetText(hAfHint,focusBusy?L"Ein Fokus- oder Kalibrierungslauf ist aktiv.":L"Parameter gültig · Stern im Livebild anklicken; blaues Fadenkreuz = fixiert.");else{wchar_t msg[360];lstrcpyW(msg,L"Parameterfehler: ");lstrcatW(msg,error);SetText(hAfHint,msg);}}
static int TabIndexFromId(UINT id){switch(id){case ID_TAB_LIVE:return 0;case ID_TAB_AUTO:return 1;case ID_TAB_BAHT:return 2;case ID_TAB_LOG:return 3;case ID_TAB_AUTOMATION:return 4;case ID_TAB_CONTINUOUS:return 5;case ID_TAB_ANALYSIS:return 6;case ID_TAB_TESTS:return 7;default:return -1;}}
static BOOL IsTabId(UINT id){return TabIndexFromId(id)>=0;}

static void FormatD(double,int,wchar_t*);
static void AppendWBounded(wchar_t* out,int cap,LPCWSTR text){
    if(!out||cap<=0||!text)return;int used=0;while(used<cap&&out[used])used++;if(used>=cap){out[cap-1]=0;return;}
    int i=0;while(text[i]&&used<cap-1)out[used++]=text[i++];out[used]=0;
}
static void FormatSignedInt(int value,wchar_t* out,int cap){
    if(!out||cap<=0)return;out[0]=0;if(cap<2)return;
    wchar_t digits[32];wsprintfW(digits,L"%d",value);
    if(value>0)AppendWBounded(out,cap,L"+");AppendWBounded(out,cap,digits);
}
static BOOL UpdateTrendHistory(const AppState* old);
static BOOL UpdateContinuousFocusHistory(const AppState* old);
static void UpdateTrendHoverFromMouse(int mx,int my);
static void AToW(const char*,wchar_t*,int);
static void WToA(LPCWSTR,char*,int);
static void AppendFrontendTrace(const char*);
static void SetFrontendPhase(const char* phase){g_frontendPhase=phase?phase:"unknown";}
static void ClearFrame(){Free(g_frame);g_frame=0;g_frameSize=0;g_framePixels=0;g_frameW=g_frameH=g_frameBpp=0;g_frameOff=0;g_lastLoadedFrameSequence=-1;}
static void DestroyBackBuffer(){if(g_backDc){if(g_backOldBitmap)SelectObject(g_backDc,g_backOldBitmap);if(g_backBitmap)DeleteObject(g_backBitmap);DeleteDC(g_backDc);}g_backDc=0;g_backBitmap=0;g_backOldBitmap=0;g_backW=g_backH=0;}
static BOOL EnsureBackBuffer(HDC ref,int w,int h){if(w<=0||h<=0)return FALSE;if(g_backDc&&g_backBitmap&&g_backW==w&&g_backH==h)return TRUE;DestroyBackBuffer();g_backDc=CreateCompatibleDC(ref);if(!g_backDc)return FALSE;g_backBitmap=CreateCompatibleBitmap(ref,w,h);if(!g_backBitmap){DeleteDC(g_backDc);g_backDc=0;return FALSE;}g_backOldBitmap=SelectObject(g_backDc,g_backBitmap);g_backW=w;g_backH=h;return TRUE;}
static HWND Add(LPCWSTR cls,LPCWSTR text,DWORD style,int id){HWND h=CreateWindowExW(0,cls,text,WS_CHILD|WS_VISIBLE|style,0,0,10,10,g_main,(HMENU)(ULONG_PTR)id,g_inst,0);if(!h)g_controlCreationFailures++;Font(h,g_font);return h;}
static void StripFile(wchar_t* p){int n=WLen(p);while(n>0&&p[n-1]!=L'\\'&&p[n-1]!=L'/')p[--n]=0;}
static void BuildPath(LPCWSTR name,wchar_t* out){int o=0;for(int i=0;g_appDir[i]&&o<698;i++)out[o++]=g_appDir[i];for(int i=0;name&&name[i]&&o<698;i++)out[o++]=name[i];out[o]=0;}
static BOOL CopyWideBounded(LPCWSTR source,LPWSTR target,int cap){if(!target||cap<2)return FALSE;int o=0;if(source)for(;source[o]&&o<cap-1;o++)target[o]=source[o];target[o]=0;return !source||source[o]==0;}
static BOOL AppendWideBounded(LPWSTR target,int cap,LPCWSTR suffix){if(!target||cap<2)return FALSE;int o=0;while(target[o]&&o<cap-1)o++;if(o>=cap-1)return FALSE;if(suffix)for(int i=0;suffix[i];i++){if(o>=cap-1){target[cap-1]=0;return FALSE;}target[o++]=suffix[i];}target[o]=0;return TRUE;}
static BOOL EnsureDirectoryExists(LPCWSTR path){if(!path||!path[0])return FALSE;if(CreateDirectoryW(path,0))return TRUE;return GetLastError()==ERROR_ALREADY_EXISTS;}
static void InitializeFrontendDiagnostics(){
    g_frontendLogPath[0]=0;wchar_t root[520];root[0]=0;DWORD n=GetEnvironmentVariableW(L"LOCALAPPDATA",root,520);
    if(n>0&&n<520){wchar_t appData[700];if(CopyWideBounded(root,appData,700)&&AppendWideBounded(appData,700,L"\\AstroFocusStudio")&&EnsureDirectoryExists(appData)&&AppendWideBounded(appData,700,L"\\Logs")&&EnsureDirectoryExists(appData)&&CopyWideBounded(appData,g_frontendLogPath,700)&&AppendWideBounded(g_frontendLogPath,700,L"\\FrontendTrace.log"))return;}
    n=GetTempPathW(520,root);if(n>0&&n<520){wchar_t tempDir[700];if(CopyWideBounded(root,tempDir,700)&&AppendWideBounded(tempDir,700,L"AstroFocusStudio")&&EnsureDirectoryExists(tempDir)&&CopyWideBounded(tempDir,g_frontendLogPath,700)&&AppendWideBounded(g_frontendLogPath,700,L"\\FrontendTrace.log"))return;}
    BuildPath(L"FrontendTrace.log",g_frontendLogPath);
}
static BOOL WriteAllHandle(HANDLE h,const void* data,DWORD length){
    if(h==INVALID_HANDLE_VALUE||(!data&&length))return FALSE;const BYTE* p=(const BYTE*)data;DWORD done=0;
    while(done<length){DWORD written=0;if(!WriteFile(h,p+done,length-done,&written,0)||written==0)return FALSE;done+=written;}
    return TRUE;
}

static int NormalizeThemeMode(int mode){return mode>=THEME_SYSTEM&&mode<=THEME_DARK?mode:THEME_SYSTEM;}
static BOOL ResolveDarkTheme(int mode,BOOL systemDark,BOOL highContrast){mode=NormalizeThemeMode(mode);if(highContrast)return FALSE;if(mode==THEME_DARK)return TRUE;if(mode==THEME_LIGHT)return FALSE;return systemDark?TRUE:FALSE;}
static int ThemeLuma(DWORD c){int r=(int)(c&255U),g=(int)((c>>8)&255U),b=(int)((c>>16)&255U);return (r*299+g*587+b*114)/1000;}
static void SetBaseThemePalette(BOOL dark){
    if(dark){
        g_theme.background=RGB(20,23,28);g_theme.panel=RGB(29,33,40);g_theme.input=RGB(37,42,50);
        g_theme.textPrimary=RGB(236,240,245);g_theme.textSecondary=RGB(198,207,218);g_theme.textMuted=RGB(151,163,178);g_theme.title=RGB(239,243,249);
        g_theme.border=RGB(63,72,84);g_theme.grid=RGB(51,59,70);g_theme.accent=RGB(78,151,255);g_theme.card=RGB(34,39,47);g_theme.overlayBox=RGB(31,36,44);
        g_theme.previewMessage=RGB(218,225,234);g_theme.simBadge=RGB(29,48,70);g_theme.simBadgeText=RGB(131,192,255);
        g_theme.referenceText=RGB(224,190,111);g_theme.thresholdText=RGB(255,126,119);g_theme.markerText=RGB(202,164,255);
        g_theme.successText=RGB(91,214,151);g_theme.errorText=RGB(255,121,115);g_theme.warningText=RGB(255,169,70);g_theme.cautionText=RGB(239,202,78);
        g_theme.connectionGood=RGB(59,201,125);g_theme.connectionBad=RGB(238,91,84);
    }else{
        g_theme.background=RGB(245,247,250);g_theme.panel=RGB(255,255,255);g_theme.input=RGB(255,255,255);
        g_theme.textPrimary=RGB(25,35,45);g_theme.textSecondary=RGB(55,68,82);g_theme.textMuted=RGB(95,105,116);g_theme.title=RGB(25,45,70);
        g_theme.border=RGB(205,212,220);g_theme.grid=RGB(220,226,233);g_theme.accent=RGB(45,115,210);g_theme.card=RGB(249,251,253);g_theme.overlayBox=RGB(248,250,253);
        g_theme.previewMessage=RGB(220,225,230);g_theme.simBadge=RGB(232,244,255);g_theme.simBadgeText=RGB(30,95,170);
        g_theme.referenceText=RGB(105,85,45);g_theme.thresholdText=RGB(180,65,60);g_theme.markerText=RGB(105,75,155);
        g_theme.successText=RGB(32,138,86);g_theme.errorText=RGB(190,70,55);g_theme.warningText=RGB(230,130,30);g_theme.cautionText=RGB(220,180,35);
        g_theme.connectionGood=RGB(30,155,95);g_theme.connectionBad=RGB(205,55,50);
    }
    // Keep the palette helper part of production builds; tests also use the same luma calculation.
    (void)ThemeLuma(g_theme.textPrimary);
}
#ifndef ASTROFOCUS_NATIVE_TEST
typedef LONG (WINAPI *PFN_RegOpenKeyExW_MIN)(HKEY,LPCWSTR,DWORD,DWORD,HKEY*);
typedef LONG (WINAPI *PFN_RegQueryValueExW_MIN)(HKEY,LPCWSTR,DWORD*,DWORD*,BYTE*,DWORD*);
typedef LONG (WINAPI *PFN_RegCloseKey_MIN)(HKEY);
typedef BOOL (WINAPI *PFN_SystemParametersInfoW_MIN)(UINT,UINT,LPVOID,UINT);
typedef DWORD (WINAPI *PFN_GetSysColor_MIN)(int);
typedef LONG (WINAPI *PFN_DwmSetWindowAttribute_MIN)(HWND,DWORD,LPCVOID,DWORD);
typedef LONG (WINAPI *PFN_SetWindowTheme_MIN)(HWND,LPCWSTR,LPCWSTR);
static BOOL QuerySystemDarkMode(){
    BOOL dark=FALSE;HMODULE a=LoadLibraryW(L"advapi32.dll");if(!a)return FALSE;
    PFN_RegOpenKeyExW_MIN openKey=(PFN_RegOpenKeyExW_MIN)GetProcAddress(a,"RegOpenKeyExW");PFN_RegQueryValueExW_MIN query=(PFN_RegQueryValueExW_MIN)GetProcAddress(a,"RegQueryValueExW");PFN_RegCloseKey_MIN closeKey=(PFN_RegCloseKey_MIN)GetProcAddress(a,"RegCloseKey");
    if(openKey&&query&&closeKey){HKEY key=0;HKEY currentUser=(HKEY)(LONG_PTR)(LONG)0x80000001UL;if(openKey(currentUser,L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",0,0x0001UL,&key)==0){DWORD value=1,type=0,size=sizeof(value);if(query(key,L"AppsUseLightTheme",0,&type,(BYTE*)&value,&size)==0&&type==4&&size==sizeof(value))dark=value==0;closeKey(key);}}
    FreeLibrary(a);return dark;
}
static BOOL QueryHighContrast(){
    BOOL enabled=FALSE;HMODULE u=LoadLibraryW(L"user32.dll");if(!u)return FALSE;PFN_SystemParametersInfoW_MIN spi=(PFN_SystemParametersInfoW_MIN)GetProcAddress(u,"SystemParametersInfoW");
    if(spi){HIGHCONTRASTW_MIN hc;memset(&hc,0,sizeof(hc));hc.cbSize=sizeof(hc);if(spi(0x0042,(UINT)sizeof(hc),&hc,0))enabled=(hc.dwFlags&0x00000001UL)!=0;}FreeLibrary(u);return enabled;
}
static DWORD QuerySystemColor(int index,DWORD fallback){HMODULE u=LoadLibraryW(L"user32.dll");if(!u)return fallback;PFN_GetSysColor_MIN fn=(PFN_GetSysColor_MIN)GetProcAddress(u,"GetSysColor");DWORD c=fn?fn(index):fallback;FreeLibrary(u);return c;}
#else
static BOOL QuerySystemDarkMode(){return FALSE;}
static BOOL QueryHighContrast(){return FALSE;}
static DWORD QuerySystemColor(int,DWORD fallback){return fallback;}
#endif
static void ApplyHighContrastPalette(){
    g_theme.background=QuerySystemColor(5,g_theme.background);g_theme.panel=QuerySystemColor(15,g_theme.panel);g_theme.input=QuerySystemColor(5,g_theme.input);
    g_theme.textPrimary=QuerySystemColor(8,g_theme.textPrimary);g_theme.textSecondary=g_theme.textPrimary;g_theme.textMuted=QuerySystemColor(17,g_theme.textMuted);g_theme.title=g_theme.textPrimary;
    g_theme.border=QuerySystemColor(6,g_theme.border);g_theme.grid=g_theme.border;g_theme.accent=QuerySystemColor(13,g_theme.accent);g_theme.card=g_theme.panel;g_theme.overlayBox=g_theme.panel;
    g_theme.previewMessage=g_theme.textPrimary;g_theme.simBadge=g_theme.panel;g_theme.simBadgeText=g_theme.textPrimary;g_theme.referenceText=g_theme.textPrimary;g_theme.thresholdText=g_theme.textPrimary;g_theme.markerText=g_theme.textPrimary;
    g_theme.successText=g_theme.textPrimary;g_theme.errorText=g_theme.textPrimary;g_theme.warningText=g_theme.textPrimary;g_theme.cautionText=g_theme.textPrimary;g_theme.connectionGood=g_theme.accent;g_theme.connectionBad=g_theme.textPrimary;
}
static void DeleteThemeResources(){
    if(g_bg)DeleteObject(g_bg);if(g_panel)DeleteObject(g_panel);if(g_input)DeleteObject(g_input);if(g_accentBrush)DeleteObject(g_accentBrush);
    if(g_border)DeleteObject(g_border);if(g_grid)DeleteObject(g_grid);if(g_curve)DeleteObject(g_curve);if(g_good)DeleteObject(g_good);if(g_bad)DeleteObject(g_bad);if(g_reference)DeleteObject(g_reference);if(g_threshold)DeleteObject(g_threshold);if(g_marker)DeleteObject(g_marker);
    g_bg=g_panel=g_input=g_accentBrush=0;g_border=g_grid=g_curve=g_good=g_bad=g_reference=g_threshold=g_marker=0;
}
static void BuildThemeResources(){
    DeleteThemeResources();g_bg=CreateSolidBrush(g_theme.background);g_panel=CreateSolidBrush(g_theme.panel);g_input=CreateSolidBrush(g_theme.input);g_accentBrush=CreateSolidBrush(g_theme.accent);
    g_border=CreatePen(PS_SOLID,1,g_theme.border);g_grid=CreatePen(PS_SOLID,1,g_theme.grid);g_curve=CreatePen(PS_SOLID,2,g_theme.accent);g_good=CreatePen(PS_SOLID,2,g_theme.connectionGood);g_bad=CreatePen(PS_SOLID,2,g_theme.connectionBad);
    g_reference=CreatePen(PS_DASH,1,g_theme.referenceText);g_threshold=CreatePen(PS_DASH,1,g_theme.thresholdText);g_marker=CreatePen(PS_DASH,1,g_theme.markerText);
}
static BOOL BuildUserDataFilePath(LPCWSTR fileName,LPWSTR out,int cap){
    if(!out||cap<2||!fileName||!fileName[0])return FALSE;out[0]=0;wchar_t root[520];root[0]=0;DWORD n=GetEnvironmentVariableW(L"LOCALAPPDATA",root,520);
    if(n>0&&n<520){wchar_t dir[700];if(CopyWideBounded(root,dir,700)&&AppendWideBounded(dir,700,L"\\AstroFocusStudio")&&EnsureDirectoryExists(dir)&&CopyWideBounded(dir,out,cap)&&AppendWideBounded(out,cap,L"\\")&&AppendWideBounded(out,cap,fileName))return TRUE;}
    root[0]=0;n=GetTempPathW(520,root);if(n>0&&n<520){wchar_t dir[700];if(CopyWideBounded(root,dir,700)&&AppendWideBounded(dir,700,L"AstroFocusStudio")&&EnsureDirectoryExists(dir)&&CopyWideBounded(dir,out,cap)&&AppendWideBounded(out,cap,L"\\")&&AppendWideBounded(out,cap,fileName))return TRUE;}
    out[0]=0;return FALSE;
}
static BOOL ReadThemeSettingFile(LPCWSTR path,int* mode){
    if(!path||!path[0]||!mode)return FALSE;HANDLE f=CreateFileW(path,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return FALSE;
    char data[64];DWORD rd=0;BOOL ok=ReadFile(f,data,sizeof(data)-1,&rd,0)&&rd<sizeof(data);CloseHandle(f);if(!ok)return FALSE;data[rd]=0;char* v=strstr(data,"theme=");if(!v||v[6]<'0'||v[6]>'2')return FALSE;*mode=NormalizeThemeMode(v[6]-'0');return TRUE;
}
static BOOL SaveThemeSetting(){
    g_themeSettingsLastError=0;g_themeSettingsPath[0]=0;if(!BuildUserDataFilePath(L"AstroFocusUiSettings.ini",g_themeSettingsPath,700)){g_themeSettingsLastError=GetLastError();return FALSE;}
    wchar_t tempPath[700],tempSuffix[40];wsprintfW(tempSuffix,L".tmp.%u",(UINT)GetCurrentProcessId());if(!CopyWideBounded(g_themeSettingsPath,tempPath,700)||!AppendWideBounded(tempPath,700,tempSuffix)){g_themeSettingsLastError=GetLastError();return FALSE;}DeleteFileW(tempPath);
    HANDLE f=CreateFileW(tempPath,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE){g_themeSettingsLastError=GetLastError();return FALSE;}
    char data[32];int n=sprintf(data,"theme=%d\r\n",NormalizeThemeMode(g_themeMode));BOOL ok=n>0&&n<(int)sizeof(data)&&WriteAllHandle(f,data,(DWORD)n)&&FlushFileBuffers(f);if(!ok)g_themeSettingsLastError=GetLastError();CloseHandle(f);
    if(ok&&!MoveFileExW(tempPath,g_themeSettingsPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)){g_themeSettingsLastError=GetLastError();ok=FALSE;}
    if(!ok)DeleteFileW(tempPath);return ok;
}
static void LoadThemeSetting(){
    g_themeMode=THEME_SYSTEM;g_themeSettingsPath[0]=0;int mode=THEME_SYSTEM;
    if(BuildUserDataFilePath(L"AstroFocusUiSettings.ini",g_themeSettingsPath,700)&&ReadThemeSettingFile(g_themeSettingsPath,&mode)){g_themeMode=mode;return;}
    wchar_t legacyPath[700];BuildPath(L"AstroFocusUiSettings.ini",legacyPath);if(ReadThemeSettingFile(legacyPath,&mode)){g_themeMode=mode;(void)SaveThemeSetting();}
}
static void SetControlThemeWith(HMODULE ux,HWND h,LPCWSTR theme){
#ifndef ASTROFOCUS_NATIVE_TEST
    if(!h||!ux)return;PFN_SetWindowTheme_MIN fn=(PFN_SetWindowTheme_MIN)GetProcAddress(ux,"SetWindowTheme");if(fn){
        /* A direct DarkMode_Explorer -> Explorer switch leaves some STATIC and EDIT
           windows with cached dark parts on Windows 11. Remove the old override first. */
        fn(h,L"",L"");fn(h,theme,0);SendMessageW(h,WM_THEMECHANGED,0,0);InvalidateRect(h,0,TRUE);UpdateWindow(h);
    }
#else
    (void)ux;(void)h;(void)theme;
#endif
}
static void ResetControlThemeWith(HMODULE ux,HWND h){
#ifndef ASTROFOCUS_NATIVE_TEST
    if(!h||!ux)return;PFN_SetWindowTheme_MIN fn=(PFN_SetWindowTheme_MIN)GetProcAddress(ux,"SetWindowTheme");if(fn){
        /* Plain STATIC controls are palette-painted by WM_CTLCOLORSTATIC. Keeping
           DarkMode_Explorer on them is what caused the stale black position field. */
        fn(h,L"",L"");fn(h,0,0);SendMessageW(h,WM_THEMECHANGED,0,0);InvalidateRect(h,0,TRUE);UpdateWindow(h);
    }
#else
    (void)ux;(void)h;
#endif
}
static void ApplyThemeToControls(){
#ifndef ASTROFOCUS_NATIVE_TEST
    HMODULE ux=LoadLibraryW(L"uxtheme.dll");if(!ux)return;LPCWSTR t=g_highContrast?0:(g_darkTheme?L"DarkMode_Explorer":L"Explorer");
#define AFS_THEME_CTL(h) SetControlThemeWith(ux,(h),t)
#define AFS_STATIC_CTL(h) ResetControlThemeWith(ux,(h))
    AFS_STATIC_CTL(hViewLabel);AFS_THEME_CTL(hViewMode);AFS_STATIC_CTL(hThemeLabel);AFS_THEME_CTL(hTheme);AFS_STATIC_CTL(hProfileLabel);AFS_THEME_CTL(hProfile);AFS_THEME_CTL(hSaveProfile);AFS_THEME_CTL(hLoadProfile);AFS_THEME_CTL(hDeleteProfile);AFS_THEME_CTL(hImportProfile);AFS_THEME_CTL(hExportProfile);AFS_STATIC_CTL(hStatus);
    for(int i=0;i<4;i++)AFS_STATIC_CTL(hCamLabels[i]);AFS_THEME_CTL(hCamBackend);AFS_THEME_CTL(hCamDevice);AFS_THEME_CTL(hCamRefresh);AFS_THEME_CTL(hCamSelect);AFS_THEME_CTL(hCamConnect);AFS_THEME_CTL(hExposure);AFS_THEME_CTL(hGain);AFS_THEME_CTL(hLive);AFS_THEME_CTL(hStretch);AFS_THEME_CTL(hStars);AFS_THEME_CTL(hValues);AFS_THEME_CTL(hSaturation);AFS_THEME_CTL(hZones);
    for(int i=0;i<7;i++)AFS_STATIC_CTL(hFocLabels[i]);AFS_THEME_CTL(hFocBackend);AFS_THEME_CTL(hFocDevice);AFS_THEME_CTL(hFocSelect);AFS_THEME_CTL(hFocConnect);AFS_THEME_CTL(hFocSetup);AFS_STATIC_CTL(hPosition);AFS_STATIC_CTL(hTemperature);AFS_THEME_CTL(hManualStep);AFS_THEME_CTL(hMoveIn);AFS_THEME_CTL(hMoveOut);AFS_THEME_CTL(hHalt);AFS_THEME_CTL(hSafeMin);AFS_THEME_CTL(hSafeMax);
    for(int i=0;i<8;i++)AFS_THEME_CTL(hTabs[i]);for(int i=0;i<4;i++)AFS_STATIC_CTL(hAfLabels[i]);AFS_THEME_CTL(hAfPoints);AFS_THEME_CTL(hAfStep);AFS_THEME_CTL(hAfSamples);AFS_THEME_CTL(hBacklash);AFS_THEME_CTL(hPrefOut);AFS_THEME_CTL(hAfUseSelected);AFS_THEME_CTL(hAfClearSelected);AFS_STATIC_CTL(hAfHint);AFS_THEME_CTL(hAfDiagnosis);AFS_THEME_CTL(hStepAssist);AFS_THEME_CTL(hAfStart);AFS_THEME_CTL(hAfStop);AFS_THEME_CTL(hBacklashCal);
    AFS_THEME_CTL(hBahtEnable);AFS_STATIC_CTL(hBahtText);AFS_THEME_CTL(hDiag);AFS_THEME_CTL(hExport);AFS_THEME_CTL(hLog);AFS_THEME_CTL(hAutoRefocus);for(int i=0;i<7;i++)AFS_STATIC_CTL(hAutoLabels[i]);AFS_THEME_CTL(hRefocusMin);AFS_THEME_CTL(hRefocusTemp);AFS_THEME_CTL(hRefocusFwhm);AFS_THEME_CTL(hRefocusBadFrames);AFS_THEME_CTL(hRefocusMinStars);AFS_THEME_CTL(hRefocusStability);AFS_THEME_CTL(hRefocusCooldown);AFS_THEME_CTL(hRefocusResume);AFS_THEME_CTL(hSaveAdv);AFS_THEME_CTL(hAutomationInfo);AFS_THEME_CTL(hAutomationDetailsToggle);AFS_THEME_CTL(hTempComp);AFS_THEME_CTL(hAutoStartPos);AFS_THEME_CTL(hEvtMeridian);AFS_THEME_CTL(hEvtReconnect);AFS_THEME_CTL(hEvtFilter);AFS_STATIC_CTL(hSmartLabel);AFS_THEME_CTL(hRefocusCaptures);AFS_THEME_CTL(hFilterName);AFS_THEME_CTL(hFilterLearn);AFS_THEME_CTL(hFilterApply);
    AFS_THEME_CTL(hCfEnable);AFS_THEME_CTL(hCfMode);AFS_THEME_CTL(hCfFallback);for(int i=0;i<6;i++)AFS_STATIC_CTL(hCfLabels[i]);AFS_THEME_CTL(hCfMinFrames);AFS_THEME_CTL(hCfDeadband);AFS_THEME_CTL(hCfMaxStep);AFS_THEME_CTL(hCfConfidence);AFS_THEME_CTL(hCfImprovement);AFS_THEME_CTL(hCfSettle);AFS_THEME_CTL(hCfSave);AFS_THEME_CTL(hCfReset);AFS_THEME_CTL(hCfResume);AFS_THEME_CTL(hCfInfo);AFS_STATIC_CTL(hCfNote);
    for(int i=0;i<2;i++)AFS_STATIC_CTL(hSimLabels[i]);AFS_THEME_CTL(hSimProfile);AFS_THEME_CTL(hSimBacklash);AFS_THEME_CTL(hSimApply);AFS_THEME_CTL(hSimRandomize);AFS_STATIC_CTL(hSimProfileInfo);AFS_THEME_CTL(hSelfTest);AFS_STATIC_CTL(hTestResult);AFS_STATIC_CTL(hTestInfo);
#undef AFS_STATIC_CTL
#undef AFS_THEME_CTL
    FreeLibrary(ux);
#endif
}
static void ApplyDarkTitleBar(){
#ifndef ASTROFOCUS_NATIVE_TEST
    if(!g_main)return;HMODULE d=LoadLibraryW(L"dwmapi.dll");if(!d)return;PFN_DwmSetWindowAttribute_MIN fn=(PFN_DwmSetWindowAttribute_MIN)GetProcAddress(d,"DwmSetWindowAttribute");if(fn){BOOL useDark=g_darkTheme&&!g_highContrast;LONG hr=fn(g_main,20,&useDark,sizeof(useDark));if(hr!=0)fn(g_main,19,&useDark,sizeof(useDark));}FreeLibrary(d);
#endif
}
static void RefreshTheme(BOOL persist){
    if(g_themeRefreshActive)return;g_themeRefreshActive=TRUE;
    g_themeMode=NormalizeThemeMode(g_themeMode);BOOL saved=TRUE;if(persist)saved=SaveThemeSetting();g_highContrast=QueryHighContrast();BOOL systemDark=QuerySystemDarkMode();g_darkTheme=ResolveDarkTheme(g_themeMode,systemDark,g_highContrast);
    SetBaseThemePalette(g_darkTheme);if(g_highContrast)ApplyHighContrastPalette();DestroyBackBuffer();BuildThemeResources();if(hTheme)ComboSelect(hTheme,g_themeMode);ApplyDarkTitleBar();ApplyThemeToControls();if(g_main){InvalidateRect(g_main,0,TRUE);UpdateWindow(g_main);}g_themeRefreshActive=FALSE;
    if(persist&&!saved){char pathA[720],trace[900];WToA(g_themeSettingsPath,pathA,720);sprintf(trace,"theme settings save failed error=%lu path=%s",(unsigned long)g_themeSettingsLastError,pathA[0]?pathA:"unavailable");AppendFrontendTrace(trace);}
}
static void AppendFrontendTrace(const char* stage){
    if(!g_frontendLogPath[0])InitializeFrontendDiagnostics();HANDLE h=CreateFileW(g_frontendLogPath,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE)return;
    SetFilePointer(h,0,0,FILE_END);SYSTEMTIME st;GetLocalTime(&st);
    char prefix[96];int prefixLength=sprintf(prefix,"%04u-%02u-%02u %02u:%02u:%02u.%03u | ",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
    if(prefixLength>0&&(unsigned)prefixLength<sizeof(prefix))WriteAllHandle(h,prefix,(DWORD)prefixLength);
    const char* text=stage?stage:"";DWORD textLength=0;while(text[textLength]&&textLength<2048U)textLength++;if(textLength)WriteAllHandle(h,text,textLength);
    char suffix[160];int suffixLength=sprintf(suffix," | tab=%d frame=%dx%d selected=%d stars=%d online=%d\r\n",g_activeTab,g_frameW,g_frameH,g_state.selectedStar,g_state.starArrayCount,g_engineOnline);
    if(suffixLength>0&&(unsigned)suffixLength<sizeof(suffix))WriteAllHandle(h,suffix,(DWORD)suffixLength);CloseHandle(h);
}
static LONG WINAPI FrontendUnhandledException(EXCEPTION_POINTERS_MIN* ep){
    char stage[520],moduleA[260]="unknown";DWORD code=ep&&ep->ExceptionRecord?ep->ExceptionRecord->ExceptionCode:0;void* address=ep&&ep->ExceptionRecord?ep->ExceptionRecord->ExceptionAddress:0;
    MEMORY_BASIC_INFORMATION_MIN mbi;memset(&mbi,0,sizeof(mbi));unsigned long long offset=0;wchar_t moduleW[260];moduleW[0]=0;
    if(address&&VirtualQuery(address,&mbi,sizeof(mbi))==sizeof(mbi)&&mbi.AllocationBase){GetModuleFileNameW((HMODULE)mbi.AllocationBase,moduleW,260);moduleW[259]=0;WToA(moduleW,moduleA,260);offset=(unsigned long long)((BYTE*)address-(BYTE*)mbi.AllocationBase);}
    unsigned long long accessKind=~0ULL,accessAddress=0;if(ep&&ep->ExceptionRecord&&code==0xC0000005U&&ep->ExceptionRecord->NumberParameters>=2){accessKind=(unsigned long long)ep->ExceptionRecord->ExceptionInformation[0];accessAddress=(unsigned long long)ep->ExceptionRecord->ExceptionInformation[1];}
    sprintf(stage,"UNHANDLED EXCEPTION code=0x%08X address=%p module=%s+0x%llX phase=%s access=%llu target=0x%llX",(UINT)code,address,moduleA,offset,g_frontendPhase?g_frontendPhase:"unknown",accessKind,accessAddress);AppendFrontendTrace(stage);
    wchar_t phaseW[180];AToW(g_frontendPhase?g_frontendPhase:"unknown",phaseW,180);wchar_t message[1400];wsprintfW(message,L"AstroFocus Studio wurde wegen eines unerwarteten Fehlers beendet.\r\n\r\nPhase: %s\r\nFehlercode: 0x%08X\r\n\r\nDiagnoseprotokoll:\r\n%s",phaseW,(UINT)code,g_frontendLogPath[0]?g_frontendLogPath:L"nicht verfügbar");MessageBoxW(g_main,message,L"AstroFocus Studio – Programmfehler",MB_OK|MB_ICONERROR);return 1;
}
static void InstallFrontendCrashHandler(){HMODULE k=GetModuleHandleW(L"kernel32.dll");if(!k)return;PFN_SetUnhandledExceptionFilter_MIN setFilter=(PFN_SetUnhandledExceptionFilter_MIN)GetProcAddress(k,"SetUnhandledExceptionFilter");if(setFilter)setFilter(FrontendUnhandledException);}
static void FailFrontendStartup(const char* trace,LPCWSTR explanation,UINT exitCode){DWORD error=GetLastError();AppendFrontendTrace(trace);wchar_t message[1100];wsprintfW(message,L"%s\r\n\r\nWindows-Fehlercode: %u\r\nDiagnoseprotokoll:\r\n%s",explanation?explanation:L"AstroFocus Studio konnte nicht gestartet werden.",error,g_frontendLogPath[0]?g_frontendLogPath:L"nicht verfügbar");MessageBoxW(g_main,message,L"AstroFocus Studio – Startfehler",MB_OK|MB_ICONERROR);ExitProcess(exitCode);}
static void LoadApplicationIcons(){
    g_appIcon=(HICON)LoadImageW(g_inst,(LPCWSTR)(ULONG_PTR)101,IMAGE_ICON,32,32,0);
    g_appIconSmall=(HICON)LoadImageW(g_inst,(LPCWSTR)(ULONG_PTR)101,IMAGE_ICON,16,16,0);
    if(!g_appIcon||!g_appIconSmall){wchar_t p[700];BuildPath(L"AstroFocusStudio.ico",p);if(!g_appIcon)g_appIcon=(HICON)LoadImageW(0,p,IMAGE_ICON,32,32,LR_LOADFROMFILE);if(!g_appIconSmall)g_appIconSmall=(HICON)LoadImageW(0,p,IMAGE_ICON,16,16,LR_LOADFROMFILE);}
    if(!g_appIcon)g_appIcon=LoadIconW(0,IDI_APPLICATION);if(!g_appIconSmall)g_appIconSmall=g_appIcon;
}

static void AToW(const char* in,wchar_t* out,int cap){if(!in){out[0]=0;return;}int n=MultiByteToWideChar(CP_UTF8,0,in,-1,out,cap);if(n<=0)MultiByteToWideChar(CP_ACP,0,in,-1,out,cap);out[cap-1]=0;}
static void WToA(LPCWSTR in,char* out,int cap){if(!in){out[0]=0;return;}int n=WideCharToMultiByte(CP_UTF8,0,in,-1,out,cap,0,0);if(n<=0)WideCharToMultiByte(CP_ACP,0,in,-1,out,cap,0,0);out[cap-1]=0;}
static BOOL UrlEncodeW(LPCWSTR in,char* out,int cap){char utf[4096];if(!out||cap<2)return FALSE;WToA(in,utf,4096);int o=0;const char* hex="0123456789ABCDEF";for(int i=0;utf[i];i++){unsigned char c=(unsigned char)utf[i];int need=((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c=='-'||c=='_'||c=='.'||c=='~')?1:3;if(o+need>=cap){out[0]=0;return FALSE;}if(need==1)out[o++]=(char)c;else{out[o++]='%';out[o++]=hex[c>>4];out[o++]=hex[c&15];}}out[o]=0;return TRUE;}
static BOOL InitWinsock(){g_ws2=LoadLibraryW(L"ws2_32.dll");if(!g_ws2)return FALSE;pWSAStartup=(PFN_WSAStartup)GetProcAddress(g_ws2,"WSAStartup");pWSACleanup=(PFN_WSACleanup)GetProcAddress(g_ws2,"WSACleanup");p_socket=(PFN_socket)GetProcAddress(g_ws2,"socket");p_connect=(PFN_connect)GetProcAddress(g_ws2,"connect");p_recv=(PFN_recv)GetProcAddress(g_ws2,"recv");p_send=(PFN_send)GetProcAddress(g_ws2,"send");p_closesocket=(PFN_closesocket)GetProcAddress(g_ws2,"closesocket");p_setsockopt=(PFN_setsockopt)GetProcAddress(g_ws2,"setsockopt");p_htons=(PFN_htons)GetProcAddress(g_ws2,"htons");p_htonl=(PFN_htonl)GetProcAddress(g_ws2,"htonl");if(!pWSAStartup||!p_socket||!p_connect||!p_recv||!p_send||!p_closesocket||!p_setsockopt||!p_htons||!p_htonl){FreeLibrary(g_ws2);g_ws2=0;return FALSE;}WSADATA_STORAGE w;memset(&w,0,sizeof(w));if(pWSAStartup(0x0202,&w)!=0){FreeLibrary(g_ws2);g_ws2=0;return FALSE;}return TRUE;}
static BOOL HttpGetTimed(const char* path,BYTE** out,DWORD* outSize,DWORD maxSize,DWORD timeoutMs){
    *out=0;*outSize=0;if(!g_ws2||maxSize<16)return FALSE;SOCKET s=p_socket(AF_INET_MIN,SOCK_STREAM_MIN,IPPROTO_TCP_MIN);if(s==INVALID_SOCKET_VALUE)return FALSE;
    if(timeoutMs<100)timeoutMs=100;if(timeoutMs>12000)timeoutMs=12000;p_setsockopt(s,SOL_SOCKET_MIN,SO_SNDTIMEO_MIN,(const char*)&timeoutMs,sizeof(timeoutMs));p_setsockopt(s,SOL_SOCKET_MIN,SO_RCVTIMEO_MIN,(const char*)&timeoutMs,sizeof(timeoutMs));SOCKADDR_IN a;memset(&a,0,sizeof(a));a.sin_family=AF_INET_MIN;a.sin_port=p_htons(AFS_LOCAL_HTTP_PORT);a.sin_addr.s_addr=p_htonl(INADDR_LOOPBACK_MIN);if(p_connect(s,(SOCKADDR*)&a,sizeof(a))!=0){p_closesocket(s);return FALSE;}
    char req[8192];int rn=sprintf(req,"GET %s HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\nCache-Control: no-cache\r\n\r\n",path);if(rn<=0||rn>=(int)sizeof(req)){p_closesocket(s);return FALSE;}int sent=0;while(sent<rn){int q=p_send(s,req+sent,rn-sent,0);if(q<=0){p_closesocket(s);return FALSE;}sent+=q;}
    DWORD cap=maxSize<65536U?maxSize:65536U;if(cap<1024U)cap=maxSize;BYTE* b=(BYTE*)Alloc((SIZE_T)cap+1);if(!b){p_closesocket(s);return FALSE;}DWORD n=0;for(;;){if(n>=cap){if(cap>=maxSize){Free(b);p_closesocket(s);return FALSE;}DWORD next=cap>maxSize/2U?maxSize:cap*2U;BYTE* grown=(BYTE*)Alloc((SIZE_T)next+1);if(!grown){Free(b);p_closesocket(s);return FALSE;}for(DWORD i=0;i<n;i++)grown[i]=b[i];Free(b);b=grown;cap=next;}int room=(int)(cap-n);int r=p_recv(s,(char*)b+n,room,0);if(r<=0)break;n+=(DWORD)r;}p_closesocket(s);b[n]=0;
    if(n<16||!(b[0]=='H'&&b[1]=='T'&&b[2]=='T'&&b[3]=='P'&&b[4]=='/'&&b[5]=='1'&&b[6]=='.'&&b[7]=='1'&&b[8]==' '&&b[9]=='2'&&b[10]=='0'&&b[11]=='0')){Free(b);return FALSE;}DWORD body=0;for(DWORD i=0;i+3<n;i++)if(b[i]=='\r'&&b[i+1]=='\n'&&b[i+2]=='\r'&&b[i+3]=='\n'){body=i+4;break;}if(!body||body>n){Free(b);return FALSE;}
    DWORD expected=0;BOOL hasLength=FALSE;const char* cl=strstr((const char*)b,"Content-Length:");if(cl&&(DWORD)(cl-(const char*)b)<body){cl+=15;while(*cl==' '||*cl=='\t')cl++;unsigned long long parsed=0;while(*cl>='0'&&*cl<='9'){unsigned digit=(unsigned)(*cl-'0');if(parsed>((unsigned long long)maxSize-digit)/10ULL){Free(b);return FALSE;}parsed=parsed*10ULL+digit;cl++;hasLength=TRUE;}if(hasLength)expected=(DWORD)parsed;}
    DWORD sz=n-body;if((hasLength&&sz!=expected)||body>maxSize||sz>maxSize-body){Free(b);return FALSE;}BYTE* v=(BYTE*)Alloc((SIZE_T)sz+1);if(!v){Free(b);return FALSE;}for(DWORD i=0;i<sz;i++)v[i]=b[body+i];v[sz]=0;Free(b);*out=v;*outSize=sz;return TRUE;
}
static BOOL HttpGet(const char* path,BYTE** out,DWORD* outSize,DWORD maxSize){return HttpGetTimed(path,out,outSize,maxSize,12000);}
static void JString(const char*,const char*,wchar_t*,int);
static BOOL ApiPathTimed(const char* path,DWORD timeoutMs){
    g_lastApiMessage[0]=0;g_lastApiTransportFailure=FALSE;BYTE* b=0;DWORD n=0;
    if(!HttpGetTimed(path,&b,&n,65536,timeoutMs)){g_lastApiTransportFailure=TRUE;lstrcpyW(g_lastApiMessage,L"AstroFocusEngine.exe ist nicht erreichbar oder hat nicht rechtzeitig geantwortet.");return FALSE;}
    BOOL ok=strstr((const char*)b,"\"ok\":true")!=0;JString((const char*)b,"message",g_lastApiMessage,640);if(!g_lastApiMessage[0])lstrcpyW(g_lastApiMessage,ok?L"Aktion erfolgreich.":L"Die Engine hat die Aktion abgelehnt.");Free(b);return ok;
}
static BOOL ApiPath(const char* path){return ApiPathTimed(path,12000);}

static BOOL ApiActionTimed(const char* name,DWORD timeoutMs){char p[512];sprintf(p,"/api/action?name=%s",name);return ApiPathTimed(p,timeoutMs);}
static BOOL ApiAction(const char* name){return ApiActionTimed(name,12000);} static BOOL ApiNamedAction(const char* name,HWND edit){wchar_t w[64];char e[256],p[640];GetText(edit,w,64);if(!UrlEncodeW(w,e,256))return FALSE;sprintf(p,"/api/action?name=%s&filterName=%s",name,e);return ApiPath(p);} static BOOL ApiToggle(const char* n,BOOL on){char p[512];sprintf(p,"/api/toggle?name=%s&value=%d",n,on?1:0);return ApiPath(p);} static BOOL ApiSetW(const char* n,LPCWSTR v){char e[1200],p[1500];if(!UrlEncodeW(v,e,1200))return FALSE;sprintf(p,"/api/set?name=%s&value=%s",n,e);return ApiPath(p);} static BOOL ApiSetInt(const char* n,HWND h){wchar_t v[80];GetText(h,v,80);return ApiSetW(n,v);}
static const char* Key(const char*,const char*);static void JString(const char*,const char*,wchar_t*,int);static void LogLine(LPCWSTR);static BOOL PollStatus();static int MeasureFocusLampHeight(int,int);static void Layout(int,int);static void ApplyBackendSelectors();
typedef BOOL (WINAPI *PFN_GetOpenFileNameW_MIN)(OPENFILENAMEW_MIN*);typedef BOOL (WINAPI *PFN_GetSaveFileNameW_MIN)(OPENFILENAMEW_MIN*);
static BOOL ProfileFileDialog(BOOL save,LPWSTR path,int cap){HMODULE c=LoadLibraryW(L"comdlg32.dll");if(!c)return FALSE;PFN_GetOpenFileNameW_MIN openFn=(PFN_GetOpenFileNameW_MIN)GetProcAddress(c,"GetOpenFileNameW");PFN_GetSaveFileNameW_MIN saveFn=(PFN_GetSaveFileNameW_MIN)GetProcAddress(c,"GetSaveFileNameW");OPENFILENAMEW_MIN o;memset(&o,0,sizeof(o));o.lStructSize=sizeof(o);o.hwndOwner=g_main;o.lpstrFilter=L"AstroFocus-Profile (*.afprofile.json)\0*.afprofile.json\0JSON-Dateien (*.json)\0*.json\0Alle Dateien (*.*)\0*.*\0\0";o.lpstrFile=path;o.nMaxFile=(DWORD)cap;o.lpstrInitialDir=g_appDir;o.lpstrTitle=save?L"AstroFocus-Profil exportieren":L"AstroFocus-Profil importieren";o.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|(save?OFN_OVERWRITEPROMPT:OFN_FILEMUSTEXIST);o.lpstrDefExt=L"afprofile.json";BOOL ok=save?(saveFn&&saveFn(&o)):(openFn&&openFn(&o));FreeLibrary(c);return ok;}
static BOOL WTextContains(LPCWSTR text,LPCWSTR needle){if(!text||!needle||!*needle)return FALSE;for(int i=0;text[i];i++){int j=0;while(needle[j]&&text[i+j]==needle[j])j++;if(!needle[j])return TRUE;}return FALSE;}
static BOOL ToupTekDllFileDialog(LPWSTR path,int cap){HMODULE c=LoadLibraryW(L"comdlg32.dll");if(!c)return FALSE;PFN_GetOpenFileNameW_MIN openFn=(PFN_GetOpenFileNameW_MIN)GetProcAddress(c,"GetOpenFileNameW");OPENFILENAMEW_MIN o;memset(&o,0,sizeof(o));o.lStructSize=sizeof(o);o.hwndOwner=g_main;o.lpstrFilter=L"ToupTek SDK (toupcam.dll)\0toupcam.dll\0DLL-Dateien (*.dll)\0*.dll\0Alle Dateien (*.*)\0*.*\0\0";o.lpstrFile=path;o.nMaxFile=(DWORD)cap;o.lpstrInitialDir=g_appDir;o.lpstrTitle=L"64-Bit-toupcam.dll auswählen";o.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;o.lpstrDefExt=L"dll";BOOL ok=openFn&&openFn(&o);FreeLibrary(c);return ok;}
static BOOL ConfigureToupTekSdkPath(){g_toupTekPickerCancelled=FALSE;wchar_t path[700]=L"";if(!ToupTekDllFileDialog(path,700)){g_toupTekPickerCancelled=TRUE;return FALSE;}if(!ApiSetW("touptekDllPath",path)){MessageBoxW(g_main,g_lastApiMessage[0]?g_lastApiMessage:L"Der ToupTek-SDK-Pfad wurde von der Engine nicht übernommen.",L"ToupTek-SDK",MB_OK|MB_ICONERROR);return FALSE;}return TRUE;}
static BOOL ProfileApiAction(const char* action,LPCWSTR profile,LPCWSTR path,wchar_t* message,int messageCap){char ep[1200],ePath[6200],url[7600];ep[0]=0;ePath[0]=0;if(profile&&!UrlEncodeW(profile,ep,1200)){if(message&&messageCap>0)lstrcpyW(message,L"Profilname ist zu lang.");return FALSE;}if(path&&!UrlEncodeW(path,ePath,6200)){if(message&&messageCap>0)lstrcpyW(message,L"Dateipfad ist zu lang.");return FALSE;}int q=sprintf(url,"/api/action?name=%s%s%s%s%s",action,profile?"&profileName=":"",profile?ep:"",path?"&path=":"",path?ePath:"");if(q<=0||q>=(int)sizeof(url)){if(message&&messageCap>0)lstrcpyW(message,L"Profilanfrage ist zu lang.");return FALSE;}BYTE* b=0;DWORD n=0;if(!HttpGet(url,&b,&n,65536)){if(message&&messageCap>0)lstrcpyW(message,L"Engine nicht erreichbar.");return FALSE;}BOOL ok=strstr((const char*)b,"\"ok\":true")!=0;if(message&&messageCap>0)JString((const char*)b,"message",message,messageCap);Free(b);return ok;}
static BOOL RefreshProfileList(){BYTE* b=0;DWORD n=0;if(!HttpGet("/api/v1/profiles",&b,&n,65536))return FALSE;const char* j=(const char*)b;if(!strstr(j,"\"ok\":true")){Free(b);return FALSE;}wchar_t active[160];JString(j,"active",active,160);SendMessageW(hProfile,CB_RESETCONTENT,0,0);const char* p=Key(j,"profiles");if(p)p=strchr(p,'[');if(p)p++;int count=0;while(p&&*p&&*p!=']'&&count<24){while(*p==' '||*p=='\t'||*p=='\r'||*p=='\n'||*p==',')p++;if(*p!='\"')break;p++;char utf[512];int u=0;while(*p&&*p!='\"'&&u<(int)sizeof(utf)-1){char ch=*p++;if(ch=='\\'&&*p)ch=*p++;utf[u++]=ch;}if(*p=='\"')p++;utf[u]=0;wchar_t name[160];AToW(utf,name,160);ComboAdd(hProfile,name);count++;}SetText(hProfile,active[0]?active:L"Standardprofil");g_profilesLoaded=TRUE;Free(b);return TRUE;}
static BOOL GetProfilePreview(LPCWSTR profile,wchar_t* summary,int cap){char ep[1200],url[1500];if(!UrlEncodeW(profile,ep,1200))return FALSE;int q=sprintf(url,"/api/v1/profile-preview?profileName=%s",ep);if(q<=0||q>=(int)sizeof(url))return FALSE;BYTE* b=0;DWORD n=0;if(!HttpGet(url,&b,&n,65536))return FALSE;BOOL ok=strstr((const char*)b,"\"ok\":true")!=0;if(ok)JString((const char*)b,"summary",summary,cap);Free(b);return ok;}
static int EditInt(HWND h,int def);
static BOOL SaveCapture();
static BOOL SaveAf();
static BOOL SaveAdv();
static BOOL CommitProfileInputs(){
    if(!SaveCapture()||!ApiSetInt("manualStep",hManualStep)||!SaveAf()||!SaveAdv())return FALSE;
    int selected=ComboSel(hSimProfile);if(selected<0||selected>8)selected=g_state.simProfileMode;
    wchar_t backlash[64];GetText(hSimBacklash,backlash,64);int configured=EditInt(hSimBacklash,-1);if(configured<0||configured>5000)return FALSE;
    if(selected!=g_state.simProfileMode){wchar_t mode[16];wsprintfW(mode,L"%d",selected);if(!ApiSetW("simProfileMode",mode))return FALSE;}
    if(configured!=g_state.simBacklashSteps&&!ApiSetW("simBacklashSteps",backlash))return FALSE;
    return TRUE;
}
static void SaveProfileUi(){wchar_t name[160],msg[320];GetText(hProfile,name,160);if(!name[0]){MessageBoxW(g_main,L"Bitte einen Profilnamen eingeben.",L"Profil speichern",MB_OK|MB_ICONWARNING);return;}wchar_t q[360];wsprintfW(q,L"Das Profil '%s' mit den aktuellen Einstellungen speichern?\r\n\r\nEin vorhandenes Profil gleichen Namens wird ersetzt.",name);if(MessageBoxW(g_main,q,L"Profil speichern",MB_YESNO|MB_ICONINFORMATION)!=IDYES)return;if(!CommitProfileInputs()){MessageBoxW(g_main,L"Die aktuellen Aufnahme-, Autofokus-, Automatik- oder Simulatorwerte konnten nicht vollständig an die Engine übertragen werden. Das Profil wurde nicht gespeichert.",L"Profil speichern",MB_OK|MB_ICONERROR);return;}if(ProfileApiAction("profile-save",name,0,msg,320)){RefreshProfileList();LogLine(msg[0]?msg:L"Profil gespeichert.");}else MessageBoxW(g_main,msg[0]?msg:L"Profil konnte nicht gespeichert werden.",L"Profil speichern",MB_OK|MB_ICONERROR);}
static void LoadProfileUi(){wchar_t name[160],summary[1800],msg[320];GetText(hProfile,name,160);if(!GetProfilePreview(name,summary,1800)){MessageBoxW(g_main,L"Profilvorschau konnte nicht geladen werden. Prüfe Profilname und Engine-Verbindung.",L"Profil laden",MB_OK|MB_ICONERROR);return;}wchar_t prompt[2100];wsprintfW(prompt,L"Profil '%s' laden?\r\n\r\n%s",name,summary);if(MessageBoxW(g_main,prompt,L"Profiländerungen prüfen",MB_YESNO|MB_ICONINFORMATION)!=IDYES)return;if(ProfileApiAction("profile-load",name,0,msg,320)){PollStatus();RefreshProfileList();LogLine(msg[0]?msg:L"Profil geladen.");}else MessageBoxW(g_main,msg[0]?msg:L"Profil konnte nicht geladen werden.",L"Profil laden",MB_OK|MB_ICONERROR);}
static void DeleteProfileUi(){wchar_t name[160],msg[320],q[320];GetText(hProfile,name,160);wsprintfW(q,L"Profil '%s' endgültig löschen?",name);if(MessageBoxW(g_main,q,L"Profil löschen",MB_YESNO|MB_ICONWARNING)!=IDYES)return;if(ProfileApiAction("profile-delete",name,0,msg,320)){RefreshProfileList();LogLine(msg[0]?msg:L"Profil gelöscht.");}else MessageBoxW(g_main,msg[0]?msg:L"Profil konnte nicht gelöscht werden.",L"Profil löschen",MB_OK|MB_ICONERROR);}
static void ImportProfileUi(){wchar_t path[700]=L"",msg[320];if(!ProfileFileDialog(FALSE,path,700))return;if(ProfileApiAction("profile-import",0,path,msg,320)){RefreshProfileList();LogLine(msg[0]?msg:L"Profil importiert.");}else MessageBoxW(g_main,msg[0]?msg:L"Profil konnte nicht importiert werden.",L"Profil importieren",MB_OK|MB_ICONERROR);}
static void ExportProfileUi(){wchar_t name[160],path[700]=L"AstroFocusProfile.afprofile.json",msg[320];GetText(hProfile,name,160);if(!ProfileFileDialog(TRUE,path,700))return;if(ProfileApiAction("profile-export",name,path,msg,320))LogLine(msg[0]?msg:L"Profil exportiert.");else MessageBoxW(g_main,msg[0]?msg:L"Profil konnte nicht exportiert werden.",L"Profil exportieren",MB_OK|MB_ICONERROR);}

static BOOL ApiStartAutofocusAtomic(){
    wchar_t inputError[256];if(!ValidateAutofocusInputs(inputError,256)){AppendFrontendTrace("autofocus bundle blocked by local validation");return FALSE;}
    wchar_t ex[80],ga[80],pts[80],step[80],samples[80],backlash[80];GetText(hExposure,ex,80);GetText(hGain,ga,80);GetText(hAfPoints,pts,80);GetText(hAfStep,step,80);GetText(hAfSamples,samples,80);GetText(hBacklash,backlash,80);
    char eEx[240],eGa[240],ePts[240],eStep[240],eSamples[240],eBacklash[240];UrlEncodeW(ex,eEx,240);UrlEncodeW(ga,eGa,240);UrlEncodeW(pts,ePts,240);UrlEncodeW(step,eStep,240);UrlEncodeW(samples,eSamples,240);UrlEncodeW(backlash,eBacklash,240);
    char path[1500];sprintf(path,"/api/action?name=autofocus-start&confirmed=1&exposure=%s&gain=%s&afPoints=%s&afStep=%s&afSamples=%s&backlash=%s&preferredOut=%d&afSelectedStar=%d",eEx,eGa,ePts,eStep,eSamples,eBacklash,Checked(hPrefOut)?1:0,Checked(hAfUseSelected)?1:0);
    char trace[620],aEx[96],aGa[96],aPts[96],aStep[96],aSamples[96],aBacklash[96];WToA(ex,aEx,96);WToA(ga,aGa,96);WToA(pts,aPts,96);WToA(step,aStep,96);WToA(samples,aSamples,96);WToA(backlash,aBacklash,96);sprintf(trace,"autofocus bundle request exp=%s gain=%s points=%s step=%s samples=%s backlash=%s preferred=%d selected=%d",aEx,aGa,aPts,aStep,aSamples,aBacklash,Checked(hPrefOut)?1:0,Checked(hAfUseSelected)?1:0);AppendFrontendTrace(trace);
    BOOL ok=ApiPath(path);AppendFrontendTrace(ok?"autofocus bundle accepted":"autofocus bundle rejected or transport failed");return ok;
}

static double SafeNumber(double v,double lo,double hi){return (v==v&&v>=lo&&v<=hi)?v:0.0;}static int SafeIntFromDouble(double v){if(!(v==v))return 0;if(v>2147483647.0)return 2147483647;if(v<-2147483648.0)return (-2147483647-1);return (int)v;}static unsigned long long SafeU64FromDouble(double v){if(!(v==v)||v<=0.0)return 0;if(v>18446744073709549568.0)return ~0ULL;return (unsigned long long)v;}
static const char* Key(const char* j,const char* k){char p[128];sprintf(p,"\"%s\":",k);return strstr(j,p);} static BOOL JBool(const char* j,const char* k){const char* p=Key(j,k);if(!p)return FALSE;p=strchr(p,':');return p&&strstr(p,"true")==p+1;} static double JNum(const char* j,const char* k){const char* p=Key(j,k);if(!p)return 0;p=strchr(p,':');return p?atof(p+1):0;} static int JInt(const char* j,const char* k){return SafeIntFromDouble(JNum(j,k));} static void JString(const char* j,const char* k,wchar_t* out,int cap){out[0]=0;const char* p=Key(j,k);if(!p)return;p=strchr(p,':');if(!p)return;p=strchr(p,'"');if(!p)return;p++;char a[1024];int n=0;while(*p&&*p!='"'&&n<1023){char ch=*p++;if(ch=='\\'&&*p){char esc=*p++;if(esc=='n')ch='\n';else if(esc=='r')ch='\r';else if(esc=='t')ch='\t';else if(esc=='b')ch='\b';else if(esc=='f')ch='\f';else ch=esc;}a[n++]=ch;}a[n]=0;AToW(a,out,cap);} static int JArrayD(const char* j,const char* k,double* out,int cap){const char* p=Key(j,k);if(!p)return 0;p=strchr(p,'[');if(!p)return 0;p++;int n=0;while(*p&&*p!=']'&&n<cap){while(*p==' '||*p=='\t'||*p=='\r'||*p=='\n'||*p==',')p++;if(!*p||*p==']')break;out[n++]=atof(p);while(*p&&*p!=','&&*p!=']')p++;if(*p==',')p++;}return n;} static AFS_NOINLINE int JArrayI(const char* j,const char* k,int* out,int cap){double d[160];int n=JArrayD(j,k,d,cap);for(int i=0;i<n;i++)out[i]=SafeIntFromDouble(d[i]);return n;}
static AFS_NOINLINE void ParseStatus(const char* j){memset(&g_state,0,sizeof(g_state));g_state.selectedStar=-1;JString(j,"version",g_state.version,32);g_state.camera=JBool(j,"camera");g_state.focuser=JBool(j,"focuser");g_state.focuserMoving=JBool(j,"focuserMoving");g_state.focuserSetupActive=JBool(j,"focuserSetupActive");g_state.autofocus=JBool(j,"autofocus");g_state.stepAssistantActive=JBool(j,"stepAssistantActive");g_state.live=JBool(j,"live");g_state.frameReady=JBool(j,"frameReady");g_state.frameSequence=JInt(j,"frameSequence");g_state.frameAgeMs=SafeU64FromDouble(JNum(j,"frameAgeMs"));g_state.simulator=JBool(j,"simulator");g_state.external=JBool(j,"external");g_state.native=JBool(j,"native");g_state.stretch=JBool(j,"stretch");g_state.stars=JBool(j,"stars");g_state.values=JBool(j,"values");g_state.saturation=JBool(j,"saturation");g_state.zones=JBool(j,"zones");g_state.bahtinov=JBool(j,"bahtinov");g_state.preferredOut=JBool(j,"preferredOut");g_state.autoRefocus=JBool(j,"autoRefocus");g_state.autoRefocusAutomaticRun=JBool(j,"autoRefocusAutomaticRun");g_state.autoRefocusReferenceReady=JBool(j,"autoRefocusReferenceReady");g_state.autoRefocusTemperatureRequired=JBool(j,"autoRefocusTemperatureRequired");g_state.autoRefocusLiveWillResume=JBool(j,"autoRefocusLiveWillResume");g_state.autofocusErrorAutomatic=JBool(j,"autofocusErrorAutomatic");g_state.autoRefocusPaused=JBool(j,"autoRefocusPaused");g_state.autoRefocusTimeEnabled=JBool(j,"autoRefocusTimeEnabled");g_state.autoRefocusTemperatureEnabled=JBool(j,"autoRefocusTemperatureEnabled");g_state.autoRefocusFwhmEnabled=JBool(j,"autoRefocusFwhmEnabled");g_state.cameraWorkerBlocked=JBool(j,"cameraWorkerBlocked");g_state.focuserWorkerBlocked=JBool(j,"focuserWorkerBlocked");g_state.manualStarLocked=JBool(j,"manualStarLocked");g_state.afUseSelectedStar=JBool(j,"afUseSelectedStar");g_state.selectedStarMisses=JInt(j,"selectedStarMisses");g_state.afRecenterCount=JInt(j,"afRecenterCount");g_state.afExpansionCount=JInt(j,"afExpansionCount");g_state.autoRefocusRetrySeconds=JInt(j,"autoRefocusRetrySeconds");g_state.autoRefocusFailureCount=JInt(j,"autoRefocusFailureCount");g_state.autoRefocusBadFrameStreak=JInt(j,"autoRefocusBadFrameStreak");g_state.refocusBadFrames=JInt(j,"refocusBadFrames");g_state.refocusMinStars=JInt(j,"refocusMinStars");g_state.cameraWorkerRetrySeconds=JInt(j,"cameraWorkerRetrySeconds");g_state.focuserWorkerRetrySeconds=JInt(j,"focuserWorkerRetrySeconds");g_state.autoRefocusElapsedMinutes=JNum(j,"autoRefocusElapsedMinutes");g_state.autoRefocusNextMinutes=JNum(j,"autoRefocusNextMinutes");g_state.autoRefocusTempDelta=JNum(j,"autoRefocusTempDelta");g_state.autoRefocusFwhmDegradePercent=JNum(j,"autoRefocusFwhmDegradePercent");g_state.autoRefocusReferenceFwhm=JNum(j,"autoRefocusReferenceFwhm");g_state.autoRefocusCooldownRemainingMinutes=JNum(j,"autoRefocusCooldownRemainingMinutes");g_state.refocusFwhmPercent=JNum(j,"refocusFwhmPercent");g_state.refocusStability=JNum(j,"refocusStability");g_state.refocusCooldown=JNum(j,"refocusCooldown");JString(j,"cameraName",g_state.cameraName,256);JString(j,"focuserName",g_state.focuserName,256);JString(j,"status",g_state.status,320);JString(j,"profile",g_state.profile,160);g_state.profileRevision=JInt(j,"profileRevision");JString(j,"selfTestSummary",g_state.selfTestSummary,256);JString(j,"tiltDirection",g_state.tiltDirection,80);JString(j,"autoRefocusLastReason",g_state.autoRefocusLastReason,256);JString(j,"autofocusErrorCode",g_state.autofocusErrorCode,96);JString(j,"autofocusErrorTitle",g_state.autofocusErrorTitle,256);JString(j,"autofocusErrorDetail",g_state.autofocusErrorDetail,640);JString(j,"cameraWorkerOperation",g_state.cameraWorkerOperation,128);JString(j,"focuserWorkerOperation",g_state.focuserWorkerOperation,128);JString(j,"exposure",g_state.exposure,64);JString(j,"gain",g_state.gain,64);JString(j,"manualStep",g_state.manualStep,64);JString(j,"afPoints",g_state.afPointsText,32);JString(j,"afStep",g_state.afStepText,32);JString(j,"afSamples",g_state.afSamplesText,32);JString(j,"backlash",g_state.backlashText,32);JString(j,"refocusMinutes",g_state.refocusMinText,32);JString(j,"refocusTemp",g_state.refocusTempText,32);g_state.position=JInt(j,"position");g_state.starsCount=JInt(j,"starCount");g_state.usedStars=JInt(j,"usedStars");g_state.selfPassed=JInt(j,"selfTestPassed");g_state.selfTotal=JInt(j,"selfTestTotal");g_state.safeMin=JInt(j,"safeMin");g_state.safeMax=JInt(j,"safeMax");g_state.fwhm=JNum(j,"fwhm");g_state.hfr=JNum(j,"hfr");g_state.snr=JNum(j,"snr");g_state.ecc=JNum(j,"ecc");g_state.stability=JNum(j,"stability");g_state.temperature=JNum(j,"temperature");g_state.hasTemperature=JBool(j,"hasTemperature");g_state.selectedFwhm=JNum(j,"selectedFwhm");g_state.selectedHfr=JNum(j,"selectedHfr");g_state.selectedSnr=JNum(j,"selectedSnr");g_state.selectedEcc=JNum(j,"selectedEcc");g_state.bahtOffset=JNum(j,"bahtOffset");g_state.bahtConfidence=JNum(j,"bahtConfidence");g_state.sharpness=JNum(j,"sharpness");g_state.bahtValid=JBool(j,"bahtValid");g_state.tilt=JNum(j,"tilt");g_state.tiltValid=JBool(j,"tiltValid");JArrayD(j,"zoneFwhm",g_state.zone,9);JArrayI(j,"zoneCounts",g_state.zoneCount,9);g_state.afCount=JArrayI(j,"afPositions",g_state.afPos,15);JArrayD(j,"afMetrics",g_state.afMetric,15);JArrayD(j,"afFwhmMetrics",g_state.afFwhm,15);JArrayD(j,"afMetricSigma",g_state.afMetricSigma,15);JArrayD(j,"afFwhmSigma",g_state.afFwhmSigma,15);JArrayD(j,"afResiduals",g_state.afResidual,15);JArrayD(j,"afFwhmResiduals",g_state.afFwhmResidual,15);JArrayI(j,"afOutliers",g_state.afOutlier,15);JArrayI(j,"afSamplesPerPoint",g_state.afSamplesPerPoint,15);JArrayD(j,"afFitParams",g_state.afFitParams,5);JArrayD(j,"afFitFwhmParams",g_state.afFitFwhmParams,5);g_state.afMeasuredCount=JInt(j,"afMeasuredCount");g_state.afFitValid=JBool(j,"afFitValid");g_state.afFitFwhmValid=JBool(j,"afFitFwhmValid");g_state.afFitA=JNum(j,"afFitA");g_state.afFitB=JNum(j,"afFitB");g_state.afFitC=JNum(j,"afFitC");g_state.afFitFwhmA=JNum(j,"afFitFwhmA");g_state.afFitFwhmB=JNum(j,"afFitFwhmB");g_state.afFitFwhmC=JNum(j,"afFitFwhmC");g_state.afFitCenter=JNum(j,"afFitCenter");g_state.afFitScale=JNum(j,"afFitScale");g_state.afFitR2=JNum(j,"afFitR2");g_state.afFitFwhmR2=JNum(j,"afFitFwhmR2");g_state.afFitConfidence=JNum(j,"afFitConfidence");g_state.afCurveQuality=JNum(j,"afCurveQuality");if(g_state.afCurveQuality<=0.0)g_state.afCurveQuality=g_state.afFitConfidence;g_state.afFocusSigma=JNum(j,"afFocusSigma");g_state.afFocusSigmaLoo=JNum(j,"afFocusSigmaLoo");g_state.afReducedChi2=JNum(j,"afReducedChi2");g_state.afResidualRms=JNum(j,"afResidualRms");g_state.afAicc=JNum(j,"afAicc");g_state.afFitModel=JInt(j,"afFitModel");g_state.afFitFwhmModel=JInt(j,"afFitFwhmModel");g_state.afFitInliers=JInt(j,"afFitInliers");g_state.afFitOutliers=JInt(j,"afFitOutliers");g_state.afAdaptiveSamplesAdded=JInt(j,"afAdaptiveSamplesAdded");JString(j,"afFitMethod",g_state.afFitMethod,160);g_state.afBestPosition=JInt(j,"afBestPosition");g_state.afExpectedHfr=JNum(j,"afExpectedHfr");g_state.afExpectedFwhm=JNum(j,"afExpectedFwhm");g_state.afFinalValid=JBool(j,"afFinalValid");g_state.afFinalPosition=JInt(j,"afFinalPosition");g_state.afFinalHfr=JNum(j,"afFinalHfr");g_state.afFinalFwhm=JNum(j,"afFinalFwhm");int sxn=JArrayD(j,"starX",g_state.starX,160),syn=JArrayD(j,"starY",g_state.starY,160),sfn=JArrayD(j,"starFwhm",g_state.starFwhm,160),sun=JArrayI(j,"starUsed",g_state.starUsed,160),ssn=JArrayI(j,"starSaturated",g_state.starSaturated,160);g_state.starArrayCount=sxn;if(syn<g_state.starArrayCount)g_state.starArrayCount=syn;if(sfn<g_state.starArrayCount)g_state.starArrayCount=sfn;if(sun<g_state.starArrayCount)g_state.starArrayCount=sun;if(ssn<g_state.starArrayCount)g_state.starArrayCount=ssn;g_state.selectedStar=JInt(j,"selectedStar");g_state.tempCompEnabled=JBool(j,"tempCompEnabled");g_state.autoStartPositionEnabled=JBool(j,"autoStartPositionEnabled");g_state.profileModelValid=JBool(j,"profileModelValid");g_state.backlashCalibrationActive=JBool(j,"backlashCalibrationActive");g_state.refocusOnMeridian=JBool(j,"refocusOnMeridian");g_state.refocusOnReconnect=JBool(j,"refocusOnReconnect");g_state.refocusOnFilter=JBool(j,"refocusOnFilter");g_state.seeingIndex=JInt(j,"seeingIndex");g_state.transparencyIndex=JNum(j,"transparencyIndex");g_state.focusNeedScore=JInt(j,"focusNeedScore");g_state.afQualityScore=JInt(j,"afQualityScore");g_state.fieldCurvature=JNum(j,"fieldCurvature");g_state.fieldAsymmetry=JNum(j,"fieldAsymmetry");g_state.fieldQualityScore=JNum(j,"fieldQualityScore");g_state.tiltConfidence=JNum(j,"tiltConfidence");g_state.profileSuccessfulRuns=JInt(j,"profileSuccessfulRuns");g_state.profileTypicalPosition=JInt(j,"profileTypicalPosition");g_state.profileRecommendedStep=JInt(j,"profileRecommendedStep");g_state.profileBacklash=JInt(j,"profileBacklash");g_state.profileTypicalFwhm=JNum(j,"profileTypicalFwhm");g_state.profileTypicalHfr=JNum(j,"profileTypicalHfr");g_state.profileQualityMean=JNum(j,"profileQualityMean");g_state.backlashCalibrationEstimated=JInt(j,"backlashCalibrationEstimated");g_state.filterOffsetCount=JInt(j,"filterOffsetCount");g_state.refocusEveryCaptures=JInt(j,"refocusEveryCaptures");g_state.captureEventCounter=JInt(j,"captureEventCounter");g_state.tempCompDeadband=JInt(j,"tempCompDeadband");g_state.tempCompMaxStep=JInt(j,"tempCompMaxStep");g_state.tempCompPredictedPosition=JInt(j,"tempCompPredictedPosition");g_state.tempProfileCount=JInt(j,"tempProfileCount");g_state.tempSlope=JNum(j,"tempSlope");g_state.tempIntercept=JNum(j,"tempIntercept");JString(j,"seeingState",g_state.seeingState,128);JString(j,"focusNeedLabel",g_state.focusNeedLabel,128);JString(j,"focusNeedReason",g_state.focusNeedReason,320);JString(j,"afQualityLabel",g_state.afQualityLabel,128);JString(j,"fieldAdvice",g_state.fieldAdvice,320);JString(j,"currentFilter",g_state.currentFilter,64);JString(j,"lastExternalEvent",g_state.lastExternalEvent,160);JString(j,"backlashCalibrationResult",g_state.backlashCalibrationResult,200);JString(j,"simProfileName",g_state.simProfileName,128);g_state.backlashCalibrationProgress=JInt(j,"backlashCalibrationProgress");g_state.backlashCalibrationLimit=JInt(j,"backlashCalibrationLimit");g_state.simProfileMode=JInt(j,"simProfileMode");g_state.simActiveProfile=JInt(j,"simActiveProfile");g_state.simBacklashSteps=JInt(j,"simBacklashSteps");g_state.simBacklashRemaining=JInt(j,"simBacklashRemaining");g_state.simMotorPosition=JInt(j,"simMotorPosition");g_state.simOpticalPosition=JInt(j,"simOpticalPosition");g_state.tempFitValid=JBool(j,"tempFitValid");g_state.tempProfileArrayCount=JArrayD(j,"tempProfileTemperature",g_state.tempProfileTemperature,64);{int pn=JArrayI(j,"tempProfilePosition",g_state.tempProfilePosition,64);if(pn<g_state.tempProfileArrayCount)g_state.tempProfileArrayCount=pn;}g_state.afValidationPassed=JBool(j,"afValidationPassed");g_state.afRollbackPerformed=JBool(j,"afRollbackPerformed");JString(j,"afValidationState",g_state.afValidationState,128);JString(j,"afValidationReason",g_state.afValidationReason,384);g_state.sessionMinutes=JNum(j,"sessionMinutes");g_state.sessionAfAttempts=JInt(j,"sessionAfAttempts");g_state.sessionAfSuccess=JInt(j,"sessionAfSuccess");g_state.sessionAfFailed=JInt(j,"sessionAfFailed");g_state.sessionAfRollbacks=JInt(j,"sessionAfRollbacks");g_state.sessionBestFwhm=JNum(j,"sessionBestFwhm");g_state.sessionWorstFwhm=JNum(j,"sessionWorstFwhm");g_state.sessionStartPosition=JInt(j,"sessionStartPosition");g_state.sessionLastPosition=JInt(j,"sessionLastPosition");g_state.sessionHasTemperature=JBool(j,"sessionHasTemperature");g_state.sessionStartTemperature=JNum(j,"sessionStartTemperature");g_state.sessionLastTemperature=JNum(j,"sessionLastTemperature");
    g_state.continuousFocusEnabled=JBool(j,"continuousFocusEnabled");g_state.continuousFocusFallback=JBool(j,"continuousFocusFallback");g_state.continuousFocusPaused=JBool(j,"continuousFocusPaused");g_state.continuousFocusMode=JInt(j,"continuousFocusMode");g_state.continuousFocusPhase=JInt(j,"continuousFocusPhase");JString(j,"continuousFocusState",g_state.continuousFocusState,96);JString(j,"continuousFocusReason",g_state.continuousFocusReason,320);g_state.continuousFocusMinFrames=JInt(j,"continuousFocusMinFrames");g_state.continuousFocusDeadband=JInt(j,"continuousFocusDeadband");g_state.continuousFocusMaxStep=JInt(j,"continuousFocusMaxStep");g_state.continuousFocusMinConfidence=JInt(j,"continuousFocusMinConfidence");g_state.continuousFocusMinImprovement=JNum(j,"continuousFocusMinImprovement");g_state.continuousFocusSettleMs=JInt(j,"continuousFocusSettleMs");g_state.continuousFocusConfidence=JNum(j,"continuousFocusConfidence");g_state.continuousFocusReferenceMetric=JNum(j,"continuousFocusReferenceMetric");g_state.continuousFocusEstimatedError=JNum(j,"continuousFocusEstimatedError");g_state.continuousFocusDriftStepsPerMinute=JNum(j,"continuousFocusDriftStepsPerMinute");g_state.continuousFocusLastCorrection=JInt(j,"continuousFocusLastCorrection");g_state.continuousFocusTarget=JInt(j,"continuousFocusTarget");g_state.continuousFocusAccepted=JInt(j,"continuousFocusAccepted");g_state.continuousFocusRejected=JInt(j,"continuousFocusRejected");
    g_state.fwhm=SafeNumber(g_state.fwhm,0.0,1000.0);g_state.hfr=SafeNumber(g_state.hfr,0.0,1000.0);g_state.snr=SafeNumber(g_state.snr,0.0,100000000.0);g_state.ecc=SafeNumber(g_state.ecc,0.0,10.0);g_state.stability=SafeNumber(g_state.stability,0.0,1000.0);g_state.temperature=SafeNumber(g_state.temperature,-273.15,1000.0);g_state.selectedFwhm=SafeNumber(g_state.selectedFwhm,0.0,1000.0);g_state.selectedHfr=SafeNumber(g_state.selectedHfr,0.0,1000.0);g_state.selectedSnr=SafeNumber(g_state.selectedSnr,0.0,100000000.0);g_state.selectedEcc=SafeNumber(g_state.selectedEcc,0.0,10.0);g_state.bahtOffset=SafeNumber(g_state.bahtOffset,-10000.0,10000.0);g_state.bahtConfidence=SafeNumber(g_state.bahtConfidence,0.0,100.0);g_state.sharpness=SafeNumber(g_state.sharpness,0.0,1000000000.0);g_state.tilt=SafeNumber(g_state.tilt,0.0,10000.0);
    g_state.autoRefocusElapsedMinutes=SafeNumber(g_state.autoRefocusElapsedMinutes,0.0,1000000.0);g_state.autoRefocusNextMinutes=SafeNumber(g_state.autoRefocusNextMinutes,-1.0,1000000.0);g_state.autoRefocusTempDelta=SafeNumber(g_state.autoRefocusTempDelta,0.0,10000.0);g_state.autoRefocusFwhmDegradePercent=SafeNumber(g_state.autoRefocusFwhmDegradePercent,-100.0,1000000.0);g_state.autoRefocusReferenceFwhm=SafeNumber(g_state.autoRefocusReferenceFwhm,0.0,1000.0);g_state.autoRefocusCooldownRemainingMinutes=SafeNumber(g_state.autoRefocusCooldownRemainingMinutes,0.0,1000000.0);g_state.refocusFwhmPercent=SafeNumber(g_state.refocusFwhmPercent,0.0,1000000.0);g_state.refocusStability=SafeNumber(g_state.refocusStability,0.0,10000.0);g_state.refocusCooldown=SafeNumber(g_state.refocusCooldown,0.0,1000000.0);
    for(int i=0;i<9;i++)g_state.zone[i]=SafeNumber(g_state.zone[i],0.0,1000.0);for(int i=0;i<15;i++){g_state.afMetric[i]=SafeNumber(g_state.afMetric[i],0.0,1000.0);g_state.afFwhm[i]=SafeNumber(g_state.afFwhm[i],0.0,1000.0);}g_state.afFitA=SafeNumber(g_state.afFitA,-1000000.0,1000000.0);g_state.afFitB=SafeNumber(g_state.afFitB,-1000000.0,1000000.0);g_state.afFitC=SafeNumber(g_state.afFitC,-1000000.0,1000000.0);g_state.afFitFwhmA=SafeNumber(g_state.afFitFwhmA,-1000000.0,1000000.0);g_state.afFitFwhmB=SafeNumber(g_state.afFitFwhmB,-1000000.0,1000000.0);g_state.afFitFwhmC=SafeNumber(g_state.afFitFwhmC,-1000000.0,1000000.0);g_state.afFitCenter=SafeNumber(g_state.afFitCenter,-100000000.0,100000000.0);g_state.afFitScale=SafeNumber(g_state.afFitScale,0.0,100000000.0);g_state.afFitR2=SafeNumber(g_state.afFitR2,-100.0,100.0);g_state.afFitFwhmR2=SafeNumber(g_state.afFitFwhmR2,-100.0,100.0);g_state.afFitConfidence=SafeNumber(g_state.afFitConfidence,0.0,100.0);g_state.afExpectedHfr=SafeNumber(g_state.afExpectedHfr,0.0,1000.0);g_state.afExpectedFwhm=SafeNumber(g_state.afExpectedFwhm,0.0,1000.0);g_state.afFinalHfr=SafeNumber(g_state.afFinalHfr,0.0,1000.0);g_state.afFinalFwhm=SafeNumber(g_state.afFinalFwhm,0.0,1000.0);
    if(g_state.starArrayCount<0)g_state.starArrayCount=0;if(g_state.starArrayCount>160)g_state.starArrayCount=160;
    for(int i=0;i<g_state.starArrayCount;i++){if(!(g_state.starX[i]>=0.0&&g_state.starX[i]<=10000.0))g_state.starX[i]=0.0;if(!(g_state.starY[i]>=0.0&&g_state.starY[i]<=10000.0))g_state.starY[i]=0.0;if(!(g_state.starFwhm[i]>=0.0&&g_state.starFwhm[i]<=1000.0))g_state.starFwhm[i]=0.0;g_state.starUsed[i]=g_state.starUsed[i]?1:0;g_state.starSaturated[i]=g_state.starSaturated[i]?1:0;}
    if(g_state.selectedStar<0||g_state.selectedStar>=g_state.starArrayCount)g_state.selectedStar=-1;
    if(g_state.afCount<0)g_state.afCount=0;if(g_state.afCount>15)g_state.afCount=15;if(g_state.afMeasuredCount<0)g_state.afMeasuredCount=0;if(g_state.afMeasuredCount>g_state.afCount)g_state.afMeasuredCount=g_state.afCount;
    if(g_state.refocusMinStars<1)g_state.refocusMinStars=1;if(g_state.refocusMinStars>160)g_state.refocusMinStars=160;
    g_state.simProfileMode=ClampI(g_state.simProfileMode,0,8);g_state.simActiveProfile=ClampI(g_state.simActiveProfile,0,7);g_state.simBacklashSteps=ClampI(g_state.simBacklashSteps,0,5000);g_state.simBacklashRemaining=ClampI(g_state.simBacklashRemaining,0,5000);g_state.simMotorPosition=ClampI(g_state.simMotorPosition,0,100000000);g_state.simOpticalPosition=ClampI(g_state.simOpticalPosition,0,100000000);g_state.backlashCalibrationProgress=ClampI(g_state.backlashCalibrationProgress,0,1000000);g_state.backlashCalibrationLimit=ClampI(g_state.backlashCalibrationLimit,0,1000000);g_state.continuousFocusMode=ClampI(g_state.continuousFocusMode,0,2);g_state.continuousFocusPhase=ClampI(g_state.continuousFocusPhase,0,3);g_state.continuousFocusMinFrames=ClampI(g_state.continuousFocusMinFrames,3,12);g_state.continuousFocusDeadband=ClampI(g_state.continuousFocusDeadband,1,1000);g_state.continuousFocusMaxStep=ClampI(g_state.continuousFocusMaxStep,g_state.continuousFocusDeadband,5000);g_state.continuousFocusMinConfidence=ClampI(g_state.continuousFocusMinConfidence,30,100);g_state.continuousFocusSettleMs=ClampI(g_state.continuousFocusSettleMs,100,30000);g_state.continuousFocusConfidence=SafeNumber(g_state.continuousFocusConfidence,0.0,100.0);g_state.continuousFocusReferenceMetric=SafeNumber(g_state.continuousFocusReferenceMetric,0.0,1000.0);g_state.continuousFocusEstimatedError=SafeNumber(g_state.continuousFocusEstimatedError,-100000.0,100000.0);g_state.continuousFocusDriftStepsPerMinute=SafeNumber(g_state.continuousFocusDriftStepsPerMinute,-100000.0,100000.0);g_state.continuousFocusMinImprovement=SafeNumber(g_state.continuousFocusMinImprovement,0.1,25.0);
}
static void LogLine(LPCWSTR t){if(!hLog||!t)return;wchar_t old[6000];GetText(hLog,old,6000);int tn=lstrlenW(t),on=lstrlenW(old);SIZE_T count=(SIZE_T)tn+(SIZE_T)on+4;wchar_t* line=(wchar_t*)Alloc(count*sizeof(wchar_t));if(!line)return;int o=0;for(int i=0;i<tn;i++)line[o++]=t[i];line[o++]=L'\r';line[o++]=L'\n';for(int i=0;i<on;i++)line[o++]=old[i];line[o]=0;SetText(hLog,line);Free(line);}
static BOOL PreviewStateChanged(const AppState* o){if(!o)return TRUE;return o->frameReady!=g_state.frameReady||o->frameSequence!=g_state.frameSequence||o->simulator!=g_state.simulator||o->live!=g_state.live||o->stretch!=g_state.stretch||o->stars!=g_state.stars||o->values!=g_state.values||o->saturation!=g_state.saturation||o->zones!=g_state.zones||o->selectedStar!=g_state.selectedStar||o->manualStarLocked!=g_state.manualStarLocked||o->starArrayCount!=g_state.starArrayCount;}
static BOOL MetricsStateChanged(const AppState* o){if(!o)return TRUE;return o->position!=g_state.position||o->autofocus!=g_state.autofocus||o->fwhm!=g_state.fwhm||o->hfr!=g_state.hfr||o->snr!=g_state.snr||o->ecc!=g_state.ecc||o->stability!=g_state.stability||o->temperature!=g_state.temperature||o->hasTemperature!=g_state.hasTemperature||o->usedStars!=g_state.usedStars||o->starsCount!=g_state.starsCount||o->selectedFwhm!=g_state.selectedFwhm||o->selectedHfr!=g_state.selectedHfr||o->selectedSnr!=g_state.selectedSnr||o->selectedEcc!=g_state.selectedEcc||o->afCount!=g_state.afCount||o->afMeasuredCount!=g_state.afMeasuredCount||o->afFitValid!=g_state.afFitValid||o->afFinalValid!=g_state.afFinalValid||o->afBestPosition!=g_state.afBestPosition||o->afFinalFwhm!=g_state.afFinalFwhm||o->selfPassed!=g_state.selfPassed||o->selfTotal!=g_state.selfTotal||o->tilt!=g_state.tilt||o->tiltValid!=g_state.tiltValid||o->focusNeedScore!=g_state.focusNeedScore||!WEqual(o->focusNeedLabel,g_state.focusNeedLabel)||!WEqual(o->focusNeedReason,g_state.focusNeedReason);}
static void FormatRetryClock(int seconds,wchar_t* out){SYSTEMTIME st;GetLocalTime(&st);int total=(int)st.wHour*3600+(int)st.wMinute*60+(int)st.wSecond+(seconds>0?seconds:0);total%=86400;wsprintfW(out,L"%02d:%02d:%02d",total/3600,(total/60)%60,total%60);}
static void UpdateStatusRail(){
    if(!hStatus)return;
    wchar_t status[760],focus[64],quality[64];
    if(g_state.focuser)wsprintfW(focus,L"Fokus %d",g_state.position);else lstrcpyW(focus,L"Fokus –");
    if(g_state.fwhm>0.0){FormatD(g_state.fwhm,2,quality);lstrcatW(quality,L" px");}else lstrcpyW(quality,L"–");
    wsprintfW(status,L"%s Kamera   %s Fokussierer   %s   FWHM %s   ·   %s",g_state.camera?L"●":L"○",g_state.focuser?L"●":L"○",focus,quality,g_state.status[0]?g_state.status:(g_engineOnline?L"Bereit":L"Engine nicht erreichbar"));
    SetText(hStatus,status);
}
static AFS_NOINLINE void UpdateUiFromState(const AppState* old){SetFrontendPhase("UI state update: begin");BOOL trendChanged=UpdateTrendHistory(old);BOOL cfHistoryChanged=UpdateContinuousFocusHistory(old);BOOL syncProfileControls=!g_uiInitialized||!old||old->profileRevision!=g_state.profileRevision;BOOL syncCalibratedBacklash=old&&g_state.backlashCalibrationEstimated>=0&&(old->backlashCalibrationEstimated!=g_state.backlashCalibrationEstimated||!WEqual(old->backlashText,g_state.backlashText));BOOL focusLampTextChanged=!old||!WEqual(old->focusNeedLabel,g_state.focusNeedLabel)||!WEqual(old->focusNeedReason,g_state.focusNeedReason);UpdateStatusRail();BOOL profileLoadSafe=!g_state.autofocus&&!g_state.stepAssistantActive&&!g_state.backlashCalibrationActive&&!g_state.live;EnableWindow(hLoadProfile,profileLoadSafe);EnableWindow(hDeleteProfile,profileLoadSafe);EnableWindow(hSaveProfile,!g_state.autofocus&&!g_state.stepAssistantActive&&!g_state.backlashCalibrationActive);EnableWindow(hImportProfile,TRUE);EnableWindow(hExportProfile,TRUE);wchar_t* w=g_uiScratch.w;if(g_state.focuser)wsprintfW(w,L"%d",g_state.position);else lstrcpyW(w,L"–");SetText(hPosition,w);if(g_state.hasTemperature){FormatD(g_state.temperature,1,w);lstrcatW(w,L" °C");}else lstrcpyW(w,L"–");SetText(hTemperature,w);SetText(hCamConnect,g_state.camera?L"Trennen":L"Verbinden");SetText(hFocConnect,g_state.focuser?L"Trennen":L"Verbinden");SetText(hLive,g_state.live?L"■ Live-Fokus stoppen":L"▶ Live-Fokus starten");SetText(hFocDevice,g_state.focuserName);
BOOL focuserSetupActive=g_focuserSetupProcess!=0||g_focuserSetupEngineLock||g_state.focuserSetupActive;BOOL focusBusy=FocuserOperationBusy();
SetText(hFocSetup,focuserSetupActive?L"ASCOM-Treiberdialog geöffnet …":L"Kalibrierung / Treibereinstellungen");SetText(hStepAssist,g_state.stepAssistantActive?L"Schritt-Assistent abbrechen":L"Schritt-Assistent");SetText(hBacklashCal,g_state.backlashCalibrationActive?L"Backlash-Kalibrierung abbrechen":L"Backlash automatisch kalibrieren");
EnableWindow(hFocBackend,!focuserSetupActive&&!focusBusy);EnableWindow(hFocSelect,!focuserSetupActive&&!focusBusy&&ComboSel(hFocBackend)==1&&g_ascomChooserProcess==0);EnableWindow(hFocConnect,!focuserSetupActive&&!focusBusy);EnableWindow(hFocSetup,!focuserSetupActive&&!focusBusy&&ComboSel(hFocBackend)==1&&g_state.focuserName[0]);EnableWindow(hMoveIn,!focuserSetupActive&&!focusBusy);EnableWindow(hMoveOut,!focuserSetupActive&&!focusBusy);EnableWindow(hHalt,!focuserSetupActive&&(g_state.focuser||focusBusy));EnableWindow(hLive,!focusBusy);EnableWindow(hStepAssist,!g_state.autofocus&&!g_state.backlashCalibrationActive);EnableWindow(hBacklashCal,!g_state.autofocus&&!g_state.stepAssistantActive);EnableWindow(hAfStop,g_state.autofocus);EnableWindow(hFilterLearn,g_state.focuser&&!focusBusy);EnableWindow(hFilterApply,g_state.focuser&&!focusBusy);
EnableWindow(hSimProfile,g_state.simulator&&!focusBusy);EnableWindow(hSimBacklash,g_state.simulator&&!focusBusy);EnableWindow(hSimApply,g_state.simulator&&!focusBusy);EnableWindow(hSimRandomize,g_state.simulator&&!focusBusy);{wchar_t simInfo[420];if(!g_state.simulator)wsprintfW(simInfo,L"Simulator ist nicht ausgewählt. Wähle links als Kamera-Backend ‚Simulator‘.");else if(g_state.backlashCalibrationActive)wsprintfW(simInfo,L"Aktives Profil: %s · Backlash-Test: %d von %d Schritten · Rest %d · Motor/optisch %d/%d",g_state.simProfileName[0]?g_state.simProfileName:L"–",g_state.backlashCalibrationProgress,g_state.backlashCalibrationLimit,g_state.simBacklashRemaining,g_state.simMotorPosition,g_state.simOpticalPosition);else wsprintfW(simInfo,L"Aktives Profil: %s · Backlash: %d · Motor/optisch: %d/%d · Modus: %s",g_state.simProfileName[0]?g_state.simProfileName:L"–",g_state.simBacklashSteps,g_state.simMotorPosition,g_state.simOpticalPosition,g_state.simProfileMode==8?L"zufällig":L"fest");SetText(hSimProfileInfo,simInfo);}
if(ComboSel(hCamBackend)!=1)SetText(hCamDevice,g_state.cameraName);Check(hStretch,g_state.stretch);Check(hStars,g_state.stars);Check(hValues,g_state.values);Check(hSaturation,g_state.saturation);Check(hZones,g_state.zones);Check(hBahtEnable,g_state.bahtinov);Check(hPrefOut,g_state.preferredOut);Check(hAutoRefocus,g_state.autoRefocus);Check(hAfUseSelected,g_state.afUseSelectedStar);Check(hCfEnable,g_state.continuousFocusEnabled);Check(hCfFallback,g_state.continuousFocusFallback);
{SetFrontendPhase("UI state update: continuous focus");wchar_t mode[32],confidence[32],reference[32],error[32],drift[32],lastCorrection[32],number[32],cfInfo[1800];lstrcpyW(mode,g_state.continuousFocusMode==0?L"Prädiktiv":(g_state.continuousFocusMode==1?L"Bildbasiert":L"Hybrid"));FormatD(g_state.continuousFocusConfidence,1,confidence);FormatD(g_state.continuousFocusReferenceMetric,2,reference);FormatD(g_state.continuousFocusEstimatedError,1,error);FormatD(g_state.continuousFocusDriftStepsPerMinute,2,drift);FormatSignedInt(g_state.continuousFocusLastCorrection,lastCorrection,32);cfInfo[0]=0;AppendWBounded(cfInfo,1800,L"Status: ");AppendWBounded(cfInfo,1800,g_state.continuousFocusState[0]?g_state.continuousFocusState:L"–");if(g_state.continuousFocusPaused)AppendWBounded(cfInfo,1800,L" (pausiert)");AppendWBounded(cfInfo,1800,L"\r\nModus: ");AppendWBounded(cfInfo,1800,mode);AppendWBounded(cfInfo,1800,L" · Regelqualität: ");AppendWBounded(cfInfo,1800,confidence);AppendWBounded(cfInfo,1800,L" %\r\nReferenzmetrik: ");AppendWBounded(cfInfo,1800,reference);AppendWBounded(cfInfo,1800,L" px · geschätzte Abweichung: ");AppendWBounded(cfInfo,1800,error);AppendWBounded(cfInfo,1800,L" Schritte\r\nPosition/Ziel: ");wsprintfW(number,L"%d",g_state.position);AppendWBounded(cfInfo,1800,number);AppendWBounded(cfInfo,1800,L" / ");wsprintfW(number,L"%d",g_state.continuousFocusTarget);AppendWBounded(cfInfo,1800,number);AppendWBounded(cfInfo,1800,L" · letzte Korrektur: ");AppendWBounded(cfInfo,1800,lastCorrection);AppendWBounded(cfInfo,1800,L"\r\nDrift: ");AppendWBounded(cfInfo,1800,drift);AppendWBounded(cfInfo,1800,L" Schritte/min · bestätigt/verworfen: ");wsprintfW(number,L"%d",g_state.continuousFocusAccepted);AppendWBounded(cfInfo,1800,number);AppendWBounded(cfInfo,1800,L"/");wsprintfW(number,L"%d",g_state.continuousFocusRejected);AppendWBounded(cfInfo,1800,number);AppendWBounded(cfInfo,1800,L"\r\n\r\n");AppendWBounded(cfInfo,1800,g_state.continuousFocusReason[0]?g_state.continuousFocusReason:L"Wartet auf Statusdaten.");SetText(hCfInfo,cfInfo);EnableWindow(hCfResume,g_state.continuousFocusPaused);BOOL cfSettingsEnabled=g_state.continuousFocusPhase!=1&&g_state.continuousFocusPhase!=2;EnableWindow(hCfMode,cfSettingsEnabled);EnableWindow(hCfMinFrames,cfSettingsEnabled);EnableWindow(hCfDeadband,cfSettingsEnabled);EnableWindow(hCfMaxStep,cfSettingsEnabled);EnableWindow(hCfConfidence,cfSettingsEnabled);EnableWindow(hCfImprovement,cfSettingsEnabled);EnableWindow(hCfSettle,cfSettingsEnabled);EnableWindow(hCfSave,cfSettingsEnabled);EnableWindow(hCfReset,cfSettingsEnabled);}

SetFrontendPhase("UI state update: automation");wchar_t* autoInfo=g_uiScratch.autoInfo;wchar_t* elapsed=g_uiScratch.elapsed;wchar_t* nextTime=g_uiScratch.nextTime;wchar_t* tempDelta=g_uiScratch.tempDelta;wchar_t* fwhmDelta=g_uiScratch.fwhmDelta;wchar_t* retryClock=g_uiScratch.retryClock;wchar_t* threshold=g_uiScratch.threshold;wchar_t* stabilityCurrent=g_uiScratch.stabilityCurrent;wchar_t* stabilityLimit=g_uiScratch.stabilityLimit;wchar_t* cooldown=g_uiScratch.cooldown;FormatD(g_state.autoRefocusElapsedMinutes,1,elapsed);FormatD(g_state.autoRefocusNextMinutes,1,nextTime);FormatD(g_state.autoRefocusTempDelta,1,tempDelta);FormatD(g_state.autoRefocusFwhmDegradePercent,1,fwhmDelta);FormatD(g_state.refocusFwhmPercent,1,threshold);FormatD(g_state.stability,2,stabilityCurrent);FormatD(g_state.refocusStability,2,stabilityLimit);FormatD(g_state.autoRefocusCooldownRemainingMinutes,1,cooldown);FormatRetryClock(g_state.autoRefocusRetrySeconds,retryClock);
wchar_t* timeLine=g_uiScratch.timeLine;wchar_t* tempLine=g_uiScratch.tempLine;wchar_t* fwhmLine=g_uiScratch.fwhmLine;wchar_t* workerLine=g_uiScratch.workerLine;
if(g_state.autoRefocusTimeEnabled)wsprintfW(timeLine,L"Zeittrigger: aktiv · nächster Refokus in %s min",nextTime);else lstrcpyW(timeLine,L"Zeittrigger: deaktiviert");
if(!g_state.autoRefocusTemperatureEnabled)lstrcpyW(tempLine,L"Temperaturtrigger: deaktiviert");else if(!g_state.hasTemperature)lstrcpyW(tempLine,L"Temperaturtrigger: aktiv · keine Temperatur verfügbar");else wsprintfW(tempLine,L"Temperaturtrigger: aktiv · Änderung seit Referenz %s °C",tempDelta);
if(!g_state.autoRefocusFwhmEnabled)lstrcpyW(fwhmLine,L"FWHM-Trigger: deaktiviert");else wsprintfW(fwhmLine,L"FWHM-Trigger: aktiv · Grenze %s %% · schlechte Bilder %d/%d · Stabilität %s/%s px",threshold,g_state.autoRefocusBadFrameStreak,g_state.refocusBadFrames,stabilityCurrent,stabilityLimit);
workerLine[0]=0;if(g_state.cameraWorkerBlocked)wsprintfW(workerLine,L"ASCOM-Kamera-Worker blockiert bei „%s“ · wartet auf Freigabe des Treibers",g_state.cameraWorkerOperation[0]?g_state.cameraWorkerOperation:L"unbekannt");if(g_state.focuserWorkerBlocked){wchar_t* t=g_uiScratch.workerTemp;wsprintfW(t,L"%sASCOM-Fokussierer-Worker blockiert bei „%s“ · wartet auf Freigabe des Treibers",workerLine[0]?L"\r\n":L"",g_state.focuserWorkerOperation[0]?g_state.focuserWorkerOperation:L"unbekannt");lstrcatW(workerLine,t);}
if(!g_state.autoRefocus)wsprintfW(autoInfo,L"Status: Auto-Refokus deaktiviert\r\n%s\r\n%s\r\n%s",timeLine,tempLine,fwhmLine);
else if(g_state.autoRefocusPaused)wsprintfW(autoInfo,L"Status: Auto-Refokus pausiert · Benutzerfreigabe erforderlich\r\nRetryfolge 30/60/120/300 s ausgeschöpft.\r\nLetzter Grund: %s\r\n%s\r\n%s\r\n%s%s%s",g_state.autofocusErrorTitle[0]?g_state.autofocusErrorTitle:g_state.autoRefocusLastReason,timeLine,tempLine,fwhmLine,workerLine[0]?L"\r\n":L"",workerLine);
else if(g_state.autoRefocusAutomaticRun)wsprintfW(autoInfo,L"Status: Refokus wird gerade ausgeführt\r\nAuslöser: %s\r\n%s\r\n%s\r\n%s\r\n%s",g_state.autoRefocusLastReason[0]?g_state.autoRefocusLastReason:L"automatische Bedingung",timeLine,tempLine,fwhmLine,g_state.autoRefocusLiveWillResume?L"Livebild wird anschließend fortgesetzt.":L"Livebild war vor dem Lauf nicht aktiv.");
else if(g_state.autoRefocusRetrySeconds>0)wsprintfW(autoInfo,L"Status: Letzter Versuch fehlgeschlagen\r\nErneuter Versuch um %s Uhr (%d s) · Stufe %d/4\r\nGrund: %s\r\n%s\r\n%s\r\n%s",retryClock,g_state.autoRefocusRetrySeconds,g_state.autoRefocusFailureCount,g_state.autofocusErrorTitle[0]?g_state.autofocusErrorTitle:g_state.autoRefocusLastReason,timeLine,tempLine,fwhmLine);
else if(!g_state.autoRefocusTimeEnabled&&!g_state.autoRefocusTemperatureEnabled&&!g_state.autoRefocusFwhmEnabled)wsprintfW(autoInfo,L"Status: Aktiv, aber ohne Auslöser\r\nAktiviere mindestens Zeit-, Temperatur- oder FWHM-Trigger.\r\n%s\r\n%s\r\n%s",timeLine,tempLine,fwhmLine);
else if(!g_state.autoRefocusReferenceReady)wsprintfW(autoInfo,L"Status: Aktiv · wartet auf erste Referenzmessung\r\nBenötigt: analysiertes Bild mit mindestens %d geeigneten Sternen.\r\n%s\r\n%s\r\n%s",g_state.refocusMinStars,timeLine,tempLine,fwhmLine);
else if(!g_state.camera||!g_state.focuser)wsprintfW(autoInfo,L"Status: Aktiv, aber nicht bereit\r\n%s%s\r\n%s\r\n%s\r\n%s%s%s",g_state.camera?L"":L"Kamera nicht verbunden. ",g_state.focuser?L"":L"Fokussierer nicht verbunden.",timeLine,tempLine,fwhmLine,workerLine[0]?L"\r\n":L"",workerLine);
else wsprintfW(autoInfo,L"Status: Aktiv und bereit\r\n%s\r\n%s\r\n%s\r\nMindeststerne: %d · Sperrzeit verbleibend: %s min\r\nLetzter Status: %s%s%s",timeLine,tempLine,fwhmLine,g_state.refocusMinStars,cooldown,g_state.autoRefocusLastReason[0]?g_state.autoRefocusLastReason:L"bereit",workerLine[0]?L"\r\n":L"",workerLine);
{wchar_t smart[1800],si[32],tr[32],fq[32],fc[32];wsprintfW(si,L"%d",g_state.seeingIndex);FormatD(g_state.transparencyIndex,1,tr);FormatD(g_state.fieldQualityScore,1,fq);FormatD(g_state.fieldCurvature,2,fc);wsprintfW(smart,L"DETAILS\r\n\r\n%s\r\n\r\nSeeing: %s (%s/100) · Transparenz %s %%\r\nLetzte AF-Qualität: %d/100 · %s\r\nBildfeld: %s/100 · Krümmung %s px\r\n%s\r\nProfilmodell: %d erfolgreiche Läufe · typische Position %d · Schritt %d · Backlash %d",autoInfo,g_state.seeingState,si,tr,g_state.afQualityScore,g_state.afQualityLabel,fq,fc,g_state.fieldAdvice,g_state.profileSuccessfulRuns,g_state.profileTypicalPosition,g_state.profileRecommendedStep,g_state.profileBacklash);SetText(hAutomationInfo,smart);}EnableWindow(hRefocusResume,g_state.autoRefocus&&g_state.autoRefocusPaused);Check(hTempComp,g_state.tempCompEnabled);Check(hAutoStartPos,g_state.autoStartPositionEnabled);Check(hEvtMeridian,g_state.refocusOnMeridian);Check(hEvtReconnect,g_state.refocusOnReconnect);Check(hEvtFilter,g_state.refocusOnFilter);if(g_uiInitialized){wchar_t cf[64];GetText(hFilterName,cf,64);if(!cf[0]&&g_state.currentFilter[0])SetText(hFilterName,g_state.currentFilter);}
SetFrontendPhase("UI state update: autofocus diagnosis");wchar_t* afDiagnosis=g_uiScratch.afDiagnosis;
if(g_state.backlashCalibrationActive){if(g_state.simulator)wsprintfW(afDiagnosis,L"Backlash-Kalibrierung\r\n%d von %d Schritten geprüft\r\nSimulator: noch %d mechanische Spielschritte",g_state.backlashCalibrationProgress,g_state.backlashCalibrationLimit,g_state.simBacklashRemaining);else wsprintfW(afDiagnosis,L"Backlash-Kalibrierung\r\n%d von %d Schritten geprüft",g_state.backlashCalibrationProgress,g_state.backlashCalibrationLimit);}
else if(g_state.autofocus)wsprintfW(afDiagnosis,L"Autofokusdiagnose\r\n%s\r\n%s",g_state.afValidationState[0]?g_state.afValidationState:L"Fokuslauf aktiv",g_state.afValidationReason[0]?g_state.afValidationReason:L"Messpunkte, Fit und Kontrollaufnahme werden fortlaufend geprüft.");
else if(g_state.autofocusErrorCode[0]&&!WEqual(g_state.autofocusErrorCode,L"NONE"))wsprintfW(afDiagnosis,L"Letzte Autofokusdiagnose\r\n%s%s%s\r\nCode: %s%s%s\r\nValidierung: %s%s%s",g_state.autofocusErrorTitle[0]?g_state.autofocusErrorTitle:L"Autofokus fehlgeschlagen",g_state.autofocusErrorAutomatic?L" (automatischer Lauf)":L"",g_state.autofocusErrorDetail[0]?L"\r\n":L"",g_state.autofocusErrorCode,g_state.autofocusErrorDetail[0]?L"\r\nDetails: ":L"",g_state.autofocusErrorDetail,g_state.afValidationState[0]?g_state.afValidationState:L"–",g_state.afValidationReason[0]?L"\r\n":L"",g_state.afValidationReason);
else wsprintfW(afDiagnosis,L"Autofokusdiagnose\r\nValidierung: %s\r\n%s",g_state.afValidationState[0]?g_state.afValidationState:L"Noch kein Fokuslauf validiert",g_state.afValidationReason[0]?g_state.afValidationReason:L"Bei einem erfolgreichen Lauf bestätigt eine Abschluss-Kontrollmessung die Bestposition.");
SetText(hAfDiagnosis,afDiagnosis);EnableWindow(hAfUseSelected,g_state.manualStarLocked&&!focusBusy);EnableWindow(hAfClearSelected,g_state.manualStarLocked&&!focusBusy);SetFrontendPhase("UI state update: profile controls");if(syncProfileControls){SetText(hProfile,g_state.profile);SetText(hExposure,g_state.exposure);SetText(hGain,g_state.gain);SetText(hManualStep,g_state.manualStep);SetAfPointComboFromText(g_state.afPointsText);SetText(hAfStep,g_state.afStepText);SetAfSampleComboFromText(g_state.afSamplesText);SetText(hBacklash,g_state.backlashText);SetText(hRefocusMin,g_state.refocusMinText);SetText(hRefocusTemp,g_state.refocusTempText);FormatD(g_state.refocusFwhmPercent,1,w);SetText(hRefocusFwhm,w);wsprintfW(w,L"%d",g_state.refocusBadFrames);SetText(hRefocusBadFrames,w);wsprintfW(w,L"%d",g_state.refocusMinStars);SetText(hRefocusMinStars,w);FormatD(g_state.refocusStability,2,w);SetText(hRefocusStability,w);FormatD(g_state.refocusCooldown,1,w);SetText(hRefocusCooldown,w);wsprintfW(w,L"%d",g_state.refocusEveryCaptures);SetText(hRefocusCaptures,w);SetText(hFilterName,g_state.currentFilter);Check(hTempComp,g_state.tempCompEnabled);Check(hAutoStartPos,g_state.autoStartPositionEnabled);Check(hEvtMeridian,g_state.refocusOnMeridian);Check(hEvtReconnect,g_state.refocusOnReconnect);Check(hEvtFilter,g_state.refocusOnFilter);wsprintfW(w,L"%d",g_state.safeMin);SetText(hSafeMin,w);wsprintfW(w,L"%d",g_state.safeMax);SetText(hSafeMax,w);ComboSelect(hSimProfile,ClampI(g_state.simProfileMode,0,8));wsprintfW(w,L"%d",g_state.simBacklashSteps);SetText(hSimBacklash,w);ComboSelect(hCfMode,g_state.continuousFocusMode);wsprintfW(w,L"%d",g_state.continuousFocusMinFrames);SetText(hCfMinFrames,w);wsprintfW(w,L"%d",g_state.continuousFocusDeadband);SetText(hCfDeadband,w);wsprintfW(w,L"%d",g_state.continuousFocusMaxStep);SetText(hCfMaxStep,w);wsprintfW(w,L"%d",g_state.continuousFocusMinConfidence);SetText(hCfConfidence,w);FormatD(g_state.continuousFocusMinImprovement,1,w);SetText(hCfImprovement,w);wsprintfW(w,L"%d",g_state.continuousFocusSettleMs);SetText(hCfSettle,w);}else if(syncCalibratedBacklash){SetText(hBacklash,g_state.backlashText);LogLine(g_state.backlashCalibrationResult[0]?g_state.backlashCalibrationResult:L"Ermittelter Backlash wurde in die Autofokus-Einstellungen übernommen.");}if(!g_uiInitialized){if(g_state.simulator){g_cameraBackendSelection=0;g_focuserBackendSelection=0;}else{g_cameraBackendSelection=g_state.external?1:(g_state.native?2:3);g_focuserBackendSelection=1;g_lastNonSimulatorCameraBackend=g_cameraBackendSelection;}ComboSelect(hCamBackend,g_cameraBackendSelection);ComboSelect(hFocBackend,g_focuserBackendSelection);g_uiInitialized=TRUE;}if(focusLampTextChanged&&g_activeTab==4&&g_focusLamp.right>g_focusLamp.left){int lampW=g_focusLamp.right-g_focusLamp.left;int pageContentH=g_page.bottom-g_page.top-36;const int focusLampMinH=148,detailsMinH=48;int focusLampMaxH=pageContentH-(12+32+10+detailsMinH+8);if(focusLampMaxH<focusLampMinH)focusLampMaxH=focusLampMinH;int targetFocusLampH=MeasureFocusLampHeight(lampW,focusLampMaxH);if(targetFocusLampH!=g_focusLamp.bottom-g_focusLamp.top&&g_layoutClientWidth>0&&g_layoutClientHeight>0)Layout(g_layoutClientWidth,g_layoutClientHeight);}SetFrontendPhase("UI state update: final controls");UpdateAutofocusInputState();if(g_state.selfTotal){wsprintfW(w,L"%d von %d Tests bestanden",g_state.selfPassed,g_state.selfTotal);SetText(hTestResult,w);SetText(hTestInfo,g_state.selfTestSummary);}if(!g_state.frameReady&&g_frame){ClearFrame();g_frameFetchFailures=0;}RECT header={0,0,32767,64};if(!old)InvalidateRect(g_main,&header,FALSE);if(!old||old->camera!=g_state.camera)InvalidateRect(g_main,&g_leftCamera,FALSE);if(!old||old->focuser!=g_state.focuser)InvalidateRect(g_main,&g_leftFocuser,FALSE);if(PreviewStateChanged(old))InvalidateRect(g_main,&g_preview,FALSE);if(MetricsStateChanged(old)||trendChanged){InvalidateRect(g_main,&g_page,FALSE);InvalidateRect(g_main,&g_rightAnalysis,FALSE);InvalidateRect(g_main,&g_rightStar,FALSE);InvalidateRect(g_main,&g_rightTrend,FALSE);InvalidateRect(g_main,&g_rightField,FALSE);}if(g_activeTab==5&&(cfHistoryChanged||!old||old->continuousFocusPhase!=g_state.continuousFocusPhase||old->continuousFocusTarget!=g_state.continuousFocusTarget))InvalidateRect(g_main,&g_page,FALSE);if(g_activeTab==6)InvalidateRect(g_main,&g_page,FALSE);}
static AFS_NOINLINE BOOL PollStatus(){
    if(g_pollBusy)return g_engineOnline;g_pollBusy=TRUE;SetFrontendPhase("status HTTP request");BYTE* b=0;DWORD n=0;BOOL result=FALSE;
    if(!HttpGet("/api/status",&b,&n,262144)){g_engineOnline=FALSE;if(hStatus)SetText(hStatus,L"Engine nicht erreichbar – RuntimeTrace.log und SimulatorStage.txt im Programmordner prüfen");g_pollBusy=FALSE;return FALSE;}
    const char* json=(const char*)b;BOOL sane=n>=2&&json[0]=='{'&&json[n-1]=='}'&&strstr(json,"\"version\":")&&strstr(json,"\"frameSequence\":");
    if(!sane){Free(b);g_engineOnline=FALSE;if(hStatus)SetText(hStatus,L"Ungültige Statusantwort der Engine verworfen");g_pollBusy=FALSE;return FALSE;}
    memcpy(&g_previousState,&g_state,sizeof(AppState));SetFrontendPhase("status parse");ParseStatus(json);Free(b);
    if(!WEqual(g_state.version,AFS_VERSION_TEXT_W)){g_engineOnline=FALSE;if(hStatus)SetText(hStatus,L"Nicht passende Engine-Version erkannt. Programm vollständig schließen und neu starten.");g_pollBusy=FALSE;return FALSE;}
    g_engineOnline=TRUE;SetFrontendPhase("UI state update");UpdateUiFromState(&g_previousState);result=TRUE;g_pollBusy=FALSE;SetFrontendPhase("idle");return result;
}
static UINT GetLe16(const BYTE* p){return (UINT)p[0]|((UINT)p[1]<<8);}
static UINT GetLe32(const BYTE* p){return (UINT)p[0]|((UINT)p[1]<<8)|((UINT)p[2]<<16)|((UINT)p[3]<<24);}
static BOOL InstallBmpFrame(BYTE* b,DWORD n){
    if(!b||n<54||b[0]!='B'||b[1]!='M'){Free(b);return FALSE;}
    UINT declared=GetLe32(b+2);
    UINT off=GetLe32(b+10);
    BITMAPINFOHEADER ih;memset(&ih,0,sizeof(ih));ih.biSize=GetLe32(b+14);ih.biWidth=(int)GetLe32(b+18);ih.biHeight=(int)GetLe32(b+22);ih.biPlanes=(WORD)GetLe16(b+26);ih.biBitCount=(WORD)GetLe16(b+28);ih.biCompression=GetLe32(b+30);ih.biSizeImage=GetLe32(b+34);
    if(ih.biSize<40||ih.biPlanes!=1||ih.biCompression!=BI_RGB){Free(b);return FALSE;}
    int w=(int)ih.biWidth;
    int signedH=(int)ih.biHeight;if(signedH==(int)0x80000000U){Free(b);return FALSE;}int h=signedH<0?-signedH:signedH;
    int bytesPerPixel=ih.biBitCount/8;
    if(off<54||off>=n||w<=0||h<=0||w>10000||h>10000||(ih.biBitCount!=24&&ih.biBitCount!=32)){Free(b);return FALSE;}
    unsigned long long stride=((unsigned long long)(UINT)w*(unsigned long long)(UINT)bytesPerPixel+3ULL)&~3ULL;
    unsigned long long required=(unsigned long long)off+stride*(unsigned long long)(UINT)h;
    if(required>(unsigned long long)n||(declared&&declared>(UINT)n)){Free(b);return FALSE;}
    Free(g_frame);g_frame=b;g_frameSize=n;memset(&g_frameInfo,0,sizeof(g_frameInfo));g_frameInfo.bmiHeader=ih;g_framePixels=b+off;g_frameW=w;g_frameH=h;g_frameBpp=ih.biBitCount;g_frameOff=off;g_frameFetchFailures=0;
    InvalidateRect(g_main,&g_preview,FALSE);return TRUE;
}
static BOOL LoadFrame(){BYTE* b=0;DWORD n=0;if(!HttpGet("/frame.bmp",&b,&n,128*1024*1024)){g_frameFetchFailures++;InvalidateRect(g_main,&g_preview,FALSE);return FALSE;}if(!InstallBmpFrame(b,n)){g_frameFetchFailures++;InvalidateRect(g_main,&g_preview,FALSE);return FALSE;}g_lastLoadedFrameSequence=g_state.frameSequence;return TRUE;}
static void MaybeLoadFrame(){if(!g_engineOnline||!g_state.frameReady)return;if(g_frame&&g_lastLoadedFrameSequence==g_state.frameSequence)return;LoadFrame();}

static BOOL FileExists(LPCWSTR p){DWORD a=GetFileAttributesW(p);return a!=INVALID_FILE_ATTRIBUTES;} static BOOL FindFfmpeg(wchar_t* out){wchar_t p[700];BuildPath(L"ffmpeg.exe",p);if(FileExists(p)){lstrcpyW(out,p);return TRUE;}BuildPath(L"tools\\ffmpeg.exe",p);if(FileExists(p)){lstrcpyW(out,p);return TRUE;}lstrcpyW(out,L"ffmpeg.exe");return TRUE;}
static BOOL IsSafeChooserArgument(LPCWSTR value){if(!value)return FALSE;for(int i=0;value[i];i++)if(value[i]==L'"'||value[i]==L'\r'||value[i]==L'\n')return FALSE;return TRUE;}
static BOOL LooksLikeAscomProgId(LPCWSTR value){if(!value||!value[0])return FALSE;BOOL dot=FALSE;int n=0;for(;value[n];n++){wchar_t c=value[n];if(n>=255||c<=L' '||c==L'\\'||c==L'/'||c==L'"'||c==L'?'||c==L'#'||c==L'&')return FALSE;if(c==L'.')dot=TRUE;}return n>=3&&dot;}
static BOOL BuildAscomChooserResultPath(BOOL camera,LPWSTR out,int cap){
    if(!out||cap<80)return FALSE;wchar_t temp[520];DWORD n=GetTempPathW(520,temp);if(n==0||n>=519)return FALSE;DWORD pid=GetCurrentProcessId();DWORD tick=(DWORD)GetTickCount64();int written=wsprintfW(out,L"%sAstroFocusAscomChooser_%u_%u_%s.txt",temp,pid,tick,camera?L"Camera":L"Focuser");return written>0&&written<cap;
}
static BOOL CopyValidatedAscomProgId(const wchar_t* text,int chars,LPWSTR out,int cap){
    if(!text||!out||cap<2||chars<=0||chars>=cap)return FALSE;out[0]=0;
    for(int i=0;i<chars;i++){wchar_t c=text[i];if(c==0||c==L'\r'||c==L'\n'||c==L'\t'||c<L' '){out[0]=0;return FALSE;}out[i]=c;}
    out[chars]=0;if(!LooksLikeAscomProgId(out)){out[0]=0;return FALSE;}return TRUE;
}
static BOOL ReadAscomChooserResult(LPCWSTR path,LPWSTR out,int cap){
    if(!path||!out||cap<2)return FALSE;out[0]=0;HANDLE f=CreateFileW(path,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return FALSE;
    DWORD size=GetFileSize(f,0);if(size<4||(size&1)||size>(DWORD)(cap*sizeof(wchar_t))){CloseHandle(f);return FALSE;}BYTE* bytes=(BYTE*)Alloc((SIZE_T)size);if(!bytes){CloseHandle(f);return FALSE;}
    DWORD read=0;BOOL ok=ReadFile(f,bytes,size,&read,0)&&read==size;CloseHandle(f);if(!ok){Free(bytes);return FALSE;}
    wchar_t* text=(wchar_t*)bytes;int units=(int)(size/sizeof(wchar_t));BOOL valid=units>1&&text[0]==0xFEFF&&CopyValidatedAscomProgId(text+1,units-1,out,cap);Free(bytes);return valid;
}
static void SetAscomChooserButtons(BOOL active){
    EnableWindow(hCamBackend,!active);EnableWindow(hFocBackend,!active);EnableWindow(hCamSelect,!active);EnableWindow(hFocSelect,!active);EnableWindow(hCamConnect,!active);EnableWindow(hFocConnect,!active);EnableWindow(hFocSetup,!active);
    if(!active)ApplyBackendSelectors();
}
static BOOL StartAscomChooser(BOOL camera){
    if(g_ascomChooserProcess){MessageBoxW(g_main,L"Ein ASCOM-Auswahldialog ist bereits geöffnet.",L"ASCOM-Auswahl",MB_OK|MB_ICONINFORMATION);return TRUE;}
    if(!g_engineOnline){MessageBoxW(g_main,L"Die AstroFocus-Engine ist nicht erreichbar. Die ASCOM-Auswahl kann deshalb nicht übernommen werden.",L"Engine nicht erreichbar",MB_OK|MB_ICONERROR);return FALSE;}
    wchar_t exe[700];BuildPath(L"AstroFocusFocuserSetup.exe",exe);if(!FileExists(exe)){MessageBoxW(g_main,L"AstroFocusFocuserSetup.exe fehlt im Programmordner.",L"ASCOM-Auswahl nicht verfügbar",MB_OK|MB_ICONERROR);return FALSE;}
    wchar_t result[700];if(!BuildAscomChooserResultPath(camera,result,700)){MessageBoxW(g_main,L"Für die ASCOM-Auswahl konnte keine sichere temporäre Ergebnisdatei angelegt werden.",L"ASCOM-Auswahl nicht verfügbar",MB_OK|MB_ICONERROR);return FALSE;}DeleteFileW(result);
    LPCWSTR initial=camera?g_state.cameraName:g_state.focuserName;if(!IsSafeChooserArgument(initial)||!LooksLikeAscomProgId(initial))initial=L"";
    wchar_t cmd[1900];int n=wsprintfW(cmd,L"\"%s\" --choose --device \"%s\" --result \"%s\" --initial \"%s\"",exe,camera?L"Camera":L"Focuser",result,initial);if(n<=0||n>=(int)(sizeof(cmd)/sizeof(cmd[0]))-1)return FALSE;
    STARTUPINFOW si;PROCESS_INFORMATION pi;memset(&si,0,sizeof(si));memset(&pi,0,sizeof(pi));si.cb=sizeof(si);si.dwFlags=STARTF_USESHOWWINDOW;si.wShowWindow=SW_SHOW;
    if(!CreateProcessW(exe,cmd,0,0,FALSE,CREATE_NEW_PROCESS_GROUP,0,g_appDir,&si,&pi)){MessageBoxW(g_main,L"Der sichtbare ASCOM-Auswahlhelfer konnte nicht gestartet werden.",L"ASCOM-Auswahl fehlgeschlagen",MB_OK|MB_ICONERROR);return FALSE;}
    CloseHandle(pi.hThread);g_ascomChooserProcess=pi.hProcess;g_ascomChooserCamera=camera;g_ascomChooserExpectedBackend=camera?ComboSel(hCamBackend):ComboSel(hFocBackend);lstrcpyW(g_ascomChooserResultPath,result);SetAscomChooserButtons(TRUE);SetText(hStatus,camera?L"ASCOM-Kameraauswahl geöffnet …":L"ASCOM-Fokussiererauswahl geöffnet …");AppendFrontendTrace(camera?"ASCOM camera chooser started":"ASCOM focuser chooser started");return TRUE;
}
static BOOL AscomChooserBackendStillValid(BOOL camera,int expectedBackend){int requiredBackend=camera?3:1;int currentBackend=camera?ComboSel(hCamBackend):ComboSel(hFocBackend);return expectedBackend==requiredBackend&&currentBackend==requiredBackend;}
static void FinishAscomChooser(){
    if(!g_ascomChooserProcess)return;DWORD code=0xffffffffUL;(void)GetExitCodeProcess(g_ascomChooserProcess,&code);CloseHandle(g_ascomChooserProcess);g_ascomChooserProcess=0;
    wchar_t selected[512];selected[0]=0;BOOL camera=g_ascomChooserCamera;int expectedBackend=g_ascomChooserExpectedBackend;g_ascomChooserCamera=FALSE;g_ascomChooserExpectedBackend=-1;BOOL readOk=code==0&&ReadAscomChooserResult(g_ascomChooserResultPath,selected,512);DeleteFileW(g_ascomChooserResultPath);g_ascomChooserResultPath[0]=0;SetAscomChooserButtons(FALSE);PollStatus();
    if(code==10){SetText(hStatus,L"ASCOM-Auswahl abgebrochen");AppendFrontendTrace("ASCOM chooser cancelled");return;}
    if(!readOk){if(code==0)MessageBoxW(g_main,L"Der ASCOM-Auswahlhelfer hat keine gültige Treiber-ID zurückgegeben.",L"ASCOM-Auswahl fehlgeschlagen",MB_OK|MB_ICONERROR);AppendFrontendTrace("ASCOM chooser failed");return;}
    if(!AscomChooserBackendStillValid(camera,expectedBackend)){SetText(hStatus,L"ASCOM-Auswahl verworfen · Backend wurde zwischenzeitlich geändert");AppendFrontendTrace("ASCOM chooser result discarded after backend change");return;}
    BOOL accepted=ApiSetW(camera?"cameraId":"focuserId",selected);if(!accepted){MessageBoxW(g_main,g_lastApiMessage[0]?g_lastApiMessage:L"Die ausgewählte ASCOM-Treiber-ID konnte nicht von der Engine übernommen werden. Trenne ein eventuell noch verbundenes Gerät und wiederhole die Auswahl.",L"ASCOM-Auswahl nicht übernommen",MB_OK|MB_ICONERROR);return;}
    PollStatus();LogLine(camera?L"ASCOM-Kameratreiber ausgewählt.":L"ASCOM-Fokussierertreiber ausgewählt.");SetText(hStatus,camera?L"ASCOM-Kamera ausgewählt · jetzt verbinden":L"ASCOM-Fokussierer ausgewählt · jetzt verbinden");AppendFrontendTrace(camera?"ASCOM camera chooser complete":"ASCOM focuser chooser complete");
}
static void PollAscomChooserProcess(){if(g_ascomChooserProcess&&WaitForSingleObject(g_ascomChooserProcess,0)==WAIT_OBJECT_0)FinishAscomChooser();}
static int ClassifyFocuserSetupExitCode(DWORD code){return code==0?0:(code==10?1:2);}
static BOOL ReleaseFocuserSetupEngineReservation(){
    BOOL releaseAccepted=ApiAction("focuser-setup-end");g_focuserSetupEngineLock=FALSE;BOOL statusOk=PollStatus();return releaseAccepted||(statusOk&&!g_state.focuserSetupActive);
}
static void FinishFocuserSetup(){
    DWORD code=0xffffffffUL;if(g_focuserSetupProcess){(void)GetExitCodeProcess(g_focuserSetupProcess,&code);CloseHandle(g_focuserSetupProcess);g_focuserSetupProcess=0;}
    int outcome=ClassifyFocuserSetupExitCode(code);
    if(outcome==0)LogLine(L"ASCOM-Treiberdialog geschlossen. AstroFocus kann nicht feststellen, ob die Kalibrierung im Celestron-Treiber gestartet oder erfolgreich abgeschlossen wurde.");
    else if(outcome==1)LogLine(L"ASCOM-Treiberdialog ohne Auswahl abgebrochen.");
    else {wchar_t detail[320];wsprintfW(detail,L"Der ASCOM-Kalibrierungshelfer wurde mit Fehlercode %u beendet. Prüfe ASCOM Platform, Treiberinstallation und Diagnoseprotokoll.",(UINT)code);LogLine(detail);MessageBoxW(g_main,detail,L"ASCOM-Treiberdialog fehlgeschlagen",MB_OK|MB_ICONERROR);}
    BOOL reconnect=g_focuserSetupReconnect;g_focuserSetupReconnect=FALSE;BOOL released=ReleaseFocuserSetupEngineReservation();
    if(!released){reconnect=FALSE;LogLine(L"Die Engine-Sperre des ASCOM-Treiberdialogs konnte nicht bestätigt aufgehoben werden. Eine automatische Wiederverbindung wurde aus Sicherheitsgründen verhindert.");MessageBoxW(g_main,L"Die Sicherheitssperre des ASCOM-Treiberdialogs konnte nicht zuverlässig aufgehoben werden. Der Fokussierer wird nicht automatisch verbunden. Starte AstroFocus Studio neu, bevor du den Motor bewegst.",L"Fokussierer bleibt gesperrt",MB_OK|MB_ICONERROR);}
    if(reconnect&&!g_state.focuser){if(ApiAction("focuser-connect")){for(int i=0;i<12&&!g_state.focuser;i++){Sleep(100);PollStatus();}}if(!g_state.focuser)MessageBoxW(g_main,L"Der Fokussierer konnte nach dem Treiberdialog nicht automatisch wieder verbunden werden. Bitte Verbindung und USB-Kabel prüfen.",L"Fokussierer erneut verbinden",MB_OK|MB_ICONWARNING);}
    PollStatus();
}
static void PollFocuserSetupProcess(){if(g_focuserSetupProcess&&WaitForSingleObject(g_focuserSetupProcess,0)==WAIT_OBJECT_0)FinishFocuserSetup();}
static void BeginFocuserSetup(){
    if(g_focuserSetupProcess||g_focuserSetupEngineLock||g_state.focuserSetupActive){MessageBoxW(g_main,L"Der ASCOM-Treiberdialog ist bereits geöffnet oder von der Engine reserviert.",L"Fokussierer-Kalibrierung",MB_OK|MB_ICONINFORMATION);return;}
    PollStatus();
    if(ComboSel(hFocBackend)!=1||g_state.simulator){MessageBoxW(g_main,L"Die Kalibrierung ist nur für einen ausgewählten ASCOM-Fokussierer verfügbar.",L"ASCOM-Fokussierer erforderlich",MB_OK|MB_ICONINFORMATION);return;}
    if(!g_state.focuserName[0]){MessageBoxW(g_main,L"Bitte zuerst über „ASCOM auswählen“ den Celestron USB Focuser auswählen.",L"Kein Fokussierertreiber",MB_OK|MB_ICONINFORMATION);return;}
    if(FocuserOperationBusy()){MessageBoxW(g_main,L"Beende zuerst Autofokus, Schritt-Assistent, Backlash-Kalibrierung oder eine noch laufende Motorbewegung. Während einer Treiberkalibrierung darf keine andere Fokusbewegung aktiv sein.",L"Kalibrierung nicht möglich",MB_OK|MB_ICONWARNING);return;}
    int answer=MessageBoxW(g_main,L"Der ASCOM-Treiberdialog wird geöffnet. Beim Celestron Focus Motor kann dort die Kalibrierung gestartet werden.\r\n\r\nDer Motor fährt dabei beide mechanischen Endlagen an. Sorge für freie Bewegung, sichere Kabel und ausreichend Abstand zu Anschlägen. Der Vorgang dauert typischerweise mehrere Minuten und darf nicht unterbrochen werden.\r\n\r\nJetzt fortfahren?",L"Celestron Focus Motor kalibrieren",MB_YESNO|MB_ICONWARNING);if(answer!=IDYES)return;
    g_focuserSetupReconnect=g_state.focuser;
    if(g_state.focuser){if(!ApiAction("focuser-connect")){g_focuserSetupReconnect=FALSE;MessageBoxW(g_main,L"Der Fokussierer konnte vor der Kalibrierung nicht sauber getrennt werden.",L"Kalibrierung abgebrochen",MB_OK|MB_ICONERROR);return;}for(int i=0;i<12&&g_state.focuser;i++){Sleep(100);PollStatus();}if(g_state.focuser){g_focuserSetupReconnect=FALSE;MessageBoxW(g_main,L"Der Fokussierer meldet sich weiterhin als verbunden. Die Kalibrierung wurde aus Sicherheitsgründen nicht gestartet.",L"Kalibrierung abgebrochen",MB_OK|MB_ICONERROR);return;}}
    if(!LooksLikeAscomProgId(g_state.focuserName)){if(g_focuserSetupReconnect)ApiAction("focuser-connect");g_focuserSetupReconnect=FALSE;MessageBoxW(g_main,L"Die ausgewählte Fokussierer-ID ist keine gültige ASCOM-ProgID.",L"Kalibrierung nicht gestartet",MB_OK|MB_ICONERROR);return;}
    wchar_t exe[700],cmd[1400];BuildPath(L"AstroFocusFocuserSetup.exe",exe);if(!FileExists(exe)){if(g_focuserSetupReconnect)ApiAction("focuser-connect");g_focuserSetupReconnect=FALSE;MessageBoxW(g_main,L"AstroFocusFocuserSetup.exe fehlt im Programmordner.",L"Kalibrierung nicht verfügbar",MB_OK|MB_ICONERROR);return;}
    PollStatus();if(g_state.focuser||FocuserOperationBusy()||!ApiAction("focuser-setup-begin")){if(g_focuserSetupReconnect)ApiAction("focuser-connect");g_focuserSetupReconnect=FALSE;MessageBoxW(g_main,g_lastApiMessage[0]?g_lastApiMessage:L"Die Engine konnte den sicheren Setup-Zustand nicht atomar reservieren.",L"Kalibrierung nicht gestartet",MB_OK|MB_ICONERROR);return;}g_focuserSetupEngineLock=TRUE;
    wsprintfW(cmd,L"\"%s\" --driver \"%s\"",exe,g_state.focuserName);STARTUPINFOW si;PROCESS_INFORMATION pi;memset(&si,0,sizeof(si));memset(&pi,0,sizeof(pi));si.cb=sizeof(si);si.dwFlags=STARTF_USESHOWWINDOW;si.wShowWindow=SW_SHOW;
    if(!CreateProcessW(exe,cmd,0,0,FALSE,CREATE_NEW_PROCESS_GROUP,0,g_appDir,&si,&pi)){BOOL reconnect=g_focuserSetupReconnect;g_focuserSetupReconnect=FALSE;BOOL released=ReleaseFocuserSetupEngineReservation();if(reconnect&&released)ApiAction("focuser-connect");if(!released)MessageBoxW(g_main,L"Der Kalibrierungshelfer konnte nicht gestartet und die Engine-Sperre nicht zuverlässig aufgehoben werden. Starte AstroFocus Studio neu, bevor du den Fokussierer bewegst.",L"Fokussierer bleibt gesperrt",MB_OK|MB_ICONERROR);else MessageBoxW(g_main,L"Der ASCOM-Kalibrierungshelfer konnte nicht gestartet werden.",L"Kalibrierung nicht gestartet",MB_OK|MB_ICONERROR);return;}
    CloseHandle(pi.hThread);g_focuserSetupProcess=pi.hProcess;LogLine(L"ASCOM-Treiberdialog für Fokussierer geöffnet. Die Engine hat Fokusbewegungen bis zum Schließen des Dialogs gesperrt.");PollStatus();
}
static BOOL IsSafeUvcDeviceName(LPCWSTR name){if(!name||!name[0])return FALSE;for(int i=0;name[i];i++)if(name[i]==L'"'||name[i]==L'\r'||name[i]==L'\n')return FALSE;return TRUE;}
static BOOL StopUvc(){if(g_uvcProcess){TerminateProcess(g_uvcProcess,0);WaitForSingleObject(g_uvcProcess,2000);CloseHandle(g_uvcProcess);g_uvcProcess=0;}return !g_engineOnline||ApiAction("external-off");}
static void PollUvcProcess(){
    if(!g_uvcProcess||WaitForSingleObject(g_uvcProcess,0)!=WAIT_OBJECT_0)return;
    CloseHandle(g_uvcProcess);g_uvcProcess=0;AppendFrontendTrace("USB/UVC capture process exited");
    BOOL detached=!g_engineOnline||ApiAction("external-off");
    SetText(hStatus,detached?L"USB/UVC-Aufnahmeprozess wurde beendet · Kamera getrennt":L"USB/UVC-Aufnahmeprozess beendet · Engine konnte nicht getrennt werden");
    g_statusRefreshRequested=TRUE;
}
static BOOL LaunchHidden(LPCWSTR app,LPWSTR cmd,HANDLE stdErr,HANDLE* processOut){STARTUPINFOW si;PROCESS_INFORMATION pi;memset(&si,0,sizeof(si));memset(&pi,0,sizeof(pi));si.cb=sizeof(si);si.dwFlags=STARTF_USESHOWWINDOW;if(stdErr){si.dwFlags|=STARTF_USESTDHANDLES;si.hStdError=stdErr;si.hStdOutput=stdErr;}si.wShowWindow=SW_HIDE_CONST;BOOL ok=CreateProcessW(app,cmd,0,0,stdErr?TRUE:FALSE,CREATE_NO_WINDOW|CREATE_NEW_PROCESS_GROUP,0,g_appDir,&si,&pi);if(!ok)return FALSE;CloseHandle(pi.hThread);if(processOut)*processOut=pi.hProcess;else CloseHandle(pi.hProcess);return TRUE;}
static int EnumerateUvc(){wchar_t ff[700],logPath[700],cmd[1800];FindFfmpeg(ff);BuildPath(L"UvcDevices.txt",logPath);SECURITY_ATTRIBUTES sa;sa.nLength=sizeof(sa);sa.lpSecurityDescriptor=0;sa.bInheritHandle=TRUE;HANDLE f=CreateFileW(logPath,GENERIC_WRITE,FILE_SHARE_READ,&sa,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return 0;wsprintfW(cmd,L"\"%s\" -hide_banner -list_devices true -f dshow -i dummy",ff);HANDLE p=0;BOOL ok=LaunchHidden(0,cmd,f,&p);CloseHandle(f);if(!ok)return 0;WaitForSingleObject(p,8000);TerminateProcess(p,0);CloseHandle(p);HANDLE rf=CreateFileW(logPath,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(rf==INVALID_HANDLE_VALUE)return 0;DWORD sz=GetFileSize(rf,0);if(sz==0||sz>1024*1024){CloseHandle(rf);return 0;}char* data=(char*)Alloc((SIZE_T)sz+1);if(!data){CloseHandle(rf);return 0;}DWORD rd=0;if(!ReadFile(rf,data,sz,&rd,0)||rd>sz){CloseHandle(rf);Free(data);return 0;}CloseHandle(rf);data[rd]=0;SendMessageW(hCamDevice,CB_RESETCONTENT,0,0);int count=0;char* line=data;while(line&&*line){char* next=strchr(line,'\n');if(next)*next=0;if(strstr(line,"(video)")&&!strstr(line,"Alternative name")){char* q1=strchr(line,'\"');if(q1){char* q2=strchr(q1+1,'\"');if(q2&&q2>q1+1){char save=*q2;*q2=0;wchar_t w[512];AToW(q1+1,w,512);ComboAdd(hCamDevice,w);count++;*q2=save;}}}line=next?next+1:0;}Free(data);if(count)ComboSelect(hCamDevice,0);return count;}
static BOOL ShowUvcProperties(){wchar_t dev[512];GetText(hCamDevice,dev,512);if(!dev[0]){MessageBoxW(g_main,L"Bitte zuerst eine USB-/UVC-Kamera aus der Geräteliste auswählen.",L"USB-Kamera",MB_OK|MB_ICONINFORMATION);return FALSE;}if(!IsSafeUvcDeviceName(dev)){MessageBoxW(g_main,L"Der DirectShow-Gerätename enthält unzulässige Anführungszeichen oder Zeilenumbrüche. Bitte die Kamera neu aus der Geräteliste auswählen.",L"Ungültiger Gerätename",MB_OK|MB_ICONWARNING);return FALSE;}wchar_t ff[700],cmd[2200];FindFfmpeg(ff);wsprintfW(cmd,L"\"%s\" -hide_banner -loglevel error -f dshow -show_video_device_dialog true -i video=\"%s\" -t 0.1 -f null NUL",ff,dev);HANDLE pr=0;if(!LaunchHidden(0,cmd,0,&pr)){MessageBoxW(g_main,L"Der DirectShow-Gerätedialog konnte nicht geöffnet werden. Prüfe, ob FFmpeg installiert ist.",L"USB-Kamera",MB_OK|MB_ICONERROR);return FALSE;}CloseHandle(pr);return TRUE;}
static BOOL StartUvc(){if(!StopUvc())return FALSE;wchar_t dev[512];GetText(hCamDevice,dev,512);if(!dev[0]){MessageBoxW(g_main,L"Bitte eine USB-/UVC-Kamera auswählen oder den DirectShow-Gerätenamen eingeben.",L"Keine Kamera",MB_OK|MB_ICONINFORMATION);return FALSE;}if(!IsSafeUvcDeviceName(dev)){MessageBoxW(g_main,L"Der DirectShow-Gerätename enthält unzulässige Anführungszeichen oder Zeilenumbrüche. Bitte die Kamera neu aus der Geräteliste auswählen.",L"Ungültiger Gerätename",MB_OK|MB_ICONWARNING);return FALSE;}wchar_t ff[700],frame[700],log[700],cmd[2600];FindFfmpeg(ff);BuildPath(L"UsbCameraFrame.bmp",frame);BuildPath(L"UsbCameraCapture.log",log);DeleteFileW(frame);SECURITY_ATTRIBUTES sa;sa.nLength=sizeof(sa);sa.lpSecurityDescriptor=0;sa.bInheritHandle=TRUE;HANDLE lf=CreateFileW(log,GENERIC_WRITE,FILE_SHARE_READ,&sa,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);if(lf==INVALID_HANDLE_VALUE)return FALSE;wsprintfW(cmd,L"\"%s\" -hide_banner -loglevel warning -f dshow -rtbufsize 512M -i video=\"%s\" -vf fps=5 -pix_fmt bgra -f image2 -update 1 -y \"%s\"",ff,dev,frame);BOOL ok=LaunchHidden(0,cmd,lf,&g_uvcProcess);CloseHandle(lf);if(!ok){MessageBoxW(g_main,L"FFmpeg konnte nicht gestartet werden. Lege ffmpeg.exe neben das Programm oder in den Ordner tools.",L"USB-Kamera",MB_OK|MB_ICONERROR);return FALSE;}for(int i=0;i<40&&!FileExists(frame);i++)Sleep(100);if(!FileExists(frame)){StopUvc();MessageBoxW(g_main,L"Die USB-Kamera lieferte kein Bild. Prüfe den DirectShow-Gerätenamen und UsbCameraCapture.log.",L"USB-Kamera",MB_OK|MB_ICONERROR);return FALSE;}if(!ApiSetW("externalName",dev)||!ApiAction("external-on")){if(g_uvcProcess){TerminateProcess(g_uvcProcess,0);WaitForSingleObject(g_uvcProcess,2000);CloseHandle(g_uvcProcess);g_uvcProcess=0;}MessageBoxW(g_main,L"FFmpeg liefert Bilder, aber die Engine hat die USB/UVC-Quelle nicht übernommen.",L"USB-Kamera",MB_OK|MB_ICONERROR);return FALSE;}return TRUE;}
static BOOL StartEngine(){AppendFrontendTrace("engine startup begin");wchar_t exe[700],cmd[900];BuildPath(L"AstroFocusEngine.exe",exe);if(!FileExists(exe)){MessageBoxW(g_main,L"AstroFocusEngine.exe fehlt im Programmordner.",L"Startfehler",MB_OK|MB_ICONERROR);AppendFrontendTrace("engine executable missing");return FALSE;}BYTE* existing=0;DWORD existingSize=0;if(HttpGet("/api/status",&existing,&existingSize,65536)){BOOL ours=strstr((const char*)existing,"\"version\":\"3.")&&strstr((const char*)existing,"\"frameReady\":")&&strstr((const char*)existing,"\"camera\":")&&strstr((const char*)existing,"\"focuser\":");Free(existing);if(!ours){MessageBoxW(g_main,L"Port " AFS_LOCAL_HTTP_PORT_TEXT_W L" wird bereits von einem anderen lokalen Dienst verwendet. Dieser Dienst wurde nicht beendet.",L"Engine-Port belegt",MB_OK|MB_ICONERROR);AppendFrontendTrace("engine port occupied by foreign service");return FALSE;}ApiAction("shutdown");for(int i=0;i<30;i++){Sleep(100);BYTE* waitBody=0;DWORD waitSize=0;if(!HttpGet("/api/status",&waitBody,&waitSize,4096))break;Free(waitBody);}}wsprintfW(cmd,L"\"%s\"",exe);STARTUPINFOW si;PROCESS_INFORMATION pi;memset(&si,0,sizeof(si));memset(&pi,0,sizeof(pi));si.cb=sizeof(si);si.dwFlags=STARTF_USESHOWWINDOW;si.wShowWindow=SW_HIDE_CONST;if(!CreateProcessW(exe,cmd,0,0,FALSE,CREATE_NO_WINDOW|CREATE_NEW_PROCESS_GROUP,0,g_appDir,&si,&pi)){AppendFrontendTrace("engine CreateProcess failed");return FALSE;}CloseHandle(pi.hThread);g_engineProcess=pi.hProcess;for(int i=0;i<50;i++){Sleep(100);if(PollStatus()){RefreshProfileList();AppendFrontendTrace("engine startup complete");return TRUE;}}if(g_engineProcess){TerminateProcess(g_engineProcess,1);WaitForSingleObject(g_engineProcess,2000);CloseHandle(g_engineProcess);g_engineProcess=0;}AppendFrontendTrace("engine startup timed out");return FALSE;}
static void StartEngineAfterWindowShown(){if(g_engineStartupAttempted)return;g_engineStartupAttempted=TRUE;SetFrontendPhase("engine startup");SetText(hStatus,L"Engine wird gestartet …");if(!g_winsockReady){SetText(hStatus,L"Windows-Netzwerkkomponente nicht verfügbar · Anwendung bleibt für Diagnose geöffnet");AppendFrontendTrace("engine startup skipped because Winsock is unavailable");SetFrontendPhase("idle");return;}if(!StartEngine())SetText(hStatus,L"Engine konnte nicht gestartet werden · FrontendTrace.log und RuntimeTrace.log prüfen");SetFrontendPhase("idle");}

static void HidePageControls(){
    for(int i=0;i<4;i++)ShowCtl(hAfLabels[i],FALSE);ShowCtl(hAfPoints,FALSE);ShowCtl(hAfStep,FALSE);ShowCtl(hAfSamples,FALSE);ShowCtl(hBacklash,FALSE);ShowCtl(hPrefOut,FALSE);ShowCtl(hAfUseSelected,FALSE);ShowCtl(hAfClearSelected,FALSE);ShowCtl(hAfHint,FALSE);ShowCtl(hAfDiagnosis,FALSE);ShowCtl(hStepAssist,FALSE);ShowCtl(hAfStart,FALSE);ShowCtl(hAfStop,FALSE);ShowCtl(hBahtEnable,FALSE);ShowCtl(hBahtText,FALSE);ShowCtl(hDiag,FALSE);ShowCtl(hExport,FALSE);ShowCtl(hLog,FALSE);ShowCtl(hAutoRefocus,FALSE);for(int i=0;i<7;i++)ShowCtl(hAutoLabels[i],FALSE);ShowCtl(hRefocusMin,FALSE);ShowCtl(hRefocusTemp,FALSE);ShowCtl(hRefocusFwhm,FALSE);ShowCtl(hRefocusBadFrames,FALSE);ShowCtl(hRefocusMinStars,FALSE);ShowCtl(hRefocusStability,FALSE);ShowCtl(hRefocusCooldown,FALSE);ShowCtl(hRefocusResume,FALSE);ShowCtl(hSaveAdv,FALSE);ShowCtl(hAutomationInfo,FALSE);ShowCtl(hAutomationDetailsToggle,FALSE);ShowCtl(hBacklashCal,FALSE);ShowCtl(hTempComp,FALSE);ShowCtl(hAutoStartPos,FALSE);ShowCtl(hFilterName,FALSE);ShowCtl(hFilterLearn,FALSE);ShowCtl(hFilterApply,FALSE);ShowCtl(hEvtMeridian,FALSE);ShowCtl(hEvtReconnect,FALSE);ShowCtl(hEvtFilter,FALSE);ShowCtl(hRefocusCaptures,FALSE);ShowCtl(hSmartLabel,FALSE);
    ShowCtl(hCfEnable,FALSE);ShowCtl(hCfMode,FALSE);ShowCtl(hCfFallback,FALSE);for(int i=0;i<6;i++)ShowCtl(hCfLabels[i],FALSE);ShowCtl(hCfMinFrames,FALSE);ShowCtl(hCfDeadband,FALSE);ShowCtl(hCfMaxStep,FALSE);ShowCtl(hCfConfidence,FALSE);ShowCtl(hCfImprovement,FALSE);ShowCtl(hCfSettle,FALSE);ShowCtl(hCfSave,FALSE);ShowCtl(hCfReset,FALSE);ShowCtl(hCfResume,FALSE);ShowCtl(hCfInfo,FALSE);ShowCtl(hCfNote,FALSE);
    ShowCtl(hSelfTest,FALSE);ShowCtl(hTestResult,FALSE);ShowCtl(hTestInfo,FALSE);for(int i=0;i<2;i++)ShowCtl(hSimLabels[i],FALSE);ShowCtl(hSimProfile,FALSE);ShowCtl(hSimBacklash,FALSE);ShowCtl(hSimApply,FALSE);ShowCtl(hSimRandomize,FALSE);ShowCtl(hSimProfileInfo,FALSE);
}
static void UpdatePage(){
    if(!g_expertMode&&g_activeTab>=4)g_activeTab=0;HidePageControls();if(g_activeTab!=0)g_trendHoverIndex=-1;BOOL af=g_activeTab==1,ba=g_activeTab==2,lo=g_activeTab==3,au=g_activeTab==4,cf=g_activeTab==5,te=g_activeTab==7;
    if(af){for(int i=0;i<4;i++)ShowCtl(hAfLabels[i],TRUE);ShowCtl(hAfPoints,TRUE);ShowCtl(hAfStep,TRUE);ShowCtl(hAfSamples,TRUE);ShowCtl(hBacklash,TRUE);ShowCtl(hPrefOut,TRUE);ShowCtl(hAfUseSelected,TRUE);ShowCtl(hAfClearSelected,TRUE);ShowCtl(hAfHint,TRUE);ShowCtl(hStepAssist,TRUE);ShowCtl(hAfStart,TRUE);ShowCtl(hAfStop,TRUE);ShowCtl(hBacklashCal,TRUE);}if(ba){ShowCtl(hBahtEnable,TRUE);ShowCtl(hBahtText,TRUE);}if(lo){ShowCtl(hDiag,TRUE);ShowCtl(hExport,TRUE);ShowCtl(hLog,TRUE);}if(au){ShowCtl(hAutoRefocus,TRUE);for(int i=0;i<7;i++)ShowCtl(hAutoLabels[i],TRUE);ShowCtl(hRefocusMin,TRUE);ShowCtl(hRefocusTemp,TRUE);ShowCtl(hRefocusFwhm,TRUE);ShowCtl(hRefocusBadFrames,TRUE);ShowCtl(hRefocusMinStars,TRUE);ShowCtl(hRefocusStability,TRUE);ShowCtl(hRefocusCooldown,TRUE);ShowCtl(hRefocusResume,TRUE);ShowCtl(hSaveAdv,TRUE);ShowCtl(hAutomationDetailsToggle,TRUE);ShowCtl(hAutomationInfo,g_automationDetailsExpanded);ShowCtl(hTempComp,TRUE);ShowCtl(hAutoStartPos,TRUE);ShowCtl(hFilterName,TRUE);ShowCtl(hFilterLearn,TRUE);ShowCtl(hFilterApply,TRUE);ShowCtl(hEvtMeridian,TRUE);ShowCtl(hEvtReconnect,TRUE);ShowCtl(hEvtFilter,TRUE);ShowCtl(hRefocusCaptures,TRUE);ShowCtl(hSmartLabel,TRUE);}if(cf){ShowCtl(hCfEnable,TRUE);ShowCtl(hCfMode,TRUE);ShowCtl(hCfFallback,TRUE);for(int i=0;i<6;i++)ShowCtl(hCfLabels[i],TRUE);ShowCtl(hCfMinFrames,TRUE);ShowCtl(hCfDeadband,TRUE);ShowCtl(hCfMaxStep,TRUE);ShowCtl(hCfConfidence,TRUE);ShowCtl(hCfImprovement,TRUE);ShowCtl(hCfSettle,TRUE);ShowCtl(hCfSave,TRUE);ShowCtl(hCfReset,TRUE);ShowCtl(hCfResume,TRUE);ShowCtl(hCfInfo,TRUE);ShowCtl(hCfNote,TRUE);}if(te){for(int i=0;i<2;i++)ShowCtl(hSimLabels[i],TRUE);ShowCtl(hSimProfile,TRUE);ShowCtl(hSimBacklash,TRUE);ShowCtl(hSimApply,TRUE);ShowCtl(hSimRandomize,TRUE);ShowCtl(hSimProfileInfo,TRUE);ShowCtl(hSelfTest,TRUE);ShowCtl(hTestResult,TRUE);ShowCtl(hTestInfo,TRUE);}InvalidateRect(g_main,&g_page,FALSE);
}
static int SimulatorApplyButtonWidth(int pageWidth){return ClampI(pageWidth/4,190,220);}
static int MeasureFocusLampHeight(int width,int maxHeight){
    // The recommendation text is dynamic and may wrap differently depending on
    // Windows font metrics and DPI scaling. Measure it with the real UI font
    // instead of assuming that a fixed 128-pixel card is always sufficient.
    const int minimumHeight=148;
    if(maxHeight<minimumHeight)maxHeight=minimumHeight;
    int textWidth=width-24;if(textWidth<120)textWidth=120;
    LPCWSTR reason=g_state.focusNeedReason[0]?g_state.focusNeedReason:L"Noch keine belastbare Fokusreferenz vorhanden.";
    int textHeight=54;
#ifdef ASTROFOCUS_NATIVE_TEST
    int charsPerLine=textWidth/7;if(charsPerLine<16)charsPerLine=16;
    int lines=(WLen(reason)+charsPerLine-1)/charsPerLine;if(lines<1)lines=1;
    textHeight=lines*18;
#else
    HDC measureDc=CreateCompatibleDC(0);
    if(measureDc){
        HGDIOBJ oldFont=SelectObject(measureDc,g_small);
        RECT calc={0,0,textWidth,0};
        int measured=DrawTextW(measureDc,reason,-1,&calc,DT_LEFT|DT_WORDBREAK|DT_EDITCONTROL|DT_CALCRECT|DT_NOPREFIX);
        if(measured>0)textHeight=measured;
        SelectObject(measureDc,oldFont);DeleteDC(measureDc);
    }else{
        int charsPerLine=textWidth/7;if(charsPerLine<16)charsPerLine=16;
        int lines=(WLen(reason)+charsPerLine-1)/charsPerLine;if(lines<1)lines=1;
        textHeight=lines*18;
    }
#endif
    // 68 px are reserved for title and lamp row; 14 px keep the last complete
    // text line visibly clear of the card border.
    return ClampI(68+textHeight+14,minimumHeight,maxHeight);
}
static void Layout(int cw,int ch){
    g_layoutClientWidth=cw;g_layoutClientHeight=ch;
    // 3.1.4: responsive rails keep the center workspace usable on narrower desktop
    // resolutions while preserving the comfortable 3.1.2 proportions on wide screens.
    const int margin=16,gap=12,header=72,status=32;
    const int leftW=ClampI(cw/5,310,340),rightW=ClampI(cw/5,290,320);
    const int top=header+margin,bottom=ch-status-margin;
    const int centerX=margin+leftW+gap,rightX=cw-margin-rightW;
    int contentH=bottom-top,tabH=34,tabGap=6,minPageH=370;
    // The live preview is a fixed workspace anchor: every functional tab uses
    // exactly the same preview rectangle and therefore the same image scale.
    const int previewPercent=52;
    int previewH=(contentH*previewPercent)/100;
    int maxPreview=contentH-(12+tabH+12)-minPageH;
    // On low-height desktops the preview may shrink below 300 px, but it does so
    // identically on every tab and never consumes the minimum function-page area.
    int minPreview=220;if(maxPreview<minPreview)minPreview=maxPreview;
    if(previewH>maxPreview)previewH=maxPreview;
    if(previewH<minPreview)previewH=minPreview;
    if(previewH>contentH-210)previewH=contentH-210;
    g_preview=(RECT){centerX,top,rightX-gap,top+previewH};
    int tabsY=g_preview.bottom+12;
    g_page=(RECT){centerX,tabsY+tabH+12,rightX-gap,bottom};

    // Keep the complete profile toolbar anchored to the right client edge.
    // The former fixed minimum x-position (790 px) pushed Import/Export beyond
    // the client area on narrower or DPI-virtualized desktops.
    const int profileRight=cw-margin,profileGap=4;
    const int profileLabelW=42,profileComboW=202,profileLoadW=64,profileSaveW=72,profileDeleteW=64,profileImportW=80,profileExportW=92;
    const int profileTotal=profileLabelW+profileComboW+profileLoadW+profileSaveW+profileDeleteW+profileImportW+profileExportW+6*profileGap;
    int profileX=profileRight-profileTotal;
    const int themeGap=10,themeLabelW=52,themeComboW=112;
    const int viewLabelW=52,viewComboW=102;
    int themeX=profileX-themeGap-themeLabelW-themeComboW-profileGap;
    int viewX=themeX-themeGap-viewLabelW-viewComboW-profileGap;
    Place(hViewLabel,viewX,24,viewLabelW,24);PlaceDropDownCombo(hViewMode,viewX+viewLabelW+profileGap,20,viewComboW,30,2);
    Place(hThemeLabel,themeX,24,themeLabelW,24);PlaceDropDownCombo(hTheme,themeX+themeLabelW+profileGap,20,themeComboW,30,3);
    int hx=profileX;
    Place(hProfileLabel,hx,24,profileLabelW,24);hx+=profileLabelW+profileGap;
    Place(hProfile,hx,20,profileComboW,180);hx+=profileComboW+profileGap;
    Place(hLoadProfile,hx,20,profileLoadW,30);hx+=profileLoadW+profileGap;
    Place(hSaveProfile,hx,20,profileSaveW,30);hx+=profileSaveW+profileGap;
    Place(hDeleteProfile,hx,20,profileDeleteW,30);hx+=profileDeleteW+profileGap;
    Place(hImportProfile,hx,20,profileImportW,30);hx+=profileImportW+profileGap;
    Place(hExportProfile,hx,20,profileExportW,30);

    const int camH=350;
    g_leftCamera=(RECT){margin,top,margin+leftW,top+camH};
    int x=margin+16,y=top+34,inner=leftW-32,half=(inner-10)/2;
    Place(hCamLabels[0],x,y,inner,18);Place(hCamBackend,x,y+19,inner,180);y+=55;
    Place(hCamLabels[1],x,y,inner,18);Place(hCamDevice,x,y+19,inner,190);y+=55;
    int thirdButton=(inner-12)/3;
    Place(hCamRefresh,x,y,thirdButton,32);Place(hCamSelect,x+thirdButton+6,y,thirdButton,32);Place(hCamConnect,x+2*(thirdButton+6),y,inner-2*(thirdButton+6),32);y+=43;
    Place(hCamLabels[2],x,y,half,18);Place(hCamLabels[3],x+half+10,y,half,18);
    Place(hExposure,x,y+19,half,28);Place(hGain,x+half+10,y+19,half,28);y+=55;
    Place(hLive,x,y,inner,36);y+=45;
    int overlayCtlGap=6,overlayCtlW=(inner-overlayCtlGap)/2;
    Place(hStretch,x,y,overlayCtlW,24);Place(hStars,x+overlayCtlW+overlayCtlGap,y,inner-overlayCtlW-overlayCtlGap,24);y+=29;
    Place(hSaturation,x,y,overlayCtlW,24);Place(hZones,x+overlayCtlW+overlayCtlGap,y,inner-overlayCtlW-overlayCtlGap,24);

    int focTop=top+camH+gap,focH=bottom-focTop;
    if(focH<300)focH=300;
    g_leftFocuser=(RECT){margin,focTop,margin+leftW,focTop+focH};x=margin+16;y=focTop+34;
    Place(hFocLabels[0],x,y,inner,18);Place(hFocBackend,x,y+19,inner,150);y+=55;
    Place(hFocLabels[1],x,y,inner,18);Place(hFocDevice,x,y+19,inner,28);y+=55;
    Place(hFocSelect,x,y,180,32);Place(hFocConnect,x+190,y,inner-190,32);y+=43;
    Place(hFocSetup,x,y,inner,32);y+=43;
    Place(hFocLabels[2],x,y,half,18);Place(hFocLabels[3],x+half+10,y,half,18);
    Place(hPosition,x,y+19,half,26);Place(hTemperature,x+half+10,y+19,half,26);y+=51;
    int third=(inner-16)/3;
    Place(hFocLabels[4],x,y,third,18);Place(hFocLabels[5],x+third+8,y,third,18);Place(hFocLabels[6],x+2*(third+8),y,third,18);
    Place(hManualStep,x,y+19,third,28);Place(hSafeMin,x+third+8,y+19,third,28);Place(hSafeMax,x+2*(third+8),y+19,third,28);y+=56;
    Place(hMoveIn,x,y,98,32);Place(hMoveOut,x+108,y,98,32);Place(hHalt,x+216,y,inner-216,32);

    int tabMin[8]={68,94,84,86,94,112,82,64};int visibleTabs=g_expertMode?8:4;int minTotal=(visibleTabs-1)*tabGap;for(int i=0;i<visibleTabs;i++)minTotal+=tabMin[i];
    int available=g_page.right-g_page.left;int extra=available-minTotal;if(extra<0)extra=0;int each=extra/visibleTabs,rem=extra%visibleTabs,tx=centerX;
    for(int i=0;i<8;i++){BOOL visible=i<visibleTabs;ShowCtl(hTabs[i],visible);if(visible){int tw=tabMin[i]+each+(i<rem?1:0);Place(hTabs[i],tx,tabsY,tw,tabH);tx+=tw+tabGap;}}

    int px=g_page.left+18,py=g_page.top+36,pw=g_page.right-g_page.left-36,ph=g_page.bottom-g_page.top-36;

    // Autofocus page ---------------------------------------------------------
    // The live preview keeps the same rectangle as on every other page. Autofocus
    // actions use the former, readable full-width vertical button rail. The
    // duplicate diagnosis control is removed; all fit information is shown in the
    // wider result panel beside the graph.
    int afHeaderGap=14;
    int afActionW=ClampI((pw*22)/100,200,250);
    int afFieldsW=pw-afActionW-afHeaderGap;
    int afActionX=px+afFieldsW+afHeaderGap;
    int afColGap=9,afColW=(afFieldsW-3*afColGap)/4;if(afColW<82)afColW=82;
    HWND edits[4]={hAfPoints,hAfStep,hAfSamples,hBacklash};
    for(int i=0;i<4;i++){
        int cx=px+i*(afColW+afColGap);Place(hAfLabels[i],cx,py,afColW,17);
        if(edits[i]==hAfPoints)PlaceDropDownCombo(edits[i],cx,py+17,afColW,29,6);
        else if(edits[i]==hAfSamples)PlaceDropDownCombo(edits[i],cx,py+17,afColW,29,5);
        else Place(edits[i],cx,py+17,afColW,29);
    }

    Place(hStepAssist,afActionX,py,afActionW,42);
    Place(hAfStart,afActionX,py+50,afActionW,44);
    Place(hAfStop,afActionX,py+102,afActionW,42);
    Place(hBacklashCal,afActionX,py+152,afActionW,54);

    int afOptionsY=py+52;
    int afClearW=132,afOptionGap=10;
    int afOptionW=(afFieldsW-afClearW-2*afOptionGap)/2;if(afOptionW<118)afOptionW=118;
    Place(hPrefOut,px,afOptionsY,afOptionW,24);
    Place(hAfUseSelected,px+afOptionW+afOptionGap,afOptionsY,afFieldsW-afOptionW-afClearW-2*afOptionGap,24);
    Place(hAfClearSelected,px+afFieldsW-afClearW,afOptionsY-3,afClearW,30);
    Place(hAfHint,px,py+79,afFieldsW,28);

    // The result/graph region stays left of the action rail. The result panel is
    // deliberately wider so model and control values remain fully readable.
    int afVisualTop=py+113,afVisualBottom=g_page.bottom-8;
    int afVisualH=afVisualBottom-afVisualTop;
    int afVisualW=afFieldsW;
    int afGap=14;
    int minChartW=280;
    // Give the FIT result priority on desktop widths. The longest productive
    // value is the final control measurement and needs about 280 px in the
    // value column at the normal Segoe UI metrics.
    int afSummaryW=ClampI((afVisualW*52)/100,360,480);
    if(afVisualW-afSummaryW-afGap<minChartW)afSummaryW=afVisualW-afGap-minChartW;
    if(afSummaryW<250)afSummaryW=250;
    int afChartAvailable=afVisualW-afSummaryW-afGap;
    int afChartMax=ClampI((afVisualH*27)/10,360,720);
    int afChartW=afChartAvailable;if(afChartW>afChartMax)afChartW=afChartMax;
    if(afChartW<minChartW)afChartW=minChartW;
    int afClusterW=afSummaryW+afGap+afChartW;
    int afClusterX=px+afVisualW-afClusterW;if(afClusterX<px)afClusterX=px;
    g_afSummary=(RECT){afClusterX,afVisualTop,afClusterX+afSummaryW,afVisualBottom};
    g_afChart=(RECT){g_afSummary.right+afGap,afVisualTop,g_afSummary.right+afGap+afChartW,afVisualBottom};
    // The former diagnosis space below the full-width buttons now contains only
    // the compact legend. Results remain exclusively in FIT-ERGEBNIS.
    g_afLegend=(RECT){afActionX,py+214,afActionX+afActionW,afVisualBottom};

    Place(hBahtEnable,px,py,pw,28);Place(hBahtText,px,py+44,pw,60);
    Place(hDiag,px,py,214,38);Place(hExport,px+224,py,224,38);Place(hLog,px,py+52,pw,ph>64?ph-64:30);

    // Automation page --------------------------------------------------------
    // Configuration and status use a responsive two-column layout. The right rail
    // remains wide enough for the traffic-light card; detailed diagnostics can be
    // collapsed so the page stays visually quiet during normal observing.
    int autoGap=18,autoInfoW=ClampI((pw*31)/100,250,310);
    const int autoMinConfigW=472;
    if(pw-autoInfoW-autoGap<autoMinConfigW)autoInfoW=pw-autoGap-autoMinConfigW;
    if(autoInfoW<230){autoInfoW=0;autoGap=0;}
    int autoConfigW=pw-autoInfoW-autoGap;
    int autoInfoX=px+autoConfigW+autoGap,autoColGap=22,autoColW=(autoConfigW-autoColGap)/2,autoCol2=px+autoColW+autoColGap;
    Place(hAutoRefocus,px,py,268,26);
    int ay=py+34,rowH=26,rowStep=30;
    int labW=ClampI(autoColW-92,124,154),editW=ClampI(autoColW-labW-10,74,94);
    Place(hAutoLabels[0],px,ay,labW,rowH);Place(hRefocusMin,px+labW+10,ay,editW,rowH);
    Place(hAutoLabels[1],autoCol2,ay,labW,rowH);Place(hRefocusTemp,autoCol2+labW+10,ay,editW,rowH);ay+=rowStep;
    Place(hAutoLabels[2],px,ay,labW,rowH);Place(hRefocusFwhm,px+labW+10,ay,editW,rowH);
    Place(hAutoLabels[3],autoCol2,ay,labW,rowH);Place(hRefocusBadFrames,autoCol2+labW+10,ay,editW,rowH);ay+=rowStep;
    Place(hAutoLabels[4],px,ay,labW,rowH);Place(hRefocusMinStars,px+labW+10,ay,editW,rowH);
    Place(hAutoLabels[5],autoCol2,ay,labW,rowH);Place(hRefocusStability,autoCol2+labW+10,ay,editW,rowH);ay+=rowStep;
    Place(hAutoLabels[6],px,ay,labW,rowH);Place(hRefocusCooldown,px+labW+10,ay,editW,rowH);
    int captureEditW=ClampI(autoColW/4,72,92),captureLabelW=autoColW-captureEditW-10;
    Place(hSmartLabel,autoCol2,ay,captureLabelW,rowH);Place(hRefocusCaptures,autoCol2+captureLabelW+10,ay,captureEditW,rowH);ay+=rowStep+4;

    int actionGap=12,autoActionW=(autoConfigW-actionGap)/2;
    Place(hSaveAdv,px,ay,autoActionW,34);Place(hRefocusResume,px+autoActionW+actionGap,ay,autoConfigW-autoActionW-actionGap,34);ay+=40;
    Place(hAutoStartPos,px,ay,autoColW,24);Place(hTempComp,autoCol2,ay,autoColW,24);ay+=28;
    Place(hEvtReconnect,px,ay,autoColW,24);Place(hEvtMeridian,autoCol2,ay,autoColW,24);ay+=28;
    Place(hEvtFilter,px,ay,autoConfigW,24);ay+=30;

    // The two offset buttons need more room than the old 96 px minimum; on real
    // Segoe UI/DPI combinations "Offset anwenden" otherwise clips at the right edge.
    const int filterGap=12;
    int filterBtnW=ClampI(autoConfigW/4,134,152);
    int filterNameW=autoConfigW-2*filterBtnW-2*filterGap;
    if(filterNameW<150){filterBtnW=(autoConfigW-150-2*filterGap)/2;if(filterBtnW<126)filterBtnW=126;filterNameW=autoConfigW-2*filterBtnW-2*filterGap;}
    Place(hFilterName,px,ay,filterNameW,32);
    Place(hFilterLearn,px+filterNameW+filterGap,ay,filterBtnW,32);
    Place(hFilterApply,px+filterNameW+filterGap+filterBtnW+filterGap,ay,filterBtnW,32);

    if(autoInfoW){
        // Reserve a usable details box even at the minimum window height, then
        // size the recommendation card from the actual wrapped reason text.
        const int focusLampMinH=148,detailsMinH=48;
        int focusLampMaxH=ph-(12+32+10+detailsMinH+8);
        if(focusLampMaxH<focusLampMinH)focusLampMaxH=focusLampMinH;
        int focusLampH=MeasureFocusLampHeight(autoInfoW,focusLampMaxH);
        g_focusLamp=(RECT){autoInfoX,py,g_page.right-18,py+focusLampH};
        int toggleY=g_focusLamp.bottom+12;Place(hAutomationDetailsToggle,autoInfoX,toggleY,autoInfoW,32);
        int infoY=toggleY+42,infoH=ph-(infoY-py)-8;if(infoH<detailsMinH)infoH=detailsMinH;
        Place(hAutomationInfo,autoInfoX,infoY,autoInfoW,infoH);
    }else{
        g_focusLamp=(RECT){0,0,0,0};
        Place(hAutomationDetailsToggle,g_page.right+20,py,1,1);
        Place(hAutomationInfo,g_page.right+20,py,1,1);
    }

    // Continuous-focus page -------------------------------------------------
    // The expert controls use a responsive two-column top rail and a full-width
    // trend chart. Widths are derived from g_page so labels and buttons remain
    // inside the client area at the supported minimum size and under DPI scaling.
    int cfGap=18,cfInfoW=ClampI((pw*36)/100,300,390);const int cfMinConfigW=430;
    if(pw-cfInfoW-cfGap<cfMinConfigW)cfInfoW=pw-cfGap-cfMinConfigW;
    if(cfInfoW<270){cfInfoW=0;cfGap=0;}
    int cfConfigW=pw-cfInfoW-cfGap,cfInfoX=px+cfConfigW+cfGap;
    int cfTopH=ClampI(ph/2,168,202);if(ph-cfTopH-18<112)cfTopH=ph-130;if(cfTopH<150)cfTopH=150;
    int cfRow=28,cfRowGap=7;int cfLeftW=(cfConfigW-18)/2,cfRightX=px+cfLeftW+18;int cfEditW=ClampI((cfLeftW*36)/100,78,98),cfLabelW=cfLeftW-cfEditW-8;
    Place(hCfEnable,px,py,cfLeftW,26);PlaceDropDownCombo(hCfMode,cfRightX,py,cfConfigW-cfLeftW-18,30,3);
    int cfy=py+34;Place(hCfFallback,px,cfy,cfConfigW,24);cfy+=31;
    Place(hCfLabels[0],px,cfy,cfLabelW,cfRow);Place(hCfMinFrames,px+cfLabelW+8,cfy,cfEditW,cfRow);
    Place(hCfLabels[1],cfRightX,cfy,cfLabelW,cfRow);Place(hCfDeadband,cfRightX+cfLabelW+8,cfy,cfEditW,cfRow);cfy+=cfRow+cfRowGap;
    Place(hCfLabels[2],px,cfy,cfLabelW,cfRow);Place(hCfMaxStep,px+cfLabelW+8,cfy,cfEditW,cfRow);
    Place(hCfLabels[3],cfRightX,cfy,cfLabelW,cfRow);Place(hCfConfidence,cfRightX+cfLabelW+8,cfy,cfEditW,cfRow);cfy+=cfRow+cfRowGap;
    Place(hCfLabels[4],px,cfy,cfLabelW,cfRow);Place(hCfImprovement,px+cfLabelW+8,cfy,cfEditW,cfRow);
    Place(hCfLabels[5],cfRightX,cfy,cfLabelW,cfRow);Place(hCfSettle,cfRightX+cfLabelW+8,cfy,cfEditW,cfRow);cfy+=cfRow+9;
    int cfButtonGap=10,cfButtonW=(cfConfigW-2*cfButtonGap)/3;Place(hCfSave,px,cfy,cfButtonW,34);Place(hCfReset,px+cfButtonW+cfButtonGap,cfy,cfButtonW,34);Place(hCfResume,px+2*(cfButtonW+cfButtonGap),cfy,cfConfigW-2*(cfButtonW+cfButtonGap),34);
    if(cfInfoW){Place(hCfInfo,cfInfoX,py,cfInfoW,cfTopH-70);Place(hCfNote,cfInfoX,py+cfTopH-64,cfInfoW,64);}else{Place(hCfInfo,g_page.right+20,py,1,1);Place(hCfNote,px,py+cfTopH-40,cfConfigW,38);}
    int cfChartTop=py+cfTopH+12;g_cfChart=(RECT){px,cfChartTop,g_page.right-18,g_page.bottom-8};if(g_cfChart.bottom-g_cfChart.top<100)g_cfChart.top=g_cfChart.bottom-100;

    int simLabelW=150,simGap=10,simBackW=110,simRandomW=150,simApplyW=SimulatorApplyButtonWidth(pw);Place(hSimLabels[0],px,py,simLabelW,32);PlaceDropDownCombo(hSimProfile,px+simLabelW+simGap,py,ClampI(pw-simLabelW-simGap-simRandomW-simGap,250,430),32,9);Place(hSimRandomize,g_page.right-18-simRandomW,py,simRandomW,32);
    Place(hSimLabels[1],px,py+44,simLabelW,36);Place(hSimBacklash,px+simLabelW+simGap,py+44,simBackW,36);Place(hSimApply,px+simLabelW+simGap+simBackW+simGap,py+44,simApplyW,36);Place(hSimProfileInfo,px,py+88,pw,48);
    Place(hSelfTest,px,py+144,252,36);Place(hTestResult,px,py+196,pw,28);Place(hTestInfo,px,py+230,pw,90);

    int rx=rightX,ry=top,rw=rightW;
    g_rightAnalysis=(RECT){rx,ry,rx+rw,ry+204};
    g_rightStar=(RECT){rx,g_rightAnalysis.bottom+gap,rx+rw,g_rightAnalysis.bottom+gap+202};
    g_rightTrend=(RECT){rx,g_rightStar.bottom+gap,rx+rw,g_rightStar.bottom+gap+210};
    g_rightField=(RECT){rx,g_rightTrend.bottom+gap,rx+rw,bottom};
    Place(hStatus,margin,ch-status,cw-2*margin,status-2);UpdatePage();
}
static void DrawPanel(HDC dc,RECT r,LPCWSTR title){FillRect(dc,&r,g_panel);HGDIOBJ op=SelectObject(dc,g_border),ob=SelectObject(dc,GetStockObject(NULL_BRUSH));Rectangle(dc,r.left,r.top,r.right,r.bottom);SelectObject(dc,op);SelectObject(dc,ob);SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);SetTextColor(dc,g_theme.textSecondary);TextOutW(dc,r.left+12,r.top+10,title,WLen(title));}
static void DrawDeviceConnectionLamp(HDC dc,RECT panel,BOOL connected){
    if(panel.right<=panel.left||panel.bottom<=panel.top)return;
    LPCWSTR text=connected?L"Verbunden":L"Getrennt";
    DWORD color=connected?g_theme.connectionGood:g_theme.connectionBad;
    // Same compact visual language as the focus-status lamp: colored circle + short label.
    const int textW=connected?66:58;
    int cy=panel.top+18;
    int lampLeft=panel.right-18-textW-17;
    HBRUSH lamp=CreateSolidBrush(color);
    HGDIOBJ oldBrush=SelectObject(dc,lamp),oldPen=SelectObject(dc,g_border);
    Ellipse(dc,lampLeft,cy-6,lampLeft+13,cy+7);
    SelectObject(dc,oldPen);SelectObject(dc,oldBrush);DeleteObject(lamp);
    SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);SetTextColor(dc,g_theme.textSecondary);
    TextOutW(dc,lampLeft+19,cy-8,text,WLen(text));
}
static void DrawMetric(HDC dc,int x,int y,LPCWSTR label,LPCWSTR value){SelectObject(dc,g_small);SetTextColor(dc,g_theme.textMuted);TextOutW(dc,x,y,label,WLen(label));SetTextColor(dc,g_theme.textPrimary);TextOutW(dc,x+148,y,value,WLen(value));}
static void FormatD(double v,int dec,wchar_t* out){if(!out)return;if(!(v==v)||v<-10000000.0||v>10000000.0){lstrcpyW(out,L"–");return;}int scale=dec==2?100:10;BOOL neg=v<0.0;double av=neg?-v:v;int q=(int)(av*scale+0.5),a=q/scale,b=q%scale;if(dec==2)wsprintfW(out,neg?L"-%d,%02d":L"%d,%02d",a,b);else wsprintfW(out,neg?L"-%d,%d":L"%d,%d",a,b);}
static BOOL TrendMetricValid(double v){return v==v&&v>0.0&&v<1000.0;}
static AFS_NOINLINE void CopyTrendPoint(TrendPoint* d,const TrendPoint* s){d->frameSequence=s->frameSequence;d->tick=s->tick;d->fwhm=s->fwhm;d->hfr=s->hfr;d->stars=s->stars;d->autofocusMarker=s->autofocusMarker;}
static void ResetTrendHistory(){g_trendCount=0;g_trendLastFrame=-1;g_trendHoverIndex=-1;g_trendPendingAfMarker=FALSE;memset(g_trend,0,sizeof(g_trend));}
static BOOL UpdateTrendHistory(const AppState* old){
    BOOL changed=FALSE;
    if(old&&old->autofocus&&!g_state.autofocus&&g_state.afFinalValid)g_trendPendingAfMarker=TRUE;
    if(g_trendLastFrame>=0&&g_state.frameSequence<g_trendLastFrame){ResetTrendHistory();changed=TRUE;}
    if(g_state.frameSequence==g_trendLastFrame)return changed;
    g_trendLastFrame=g_state.frameSequence;
    if(!g_state.frameReady||!g_state.live||g_state.autofocus||g_state.usedStars<=0||!TrendMetricValid(g_state.fwhm)||!TrendMetricValid(g_state.hfr))return changed;
    if(g_trendCount>=TREND_CAPACITY){for(int i=1;i<TREND_CAPACITY;i++)CopyTrendPoint(&g_trend[i-1],&g_trend[i]);g_trendCount=TREND_CAPACITY-1;if(g_trendHoverIndex>0)g_trendHoverIndex--;else g_trendHoverIndex=-1;}
    TrendPoint* p=&g_trend[g_trendCount++];p->frameSequence=g_state.frameSequence;p->tick=GetTickCount64();p->fwhm=g_state.fwhm;p->hfr=g_state.hfr;p->stars=g_state.usedStars;p->autofocusMarker=g_trendPendingAfMarker;g_trendPendingAfMarker=FALSE;return TRUE;
}
static AFS_NOINLINE void CopyContinuousFocusUiPoint(ContinuousFocusUiPoint* d,const ContinuousFocusUiPoint* a){d->frameSequence=a->frameSequence;d->position=a->position;d->target=a->target;d->correction=a->correction;d->confidence=a->confidence;}
static BOOL UpdateContinuousFocusHistory(const AppState* old){
    BOOL changed=FALSE;if(g_cfUiLastFrame>=0&&g_state.frameSequence<g_cfUiLastFrame){g_cfUiCount=0;g_cfUiLastFrame=-1;g_cfUiLastCorrection=0;memset(g_cfUi,0,sizeof(g_cfUi));changed=TRUE;}
    BOOL correctionChanged=!old||old->continuousFocusLastCorrection!=g_state.continuousFocusLastCorrection||old->continuousFocusAccepted!=g_state.continuousFocusAccepted||old->continuousFocusRejected!=g_state.continuousFocusRejected;
    if(g_state.frameSequence==g_cfUiLastFrame&&!correctionChanged)return changed;
    if(g_state.frameSequence<=0||g_state.position<0)return changed;
    if(g_cfUiCount>=CF_UI_CAPACITY){for(int i=1;i<CF_UI_CAPACITY;i++)CopyContinuousFocusUiPoint(&g_cfUi[i-1],&g_cfUi[i]);g_cfUiCount=CF_UI_CAPACITY-1;}
    ContinuousFocusUiPoint* p=&g_cfUi[g_cfUiCount++];p->frameSequence=g_state.frameSequence;p->position=g_state.position;p->target=g_state.continuousFocusTarget>=0?g_state.continuousFocusTarget:g_state.position;p->correction=correctionChanged?g_state.continuousFocusLastCorrection:0;p->confidence=g_state.continuousFocusConfidence;g_cfUiLastFrame=g_state.frameSequence;g_cfUiLastCorrection=g_state.continuousFocusLastCorrection;return TRUE;
}
static int TrendPointX(int index,const RECT* plot){
    if(!plot||index<0||index>=g_trendCount)return plot?plot->left:0;int width=plot->right-plot->left;if(width<=0||g_trendCount<=1)return plot->left;
    ULONGLONG first=g_trend[0].tick,last=g_trend[g_trendCount-1].tick;if(last<=first)return plot->left+(index*width)/(g_trendCount-1);
    double f=(double)(g_trend[index].tick-first)/(double)(last-first);if(f<0.0)f=0.0;if(f>1.0)f=1.0;return plot->left+(int)(f*(double)width+0.5);
}
static int TrendPointY(double value,double ymin,double ymax,const RECT* plot){if(!plot||ymax<=ymin)return plot?plot->bottom:0;double f=(value-ymin)/(ymax-ymin);if(f<0.0)f=0.0;if(f>1.0)f=1.0;return plot->bottom-(int)(f*(double)(plot->bottom-plot->top)+0.5);}
static void TrendRange(double* outMin,double* outMax){
    double mn=0.0,mx=0.0;BOOL any=FALSE;for(int i=0;i<g_trendCount;i++){double v=g_trend[i].fwhm;if(!TrendMetricValid(v))continue;if(!any||v<mn)mn=v;if(!any||v>mx)mx=v;any=TRUE;}
    if(g_state.autoRefocusReferenceReady&&TrendMetricValid(g_state.autoRefocusReferenceFwhm)){double ref=g_state.autoRefocusReferenceFwhm;if(!any||ref<mn)mn=ref;if(!any||ref>mx)mx=ref;any=TRUE;if(g_state.autoRefocusFwhmEnabled&&g_state.refocusFwhmPercent>0.0){double limit=ref*(1.0+g_state.refocusFwhmPercent/100.0);if(TrendMetricValid(limit)){if(limit<mn)mn=limit;if(limit>mx)mx=limit;}}}
    if(!any){mn=0.0;mx=1.0;}double span=mx-mn;if(span<0.8){double mid=(mn+mx)*0.5;mn=mid-0.4;mx=mid+0.4;span=0.8;}double pad=span*0.10;if(pad<0.08)pad=0.08;mn-=pad;mx+=pad;if(mn<0.0)mn=0.0;if(mx<=mn)mx=mn+1.0;*outMin=mn;*outMax=mx;
}
static void UpdateTrendHoverFromMouse(int mx,int my){
    int next=-1;if(g_activeTab==0&&g_trendCount>0&&mx>=g_liveTrendPlot.left&&mx<=g_liveTrendPlot.right&&my>=g_liveTrendPlot.top&&my<=g_liveTrendPlot.bottom){int best=0,bestDist=0x7fffffff;for(int i=0;i<g_trendCount;i++){int d=mx-TrendPointX(i,&g_liveTrendPlot);if(d<0)d=-d;if(d<bestDist){bestDist=d;best=i;}}next=best;}
    if(next!=g_trendHoverIndex){g_trendHoverIndex=next;if(g_main)InvalidateRect(g_main,&g_page,FALSE);}
}
static void DrawFocusTrend(HDC dc){
    DrawPanel(dc,g_page,L"LIVE-FWHM-VERLAUF · LETZTE 60 GÜLTIGE MESSUNGEN");
    RECT plot={g_page.left+64,g_page.top+66,g_page.right-26,g_page.bottom-78};g_liveTrendPlot=plot;SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);
    if(plot.right<=plot.left+40||plot.bottom<=plot.top+40)return;
    double ymin=0.0,ymax=1.0;TrendRange(&ymin,&ymax);
    HGDIOBJ oldPen=SelectObject(dc,g_grid);for(int i=0;i<=4;i++){int yy=plot.top+i*(plot.bottom-plot.top)/4;MoveToEx(dc,plot.left,yy,0);LineTo(dc,plot.right,yy);double v=ymax-(ymax-ymin)*(double)i/4.0;wchar_t val[32];FormatD(v,2,val);SetTextColor(dc,g_theme.textMuted);TextOutW(dc,plot.left-50,yy-8,val,WLen(val));}SelectObject(dc,oldPen);
    SetTextColor(dc,g_theme.textSecondary);TextOutW(dc,plot.left,g_page.top+38,L"FWHM [px] · niedriger ist besser",WLen(L"FWHM [px] · niedriger ist besser"));
    if(g_trendCount==0){RECT empty={plot.left,plot.top,plot.right,plot.bottom};SetTextColor(dc,g_theme.textMuted);DrawTextW(dc,L"Noch keine gültigen Live-Messungen. Kamera verbinden und Live-Fokus starten.",-1,&empty,DT_CENTER|DT_VCENTER|DT_SINGLELINE);return;}
    if(g_state.autoRefocusReferenceReady&&TrendMetricValid(g_state.autoRefocusReferenceFwhm)){
        double ref=g_state.autoRefocusReferenceFwhm;int ry=TrendPointY(ref,ymin,ymax,&plot);oldPen=SelectObject(dc,g_reference);MoveToEx(dc,plot.left,ry,0);LineTo(dc,plot.right,ry);SelectObject(dc,oldPen);wchar_t rf[32],label[96];FormatD(ref,2,rf);wsprintfW(label,L"Referenz %s px",rf);SetTextColor(dc,g_theme.referenceText);TextOutW(dc,plot.right-150,ry-17,label,WLen(label));
        if(g_state.autoRefocusFwhmEnabled&&g_state.refocusFwhmPercent>0.0){double limit=ref*(1.0+g_state.refocusFwhmPercent/100.0);if(TrendMetricValid(limit)){int ly=TrendPointY(limit,ymin,ymax,&plot);oldPen=SelectObject(dc,g_threshold);MoveToEx(dc,plot.left,ly,0);LineTo(dc,plot.right,ly);SelectObject(dc,oldPen);wchar_t lm[32],pct[32];FormatD(limit,2,lm);FormatD(g_state.refocusFwhmPercent,1,pct);wsprintfW(label,L"Refokus +%s %% · %s px",pct,lm);SetTextColor(dc,g_theme.thresholdText);TextOutW(dc,plot.right-205,ly+4,label,WLen(label));}}
    }
    for(int i=0;i<g_trendCount;i++)if(g_trend[i].autofocusMarker){int xx=TrendPointX(i,&plot);oldPen=SelectObject(dc,g_marker);MoveToEx(dc,xx,plot.top,0);LineTo(dc,xx,plot.bottom);SelectObject(dc,oldPen);SetTextColor(dc,g_theme.markerText);TextOutW(dc,xx+4,plot.top+3,L"AF",2);}
    oldPen=SelectObject(dc,g_curve);for(int i=0;i<g_trendCount;i++){int xx=TrendPointX(i,&plot),yy=TrendPointY(g_trend[i].fwhm,ymin,ymax,&plot);if(i==0)MoveToEx(dc,xx,yy,0);else LineTo(dc,xx,yy);}SelectObject(dc,oldPen);
    int latest=g_trendCount-1,lx=TrendPointX(latest,&plot),ly=TrendPointY(g_trend[latest].fwhm,ymin,ymax,&plot);HGDIOBJ oldBrush=SelectObject(dc,GetStockObject(NULL_BRUSH));oldPen=SelectObject(dc,g_curve);Ellipse(dc,lx-4,ly-4,lx+5,ly+5);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);
    ULONGLONG now=GetTickCount64();int age=(int)((now-g_trend[0].tick)/1000ULL);if(age<0)age=0;wchar_t leftTime[48];wsprintfW(leftTime,L"vor %d s",age);SetTextColor(dc,g_theme.textMuted);TextOutW(dc,plot.left,plot.bottom+10,leftTime,WLen(leftTime));TextOutW(dc,plot.right-30,plot.bottom+10,L"jetzt",5);
    wchar_t cur[32],ref[32],deg[32],stab[32],summary[320];FormatD(g_trend[latest].fwhm,2,cur);FormatD(g_state.stability,2,stab);if(g_state.autoRefocusReferenceReady&&TrendMetricValid(g_state.autoRefocusReferenceFwhm)){FormatD(g_state.autoRefocusReferenceFwhm,2,ref);FormatD(g_state.autoRefocusFwhmDegradePercent,1,deg);wsprintfW(summary,L"Aktuell %s px · Referenz %s px · %s%s %% · Stabilität %s px · %d Sterne",cur,ref,g_state.autoRefocusFwhmDegradePercent>=0.0?L"+":L"",deg,stab,g_trend[latest].stars);}else wsprintfW(summary,L"Aktuell %s px · Referenz noch nicht gesetzt · Stabilität %s px · %d Sterne",cur,stab,g_trend[latest].stars);SetTextColor(dc,g_theme.textPrimary);RECT summaryRect={plot.left,g_page.bottom-38,plot.right,g_page.bottom-12};DrawTextW(dc,summary,-1,&summaryRect,DT_LEFT|DT_SINGLELINE|DT_END_ELLIPSIS);
    if(g_trendHoverIndex>=0&&g_trendHoverIndex<g_trendCount){int i=g_trendHoverIndex,xx=TrendPointX(i,&plot),yy=TrendPointY(g_trend[i].fwhm,ymin,ymax,&plot);oldBrush=SelectObject(dc,GetStockObject(NULL_BRUSH));oldPen=SelectObject(dc,g_bad);Ellipse(dc,xx-5,yy-5,xx+6,yy+6);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);int sec=(int)((now-g_trend[i].tick)/1000ULL);if(sec<0)sec=0;wchar_t f[32],h[32],tipText[260];FormatD(g_trend[i].fwhm,2,f);FormatD(g_trend[i].hfr,2,h);wsprintfW(tipText,L"Frame %d · vor %d s · FWHM %s px · HFR %s px · %d Sterne",g_trend[i].frameSequence,sec,f,h,g_trend[i].stars);int tw=520,th=34,tx=xx+12,ty=yy-46;if(tx+tw>plot.right)tx=xx-tw-12;if(tx<plot.left)tx=plot.left;if(ty<plot.top)ty=yy+12;if(ty+th>plot.bottom)ty=plot.bottom-th;RECT tip={tx,ty,tx+tw,ty+th};FillRect(dc,&tip,g_panel);oldPen=SelectObject(dc,g_border);oldBrush=SelectObject(dc,GetStockObject(NULL_BRUSH));Rectangle(dc,tip.left,tip.top,tip.right,tip.bottom);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);SetTextColor(dc,g_theme.textPrimary);TextOutW(dc,tip.left+8,tip.top+9,tipText,WLen(tipText));}
}
static BOOL ValidStarOverlayPoint(int i){
    if(i<0||i>=g_state.starArrayCount||i>=160||g_frameW<=0||g_frameH<=0)return FALSE;
    double x=g_state.starX[i],y=g_state.starY[i],f=g_state.starFwhm[i];
    return x==x&&y==y&&f==f&&x>=0.0&&x<(double)g_frameW&&y>=0.0&&y<(double)g_frameH&&f>=0.0&&f<=1000.0;
}
static void PaintPreview(HDC dc){
    FillRect(dc,&g_preview,g_panel);HGDIOBJ op=SelectObject(dc,g_border),ob=SelectObject(dc,GetStockObject(NULL_BRUSH));Rectangle(dc,g_preview.left,g_preview.top,g_preview.right,g_preview.bottom);SelectObject(dc,op);SelectObject(dc,ob);
    RECT inner={g_preview.left+8,g_preview.top+8,g_preview.right-8,g_preview.bottom-8};HBRUSH black=CreateSolidBrush(RGB(16,18,22));FillRect(dc,&inner,black);DeleteObject(black);
    if(g_frame&&g_framePixels&&g_frameW>0&&g_frameH>0&&g_frameW<=10000&&g_frameH<=10000&&g_frameOff<g_frameSize){
        int pw=inner.right-inner.left,ph=inner.bottom-inner.top;double sx=(double)pw/g_frameW,sy=(double)ph/g_frameH,sc=sx<sy?sx:sy;int dw=(int)(g_frameW*sc),dh=(int)(g_frameH*sc),dx=inner.left+(pw-dw)/2,dy=inner.top+(ph-dh)/2;
        StretchDIBits(dc,dx,dy,dw,dh,0,0,g_frameW,g_frameH,g_framePixels,&g_frameInfo,DIB_RGB_COLORS,SRCCOPY);
        SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);
        if(g_state.simulator){RECT badge={dx+dw-210,dy+10,dx+dw-10,dy+42};HBRUSH sb=CreateSolidBrush(g_theme.simBadge);FillRect(dc,&badge,sb);DeleteObject(sb);HGDIOBJ bp=SelectObject(dc,g_curve),bb=SelectObject(dc,GetStockObject(NULL_BRUSH));Rectangle(dc,badge.left,badge.top,badge.right,badge.bottom);SelectObject(dc,bp);SelectObject(dc,bb);wchar_t st[96];wsprintfW(st,L"SIMULATOR · Frame %d%s",g_state.frameSequence,g_state.live?L" · LIVE":L"");SetTextColor(dc,g_theme.simBadgeText);TextOutW(dc,badge.left+8,badge.top+8,st,WLen(st));}
        if(g_state.zones){
            HGDIOBJ gp=SelectObject(dc,g_grid);for(int k=1;k<3;k++){int xx=dx+dw*k/3,yy=dy+dh*k/3;MoveToEx(dc,xx,dy,0);LineTo(dc,xx,dy+dh);MoveToEx(dc,dx,yy,0);LineTo(dc,dx+dw,yy);}SelectObject(dc,gp);
            SetTextColor(dc,RGB(255,220,90));for(int z=0;z<9;z++)if(g_state.zoneCount[z]){int zx=z%3,zy=z/3;wchar_t v[48];FormatD(g_state.zone[z],2,v);lstrcatW(v,L" px");TextOutW(dc,dx+zx*dw/3+8,dy+zy*dh/3+8,v,WLen(v));}
        }
        if(g_state.stars){
            HGDIOBJ hollow=SelectObject(dc,GetStockObject(NULL_BRUSH));int labels=0,starCount=ClampI(g_state.starArrayCount,0,160);
            for(int i=0;i<starCount;i++){
                if(!ValidStarOverlayPoint(i))continue;
                int fx=ClampI((int)(g_state.starX[i]+0.5),0,g_frameW-1),fy=ClampI((int)(g_state.starY[i]+0.5),0,g_frameH-1);
                int xx=dx+(int)(((long long)fx*dw)/g_frameW),yy=dy+(int)(((long long)fy*dh)/g_frameH);int rr=(int)(g_state.starFwhm[i]*sc*1.7);rr=ClampI(rr,4,18);
                xx=ClampI(xx,dx,dx+dw-1);yy=ClampI(yy,dy,dy+dh-1);
                HPEN pen=(i==g_state.selectedStar)?g_curve:((g_state.starSaturated[i]&&g_state.saturation)?g_bad:(g_state.starUsed[i]?g_good:g_grid));HGDIOBJ oldp=SelectObject(dc,pen);Ellipse(dc,xx-rr,yy-rr,xx+rr+1,yy+rr+1);
                if(i==g_state.selectedStar){MoveToEx(dc,xx-rr-5,yy,0);LineTo(dc,xx+rr+5,yy);MoveToEx(dc,xx,yy-rr-5,0);LineTo(dc,xx,yy+rr+5);}SelectObject(dc,oldp);
                if(g_state.values&&labels<50){wchar_t v[32];FormatD(g_state.starFwhm[i],1,v);SetTextColor(dc,(g_state.starSaturated[i]&&g_state.saturation)?RGB(255,105,95):(g_state.starUsed[i]?RGB(120,235,160):RGB(190,205,225)));TextOutW(dc,xx+rr+3,yy-8,v,WLen(v));labels++;}
            }
            SelectObject(dc,hollow);
            if(g_state.starsCount>0&&g_state.starArrayCount==0){SetTextColor(dc,RGB(255,185,70));TextOutW(dc,dx+12,dy+52,L"Overlaydaten fehlen – Statusübertragung prüfen",42);}
        }
        if(!g_state.stars&&g_state.manualStarLocked&&ValidStarOverlayPoint(g_state.selectedStar)){
            int i=g_state.selectedStar,fx=ClampI((int)(g_state.starX[i]+0.5),0,g_frameW-1),fy=ClampI((int)(g_state.starY[i]+0.5),0,g_frameH-1),xx=dx+(int)(((long long)fx*dw)/g_frameW),yy=dy+(int)(((long long)fy*dh)/g_frameH);xx=ClampI(xx,dx,dx+dw-1);yy=ClampI(yy,dy,dy+dh-1);int rr=(int)(g_state.starFwhm[i]*sc*1.7);rr=ClampI(rr,5,18);HGDIOBJ hollow=SelectObject(dc,GetStockObject(NULL_BRUSH)),oldp=SelectObject(dc,g_curve);Ellipse(dc,xx-rr,yy-rr,xx+rr+1,yy+rr+1);MoveToEx(dc,xx-rr-5,yy,0);LineTo(dc,xx+rr+5,yy);MoveToEx(dc,xx,yy-rr-5,0);LineTo(dc,xx,yy+rr+5);SelectObject(dc,oldp);SelectObject(dc,hollow);
        }
    }else{SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_font);SetTextColor(dc,g_theme.previewMessage);RECT t=inner;LPCWSTR msg=L"Kamera verbinden und Live-Fokus starten";if(g_state.frameReady&&g_frameFetchFailures>0)msg=L"Livebild wurde erzeugt, konnte aber nicht geladen werden";else if(g_state.live&&g_state.camera)msg=L"Simulatoraufnahme läuft – erstes Livebild wird geladen …";DrawTextW(dc,msg,-1,&t,DT_CENTER|DT_VCENTER|DT_SINGLELINE);}
}
static int PlotX(int pos,int pmin,int pmax,int l,int r){if(pmax<=pmin)return l;return l+(int)(((double)(pos-pmin)*(double)(r-l))/(double)(pmax-pmin));}
static int PlotY(double v,double ymin,double ymax,int t,int b){if(ymax<=ymin)return b;return b-(int)(((v-ymin)*(double)(b-t))/(ymax-ymin));}
#include "autofocus_chart_math.inc"
static DWORD AfMixColor(DWORD a,DWORD b,int bPercent){
    if(bPercent<0)bPercent=0;if(bPercent>100)bPercent=100;int aPercent=100-bPercent;
    int ar=(int)(a&255),ag=(int)((a>>8)&255),ab=(int)((a>>16)&255);
    int br=(int)(b&255),bg=(int)((b>>8)&255),bb=(int)((b>>16)&255);
    return RGB((ar*aPercent+br*bPercent)/100,(ag*aPercent+bg*bPercent)/100,(ab*aPercent+bb*bPercent)/100);
}
static void DrawAfCross(HDC dc,int x,int y,int radius){MoveToEx(dc,x-radius,y-radius,0);LineTo(dc,x+radius+1,y+radius+1);MoveToEx(dc,x-radius,y+radius,0);LineTo(dc,x+radius+1,y-radius-1);}
static LPCWSTR AutofocusCompactModelName(){
    if(g_state.afFitModel==1&&g_state.afFitFwhmModel==1)return L"Gewichtete robuste Parabel";
    if(g_state.afFitModel==2&&g_state.afFitFwhmModel==2)return L"Symmetrische Hyperbel";
    if(g_state.afFitModel==3&&g_state.afFitFwhmModel==3)return L"Geneigte Hyperbel";
    if(g_state.afFitModel>0&&g_state.afFitFwhmModel>0)return L"Hybridmodell";
    return L"–";
}
static void DrawAutofocusSummary(HDC dc){
    int panelW=g_afSummary.right-g_afSummary.left,panelH=g_afSummary.bottom-g_afSummary.top;
    if(panelW<250||panelH<220)return;
    DrawPanel(dc,g_afSummary,L"FIT-ERGEBNIS");
    SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);
    int left=g_afSummary.left+14,right=g_afSummary.right-14;
    int innerW=right-left;
    int labelW=ClampI((innerW*43)/100,116,148),valueX=left+labelW+12;
    int spacious=panelH>=280;
    int y=g_afSummary.top+(spacious?38:30);
    int bottom=g_afSummary.bottom-(spacious?12:8);
    wchar_t value[224],sigma[32],loo[32],quality[32],chi[32],r2h[24],r2f[24];
    FormatD(g_state.afFocusSigma,1,sigma);FormatD(g_state.afFocusSigmaLoo,1,loo);FormatD(g_state.afCurveQuality,2,quality);FormatD(g_state.afReducedChi2,2,chi);FormatD(g_state.afFitR2,2,r2h);FormatD(g_state.afFitFwhmR2,2,r2f);

    int leadRowH;
    if(spacious){
        const int labelH=20,valueH=24,sectionGap=7;
        SelectObject(dc,g_small);SetTextColor(dc,g_theme.textMuted);RECT bl={left,y,right,y+labelH};DrawTextW(dc,L"Beste Fokusposition",-1,&bl,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=labelH;
        wsprintfW(value,L"%d ± %s Schritte",g_state.afBestPosition,sigma);SelectObject(dc,g_font);SetTextColor(dc,g_theme.accent);RECT bv={left,y,right,y+valueH};DrawTextW(dc,value,-1,&bv,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=valueH+sectionGap;

        SelectObject(dc,g_small);SetTextColor(dc,g_theme.textMuted);RECT ml={left,y,right,y+labelH};DrawTextW(dc,L"Modell",-1,&ml,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=labelH;
        SetTextColor(dc,g_theme.textPrimary);RECT mv={left,y,right,y+valueH};DrawTextW(dc,AutofocusCompactModelName(),-1,&mv,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=valueH+sectionGap;
        leadRowH=0;
    }else{
        int available=bottom-y;
        leadRowH=available/10;
        if(leadRowH<18)leadRowH=18;
        if(leadRowH>22)leadRowH=22;
        SelectObject(dc,g_small);SetTextColor(dc,g_theme.textMuted);RECT bl={left,y,right,y+leadRowH};DrawTextW(dc,L"Beste Fokusposition",-1,&bl,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=leadRowH;
        wsprintfW(value,L"%d ± %s Schritte",g_state.afBestPosition,sigma);SetTextColor(dc,g_theme.accent);RECT bv={left,y,right,y+leadRowH};DrawTextW(dc,value,-1,&bv,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=leadRowH;
        SetTextColor(dc,g_theme.textMuted);RECT ml={left,y,right,y+leadRowH};DrawTextW(dc,L"Modell",-1,&ml,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=leadRowH;
        SetTextColor(dc,g_theme.textPrimary);RECT mv={left,y,right,y+leadRowH};DrawTextW(dc,AutofocusCompactModelName(),-1,&mv,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=leadRowH;
    }

    int controlValueW=right-valueX;
    BOOL stackControl=controlValueW<276;
    int remaining=bottom-y;
    int rowCount=stackControl?7:6;
    int rowH=remaining/rowCount;
    if(rowH>30)rowH=30;
    if(rowH<(spacious?20:18))rowH=spacious?20:18;
#define DRAW_AF_RESULT_ROW(label,textValue) do{ \
        SelectObject(dc,g_small);SetTextColor(dc,g_theme.textMuted);RECT lr={left,y,valueX-6,y+rowH};DrawTextW(dc,label,-1,&lr,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX); \
        SetTextColor(dc,g_theme.textPrimary);RECT vr={valueX,y,right,y+rowH};DrawTextW(dc,textValue,-1,&vr,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=rowH; \
    }while(0)
    wsprintfW(value,L"H/F %s / %s",r2h,r2f);DRAW_AF_RESULT_ROW(L"R²",value);
    DRAW_AF_RESULT_ROW(L"Kurvenqualität",quality);
    wsprintfW(value,L"%s / ± %s",chi,loo);DRAW_AF_RESULT_ROW(L"χ²red / LOO",value);
    wsprintfW(value,L"%d / %d",g_state.afFitInliers,g_state.afFitOutliers);DRAW_AF_RESULT_ROW(L"Inlier / Ausreißer",value);
    wsprintfW(value,L"%d",g_state.afAdaptiveSamplesAdded);DRAW_AF_RESULT_ROW(L"Zusatzaufnahmen",value);
    if(g_state.afFinalValid){wchar_t fh[24],ff[24];FormatD(g_state.afFinalHfr,2,fh);FormatD(g_state.afFinalFwhm,2,ff);wsprintfW(value,L"%d · HFR %s · FWHM %s",g_state.afFinalPosition,fh,ff);}else lstrcpyW(value,L"steht noch aus");
    if(stackControl){
        SelectObject(dc,g_small);SetTextColor(dc,g_theme.textMuted);RECT lr={left,y,right,y+rowH};DrawTextW(dc,L"Kontrollmessung",-1,&lr,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);y+=rowH;
        SetTextColor(dc,g_theme.textPrimary);RECT vr={left,y,right,y+rowH};DrawTextW(dc,value,-1,&vr,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);
    }else DRAW_AF_RESULT_ROW(L"Kontrollmessung",value);
#undef DRAW_AF_RESULT_ROW
    (void)leadRowH;
}

static void DrawAutofocusLegend(HDC dc){
    int panelW=g_afLegend.right-g_afLegend.left,panelH=g_afLegend.bottom-g_afLegend.top;
    if(panelW<150||panelH<140)return;
    DrawPanel(dc,g_afLegend,L"LEGENDE");
    SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);
    int symbolX=g_afLegend.left+16,textX=symbolX+34,right=g_afLegend.right-14;
    int y=g_afLegend.top+38;
    int rowH=(g_afLegend.bottom-12-y)/5;
    if(rowH>28)rowH=28;
    if(rowH<20)rowH=20;
#define DRAW_AF_LEGEND_TEXT(color,label) do{RECT tr={textX,y,right,y+rowH};SetTextColor(dc,color);DrawTextW(dc,label,-1,&tr,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);}while(0)
    int cy=y+rowH/2;
    HGDIOBJ oldPen=SelectObject(dc,g_good);MoveToEx(dc,symbolX,cy,0);LineTo(dc,symbolX+24,cy);Ellipse(dc,symbolX+8,cy-5,symbolX+18,cy+5);SelectObject(dc,oldPen);DRAW_AF_LEGEND_TEXT(g_theme.successText,L"HFR grün");y+=rowH;
    cy=y+rowH/2;oldPen=SelectObject(dc,g_curve);MoveToEx(dc,symbolX,cy,0);LineTo(dc,symbolX+24,cy);Ellipse(dc,symbolX+7,cy-6,symbolX+19,cy+6);SelectObject(dc,oldPen);DRAW_AF_LEGEND_TEXT(g_theme.accent,L"FWHM blau");y+=rowH;
    cy=y+rowH/2;oldPen=SelectObject(dc,g_marker);MoveToEx(dc,symbolX+12,cy-7,0);LineTo(dc,symbolX+12,cy+7);MoveToEx(dc,symbolX+7,cy-7,0);LineTo(dc,symbolX+17,cy-7);MoveToEx(dc,symbolX+7,cy+7,0);LineTo(dc,symbolX+17,cy+7);SelectObject(dc,oldPen);DRAW_AF_LEGEND_TEXT(g_theme.textPrimary,L"Fehler ±1σ");y+=rowH;
    cy=y+rowH/2;oldPen=SelectObject(dc,g_bad);DrawAfCross(dc,symbolX+12,cy,7);SelectObject(dc,oldPen);DRAW_AF_LEGEND_TEXT(g_theme.errorText,L"Ausreißer");y+=rowH;
    cy=y+rowH/2;HGDIOBJ oldBrush=SelectObject(dc,GetStockObject(NULL_BRUSH));oldPen=SelectObject(dc,g_curve);Rectangle(dc,symbolX+6,cy-7,symbolX+19,cy+7);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);DRAW_AF_LEGEND_TEXT(g_theme.textPrimary,L"Kontrolle");
#undef DRAW_AF_LEGEND_TEXT
}

static void DrawAutofocusChart(HDC dc){
    DrawAutofocusSummary(dc);
    DrawAutofocusLegend(dc);
    AfChartLayout layout;if(!AfChartComputeLayout(g_afChart.left,g_afChart.top,g_afChart.right,g_afChart.bottom,&layout))return;
    RECT plot={layout.plotLeft,layout.plotTop,layout.plotRight,layout.plotBottom};
    RECT axis={layout.plotLeft,layout.axisTop,layout.plotRight,layout.axisBottom};
    RECT residual={layout.plotLeft,layout.residualTop,layout.plotRight,layout.residualBottom};
    int measured=g_state.afMeasuredCount,n=g_state.afCount;if(n>15)n=15;if(measured>n)measured=n;if(measured<0)measured=0;
    SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);SetTextColor(dc,g_theme.textSecondary);
    if(n<3||measured<1){
        HGDIOBJ gridPen=SelectObject(dc,g_grid);for(int i=0;i<=4;i++){int yy=plot.top+i*(plot.bottom-plot.top)/4;MoveToEx(dc,plot.left,yy,0);LineTo(dc,plot.right,yy);}for(int i=0;i<=4;i++){int xx=plot.left+i*(plot.right-plot.left)/4;MoveToEx(dc,xx,plot.top,0);LineTo(dc,xx,plot.bottom);}SelectObject(dc,gridPen);
        SetTextColor(dc,g_theme.textMuted);RECT empty={plot.left+12,plot.top+10,plot.right-12,plot.bottom-10};DrawTextW(dc,L"Noch keine vollständige Autofokusmessung",-1,&empty,DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX);return;
    }
    int pmin=g_state.afPos[0],pmax=g_state.afPos[n-1];if(pmax<pmin){int q=pmin;pmin=pmax;pmax=q;}if(pmax<=pmin)return;
    double ymin=1e30,ymax=-1e30;
    for(int i=0;i<measured;i++){
        double hs=g_state.afMetricSigma[i]>0.0?g_state.afMetricSigma[i]:0.0,fs=g_state.afFwhmSigma[i]>0.0?g_state.afFwhmSigma[i]:0.0;
        if(g_state.afMetric[i]>0.0){double lo=g_state.afMetric[i]-hs,hi=g_state.afMetric[i]+hs;if(lo<ymin)ymin=lo;if(hi>ymax)ymax=hi;}
        if(g_state.afFwhm[i]>0.0){double lo=g_state.afFwhm[i]-fs,hi=g_state.afFwhm[i]+fs;if(lo<ymin)ymin=lo;if(hi>ymax)ymax=hi;}
    }
    for(int k=0;k<=100;k++){
        double pos=pmin+(pmax-pmin)*(double)k/100.0;
        if(g_state.afFitValid){double yv=AfChartEvalModel(g_state.afFitModel,g_state.afFitParams,pos,g_state.afFitCenter,g_state.afFitScale,g_state.afFitA,g_state.afFitB,g_state.afFitC);if(yv>0.0){if(yv<ymin)ymin=yv;if(yv>ymax)ymax=yv;}}
        if(g_state.afFitFwhmValid){double yv=AfChartEvalModel(g_state.afFitFwhmModel,g_state.afFitFwhmParams,pos,g_state.afFitCenter,g_state.afFitScale,g_state.afFitFwhmA,g_state.afFitFwhmB,g_state.afFitFwhmC);if(yv>0.0){if(yv<ymin)ymin=yv;if(yv>ymax)ymax=yv;}}
    }
    if(ymin>=1e29||ymax<=-1e29){ymin=0.0;ymax=1.0;}if(ymax<=ymin)ymax=ymin+1.0;double pad=(ymax-ymin)*0.15;ymin-=pad;if(ymin<0.0)ymin=0.0;ymax+=pad;

    if(g_state.afFitValid&&g_state.afFocusSigma>0.0){
        double lo=(double)g_state.afBestPosition-g_state.afFocusSigma,hi=(double)g_state.afBestPosition+g_state.afFocusSigma;if(lo<pmin)lo=pmin;if(hi>pmax)hi=pmax;
        int lx=PlotX((int)(lo+0.5),pmin,pmax,plot.left,plot.right),hx=PlotX((int)(hi+0.5),pmin,pmax,plot.left,plot.right);if(hx<lx){int tmp=lx;lx=hx;hx=tmp;}
        RECT band={lx,plot.top,hx+1,plot.bottom};HBRUSH bandBrush=CreateSolidBrush(AfMixColor(g_theme.card,g_theme.accent,18));FillRect(dc,&band,bandBrush);DeleteObject(bandBrush);
        HGDIOBJ old=SelectObject(dc,g_threshold);MoveToEx(dc,lx,plot.top,0);LineTo(dc,lx,plot.bottom);MoveToEx(dc,hx,plot.top,0);LineTo(dc,hx,plot.bottom);SelectObject(dc,old);
    }
    HGDIOBJ gridPen=SelectObject(dc,g_grid);for(int i=0;i<=4;i++){int yy=plot.top+i*(plot.bottom-plot.top)/4;MoveToEx(dc,plot.left,yy,0);LineTo(dc,plot.right,yy);}for(int i=0;i<=4;i++){int xx=plot.left+i*(plot.right-plot.left)/4;MoveToEx(dc,xx,plot.top,0);LineTo(dc,xx,plot.bottom);}SelectObject(dc,gridPen);

    wchar_t w[320],q[48];FormatD(ymax,2,q);RECT yTop={g_afChart.left,plot.top-8,plot.left-6,plot.top+12};DrawTextW(dc,q,-1,&yTop,DT_RIGHT|DT_SINGLELINE|DT_NOPREFIX);FormatD(ymin,2,q);RECT yBottom={g_afChart.left,plot.bottom-10,plot.left-6,plot.bottom+10};DrawTextW(dc,q,-1,&yBottom,DT_RIGHT|DT_SINGLELINE|DT_NOPREFIX);
    wsprintfW(w,L"%d",pmin);RECT xLeft={axis.left,axis.top,axis.left+90,axis.bottom};DrawTextW(dc,w,-1,&xLeft,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);wsprintfW(w,L"%d",pmax);RECT xRight={axis.right-90,axis.top,axis.right,axis.bottom};DrawTextW(dc,w,-1,&xRight,DT_RIGHT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);if(layout.detailed){RECT xTitle={axis.left+90,axis.top,axis.right-90,axis.bottom};DrawTextW(dc,L"Fokusposition (Schritte)",-1,&xTitle,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS|DT_NOPREFIX);}

    if(g_state.afFitValid){HGDIOBJ old=SelectObject(dc,g_good);BOOL first=TRUE;for(int k=0;k<=160;k++){double pos=pmin+(pmax-pmin)*(double)k/160.0,yv=AfChartEvalModel(g_state.afFitModel,g_state.afFitParams,pos,g_state.afFitCenter,g_state.afFitScale,g_state.afFitA,g_state.afFitB,g_state.afFitC);int xx=PlotX((int)(pos+0.5),pmin,pmax,plot.left,plot.right),yy=AfChartClampInt(PlotY(yv,ymin,ymax,plot.top,plot.bottom),plot.top,plot.bottom);if(first){MoveToEx(dc,xx,yy,0);first=FALSE;}else LineTo(dc,xx,yy);}SelectObject(dc,old);}
    if(g_state.afFitFwhmValid){HGDIOBJ old=SelectObject(dc,g_curve);BOOL first=TRUE;for(int k=0;k<=160;k++){double pos=pmin+(pmax-pmin)*(double)k/160.0,yv=AfChartEvalModel(g_state.afFitFwhmModel,g_state.afFitFwhmParams,pos,g_state.afFitCenter,g_state.afFitScale,g_state.afFitFwhmA,g_state.afFitFwhmB,g_state.afFitFwhmC);int xx=PlotX((int)(pos+0.5),pmin,pmax,plot.left,plot.right),yy=AfChartClampInt(PlotY(yv,ymin,ymax,plot.top,plot.bottom),plot.top,plot.bottom);if(first){MoveToEx(dc,xx,yy,0);first=FALSE;}else LineTo(dc,xx,yy);}SelectObject(dc,old);}

    HGDIOBJ hollow=SelectObject(dc,GetStockObject(NULL_BRUSH));
    for(int i=0;i<measured;i++){
        int baseX=PlotX(g_state.afPos[i],pmin,pmax,plot.left,plot.right);BOOL out=g_state.afOutlier[i]!=0;
        if(g_state.afMetric[i]>0.0){
            int xx=AfChartClampInt(baseX-3,plot.left+5,plot.right-5),yy=AfChartClampInt(PlotY(g_state.afMetric[i],ymin,ymax,plot.top,plot.bottom),plot.top+1,plot.bottom-1),sy=AfChartDisplayedErrorHalfHeight(g_state.afMetricSigma[i],ymin,ymax,plot.bottom-plot.top,4);HGDIOBJ old=SelectObject(dc,out?g_bad:g_good);
            if(sy>0){int y1=AfChartClampInt(yy-sy,plot.top,plot.bottom),y2=AfChartClampInt(yy+sy,plot.top,plot.bottom);MoveToEx(dc,xx,y1,0);LineTo(dc,xx,y2);MoveToEx(dc,xx-4,y1,0);LineTo(dc,xx+4,y1);MoveToEx(dc,xx-4,y2,0);LineTo(dc,xx+4,y2);}
            if(out)DrawAfCross(dc,xx,yy,7);else Ellipse(dc,xx-4,yy-4,xx+5,yy+5);SelectObject(dc,old);
        }
        if(g_state.afFwhm[i]>0.0){
            int xx=AfChartClampInt(baseX+3,plot.left+6,plot.right-6),yy=AfChartClampInt(PlotY(g_state.afFwhm[i],ymin,ymax,plot.top,plot.bottom),plot.top+1,plot.bottom-1),sy=AfChartDisplayedErrorHalfHeight(g_state.afFwhmSigma[i],ymin,ymax,plot.bottom-plot.top,5);HGDIOBJ old=SelectObject(dc,out?g_bad:g_curve);
            if(sy>0){int y1=AfChartClampInt(yy-sy,plot.top,plot.bottom),y2=AfChartClampInt(yy+sy,plot.top,plot.bottom);MoveToEx(dc,xx,y1,0);LineTo(dc,xx,y2);MoveToEx(dc,xx-4,y1,0);LineTo(dc,xx+4,y1);MoveToEx(dc,xx-4,y2,0);LineTo(dc,xx+4,y2);}
            if(out)DrawAfCross(dc,xx,yy,8);else Ellipse(dc,xx-5,yy-5,xx+6,yy+6);SelectObject(dc,old);
        }
    }
    SelectObject(dc,hollow);
    if(g_state.afFitValid){int bx=PlotX(g_state.afBestPosition,pmin,pmax,plot.left,plot.right);HGDIOBJ old=SelectObject(dc,g_bad);MoveToEx(dc,bx,plot.top,0);LineTo(dc,bx,plot.bottom);SelectObject(dc,old);}

    if(layout.detailed){
        double rm=0.0;for(int i=0;i<measured;i++){double a=AfChartAbs(g_state.afResidual[i]);if(a>rm)rm=a;}if(rm<0.25)rm=0.25;
        const int residualLabelH=19,residualMarkerRadius=3;
        RECT residualLabel={residual.left,residual.top+1,residual.right,residual.top+1+residualLabelH};
        SetTextColor(dc,g_theme.textMuted);DrawTextW(dc,L"Standardisierte HFR-Residuen",-1,&residualLabel,DT_RIGHT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS|DT_NOPREFIX);
        int graphTop=residualLabel.bottom+2,graphBottom=residual.bottom-6;
        if(graphBottom<graphTop+8)graphBottom=graphTop+8;
        int zero=(graphTop+graphBottom)/2;gridPen=SelectObject(dc,g_grid);MoveToEx(dc,residual.left,zero,0);LineTo(dc,residual.right,zero);SelectObject(dc,gridPen);
        int residualAmplitude=(graphBottom-graphTop-2*residualMarkerRadius)/2;if(residualAmplitude<1)residualAmplitude=1;
        for(int i=0;i<measured;i++){int xx=PlotX(g_state.afPos[i],pmin,pmax,residual.left,residual.right),yy=zero-(int)(g_state.afResidual[i]*residualAmplitude/rm);yy=AfChartClampInt(yy,graphTop+residualMarkerRadius,graphBottom-residualMarkerRadius);HGDIOBJ old=SelectObject(dc,g_state.afOutlier[i]?g_bad:g_marker);MoveToEx(dc,xx,zero,0);LineTo(dc,xx,yy);Ellipse(dc,xx-residualMarkerRadius,yy-residualMarkerRadius,xx+residualMarkerRadius+1,yy+residualMarkerRadius+1);SelectObject(dc,old);}
    }

    if(g_state.afFinalValid){int fx=PlotX(g_state.afFinalPosition,pmin,pmax,plot.left,plot.right);HGDIOBJ oldBrush=SelectObject(dc,GetStockObject(NULL_BRUSH));if(g_state.afFinalFwhm>0.0){int fy=AfChartClampInt(PlotY(g_state.afFinalFwhm,ymin,ymax,plot.top,plot.bottom),plot.top+7,plot.bottom-7);HGDIOBJ oldPen=SelectObject(dc,g_curve);Rectangle(dc,fx-7,fy-7,fx+8,fy+8);SelectObject(dc,oldPen);}if(g_state.afFinalHfr>0.0){int hy=AfChartClampInt(PlotY(g_state.afFinalHfr,ymin,ymax,plot.top,plot.bottom),plot.top+6,plot.bottom-6);HGDIOBJ oldPen=SelectObject(dc,g_good);Rectangle(dc,fx-6,hy-6,fx+7,hy+7);SelectObject(dc,oldPen);}SelectObject(dc,oldBrush);}
}
static DWORD FocusLampColor(){if(g_state.focusNeedScore>=85)return g_theme.connectionBad;if(g_state.focusNeedScore>=60)return g_theme.warningText;if(g_state.focusNeedScore>=30)return g_theme.cautionText;return g_theme.connectionGood;}
static void DrawFocusLamp(HDC dc,RECT r,BOOL detailed){
    if(r.right<=r.left||r.bottom<=r.top)return;
    SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);DWORD c=FocusLampColor();
    if(!detailed){HBRUSH lamp=CreateSolidBrush(c);HGDIOBJ oldBrush=SelectObject(dc,lamp),oldPen=SelectObject(dc,g_border);int cy=(r.top+r.bottom)/2;Ellipse(dc,r.left,cy-7,r.left+15,cy+8);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);DeleteObject(lamp);SetTextColor(dc,g_theme.textSecondary);TextOutW(dc,r.left+22,cy-8,g_state.focusNeedLabel[0]?g_state.focusNeedLabel:L"noch keine Bewertung",WLen(g_state.focusNeedLabel[0]?g_state.focusNeedLabel:L"noch keine Bewertung"));return;}
    HBRUSH bg=CreateSolidBrush(g_theme.card);FillRect(dc,&r,bg);DeleteObject(bg);HGDIOBJ oldPen=SelectObject(dc,g_border),oldBrush=SelectObject(dc,GetStockObject(NULL_BRUSH));Rectangle(dc,r.left,r.top,r.right,r.bottom);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);
    SetTextColor(dc,g_theme.textSecondary);RECT title={r.left+12,r.top+8,r.right-12,r.top+30};DrawTextW(dc,L"Autofokus jetzt sinnvoll?",-1,&title,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX);
    HBRUSH lamp=CreateSolidBrush(c);oldBrush=SelectObject(dc,lamp);oldPen=SelectObject(dc,g_border);int cy=r.top+48;Ellipse(dc,r.left+12,cy-8,r.left+29,cy+9);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);DeleteObject(lamp);
    SetTextColor(dc,g_theme.textPrimary);wchar_t line[220];wsprintfW(line,L"%s  ·  %d/100",g_state.focusNeedLabel[0]?g_state.focusNeedLabel:L"noch keine Bewertung",g_state.focusNeedScore);RECT label={r.left+38,cy-11,r.right-12,cy+12};DrawTextW(dc,line,-1,&label,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS|DT_NOPREFIX);
    RECT rr={r.left+12,r.top+68,r.right-12,r.bottom-14};SetTextColor(dc,g_theme.textMuted);DrawTextW(dc,g_state.focusNeedReason[0]?g_state.focusNeedReason:L"Noch keine belastbare Fokusreferenz vorhanden.",-1,&rr,DT_LEFT|DT_WORDBREAK|DT_EDITCONTROL|DT_NOPREFIX);
}
static void DrawTemperatureFocusModel(HDC dc,RECT r){
    if(r.right-r.left<260||r.bottom-r.top<180)return;DrawPanel(dc,r,L"TEMPERATUR → FOKUSPOSITION");
    RECT plot={r.left+62,r.top+50,r.right-20,r.bottom-42};HGDIOBJ oldPen=SelectObject(dc,g_grid);for(int i=0;i<=4;i++){int yy=plot.top+i*(plot.bottom-plot.top)/4;MoveToEx(dc,plot.left,yy,0);LineTo(dc,plot.right,yy);int xx=plot.left+i*(plot.right-plot.left)/4;MoveToEx(dc,xx,plot.top,0);LineTo(dc,xx,plot.bottom);}SelectObject(dc,oldPen);
    int n=g_state.tempProfileArrayCount;if(n<1){SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_font);SetTextColor(dc,g_theme.textMuted);RECT m={plot.left+10,plot.top+20,plot.right-10,plot.bottom-10};DrawTextW(dc,L"Noch keine Temperatur-Fokuspunkte. Erfolgreiche Autofokusläufe mit verfügbarer Fokussierertemperatur bauen das Modell automatisch auf.",-1,&m,DT_LEFT|DT_WORDBREAK);return;}
    double tmin=g_state.tempProfileTemperature[0],tmax=tmin;int pmin=g_state.tempProfilePosition[0],pmax=pmin;for(int i=1;i<n;i++){double tv=g_state.tempProfileTemperature[i];int pv=g_state.tempProfilePosition[i];if(tv<tmin)tmin=tv;if(tv>tmax)tmax=tv;if(pv<pmin)pmin=pv;if(pv>pmax)pmax=pv;}if(tmax-tmin<0.5){tmin-=0.25;tmax+=0.25;}if(pmax-pmin<20){pmin-=10;pmax+=10;}
    if(g_state.tempFitValid){double yv1=g_state.tempSlope*tmin+g_state.tempIntercept,yv2=g_state.tempSlope*tmax+g_state.tempIntercept;int y1=PlotY(yv1,(double)pmin,(double)pmax,plot.top,plot.bottom),y2=PlotY(yv2,(double)pmin,(double)pmax,plot.top,plot.bottom);oldPen=SelectObject(dc,g_curve);MoveToEx(dc,plot.left,y1,0);LineTo(dc,plot.right,y2);SelectObject(dc,oldPen);}
    HBRUSH point=CreateSolidBrush(g_theme.accent);HGDIOBJ ob=SelectObject(dc,point),op=SelectObject(dc,g_border);for(int i=0;i<n;i++){int xp=plot.left+(int)(((g_state.tempProfileTemperature[i]-tmin)/(tmax-tmin))*(plot.right-plot.left));int yp=PlotY((double)g_state.tempProfilePosition[i],(double)pmin,(double)pmax,plot.top,plot.bottom);Ellipse(dc,xp-4,yp-4,xp+5,yp+5);}SelectObject(dc,op);SelectObject(dc,ob);DeleteObject(point);
    SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);SetTextColor(dc,g_theme.textSecondary);wchar_t a[64],b[64],line[180];FormatD(tmin,1,a);FormatD(tmax,1,b);wsprintfW(line,L"%s °C",a);TextOutW(dc,plot.left,plot.bottom+8,line,WLen(line));wsprintfW(line,L"%s °C",b);RECT tr={plot.right-90,plot.bottom+8,plot.right,plot.bottom+30};DrawTextW(dc,line,-1,&tr,DT_RIGHT|DT_SINGLELINE);wsprintfW(line,L"%d",pmax);TextOutW(dc,r.left+18,plot.top-7,line,WLen(line));wsprintfW(line,L"%d",pmin);TextOutW(dc,r.left+18,plot.bottom-7,line,WLen(line));wchar_t slope[48];FormatD(g_state.tempSlope,2,slope);wsprintfW(line,L"%d Punkte · %s Schritte/°C%s",n,slope,g_state.tempFitValid?L" · Regression aktiv":L"");RECT info={r.left+18,r.top+26,r.right-18,r.top+46};DrawTextW(dc,line,-1,&info,DT_RIGHT|DT_SINGLELINE|DT_END_ELLIPSIS);
}
static void DrawAnalysisPage(HDC dc){
    DrawPanel(dc,g_page,L"FOKUSMODELL, VALIDIERUNG UND NACHTSTATISTIK");int pad=18,top=g_page.top+36,bottom=g_page.bottom-16,left=g_page.left+pad,right=g_page.right-pad;int gap=14;int rightW=ClampI((right-left)*34/100,280,330);RECT model={left,top,right-rightW-gap,bottom};RECT stats={model.right+gap,top,right,bottom};DrawTemperatureFocusModel(dc,model);DrawPanel(dc,stats,L"AKTUELLE SESSION");
    int x=stats.left+16,y=stats.top+44;wchar_t w[96];FormatD(g_state.sessionMinutes,0,w);lstrcatW(w,L" min");DrawMetric(dc,x,y,L"Laufzeit",w);y+=28;wsprintfW(w,L"%d / %d",g_state.sessionAfSuccess,g_state.sessionAfAttempts);DrawMetric(dc,x,y,L"AF erfolgreich / gesamt",w);y+=28;wsprintfW(w,L"%d / %d",g_state.sessionAfFailed,g_state.sessionAfRollbacks);DrawMetric(dc,x,y,L"Fehler / Rollbacks",w);y+=28;if(g_state.sessionBestFwhm>0){FormatD(g_state.sessionBestFwhm,2,w);lstrcatW(w,L" px");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"Beste FWHM",w);y+=28;if(g_state.sessionWorstFwhm>0){FormatD(g_state.sessionWorstFwhm,2,w);lstrcatW(w,L" px");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"Schlechteste FWHM",w);y+=28;if(g_state.sessionStartPosition>=0&&g_state.sessionLastPosition>=0){wchar_t signedShift[32];FormatSignedInt(g_state.sessionLastPosition-g_state.sessionStartPosition,signedShift,32);lstrcpyW(w,signedShift);lstrcatW(w,L" Schritte");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"Fokusverschiebung",w);y+=28;if(g_state.sessionHasTemperature){FormatD(g_state.sessionLastTemperature-g_state.sessionStartTemperature,1,w);lstrcatW(w,L" °C");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"Temperaturänderung",w);y+=40;
    SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);SetTextColor(dc,g_state.afValidationPassed?g_theme.successText:(g_state.afRollbackPerformed?g_theme.errorText:g_theme.textMuted));RECT vr={stats.left+16,y,stats.right-16,y+28};DrawTextW(dc,g_state.afValidationState[0]?g_state.afValidationState:L"Noch kein Fokuslauf validiert",-1,&vr,DT_LEFT|DT_SINGLELINE|DT_END_ELLIPSIS);y+=28;SetTextColor(dc,g_theme.textMuted);RECT rr={stats.left+16,y,stats.right-16,stats.bottom-88};DrawTextW(dc,g_state.afValidationReason[0]?g_state.afValidationReason:L"–",-1,&rr,DT_LEFT|DT_WORDBREAK|DT_EDITCONTROL);
    SetTextColor(dc,g_theme.textMuted);RECT api={stats.left+16,stats.bottom-76,stats.right-16,stats.bottom-14};DrawTextW(dc,L"Read-only API für Observatory Center:\r\n127.0.0.1:" AFS_LOCAL_HTTP_PORT_TEXT_W L"/api/v1/status\r\nModell: /api/v1/focus-model",-1,&api,DT_LEFT|DT_WORDBREAK);
}
static void DrawContinuousFocusPage(HDC dc){
    DrawPanel(dc,g_page,L"KONTINUIERLICHE FOKUSNACHFÜHRUNG · KORREKTUREN ZWISCHEN BELICHTUNGEN");
    RECT r=g_cfChart;if(r.right<=r.left||r.bottom<=r.top)return;FillRect(dc,&r,g_panel);HGDIOBJ oldPen=SelectObject(dc,g_border),oldBrush=SelectObject(dc,GetStockObject(NULL_BRUSH));Rectangle(dc,r.left,r.top,r.right,r.bottom);SelectObject(dc,oldPen);SelectObject(dc,oldBrush);SetBkMode(dc,TRANSPARENT);SelectObject(dc,g_small);SetTextColor(dc,g_theme.textSecondary);TextOutW(dc,r.left+12,r.top+10,L"FOKUSPOSITION UND REGELZIEL",WLen(L"FOKUSPOSITION UND REGELZIEL"));
    RECT plot={r.left+54,r.top+42,r.right-20,r.bottom-34};if(plot.right<=plot.left+40||plot.bottom<=plot.top+30)return;
    if(g_cfUiCount<1){SetTextColor(dc,g_theme.textMuted);DrawTextW(dc,L"Noch keine Nachführungsdaten. Live-Fokus, Kamera und Fokussierer müssen aktiv sein.",-1,&plot,DT_CENTER|DT_VCENTER|DT_WORDBREAK);return;}
    int mn=g_cfUi[0].position,mx=g_cfUi[0].position;for(int i=0;i<g_cfUiCount;i++){int a=g_cfUi[i].position,b=g_cfUi[i].target;if(a<mn)mn=a;if(a>mx)mx=a;if(b<mn)mn=b;if(b>mx)mx=b;}int span=mx-mn;if(span<20){int pad=(20-span+1)/2;mn-=pad;mx+=20-span-pad;}else{int pad=span/10+2;mn-=pad;mx+=pad;}span=mx-mn;if(span<1)span=1;
    oldPen=SelectObject(dc,g_grid);for(int i=0;i<=4;i++){int yy=plot.top+i*(plot.bottom-plot.top)/4;MoveToEx(dc,plot.left,yy,0);LineTo(dc,plot.right,yy);int value=mx-(span*i)/4;wchar_t w[32];wsprintfW(w,L"%d",value);SetTextColor(dc,g_theme.textMuted);TextOutW(dc,plot.left-48,yy-8,w,WLen(w));}SelectObject(dc,oldPen);
    auto pointX=[&](int i)->int{return g_cfUiCount<=1?plot.left:plot.left+(i*(plot.right-plot.left))/(g_cfUiCount-1);};
    auto pointY=[&](int v)->int{return plot.bottom-((v-mn)*(plot.bottom-plot.top))/span;};
    oldPen=SelectObject(dc,g_reference);for(int i=0;i<g_cfUiCount;i++){int x=pointX(i),y=pointY(g_cfUi[i].target);if(i==0)MoveToEx(dc,x,y,0);else LineTo(dc,x,y);}SelectObject(dc,oldPen);
    oldPen=SelectObject(dc,g_curve);for(int i=0;i<g_cfUiCount;i++){int x=pointX(i),y=pointY(g_cfUi[i].position);if(i==0)MoveToEx(dc,x,y,0);else LineTo(dc,x,y);}SelectObject(dc,oldPen);
    for(int i=0;i<g_cfUiCount;i++)if(g_cfUi[i].correction){int x=pointX(i),y=pointY(g_cfUi[i].position);oldPen=SelectObject(dc,g_marker);MoveToEx(dc,x,y-8,0);LineTo(dc,x,y+9);SelectObject(dc,oldPen);}
    SetTextColor(dc,g_theme.textSecondary);wchar_t legend[320],confidence[32],error[32],drift[32];FormatD(g_state.continuousFocusConfidence,1,confidence);FormatD(g_state.continuousFocusEstimatedError,1,error);FormatD(g_state.continuousFocusDriftStepsPerMinute,2,drift);wsprintfW(legend,L"Position %d · Ziel %d · Abweichung %s Schritte · Drift %s Schritte/min · Regelqualität %s %% · Korrekturen %d/%d",g_state.position,g_state.continuousFocusTarget,error,drift,confidence,g_state.continuousFocusAccepted,g_state.continuousFocusRejected);RECT lr={plot.left,r.bottom-27,plot.right,r.bottom-6};DrawTextW(dc,legend,-1,&lr,DT_LEFT|DT_SINGLELINE|DT_END_ELLIPSIS);
}
static void PaintCharts(HDC dc){if(g_activeTab==0){DrawFocusTrend(dc);}
    else if(g_activeTab==1){DrawPanel(dc,g_page,L"AUTOFOKUS · BEIDSEITIG VERMESSENES MINIMUM");DrawAutofocusChart(dc);}
    else if(g_activeTab==2)DrawPanel(dc,g_page,L"BAHTINOV-FOKUSHILFE");else if(g_activeTab==3)DrawPanel(dc,g_page,L"PROTOKOLL UND EXPORT");else if(g_activeTab==4){DrawPanel(dc,g_page,L"AUTOMATISIERUNG UND SICHERHEIT");DrawFocusLamp(dc,g_focusLamp,TRUE);}else if(g_activeTab==5)DrawContinuousFocusPage(dc);else if(g_activeTab==6)DrawAnalysisPage(dc);else DrawPanel(dc,g_page,L"SYNTHETISCHE TESTS");}
static void PaintRight(HDC dc){DrawPanel(dc,g_rightAnalysis,L"AKTUELLE ANALYSE");wchar_t w[96];int x=g_rightAnalysis.left+16,y=g_rightAnalysis.top+44;FormatD(g_state.fwhm,2,w);lstrcatW(w,L" px");DrawMetric(dc,x,y,L"Median-FWHM",w);y+=28;FormatD(g_state.hfr,2,w);lstrcatW(w,L" px");DrawMetric(dc,x,y,L"Median-HFR",w);y+=28;wsprintfW(w,L"%d / %d",g_state.usedStars,g_state.starsCount);DrawMetric(dc,x,y,L"Verwendete Sterne",w);y+=28;FormatD(g_state.snr,1,w);DrawMetric(dc,x,y,L"SNR (Median)",w);y+=28;FormatD(g_state.ecc,2,w);DrawMetric(dc,x,y,L"Exzentrizität",w);y+=28;FormatD(g_state.stability,2,w);DrawMetric(dc,x,y,L"Stabilität",w);
DrawPanel(dc,g_rightStar,g_state.manualStarLocked?(g_state.afUseSelectedStar?L"FOKUSSTERN · MANUELL · AF":L"FOKUSSTERN · MANUELL"):L"FOKUSSTERN · AUTOMATISCH");x=g_rightStar.left+16;y=g_rightStar.top+44;if(g_state.selectedStar>=0){FormatD(g_state.selectedFwhm,2,w);lstrcatW(w,L" px");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"FWHM",w);y+=28;if(g_state.selectedStar>=0){FormatD(g_state.selectedHfr,2,w);lstrcatW(w,L" px");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"HFR",w);y+=28;if(g_state.selectedStar>=0)FormatD(g_state.selectedSnr,1,w);else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"SNR",w);y+=28;if(g_state.selectedStar>=0)FormatD(g_state.selectedEcc,2,w);else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"Exzentrizität",w);SelectObject(dc,g_small);SetTextColor(dc,g_theme.textMuted);LPCWSTR mode=g_state.afUseSelectedStar?L"Autofokus-Metrik: dieser Stern":L"Autofokus-Metrik: Feldmedian";if(g_state.manualStarLocked&&g_state.selectedStar<0){SetTextColor(dc,g_theme.errorText);mode=L"Fokusstern im aktuellen Frame nicht erkannt";}RECT modeRect={x,g_rightStar.top+156,g_rightStar.right-14,g_rightStar.bottom-10};DrawTextW(dc,mode,-1,&modeRect,DT_LEFT|DT_WORDBREAK|DT_EDITCONTROL);
DrawPanel(dc,g_rightTrend,L"FOKUS-STATUS");{RECT lamp={g_rightTrend.left+116,g_rightTrend.top+5,g_rightTrend.right-8,g_rightTrend.top+34};DrawFocusLamp(dc,lamp,FALSE);}x=g_rightTrend.left+16;y=g_rightTrend.top+44;wsprintfW(w,L"%d",g_state.position);DrawMetric(dc,x,y,L"Position",w);y+=28;if(g_state.hasTemperature){FormatD(g_state.temperature,1,w);lstrcatW(w,L" °C");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"Temperatur",w);y+=28;if(g_state.bahtValid){FormatD(g_state.bahtOffset,2,w);lstrcatW(w,L" px");}else lstrcpyW(w,L"–");DrawMetric(dc,x,y,L"Bahtinov-Offset",w);y+=28;if(g_state.autofocus)lstrcpyW(w,L"läuft");else if(g_state.afFinalValid)lstrcpyW(w,L"erfolgreich bestätigt");else lstrcpyW(w,L"bereit");DrawMetric(dc,x,y,L"Autofokus",w);y+=28;if(g_state.autofocus){wsprintfW(w,L"%d / %d",g_state.afRecenterCount,g_state.afExpansionCount);DrawMetric(dc,x,y,L"Zentriert / erweitert",w);}else if(g_state.afFinalValid){FormatD(g_state.afFinalFwhm,2,w);lstrcatW(w,L" px");DrawMetric(dc,x,y,L"AF-Ende FWHM",w);y+=28;FormatD(g_state.afFinalHfr,2,w);lstrcatW(w,L" px");DrawMetric(dc,x,y,L"AF-Ende HFR",w);}
DrawPanel(dc,g_rightField,L"BILDFELD · MEDIAN FWHM");int gx=g_rightField.left+14,gy=g_rightField.top+42,gw=g_rightField.right-g_rightField.left-28,gh=g_rightField.bottom-g_rightField.top-54;HGDIOBJ op=SelectObject(dc,g_grid);for(int i=1;i<3;i++){int xx=gx+i*gw/3,yy=gy+i*gh/3;MoveToEx(dc,xx,gy,0);LineTo(dc,xx,gy+gh);MoveToEx(dc,gx,yy,0);LineTo(dc,gx+gw,yy);}SelectObject(dc,op);for(int z=0;z<9;z++){int zx=z%3,zy=z/3;if(g_state.zoneCount[z])FormatD(g_state.zone[z],2,w);else lstrcpyW(w,L"–");TextOutW(dc,gx+zx*gw/3+8,gy+zy*gh/3+8,w,WLen(w));}}
static void Paint(HDC dc){SetFrontendPhase("paint background");RECT rc;GetClientRect(g_main,&rc);FillRect(dc,&rc,g_bg);RECT header={0,0,rc.right,72};FillRect(dc,&header,g_panel);SelectObject(dc,g_title);SetBkMode(dc,TRANSPARENT);SetTextColor(dc,g_theme.title);TextOutW(dc,18,22,AFS_FRONTEND_TITLE_W,WLen(AFS_FRONTEND_TITLE_W));DrawPanel(dc,g_leftCamera,L"KAMERA");DrawDeviceConnectionLamp(dc,g_leftCamera,g_state.camera);DrawPanel(dc,g_leftFocuser,L"FOKUSSIERER");DrawDeviceConnectionLamp(dc,g_leftFocuser,g_state.focuser);SetFrontendPhase("paint preview");PaintPreview(dc);SetFrontendPhase("paint charts");PaintCharts(dc);SetFrontendPhase("paint right panels");PaintRight(dc);SetFrontendPhase("idle");}

static BOOL ApplyAutoRefocusToggle(BOOL desired){
    BOOL previous=g_state.autoRefocus;Check(hAutoRefocus,desired);
    if(!ApiToggle("autoRefocus",desired)){Check(hAutoRefocus,previous);return FALSE;}
    // Keep the accepted value visible immediately. A status poll is used as a verification,
    // not as an opportunity for an older state to erase the user's click.
    g_state.autoRefocus=desired;Check(hAutoRefocus,desired);
    if(!PollStatus())return TRUE;
    if(g_state.autoRefocus==desired)return TRUE;
    // A second exact request covers a stale/foreign engine response. Only after two
    // contradictory confirmations is the checkbox restored to the engine-reported state.
    if(ApiToggle("autoRefocus",desired)&&PollStatus()&&g_state.autoRefocus==desired)return TRUE;
    Check(hAutoRefocus,g_state.autoRefocus);return FALSE;
}
static int EditInt(HWND h,int def){wchar_t w[80];char a[160];GetText(h,w,80);WToA(w,a,160);if(!a[0])return def;return atoi(a);}static BOOL SaveCapture(){BOOL ok=TRUE;ok=ApiSetInt("exposure",hExposure)&&ok;ok=ApiSetInt("gain",hGain)&&ok;return ok;} static BOOL SaveAf(){wchar_t error[256];if(!ValidateAutofocusInputs(error,256)){UpdateAutofocusInputState();return FALSE;}BOOL ok=TRUE;ok=ApiSetInt("afPoints",hAfPoints)&&ok;ok=ApiSetInt("afStep",hAfStep)&&ok;ok=ApiSetInt("afSamples",hAfSamples)&&ok;ok=ApiSetInt("backlash",hBacklash)&&ok;ok=ApiToggle("preferredOut",Checked(hPrefOut))&&ok;return ok;} static BOOL SaveAdv(){int mn=EditInt(hSafeMin,-1),mx=EditInt(hSafeMax,-1);if(mn<0||mx<=mn){MessageBoxW(g_main,L"Die sichere Fokuszone ist ungültig. Das Maximum muss größer als das nichtnegative Minimum sein.",L"Sichere Fokuszone",MB_OK|MB_ICONWARNING);return FALSE;}BOOL ok=ApiSetInt("refocusMinutes",hRefocusMin)&&ApiSetInt("refocusTemp",hRefocusTemp)&&ApiSetInt("refocusFwhmPercent",hRefocusFwhm)&&ApiSetInt("refocusBadFrames",hRefocusBadFrames)&&ApiSetInt("refocusMinStars",hRefocusMinStars)&&ApiSetInt("refocusStability",hRefocusStability)&&ApiSetInt("refocusCooldown",hRefocusCooldown);if(mn>=g_state.safeMax)ok=ApiSetInt("safeMax",hSafeMax)&&ApiSetInt("safeMin",hSafeMin)&&ok;else ok=ApiSetInt("safeMin",hSafeMin)&&ApiSetInt("safeMax",hSafeMax)&&ok;ok=ApplyAutoRefocusToggle(Checked(hAutoRefocus))&&ok;ok=ApiToggle("tempComp",Checked(hTempComp))&&ok;ok=ApiToggle("autoStartPosition",Checked(hAutoStartPos))&&ok;ok=ApiToggle("refocusOnMeridian",Checked(hEvtMeridian))&&ok;ok=ApiToggle("refocusOnReconnect",Checked(hEvtReconnect))&&ok;ok=ApiToggle("refocusOnFilter",Checked(hEvtFilter))&&ok;ok=ApiSetInt("refocusEveryCaptures",hRefocusCaptures)&&ok;if(!ok)MessageBoxW(g_main,L"Die Einstellungen konnten nicht vollständig an die Engine übertragen oder bestätigt werden.",L"Engine-Kommunikation",MB_OK|MB_ICONERROR);return ok;}
static BOOL SaveContinuousFocus(){
    unsigned minFrames=0,deadband=0,maxStep=0,confidence=0,settle=0;double improvement=0.0;
    if(!ReadUiUInt(hCfMinFrames,&minFrames)||minFrames<3||minFrames>12){MessageBoxW(g_main,L"Messfenster muss zwischen 3 und 12 Bildern liegen.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);return FALSE;}
    if(!ReadUiUInt(hCfDeadband,&deadband)||deadband<1||deadband>1000){MessageBoxW(g_main,L"Totzone muss zwischen 1 und 1000 Schritten liegen.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);return FALSE;}
    if(!ReadUiUInt(hCfMaxStep,&maxStep)||maxStep<deadband||maxStep>5000){MessageBoxW(g_main,L"Die maximale Korrektur muss mindestens der Totzone entsprechen und höchstens 5000 Schritte betragen.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);return FALSE;}
    if(!ReadUiUInt(hCfConfidence,&confidence)||confidence<30||confidence>100){MessageBoxW(g_main,L"Mindest-Regelqualität muss zwischen 30 und 100 Prozent liegen.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);return FALSE;}
    if(!ReadUiDouble(hCfImprovement,&improvement)||improvement<0.1||improvement>25.0){MessageBoxW(g_main,L"Mindestverbesserung muss zwischen 0,1 und 25 Prozent liegen.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);return FALSE;}
    if(!ReadUiUInt(hCfSettle,&settle)||settle<100||settle>30000){MessageBoxW(g_main,L"Beruhigungszeit muss zwischen 100 und 30000 ms liegen.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);return FALSE;}
    int mode=ComboSel(hCfMode);if(mode<0||mode>2)mode=2;wchar_t v[64],improvementText[64];GetText(hCfImprovement,improvementText,64);BOOL ok=TRUE;wsprintfW(v,L"%d",mode);ok=ApiSetW("continuousFocusMode",v)&&ok;ok=ApiSetInt("continuousFocusMinFrames",hCfMinFrames)&&ok;ok=ApiSetInt("continuousFocusDeadband",hCfDeadband)&&ok;ok=ApiSetInt("continuousFocusMaxStep",hCfMaxStep)&&ok;ok=ApiSetInt("continuousFocusConfidence",hCfConfidence)&&ok;ok=ApiSetW("continuousFocusImprovement",improvementText)&&ok;ok=ApiSetInt("continuousFocusSettleMs",hCfSettle)&&ok;ok=ApiToggle("continuousFocusFallback",Checked(hCfFallback))&&ok;ok=ApiToggle("continuousFocus",Checked(hCfEnable))&&ok;
    if(!ok)MessageBoxW(g_main,L"Die Nachführungseinstellungen konnten nicht vollständig an die Engine übertragen oder bestätigt werden.",L"Fokusnachführung",MB_OK|MB_ICONERROR);return ok;
}
static int CameraBackendFromState(){if(g_state.simulator)return 0;if(g_state.external)return 1;if(g_state.native)return 2;return 3;}
static int FocuserBackendFromState(){return g_state.simulator?0:1;}
static void ApplyBackendSelectors(){
    if(g_cameraBackendSelection<0)g_cameraBackendSelection=CameraBackendFromState();
    if(g_focuserBackendSelection<0)g_focuserBackendSelection=FocuserBackendFromState();
    ComboSelect(hCamBackend,g_cameraBackendSelection);ComboSelect(hFocBackend,g_focuserBackendSelection);
    BOOL u=g_cameraBackendSelection==1;EnableWindow(hCamRefresh,u);EnableWindow(hCamDevice,u);EnableWindow(hCamSelect,g_ascomChooserProcess==0);SetText(hCamSelect,u?L"Eigenschaften":(g_cameraBackendSelection==3?L"ASCOM auswählen":(g_cameraBackendSelection==2?L"SDK/Kamera suchen":L"Simulator")));BOOL ascomFoc=g_focuserBackendSelection==1;SetText(hFocSelect,ascomFoc?L"ASCOM auswählen":L"Simulator");EnableWindow(hFocSelect,ascomFoc&&g_ascomChooserProcess==0);
}
static void CameraBackendChanged(){
    int requested=ComboSel(hCamBackend),previous=g_cameraBackendSelection>=0?g_cameraBackendSelection:CameraBackendFromState();
    if(requested<0||requested>3){ApplyBackendSelectors();return;}if(requested==previous){ApplyBackendSelectors();return;}
    char trace[96];sprintf(trace,"camera backend request previous=%d requested=%d",previous,requested);AppendFrontendTrace(trace);
    BOOL disconnected=TRUE;if(g_uvcProcess||g_state.external)disconnected=StopUvc();else if(g_state.camera&&!g_state.simulator)disconnected=ApiAction("camera-connect");
    if(!disconnected){g_cameraBackendSelection=previous;ApplyBackendSelectors();MessageBoxW(g_main,L"Die aktive Kamera konnte vor dem Backendwechsel nicht sauber getrennt werden.",L"Backendwechsel abgebrochen",MB_OK|MB_ICONERROR);PollStatus();return;}
    BOOL ok=TRUE;if(requested==0)ok=ApiToggle("simulator",TRUE);else{ok=ApiToggle("simulator",FALSE);if(ok)ok=ApiToggle("native",requested==2);}
    if(!ok){ApiToggle("simulator",previous==0);if(previous!=0)ApiToggle("native",previous==2);g_cameraBackendSelection=previous;ApplyBackendSelectors();MessageBoxW(g_main,L"Das Kamerabackend wurde von der Engine nicht vollständig übernommen. Die Auswahl wurde zurückgesetzt.",L"Backendwechsel fehlgeschlagen",MB_OK|MB_ICONERROR);PollStatus();return;}
    g_cameraBackendSelection=requested;if(requested==0)g_focuserBackendSelection=0;else{g_lastNonSimulatorCameraBackend=requested;g_focuserBackendSelection=1;}ApplyBackendSelectors();PollStatus();if(requested==3&&!LooksLikeAscomProgId(g_state.cameraName))StartAscomChooser(TRUE);AppendFrontendTrace("camera backend selection committed");
}
static void FocBackendChanged(){
    int requested=ComboSel(hFocBackend),previous=g_focuserBackendSelection>=0?g_focuserBackendSelection:FocuserBackendFromState();
    if(requested<0||requested>1){ApplyBackendSelectors();return;}if(requested==previous){ApplyBackendSelectors();return;}
    char trace[96];sprintf(trace,"focuser backend request previous=%d requested=%d",previous,requested);AppendFrontendTrace(trace);
    BOOL ok=TRUE;if(requested==0){if(g_uvcProcess||g_state.external)ok=StopUvc();if(ok)ok=ApiToggle("simulator",TRUE);}else{ok=ApiToggle("simulator",FALSE);if(ok){int cam=g_lastNonSimulatorCameraBackend;if(cam<1||cam>3)cam=3;ok=ApiToggle("native",cam==2);}}
    if(!ok){ApiToggle("simulator",previous==0);g_focuserBackendSelection=previous;ApplyBackendSelectors();MessageBoxW(g_main,L"Das Fokussiererbackend wurde von der Engine nicht übernommen. Die Auswahl wurde zurückgesetzt.",L"Backendwechsel fehlgeschlagen",MB_OK|MB_ICONERROR);PollStatus();return;}
    g_focuserBackendSelection=requested;if(requested==0)g_cameraBackendSelection=0;else{if(g_lastNonSimulatorCameraBackend<1||g_lastNonSimulatorCameraBackend>3)g_lastNonSimulatorCameraBackend=3;g_cameraBackendSelection=g_lastNonSimulatorCameraBackend;}ApplyBackendSelectors();PollStatus();if(requested==1&&!LooksLikeAscomProgId(g_state.focuserName))StartAscomChooser(FALSE);AppendFrontendTrace("focuser backend selection committed");
}
static void CameraConnect(){
    int b=ComboSel(hCamBackend);if(b==3&&!LooksLikeAscomProgId(g_state.cameraName)){StartAscomChooser(TRUE);return;}
    BOOL ok=FALSE;if(b==1)ok=g_state.external?StopUvc():StartUvc();else ok=ApiAction("camera-connect");
    if(!ok&&b==2&&!g_lastApiTransportFailure&&WTextContains(g_lastApiMessage,L"toupcam.dll")){
        int answer=MessageBoxW(g_main,L"Die 64-Bit-toupcam.dll wurde nicht gefunden oder ist inkompatibel. Möchtest du die passende DLL jetzt auswählen?",L"ToupTek-SDK auswählen",MB_YESNO|MB_ICONINFORMATION);
        if(answer==IDYES){if(ConfigureToupTekSdkPath())ok=ApiAction("camera-connect");else if(g_toupTekPickerCancelled){PollStatus();return;}}
    }
    if(!ok){wchar_t msg[900];if(g_lastApiMessage[0])lstrcpyW(msg,g_lastApiMessage);else lstrcpyW(msg,b==3?L"Die ASCOM-Kamera konnte nicht verbunden werden.":L"Die Kameraaktion ist fehlgeschlagen.");MessageBoxW(g_main,msg,L"Kameraverbindung",MB_OK|MB_ICONERROR);PollStatus();return;}PollStatus();
}
static void CameraSelect(){
    int b=ComboSel(hCamBackend);BOOL ok=FALSE;
    if(b==1)ok=ShowUvcProperties();else if(b==3)ok=StartAscomChooser(TRUE);else if(b==2){ok=ApiAction("camera-select");if(!ok&&!g_lastApiTransportFailure&&WTextContains(g_lastApiMessage,L"toupcam.dll")){if(ConfigureToupTekSdkPath())ok=ApiAction("camera-select");else if(g_toupTekPickerCancelled){PollStatus();return;}}}else ok=ApiAction("camera-select");
    if(!ok&&g_lastApiMessage[0])MessageBoxW(g_main,g_lastApiMessage,L"Kameraauswahl fehlgeschlagen",MB_OK|MB_ICONERROR);else if(!ok)MessageBoxW(g_main,L"Die Kameraauswahl oder die Geräteoptionen konnten nicht geöffnet werden.",L"Kameraauswahl fehlgeschlagen",MB_OK|MB_ICONERROR);PollStatus();
}
static void FocuserSelect(){
    int backend=ComboSel(hFocBackend);
    if(backend==0){
        if(!ApiAction("focuser-select"))MessageBoxW(g_main,g_lastApiMessage[0]?g_lastApiMessage:L"Die Simulatorauswahl wurde von der Engine abgelehnt.",L"Simulatorauswahl",MB_OK|MB_ICONERROR);
        PollStatus();return;
    }
    StartAscomChooser(FALSE);
}
static void FocuserConnect(){
    int backend=ComboSel(hFocBackend);
    if(backend==0){
        if(!ApiAction("focuser-connect")){
            wchar_t msg[900];if(g_lastApiMessage[0])lstrcpyW(msg,g_lastApiMessage);else lstrcpyW(msg,L"Der synthetische Fokussierer konnte nicht verbunden oder getrennt werden.");
            MessageBoxW(g_main,msg,L"Simulator-Fokussierer",MB_OK|MB_ICONERROR);
        }
        PollStatus();return;
    }
    if(!LooksLikeAscomProgId(g_state.focuserName)){StartAscomChooser(FALSE);return;}
    if(!ApiAction("focuser-connect")){
        wchar_t msg[900];if(g_lastApiMessage[0])lstrcpyW(msg,g_lastApiMessage);else lstrcpyW(msg,L"Der ASCOM-Fokussierer konnte nicht verbunden werden. Prüfe die ausgewählte Treiber-ID, den ASCOM-Treiber und den Engine-Status.");
        MessageBoxW(g_main,msg,L"Verbindung fehlgeschlagen",MB_OK|MB_ICONERROR);
    }
    PollStatus();
}
static BOOL MapPreviewClickToFrame(int mx,int my,int* outX,int* outY){
    if(outX)*outX=-1;if(outY)*outY=-1;if(!g_frame||g_frameW<=0||g_frameH<=0||g_frameW>10000||g_frameH>10000||mx<g_preview.left||mx>=g_preview.right||my<g_preview.top||my>=g_preview.bottom)return FALSE;
    RECT inner={g_preview.left+8,g_preview.top+8,g_preview.right-8,g_preview.bottom-8};int pw=inner.right-inner.left,ph=inner.bottom-inner.top;if(pw<=0||ph<=0)return FALSE;
    double sx=(double)pw/(double)g_frameW,sy=(double)ph/(double)g_frameH,sc=sx<sy?sx:sy;if(!(sc>0.0))return FALSE;int dw=(int)(g_frameW*sc),dh=(int)(g_frameH*sc);if(dw<=0||dh<=0)return FALSE;
    int dx=inner.left+(pw-dw)/2,dy=inner.top+(ph-dh)/2;if(mx<dx||mx>=dx+dw||my<dy||my>=dy+dh)return FALSE;
    int ix=(int)(((long long)(mx-dx)*(long long)g_frameW)/(long long)dw),iy=(int)(((long long)(my-dy)*(long long)g_frameH)/(long long)dh);ix=ClampI(ix,0,g_frameW-1);iy=ClampI(iy,0,g_frameH-1);if(outX)*outX=ix;if(outY)*outY=iy;return TRUE;
}
static void QueueStarSelectionFromClick(int mx,int my){
    int ix=-1,iy=-1;if(!MapPreviewClickToFrame(mx,my,&ix,&iy))return;
    // Never perform blocking network I/O inside WM_LBUTTONDOWN. The previous synchronous
    // path could nest status updates and paint/control notifications on the mouse stack.
    g_pendingStarX=ix;g_pendingStarY=iy;
    if(!g_starSelectionQueued&&!g_starSelectionBusy&&!g_commandBusy){g_starSelectionQueued=TRUE;if(!PostMessageW(g_main,WM_APP_SELECT_STAR,0,0)){g_starSelectionQueued=FALSE;AppendFrontendTrace("select-star PostMessage failed");}}
}
static void ExecuteQueuedStarSelection(){
    if(g_starSelectionBusy||g_commandBusy)return;SetFrontendPhase("star selection request");g_starSelectionQueued=FALSE;
    int ix=g_pendingStarX,iy=g_pendingStarY;g_pendingStarX=g_pendingStarY=-1;
    if(ix<0||iy<0)return;g_starSelectionBusy=TRUE;AppendFrontendTrace("select-star request begin");
    char path[256];int n=sprintf(path,"/api/action?name=select-star&x=%d&y=%d",ix,iy);
    BOOL ok=n>0&&n<(int)sizeof(path)&&ApiPath(path);if(!ok)LogLine(L"An der Klickposition wurde kein geeigneter Fokusstern fixiert.");
    // Do not nest a second HTTP/status parse and repaint inside the selection callback. The
    // regular timer performs the refresh after this message has fully unwound.
    g_statusRefreshRequested=TRUE;AppendFrontendTrace(ok?"select-star request complete":"select-star request rejected");g_starSelectionBusy=FALSE;
    if(g_pendingStarX>=0&&g_pendingStarY>=0&&!g_starSelectionQueued){g_starSelectionQueued=TRUE;if(!PostMessageW(g_main,WM_APP_SELECT_STAR,0,0))g_starSelectionQueued=FALSE;}SetFrontendPhase("idle");
}
static void CreateControls(){hViewLabel=Add(L"STATIC",L"Ansicht",SS_LEFT|SS_CENTERIMAGE,0);hViewMode=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_TABSTOP,ID_VIEW_MODE);ComboAdd(hViewMode,L"Basis");ComboAdd(hViewMode,L"Experte");ComboSelect(hViewMode,g_expertMode?1:0);hThemeLabel=Add(L"STATIC",L"Design",SS_LEFT|SS_CENTERIMAGE,0);hTheme=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_TABSTOP,ID_THEME);ComboAdd(hTheme,L"System");ComboAdd(hTheme,L"Hell");ComboAdd(hTheme,L"Dunkel");ComboSelect(hTheme,g_themeMode);hProfileLabel=Add(L"STATIC",L"Profil",SS_LEFT|SS_CENTERIMAGE,0);hProfile=Add(L"COMBOBOX",L"Standardprofil",CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_TABSTOP,ID_PROFILE);hLoadProfile=Add(L"BUTTON",L"Laden",BS_PUSHBUTTON|WS_TABSTOP,ID_LOAD_PROFILE);hSaveProfile=Add(L"BUTTON",L"Speichern",BS_PUSHBUTTON|WS_TABSTOP,ID_SAVE_PROFILE);hDeleteProfile=Add(L"BUTTON",L"Löschen",BS_PUSHBUTTON|WS_TABSTOP,ID_DELETE_PROFILE);hImportProfile=Add(L"BUTTON",L"Import",BS_PUSHBUTTON|WS_TABSTOP,ID_IMPORT_PROFILE);hExportProfile=Add(L"BUTTON",L"Export",BS_PUSHBUTTON|WS_TABSTOP,ID_EXPORT_PROFILE);
 hCamGroup=0;hCamLabels[0]=Add(L"STATIC",L"Backend",SS_LEFT|SS_CENTERIMAGE,0);hCamLabels[1]=Add(L"STATIC",L"Gerät",SS_LEFT|SS_CENTERIMAGE,0);hCamLabels[2]=Add(L"STATIC",L"Belichtung [ms]",SS_LEFT|SS_CENTERIMAGE,0);hCamLabels[3]=Add(L"STATIC",L"Gain",SS_LEFT|SS_CENTERIMAGE,0);hCamBackend=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_TABSTOP,ID_CAMERA_BACKEND);ComboAdd(hCamBackend,L"Simulator");ComboAdd(hCamBackend,L"USB/UVC (DirectShow)");ComboAdd(hCamBackend,L"ToupTek SDK");ComboAdd(hCamBackend,L"ASCOM Kamera");ComboSelect(hCamBackend,0);hCamDevice=Add(L"COMBOBOX",L"",CBS_DROPDOWN|CBS_AUTOHSCROLL|WS_TABSTOP,ID_CAMERA_DEVICE);hCamRefresh=Add(L"BUTTON",L"Suchen",BS_PUSHBUTTON|WS_TABSTOP,ID_CAMERA_REFRESH);hCamSelect=Add(L"BUTTON",L"Optionen",BS_PUSHBUTTON|WS_TABSTOP,ID_CAMERA_SELECT);hCamConnect=Add(L"BUTTON",L"Verbinden",BS_DEFPUSHBUTTON|WS_TABSTOP,ID_CAMERA_CONNECT);hExposure=Add(L"EDIT",L"800",WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER,ID_EXPOSURE);hGain=Add(L"EDIT",L"180",WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER,ID_GAIN);hLive=Add(L"BUTTON",L"Live-Fokus starten/stoppen",BS_DEFPUSHBUTTON|WS_TABSTOP,ID_LIVE);hStretch=Add(L"BUTTON",L"Auto-Stretch",BS_AUTOCHECKBOX|WS_TABSTOP,ID_STRETCH);hStars=Add(L"BUTTON",L"Sterne",BS_AUTOCHECKBOX|WS_TABSTOP,ID_STARS);hValues=0;hSaturation=Add(L"BUTTON",L"Sättigung",BS_AUTOCHECKBOX|WS_TABSTOP,ID_SATURATION);hZones=Add(L"BUTTON",L"9-Zonen",BS_AUTOCHECKBOX|WS_TABSTOP,ID_ZONES);
 hFocGroup=0;{const wchar_t* fl[7]={L"Backend",L"Gerät",L"Position",L"Temperatur",L"Schritt",L"Minimum",L"Maximum"};for(int i=0;i<7;i++)hFocLabels[i]=Add(L"STATIC",fl[i],SS_LEFT|SS_CENTERIMAGE,0);}hFocBackend=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_TABSTOP,ID_FOCUSER_BACKEND);ComboAdd(hFocBackend,L"Simulator");ComboAdd(hFocBackend,L"ASCOM Fokussierer");ComboSelect(hFocBackend,0);hFocDevice=Add(L"EDIT",L"",WS_BORDER|ES_READONLY,ID_FOCUSER_DEVICE);hFocSelect=Add(L"BUTTON",L"ASCOM auswählen",BS_PUSHBUTTON|WS_TABSTOP,ID_FOCUSER_SELECT);hFocConnect=Add(L"BUTTON",L"Verbinden",BS_PUSHBUTTON|WS_TABSTOP,ID_FOCUSER_CONNECT);hFocSetup=Add(L"BUTTON",L"Kalibrierung / Treibereinstellungen",BS_PUSHBUTTON|WS_TABSTOP,ID_FOCUSER_SETUP);hPosition=Add(L"STATIC",L"–",SS_LEFT|SS_CENTERIMAGE,0);hTemperature=Add(L"STATIC",L"–",SS_LEFT|SS_CENTERIMAGE,0);hManualStep=Add(L"EDIT",L"100",WS_BORDER|ES_AUTOHSCROLL,ID_MANUAL_STEP);hMoveIn=Add(L"BUTTON",L"Innen",BS_PUSHBUTTON|WS_TABSTOP,ID_MOVE_IN);hMoveOut=Add(L"BUTTON",L"Außen",BS_PUSHBUTTON|WS_TABSTOP,ID_MOVE_OUT);hHalt=Add(L"BUTTON",L"Stopp",BS_PUSHBUTTON|WS_TABSTOP,ID_HALT);hSafeMin=Add(L"EDIT",L"0",WS_BORDER|ES_AUTOHSCROLL,ID_SAFE_MIN);hSafeMax=Add(L"EDIT",L"60000",WS_BORDER|ES_AUTOHSCROLL,ID_SAFE_MAX);
 const wchar_t* tabs[8]={L"Live",L"Autofokus",L"Bahtinov",L"Protokoll",L"Automatik",L"Nachführung",L"Analyse",L"Tests"};const UINT tabIds[8]={ID_TAB_LIVE,ID_TAB_AUTO,ID_TAB_BAHT,ID_TAB_LOG,ID_TAB_AUTOMATION,ID_TAB_CONTINUOUS,ID_TAB_ANALYSIS,ID_TAB_TESTS};for(int i=0;i<8;i++)hTabs[i]=Add(L"BUTTON",tabs[i],BS_PUSHBUTTON|WS_TABSTOP,tabIds[i]);
 const wchar_t* labs[4]={L"Messpunkte",L"Schrittweite",L"Samples",L"Backlash"};for(int i=0;i<4;i++)hAfLabels[i]=Add(L"STATIC",labs[i],SS_LEFT|SS_CENTERIMAGE,0);hAfPoints=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP,ID_AF_POINTS);ComboAdd(hAfPoints,L"5");ComboAdd(hAfPoints,L"7");ComboAdd(hAfPoints,L"9");ComboAdd(hAfPoints,L"11");ComboAdd(hAfPoints,L"13");ComboAdd(hAfPoints,L"15");ComboSelect(hAfPoints,2);hAfStep=Add(L"EDIT",L"120",WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER,ID_AF_STEP);hAfSamples=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP,ID_AF_SAMPLES);for(int sample=1;sample<=5;sample++){wchar_t sv[4];wsprintfW(sv,L"%d",sample);ComboAdd(hAfSamples,sv);}ComboSelect(hAfSamples,2);hBacklash=Add(L"EDIT",L"250",WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER,ID_BACKLASH);hPrefOut=Add(L"BUTTON",L"Finale Annäherung nach außen",BS_AUTOCHECKBOX|WS_TABSTOP,ID_PREF_OUT);hAfUseSelected=Add(L"BUTTON",L"Gewählten Fokusstern verwenden",BS_AUTOCHECKBOX|WS_TABSTOP,ID_AF_USE_SELECTED);hAfClearSelected=Add(L"BUTTON",L"Stern lösen",BS_PUSHBUTTON|WS_TABSTOP,ID_AF_CLEAR_SELECTED);hAfHint=Add(L"STATIC",L"Stern im Livebild anklicken; blaues Fadenkreuz = fixiert.",SS_LEFT|SS_CENTERIMAGE,0);hAfDiagnosis=0;hStepAssist=Add(L"BUTTON",L"Schritt-Assistent",BS_PUSHBUTTON|WS_TABSTOP,ID_STEP_ASSIST);hBacklashCal=Add(L"BUTTON",L"Backlash automatisch kalibrieren",BS_PUSHBUTTON|BS_MULTILINE|WS_TABSTOP,ID_BACKLASH_CAL);hAfStart=Add(L"BUTTON",L"Autofokus starten",BS_DEFPUSHBUTTON|WS_TABSTOP,ID_AF_START);hAfStop=Add(L"BUTTON",L"Autofokus abbrechen",BS_PUSHBUTTON|WS_TABSTOP,ID_AF_STOP);
 hBahtEnable=Add(L"BUTTON",L"Bahtinov-Auswertung aktivieren",BS_AUTOCHECKBOX|WS_TABSTOP,ID_BAHT_ENABLE);hBahtText=Add(L"STATIC",L"Einen hellen Stern im Livebild anklicken. Offset, Konfidenz und Schärfescore werden rechts angezeigt.",SS_LEFT,0);
 hDiag=Add(L"BUTTON",L"Diagnose speichern",BS_PUSHBUTTON|WS_TABSTOP,ID_DIAGNOSTICS);hExport=Add(L"BUTTON",L"CSV/SVG exportieren",BS_PUSHBUTTON|WS_TABSTOP,ID_EXPORT);hLog=Add(L"EDIT",L"Bereit.",WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|ES_READONLY|WS_VSCROLL,0);Font(hLog,g_mono);
 hAutoRefocus=Add(L"BUTTON",L"Auto-Refokus aktivieren",BS_AUTOCHECKBOX|WS_TABSTOP,ID_AUTO_REFOCUS);hAutoLabels[0]=Add(L"STATIC",L"Intervall [min]",SS_LEFT|SS_CENTERIMAGE,0);hAutoLabels[1]=Add(L"STATIC",L"Temperatur Δ [°C]",SS_LEFT|SS_CENTERIMAGE,0);hAutoLabels[2]=Add(L"STATIC",L"FWHM-Grenze [%]",SS_LEFT|SS_CENTERIMAGE,0);hAutoLabels[3]=Add(L"STATIC",L"Schlechte Bilder",SS_LEFT|SS_CENTERIMAGE,0);hAutoLabels[4]=Add(L"STATIC",L"Mindeststerne",SS_LEFT|SS_CENTERIMAGE,0);hAutoLabels[5]=Add(L"STATIC",L"Stabilität [px]",SS_LEFT|SS_CENTERIMAGE,0);hAutoLabels[6]=Add(L"STATIC",L"Sperrzeit [min]",SS_LEFT|SS_CENTERIMAGE,0);hRefocusMin=Add(L"EDIT",L"60",WS_BORDER|ES_AUTOHSCROLL,ID_REFOCUS_MIN);hRefocusTemp=Add(L"EDIT",L"1,5",WS_BORDER|ES_AUTOHSCROLL,ID_REFOCUS_TEMP);hRefocusFwhm=Add(L"EDIT",L"30",WS_BORDER|ES_AUTOHSCROLL,ID_REFOCUS_FWHM);hRefocusBadFrames=Add(L"EDIT",L"3",WS_BORDER|ES_AUTOHSCROLL,ID_REFOCUS_BAD_FRAMES);hRefocusMinStars=Add(L"EDIT",L"4",WS_BORDER|ES_AUTOHSCROLL,ID_REFOCUS_MIN_STARS);hRefocusStability=Add(L"EDIT",L"0,45",WS_BORDER|ES_AUTOHSCROLL,ID_REFOCUS_STABILITY);hRefocusCooldown=Add(L"EDIT",L"10",WS_BORDER|ES_AUTOHSCROLL,ID_REFOCUS_COOLDOWN);hRefocusResume=Add(L"BUTTON",L"Auto-Refokus freigeben",BS_PUSHBUTTON|BS_MULTILINE|WS_TABSTOP,ID_REFOCUS_RESUME);hSaveAdv=Add(L"BUTTON",L"Einstellungen speichern",BS_PUSHBUTTON|BS_MULTILINE|WS_TABSTOP,ID_SAVE_ADV);hAutomationInfo=Add(L"EDIT",L"Auto-Refokus-Status wird geladen …",WS_BORDER|ES_LEFT|ES_MULTILINE|ES_AUTOVSCROLL|ES_READONLY|WS_VSCROLL,0);Font(hAutomationInfo,g_small);SendMessageW(hAutomationInfo,EM_SETMARGINS,EC_LEFTMARGIN|EC_RIGHTMARGIN,MAKELPARAM(8,8));hAutomationDetailsToggle=Add(L"BUTTON",L"Details anzeigen",BS_PUSHBUTTON|WS_TABSTOP,ID_AUTOMATION_DETAILS);hTempComp=Add(L"BUTTON",L"Temperaturkompensation",BS_AUTOCHECKBOX|WS_TABSTOP,ID_TEMP_COMP);hAutoStartPos=Add(L"BUTTON",L"Automatische Startposition",BS_AUTOCHECKBOX|WS_TABSTOP,ID_AUTO_START_POS);hEvtMeridian=Add(L"BUTTON",L"Refokus nach Meridian-Flip",BS_AUTOCHECKBOX|WS_TABSTOP,ID_EVT_MERIDIAN);hEvtReconnect=Add(L"BUTTON",L"Refokus nach Reconnect",BS_AUTOCHECKBOX|WS_TABSTOP,ID_EVT_RECONNECT);hEvtFilter=Add(L"BUTTON",L"Refokus bei Filterwechsel",BS_AUTOCHECKBOX|WS_TABSTOP,ID_EVT_FILTER);hSmartLabel=Add(L"STATIC",L"Refokus nach Aufnahmen",SS_LEFT|SS_CENTERIMAGE,0);hRefocusCaptures=Add(L"EDIT",L"0",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,ID_REFOCUS_CAPTURES);hFilterName=Add(L"EDIT",L"",WS_BORDER|ES_AUTOHSCROLL,ID_FILTER_NAME);hFilterLearn=Add(L"BUTTON",L"Offset lernen",BS_PUSHBUTTON|WS_TABSTOP,ID_FILTER_LEARN);hFilterApply=Add(L"BUTTON",L"Offset anwenden",BS_PUSHBUTTON|WS_TABSTOP,ID_FILTER_APPLY);
 hCfEnable=Add(L"BUTTON",L"Kontinuierliche Fokusnachführung aktivieren",BS_AUTOCHECKBOX|WS_TABSTOP,ID_CF_ENABLE);hCfMode=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_TABSTOP,ID_CF_MODE);ComboAdd(hCfMode,L"Prädiktiv");ComboAdd(hCfMode,L"Bildbasiert");ComboAdd(hCfMode,L"Hybrid");ComboSelect(hCfMode,2);hCfFallback=Add(L"BUTTON",L"Bei geringer Sicherheit vollständigen Autofokus auslösen",BS_AUTOCHECKBOX|WS_TABSTOP,ID_CF_FALLBACK);
 hCfLabels[0]=Add(L"STATIC",L"Messfenster [Bilder]",SS_LEFT|SS_CENTERIMAGE,0);hCfLabels[1]=Add(L"STATIC",L"Totzone [Schritte]",SS_LEFT|SS_CENTERIMAGE,0);hCfLabels[2]=Add(L"STATIC",L"Max. Korrektur",SS_LEFT|SS_CENTERIMAGE,0);hCfLabels[3]=Add(L"STATIC",L"Mindestqualität [%]",SS_LEFT|SS_CENTERIMAGE,0);hCfLabels[4]=Add(L"STATIC",L"Verbesserung [%]",SS_LEFT|SS_CENTERIMAGE,0);hCfLabels[5]=Add(L"STATIC",L"Beruhigung [ms]",SS_LEFT|SS_CENTERIMAGE,0);hCfMinFrames=Add(L"EDIT",L"4",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,ID_CF_MIN_FRAMES);hCfDeadband=Add(L"EDIT",L"3",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,ID_CF_DEADBAND);hCfMaxStep=Add(L"EDIT",L"12",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,ID_CF_MAX_STEP);hCfConfidence=Add(L"EDIT",L"75",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,ID_CF_CONFIDENCE);hCfImprovement=Add(L"EDIT",L"1,5",WS_BORDER|ES_AUTOHSCROLL,ID_CF_IMPROVEMENT);hCfSettle=Add(L"EDIT",L"700",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,ID_CF_SETTLE);hCfSave=Add(L"BUTTON",L"Einstellungen speichern",BS_PUSHBUTTON|BS_MULTILINE|WS_TABSTOP,ID_CF_SAVE);hCfReset=Add(L"BUTTON",L"Referenz neu aufbauen",BS_PUSHBUTTON|BS_MULTILINE|WS_TABSTOP,ID_CF_RESET);hCfResume=Add(L"BUTTON",L"Nachführung freigeben",BS_PUSHBUTTON|BS_MULTILINE|WS_TABSTOP,ID_CF_RESUME);hCfInfo=Add(L"EDIT",L"Nachführungsstatus wird geladen …",WS_BORDER|ES_LEFT|ES_MULTILINE|ES_AUTOVSCROLL|ES_READONLY|WS_VSCROLL,0);Font(hCfInfo,g_small);SendMessageW(hCfInfo,EM_SETMARGINS,EC_LEFTMARGIN|EC_RIGHTMARGIN,MAKELPARAM(8,8));hCfNote=Add(L"STATIC",L"Korrekturen erfolgen ausschließlich zwischen normalen Belichtungen. Während einer laufenden Hauptbelichtung wird der Fokussierer nie bewegt. Eine separate Guide-/ONAG-Echtzeitquelle ist in " AFS_VERSION_TEXT_W L" noch nicht gekoppelt.",SS_LEFT,0);
 hSimLabels[0]=Add(L"STATIC",L"Simulatorprofil",SS_LEFT|SS_CENTERIMAGE,0);hSimLabels[1]=Add(L"STATIC",L"Mechanisches Backlash",SS_LEFT|SS_CENTERIMAGE,0);hSimProfile=Add(L"COMBOBOX",L"",CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP,ID_SIM_PROFILE);const wchar_t* simProfiles[9]={L"Normal / Referenz",L"Wenige Sterne",L"Stark defokussiert",L"Schlechtes Seeing",L"Stark schwankendes Seeing",L"Dünne Wolken / Transparenz",L"Elongierte Sterne",L"Schwierige Nacht",L"Zufällig bei Simulatorstart"};for(int i=0;i<9;i++)ComboAdd(hSimProfile,simProfiles[i]);ComboSelect(hSimProfile,8);hSimBacklash=Add(L"EDIT",L"250",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL,ID_SIM_BACKLASH);hSimApply=Add(L"BUTTON",L"Simulation übernehmen",BS_PUSHBUTTON|WS_TABSTOP,ID_SIM_APPLY);hSimRandomize=Add(L"BUTTON",L"Neu zufällig laden",BS_PUSHBUTTON|WS_TABSTOP,ID_SIM_RANDOMIZE);hSimProfileInfo=Add(L"STATIC",L"Simulatorstatus wird geladen …",SS_LEFT,0);
 hSelfTest=Add(L"BUTTON",L"Synthetische Tests starten",BS_DEFPUSHBUTTON|WS_TABSTOP,ID_SELFTEST);hTestResult=Add(L"STATIC",L"Noch nicht ausgeführt",SS_LEFT|SS_CENTERIMAGE,0);hTestInfo=Add(L"STATIC",L"Die Tests prüfen Sternanalyse, alle acht Kameraprofile, Defokus-Reaktion, Rauschen, Sättigung, Tilt, Autofokus, mechanisches Backlash und die Kalibrierungsanzeige.",SS_LEFT,0);hStatus=Add(L"STATIC",L"Engine wird gestartet …",SS_LEFT|SS_CENTERIMAGE,0);UpdatePage();}
static LRESULT HandleUiCommand(UINT id,UINT code){SetFrontendPhase("UI command");char commandTrace[96];sprintf(commandTrace,"WM_COMMAND id=%d code=%d",id,code);AppendFrontendTrace(commandTrace);int tabIndex=TabIndexFromId(id);if(tabIndex>=0){g_activeTab=tabIndex;if(g_layoutClientWidth>0&&g_layoutClientHeight>0)Layout(g_layoutClientWidth,g_layoutClientHeight);else UpdatePage();AppendFrontendTrace("tab selection complete");return 0;}if(id==ID_VIEW_MODE&&code==CBN_SELCHANGE){g_expertMode=ComboSel(hViewMode)!=0;if(!g_expertMode&&g_activeTab>=4)g_activeTab=0;if(g_layoutClientWidth>0&&g_layoutClientHeight>0)Layout(g_layoutClientWidth,g_layoutClientHeight);else UpdatePage();AppendFrontendTrace(g_expertMode?"expert view enabled":"basic view enabled");return 0;}if(id==ID_THEME&&code==CBN_SELCHANGE){g_themeMode=NormalizeThemeMode(ComboSel(hTheme));RefreshTheme(TRUE);return 0;}if(id==ID_CAMERA_BACKEND&&code==CBN_SELCHANGE){CameraBackendChanged();return 0;}if(id==ID_FOCUSER_BACKEND&&code==CBN_SELCHANGE){FocBackendChanged();return 0;}if(code==BN_CLICKED||code==0){switch(id){case ID_CAMERA_REFRESH:if(!EnumerateUvc())MessageBoxW(g_main,L"Keine DirectShow-Kamera gefunden. Prüfe die USB-Verbindung und installiere bei Bedarf FFmpeg über das beiliegende Installationsskript.",L"USB-Kameras",MB_OK|MB_ICONWARNING);break;case ID_CAMERA_SELECT:CameraSelect();break;case ID_CAMERA_CONNECT:CameraConnect();break;case ID_FOCUSER_SELECT:FocuserSelect();break;case ID_FOCUSER_CONNECT:FocuserConnect();break;case ID_FOCUSER_SETUP:BeginFocuserSetup();break;case ID_LIVE:if(!SaveCapture()||!ApiAction("live"))MessageBoxW(g_main,L"Live-Fokus konnte nicht gestartet oder beendet werden. Belichtungswerte und Engine-Status prüfen.",L"Live-Fokus fehlgeschlagen",MB_OK|MB_ICONERROR);PollStatus();break;case ID_MOVE_IN:if(!ApiSetInt("manualStep",hManualStep)||!ApiAction("move-in"))MessageBoxW(g_main,L"Die Fokusbewegung nach innen wurde nicht ausgeführt.",L"Fokusbewegung fehlgeschlagen",MB_OK|MB_ICONERROR);PollStatus();break;case ID_MOVE_OUT:if(!ApiSetInt("manualStep",hManualStep)||!ApiAction("move-out"))MessageBoxW(g_main,L"Die Fokusbewegung nach außen wurde nicht ausgeführt.",L"Fokusbewegung fehlgeschlagen",MB_OK|MB_ICONERROR);PollStatus();break;case ID_HALT:if(!ApiAction("halt"))MessageBoxW(g_main,L"Es war keine aktive Fokusbewegung vorhanden oder die Engine ist nicht erreichbar.",L"Stopp nicht ausgeführt",MB_OK|MB_ICONWARNING);PollStatus();break;case ID_STRETCH:if(!ApiToggle("stretch",Checked(hStretch)))Check(hStretch,g_state.stretch);break;case ID_STARS:if(!ApiToggle("stars",Checked(hStars)))Check(hStars,g_state.stars);break;case ID_VALUES:if(!ApiToggle("values",Checked(hValues)))Check(hValues,g_state.values);break;case ID_SATURATION:if(!ApiToggle("saturation",Checked(hSaturation)))Check(hSaturation,g_state.saturation);break;case ID_ZONES:if(!ApiToggle("zones",Checked(hZones)))Check(hZones,g_state.zones);break;case ID_PREF_OUT:if(!ApiToggle("preferredOut",Checked(hPrefOut)))Check(hPrefOut,g_state.preferredOut);break;case ID_AF_USE_SELECTED:if(!ApiToggle("afSelectedStar",Checked(hAfUseSelected)))Check(hAfUseSelected,g_state.afUseSelectedStar);PollStatus();break;case ID_AF_CLEAR_SELECTED:if(!ApiAction("clear-star"))MessageBoxW(g_main,L"Die Fokussternauswahl konnte nicht aufgehoben werden.",L"Aktion fehlgeschlagen",MB_OK|MB_ICONWARNING);PollStatus();break;case ID_STEP_ASSIST:if(!SaveCapture()||!SaveAf())MessageBoxW(g_main,L"Die Aufnahme- oder Fokusparameter konnten nicht vollständig gespeichert werden. Der Schritt-Assistent wurde nicht gestartet.",L"Einstellungen nicht übernommen",MB_OK|MB_ICONERROR);else if(!ApiAction("step-assist"))MessageBoxW(g_main,L"Der Schritt-Assistent konnte nicht gestartet werden. Gerätestatus und Engine-Meldung prüfen.",L"Schritt-Assistent fehlgeschlagen",MB_OK|MB_ICONERROR);PollStatus();break;case ID_BACKLASH_CAL:if(!SaveCapture()||!SaveAf()||!ApiAction("backlash-calibrate"))MessageBoxW(g_main,L"Die automatische Backlash-Kalibrierung konnte nicht gestartet werden.",L"Backlash-Kalibrierung",MB_OK|MB_ICONWARNING);PollStatus();break;case ID_AF_START:{wchar_t inputError[256];if(!ValidateAutofocusInputs(inputError,256)){wchar_t inputMsg[420];lstrcpyW(inputMsg,L"Autofokus kann mit den aktuellen Eingaben nicht gestartet werden.\r\n\r\n");lstrcatW(inputMsg,inputError);MessageBoxW(g_main,inputMsg,L"Autofokusparameter prüfen",MB_OK|MB_ICONWARNING);UpdateAutofocusInputState();break;}if(MessageBoxW(g_main,L"Autofokus mit den eingestellten Messpunkten jetzt starten?",L"Autofokus starten",MB_YESNO|MB_ICONINFORMATION)==IDYES){if(!ApiStartAutofocusAtomic()){PollStatus();wchar_t msg[1200];wsprintfW(msg,L"%s%s%s%s%s",g_state.autofocusErrorTitle[0]?g_state.autofocusErrorTitle:L"Autofokus konnte nicht gestartet werden",g_state.autofocusErrorDetail[0]?L"\r\n\r\n":L"",g_state.autofocusErrorDetail,g_state.autofocusErrorCode[0]?L"\r\n\r\nFehlercode: ":L"",g_state.autofocusErrorCode);MessageBoxW(g_main,msg,L"Autofokusdiagnose",MB_OK|MB_ICONERROR);}}PollStatus();break;}case ID_AF_STOP:if(!ApiAction("autofocus-stop"))MessageBoxW(g_main,L"Es ist kein Autofokuslauf aktiv oder die Engine ist nicht erreichbar.",L"Autofokus nicht abgebrochen",MB_OK|MB_ICONWARNING);PollStatus();break;case ID_BAHT_ENABLE:if(!ApiToggle("bahtinov",Checked(hBahtEnable)))Check(hBahtEnable,g_state.bahtinov);break;case ID_DIAGNOSTICS:if(ApiAction("diagnostics"))LogLine(L"Diagnosebericht gespeichert.");else LogLine(L"Diagnosebericht konnte nicht gespeichert werden. Schreibrechte und Engine-Status prüfen.");break;case ID_EXPORT:if(ApiAction("export"))LogLine(L"CSV/SVG-Bericht gespeichert.");else LogLine(L"CSV/SVG-Bericht konnte nicht gespeichert werden. Schreibrechte, Messdaten und Engine-Status prüfen.");break;case ID_AUTO_REFOCUS:if(!ApplyAutoRefocusToggle(Checked(hAutoRefocus)))MessageBoxW(g_main,L"Auto-Refokus konnte nicht zuverlässig an die Engine übertragen und bestätigt werden.",L"Auto-Refokus",MB_OK|MB_ICONERROR);break;case ID_TEMP_COMP:if(!ApiToggle("tempComp",Checked(hTempComp)))Check(hTempComp,g_state.tempCompEnabled);break;case ID_AUTO_START_POS:if(!ApiToggle("autoStartPosition",Checked(hAutoStartPos)))Check(hAutoStartPos,g_state.autoStartPositionEnabled);break;case ID_EVT_MERIDIAN:if(!ApiToggle("refocusOnMeridian",Checked(hEvtMeridian)))Check(hEvtMeridian,g_state.refocusOnMeridian);break;case ID_EVT_RECONNECT:if(!ApiToggle("refocusOnReconnect",Checked(hEvtReconnect)))Check(hEvtReconnect,g_state.refocusOnReconnect);break;case ID_EVT_FILTER:if(!ApiToggle("refocusOnFilter",Checked(hEvtFilter)))Check(hEvtFilter,g_state.refocusOnFilter);break;case ID_FILTER_LEARN:if(!ApiNamedAction("filter-learn",hFilterName))MessageBoxW(g_main,L"Der Filteroffset konnte nicht gelernt werden. Fokussierer verbinden und Filtername eingeben.",L"Filteroffset",MB_OK|MB_ICONWARNING);PollStatus();break;case ID_FILTER_APPLY:if(!ApiNamedAction("filter-apply",hFilterName))MessageBoxW(g_main,L"Für diesen Filter ist noch kein Offset gelernt.",L"Filteroffset",MB_OK|MB_ICONINFORMATION);PollStatus();break;case ID_SAVE_ADV:if(SaveAdv())LogLine(L"Automatisierungs- und Sicherheitseinstellungen gespeichert.");break;case ID_REFOCUS_RESUME:if(ApiAction("auto-refocus-resume")){LogLine(L"Auto-Refokus wurde wieder freigegeben.");PollStatus();}else MessageBoxW(g_main,L"Auto-Refokus konnte nicht freigegeben werden.",L"Auto-Refokus",MB_OK|MB_ICONWARNING);break;case ID_CF_ENABLE:if(!ApiToggle("continuousFocus",Checked(hCfEnable)))Check(hCfEnable,g_state.continuousFocusEnabled);PollStatus();break;case ID_CF_FALLBACK:if(!ApiToggle("continuousFocusFallback",Checked(hCfFallback)))Check(hCfFallback,g_state.continuousFocusFallback);PollStatus();break;case ID_CF_SAVE:if(SaveContinuousFocus()){LogLine(L"Kontinuierliche Fokusnachführung gespeichert.");PollStatus();}break;case ID_CF_RESET:if(ApiAction("continuous-focus-reset")){g_cfUiCount=0;g_cfUiLastFrame=-1;LogLine(L"Nachführungsreferenz wird neu aufgebaut.");PollStatus();}else MessageBoxW(g_main,L"Die Nachführungsreferenz konnte nicht zurückgesetzt werden.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);break;case ID_CF_RESUME:if(ApiAction("continuous-focus-resume")){LogLine(L"Kontinuierliche Fokusnachführung wurde freigegeben.");PollStatus();}else MessageBoxW(g_main,L"Die Fokusnachführung konnte nicht freigegeben werden.",L"Fokusnachführung",MB_OK|MB_ICONWARNING);break;case ID_AUTOMATION_DETAILS:g_automationDetailsExpanded=!g_automationDetailsExpanded;SetText(hAutomationDetailsToggle,g_automationDetailsExpanded?L"Details ausblenden":L"Details anzeigen");{RECT cr;GetClientRect(g_main,&cr);Layout(cr.right,cr.bottom);}break;case ID_SIM_APPLY:{int profile=ComboSel(hSimProfile);if(profile<0||profile>8)profile=8;wchar_t pv[16];wsprintfW(pv,L"%d",profile);if(!ApiSetW("simProfileMode",pv)||!ApiSetInt("simBacklashSteps",hSimBacklash))MessageBoxW(g_main,L"Simulatorprofil oder mechanisches Backlash konnte nicht übernommen werden. Zulässig sind 0 bis 5000 Schritte.",L"Simulator",MB_OK|MB_ICONWARNING);PollStatus();break;}case ID_SIM_RANDOMIZE:if(!ApiAction("sim-randomize"))MessageBoxW(g_main,L"Das Zufallsprofil kann nur bei ausgewähltem und ruhendem Simulator geladen werden.",L"Simulator",MB_OK|MB_ICONINFORMATION);else ComboSelect(hSimProfile,8);PollStatus();break;case ID_SELFTEST:if(!ApiAction("selftest"))MessageBoxW(g_main,L"Die synthetischen Tests konnten nicht gestartet werden. Simulator vollständig verbinden und laufende Aktionen beenden.",L"Tests nicht gestartet",MB_OK|MB_ICONWARNING);PollStatus();break;case ID_SAVE_PROFILE:SaveProfileUi();break;case ID_LOAD_PROFILE:LoadProfileUi();break;case ID_DELETE_PROFILE:DeleteProfileUi();break;case ID_IMPORT_PROFILE:ImportProfileUi();break;case ID_EXPORT_PROFILE:ExportProfileUi();break;}}return 0;
}
static BOOL IsActionableUiCommand(UINT id,UINT code){
    if(IsTabId(id))return code==BN_CLICKED;
    if(id==ID_VIEW_MODE||id==ID_THEME||id==ID_CAMERA_BACKEND||id==ID_FOCUSER_BACKEND)return code==CBN_SELCHANGE;
    if(code!=BN_CLICKED)return FALSE;
    switch(id){
        case ID_CAMERA_REFRESH:case ID_CAMERA_SELECT:case ID_CAMERA_CONNECT:case ID_FOCUSER_SELECT:case ID_FOCUSER_CONNECT:case ID_FOCUSER_SETUP:
        case ID_LIVE:case ID_MOVE_IN:case ID_MOVE_OUT:case ID_HALT:case ID_STRETCH:case ID_STARS:case ID_VALUES:case ID_SATURATION:case ID_ZONES:
        case ID_PREF_OUT:case ID_AF_USE_SELECTED:case ID_AF_CLEAR_SELECTED:case ID_STEP_ASSIST:case ID_AF_START:case ID_AF_STOP:case ID_BAHT_ENABLE:
        case ID_DIAGNOSTICS:case ID_EXPORT:case ID_AUTO_REFOCUS:case ID_CF_ENABLE:case ID_CF_FALLBACK:case ID_CF_SAVE:case ID_CF_RESET:case ID_CF_RESUME:case ID_BACKLASH_CAL:case ID_TEMP_COMP:case ID_AUTO_START_POS:case ID_EVT_MERIDIAN:case ID_EVT_RECONNECT:case ID_EVT_FILTER:case ID_FILTER_LEARN:case ID_FILTER_APPLY:case ID_SAVE_ADV:case ID_REFOCUS_RESUME:case ID_AUTOMATION_DETAILS:case ID_SIM_APPLY:case ID_SIM_RANDOMIZE:case ID_SELFTEST:case ID_SAVE_PROFILE:case ID_LOAD_PROFILE:case ID_DELETE_PROFILE:case ID_IMPORT_PROFILE:case ID_EXPORT_PROFILE:return TRUE;
        default:return FALSE;
    }
}
static BOOL IsThemeInputControl(HWND h){
    return h&&((h==hFocDevice)||(h==hAfDiagnosis)||(h==hLog)||(h==hAutomationInfo)||(h==hCfInfo));
}
static BOOL IsThemeValueControl(HWND h){return h&&((h==hPosition)||(h==hTemperature)||(h==hTestResult));}
static void QueueUiCommand(UINT id,UINT code){
    if(g_commandBusy||g_commandQueued||g_starSelectionBusy){AppendFrontendTrace("command ignored while another action is active");return;}
    g_pendingCommandId=id;g_pendingCommandCode=code;g_commandQueued=TRUE;if(!PostMessageW(g_main,WM_APP_EXECUTE_COMMAND,0,0)){g_commandQueued=FALSE;g_pendingCommandId=g_pendingCommandCode=0;AppendFrontendTrace("command PostMessage failed");}
}
static void ExecuteQueuedUiCommand(){
    if(g_commandBusy||!g_commandQueued)return;g_commandQueued=FALSE;g_commandBusy=TRUE;UINT id=g_pendingCommandId,code=g_pendingCommandCode;g_pendingCommandId=g_pendingCommandCode=0;
    HandleUiCommand(id,code);g_commandBusy=FALSE;SetFrontendPhase("idle");
    if(g_pendingStarX>=0&&g_pendingStarY>=0&&!g_starSelectionQueued){g_starSelectionQueued=TRUE;if(!PostMessageW(g_main,WM_APP_SELECT_STAR,0,0))g_starSelectionQueued=FALSE;}
}
static BOOL BeginShutdownGuard(){if(g_shutdownStarted)return FALSE;g_shutdownStarted=TRUE;return TRUE;}
static void CloseTrackedProcessForShutdown(HANDLE* process,DWORD gracefulWaitMs,UINT exitCode){
    if(!process||!*process)return;HANDLE p=*process;*process=0;DWORD state=WaitForSingleObject(p,gracefulWaitMs);if(state!=WAIT_OBJECT_0){TerminateProcess(p,exitCode);WaitForSingleObject(p,500);}CloseHandle(p);
}
static void StopUvcForShutdown(){
    if(g_uvcProcess){HANDLE p=g_uvcProcess;g_uvcProcess=0;TerminateProcess(p,0);WaitForSingleObject(p,500);CloseHandle(p);}
}
static void StopFocuserSetupForShutdown(){
    if(g_focuserSetupProcess){HANDLE p=g_focuserSetupProcess;g_focuserSetupProcess=0;TerminateProcess(p,0);WaitForSingleObject(p,500);CloseHandle(p);}if(g_focuserSetupEngineLock||g_state.focuserSetupActive)(void)ApiActionTimed("focuser-setup-end",500);g_focuserSetupEngineLock=FALSE;g_focuserSetupReconnect=FALSE;
}
static void StopAscomChooserForShutdown(){if(g_ascomChooserProcess){HANDLE p=g_ascomChooserProcess;g_ascomChooserProcess=0;TerminateProcess(p,0);WaitForSingleObject(p,500);CloseHandle(p);}if(g_ascomChooserResultPath[0]){DeleteFileW(g_ascomChooserResultPath);g_ascomChooserResultPath[0]=0;}}
static void ShutdownFrontend(HWND h){
    if(!BeginShutdownGuard())return;SetFrontendPhase("shutdown");KillTimer(h,TIMER_POLL);KillTimer(h,TIMER_FRAME);g_commandQueued=g_commandBusy=g_starSelectionQueued=g_starSelectionBusy=FALSE;g_pendingCommandId=g_pendingCommandCode=0;g_pendingStarX=g_pendingStarY=-1;StopUvcForShutdown();StopAscomChooserForShutdown();StopFocuserSetupForShutdown();
    /* The close button must never leave a hidden frontend behind. Give the local
       engine a short graceful window, then terminate only the child we started. */
    (void)ApiActionTimed("shutdown",500);CloseTrackedProcessForShutdown(&g_engineProcess,1500,0);
    if(!DestroyWindow(h))PostQuitMessage(0);
}
static LRESULT CALLBACK WndProc(HWND h,UINT m,WPARAM w,LPARAM l){if(g_shutdownStarted&&m!=WM_DESTROY&&m!=WM_CLOSE)return DefWindowProcW(h,m,w,l);if(m==WM_SETTINGCHANGE||m==WM_SYSCOLORCHANGE||m==WM_THEMECHANGED){RefreshTheme(FALSE);return 0;}if(m==WM_GETMINMAXINFO){MINMAXINFO* mm=(MINMAXINFO*)l;mm->ptMinTrackSize.x=1490;mm->ptMinTrackSize.y=940;return 0;}if(m==WM_SIZE){if(w==SIZE_MINIMIZED)return 0;RECT r;GetClientRect(h,&r);Layout(r.right,r.bottom);DestroyBackBuffer();InvalidateRect(h,0,FALSE);return 0;}if(m==WM_MOUSEMOVE){UpdateTrendHoverFromMouse((short)LOWORD(l),(short)HIWORD(l));return 0;}if(m==WM_LBUTTONDOWN){QueueStarSelectionFromClick((short)LOWORD(l),(short)HIWORD(l));return 0;}if(m==WM_APP_SELECT_STAR){ExecuteQueuedStarSelection();return 0;}if(m==WM_APP_START_ENGINE){StartEngineAfterWindowShown();return 0;}if(m==WM_TIMER){if(w==TIMER_POLL){PollAscomChooserProcess();PollFocuserSetupProcess();PollUvcProcess();if(!g_commandBusy&&!g_starSelectionBusy){if(PollStatus())g_statusRefreshRequested=FALSE;}}else if(w==TIMER_FRAME){if(!g_commandBusy&&!g_starSelectionBusy&&!g_pollBusy)MaybeLoadFrame();}return 0;}if(m==WM_COMMAND){UINT id=(UINT)LOWORD(w),code=(UINT)HIWORD(w);if(((id==ID_AF_POINTS||id==ID_AF_SAMPLES)&&code==CBN_SELCHANGE)||((id==ID_EXPOSURE||id==ID_GAIN||id==ID_AF_STEP||id==ID_BACKLASH)&&code==EN_CHANGE)){UpdateAutofocusInputState();return 0;}if(IsActionableUiCommand(id,code))QueueUiCommand(id,code);return 0;}if(m==WM_APP_EXECUTE_COMMAND){ExecuteQueuedUiCommand();return 0;}if(m==WM_ERASEBKGND)return 1;if(m==WM_PAINT){PAINTSTRUCT ps;HDC dc=BeginPaint(h,&ps);RECT rc;GetClientRect(h,&rc);if(EnsureBackBuffer(dc,rc.right,rc.bottom)){Paint(g_backDc);BitBlt(dc,ps.rcPaint.left,ps.rcPaint.top,ps.rcPaint.right-ps.rcPaint.left,ps.rcPaint.bottom-ps.rcPaint.top,g_backDc,ps.rcPaint.left,ps.rcPaint.top,SRCCOPY);}else Paint(dc);EndPaint(h,&ps);return 0;}if(m==WM_CTLCOLOREDIT||m==WM_CTLCOLORLISTBOX){HDC dc=(HDC)w;SetTextColor(dc,g_theme.textPrimary);SetBkColor(dc,g_theme.input);return (LRESULT)g_input;}if(m==WM_CTLCOLORSTATIC){HDC dc=(HDC)w;BOOL input=IsThemeInputControl((HWND)l),value=IsThemeValueControl((HWND)l);SetTextColor(dc,(input||value)?g_theme.textPrimary:g_theme.textSecondary);SetBkColor(dc,input?g_theme.input:g_theme.panel);return (LRESULT)(input?g_input:g_panel);}if(m==WM_CTLCOLORBTN){HDC dc=(HDC)w;SetTextColor(dc,g_theme.textPrimary);SetBkColor(dc,g_theme.panel);return (LRESULT)g_panel;}if(m==WM_CLOSE){ShutdownFrontend(h);return 0;}if(m==WM_DESTROY){AppendFrontendTrace("frontend window destroyed");g_main=0;KillTimer(h,TIMER_POLL);KillTimer(h,TIMER_FRAME);ClearFrame();DestroyBackBuffer();DeleteThemeResources();if(g_ws2){if(pWSACleanup)pWSACleanup();FreeLibrary(g_ws2);g_ws2=0;}PostQuitMessage(0);return 0;}return DefWindowProcW(h,m,w,l);}
extern "C" void AstroFocusApplicationMain(){
    g_inst=(HINSTANCE)GetModuleHandleW(0);GetModuleFileNameW(GetModuleHandleW(0),g_appDir,600);StripFile(g_appDir);InitializeFrontendDiagnostics();InstallFrontendCrashHandler();SetFrontendPhase("resource initialization");AppendFrontendTrace("frontend startup begin");
    g_font=CreateFontW(-16,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");g_small=CreateFontW(-14,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");g_title=CreateFontW(-23,0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");g_mono=CreateFontW(-14,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Consolas");
    LoadThemeSetting();g_highContrast=QueryHighContrast();g_darkTheme=ResolveDarkTheme(g_themeMode,QuerySystemDarkMode(),g_highContrast);SetBaseThemePalette(g_darkTheme);if(g_highContrast)ApplyHighContrastPalette();BuildThemeResources();LoadApplicationIcons();AppendFrontendTrace("frontend resources initialized");
    SetFrontendPhase("window class registration");WNDCLASSEXW wc;memset(&wc,0,sizeof(wc));wc.cbSize=sizeof(wc);wc.style=0;wc.lpfnWndProc=(void*)WndProc;wc.hInstance=g_inst;wc.hCursor=LoadCursorW(0,IDC_ARROW);wc.hIcon=g_appIcon;wc.hIconSm=g_appIconSmall;wc.hbrBackground=0;wc.lpszClassName=L"AstroFocusStudioWindow";
    if(!RegisterClassExW(&wc)&&GetLastError()!=ERROR_CLASS_ALREADY_EXISTS)FailFrontendStartup("window class registration failed",L"Die Windows-Fensterklasse konnte nicht registriert werden.",2);
    SetFrontendPhase("main window creation");g_main=CreateWindowExW(0,L"AstroFocusStudioWindow",AFS_FRONTEND_TITLE_W,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_THICKFRAME|WS_CLIPCHILDREN,CW_USEDEFAULT,CW_USEDEFAULT,1720,1020,0,0,g_inst,0);if(!g_main)FailFrontendStartup("main window creation failed",L"Das Hauptfenster konnte nicht erstellt werden.",3);
    SetFrontendPhase("child control creation");SendMessageW(g_main,WM_SETICON,ICON_BIG,(LPARAM)g_appIcon);SendMessageW(g_main,WM_SETICON,ICON_SMALL,(LPARAM)g_appIconSmall);CreateControls();if(g_controlCreationFailures>0)FailFrontendStartup("child control creation failed",L"Mindestens ein Bedienelement konnte nicht erstellt werden.",5);SetFrontendPhase("theme application");ApplyDarkTitleBar();ApplyThemeToControls();AppendFrontendTrace("frontend controls initialized");
    SetFrontendPhase("window display");ShowWindow(g_main,SW_MAXIMIZE);UpdateWindow(g_main);AppendFrontendTrace("frontend window shown");
    SetFrontendPhase("Winsock initialization");g_winsockReady=InitWinsock();if(!g_winsockReady){SetText(hStatus,L"Windows-Netzwerkkomponente konnte nicht initialisiert werden · Diagnosefenster bleibt geöffnet");MessageBoxW(g_main,L"Die Windows-Netzwerkkomponente konnte nicht initialisiert werden. Das Programm bleibt geöffnet, damit das Diagnoseprotokoll geprüft werden kann.",L"Startfehler",MB_OK|MB_ICONERROR);AppendFrontendTrace("Winsock initialization failed");}
    SetTimer(g_main,TIMER_POLL,250,0);SetTimer(g_main,TIMER_FRAME,100,0);if(!PostMessageW(g_main,WM_APP_START_ENGINE,0,0)){AppendFrontendTrace("deferred engine startup PostMessage failed");StartEngineAfterWindowShown();}else SetFrontendPhase("message loop");
    MSG msg;int messageResult=0;while((messageResult=GetMessageW(&msg,0,0,0))>0){TranslateMessage(&msg);DispatchMessageW(&msg);}if(messageResult<0){AppendFrontendTrace("GetMessage failed");MessageBoxW(g_main,L"Die Windows-Nachrichtenschleife wurde unerwartet beendet. Details stehen im FrontendTrace-Protokoll.",L"Programmfehler",MB_OK|MB_ICONERROR);ExitProcess(6);}AppendFrontendTrace("frontend normal exit");ExitProcess(0);
}
