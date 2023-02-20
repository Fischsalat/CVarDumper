#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "containers.h"
#include "Utils.h"

struct FConsoleObject
{
	void* Vft;
	FString Description;
};

void Main()
{
	AllocConsole();

	FILE* pFile;
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	//uint8** Singletone = reinterpret_cast<uint8**>(uintptr_t(GetModuleHandle(0)) + 0xC36CDB0);
	uint8** Singletone = reinterpret_cast<uint8**>(uintptr_t(GetModuleHandle(0)) + 0xEB916D8);
	//uint8** Singletone = FindByWString(L"Valet.AdditionalUprightTorque"); // 0xEB916D8

	std::cout << "Singletone: " << Singletone << std::endl;

	auto& ConsoleObjects = *reinterpret_cast<TMap<FString, FConsoleObject*>*>(*Singletone + 8);

	std::cout << "\nConsoleObjects: " << &ConsoleObjects << " Num: " << ConsoleObjects.Num() << "\n\n";

	std::ofstream CVarDump("CVars.txt");
	
	for (auto& Pair : ConsoleObjects)
	{
		if (Pair.Key())
		{
			CVarDump << Pair.Key().ToString() << "\n";

			if (Pair.Value() && Pair.Value()->Description.IsValid())
			{
				CVarDump << "\"" << Pair.Value()->Description.ToString() << "\"\n\n";
			}
			else
			{
				CVarDump << "\"---\"\n\n";
			}
		}
	}
	CVarDump.close();

	std::cout << "done!\n" << std::endl;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH: {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
		break;
	}
	case DLL_PROCESS_DETACH: {
		break;
	}
	}
	return TRUE;
}