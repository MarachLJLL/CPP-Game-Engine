#include "entity_struct.cpp"
#include "shape.h"
#include "utils.h"
#include "renderer.h"


#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

Entity_Struct player1;
Entity_Struct ground1;
Entity_Struct ground2;
Entity_Struct ground3;
// also not sure why i can't initialize this in the simulate game function

bool initialized = false;

float speed = 50.f;

// testing rotate_point
float ax = 0;
float ay = 0;
float bx = 0;
float by = 10;
float cx = 0;
float cy = 0;

float ax1 = 27;
float ay1 = 7;
float bx1 = 27;
float by1 = 57;
float cx1 = 47;
float cy1 = 8;

void simulate_game(Input* input, float dt) {
	// find out why I can't call initEntity_Struct() outside of simulate_game
	if (!initialized) {
		initEntity_Struct(&player1, 20.f, -20.f, 2.f, 2.f, 0.f, 0.f, 0x0000ff);
		initEntity_Struct(&ground1, 0.f, -50.f, 100.f, 20.f, 0.f, 0.f, 0x00ff00);
		initEntity_Struct(&ground2, -30.f, -40.f, 20.f, 20.f, 0.f, 0.f, 0x00ff00);
		initEntity_Struct(&ground3, 30.f, -10.f, 20.f, 1.f, 0.f, 0.f, 0x00ffff);
		initialized = true;
	}

	/*
	* CHECK COLISSIONS
	*/
	player1.y_speed -= 100 * dt;
	if (check_collision(player1, ground1) || check_collision(player1, ground2) || check_collision(player1, ground3)) {
		player1.y_speed = max(0, player1.y_speed);
	}

	/*
	* UPDATE POSITIONS
	*/

	player1.y_pos += player1.y_speed * dt;

	//y_speed -= 0.1f;
	if (pressed(BUTTON_UP)) player1.y_speed = 60.f;
	//if (is_down(BUTTON_DOWN)) player1.y_pos -= speed * dt * 0.1;
	if (is_down(BUTTON_LEFT)) player1.x_pos -= speed * dt;
	if (is_down(BUTTON_RIGHT)) player1.x_pos += speed * dt;
	if (is_down(BUTTON_DOWN)) {
		float rad_to_rotate = 3 * dt;
		rotate_point(-6, -6, &ax, &ay, rad_to_rotate);
		rotate_point(3, 3, &bx, &by, rad_to_rotate);
		rotate_point(6, 6, &cx, &cy, rad_to_rotate);

		rotate_point(50, 20, &ax1, &ay1, rad_to_rotate);
		rotate_point(50, 20, &bx1, &by1, rad_to_rotate);
		rotate_point(50, 20, &cx1, &cy1, rad_to_rotate);

		rotate_point(0, 0, &player1.x_pos, &player1.y_pos, rad_to_rotate);
	}


	/*
	* DRAW EVERYTHING
	*/

	// background
	clear_screen(0xaaaaff);
	draw_rect_Entity_Struct(player1);
	
	draw_rect_Entity_Struct(ground1);
	draw_rect_Entity_Struct(ground2);
	draw_rect_Entity_Struct(ground3);
	//draw_rect_in_pixels(900, 200, 1100, 400, 0x000000);
	//draw_circle_in_pixels(900, 200, 50, 0xffffff);
	draw_tri(ax1, ay1, bx1, by1, cx1, cy1, 0xffffff);
	draw_tri(ax, ay, bx, by, cx, cy, 0x000000);
	
	draw_tri(player1.x_pos + 2, player1.y_pos + 2, player1.x_pos + 3, player1.y_pos + 5, player1.x_pos + 4, player1.y_pos + 2, 0xeeeeee);
	
}