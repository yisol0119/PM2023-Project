#pragma once
#include "Texture.h"
class Wall
{
	friend class Collision; //Collision class¿¡ private º¯¼ö(width, center height)»ç¿ë ±ÇÇÑ ºÎ¿©

public:
	Wall(float x, float y, float z, float w, float h);
	
	void draw() const;
	void setTexture(const Texture& texture);
	


private:
	float center[3];

	float width, height;
	
	Texture wall_texture;
	float boundary[2];

};

