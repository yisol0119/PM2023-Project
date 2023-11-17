#pragma once

#include <GL/freeglut.h>
#include "Bubble.h"
#include "Constants.h"

class Player
{
	friend class Collision; //Collision class에 private 변수(width, center height)사용 권한 부여
	friend class Stage;

public:
	enum FACE { LEFT, RIGHT };
	enum HORIZONTAL_STATE { HSTOP, MOVE };
	enum VERTICAL_STATE { VSTOP, JUMP, FALL };
	Player() = default;
	Player(float x, float y, float z, float s);
	Player(const Player& player) = default;

	void move();
	void draw();

	void setFace(FACE f);
	void setHorizontalState(HORIZONTAL_STATE hs);
	void setVerticalState(VERTICAL_STATE vs);
	void setVelocityX(float velocity);
	void setVelocityY(float velocity);

	

	const float* getCenter() const;
	const float getSize() const;
	const int getScore() const;
	const int getLife() const;
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
	int score;
	int life;
	bool shield;
	float shield_timer;

	FACE face;
	HORIZONTAL_STATE horizontalState;
	VERTICAL_STATE verticalState;
	Texture texture;
};

