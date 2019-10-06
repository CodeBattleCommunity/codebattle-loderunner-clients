#include "window.hpp"

void window::initialize(HINSTANCE hInstance, window_flags flags) {
	window_ = create_window(hInstance, { 1000,1000 });
	if (window_ == nullptr)
		std::cout << "hwnd == nullptr\n";
	ShowWindow(window_, SW_SHOWDEFAULT);
	UpdateWindow(window_);
	if (flags & flags_console)
		create_console();
}

bool window::tick() {
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			return false;
	}
	return true;
}

void window::create_console() {
	AllocConsole();

	HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
	FILE* COutputHandle = _fdopen(SystemOutput, "w");

	HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
	int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
	FILE* CErrorHandle = _fdopen(SystemError, "w");

	HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
	FILE* CInputHandle = _fdopen(SystemInput, "r");

	std::ios::sync_with_stdio(true);

	freopen_s(&CInputHandle, "CONIN$", "r", stdin);
	freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
	freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);
}

LRESULT WINAPI window::__WndInit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND window::create_window(HINSTANCE hInstance, vec window_size) {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,__WndInit,0,0,
		hInstance,nullptr,nullptr,nullptr,nullptr,
		L"PomoikaGUI",nullptr };
	wc.hIconSm = (HICON)LoadImage(hInstance, NULL, IMAGE_ICON, 16, 16, 0);
	wc.hIcon = (HICON)LoadImage(hInstance, NULL, IMAGE_ICON, 32, 32, 0);
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	RegisterClassEx(&wc);

	RECT wr;
	wr.left = 10;
	wr.right = window_size.x + wr.left;
	wr.top = 10;
	wr.bottom = window_size.y + wr.top;
	AdjustWindowRect(&wr, WS_BORDER | WS_SYSMENU, FALSE);
	return CreateWindowW(L"PomoikaGUI", L"PomoikaGUI",
		WS_BORDER | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, hInstance, nullptr);
} 