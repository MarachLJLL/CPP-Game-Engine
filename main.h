#ifndef MAIN_H
#define MAIN_H

# include <windows.h>

global_variable bool running = true;

struct Render_State {
	void* memory;
	int width;
	int height;
	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#define process_button(b, vk)\
case vk: {\
input.buttons[b].changed = is_down != input.buttons[BUTTON_UP].is_down;\
input.buttons[b].is_down = is_down;\
} break;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);

#endif