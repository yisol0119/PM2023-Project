#pragma once

#include <GL/freeglut.h>

class Player
{
public:
	enum FACE { LEFT, RIGHT };
	enum HORIZONTAL_STATE { HSTOP, MOVE };
	enum VERTICAL_STATE { VSTOP, JUMP, FALL };

	Player(float x, float y, float z, float s);

	void move();
	void draw() const;

	void setFace(FACE f);
	void setHorizontalState(HORIZONTAL_STATE hs);
	void setVerticalState(VERTICAL_STATE vs);
	void setVelocityX(float velocity);
	void setVelocityY(float velocity);

	

	const float* getCenter() const;
	const float getSize() const;

	FACE getFace() const;

	HORIZONTAL_STATE getHorizontalState() const;
	VERTICAL_STATE getVerticalState() const;
	

	
private:
	float center[3];
	float size;
	float velocity[3];
	float boundary[4];
	FACE face;
	HORIZONTAL_STATE horizontalState;
	VERTICAL_STATE verticalState;
};

