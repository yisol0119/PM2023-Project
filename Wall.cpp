#include "Wall.h"

Wall::Wall(float x, float y, float z, float w, float h, bool impassable) {

	center[0] = x;
	center[1] = y;
	center[2] = z;
	this->width = w;
	this->height = h;
	this->impassable = impassable;


}


void Wall::setTexture(const Texture& texture) {


	// ÇÃ·§Æû ÅØ½ºÃÄ ÇÒ´ç

	wall_texture = texture;


}
float Wall::getleftBoundary() const {
	return boundary[0];

}
float Wall::getrightBoundary() const {
	return boundary[1];

}

void Wall::draw() const {
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