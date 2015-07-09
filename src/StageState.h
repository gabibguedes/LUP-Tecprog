#ifndef SRC_STAGESTATE_H_
#define SRC_STAGESTATE_H_

#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Minion.h"
#include "Player.h"
#include "WeaponBroom.h"
#include "WeaponSword.h"
#include "WeaponGun.h"
#include "EnemyTank.h"
#include "Support.h"
#include "State.h"
#include "Music.h"
#include "UI.h"
#include "Plataforma.h"
#include "Planet.h"
#include "Planta.h"
#include "Enemy3.h"

using std::string;

class StageState: public State {
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	Sprite bg;
	Music music;
	UI ui;
	float xBg;
	Weapon* activeWeapon;
	Timer changeWpCD;
};

#endif /* SRC_STAGESTATE_H_ */
