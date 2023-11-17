#include <iostream>
#include "Bubble.h"
#include <GL/freeglut.h>
using namespace std;

Bubble::Bubble(float r) {
	setRadius(r);
	bubble_timer = 0;
	bubbleState = BLANK;
	texture_blank.initializeTexture("bubble_blank.png");
	texture_float.initializeTexture("bubble_solidgreen.png");
	texture_capture.initializeTexture("enemy_capture.png");
}

Bubble::Bubble(const Bubble& Bubble) = default;

void Bubble::setRadius(float r) {

	radius = r;

}
float Bubble::getRadius() const {

	return radius;

}
//void Bubble::setSlice(int sl) {
//	slice = sl;
//
//}
//float Bubble::getSlice() const {
//
//	return slice;
//}
//
//
//
//void Bubble::setStack(int st) {
//
//	stack = st;
//}
//float Bubble::getStack() const {
//
//	return stack;
//
//}


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

//void Bubble::setMTL(const Material& m) {
//	mtl = m;
//
//}
//Material Bubble::getMTL() const {
//	return mtl;
//
//}


void Bubble::increaseBubbletimer() {
	bubble_timer += 0.1f;
}
void Bubble::increaseCapturetimer() {
	capture_timer += 0.1f;
}

Bubble::BUBBLE_STATE Bubble::getBubblestate() {
	return bubbleState;
}

void Bubble::move() {
	for (int i = 0; i < 3; i++) {
		center[i] = center[i] + velocity[i];

	}

}
void Bubble::draw() {

	if (bubbleState == BLANK) {
	
		radius = bubble_timer*5+10;
		if (bubble_timer >= 7.0f) {
			bubbleState = FLOAT;
		}
		texture_blank.drawtexture(radius, radius, center, 0);
	}
	else if (bubbleState == FLOAT) {
		
		velocity[0] = 0.0f;
		velocity[1] = 1.0f;
		texture_float .drawtexture(radius, radius, center,0);
	}
	else if (bubbleState == CAPTURE) {
		
		velocity[0] = 0.0f;
		velocity[1] = 0.8f;
		texture_capture.drawtexture(50, 50, center,0);
	}
	
	
	
	
	
}