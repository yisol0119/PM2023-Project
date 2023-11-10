#include <iostream>
#include "Bubble.h"
#include <GL/freeglut.h>
using namespace std;

Bubble::Bubble(float r, int sl, int st) {
	setRadius(r);
	setSlice(sl);
	setStack(st);


}

Bubble::Bubble(const Bubble& Bubble) {
	setRadius(Bubble.getRadius());
	setSlice(Bubble.getSlice());
	setStack(Bubble.getStack());
	setCenter(Bubble.getCenterX(), Bubble.getCenterY(), Bubble.getCenterZ());
	setVelocity(Bubble.getVelocityX(), Bubble.getVelocityY(), Bubble.getVelocityZ());
	setMTL(Bubble.getMTL());

}

void Bubble::setRadius(float r) {

	radius = r;

}
float Bubble::getRadius() const {

	return radius;

}
void Bubble::setSlice(int sl) {
	slice = sl;

}
float Bubble::getSlice() const {

	return slice;
}



void Bubble::setStack(int st) {

	stack = st;
}
float Bubble::getStack() const {

	return stack;

}


void Bubble::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;

}

float Bubble::getCenterX() const {
	return center[0];

}
float Bubble::getCenterY() const {
	return center[1];

}
float Bubble::getCenterZ() const {
	return center[2];

}

void Bubble::setVelocity(float x, float y, float z) {
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;


}
float Bubble::getVelocityX() const {
	return velocity[0];

}
float Bubble::getVelocityY() const {
	return velocity[1];

}
float Bubble::getVelocityZ() const {
	return velocity[2];

}

void Bubble::setMTL(const Material& m) {
	mtl = m;

}
Material Bubble::getMTL() const {
	return mtl;

}
void Bubble::move() {
	for (int i = 0; i < 3; i++) {
		center[i] = center[i] + velocity[i];

	}

}
void Bubble::draw() const {
	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());
	glutSolidSphere(radius, slice, stack);
	glPopMatrix();
}