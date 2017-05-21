#ifndef INJECT_CPP
#define INJECT_CPP

//#define INJECT_MAIN

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdio.h>

/*
	��ϵͳȨ��������Debugģʽ�£�ֻ��Debugģʽ���ܴ򿪽��̾����
*/
int enableDebugPriv(const char* name)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	LUID luid;
	// �򿪽������ƻ�
	OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken);
	// ��ý��̱���ϵͳΨһID������ϵͳȨ�޸���
	LookupPrivilegeValue(NULL, name, &luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;
	// ���Ľ���Ȩ��
	return AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
}

bool injectDll(const char* dllFullPath, const DWORD dwRemoteProcessId)
{
	HANDLE hRemoteProcess;
	if (!enableDebugPriv(SE_DEBUG_NAME))
	{
		std::cout << "debugȨ������ʧ��\n";
		return false;
	}
	//��Զ�̽��̣�Ȩ�ޣ�PROCESS_CREATE_THREAD��PROCESS_VM_OPERATION��PROCESS_VM_WRITE��
	hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwRemoteProcessId);
	if (hRemoteProcess == NULL)
	{
		std::cout << "��Զ�̽���ʧ��\n";
		return false;
	}
	char * pszLibFileRemote;
	// ʹ�� VirtualAllocEx ������Զ�̽��̵��ڴ��ַ�ռ��з��� dll �ļ����ռ�
	pszLibFileRemote = (char*)VirtualAllocEx(hRemoteProcess, NULL,
		lstrlen(dllFullPath) + 1, MEM_COMMIT, PAGE_READWRITE);
	// ʹ��WriteProcessMemory������dll��·����д�뵽Զ�̽��̵��ڴ�ռ�
	WriteProcessMemory(hRemoteProcess, pszLibFileRemote, (void*)dllFullPath,
		lstrlen(dllFullPath) + 1, NULL);
	// ���� LoadLibraryA ����ڵ�ַ��LoadLibraryA����ֻ��ҪdLL�ļ���·��������dll��
	PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32.dll")), TEXT("LoadLibraryA"));
	// ����Զ���߳�LoadLibraryA��ͨ��Զ���̵߳��ô����µ��߳�
	HANDLE hRemoteThread;
	if ((hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, pfnStartAddr,
		pszLibFileRemote, 0, NULL)) == NULL)
	{
		std::cout << "ע���߳�ʧ�ܣ�\n";
		return false;
	}
	else
	{
		std::cout << "ע���̳߳ɹ�!\n";
	}
	// �ȴ�LoadLibrary�������
	WaitForSingleObject(hRemoteThread, INFINITE);
	// �ͷ�Ŀ�����������Ŀռ�
	VirtualFreeEx(hRemoteProcess, pszLibFileRemote, lstrlen(dllFullPath) + 1, MEM_DECOMMIT);
	// �ͷž��
	CloseHandle(hRemoteProcess);
	CloseHandle(hRemoteThread);
	return true;
}

DWORD GetProcessId()
{
	DWORD pId = -1;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// ����ϵͳ����
	PROCESSENTRY32 lPrs;
	ZeroMemory(&lPrs, sizeof(lPrs));
	lPrs.dwSize = sizeof(lPrs);
	TCHAR* targetFile = TEXT("exam.exe");
	Process32First(hSnap, &lPrs);//���ϵͳ�����е�һ��������Ϣ
	if (strstr(targetFile, lPrs.szExeFile)) // �жϽ�����Ϣ�Ƿ�Ϊ explorer.exe
	{
		pId = lPrs.th32ProcessID;
		return pId;
	}
	while(1)
	{
		ZeroMemory(&lPrs, sizeof(lPrs));
		lPrs.dwSize = sizeof(lPrs);
		if (!Process32Next(hSnap, &lPrs)) // ����ö�ٽ�����Ϣ
		{
			pId = -1;
			break;
		}
		if (strstr(targetFile, lPrs.szExeFile)) // �жϽ�����Ϣ�Ƿ�Ϊ explorer.exe
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
	// ȡ��ǰ·���� myFile
	strcat(myFile, "\\exam.dll"); // ��ǰ·���� door.dll
	std::cout << myFile << std::endl;
	std::cout << GetProcessId() << std::endl;

	// �������������ע��Ľ��̵�ID��
	injectDll(myFile, GetProcessId());
	
	std::cin.get();
}

#endif
#endif