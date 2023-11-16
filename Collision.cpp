#include <iostream>
#include "Collision.h"
#include "Stage.h"


using namespace std;


void Collision::collide(Stage& stage) {
	static bool player_bubble;
	static bool enemy_bubble;
	//player-bubble 
	for (auto itr = stage.bubbles.begin(); itr != stage.bubbles.end();) {
		player_bubble = handleCollision(stage.player, *itr); 
		if (player_bubble == TRUE) {
			if ((*itr).bubbleState == Bubble::CAPTURE) {
				stage.capturebubble_count--;
				// 버블을 터뜨려 남아있는  Enemy가 없을 경우 재생성
				if (stage.enemies.size() == 0 && stage.capturebubble_count == 0) {
					Enemy enemy1(-boundaryX + PLAYER_SIZE * 1.5f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
					Enemy enemy2(PLAYER_SIZE * 1.5f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
					Enemy enemy3(boundaryX - PLAYER_SIZE * 1.5f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
					stage.setEnemy(enemy1);
					stage.setEnemy(enemy2);
					stage.setEnemy(enemy3);

				}
			}
			itr = stage.bubbles.erase(itr);
		}
		else {
			itr++;
		}
	}
	//
	for (int i = 0; i < stage.getEnemysize(); i++) {

		handleCollision(stage.player, stage.enemies[i]);

	}
	//
	for (int i = 0; i < stage.getPlatformsize(); i++)
		handleCollision(stage.player, stage.stageplatform[i]);
	//
	for (int i = 0; i < stage.getWallsize(); i++)
		handleCollision(stage.player, stage.stagewall[i]);
	//
	for (int i = 0; i < stage.getBubblesize(); i++) {
		for (auto itr = stage.enemies.begin(); itr != stage.enemies.end();) {
			enemy_bubble= handleCollision(*itr, stage.bubbles[i]); //오류 생길수 있음 
			if (enemy_bubble == TRUE) {
				stage.capturebubble_count++;
				itr= stage.enemies.erase(itr);

			}
			else {
				itr++;
			}
		}
	}
	//
	for (int i = 0; i < stage.getEnemysize(); i++) {
		for (int j = 0; j < stage.getWallsize(); j++) {
			handleCollision(stage.enemies[i], stage.stagewall[j]); 
		}
	}
	//
	for (int i = 0; i < stage.getEnemysize(); i++) {
		for (int j = 0; j < stage.getPlatformsize(); j++) {
			handleCollision(stage.enemies[i], stage.stageplatform[j]);
		}
	}

}

bool Collision::isCollisionDetected(const Bubble& bub1, const Bubble& bub2) {
	return 0;
}
bool Collision::isCollisionDetected(const Enemy& enm, const Bubble& bub) {
	static float enemy_center[2];
	static float bubble_center[2];
	static float enemy_size;
	static float bubble_radius;
	static Bubble::BUBBLE_STATE bubble_state;
	static float dcenter[2];
	static float size;
	enemy_center[0] = enm.center[0];
	enemy_center[1] = enm.center[1];
	bubble_center[0] = bub.center[0];
	bubble_center[1] = bub.center[1];
	enemy_size = enm.size;
	bubble_radius = bub.radius;
	bubble_state = bub.bubbleState;
	dcenter[0] = bubble_center[0] - enemy_center[0];
	dcenter[1] = bubble_center[1] - enemy_center[1];
	size = (bubble_radius + enemy_size) / 2;

	if ((bubble_state == Bubble::BLANK) || (bubble_state == Bubble::FLOAT)) {
		if ((dcenter[0]< size && dcenter[0] > -size && dcenter[1] < size && dcenter[1] > -size)) {

			
			return TRUE;

		}

	}
	

	return 0;
}
bool Collision::isCollisionDetected(const Player& ply, const Bubble& bub) {

	static float player_center[2];
	static float bubble_center[2];
	static float player_size;
	static float bubble_radius;
	static Bubble::BUBBLE_STATE bubble_state;
	static float dcenter[2];
	static float size;
	player_center[0] = ply.center[0];
	player_center[1] = ply.center[1];
	bubble_center[0] = bub.center[0];
	bubble_center[1] = bub.center[1];
	player_size = ply.size;
	bubble_radius = bub.radius;
	bubble_state = bub.bubbleState;
	dcenter[0] = bubble_center[0] - player_center[0];
	dcenter[1] = bubble_center[1] - player_center[1];
	size = (bubble_radius + player_size) / 2;

	if ((bubble_state != Bubble::BLANK)) {
		if ((dcenter[0]< size && dcenter[0] > -size && dcenter[1] < size && dcenter[1] > -size)) return TRUE;

	}

	return 0;
}
bool Collision::isCollisionDetected(const Player& ply, const Enemy& enm) {
	static float player_center[2];
	static float enemy_center[2];
	static float player_size;
	static float enemy_size;
	static float dcenter[2];
	static float size;
	player_center[0] = ply.center[0];
	player_center[1] = ply.center[1];
	enemy_center[0] = enm.center[0];
	enemy_center[1] = enm.center[1];
	player_size = ply.size;
	enemy_size = enm.size;
	dcenter[0] = enemy_center[0] - player_center[0];
	dcenter[1] = enemy_center[1] - player_center[1];
	size = (enemy_size + player_size) / 2;

	if ((dcenter[0]< size && dcenter[0] > -size && dcenter[1] < size && dcenter[1] > -size)) return TRUE;



	else return FALSE;
}
Collision::COLLISION_TYPE Collision::isCollisionDetected(const Player& ply, const Wall& wal) {
	static float player_center;
	static float player_newcenter; //velocity로 이동 시 예측 위치
	static float wall_center;
	static float player_size;
	static float wall_width;

	player_center = ply.center[0];
	player_newcenter = player_center + ply.velocity[0];
	player_size = ply.size;
	wall_center = wal.center[0];
	
	wall_width = wal.width;


	if ((player_newcenter - wall_center > -(player_size / 2 + wall_width / 2)) && (player_center - wall_center <= -(player_size / 2 + wall_width / 2))) {
				cout << "LEFT" << endl;
				return LEFT;
	}

	else if ((player_newcenter - wall_center < (player_size / 2 + wall_width / 2)) && (player_center - wall_center >= (player_size / 2 + wall_width / 2))) {
				cout << "RIGHT" << endl;
				return RIGHT;
	}


	
 return NONE;
}
Collision::COLLISION_TYPE Collision::isCollisionDetected(const Player& ply, const Platform& plat) {
	
	static float player_center[2];
	static float player_newcenter[2]; //velocity로 이동 시 예측 위치
	static float platform_center[2];
	static float player_size;
	static float platform_width;
	static float platform_height;

	player_center[0] = ply.center[0];
	player_center[1] = ply.center[1];
	player_newcenter[0] = player_center[0] + ply.velocity[0];
	player_newcenter[1] = player_center[1] + ply.velocity[1];
	player_size = ply.size;
	platform_center[0] = plat.center[0];
	platform_center[1] = plat.center[1];
	platform_width=plat.width;
	platform_height=plat.height;

	
	if ((player_newcenter[0] - platform_center[0] >= -(player_size / 2 + platform_width / 2)) && ((player_newcenter[0] - platform_center[0]) <= (player_size / 2 + platform_width / 2))) {

		if ((player_newcenter[1] - platform_center[1] < (player_size / 2 + platform_height / 2)) && (player_center[1] - platform_center[1] >= (player_size / 2 + platform_height / 2))) {
			cout << "TOP" << endl;
			return TOP;

		}

		else if ((player_newcenter[1] - platform_center[1] > -(player_size / 2 + platform_height / 2)) && (player_center[1] - platform_center[1] <= -(player_size / 2 + platform_height / 2))) {
			cout << "BOTTOM" << endl;
			return BOTTOM;
		}

		else if ((player_center[1] - platform_center[1] - player_size / 4 < (player_size / 2 + platform_height / 2)) && (player_center[1] - platform_center[1] >= (player_size / 2 + platform_height / 2))) {

			//cout << "ONPLAT" << endl;
			return ONPLAT;

		}
		
		else if ((player_newcenter[1] - platform_center[1] >= -(player_size / 2 + platform_height / 2)) && ((player_newcenter[1] - platform_center[1]) <= (player_size / 2 + platform_height / 2))) {
			
			
			if ((player_newcenter[0] - platform_center[0] > -(player_size / 2 + platform_width / 2)) && (player_center[0] - platform_center[0] <= -(player_size / 2 + platform_width / 2))) {
				cout << "LEFT" << endl;
				return LEFT;
			}

			else if ((player_newcenter[0] - platform_center[0] < (player_size / 2 + platform_width / 2)) && (player_center[0] - platform_center[0] >= (player_size / 2 + platform_width / 2))) {
				cout << "RIGHT" << endl;
				return RIGHT;
			}

		}
	}
	
		
		
	


	return NONE;
}
Collision::COLLISION_TYPE Collision::isCollisionDetected(const Enemy& enm, const Wall& wal) {
	return NONE;
}
Collision::COLLISION_TYPE Collision::isCollisionDetected(const Enemy& enm, const Platform& plat) {
	static float enemy_center[2];
	static float enemy_newcenter[2]; //velocity로 이동 시 예측 위치
	static float platform_center[2];
	static float enemy_size;
	static float platform_width;
	static float platform_height;

	enemy_center[0] = enm.center[0];
	enemy_center[1] = enm.center[1];
	enemy_newcenter[0] = enemy_center[0] + enm.velocity[0];
	enemy_newcenter[1] = enemy_center[1] + enm.velocity[1];
	enemy_size = enm.size;
	platform_center[0] = plat.center[0];
	platform_center[1] = plat.center[1];
	platform_width = plat.width;
	platform_height = plat.height;

	if ((enemy_newcenter[0] - platform_center[0] >= -(enemy_size / 2 + platform_width / 2)) && ((enemy_newcenter[0] - platform_center[0]) <= (enemy_size / 2 + platform_width / 2))) {

		if ((enemy_newcenter[1] - platform_center[1] < (enemy_size / 2 + platform_height / 2)) && (enemy_center[1] - platform_center[1] >= (enemy_size / 2 + platform_height / 2))) {
			cout << "TOP" << endl;
			return TOP;

		}


		else if ((enemy_center[1] - platform_center[1] - enemy_size / 4 < (enemy_size / 2 + platform_height / 2)) && (enemy_center[1] - platform_center[1] >= (enemy_size / 2 + platform_height / 2))) {


			//enemy의 left right는 플랫폼의 왼쪽, 오른쪽에 충돌하는 것이 아닌 플랫폼의 양 끝에 다다랐을때를 나타낸다. 
		if ((enemy_newcenter[0] - platform_center[0] < -(-enemy_size / 2 + platform_width / 2)) && (enemy_center[0] - platform_center[0] >= -(-enemy_size / 2 + platform_width / 2))) {
			cout << "LEFT" << endl;
			return LEFT;
		}

		else if ((enemy_newcenter[0] - platform_center[0] > (-enemy_size / 2 + platform_width / 2)) && (enemy_center[0] - platform_center[0] <= (-enemy_size / 2 + platform_width / 2))) {
			cout << "RIGHT" << endl;
			return RIGHT;
		}
			//cout << "ONPLAT" << endl;
			return ONPLAT;

		}


	}






	return NONE;
}

void Collision::handleCollision(Bubble& bub1, Bubble& bub2) {

}
 bool Collision::handleCollision(Enemy& enm, Bubble& bub) {
	bool isColliding = isCollisionDetected(enm, bub);
	if (isColliding == TRUE) {
		bub.bubbleState = Bubble::CAPTURE;
		bub.capture_timer = 0;
		
		return TRUE;
	}
	return FALSE;
}
bool Collision::handleCollision(Player& ply, Bubble& bub) {
	bool isColliding = isCollisionDetected(ply, bub);
	if (isColliding == TRUE&& bub.bubbleState == Bubble::CAPTURE) {
		ply.score += 200;

		return TRUE;
	}
	else if (isColliding == TRUE && bub.bubbleState == Bubble::FLOAT) {
		


		return TRUE;
	}
	return FALSE;
}
void Collision::handleCollision(Player& ply, Enemy& enm) {

	bool isColliding = isCollisionDetected(ply, enm);

	if (isColliding == TRUE&&ply.shield==FALSE ) {
		ply.life--;
		ply.shield = TRUE;
		ply.shield_timer = 0;
	}

}
void Collision::handleCollision(Player& ply, const Wall& wal) {
	COLLISION_TYPE iscolliding = isCollisionDetected(ply, wal);

	if (((iscolliding == LEFT) || (iscolliding == RIGHT))) {

	ply.setHorizontalState(Player::HSTOP);
	cout << "wall" << endl;
	}

}
void Collision::handleCollision(Player& ply, Platform& plat) {

	
	

	COLLISION_TYPE iscolliding = isCollisionDetected(ply, plat);
	

	if ((iscolliding == NONE)&& ((ply.getHorizontalState() == Player::MOVE)&& (ply.getVerticalState() == Player::VSTOP))&&(plat.getColliding()== ONPLAT)) {//문제: 이전의 충돌정보를 알아야 플랫폼에서 벗어난것을 알 수 있는데 auto로 카피한 플랫폼이기 떄문에 colliding 변수가 수정되지 않음.
		//충돌 안하고있고 좌우로 움직이고 점프나 폴 아닐때(좌우로만 움직일 때)
		ply.setVerticalState(Player::FALL);
		//cout << "CASE1" << endl;
		
		
	}
	else if ((iscolliding==TOP) && (ply.getVerticalState() == Player::FALL)) {
		ply.setVerticalState(Player::VSTOP);
		ply.center[1] = plat.center[1] + plat.height / 2 + ply.size / 2;
		//cout << "CASE2" << endl;
	}

	
	else if (((iscolliding == LEFT) || (iscolliding == RIGHT)) && plat.getplatformtype() == Platform::IMPASSABLE) {
		
		ply.setHorizontalState(Player::HSTOP);
		//cout << "CASE3" << endl;
	}
	else if (((iscolliding == BOTTOM)) && plat.getplatformtype() == Platform::IMPASSABLE) {
		ply.setVerticalState(Player::FALL);
		ply.setHorizontalState(Player::HSTOP);
		//cout << "CASE3" << endl;
	}
	plat.setColliding(iscolliding);  
	
}
void Collision::handleCollision(Enemy& enm, const Wall& wal) {

}
void Collision::handleCollision(Enemy& enm, Platform& plat) {

	COLLISION_TYPE iscolliding = isCollisionDetected(enm, plat);


	//if ((iscolliding == NONE) && ((enm.getHorizontalState() == Enemy::MOVE) && (enm.getVerticalState() == Enemy::VSTOP)) && (plat.getColliding() == ONPLAT)) {//문제: 이전의 충돌정보를 알아야 플랫폼에서 벗어난것을 알 수 있는데 auto로 카피한 플랫폼이기 떄문에 colliding 변수가 수정되지 않음.
	//	//충돌 안하고있고 좌우로 움직이고 점프나 폴 아닐때(좌우로만 움직일 때)
	//	enm.velocity[0] = -enm.velocity[0];
	//	cout << "CASE1" << endl;


	//}
	if ((iscolliding == TOP) && (enm.getVerticalState() == Enemy::FALL)) {
		enm.setVerticalState(Enemy::VSTOP);
		enm.center[1] = plat.center[1] + plat.height / 2 + enm.size / 2;
		enm.velocity[0] = 3.0f;
		cout << "CASE2" << endl;
	}
	else if (((iscolliding == LEFT) || (iscolliding == RIGHT))) {

		enm.velocity[0] = -enm.velocity[0];
		if (enm.face == Enemy::RIGHT) enm.face = Enemy::LEFT;
		else enm.face = Enemy::RIGHT;
		cout << "CASE3" << endl;
	}
	


}