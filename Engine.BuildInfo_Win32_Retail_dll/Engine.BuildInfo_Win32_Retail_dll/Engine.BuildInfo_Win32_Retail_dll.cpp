#include <windows.h>
#include <stdio.h>
#include <memoryapi.h>
#include <processthreadsapi.h>


HINSTANCE mHinst = 0, mHinstDLL = 0;
UINT_PTR mProcs[1] = {0};

//def
void InjectUIScaleLimit(void);

LPCSTR mImportNames[] = {"getBuildInfo"};
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
	mHinst = hinstDLL;
	if ( fdwReason == DLL_PROCESS_ATTACH ) {
		mHinstDLL = LoadLibrary( "ori_Engine.BuildInfo_Win32_Retail_dll.dll" );
		if ( !mHinstDLL )
			return ( FALSE );
		for ( int i = 0; i < 1; i++ )
			mProcs[ i ] = (UINT_PTR)GetProcAddress( mHinstDLL, mImportNames[ i ] );
	} else if ( fdwReason == DLL_PROCESS_DETACH ) {
		FreeLibrary( mHinstDLL );
	}
	//这个DLL被加载的时候游戏.text已经被解密了可以修改内存了
	InjectUIScaleLimit();
	return ( TRUE );
}

extern "C" __declspec(naked) void __stdcall getBuildInfo_wrapper(){__asm{jmp mProcs[0*4]}}

void InjectUIScaleLimit(void) {
	int value = 0xFF ;
	//UI检测分辨率的地址
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)0x01766A9A, (LPVOID)&value, 1, NULL);
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)0x01766AA2, (LPVOID)&value, 1, NULL);
	//按键提示检测分辨率的地址
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)0x0094FC63, (LPVOID)&value, 1, NULL);
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)0x0094FC8B, (LPVOID)&value, 1, NULL);
	//小地图
	value = 0x8E;
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)0x00936733, (LPVOID)&value, 1, NULL);
}
