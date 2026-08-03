// AstroFocus Studio 3.9.0 setup/updater launcher.
// Starts the fixed sibling PowerShell script and reports bootstrap failures visibly.
extern "C" {
typedef unsigned long DWORD; typedef int BOOL; typedef unsigned short WORD; typedef unsigned char BYTE;
typedef long LONG; typedef long long LONG_PTR; typedef unsigned long long SIZE_T; typedef void* HANDLE;
typedef HANDLE HMODULE; typedef const wchar_t* LPCWSTR; typedef wchar_t* LPWSTR; typedef void* LPVOID;
#ifdef _MSC_VER
#define WINAPI __stdcall
#else
#define WINAPI __attribute__((stdcall))
#endif
#define TRUE 1
#define FALSE 0
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
struct SECURITY_ATTRIBUTES;
struct STARTUPINFOW_MIN {DWORD cb;LPWSTR lpReserved,lpDesktop,lpTitle;DWORD dwX,dwY,dwXSize,dwYSize,dwXCountChars,dwYCountChars,dwFillAttribute,dwFlags;WORD wShowWindow,cbReserved2;BYTE* lpReserved2;HANDLE hStdInput,hStdOutput,hStdError;};
struct PROCESS_INFORMATION_MIN {HANDLE hProcess,hThread;DWORD dwProcessId,dwThreadId;};
void WINAPI ExitProcess(unsigned int);
DWORD WINAPI GetLastError(void);
DWORD WINAPI GetModuleFileNameW(HMODULE,LPWSTR,DWORD);
DWORD WINAPI GetSystemDirectoryW(LPWSTR,DWORD);
DWORD WINAPI GetFileAttributesW(LPCWSTR);
LPCWSTR WINAPI GetCommandLineW(void);
BOOL WINAPI CreateProcessW(LPCWSTR,LPWSTR,SECURITY_ATTRIBUTES*,SECURITY_ATTRIBUTES*,BOOL,DWORD,LPVOID,LPCWSTR,STARTUPINFOW_MIN*,PROCESS_INFORMATION_MIN*);
DWORD WINAPI WaitForSingleObject(HANDLE,DWORD);
BOOL WINAPI GetExitCodeProcess(HANDLE,DWORD*);
BOOL WINAPI CloseHandle(HANDLE);
int WINAPI MessageBoxW(void*,LPCWSTR,LPCWSTR,unsigned int);
void* memset(void* d,int v,SIZE_T n){BYTE* p=(BYTE*)d;while(n--)*p++=(BYTE)v;return d;}
}
#define INFINITE 0xffffffffUL
#define INVALID_FILE_ATTRIBUTES 0xffffffffUL
#define FILE_ATTRIBUTE_DIRECTORY 0x10UL
#define MB_OK 0x00000000UL
#define MB_ICONERROR 0x00000010UL
#define MB_SETFOREGROUND 0x00010000UL
#ifndef ASTROFOCUS_SCRIPT_NAME
#define ASTROFOCUS_SCRIPT_NAME L"AstroFocusUpdater.ps1"
#endif
#ifndef ASTROFOCUS_TOOL_TITLE
#define ASTROFOCUS_TOOL_TITLE L"AstroFocus Studio"
#endif
static int WLen(LPCWSTR s){int n=0;while(s&&s[n])n++;return n;}
static BOOL Append(LPWSTR out,int cap,LPCWSTR in){int n=WLen(out),i=0;if(n>=cap)return FALSE;while(in&&in[i]&&n<cap-1)out[n++]=in[i++];out[n]=0;return !in||!in[i];}
static BOOL AppendUInt(LPWSTR out,int cap,DWORD value){wchar_t digits[16]={0};int used=0;do{digits[used++]=(wchar_t)(L'0'+(value%10));value/=10;}while(value&&used<15);for(int i=used-1;i>=0;i--){wchar_t one[2]={digits[i],0};if(!Append(out,cap,one))return FALSE;}return TRUE;}
static void DirectoryOf(LPWSTR p){int last=-1;for(int i=0;p[i];i++)if(p[i]==L'\\'||p[i]==L'/')last=i;if(last>=0)p[last+1]=0;else p[0]=0;}
static LPCWSTR SkipExecutable(LPCWSTR cmd){if(!cmd)return L"";BOOL quote=*cmd==L'\"';if(quote)cmd++;while(*cmd&&((quote&&*cmd!=L'\"')||(!quote&&*cmd!=L' '&&*cmd!=L'\t')))cmd++;if(quote&&*cmd==L'\"')cmd++;while(*cmd==L' '||*cmd==L'\t')cmd++;return cmd;}
static wchar_t LowerAscii(wchar_t c){return c>=L'A'&&c<=L'Z'?(wchar_t)(c+(L'a'-L'A')):c;}
static BOOL TokenEqualsI(LPCWSTR begin,int length,LPCWSTR expected){int expectedLength=WLen(expected);if(length!=expectedLength)return FALSE;for(int i=0;i<length;i++)if(LowerAscii(begin[i])!=LowerAscii(expected[i]))return FALSE;return TRUE;}
static BOOL HasSwitch(LPCWSTR args,LPCWSTR expected){if(!args)return FALSE;while(*args){while(*args==L' '||*args==L'\t')args++;if(!*args)break;BOOL quoted=*args==L'\"';if(quoted)args++;LPCWSTR begin=args;while(*args&&((quoted&&*args!=L'\"')||(!quoted&&*args!=L' '&&*args!=L'\t')))args++;if(TokenEqualsI(begin,(int)(args-begin),expected))return TRUE;if(quoted&&*args==L'\"')args++;}return FALSE;}
static BOOL IsRegularFile(LPCWSTR path){DWORD attributes=GetFileAttributesW(path);return attributes!=INVALID_FILE_ATTRIBUTES&&(attributes&FILE_ATTRIBUTE_DIRECTORY)==0;}
static void ShowBootstrapError(LPCWSTR detail,DWORD code){wchar_t message[1400]={0};Append(message,1400,detail);if(code){Append(message,1400,L"\n\nWindows-Fehler-/Exitcode: ");AppendUInt(message,1400,code);}Append(message,1400,L"\n\nBitte das Setup vollständig entpacken und erneut starten.");MessageBoxW(0,message,ASTROFOCUS_TOOL_TITLE,MB_OK|MB_ICONERROR|MB_SETFOREGROUND);}
extern "C" void AstroFocusApplicationMain(){
    wchar_t dir[1024]={0},script[1200]={0},powershell[1400]={0},command[8192]={0};
    if(!GetModuleFileNameW(0,dir,1024)){ShowBootstrapError(L"Der Pfad des AstroFocus-Launchers konnte nicht ermittelt werden.",GetLastError());ExitProcess(10);}DirectoryOf(dir);
    if(!Append(script,1200,dir)||!Append(script,1200,ASTROFOCUS_SCRIPT_NAME)||!IsRegularFile(script)){ShowBootstrapError(L"Das zum Launcher gehörende PowerShell-Skript fehlt.",0);ExitProcess(13);}
    DWORD systemLength=GetSystemDirectoryW(powershell,1024);if(systemLength==0||systemLength>=1024||!Append(powershell,1400,L"\\WindowsPowerShell\\v1.0\\powershell.exe")||!IsRegularFile(powershell)){ShowBootstrapError(L"Windows PowerShell 5.1 wurde im Windows-Systemverzeichnis nicht gefunden.",GetLastError());ExitProcess(14);}
    if(!Append(command,8192,L"\"")||!Append(command,8192,powershell)||!Append(command,8192,L"\" -NoLogo -NoProfile -NonInteractive -ExecutionPolicy Bypass -File \"")||!Append(command,8192,script)||!Append(command,8192,L"\"")){ShowBootstrapError(L"Die Setup-Befehlszeile ist zu lang.",0);ExitProcess(15);}
    LPCWSTR rest=SkipExecutable(GetCommandLineW());if(rest&&*rest){if(!Append(command,8192,L" ")||!Append(command,8192,rest)){ShowBootstrapError(L"Die Setup-Argumente sind zu lang.",0);ExitProcess(15);}}
#ifdef ASTROFOCUS_AUTO_DEV_SWITCH
    wchar_t marker[1200]={0};
    if(!HasSwitch(rest,L"-AllowUnsignedDevelopment")){Append(marker,1200,dir);Append(marker,1200,L"UNSIGNED_DEVELOPMENT_BUILD.txt");if(IsRegularFile(marker)){if(!Append(command,8192,L" -AllowUnsignedDevelopment")){ShowBootstrapError(L"Die Setup-Befehlszeile ist zu lang.",0);ExitProcess(15);}}}
#endif
    STARTUPINFOW_MIN si;PROCESS_INFORMATION_MIN pi;memset(&si,0,sizeof(si));memset(&pi,0,sizeof(pi));si.cb=sizeof(si);
    if(!CreateProcessW(powershell,command,0,0,FALSE,0,0,dir,&si,&pi)){DWORD error=GetLastError();ShowBootstrapError(L"Windows PowerShell konnte für das AstroFocus-Setup nicht gestartet werden.",error);ExitProcess(11);}CloseHandle(pi.hThread);WaitForSingleObject(pi.hProcess,INFINITE);DWORD code=12;if(!GetExitCodeProcess(pi.hProcess,&code))code=12;CloseHandle(pi.hProcess);
    if(code!=0&&!HasSwitch(rest,L"-Quiet"))ShowBootstrapError(L"Das AstroFocus-Setup wurde mit einem Fehler beendet. Weitere Details stehen – sofern bereits angelegt – in C:\\ProgramData\\AstroFocusStudio\\Logs\\Installer.log.",code);
    ExitProcess(code);
}
