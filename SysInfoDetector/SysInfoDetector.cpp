#include "stdafx.h"
#include <strsafe.h>
#include <windows.h>

#define DOTNET_INFO_LENGTH 1024

WCHAR szDotNetFramework[DOTNET_INFO_LENGTH];

WCHAR* GetFxVersionGreaterThen4dot5(DWORD release)
{
	switch (release) {
	case 378389: //4.5
		return L".NET Framework 4.5";
	case 378675: //4.5.1 installed with Windows 8.1 or Windows Server 2012 R2
	case 378758: //4.5.1 installed on Windows 8, Windows 7 SP1, or Windows Vista SP2
		return L".NET Framework 4.5.1";
	case 379893: //4.5.2
		return L".NET Framework 4.5.2";
	case 393295: //4.6 on Windows 10
	case 393297: //4.6 on all other OS
		return L".NET Framework 4.6";
	case 394254: //4.6.1 on Windows 10 November Update systems
	case 394271: //4.6.1 on all other OS versions
		return L".NET Framework 4.6.1";
	case 394802: //4.6.2 on Windows 10 Anniversary Update
	case 394806: //4.6.2 on all other OS versions
		return L".NET Framework 4.6.2";
	case 460798: //4.7 on Windows 10 Creators Update
	case 460805: //4.7 on all other OS versions.
		return L".NET Framework 4.7";
	case 461308: //4.7.1 on Windows 10 Fall Creators Update
	case 461310: //4.7.1 on all other OS versions.
		return L".NET Framework 4.7.1";
	case 461808: //4.7.2 on Windows 10 April 2018 Update
	case 461814: //4.7.2 on all other OS versions.
		return L".NET Framework 4.7.2";
	case 528040: //4.8 on Windows 10 May 2019 Update
	case 528372: //4.8 on Windows 10 May 2020 Update and Windows 10 October 2020
	case 528049: //4.8 on all others Windows operating systems
		return L".NET Framework 4.8";
	case 533320: //4.8.1 on Windows 11 2022 Update and Windows 11 2023 Update
	case 533325: //4.8.1 on all other Windows operating systems
		return L".NET Framework 4.8.1";
	default:     //Unknown
		return L".NET Framework > 4.8.1";
	}
}

WCHAR* GetDotNetFramework()
{
	DWORD dwInstall;
	DWORD dwRelease;
	DWORD dwSP;
	DWORD dwSize;
	HKEY hkResult;

	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v1.1.4322\Install - 1
	//         else if(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v1.1.4322\SP - 1)
	//             => .NET Framework 1.1 Service Pack 1
	//         else
	//             => .NET Framework 1.1
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"SP", 0, 0, (LPBYTE)&dwSP, &dwSize) && 1 == dwSP)
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 1.1 Service Pack 1\r\n");
			}
			else
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 1.1\r\n");
			}
		}
		RegCloseKey(hkResult);
	}

	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v2.0.50727\Install - 1
	//         if(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v2.0.50727\SP - 2)
	//             => .NET Framework 2.0 Service Pack 2
	//         else if(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v2.0.50727\SP - 1)
	//             => .NET Framework 2.0 Service Pack 1
	//         else
	//             => .NET Framework 2.0
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"SP", 0, 0, (LPBYTE)&dwSP, &dwSize) && (2 == dwSP || 1 == dwSP))
			{
				if (2 == dwSP)
				{
					StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 2.0 Service Pack 2\r\n");
				}
				else
				{
					StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 2.0 Service Pack 1\r\n");
				}
			}
			else
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 2.0\r\n");
			}
		}
		RegCloseKey(hkResult);
	}

	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v3.0\Install - 1
	//         if(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v3.0\SP - 2)
	//             => .NET Framework 3.0 Service Pack 2
	//         else if(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v3.0\SP - 1)
	//             => .NET Framework 3.0 Service Pack 1
	//         else
	//             => .NET Framework 3.0
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v3.0", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"SP", 0, 0, (LPBYTE)&dwSP, &dwSize) && (2 == dwSP || 1 == dwSP))
			{
				if (2 == dwSP)
				{
					StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 3.0 Service Pack 2\r\n");
				}
				else
				{
					StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 3.0 Service Pack 1\r\n");
				}
			}
			else
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 3.0\r\n");
			}
		}
		RegCloseKey(hkResult);
	}

	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v3.5\Install - 1
	//         if(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v3.5\SP - 1)
	//             => .NET Framework 3.5 Service Pack 1
	//         else
	//             => .NET Framework 3.5
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v3.5", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"SP", 0, 0, (LPBYTE)&dwSP, &dwSize) && 1 == dwSP)
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 3.5 Service Pack 1\r\n");
			}
			else
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 3.5\r\n");
			}
		}
		RegCloseKey(hkResult);
	}

	bool is40ClientDetected = false;
	bool is40FullDetected = false;
	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4.0\Client\Install - 1
	//             => .NET Framework 4.0 Client Profile
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4.0\\Client", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 4.0 Client Profile\r\n");
			is40ClientDetected = true;
		}
		RegCloseKey(hkResult);
	}

	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4.0\Full\Install - 1
	//             => .NET Framework 4.0 Full
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4.0\\Full", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 4.0 Full\r\n");
			is40FullDetected = true;
		}
		RegCloseKey(hkResult);
	}

	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Client\Install - 1
	//         switch(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Client\Release)
	//             => .NET Framework 4.5/4.5.1/4.5.2/4.6/4.6.1 Client Profile
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Release", 0, 0, (LPBYTE)&dwRelease, &dwSize))
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, GetFxVersionGreaterThen4dot5(dwRelease));
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L" Client Profile\r\n");
			}
			else if(!is40ClientDetected){
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 4.0 Client Profile\r\n");
			}
		}
		RegCloseKey(hkResult);
	}

	//��� HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full\Install - 1
	//         switch(HKLM\SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full\Release)
	//             => .NET Framework 4.5/4.5.1/4.5.2/4.6/4.6.1 Full
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full", 0, KEY_READ, &hkResult))
	{
		dwSize = sizeof(dwInstall);
		if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Install", 0, 0, (LPBYTE)&dwInstall, &dwSize) && 1 == dwInstall)
		{
			if (ERROR_SUCCESS == RegQueryValueExW(hkResult, L"Release", 0, 0, (LPBYTE)&dwRelease, &dwSize))
			{
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, GetFxVersionGreaterThen4dot5(dwRelease));
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L" Full\r\n");
			}
			else if(!is40FullDetected){
				StringCchCatW(szDotNetFramework, DOTNET_INFO_LENGTH, L".NET Framework 4.0 Full\r\n");
			}
		}
		RegCloseKey(hkResult);
	}

	return szDotNetFramework;
}


void main(int argc, wchar_t* argv[])
{
	wprintf(GetDotNetFramework());
	getchar();
}
