// Minimal /GS support for the custom no-CRT Windows x64 build.
extern "C" {
typedef unsigned long long UINT_PTR_AF;
typedef unsigned int UINT_AF;
#ifdef _MSC_VER
#define AFS_STDCALL __stdcall
#else
#define AFS_STDCALL __attribute__((stdcall))
#endif
void AFS_STDCALL ExitProcess(UINT_AF);
UINT_PTR_AF __security_cookie = 0x00002B992DDFA232ULL;
UINT_PTR_AF __security_cookie_complement = ~0x00002B992DDFA232ULL;
void __security_init_cookie(){
    UINT_PTR_AF local=0;
    UINT_PTR_AF value=(UINT_PTR_AF)&__security_cookie ^ (UINT_PTR_AF)&local ^ 0x9E3779B97F4A7C15ULL;
    if(value==0 || value==0x00002B992DDFA232ULL)value^=0xD1B54A32D192ED03ULL;
    __security_cookie=value;
    __security_cookie_complement=~value;
}
void __security_check_cookie(UINT_PTR_AF value){if(value!=__security_cookie)ExitProcess(0xC0000409U);}
void __report_gsfailure(){ExitProcess(0xC0000409U);}
}
