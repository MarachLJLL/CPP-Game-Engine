#ifndef RENDERER_H
#define RENDERER_H
#include "utils.h"


global_variable float render_scale = 0.01f;
#define min3(a, b, c) min(min(a, b), c)
#define max3(a, b, c) max(max(a, b), c)
#define calc_slope(x0, x1, y0, y1) (((float) (y1 - y0)) / ((float) (x1 - x0)))

void clear_screen(u32 color);
void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color);
void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color);

void draw_right_tri_in_pixels(int x0, int y0, int x1, int y1, u32 color);
void draw_right_tri(float x0, float y0, float x1, float y1, u32 color);
void draw_tri_by_points_in_pixels(int ax, int ay, int bx, int by, int cx, int cy, u32 color);
void draw_tri(float ax, float ay, float bx, float by, float cx, float cy, u32 color);

void draw_quad(float ax, float ay, float bx, float by, float cx, float cy, float dx, float dy, u32 color);

void draw_circle(float x, float y, float half_size, u32 color);
void draw_ellipse_in_pixels();
void rotate_point(float x0, float y0, float* x, float* y, float rad);

#endif