#define KEYBOARD_HOOK_CPP

#ifdef KEYBOARD_HOOK_CPP

#include <Windows.h>
#include <iostream>

//#define KEYBOARD_HOOK_MAIN
HHOOK keyboardHook = 0;

LRESULT CALLBACK keyboardHook_Callback(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;
	// 判定是否为有效按键
	if (code >= HC_ACTION && wParam == WM_KEYDOWN)
	{
		std::cout << "拦截" << ks->vkCode << "键\n";
		//putchar(ks->vkCode); putchar('\n');
		//return 1;
	}
	return CallNextHookEx(0, code, wParam, lParam);
}

#ifdef KEYBOARD_HOOK_MAIN
int main()
{
	keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, keyboardHook_Callback, GetModuleHandleA(0), 0);
	if (keyboardHook == 0)
	{
		std::cout << "挂钩键盘失败\n";
		return -1;
	}
	std::cout << "程序正常运行\n";

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

	std::cout << "程序正常退出\n";

	return 0;
}
#endif
#endif