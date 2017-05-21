#ifndef SIMPLE_TCP_SERVER_CPP
#define SIMPLE_TCP_SERVER_CPP

//#define SIMPLE_TCP_SERVER_TEST

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <stdio.h>

#define SIMPLE_TCP_SERVER_PORT 1234

#define LISTENING_STATE_MESSAGE "listen......\n"
#define HELLO_MESSAGE "hello!\n"
#define SEND_STATE_OK "send ok!\n"

BOOL InitWinsock();

void simple_tcp_server();

#ifdef SIMPLE_TCP_SERVER_TEST
int main()
{
	simple_tcp_server();

	return 0;
}
#endif

BOOL InitWinsock()
{
	int Error;
	WORD VersionRequested;
	WSADATA WsaData;
	VersionRequested = MAKEWORD(2, 2);
	Error = WSAStartup(VersionRequested, &WsaData);//启动WinSock2
	if (Error != 0)
		return FALSE;
	else
	{
		if (LOBYTE(WsaData.wVersion) != 2 || HIBYTE(WsaData.wHighVersion) != 2)
		{
			WSACleanup();
			return FALSE;
		}
	}
	return TRUE;
}

void simple_tcp_server()
{
	SOCKET mysock, tsock;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	mysock = socket(AF_INET, SOCK_STREAM, 0);

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(SIMPLE_TCP_SERVER_PORT);
	my_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(mysock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

	listen(mysock, 10); //等待连接数目
	printf(LISTENING_STATE_MESSAGE);

	sin_size = sizeof(struct sockaddr_in);
	tsock = accept(mysock, (struct sockaddr*)&their_addr, &sin_size);

	send(tsock, HELLO_MESSAGE, sizeof(HELLO_MESSAGE), 0);
	printf(SEND_STATE_OK);

	//关闭套接字
	closesocket(mysock);
	closesocket(tsock);

	return;
}

#endif