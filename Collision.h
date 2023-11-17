#pragma once

#include "Bubble.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

class Stage;
class Platform;

class Collision {


public:

	enum COLLISION_TYPE { NONE, ONPLAT, LEFT, RIGHT, TOP, BOTTOM }; // collision�� ��𿡼� �Ͼ���� ��ȯ�ϴ� ENUM
	//ONPLAT�� TOP�� �ٸ���

	void collide(Stage& stage);
	bool isCollisionDetected(const Bubble& bub1, const Bubble& bub2);
	bool isCollisionDetected(const Enemy& Enm,const Bubble& bub);
	bool isCollisionDetected(const Player& ply, const Bubble& bub);
	bool isCollisionDetected(const Player& ply, const Enemy& Enm);
	COLLISION_TYPE isCollisionDetected(const Player& ply, const Wall& wal);   // wall, platform�� �浹 ������ �ٸ��� ������ 
	COLLISION_TYPE isCollisionDetected(const Player& ply, const Platform& plat);
	COLLISION_TYPE isCollisionDetected(const Enemy& enm, const Wall& wal);
	COLLISION_TYPE isCollisionDetected(const Enemy& enm, const Platform& plat);

	void handleCollision(Bubble& bub1, Bubble& bub2);
	bool handleCollision(Enemy& Enm, Bubble& bub); //��ȯ���� �浹 ���θ� �ǹ�
	bool handleCollision(Player& ply, Bubble& bub);//��ȯ���� �浹 ���θ� �ǹ�
	void handleCollision(Player& ply, Enemy& Enm);
	void handleCollision(Player& ply, const Wall& wal);
	void handleCollision(Player& ply, Platform& plat);
	void handleCollision(Enemy& enm, const Wall& wal);
	void handleCollision(Enemy& enm, Platform& plat);
};