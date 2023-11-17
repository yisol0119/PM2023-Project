#pragma once

#include <vector>
#include "Wall.h"
#include "Platform.h"
#include "Bubble.h"
#include "Enemy.h"
using namespace std;

class Stage
{
	friend class Collision;
	
public:
	enum STAGELEVEL { START, END, RESTART, FIRST, SECOND, THIRD };
	Stage(STAGELEVEL stage_level);


	void setPlayer(const Player& player);
	void setWall(const Wall& Wall);
	int getWallsize() const;
	void setPlatform(const Platform& platform);
	int getPlatformsize() const;
	void setBubble();
	int getBubblesize() const;
	void setEnemy(const Enemy& enemy);
	int getEnemysize() const;

	void setplayermove(bool bPressLeft, bool bPressRight, bool bPressUp, bool bPressSpace);
	void move(); //enemy, Bubble ¿òÁ÷ÀÓ
	
	void draw();
	
	Player player;
private:
	
	vector<Platform> stageplatform;
	vector<Wall> stagewall;
	vector<Bubble> bubbles;
	vector<Enemy> enemies;
	STAGELEVEL stagelevel;
	int capturebubble_count;
	

};

