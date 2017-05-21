#ifndef REGISTRY_OPERATOR_CPP
#define REGISTRY_OPERATOR_CPP

//#define REGISTRY_OPERATOR_TEST

#include <stdio.h>
#include <Windows.h>

void registry_read()
{
	long lRet;
	HKEY hKey;
	TCHAR tchData[64];
	DWORD dwSize;
	TCHAR regkey[] = TEXT("Hardware\\Description\\System\\CentralProcessor\\0");

	lRet = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		regkey,
		0,
		KEY_QUERY_VALUE | KEY_WOW64_64KEY,
		&hKey
		);
	if (lRet == ERROR_SUCCESS)
	{
		TCHAR regitem[] = TEXT("ProcessorNameString");
		dwSize = sizeof(tchData);
		lRet = RegQueryValueEx(
			hKey,
			regitem,
			NULL,
			NULL,
			(LPBYTE)tchData,
			&dwSize
			);
		if (lRet == ERROR_SUCCESS)
		{
			printf("\n CPU INFO:");
#ifdef UNICODE
			printf("%ls\n", tchData);
#else
			printf("%s\n", tchData);
#endif
		}
		else
		{
			printf("\nCPU INFO:");
			printf("UNKNOWN\n");
		}
	}
	else
	{
		printf("\n CPU INFO:");
		printf("UNKNOWN\n");
	}
	RegCloseKey(hKey);
}

void registry_write()
{
	HKEY hRoot = HKEY_LOCAL_MACHINE;
	TCHAR szSubKey[] = TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	HKEY hKey;
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;

	LONG lRet = RegCreateKeyEx(
		hRoot,
		szSubKey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDisposition
		);
	if (lRet != ERROR_SUCCESS)
		return;
	TCHAR szModule[MAX_PATH];
	GetModuleFileName(NULL, szModule, MAX_PATH);

	TCHAR regitem[] = TEXT("SelfRunDemo");
	lRet = RegSetValueEx(
		hKey,
		regitem,
		0,
		REG_SZ,
		(BYTE*)szModule,
		lstrlen(szModule));
	if (lRet == ERROR_SUCCESS)
	{
		printf(" self run success\n");
	}
	RegCloseKey(hKey);
}

#ifdef REGISTRY_OPERATOR_TEST
int main()
{
	registry_read();
	return 0;
}
#endif
#endif