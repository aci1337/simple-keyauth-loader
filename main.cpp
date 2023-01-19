#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "skStr.h"
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

using namespace KeyAuth;

std::string name = ""; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = ""; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = ""; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting

/*
	Video on what ownerid and secret are https://youtu.be/uJ0Umy_C6Fg

	Video on how to add KeyAuth to your own application https://youtu.be/GB4XW_TsHqA

	Video to use Web Loader (control loader from customer panel) https://youtu.be/9-qgmsUUCK4
*/

api KeyAuthApp(name, ownerid, secret, version, url);
#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>
#include <accctrl.h>
#include <aclapi.h>
#include <shlobj_core.h>
#include <tlhelp32.h>

#pragma comment(lib, "shlwapi.lib")

void Fullscreen()
{
	HWND consoleWindow = GetConsoleWindow();

	SetWindowLong(consoleWindow, GWL_STYLE, 0);

	ShowWindow(consoleWindow, SW_MAXIMIZE);
}
void randomString(char* str, const unsigned int len)
{
	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (unsigned int i = 0; i < len; ++i)
	{
		str[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	str[len] = 0;
}
void DrawBox()
{
	int width = 50;
	int height = 8;

	int x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
	int y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);

	SetWindowPos(GetConsoleWindow(), 0, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
	SetConsoleTitle("");
	system("cls");
	for (int i = 0; i < width; i++)
	{
		std::cout << (char)219;
	}
	std::cout << std::endl;
	for (int j = 0; j < height; j++)
	{
		std::cout << (char)219;
		for (int k = 0; k < width - 2; k++)
		{
			std::cout << " ";
		}
		std::cout << (char)219;
		std::cout << std::endl;
	}
	for (int i = 0; i < width; i++)
	{
		std::cout << (char)219;
	}
	std::cout << std::endl;
}
#include <tlhelp32.h>
#include <tchar.h>
#include <WinUser.h>
#include <filesystem>
using namespace std;
std::string GenerateMACAddress()
{
	std::string macAddress;
	const char* charset = "ABCDEF0123456789";
	const char* charset2 = "26AE";

	for (int i = 0; i < 12; i++)
	{
		if (i == 2)
		{
			int randomChar = rand() % 4;
			macAddress += charset2[randomChar];
		}
		else
		{
			int randomChar = rand() % 16;
			macAddress += charset[randomChar];
		}
	}

	return macAddress;
}

BOOL SetMACAddress(std::string macAddress)
{
	HKEY hKey;
	LONG regResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E972-E325-11CE-BFC1-08002bE10318}"), 0, KEY_ALL_ACCESS, &hKey);

	if (regResult != ERROR_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; i < 3; i++)
	{
		std::string subkeyName = std::to_string(i) + "000";
		HKEY hSubKey;
		regResult = RegOpenKeyEx(hKey, TEXT(subkeyName.c_str()), 0, KEY_ALL_ACCESS, &hSubKey);

		if (regResult != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			return FALSE;
		}

		regResult = RegSetValueEx(hSubKey, TEXT("NetworkAddress"), 0, REG_SZ, (LPBYTE)macAddress.c_str(), macAddress.size());

		if (regResult != ERROR_SUCCESS)
		{
			RegCloseKey(hSubKey);
			RegCloseKey(hKey);
			return FALSE;
		}

		DWORD powerSavingMode = 24;
		regResult = RegSetValueEx(hSubKey, TEXT("PnPCapabilities"), 0, REG_DWORD, (LPBYTE)&powerSavingMode, sizeof(DWORD));

		if (regResult != ERROR_SUCCESS)
		{
			RegCloseKey(hSubKey);
			RegCloseKey(hKey);
			return FALSE;
		}

		RegCloseKey(hSubKey);
	}

	RegCloseKey(hKey);

	return TRUE;
}

BOOL ResetNetworkAdapters()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	std::string commandStr = "netsh interface set interface name=\"%s\" disable";
	CreateProcess(NULL, (LPSTR)commandStr.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);


	WaitForSingleObject(pi.hProcess, INFINITE);


	commandStr = "netsh interface set interface name=\"%s\" enable";
	CreateProcess(NULL, (LPSTR)commandStr.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);


	WaitForSingleObject(pi.hProcess, INFINITE);

	return TRUE;
}
#include <filesystem>
#include <stdio.h>
#include <tchar.h>
#include <IPHlpApi.h>
#include <stdlib.h>
#include <iptypes.h>
#pragma comment(lib, "IPHlpApi.lib")
#include <algorithm>
#include <random>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <thread>
const int width = 60;
const int height = 20;
int x = 0;
int y = 0;

int xDir = 1;
int yDir = 1;

int color = 0x0A;

bool running = true;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void blockInput()
{
	int mouse_state, keyboard_state;

	GetKeyboardState((LPBYTE)&keyboard_state);
	GetKeyboardState((LPBYTE)&mouse_state);

	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_TAB, 0x8, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(0x38, 0x38, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_DELETE, 0x53, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_LWIN, 0x5B, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_RETURN, 0x1C, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_LBUTTON, 0x1, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_RBUTTON, 0x2, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_MBUTTON, 0x4, KEYEVENTF_EXTENDEDKEY, 0);

	SetKeyboardState((LPBYTE)&mouse_state);
	SetKeyboardState((LPBYTE)&keyboard_state);
}

void unblockInput()
{
	int mouse_state, keyboard_state;

	GetKeyboardState((LPBYTE)&keyboard_state);
	GetKeyboardState((LPBYTE)&mouse_state);

	keybd_event(VK_MENU, 0x38, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_TAB, 0x8, 0, 0);
	keybd_event(VK_CONTROL, 0x1D, 0, 0);
	keybd_event(0x38, 0x38, 0, 0);
	keybd_event(VK_DELETE, 0x53, 0, 0);
	keybd_event(VK_LWIN, 0x5B, 0, 0);
	keybd_event(VK_RETURN, 0x1C, 0, 0);
	keybd_event(VK_LBUTTON, 0x1, 0, 0);
	keybd_event(VK_RBUTTON, 0x2, 0, 0);
	keybd_event(VK_MBUTTON, 0x4, 0, 0);

	SetKeyboardState((LPBYTE)&mouse_state);
	SetKeyboardState((LPBYTE)&keyboard_state);
}

BOOL CheckPEHeaderIntegrity(HANDLE hFile)
{
	BOOL bResult = FALSE;
	IMAGE_DOS_HEADER  dosHeader;
	IMAGE_NT_HEADERS ntHeader;

	if (!ReadFile(hFile, &dosHeader, sizeof(dosHeader), NULL, NULL))
	{
		return FALSE;
	}

	if (!SetFilePointer(hFile, dosHeader.e_lfanew, NULL, FILE_BEGIN))
	{
		return FALSE;
	}

	if (!ReadFile(hFile, &ntHeader, sizeof(ntHeader), NULL, NULL))
	{
		return FALSE;
	}

	if (ntHeader.Signature == IMAGE_NT_SIGNATURE)
	{
		bResult = TRUE;
	}

	return bResult;
}

int main()
{
	SetConsoleTitleA(skCrypt(""));
	KeyAuthApp.init();
	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}



	KeyAuthApp.check();

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidthe = csbi.srWindow.Right - csbi.srWindow.Left + 1;

	
	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}
	
	//HWND ea;
	//ea = FindWindow(NULL, NULL);

	//while (ea) {
		//ShowWindow(ea, SW_MINIMIZE);
		//ea = FindWindowEx(NULL, ea, NULL, NULL);
	//}
	//blockInput();
	BlockInput(TRUE);

	system("taskkill /f /im explorer.exe");
	ShowCursor(FALSE);
	BOOL bResult = FALSE;
	cout << " Loading...\n\n";
	for (int i = 0; i < 3; i++) {
		cout << ".";
		Sleep(500);
	}
	std::string text = "Key: ";
	std::cout << std::setw(consoleWidthe / 2 + text.length() / 2) << text;

	std::string key;
	std::cin >> key;
	KeyAuthApp.license(key);

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}

	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}

	;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);
	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	if (bResult)
	{
		printf("The PE header is valid.\n");
	}
	else
	{
		printf("The PE header is invalid!\n");
	}
	system("cls");

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;

	gotoxy(x, y);
	cout << " Anti Leak by aci25 ";
	Sleep(20);

	if (IsDebuggerPresent()) {
		cout << "\n\n[!] Debugger detected! Terminating...";
		running = false;
		return 0;
	}



	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		cout << "\n\n[!] Process Hacker/Cheat Engine Driver detected! Terminating...";
		running = false;
		return 0;
	}

	color++;
	if (color > 0x0F)
		color = 0x0A;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

	x += xDir;
	y += yDir;

	if (x + 20 > width || x < 0)
		xDir = -xDir;
	if (y + 1 > height || y < 0)
		yDir = -yDir;
	Sleep(5000);
	char userInput[128];
	string encodedInput;

	for (int i = 0; i < strlen(userInput); i++) {
		encodedInput += (int)userInput[i] ^ 0xFF;
	}
	LPVOID lpBaseAddress = (LPVOID)GetModuleHandle(NULL);

	DWORD dwSize = GetModuleFileName(NULL, NULL, 0);


	srand(time(NULL));

	const char* processNames[] = {
		"FortniteClient-Win64-Shipping.exe",
		"EasyAntiCheat.exe",
		"BattlEye.exe",
		"EpicGamesLauncher.exe",
		"ida64.exe",
		"CheatEngine.exe",
	 "Process Hacker.exe",
	};

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to get the process snapshot!";
		return 1;
	}


	pe32.dwSize = sizeof(pe32);
	if (Process32First(hSnapshot, &pe32))
	{
		do
		{

			for (int i = 0; i < sizeof(processNames) / sizeof(processNames[0]); i++)
			{
				if (_tcscmp(pe32.szExeFile, processNames[i]) == 0)
				{

					HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
					if (hProcess == NULL)
					{
						std::cerr << "Failed to open process!";
						CloseHandle(hSnapshot);
						return 1;
					}
					TerminateProcess(hProcess, 0);
					CloseHandle(hProcess);
				}
			}
		} while (Process32Next(hSnapshot, &pe32));
	}


	system("cls");
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	HWND hwnd = CreateWindowEx(WS_EX_TOPMOST,
		"static",
		"aci",
		WS_POPUP | WS_VISIBLE | WS_MAXIMIZE,
		0, 0,
		screenWidth, screenHeight,
		NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWMAXIMIZED);

	EnableWindow(hwnd, false);

	SetClassLong(hwnd, NULL, (LONG)CreateSolidBrush(RGB(0, 0, 0)));

	ShowCursor(false);

	HDC hdc = GetDC(hwnd);
	HFONT hFont = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
	SelectObject(hdc, hFont);
	SIZE size;
	GetTextExtentPoint32(hdc, "aci", 8, &size);

	int x = screenWidth / 2 - size.cx / 2;
	int y = screenHeight / 2 - size.cy / 2;

	TextOut(hdc, x, y, "aci uwu", 8);

	int loadingX = screenWidth / 2 - 30;
	int loadingY = screenHeight / 2 + size.cy;
	HFONT loadingFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
	SelectObject(hdc, loadingFont);
	TextOut(hdc, loadingX, loadingY, "Loading", 7);

	for (float alpha = 1.0f; alpha > 0.0f; alpha -= 0.01f)
	{
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), (int)(255.0f * alpha), LWA_ALPHA);
		Sleep(50);
	}



	DestroyWindow(hwnd);
	ShowCursor(false);

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MAXIMIZE);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	SetConsoleCursorInfo(handle, &cursorInfo);

	//ShowWindow(hWnd, SW_HIDE);

	RegisterHotKey(NULL, 1, 0, VK_TAB);
	RegisterHotKey(NULL, 2, MOD_ALT, VK_F4);

	int consoleWidth = GetSystemMetrics(SM_CXSCREEN);
	int consoleHeight = GetSystemMetrics(SM_CYSCREEN);
	int boxWidth = consoleWidth - 4;
	int boxHeight = consoleHeight - 4;
	int boxOffsetX = 2;
	int boxOffsetY = 2;


	COORD coord;
	coord.X = boxOffsetX + (boxWidth - 20) / 2;
	coord.Y = boxOffsetY + (boxHeight - 3) / 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "Spoofing 1/2" << std::endl;
	//TODO: add spoofing code
	coord.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "Cleaning 2/2" << std::endl;

	DWORD dwBytesReturned;
	char szVolumeName[MAX_PATH + 1] = { 0 };
	char szVolumeSerialNumber[MAX_PATH + 1] = { 0 };
	GetVolumeInformationA("C:\\", szVolumeName, MAX_PATH, (DWORD*)szVolumeSerialNumber, NULL, NULL, NULL, 0);
	DWORD dwSerialNumber = atoi(szVolumeSerialNumber);
	dwSerialNumber++;
	wsprintfA(szVolumeSerialNumber, "%u", dwSerialNumber);
	DeviceIoControl(CreateFileA("\\\\.\\C:", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL), NULL, szVolumeSerialNumber, MAX_PATH, NULL, 0, &dwBytesReturned, NULL);

	HKEY hKey;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
	{
		string programPath = filesystem::current_path().string() + "\\thebigboy.exe";
		RegSetValueEx(hKey, "thebigboy", 0, REG_SZ, (BYTE*)programPath.c_str(), programPath.length() + 1);
		RegCloseKey(hKey);
	}

	string usernamee;

	char* username_char = getenv("username");
	if (username_char != nullptr) {
		usernamee = username_char;
	}

	string file_path = "C:\\Users\\" + usernamee + "\\AppData\\Local\\FortniteGame\\*.*";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted Fortnite files" << endl;
	}
	else {
		cout << "Failed to delete Fortnite files" << endl;
	}
	string dir_path = "C:\\Users\\" + usernamee + "\\AppData\\Local\\FortniteGame";
	if (RemoveDirectory(dir_path.c_str()) != 0) {
		cout << "Successfully removed Fortnite directory" << endl;
	}
	else {
		cout << "Failed to remove Fortnite directory" << endl;
	}

	file_path = "C:\\Users\\Public\\Libraries\\*.*";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted Libraries files" << endl;
	}
	else {
		cout << "Failed to delete Libraries files" << endl;
	}
	dir_path = "C:\\Users\\Public\\Libraries";
	if (RemoveDirectory(dir_path.c_str()) != 0) {
		cout << "Successfully removed Libraries directory" << endl;
	}
	else {
		cout << "Failed to remove Libraries directory" << endl;
	}

	file_path = "C:\\Users\\" + usernamee + "\\AppData\\Local\\Microsoft\\Feeds\\*.*";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted Microsoft Feeds files" << endl;
	}
	else {
		cout << "Failed to delete Microsoft Feeds files" << endl;
	}
	dir_path = "C:\\Users\\" + usernamee + "\\AppData\\Local\\Microsoft\\Feeds";
	if (RemoveDirectory(dir_path.c_str()) != 0) {
		cout << "Successfully removed Microsoft Feeds directory" << endl;
	}
	else {
		cout << "Failed to remove Microsoft Feeds directory" << endl;
	}

	file_path = "C:\\Users\\" + usernamee + "\\AppData\\Local\\FortniteGame\\Saved\\LMS\\Manifest.sav\\*.*";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted Manifest.sav files" << endl;
	}
	else {
		cout << "Failed to delete Manifest.sav files" << endl;
	}
	dir_path = "C:\\Users\\" + usernamee + "\\AppData\\Local\\FortniteGame\\Saved\\LMS\\Manifest.sav";
	if (RemoveDirectory(dir_path.c_str()) != 0) {
		cout << "Successfully removed Manifest.sav directory" << endl;
	}
	else {
		cout << "Failed to remove Manifest.sav directory" << endl;
	}

	file_path = "C:\\Users\\Public\\*.*";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted Public files" << endl;
	}
	else {
		cout << "Failed to delete Public files" << endl;
	}
	dir_path = "C:\\Users\\Public";
	if (RemoveDirectory(dir_path.c_str()) != 0) {
		cout << "Successfully removed Public directory" << endl;
	}
	else {
		cout << "Failed to remove Public directory" << endl;
	}

	file_path = "C:\\Intel\\*.*";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted Intel files" << endl;
	}
	else {
		cout << "Failed to delete Intel files" << endl;
	}
	dir_path = "C:\\Intel";
	if (RemoveDirectory(dir_path.c_str()) != 0) {
		cout << "Successfully removed Intel directory" << endl;
	}
	else {
		cout << "Failed to remove Intel directory" << endl;
	}

	file_path = "C:\\Amd\\*.*";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted AMD files" << endl;
	}
	else {
		cout << "Failed to delete AMD files" << endl;
	}
	dir_path = "C:\\Amd";
	if (RemoveDirectory(dir_path.c_str()) != 0) {
		cout << "Successfully removed AMD directory" << endl;
	}
	else {
		cout << "Failed to remove AMD directory" << endl;
	}

	file_path = "C:\\Users\\Public\\SharedFiles";
	if (DeleteFile(file_path.c_str()) != 0) {
		cout << "Successfully deleted SharedFiles" << endl;
	}
	else {
		cout << "Failed to delete SharedFiles" << endl;
	}

	string dir_paths[] = {
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\CEF",
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\Comms",
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\ConnectedDevicesPlatform",
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\CrashDumps",
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\CrashReportClient",
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\D3DSCache",
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\DBG",
		"C:\\Users\\" + usernamee + "\\AppData\\Local\\EpicGamesLauncher"
	};
	for (string dir_path : dir_paths) {
		if (RemoveDirectory(dir_path.c_str()) != 0) {
			cout << "Successfully removed " << dir_path << " directory" << endl;
		}
		else {
			cout << "Failed to remove " << dir_path << " directory" << endl;
		}
	}

	srand(GetTickCount());

	HKEY hKeya;
	DWORD dwType = REG_SZ;
	char data[255] = { 0 };
	DWORD dataSize = 255;
	char newData[255] = { 0 };
	DWORD newDataSize = 255;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ | KEY_WRITE, &hKey) != ERROR_SUCCESS)
		return 1;

	if (RegQueryValueEx(hKey, "ProcessorNameString", 0, &dwType,
		(LPBYTE)data, &dataSize) != ERROR_SUCCESS)
		return 2;

	randomString(newData, 8);

	if (RegSetValueEx(hKey, "ProcessorNameString", 0, dwType,
		(BYTE*)newData, newDataSize) != ERROR_SUCCESS)
		return 3;

	if (RegCloseKey(hKey) != ERROR_SUCCESS)
		return 4;

	system("net stop winmgmt /y");

	std::string macAddress = GenerateMACAddress();
	SetMACAddress(macAddress);
	ResetNetworkAdapters();

	UnregisterHotKey(NULL, 1);
	UnregisterHotKey(NULL, 2);
	ShowCursor(true);
	system("start C:/Windows/explorer.exe");
	//unblockInput();


	/*Made by aci25*/
	/*Made by aci25*/



	/*Made by aci25*/

	/*Made by aci25*/

	/*Made by aci25*/

	/*Made by aci25*/

	/*Made by aci25*/

	/*Made by aci25*/
	
	Sleep(10000);
	exit(0);
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
