#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
private:
	float x;
	float y;

public:
	Coordinate(float xCoord, float yCoord);

	// getters

	float getX() const;
	float getY() const;

	// setters

	void setX(float xCoord);
	void setY(float yCoord);
	void setCoord(float new_x, float new_y);

	// others

	void rotate_coord(Coordinate center, float rad);
};

#endif