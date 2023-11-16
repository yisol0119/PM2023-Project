#pragma once
#include <GL/freeglut.h>
#include "Bubble.h"
#include "Constants.h"
class Enemy
{
	friend class Collision; //Collision class¿¡ private º¯¼ö(width, center height)»ç¿ë ±ÇÇÑ ºÎ¿©
public:
	enum FACE { LEFT, RIGHT };
	enum HORIZONTAL_STATE { HSTOP, MOVE };
	enum VERTICAL_STATE { VSTOP, JUMP, FALL };

	Enemy(float x, float y, float z, float s);
	Enemy(const Enemy& enemy) = default;

	void move();
	void draw();

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

	void inittexture();

	Bubble shootBubble();

private:
	float center[3];
	float size;
	float velocity[3];
	float boundary[4];

	FACE face;
	HORIZONTAL_STATE horizontalState;
	VERTICAL_STATE verticalState;
	Texture texture;

};
