#pragma once


#include "Texture.h"

class Bubble
{
	friend class Collision;
	friend class Stage;
public:
	enum BUBBLE_STATE { BLANK, CAPTURE, FLOAT };
	Bubble(float r);
	Bubble(const Bubble& Bubble);

	void setRadius(float r);
	float getRadius() const;
	//void setSlice(int sl);
	//float getSlice() const;
	//void setStack(int st);
	//float getStack() const;

	void setCenter(float x, float y, float z);
	float getCenterX() const;
	float getCenterY() const;
	float getCenterZ() const;

	void setVelocity(float x, float y, float z);
	float getVelocityX() const;
	float getVelocityY() const;
	float getVelocityZ() const;

	void move();
	/*void setMTL(const Material& m);
	Material getMTL() const;*/

	BUBBLE_STATE getBubblestate();
	void increaseBubbletimer();
	void increaseCapturetimer();
	void draw();

	~Bubble() = default;

	

private:
	float radius;
	int slice;
	int stack;

	float center[3];
	float velocity[3];
	float bubble_timer, capture_timer;

	
	Texture texture_blank, texture_float, texture_capture;
	BUBBLE_STATE bubbleState;
};

