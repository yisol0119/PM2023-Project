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
	setHorizontalState(HSTOP);
	setVerticalState(FALL);
	
	score = 0;
	life = 3;

	inittexture();
	printf("player constructure texture\n");
}



void Player::draw() {
	if (shield == TRUE && ((int)shield_timer % 2) == 0) return;    //shield가 활성화 되었을 때 player의 형상이 깜박거리도록 한다. 
	if(face==LEFT)
		texture.drawtexture(size, size, center,0 );
	else
		texture.drawtexture(size, size, center,1);
}

void Player::setFace(FACE f) {
	face = f;
}

void Player::setHorizontalState(HORIZONTAL_STATE hs) {
	horizontalState = hs;

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
}

void Player::setVerticalState(VERTICAL_STATE vs) {
	verticalState = vs;
	switch (verticalState)
	{
	case Player::VSTOP:
		velocity[1] = 0.0f;
		break;
	case Player::JUMP:
		velocity[1]=12.0f;
		break;
	case Player::FALL:
		velocity[1] = -3.0f;
		break;
	default:
		break;
	}
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

const int Player::getScore() const {

	return score;

}
const int Player::getLife() const {


	return life;
}

void Player::move() {

	/*if (bPressSpace && (bubbles.empty()||(bubbles.back()).getBubblestate() != Bubble::BLANK)) {

		bubbles.push_back(player.shootBubble());
		printf("pushback bubble\n");

	}*/
	// Bubble 개수를 제한하는 것으로 수정 


	if (verticalState == JUMP) {
		velocity[1] -= 0.4f;
		if (velocity[1] <= 0) {
			cout << "player fall" << endl;
			setVerticalState(FALL);
		}
	}
	if(shield==TRUE) shield_timer += 0.3f;
	if (shield_timer > 20.0f) {
		shield_timer = 0;
		shield = FALSE;

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


void Player::inittexture() {

	texture.initializeTexture("dragon_facingleft.png");
}

Bubble Player::shootBubble() {
	Bubble newbubble(20.0f);

	newbubble.setCenter(center[0], center[1], center[2]);
	if(face==RIGHT)
		newbubble.setVelocity(5.0f, 0.0f, 0.0f);
	else newbubble.setVelocity(-5.0f, 0.0f, 0.0f);

	return newbubble;
}


//float center[3];
//float size;
//FACE face;
//HORIZONTAL_STATE horizontalState;