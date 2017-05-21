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
		std::cout << "����" << ks->vkCode << "��\n";
		return 1;
	}
	return CallNextHookEx(0, code, wParam, lParam);
}

int run()
{
	keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, keyboardHook_Callback, GetModuleHandleA(0), 0);
	if (keyboardHook == 0)
	{
		//std::cout << "�ҹ�����ʧ��\n";
		return -1;
	}
	//std::cout << "������������\n";

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
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
{
	char *szProcessId = (char*)malloc(10 * sizeof(char));
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		// ��ȡ����ʾ��ǰ����ID
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