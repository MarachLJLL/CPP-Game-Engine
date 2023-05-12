#include "utils.h"
#include <vector>
#include "coordinate.h"
#include "shape.h"
#include "renderer.h"

// constructor

Shape::Shape(std::vector<Coordinate> initCoords, u32 initColor) : coords(initCoords), color(initColor), rotation(0) {}

// getters

std::vector<Coordinate> Shape::getCoords() const {
	return  coords;
}

Coordinate Shape::getCoord(int index) const {
	return coords[index];
}

u32 Shape::getColor() const {
	return color;
}

float Shape::getRotataion() const {
	return rotation;
}

// setters

void Shape::setCoords(std::vector<Coordinate> new_coords) {
	coords = new_coords;
}

void Shape::setCoord(int index, float x, float y) {
	coords[index].setCoord(x, y);
}

void Shape::setColor(u32 new_color) {
	color = new_color;
}

// other functions

void Shape::addCoord(Coordinate new_coord) {
	coords.push_back(new_coord);
}
	
void Shape::rotateCoords(Coordinate center, float rad) {
	for (Coordinate coord : coords) {
		coord.rotate_coord(center, rad);
	}
}
	
void Shape::drawShape() {
	switch (coords.size()) {
	case 1:
		//draw_dot;
		break;
	case 2:
		//draw_line;
		break;
	case 3:
		draw_tri(coords[0].getX(), coords[0].getY(), coords[1].getX(), coords[1].getY(), coords[2].getX(), coords[2].getY(), color);
		break;
	case 4:
		draw_quad(coords[0].getX(), coords[0].getY(), coords[1].getX(), coords[1].getY(), coords[2].getX(), coords[2].getY(), coords[3].getX(), coords[3].getY(), color);
	}
}

