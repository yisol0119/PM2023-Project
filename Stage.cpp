#include "Stage.h"
#include <string>

void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

Stage::Stage(STAGELEVEL stage_level) {
	stagelevel = stage_level;
	capturebubble_count = 0;

}

void Stage::setPlayer(const Player& ply) {


	player = ply;

}

void Stage::setWall(const Wall& wal) {
	stagewall.push_back(wal);
}
int Stage::getWallsize() const{

	return stagewall.size();
}

void Stage::setPlatform(const Platform& plat) {
	stageplatform.push_back(plat);
}
int Stage::getPlatformsize() const {

	return stageplatform.size();
}
void Stage::setBubble() {
	bubbles.push_back(player.shootBubble());
}
int Stage::getBubblesize() const{
	return bubbles.size();
}
void Stage::setEnemy(const Enemy& enemy) {
	enemies.push_back(enemy);
}
int Stage::getEnemysize() const {
	return enemies.size();
}

void Stage::setplayermove(bool bPressLeft, bool bPressRight, bool bPressUp, bool bPressSpace) {
	if (bPressLeft == false && bPressRight == false) {
		player.setHorizontalState(Player::HSTOP);
	}
	else if (bPressLeft) {
		player.setFace(Player::LEFT);
		player.setHorizontalState(Player::MOVE);
	}
	else if (bPressRight) {
		player.setFace(Player::RIGHT);
		player.setHorizontalState(Player::MOVE);
	}

	if (bPressUp)
		if (player.getVerticalState() == Player::VSTOP) {

			player.setVerticalState(Player::JUMP);
		}

}

void Stage::move() {
	if (stagelevel == END) {


	}
	else if (stagelevel == START) {


	}
	else if (stagelevel == RESTART) {



	}
	else {

		

		for (auto itr = bubbles.begin(); itr != bubbles.end();) {

			if ((*itr).getBubblestate() == Bubble::CAPTURE) (*itr).increaseCapturetimer();

			if ((*itr).capture_timer >= 50.0f) {
				Enemy enemy((*itr).center[0], (*itr).center[1], 0.0f, PLAYER_SIZE);
				enemies.push_back(enemy);
				itr = bubbles.erase(itr);

			}
			else {
				(*itr).increaseBubbletimer();
				(*itr).move();
				itr++;
			}

		}


		for (int i = 0; i < enemies.size(); i++) {

			enemies[i].move();

		}

		player.move();
	}

}


void Stage::draw() {
	if (stagelevel == END) {

		
	}
	else if (stagelevel == START) {


	}
	else if (stagelevel == RESTART) {
		glColor3f(0.0f, 1.0f, 0.0f);
		displayCharacters(GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER", -30.0f, 0);
		


	}
	else {
		for (auto wal : stagewall) wal.draw();
		for (auto plat : stageplatform) plat.draw();
		for (auto itr = bubbles.begin(); itr != bubbles.end();) {
			if ((*itr).getCenterX() < -boundaryX || (*itr).getCenterX() > boundaryX || (*itr).getCenterY() > boundaryY) {	//bubble이 boundary 벗어나면 삭제

				if ((*itr).bubbleState == Bubble::CAPTURE) {
					capturebubble_count--;
					// Bubble이 맵밖으로 나간경우 Enemy 재생성
					if (enemies.size() == 0&& capturebubble_count==0) {
						Enemy enemy1(-boundaryX + PLAYER_SIZE * 1.5f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
						Enemy enemy2(PLAYER_SIZE * 1.5f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
						Enemy enemy3(boundaryX - PLAYER_SIZE * 1.5f, PLAYER_SIZE * 1.5f, 0.0f, PLAYER_SIZE);
						setEnemy(enemy1);
						setEnemy(enemy2);
						setEnemy(enemy3);

					}
				}

				itr = bubbles.erase(itr);

			}
			else {

				(*itr).draw();		//bubble 그리기
				itr++;
			}
		}
		for (auto enemy : enemies) enemy.draw();
		player.draw();				//player 그리기

		glColor3f(0.0f, 1.0f, 0.0f);
		displayCharacters(GLUT_BITMAP_9_BY_15, "Score:" + to_string(player.getScore()), -boundaryX + 10.f, boundaryY - 30.f);
		displayCharacters(GLUT_BITMAP_9_BY_15, "Life:" + to_string(player.getLife()), -boundaryX + 10.f, boundaryY - 50.f);
	}

	
}


//vector<Wall> stagewall;
//vector<Platform> stageplatform;