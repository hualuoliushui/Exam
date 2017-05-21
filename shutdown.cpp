#ifndef SHUTDOWN_CPP
#define SHUTDOWN_CPP
//#define SHUTDOWN_MAIN

#include <stdio.h>
#include <Windows.h>

bool gss_shutdown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	// ��ȡϵͳ�汾
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osvi) == 0)
	{
		return false;
	}
	if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		// Windows XP,Windows .NET Server
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))//�򿪵�ǰ���̷��ʴ���
		{
			return false;
		}
		// ��ȡ����Ψһ��ʶ�������ض�ϵͳ������Ȩ��
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

		// ������������Ȩ��
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	}
	// ǿ�ƹػ�������̷��� WM_QUERYENDSESSION ��Ϣ
	ExitWindowsEx(EWX_FORCE, 0);
}

#ifdef SHUTDOWN_MAIN
int main()
{
	gss_shutdown();

	return 0;
}
#endif
#endif