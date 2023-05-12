#include "renderer.h"
//#include "entity.h"

struct Entity_Struct {
	float x_pos;
	float y_pos;
	float half_size_x;
	float half_size_y;
	float x_speed;
	float y_speed;
	u32 color;
};

void initEntity_Struct(struct Entity_Struct* e, float x_pos, float y_pos, float half_size_x, float half_size_y, float x_speed, float y_speed, u32 color) {
	e->x_pos = x_pos;
	e->y_pos = y_pos;
	e->half_size_x = half_size_x;
	e->half_size_y = half_size_y;
	e->x_speed = x_speed;
	e->y_speed = y_speed;
	e->color = color;
}

void draw_rect_Entity_Struct(Entity_Struct e) {
	draw_rect(e.x_pos, e.y_pos, e.half_size_x, e.half_size_y, e.color);
}

bool check_collision(Entity_Struct e1, Entity_Struct e2) {
	if (e1.x_pos == e2.x_pos && e1.y_pos == e2.y_pos) return true; // right on top of each other
	return (
	// check for horizontal overlap
	(
	(e1.x_pos < e2.x_pos && e1.x_pos + e1.half_size_x >= e2.x_pos - e2.half_size_x) || // e1 is to the left of e2
	(e1.x_pos > e2.x_pos && e1.x_pos - e1.half_size_x <= e2.x_pos + e2.half_size_x) // e1 is to the right of e2
	) && // this && is to check that there is both horizontal and vertical overlap
	// check for vertical overlap
	(
	(e1.y_pos < e2.y_pos && e1.y_pos + e1.half_size_y >= e2.y_pos - e2.half_size_y) || // e1 is below e2
	(e1.y_pos > e2.y_pos && e1.y_pos - e1.half_size_y <= e2.y_pos + e2.half_size_y) // e1 is above e2
	)
	);
}