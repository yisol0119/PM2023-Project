#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include "FreeImage.h"

class Texture {
public:
	Texture() = default;
	Texture(const Texture& texture) = default;
	FIBITMAP* createBitMap(char const* filename);
	void generateTexture();
	void initializeTexture(char const* filename);
	
	void drawtexture(float width, float height, float* center, bool reverse);  //player 그리기 용도
	void drawtexture(float width, float height, float* center);  //벽 및 플랫폼 그리기 용도
private:
	GLuint getTextureID() const;
	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;

};