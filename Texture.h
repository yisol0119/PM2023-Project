#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include "FreeImage.h"

class Texture {
public:
	Texture();
	FIBITMAP* createBitMap(char const* filename);
	void generateTexture();
	void initializeTexture(char const* filename);
private:
	GLuint getTextureID() const;
	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;

};