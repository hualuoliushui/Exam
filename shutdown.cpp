#ifndef SHUTDOWN_CPP
#define SHUTDOWN_CPP
//#define SHUTDOWN_MAIN

#include <stdio.h>
#include <Windows.h>

bool gss_shutdown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	// 获取系统版本
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osvi) == 0)
	{
		return false;
	}
	if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		// Windows XP,Windows .NET Server
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))//打开当前进程访问代号
		{
			return false;
		}
		// 获取本地唯一标识用于在特定系统中设置权限
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

		// 提升访问令牌权限
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	}
	// 强制关机不向进程发送 WM_QUERYENDSESSION 消息
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