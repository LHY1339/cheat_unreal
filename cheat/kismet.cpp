#include "kismet.h"

#include "gvalue.h"
#include "gdefine.h"

bool kismet::is_key_down(const int& key)
{
	return (GetAsyncKeyState(key) & 0x8000) && GetForegroundWindow() == get_window();
}

HWND kismet::get_window()
{
	return FindWindowW(WINDOW_CLASS_NAME, WINDOW_NAME);
}
