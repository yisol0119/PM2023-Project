#pragma once
#include "Texture.h"
class Wall
{
	friend class Collision; //Collision class에 private 변수(width, center height)사용 권한 부여

public:
	Wall(float x, float y, float z, float w, float h);
	
	void draw();
	void setTexture(const Texture& texture);
	void inittexture();


private:
	float center[3];

	float width, height;
	
	Texture wall_texture;
	float boundary[2];

};

