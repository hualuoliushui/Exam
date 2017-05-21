//#ifndef TESTDLL_CPP
//#define TESTDLL_CPP
#ifdef TESTDLL_CPP
#include <Windows.h>
#include <iostream>

HHOOK keyboardHook = 0;

LRESULT CALLBACK keyboardHook_Callback(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;
	if (ks->vkCode - 'A' >= 0 && ks->vkCode - 'Z' <= 0)
	{
		std::cout << "拦截" << ks->vkCode << "键\n";
		return 1;
	}
	return CallNextHookEx(0, code, wParam, lParam);
}

int run()
{
	keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, keyboardHook_Callback, GetModuleHandleA(0), 0);
	if (keyboardHook == 0)
	{
		//std::cout << "挂钩键盘失败\n";
		return -1;
	}
	//std::cout << "程序正常运行\n";

	// 不可漏掉消息处理，否则程序会卡死
	MSG msg;
	while (1)
	{
		if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
		{
			// 避免CPU全负载运行
			Sleep(0);
		}
	}
	UnhookWindowsHookEx(keyboardHook);
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
{
	char *szProcessId = (char*)malloc(10 * sizeof(char));
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		// 获取并显示当前进程ID
		_itoa(GetCurrentProcessId(), szProcessId, 10);
		MessageBox(NULL, szProcessId, TEXT("RemoteDLL"), MB_OK);
		run();
	}
	default:
		break;
	}
	return true;
}

#endif