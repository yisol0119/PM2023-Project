#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include "Light.h"


//mat func



//Light func


Light::Light(float x, float y, float z, int LID) {
	lightID = LID;
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	setAmbient(1, 1,  1, 1);
	setDiffuse(1, 1, 1, 1);
	setSpecular(1, 1, 1, 1);
	//draw();
}




void Light::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;


}

void Light::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;


}

void Light::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;


}

//void Light::enableLight(bool bOn) {
//	bLightOn = bOn;
//
//	
//}

//bool Light::isLightOn() const {
//
//	return bLightOn;
//
//}

void Light::draw() const {
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glEnable(lightID); //lightid가 int가 되는지  확인해야함

	glLightfv(lightID, GL_AMBIENT, ambient);
	glLightfv(lightID, GL_DIFFUSE, diffuse);
	glLightfv(lightID, GL_SPECULAR, specular);
	glLightfv(lightID, GL_POSITION, pos);
	glPopMatrix();
	

}