#pragma once
#include "Texture.h"
#include "Collision.h"


class Platform
{
	friend class Collision; //Collision class�� private ����(width, center height)��� ���� �ο�
public:
	enum PLATFORM_TYPE { ISPASSABLE, IMPASSABLE };

	Platform(float x, float y, float z, float w, float h, PLATFORM_TYPE platformtype);
	//Platform(const Platform& Plat); //Copy constructor, vector �����Ҷ� �ʿ�

	void draw();

	const float* getCenter() const;
	const float getWidth() const;
	const float getHeight() const;
	
	void setColliding(Collision::COLLISION_TYPE collide);
	const Collision::COLLISION_TYPE getColliding() const;
	
	
	PLATFORM_TYPE getplatformtype() const;
	void setplatformtype(PLATFORM_TYPE platformtype);
	void inittexture();
private:
	float center[3];
	float width, height;
	Collision::COLLISION_TYPE colliding;
	PLATFORM_TYPE platformtype;
	Texture platform_texture;
};

