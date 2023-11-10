#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(float x, float y, float z, float s) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
	size = s;

	velocity[0] = 0.0f;
	velocity[1] = 0.0f;

	face = FACE::RIGHT;
	horizontalState = HORIZONTAL_STATE::HSTOP;
	verticalState = VERTICAL_STATE::VSTOP;

	boundary[0] = center[1] + size / 2;		//╩С
	boundary[1] = center[1] - size / 2;		//го
	boundary[2] = center[0] - size / 2;		//аб
	boundary[3] = center[0] + size / 2;		//©Л
}

void Player::draw() const {
	glPointSize(size);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(center[0], center[1]);
	glEnd();
}

void Player::setFace(FACE f) {
	face = f;
}

void Player::setHorizontalState(HORIZONTAL_STATE hs) {
	horizontalState = hs;
}

void Player::setVerticalState(VERTICAL_STATE vs) {
	verticalState = vs;
}

Player::VERTICAL_STATE Player::getVerticalState() const {
	return verticalState;
}
Player::HORIZONTAL_STATE Player::getHorizontalState() const {

	return horizontalState;
}



Player::FACE Player::getFace() const {


	return face;
}
const float* Player::getCenter() const {
	return center;


}
const float Player::getSize() const {
	return size;

}

void Player::move() {
	
	switch (horizontalState)
	{
	case Player::HSTOP:
		velocity[0] = 0.0f;
		break;
	case Player::MOVE:
		switch (face)
		{
		case Player::LEFT:
			velocity[0] = -5.0f;
			break;
		case Player::RIGHT:
			velocity[0] = 5.0f;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	switch (verticalState)
	{
	case Player::VSTOP:
		velocity[1] = 0.0f;
		break;
	case Player::JUMP:
		velocity[1] -= 2.0f;
		if (velocity[1] <= 0) {
			cout << "player fall" << endl;
			verticalState = FALL;
		}
		break;
	case Player::FALL:
		velocity[1] = -5.0f;
		break;
	default:
		break;
	}

	center[0] += velocity[0];
	center[1] += velocity[1];

	
}



void Player::setVelocityX(float vel) {
	velocity[0] = vel;


}
void Player::setVelocityY(float vel) {
	velocity[1] = vel;
}

//float center[3];
//float size;
//FACE face;
//HORIZONTAL_STATE horizontalState;