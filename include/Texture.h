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
	void drawtexture(int width, int height, float* center, bool reverse);
	void drawtexture(int width, int height, float* center);
private:
	GLuint getTextureID() const;
	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;

};
