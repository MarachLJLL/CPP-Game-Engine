#ifndef PLATFORM_COMMON_H
#define PLATFORM_COMMON_H

struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT, // Should be last item
};

struct Input {
	Button_State buttons[BUTTON_COUNT];
};

#endif

