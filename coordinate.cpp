#include "coordinate.h"
#include <cmath>

Coordinate::Coordinate(float xCoord, float yCoord) : x(xCoord), y(yCoord) {}

// getters

float Coordinate::getX() const {
	return x;
}

float Coordinate::getY() const {
	return y;
}

// setters

void Coordinate::setX(float xCoord) {
	x = xCoord;
}

void Coordinate::setY(float yCoord) {
	y = yCoord;
}

void Coordinate::setCoord(float new_x, float new_y) {
	x = new_x;
	y = new_y;
}

// others

void Coordinate::rotate_coord(Coordinate center, float rad) { // rotates (x,y) rad radians around the origin (x0, y0) by changing the values stored at x and y

	// bring to origin (center of screen)
	x -= center.getX();
	y -= center.getY();

	float prev_x = x;
	float prev_y = y;

	// rotate around center of screen
	x = prev_x * cos(rad) - prev_y * sin(rad);
	y = prev_x * sin(rad) + prev_y * cos(rad);

	// bring back to original starting point
	x += center.getX();
	y += center.getY();
}