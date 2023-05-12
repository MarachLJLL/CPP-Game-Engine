#include "entity.h"
#include "shape.h"
#include "coordinate.h"

Entity::Entity(Coordinate c_position, float c_half_size, float c_x_speed, float c_y_speed) : position(c_position), half_size(c_half_size), x_speed(c_x_speed), y_speed(c_y_speed) {};

// getters

Coordinate Entity::getPosition() const {
	return position;
}
float Entity::getHalfSize() const {
	return half_size;
}
float Entity::getXSpeed() const {
	return x_speed;
}
float Entity::getYSpeed() const {
	return y_speed;
}
float Entity::getXAcceleration() const {
	return x_acceleration;
}
float Entity::getYAcceleration() const {
	return y_acceleration;
}
std::vector<Shape> Entity::getShapes() const {
	return shapes;
}

// setters

void Entity::setPosition(Coordinate new_position) {
	position = new_position;
}
void Entity::setHalfSize(float new_half_size) {
	half_size = new_half_size;
}
void Entity::setXSpeed(float new_x_speed) {
	x_speed = new_x_speed;
}
void Entity::setYSpeed(float new_y_speed) {
	y_speed = new_y_speed;
}
void Entity::setXAcceleration(float new_x_acceleration) {
	x_acceleration = new_x_acceleration;
}
void Entity::setYAcceleration(float new_y_acceleration) {
	y_acceleration = new_y_acceleration;
}
void Entity::setShapes(std::vector<Shape> new_shapes) {
	shapes = new_shapes;
}

// others

void Entity::updatePosition() {
	for (Shape shape : shapes) {
		for (Coordinate coord : shape.getCoords()) {
			coord.setX(coord.getX() + x_speed);
			coord.setY(coord.getY() + y_speed);
		}
	}
	position.setX(position.getX() + x_speed);
	position.setY(position.getY() + y_speed);
}
void Entity::drawEntity() {
	for (Shape shape : shapes) {
		shape.drawShape();
	}
}