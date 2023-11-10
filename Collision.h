#pragma once

#include "Bubble.h"
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"
#include "Wall.h"



class Collision {
public:
	bool isCollisionDetected(const Bubble& bub1, const Bubble& bub2);
	bool isCollisionDetected(const Enemy& Enm,const Bubble& bub);
	bool isCollisionDetected(const Player& ply, const Bubble& bub);
	bool isCollisionDetected(const Player& ply, const Enemy& Enm);
	bool isCollisionDetected(const Player& ply, const Wall& wal);
	bool isCollisionDetected(const Player& ply, const Platform& plat);
	bool isCollisionDetected(const Enemy& enm, const Wall& wal);
	bool isCollisionDetected(const Enemy& enm, const Platform& plat);

	void handleCollision(Bubble& bub1, Bubble& bub2);
	void handleCollision(Enemy& Enm, Bubble& bub);
	void handleCollision(Player& ply, Bubble& bub);
	void handleCollision(Player& ply, Enemy& Enm);
	void handleCollision(Player& ply, const Wall& wal);
	void handleCollision(Player& ply, Platform& plat);
	void handleCollision(Enemy& enm, const Wall& wal);
	void handleCollision(Enemy& enm, const Platform& plat);
};