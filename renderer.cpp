#include "utils.h"
#include "renderer.h"
#include "main.h"

void clear_screen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;

		}
	}
}

void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;

		}
	}
}



void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {
	// Change to pixels
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

// The rendering of all shapes that are not rectangles might possibly be optimized by
// having functions to calculate the number of pixels it has to jump between lines
// and how many pixels on that line to fill so that it won't need an if statement
// these calculations could take longer though so need to check. regardless
// each shape is individually cachle friendly, but separate shapes won't be.

void draw_right_tri_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	// formula is pixel > or < ax+b
	float a = ((float) (y0 - y1)) / ((float) (x1 - x0));
	float b = y1 - y0;

	int start_x = clamp(0, min(x0, x1), render_state.width);
	int end_x = clamp(0, max(x0, x1), render_state.width);
	int start_y = clamp(0, min(y0, y1), render_state.height);
	int end_y = clamp(0, max(y0, y1), render_state.height);

	float flip_factor = 1;
	if (y0 > y1) flip_factor *= -1;

	for (int y = start_y; y < end_y; y++) {
		u32* pixel = (u32*)render_state.memory + start_x + y * render_state.width;
		for (int x = start_x; x < end_x; x++) {
			if ((y - y0) * flip_factor < (a * (x - x0) + b) * flip_factor ) *pixel = color;
			pixel++;
		}
	}
	/*
	draw_right_tri_in_pixels(200, 300, 0, 0, 0xffffff);
	draw_right_tri_in_pixels(200, 300, 0, 400, 0xffffff);
	draw_right_tri_in_pixels(200, 300, 300, 400, 0xffffff);
	*/
}

void draw_right_tri(float x0, float y0, float x1, float y1, u32 color) {
	x0 *= render_state.height * render_scale;
	y0 *= render_state.height * render_scale;
	x1 *= render_state.height * render_scale;
	y1 *= render_state.height * render_scale;

	x0 += render_state.width / 2.f;
	y0 += render_state.height / 2.f;
	x1 += render_state.width / 2.f;
	y1 += render_state.height / 2.f;
	draw_right_tri_in_pixels(x0, y0, x1, y1, color);
}



void draw_tri_by_points_in_pixels(int ax, int ay, int bx, int by, int cx, int cy, u32 color) {
	int coords[6] = { ax, ay, bx, by, cx, cy };

	int temp_x;
	int temp_y;

	// bubble sort with 3 elements in descending order of y-value
	for (int i = 1; i < 4; i += 2) // this for loop only iterates twice
		if (coords[i] < coords[i + 2]) {
			temp_x = coords[i + 1];
			temp_y = coords[i + 2];
			coords[i + 1] = coords[i - 1];
			coords[i + 2] = coords[i];
			coords[i - 1] = temp_x;
			coords[i] = temp_y;
		}
	if (coords[1] < coords[3]) {
		temp_x = coords[2];
		temp_y = coords[3];
		coords[2] = coords[0];
		coords[3] = coords[1];
		coords[0] = temp_x;
		coords[1] = temp_y;
	}

	if (ax == bx || ax == cx || bx == cx) {
		if (ax == bx && bx == cx) return;
		float slope = calc_slope(coords[0], coords[4], coords[1], coords[5]);
		float constant = coords[1] - slope * coords[0]; // b = y - ax
		float x_val = (coords[3] - constant) / slope; // x = (y - b) / a
		if (coords[1] == coords[3]) { // avoid 0 division error
			color = 0x0000ff;
			draw_right_tri_in_pixels(coords[2], coords[3], x_val, coords[1], color);
			draw_tri_by_points_in_pixels(coords[2], coords[3], coords[4], coords[5], x_val, coords[3], color);
			return;
		}

		if (coords[1] == coords[5]) {
			color = 0xff0000;
			draw_right_tri_in_pixels(coords[0], coords[3], coords[2], coords[1], color);
			draw_right_tri_in_pixels(coords[0], coords[3], coords[2], coords[5], color);
			return;
		}

		if (coords[3] == coords[5]) { // not rendering right angled triangles with both sides parallel to x and y axis
			color = 0x00ff00;
			//draw_right_tri_in_pixels(coords[2], coords[3], x_val, coords[5], color);
			//draw_tri_by_points_in_pixels(coords[2], coords[3], coords[0], coords[1], x_val, coords[3], color);
			return;
		}
	}

	int start_x = clamp(0, min3(ax, bx, cx), render_state.width);
	int end_x = clamp(0, max3(ax, bx, cx), render_state.width);

	int y_loop_bounds[3];

	y_loop_bounds[0] = clamp(0, coords[1], render_state.height - 1);
	y_loop_bounds[1] = clamp(0, coords[3], render_state.height);
	y_loop_bounds[2] = clamp(0, coords[5], render_state.height);
	// 3 lines above can be put into a loop but is more readable this way

	// get formulas for lines of sides of triangle in slope y-intercept form for the conditional of the if statement in the loop
	
	/*
	line order of slopes and constants based on ordered y-value (coords[]):
	0. ab (coords[0:2] to coords[2:4]
	1. ac (coords[0:2] to coords[4:6]
	2. bc (coords[2:4] to coords[2:6]
	*/

	float slopes[3];
	slopes[0] = calc_slope(coords[0], coords[2], coords[1], coords[3]);
	slopes[1] = calc_slope(coords[0], coords[4], coords[1], coords[5]);
	slopes[2] = calc_slope(coords[2], coords[4], coords[3], coords[5]);

	float slope_sign[3];
	slope_sign[0] = slopes[0] / abs(slopes[0]);
	slope_sign[1] = slopes[1] / abs(slopes[1]);
	slope_sign[2] = slopes[2] / abs(slopes[2]);

	float constants[3];
	constants[0] = coords[1] - slopes[0] * coords[0]; // b = y - ax 
	constants[1] = coords[5] - slopes[1] * coords[4];
	constants[2] = coords[5] - slopes[2] * coords[4];
	// point c (coords[5], coords[4]) are on both lines ac and bc



	u32* pixel;
	for (int y = y_loop_bounds[0]; y > y_loop_bounds[1]; y--) {
		pixel = (u32*)render_state.memory + start_x + y * render_state.width;
		for (int x = start_x; x < end_x; x++) {
			if (
				((x * slope_sign[0] < coords[0] * slope_sign[0] && slopes[0] * x + constants[0] >= y) != // >= -> equal sign needed to remove gaps. != acts as logical XOR
				(x * slope_sign[1] < coords[0] * slope_sign[1] && slopes[1] * x + constants[1] >= y)) ||
				(x == coords[0] && y == coords[1]) ||
				(x == coords[0] && slope_sign[0] != slope_sign[1])
				) *pixel = 0xff0000;
			pixel++;
		}
	}

	for (int y = y_loop_bounds[1]; y > y_loop_bounds[2]; y--) {
		pixel = (u32*)render_state.memory + start_x + y * render_state.width;
		for (int x = start_x; x < end_x; x++) {
			if (
				((x * slope_sign[2] > coords[4] * slope_sign[2] && slopes[2] * x + constants[2] <= y) != 
				(x * slope_sign[1] > coords[4] * slope_sign[1] && slopes[1] * x + constants[1] <= y)) ||
				(x == coords[4] && y == coords[5]) ||
				(x == coords[4] && slope_sign[2] != slope_sign[1])
				/*
				Boolean algebra alternative for != as xor by instead using && and ||:
				(!((x * slope_sign[2] > coords[4] * slope_sign[2] && slopes[2] * x + constants[2] <= y) && (x * slope_sign[1] > coords[4] * slope_sign[1] && slopes[1] * x + constants[1] <= y))
				&& ((x * slope_sign[2] > coords[4] * slope_sign[2] && slopes[2] * x + constants[2] <= y) || (x * slope_sign[1] > coords[4] * slope_sign[1] && slopes[1] * x + constants[1] <= y))) ||
				(x == coords[4] && y == coords[5]) ||
				(x == coords[4] && slope_sign[2] != slope_sign[1])
				*/
				) *pixel = color;
			pixel++;
		}
	}
	
}

void draw_tri(float ax, float ay, float bx, float by, float cx, float cy, u32 color) {
	// Change to pixels
	ax *= render_state.height * render_scale;
	ay *= render_state.height * render_scale;
	ax += render_state.width / 2.f;
	ay += render_state.height / 2.f;

	bx *= render_state.height * render_scale;
	by *= render_state.height * render_scale;
	bx += render_state.width / 2.f;
	by += render_state.height / 2.f;

	cx *= render_state.height * render_scale;
	cy *= render_state.height * render_scale;
	cx += render_state.width / 2.f;
	cy += render_state.height / 2.f;
	
	int iax = (int)ax;
	int ibx = (int)bx;
	int icx = (int)cx;
	int iay = (int)ay;
	int iby = (int)by;
	int icy = (int)cy;

	draw_tri_by_points_in_pixels(iax, iay, ibx, iby, icx, icy, color);
}

void draw_quad(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy, u32 color){ 
	// could draw weird depending on input coord order -> need to check
	// a much more cache frienly version can be made
	draw_tri(ax, ay, bx, by, cx, cy, color);
	draw_tri(bx, by, cx, cy, dx, dy, color);
}

void draw_circle_in_pixels(int x0, int y0, int r, u32 color) {
	int start_x = clamp(0, x0 - r, render_state.width);
	int end_x = clamp(0, x0 + r, render_state.width);
	int start_y = clamp(0, y0 - r, render_state.height);
	int end_y = clamp(0, y0 + r, render_state.height);
	
	for (int y = start_y; y < end_y; y++) {
		u32* pixel = (u32*)render_state.memory + start_x + y * render_state.width;
		for (int x = start_x; x < end_x; x++) {
			if (sqrt(pow(x-x0,2) + pow(y-y0,2)) < r) *pixel = color;
			// the if conditional uses one only square root (square root is slow)
			pixel++;
		}
	}
}

void draw_circle(float x, float y, float half_size, u32 color) {
	// Change to pixels
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	draw_circle_in_pixels(x, y, half_size, color);
}

void draw_parabola_in_pixels(int x0, int y0, int x1, int y1, u32 color) {
	// (x0, y0) is the vertex of the parabola
	// x1 is the horizontal distance from the root to the vertex
	// y1 is the veritcal distance from the root to the vertex
	int start_x = clamp(0, x0 - x1, render_state.width);
	int end_x = clamp(0, x0 + x1, render_state.width);
	int start_y = clamp(0, y0 - y1, render_state.height);
	int end_y = clamp(0, y0 + y1, render_state.height);

	for (int y = start_y; y < end_y; y++) {
		u32* pixel = (u32*)render_state.memory + start_x + y * render_state.width;
		for (int x = start_x; x < end_x; x++) {
			if (true) *pixel = color;
			pixel++;
		}
	}
}
void draw_ellipse_in_pixels();

void rotate_point(float x0, float y0, float* x, float* y, float rad) { // rotates (x,y) rad radians around the origin (x0, y0) by changing the values stored at x and y

	// bring to origin (center of screen)
	*x -= x0;
	*y -= y0;

	float prev_x = *x;
	float prev_y = *y;

	// rotate around center of screen
	*x = prev_x * cos(rad) - prev_y * sin(rad);
	*y = prev_x * sin(rad) + prev_y * cos(rad);

	// bring back to original starting point
	*x += x0;
	*y += y0;

}
