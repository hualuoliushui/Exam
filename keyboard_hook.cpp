#define KEYBOARD_HOOK_CPP

#ifdef KEYBOARD_HOOK_CPP

#include <Windows.h>
#include <iostream>

//#define KEYBOARD_HOOK_MAIN
HHOOK keyboardHook = 0;

LRESULT CALLBACK keyboardHook_Callback(int code, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;
	// �ж��Ƿ�Ϊ��Ч����
	if (code >= HC_ACTION && wParam == WM_KEYDOWN)
	{
		std::cout << "����" << ks->vkCode << "��\n";
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
		std::cout << "�ҹ�����ʧ��\n";
		return -1;
	}
	std::cout << "������������\n";

	// ����©����Ϣ�����������Ῠ��
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
			// ����CPUȫ��������
			Sleep(0);
		}
	}
	UnhookWindowsHookEx(keyboardHook);

	std::cout << "���������˳�\n";

	return 0;
}
#endif
#endif