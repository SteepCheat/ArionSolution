#pragma warning(disable : 4530)

#define _CRT_SECURE_NO_WARNINGS


#include <Windows.h>
#include <psapi.h>
#include <d3d11.h>
#include <iostream>
#include <string>
#include <cassert>
#include <emmintrin.h>
#include <tlhelp32.h>
#include <winternl.h>
#include <signal.h>

#include <emmintrin.h>
#include <tlhelp32.h>
#include <winternl.h>

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include <Wininet.h>
#pragma comment(lib, "wininet.lib")




#include <iostream>
#include <tlhelp32.h>
#include <psapi.h>
#include "Main.h"

#include "Vars.h"
#include <chrono>
#include <random>
#include "xorstr.h"
#include "jopa.h"
#include "Offsets.h"
#include "Math.h"


DWORD g_PID;
uint64_t u_Base;
uint64_t g_Base;
bool g_Locked;
#define CTL_CODE(DeviceType, Function, Method, Access) (  ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))
constexpr DWORD init_code = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x775, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
constexpr DWORD read_code = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x776, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
constexpr DWORD write_code = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x777, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

class driver_manager {
	HANDLE m_driver_handle = nullptr;

	struct info_t {
		UINT64 target_pid = 0;
		UINT64 target_address = 0x0;
		UINT64 buffer_address = 0x0;
		UINT64 size = 0;
		UINT64 return_size = 0;
		UINT64 GA = 0;
		UINT64 UP = 0;
	};

public:
	driver_manager(const char* driver_name, DWORD target_process_id) {
		m_driver_handle = CreateFileA(driver_name, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		attach_to_process(target_process_id);
	}

	void attach_to_process(DWORD process_id) {
		info_t io_info;

		io_info.target_pid = process_id;

		DeviceIoControl(m_driver_handle, init_code, &io_info, sizeof(io_info), &io_info, sizeof(io_info), nullptr, nullptr);
		g_Base = io_info.GA;
		u_Base = io_info.UP;
		Sleep(10000);
	}

	template<typename T> T RPM(const UINT64 address) {
		info_t io_info;
		T read_data;

		io_info.target_address = address;
		io_info.buffer_address = (UINT64)&read_data;
		io_info.size = sizeof(T);

		DeviceIoControl(m_driver_handle, read_code, &io_info, sizeof(io_info), &io_info, sizeof(io_info), nullptr, nullptr);
		if (!io_info.buffer_address)
			std::cout << "read_data is null" << std::endl;
		return read_data;
	}

	template<typename T> bool WPM(const UINT64 address, const T buffer) {
		info_t io_info;

		io_info.target_address = address;
		io_info.buffer_address = (UINT64)&buffer;
		io_info.size = sizeof(T);

		DeviceIoControl(m_driver_handle, write_code, &io_info, sizeof(io_info), &io_info, sizeof(io_info), nullptr, nullptr);
		return io_info.return_size == sizeof(T);
	}
};

driver_manager* gDriver;

#define safe_read(Addr, Type) gDriver->RPM<Type>(Addr)
#define safe_write(Addr, Data, Type) gDriver->WPM<Type>(Addr, Data)
#define safe_memcpy(Dst, Src, Size) driver::write_memory(Sock, pid, Dst, driver::read_memory(Sock, pid, Src, 0, Size), Size)


#include "WeaponsData.h"
#include "BasePlayer.h"
#include "MiscFuncs.h"
#include "Weapon.h"
#include "Aim.h"

#include <thread>





DWORD GetPID(const std::wstring& procname);
DWORD RPid();
BasePlayer* AimEntity = nullptr;


#define AllocCons 0
using namespace std;

void InitCheat();
void InitLockalPlayer();
void MainLoop();
void Switch(int index);


long long firstentry = 0;

UINT64 TodCycle = 0;
bool panic = false;

//FACE AddUtils





using namespace std;

string replaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}


void Entity() {
	DWORD64 Id = LocalPlayer.BasePlayer->GetActiveWeapon()->GetItemID();
	if (Id == 1525520776 || Id == 200773292) return;

	static UINT64 oPlayerList = 0;
	if (!oPlayerList) {
		UINT64 val = safe_read(g_Base + oBasePlayer, UINT64);
		UINT64 st = safe_read(val + 0xB8, UINT64);
		UINT64 list = safe_read(st + 0x8, UINT64);
		oPlayerList = safe_read(list + 0x28, UINT64);
	}

	int EntityCount = safe_read(oPlayerList + 0x10, int);
	UINT64 EntityBuffer = safe_read(oPlayerList + 0x18, UINT64);
	for (int i = 0; i < EntityCount; i++)
	{
		auto Player = (BasePlayer*)safe_read(EntityBuffer + 0x20 + (i * 0x8), UINT64);
		if (!Player || Player == LocalPlayer.BasePlayer || !Player->IsValid())
			continue;
		if (Vars::Aim::VisibleCheck) {
			if (!Player->IsVisible())
				continue;
		}

		if (AimFov(Player) > Vars::Aim::Fov) continue;
		if (Vars::Aim::IgnoreTeam) {
			UINT64 EntitySID = Player->GetSteamID();
			int size = LocalPlayer.BasePlayer->GetTeamSize();
			for (int j = 0; j < size; j++) {
				UINT64 SlotSID = LocalPlayer.BasePlayer->IsTeamMate(j);
				if (SlotSID == EntitySID)
					continue;
			}
		}
		AimEntity = Player;
		Aim(AimEntity);
	}
	return;
}


void InitLockalPlayer()
{
	long long i = 0;
	UINT64  ObjMgr = safe_read(u_Base + oGameObjectManager, UINT64);
	UINT64  Obj = safe_read(ObjMgr + 0x8, UINT64);

	bool LP_isValid = false;

	for (UINT64 Obj = safe_read(ObjMgr + 0x8, UINT64); (Obj && (Obj != safe_read(ObjMgr, UINT64))); Obj = safe_read(Obj + 0x8, UINT64))
	{
		UINT64 GameObject = safe_read(Obj + 0x10, UINT64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);
		if (Tag == 6 || Tag == 5 || Tag == 20011)
		{
			UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
			UINT64 Entity = safe_read(ObjClass + 0x18, UINT64);

			if (Tag == 6)
			{
				BasePlayer* Player = (BasePlayer*)safe_read(Entity + 0x28, UINT64);
				if (safe_read(safe_read(GameObject + 0x60, UINT64), UINT64) == 0x616C506C61636F4C)
				{

					LP_isValid = true;
					LocalPlayer.BasePlayer = Player;
					firstentry = Obj;
					AimEntity = Player;
					if (TodCycle && LocalPlayer.pViewMatrix)
						return;
				}
			}
			else if (Tag == 5)
			{
				UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
				UINT64	Entity = safe_read(ObjClass + 0x18, UINT64);
				LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);
			}
			else if (Tag == 20011)
			{
				UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
				UINT64	Entity = safe_read(ObjClass + 0x18, UINT64);
				UINT64 Dome = safe_read(Entity + 0x28, UINT64);
				TodCycle = safe_read(Dome + 0x38, UINT64);
			}
		}
	}
}

DWORD RPid()
{
	if (g_PID) {
		if (!safe_read(g_Base, int)) {
			std::cout << "Rust closed...(or driver fail)" << std::endl;
			std::cin.get();
			exit(1);
		}
		return g_PID;
	}
	else {
		DWORD pid = GetPID(L"RustClient.exe");

		if (!pid) {
			std::cout << "Rust closed..." << std::endl;
			std::cin.get();
			exit(1);
		}
		return pid;
	}
}

DWORD GetPID(const std::wstring& procname)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!procname.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!procname.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}
#include "Main.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}



int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// Create application window
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, LOADER_BRAND1, NULL };
	RegisterClassEx(&wc);
	main_hwnd = CreateWindow(wc.lpszClassName, LOADER_BRAND1, WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (!CreateDeviceD3D(main_hwnd)) {
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	ShowWindow(main_hwnd, SW_HIDE);
	UpdateWindow(main_hwnd);

	// Setup Dear ImGui context
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr; //crutial for not leaving the imgui.ini file
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(main_hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);


	DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	auto x = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
	auto y = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	

	g_PID = RPid();
	gDriver = new driver_manager("\\\\.\\rustzxcursedtest", g_PID);
	if (!gDriver) {
		std::cout << "Connection failed" << std::endl;
		Sleep(10000);
		return 0;
	}
	InitLockalPlayer();
	while (msg.message != WM_QUIT)
	{
		
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
			ImGui::SetNextWindowBgAlpha(1.0f);

			ImGui::Begin(LOADER_BRAND, &loader_active, window_flags);
			{
				ImGui::Checkbox("AimBot", &Vars::Aim::AimBot);
				ImGui::Checkbox("VisibleCheck", &Vars::Aim::VisibleCheck);
				ImGui::Checkbox("IgnoreTeam", &Vars::Aim::IgnoreTeam);
				ImGui::Checkbox("Admin Mode", &Vars::Misc::FakeAdmin);
				ImGui::Checkbox("Automatic", &Vars::Misc::automatic);
				ImGui::Checkbox("No Spread", &Vars::Misc::anti_spread);
				ImGui::Checkbox("No Recoil", &Vars::Misc::no_recoil);
				ImGui::Checkbox("FatBullet", &Vars::Misc::FatBullet);
				ImGui::Checkbox("Spider Man", &Vars::Misc::SpiderMan);
				ImGui::Checkbox("Infinity Jump", &Vars::Misc::InfinityJump);
				ImGui::Checkbox("AlwaysDay", &Vars::Misc::AlwaysDay);
				if (Vars::Misc::AlwaysDay)
					ImGui::SliderInt("Time", &Vars::FloatAntInt::TimeOfDay, 0, 24);
				ImGui::Checkbox("High Jump", &Vars::Misc::SetGravitu);
				if (Vars::Misc::SetGravitu)
					ImGui::SliderFloat("Gravity", &Vars::FloatAntInt::JumpValue, 0, 2);
				if (ImGui::Button("Init Cheat"))
					InitLockalPlayer();

			}
			ImGui::End();
		}
		ImGui::EndFrame();
		
		if (LocalPlayer.BasePlayer->IsValid()) {
			Misc(TodCycle);
			Entity();
			WeaponFix(LocalPlayer.BasePlayer->GetActiveWeapon());
		}
		else
			InitLockalPlayer();

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		// Handle loss of D3D9 device
		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ResetDevice();
		}
		if (!loader_active) {
			msg.message = WM_QUIT;
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	DestroyWindow(main_hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}
