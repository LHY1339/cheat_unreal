#pragma once
#include <Windows.h>
#include <string>

using fn_post_render = void(__thiscall*)(void*, void*);
using fn_wnd_proc = WNDPROC;

namespace SDK
{
	class UWorld;
	class APlayerController;
	class UCanvas;
	class UEngine;
}

struct s_mouse
{
	int x = 0;
	int y = 0;
	bool left = false;
};

namespace gvalue
{
	inline HINSTANCE dll_inst;
	inline void** viewport_client_vtb;
	inline fn_post_render def_post_render;
	inline fn_wnd_proc def_wnd_proc;

	inline SDK::UWorld* world;
	inline SDK::APlayerController* controller;
	inline SDK::UCanvas* canvas;
	inline SDK::UEngine* engine;
	inline float delta_time;

	inline bool menu_open = true;
	inline bool is_clean = false;
	inline bool is_exit = false;
	inline s_mouse mouse = {};
	inline std::string version;
}