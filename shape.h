#ifndef SHAPE_H
#define SHAPE_H
#include "utils.h"
#include "coordinate.h"
#include <vector>

class Shape {
private:
	std::vector<Coordinate> coords; // basically ArrayList from Java
	u32 color;
	float rotation; // the amount that the shape has been rotated in radinas

public:
	// constructor

	Shape(std::vector<Coordinate> initCoords, u32 initColor);
	std::vector<Coordinate> getCoords() const;
	Coordinate getCoord(int index) const;
	u32 getColor() const;
	float getRotataion() const;


	// setters

	void setCoords(std::vector<Coordinate> new_coords);
	void setCoord(int index, float x, float y);
	void setColor(u32 new_color);

	// other functions

	void addCoord(Coordinate new_coord);
	void rotateCoords(Coordinate center, float rad);
	void drawShape();
};
#endif