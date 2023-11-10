#pragma once
#include "Texture.h"

class Platform
{
public:
	enum PLATFORM_TYPE { ISPASSABLE, IMPASSABLE };

	Platform(float x, float y, float z, float w, float h);
	//Platform(const Platform& Plat); //Copy constructor, vector 생성할때 필요

	void draw() const;

	const float* getCenter() const;
	const float getWidth() const;
	const float getHeight() const;
	
	void setColliding(bool collide);
	const bool getColliding() const;
	
	
	PLATFORM_TYPE getplatformtype() const;
	void setplatformtype(PLATFORM_TYPE platformtype);

private:
	float center[3];

	float width, height;

	float boundary[4];
	bool colliding;
	PLATFORM_TYPE platformtype;
	Texture wall_texture;
};

