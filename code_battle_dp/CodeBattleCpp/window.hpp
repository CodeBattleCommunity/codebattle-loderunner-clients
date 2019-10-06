#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <io.h>
#include <fcntl.h> 

#include "vec.hpp"

class window {
public:
	enum window_flags {
		flags_none = 0x0,
		flags_console = 0x1,
	};
public:
	static std::shared_ptr<window>& instance() {
		static std::shared_ptr<window> inst = std::make_shared<window>();
		return inst;
	}
	void initialize(HINSTANCE hInstance, window_flags flags = flags_none);
	bool tick();
	HWND get_window_handle() { return window_; }
protected:
	static void create_console();
	static HWND create_window(HINSTANCE hInstance, vec window_size);
	static LRESULT WINAPI __WndInit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	HWND window_;
};

#define app_window window::instance()