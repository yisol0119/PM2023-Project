#pragma once

#include <vector>
#include "Wall.h"
#include "Platform.h"
using namespace std;

class Stage
{
public:
	Stage();
	void setWall(const Wall& Wall);
	vector<Wall> getWall() const;
	void setPlatform(const Platform& platform);
	vector<Platform> getPlatform() const;
	void draw();

private:
	vector<Wall> stagewall;
	vector<Platform> stageplatform;

};

