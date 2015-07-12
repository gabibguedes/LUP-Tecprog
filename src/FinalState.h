/*
 * FinalState.h
 *
 *  Created on: 11/07/2015
 *      Author: Vitor
 */

#ifndef SRC_FINALSTATE_H_
#define SRC_FINALSTATE_H_

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "Timer.h"
#include "UI.h"
#include "Plataforma.h"
#include "Planet.h"
#include "Planta.h"
#include "Enemy3.h"
#include "PlanetaFundo.h"
#include "Cometa.h"
#include "Energia.h"
#include "Laser.h"
#include "Nave.h"

class Weapon;

using std::string;

class FinalState: public State {
public:
	enum WeaponName_lazy {
		BROOM, SWORD, GUN
	};

	FinalState();
	~FinalState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	static WeaponName_lazy CheckWeapon();
private:
	Sprite bg;
	Music music;
	UI ui;
	float xBg;
	Weapon* activeWeapon;
	Timer changeWpCD;
	static WeaponName_lazy weapon;
};

#endif /* SRC_FINALSTATE_H_ */
