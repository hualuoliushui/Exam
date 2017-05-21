#ifndef DOWNLOADER_CPP
#define DOWNLOADER_CPP
//#define DOWNLOADER_MAIN

#include <Windows.h>
#include <stdio.h>
#pragma comment(lib,"Urlmon")

void downloader(char* filePathToSave)
{
	HRESULT urldownload;
	urldownload = URLDownloadToFile(NULL, "http://localhost:89", filePathToSave, 0, NULL);
	switch (urldownload)
	{
	case E_OUTOFMEMORY:
		printf("����ʧ��\n");
		break;
	case S_OK:
		printf("���سɹ�\n");
		break;
	default:
		break;
	}
}

#ifdef DOWNLOADER_MAIN
int main()
{
	downloader("D:\\temp.html");

	return 0;
}

#endif
#endif