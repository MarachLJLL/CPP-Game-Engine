#ifndef ENTITY_H
#define ENTITY_H
#include "coordinate.h"
#include "shape.h"
#include <vector>

class Entity {
private:
	Coordinate position;
	float half_size;
	float x_speed;
	float y_speed;
	float x_acceleration;
	float y_acceleration;
	std::vector<Shape> shapes;

public:
	Entity(Coordinate c_position, float c_half_size, float c_x_speed, float c_y_speed);

	// getters

	Coordinate getPosition() const;
	float getHalfSize() const;
	float getXSpeed() const;
	float getYSpeed() const;
	float getXAcceleration() const;
	float getYAcceleration() const;
	std::vector<Shape> getShapes() const;

	// setters

	void setPosition(Coordinate new_position);
	void setHalfSize(float new_half_size);
	void setXSpeed(float new_x_speed);
	void setYSpeed(float new_y_speed);
	void setXAcceleration(float new_x_acceleration);
	void setYAcceleration(float new_y_acceleration);
	void setShapes(std::vector<Shape> new_shapes);

	// others

	void updatePosition();
	void drawEntity();

};

#endif

