#pragma once
#include "Texture.h"
class Wall
{
public:
	Wall(float x, float y, float z, float w, float h, bool impassable);
	
	void draw() const;
	void setTexture(const Texture& texture);
	
	float getleftBoundary() const;
	float getrightBoundary() const;

private:
	float center[3];

	float width, height;
	
	Texture wall_texture;
	bool impassable;
	float boundary[2];

};

