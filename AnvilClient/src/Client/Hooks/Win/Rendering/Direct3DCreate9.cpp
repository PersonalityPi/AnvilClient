#include <Client/Hooks/WinHooks.hpp>

using namespace Anvil::Client::Hooks;

LRESULT CALLBACK MsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }

HookedFunction(WinHooks, void*, Direct3DCreate9, __stdcall, uint32_t p_SdkVersion)
{
	auto s_IDirect3D9 = static_cast<LPDIRECT3D9>(o_Direct3DCreate9(p_SdkVersion));
	
	WriteLog("Direct3DCreate9 called.");

	
	/*WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassEx(&wc);
	auto hWnd = CreateWindow("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	LPDIRECT3DDEVICE9 pd3dDevice;
	s_IDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pd3dDevice);
	auto pVTable = reinterpret_cast<DWORD*>(pd3dDevice);
	pVTable = reinterpret_cast<DWORD*>(pVTable[0]);*/

	auto pVTable = reinterpret_cast<DWORD*>(s_IDirect3D9);
	pVTable = reinterpret_cast<DWORD*>(pVTable[0]);

	auto s_CreateDevice = pVTable[16];

	WriteLog("CreateDevice: %p", s_CreateDevice);

	DeclareHookAtOffset(Direct3D_CreateDevice, s_CreateDevice);
	//DestroyWindow(hWnd);

	WriteLog("DirectX Init Hooks installed.");

	return s_IDirect3D9;
}
