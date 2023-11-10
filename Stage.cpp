#include "Stage.h"

Stage::Stage() {

}

void Stage::setWall(const Wall& wal) {
	stagewall.push_back(wal);
}
vector<Wall> Stage::getWall() const{

	return stagewall;
}

void Stage::setPlatform(const Platform& plat) {
	stageplatform.push_back(plat);
}
vector<Platform> Stage::getPlatform() const {
	return stageplatform;
}
void Stage::draw() {
	for (auto wal : stagewall) wal.draw();
	for (auto plat : stageplatform) plat.draw();
}

//vector<Wall> stagewall;
//vector<Platform> stageplatform;