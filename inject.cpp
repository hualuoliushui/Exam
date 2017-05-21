#ifndef INJECT_CPP
#define INJECT_CPP

//#define INJECT_MAIN

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdio.h>

/*
	将系统权限提升到Debug模式下（只有Debug模式才能打开进程句柄）
*/
int enableDebugPriv(const char* name)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;
	// 打开进程令牌环
	OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken);
	// 获得进程本地系统唯一ID，用于系统权限更改
	LookupPrivilegeValue(NULL, name, &luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;
	// 更改进程权限
	return AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
}

bool injectDll(const char* dllFullPath, const DWORD dwRemoteProcessId)
{
	HANDLE hRemoteProcess;
	if (!enableDebugPriv(SE_DEBUG_NAME))
	{
		std::cout << "debug权限提升失败\n";
		return false;
	}
	//打开远程进程（权限：PROCESS_CREATE_THREAD、PROCESS_VM_OPERATION、PROCESS_VM_WRITE）
	hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwRemoteProcessId);
	if (hRemoteProcess == NULL)
	{
		std::cout << "打开远程进程失败\n";
		return false;
	}
	char * pszLibFileRemote;
	// 使用 VirtualAllocEx 函数在远程进程的内存地址空间中分配 dll 文件名空间
	pszLibFileRemote = (char*)VirtualAllocEx(hRemoteProcess, NULL,
		lstrlen(dllFullPath) + 1, MEM_COMMIT, PAGE_READWRITE);
	// 使用WriteProcessMemory函数将dll的路径名写入到远程进程的内存空间
	WriteProcessMemory(hRemoteProcess, pszLibFileRemote, (void*)dllFullPath,
		lstrlen(dllFullPath) + 1, NULL);
	// 计算 LoadLibraryA 的入口地址（LoadLibraryA函数只需要dLL文件的路径来加载dll）
	PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32.dll")), TEXT("LoadLibraryA"));
	// 启动远程线程LoadLibraryA，通过远程线程调用创建新的线程
	HANDLE hRemoteThread;
	if ((hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, pfnStartAddr,
		pszLibFileRemote, 0, NULL)) == NULL)
	{
		std::cout << "注入线程失败！\n";
		return false;
	}
	else
	{
		std::cout << "注入线程成功!\n";
	}
	// 等待LoadLibrary加载完毕
	WaitForSingleObject(hRemoteThread, INFINITE);
	// 释放目标进程中申请的空间
	VirtualFreeEx(hRemoteProcess, pszLibFileRemote, lstrlen(dllFullPath) + 1, MEM_DECOMMIT);
	// 释放句柄
	CloseHandle(hRemoteProcess);
	CloseHandle(hRemoteThread);
	return true;
}

DWORD GetProcessId()
{
	DWORD pId = -1;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// 创建系统快照
	PROCESSENTRY32 lPrs;
	ZeroMemory(&lPrs, sizeof(lPrs));
	lPrs.dwSize = sizeof(lPrs);
	TCHAR* targetFile = TEXT("exam.exe");
	Process32First(hSnap, &lPrs);//获得系统快照中第一个进程信息
	if (strstr(targetFile, lPrs.szExeFile)) // 判断进程信息是否为 explorer.exe
	{
		pId = lPrs.th32ProcessID;
		return pId;
	}
	while(1)
	{
		ZeroMemory(&lPrs, sizeof(lPrs));
		lPrs.dwSize = sizeof(lPrs);
		if (!Process32Next(hSnap, &lPrs)) // 继续枚举进程信息
		{
			pId = -1;
			break;
		}
		if (strstr(targetFile, lPrs.szExeFile)) // 判断进程信息是否为 explorer.exe
		{
			pId = lPrs.th32ProcessID;
			break;
		}
	}
	return pId;
}

#ifdef INJECT_MAIN

void main()
{
	TCHAR myFile[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, myFile);
	// 取当前路径给 myFile
	strcat(myFile, "\\exam.dll"); // 当前路径加 door.dll
	std::cout << myFile << std::endl;
	std::cout << GetProcessId() << std::endl;

	// 这个数字是你想注入的进程的ID号
	injectDll(myFile, GetProcessId());
	
	std::cin.get();
}

#endif
#endif