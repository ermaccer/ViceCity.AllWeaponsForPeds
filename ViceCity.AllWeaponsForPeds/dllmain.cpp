// dllmain.cpp : Defines the entry point for the DLL application.
#include "MemoryMgr.h"
#include <iostream>

using namespace Memory::VP;

int randomWeapon = 0;


void __declspec(naked) WeaponHook()
{
	static int jumpContinue = 0x53B6ED;
	randomWeapon = rand() % 36;

	// some sanity 
	switch (randomWeapon)
	{
		// missile
	case 16:
		randomWeapon = 30;
		break;
		// heli cannon
	case 35:
		randomWeapon = 32;
		break;
		// detonator/rem gren
	case 13:
	case 34:
		randomWeapon = 12;
		break;
	}
	_asm {
		mov ebx, randomWeapon
		jmp jumpContinue
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		if (*(DWORD*)0x667BF5 == 0xB85548EC)
		{
			InjectHook(0x53B6B4, WeaponHook, PATCH_JUMP);
		}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

