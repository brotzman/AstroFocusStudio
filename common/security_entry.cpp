// AstroFocus Studio 3.9.0 no-CRT process entry.
// This translation unit MUST be compiled with /GS- because the security
// cookie has to be initialized before any /GS-protected function begins.
extern "C" {
typedef unsigned int UINT_AF;
#ifdef _MSC_VER
#define AFS_STDCALL __stdcall
#else
#define AFS_STDCALL __attribute__((stdcall))
#endif
void __security_init_cookie();
void AstroFocusApplicationMain();
void AFS_STDCALL ExitProcess(UINT_AF);

void WinMainCRTStartup(){
    __security_init_cookie();
    AstroFocusApplicationMain();
    ExitProcess(0);
}
}
