#include <iostream>
#include "Enemy.h"


using namespace std;

Enemy::Enemy(float x, float y, float z, float s) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
	size = s;

	velocity[0] = 0.0f;
	velocity[1] = -3.0f;

	face = FACE::RIGHT;

	setHorizontalState(HSTOP);
	setVerticalState(FALL);
	inittexture();
	printf("Enemy constructure texture\n");
}



void Enemy::draw() {
	if (face == LEFT)
		texture.drawtexture(size, size, center,1);
	else
		texture.drawtexture(size, size, center ,0);
}

void Enemy::setFace(FACE f) {
	face = f;
}

void Enemy::setHorizontalState(HORIZONTAL_STATE hs) {
	horizontalState = hs;

	switch (horizontalState)
	{
	case Enemy::HSTOP:
		velocity[0] = 0.0f;
		break;
	case Enemy::MOVE:
		switch (face)
		{
		case Enemy::LEFT:
			velocity[0] = -5.0f;
			break;
		case Enemy::RIGHT:
			velocity[0] = 5.0f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Enemy::setVerticalState(VERTICAL_STATE vs) {
	verticalState = vs;
	switch (verticalState)
	{
	case Enemy::VSTOP:
		velocity[1] = 0.0f;
		break;
	case Enemy::JUMP:
		velocity[1] = 10.0f;
		break;
	case Enemy::FALL:
		velocity[1] = -3.0f;
		break;
	default:
		break;
	}
}

Enemy::VERTICAL_STATE Enemy::getVerticalState() const {
	return verticalState;
}
Enemy::HORIZONTAL_STATE Enemy::getHorizontalState() const {

	return horizontalState;
}



Enemy::FACE Enemy::getFace() const {


	return face;
}
const float* Enemy::getCenter() const {
	return center;


}
const float Enemy::getSize() const {
	return size;

}

void Enemy::move() {


	if (verticalState == JUMP) {
		velocity[1] -= 0.4f;
		if (velocity[1] <= 0) {
			cout << "Enemy fall" << endl;
			setVerticalState(FALL);
		}
	}



	center[0] += velocity[0];
	center[1] += velocity[1];


}



void Enemy::setVelocityX(float vel) {
	velocity[0] = vel;


}
void Enemy::setVelocityY(float vel) {
	velocity[1] = vel;
}


void Enemy::inittexture() {

	texture.initializeTexture("enemy_facingright.png");
}

Bubble Enemy::shootBubble() {
	Bubble newbubble(20.0f);

	newbubble.setCenter(center[0], center[1], center[2]);
	if (face == RIGHT)
		newbubble.setVelocity(5.0f, 0.0f, 0.0f);
	else newbubble.setVelocity(-5.0f, 0.0f, 0.0f);

	return newbubble;
}


//float center[3];
//float size;
//FACE face;
//HORIZONTAL_STATE horizontalState;