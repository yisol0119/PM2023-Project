#include "Platform.h"
#include <GL/freeglut.h>


Platform::Platform(float x, float y, float z, float w, float h) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
	width = w;
	height = h;
	platformtype = ISPASSABLE;
	boundary[0] = center[1] + height / 2;		//╩С
	boundary[1] = center[1] - height / 2;		//го
	boundary[2] = center[0] - width / 2;		//аб
	boundary[3] = center[0] + width / 2;		//©Л
	
	
	
}



void Platform::draw() const {
	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	//glShadeModel(GL_SMOOTH);
	//glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	//glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.0f, 0.5f);
	glVertex3f(-width / 2, height / 2, 0.0f); // { Front }
	glVertex3f(width / 2, height / 2, 0.0f); // { Front }
	glVertex3f(width / 2, -height / 2, 0.0f); // { Front }
	glVertex3f(-width / 2, -height / 2, 0.0f); // { Front }
	glEnd();
	glPopMatrix();

}
const float* Platform::getCenter() const {

	return center;
}
const float Platform::getWidth() const {

	return width;
}
const float Platform::getHeight() const {


	return height;
}

void Platform::setColliding(bool collide) {
	colliding = collide;

}
const bool Platform::getColliding() const {
	return colliding;

}



Platform::PLATFORM_TYPE Platform::getplatformtype() const {
	return platformtype;
}
void Platform::setplatformtype(PLATFORM_TYPE plattype) {
	platformtype = plattype;
}

//float center[3];
//
//float width, height;
//
//PLATFORM_TYPE platformtype;
//Texture wall_texture;