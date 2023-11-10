#include <iostream>
#include "Collision.h"

using namespace std;

bool Collision::isCollisionDetected(const Bubble& bub1, const Bubble& bub2) {
	return 0;
}
bool Collision::isCollisionDetected(const Enemy& Enm, const Bubble& bub) {
	return 0;
}
bool Collision::isCollisionDetected(const Player& ply, const Bubble& bub) {
	return 0;
}
bool Collision::isCollisionDetected(const Player& ply, const Enemy& Enm) {
	return 0;
}
bool Collision::isCollisionDetected(const Player& ply, const Wall& wal) {
	
 return false;
}
bool Collision::isCollisionDetected(const Player& ply, const Platform& plat) {
	
	float player_center[2];
	float platform_center[2];
	float player_size;
	float player_height;
	float platform_width;
	float platform_height;
	player_center[0] = ply.getCenter()[0];
	player_center[1] = ply.getCenter()[1];
	player_size = ply.getSize();
	platform_center[0] = plat.getCenter()[0];
	platform_center[1] = plat.getCenter()[1];
	platform_width=plat.getWidth();
	platform_height=plat.getHeight();

	if ((player_center[0] - platform_center[0] >= -(player_size / 2 + platform_width / 2)) && ((player_center[0] - platform_center[0]) <= (player_size / 2 + platform_width / 2))) {
		
		
		if ((player_center[1] - platform_center[1] <= (player_size / 2 + platform_height / 2)) && (player_center[1] - platform_center[1]) >= 0 && (ply.getVerticalState() != Player::JUMP)) {
			  return TRUE;
		}
		else if ((player_center[1] - platform_center[1] >= -(player_size / 2 + platform_height / 2)) && ((player_center[1] - platform_center[1]) <= 0)&& (plat.getplatformtype() == Platform::IMPASSABLE)) {
			 return TRUE;
		}
		
		
	}
	

	 return FALSE;
}
bool Collision::isCollisionDetected(const Enemy& enm, const Wall& wal) {
	return 0;
}
bool Collision::isCollisionDetected(const Enemy& enm, const Platform& plat) {
	return 0;
}

void Collision::handleCollision(Bubble& bub1, Bubble& bub2) {

}
void Collision::handleCollision(Enemy& Enm, Bubble& bub) {

}
void Collision::handleCollision(Player& ply, Bubble& bub) {

}
void Collision::handleCollision(Player& ply, Enemy& Enm) {

}
void Collision::handleCollision(Player& ply, const Wall& wal) {
	
	if (isCollisionDetected(ply, wal) && (ply.getVerticalState() == Player::VSTOP)) {	//수평으로만 움직이다가 벽과 부딪힘
		ply.setHorizontalState(Player::HSTOP);
	}
	else if (isCollisionDetected(ply, wal)) {	//점프나 떨어지는 상태에서 벽과 부딪힘
		ply.setHorizontalState(Player::HSTOP);
		ply.setVerticalState(Player::FALL);
	}
}
void Collision::handleCollision(Player& ply, Platform& plat) {

	
	

	bool iscolliding = isCollisionDetected(ply, plat);
	

	if ((iscolliding == FALSE)&& ((ply.getHorizontalState() == Player::MOVE)&& (ply.getVerticalState() == Player::VSTOP))&&(plat.getColliding()== TRUE)) {//문제: 이전의 충돌정보를 알아야 플랫폼에서 벗어난것을 알 수 있는데 auto로 카피한 플랫폼이기 떄문에 colliding 변수가 수정되지 않음.
		ply.setVerticalState(Player::FALL);
		
		
	}
	else if ((iscolliding==TRUE) && (ply.getVerticalState() == Player::FALL)) {
		ply.setVerticalState(Player::VSTOP);
		
	}
	else if ((iscolliding==TRUE) && (ply.getVerticalState() == Player::JUMP) && plat.getplatformtype() == Platform::IMPASSABLE) {
		ply.setVerticalState(Player::FALL);
	
	}

	plat.setColliding(iscolliding);
	
}
void Collision::handleCollision(Enemy& enm, const Wall& wal) {

}
void Collision::handleCollision(Enemy& enm, const Platform& plat) {

}