#include "Texture.h"
#include "Constants.h"
using namespace std;


	
FIBITMAP* Texture::createBitMap(char const* filename) {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	if (format == -1) { // couldn't find image
		//cout << "Can't find" << endl;
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) { // couldn't determine file format
	// attemp to get from file extension
		//cout << "Can't find2" << endl;
		format = FreeImage_GetFIFFromFilename(filename);
		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}
	//cout << "Can find3" << endl;
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	//cout << "Source image has " << bitsPerPixel << " bits per pixel." << endl;
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		//cout << "Skipping conversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		cout << "Converting to 32-bits." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}
	return bitmap32;
}

void Texture::generateTexture() {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}

void Texture::initializeTexture(char const* filename) {
	FIBITMAP* bitmap32 = createBitMap(filename);
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);
	generateTexture();
}

GLuint Texture::getTextureID() const {

	return textureID;

}


void Texture::drawtexture(float width, float height, float* center, bool reverse) {
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	if (reverse == 0) {
		glTexCoord2f(0.0f, 0.0f); glVertex2f(center[0] - width / 2, center[1] - height / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(center[0] - width / 2, center[1] + height / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(center[0] + width / 2, center[1] + height / 2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(center[0] + width / 2, center[1] - height / 2);
	}
	else {
		glTexCoord2f(1.0f, 0.0f); glVertex2f(center[0] - width / 2, center[1] - height / 2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(center[0] - width / 2, center[1] + height / 2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(center[0] + width / 2, center[1] + height / 2);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(center[0] + width / 2, center[1] - height / 2);

	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void Texture::drawtexture(float width, float height, float* center) {
	static float texcoord;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	

	glTexCoord2f(0.0f, 0.0f); glVertex2f(center[0] - width / 2, center[1] - height / 2);
	glTexCoord2f(0.0f, height/PLAYER_SIZE); glVertex2f(center[0] - width / 2, center[1] + height / 2);
	glTexCoord2f(width / PLAYER_SIZE, height / PLAYER_SIZE); glVertex2f(center[0] + width / 2, center[1] + height / 2);
	glTexCoord2f(width / PLAYER_SIZE, 0); glVertex2f(center[0] + width / 2, center[1] - height / 2);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}