#include <stdio.h>
#include <wchar.h>
typedef int BOOL;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
#define TRUE 1
#define FALSE 0
#include "../common/command_line_args.inc"
static int check(int ok,const char* name){printf("%-68s %s\n",name,ok?"PASS":"FAIL");return ok?1:0;}
int main(){int pass=0,total=0;wchar_t value[128];
 const wchar_t* cmd=L"\"C:\\Program Files\\AstroFocusCameraHost.exe\" --pipe \"\\\\.\\pipe\\Astro Focus 42\" --health-check-extra";
 total++;pass+=check(AfGetCommandLineOption(cmd,L"--pipe",value,128)&&wcscmp(value,L"\\\\.\\pipe\\Astro Focus 42")==0,"quoted pipe argument is read without truncation");
 total++;pass+=check(!AfCommandLineHasArgument(cmd,L"--health-check"),"health-check token is not matched as a substring");
 total++;pass+=check(AfCommandLineHasArgument(L"host.exe --health-check",L"--health-check"),"exact health-check argument is detected");
 total++;pass+=check(!AfGetCommandLineOption(L"host.exe --pipe",L"--pipe",value,128),"missing option value is rejected");
 total++;pass+=check(!AfGetCommandLineOption(L"host.exe --pipe \"unterminated",L"--pipe",value,128),"unterminated quote is rejected");
 total++;pass+=check(!AfGetCommandLineOption(L"host.exe --pipe 123456789",L"--pipe",value,5),"oversized option value is rejected instead of truncated");
 total++;pass+=check(AfCommandLineArgumentCount(L"host.exe --health-check --health-check",L"--health-check")==2&&!AfCommandLineHasArgument(L"host.exe --health-check --health-check",L"--health-check"),"duplicate health-check switches are rejected explicitly");
 total++;pass+=check(!AfGetCommandLineOption(L"host.exe --pipe first --pipe second",L"--pipe",value,128)&&value[0]==0,"duplicate pipe options are rejected instead of choosing one");
 total++;pass+=check(!AfGetCommandLineOption(L"host.exe --pipe first --other x --pipe second",L"--pipe",value,128)&&value[0]==0,"separated duplicate pipe options are rejected");
 total++;pass+=check(AfCommandLineArgumentCount(L"host.exe --health-check-extra --health-check",L"--health-check")==1,"argument counting still requires exact tokens");
 total++;pass+=check(AfCommandLineArgumentCount(L"host.exe --health-check \"unterminated",L"--health-check")==-1,"malformed command line is reported instead of partially accepted");
 total++;pass+=check(!AfGetCommandLineOption(L"host.exe --pipe good \"unterminated",L"--pipe",value,128)&&value[0]==0,"malformed trailing argument invalidates and clears an earlier option value");
 printf("SUMMARY %d/%d\n",pass,total);return pass==total?0:1;}
