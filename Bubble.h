#pragma once


#include "Material.h"

class Bubble
{
public:

	Bubble(float r, int sl, int st);
	Bubble(const Bubble& Bubble);

	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	float getSlice() const;
	void setStack(int st);
	float getStack() const;

	void setCenter(float x, float y, float z);
	float getCenterX() const;
	float getCenterY() const;
	float getCenterZ() const;

	void setVelocity(float x, float y, float z);
	float getVelocityX() const;
	float getVelocityY() const;
	float getVelocityZ() const;

	void move();
	void setMTL(const Material& m);
	Material getMTL() const;

	void draw() const;

private:
	float radius;
	int slice;
	int stack;

	float center[3];
	float velocity[3];
	Material mtl;
};

