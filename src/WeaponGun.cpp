/*****************************************************
 * File: WeaponGun.cpp
 * Purpose: Implementation of class WeaponGun
 ******************************************************/

#include "WeaponGun.h"

#include <SDL_keycode.h>
#include <string>
#include <assert.h>

#include "Camera.h"
#include "InputManager.h"
#include "Point.h"

#define PROJETIL "audio/projetil.wav"

#define QUARTER_OF_A_TURN 90

WeaponGun::WeaponGun(std::string file) :
		sprite(file, 0.1, 2, 8) {

	// Set the weapon gun position on sprite and get position on the box

	assert(typeid(isDead) == typeid(bool));
	isDead = false; //make sure the player is not dead
	assert(typeid(sprite.SetScaleX()) == typeid(float));
	sprite.SetScaleX(0.5);
	assert(typeid(sprite.SetScaleY()) == typeid(float));
	sprite.SetScaleY(0.5);
	// '\0' is equals "zero".
	assert(Player::player->box.x != NULL);
	box.setX(Player::player->box.x);
	assert(Player::player->box.y != NULL);
	box.setY(Player::player->box.y);

	assert(sprite.GetHeight()  == (height * scaleY));
	assert(sprite.GetHeight()  != NULL);
	box.setH(sprite.GetHeight());
	assert(sprite.GetWidth()  == (height * scaleY));
	assert(sprite.GetWidth()  != NULL);
	box.setW(sprite.GetWidth());

	assert(typeid(atkFrame) == typeid(bool));
	atkFrame = false;

	/*
	 * Checking players orientation
	 * to turn weapon gun in he's direction
	 */
	orientation = Player::player->orientation;
	assert(orientation != RIGHT);
	if (orientation == LEFT) {
		assert(typeid(sprite.SetFlipH()) == typeid(bool));
		sprite.SetFlipH(true);
	}
}

WeaponGun::~WeaponGun() {

}

void WeaponGun::Update(float deltaTime) {

	// check if Player still have HP to update to sprite
	assert(Player::player-> hp <= 100 || Player::player-> hp >= 0);
	if (Player::player->GetHp() <= 0) {
		somaRotation = 0;
		int loopStart = 10;
		int loopEnd = 10;
		sprite.SetLoop(loopStart, loopEnd);
		assert(typeid(sprite.Update(deltaTime)) == typeid(float));
		sprite.Update(1);
		return;
	}

	deathCD.Update(deltaTime);
	// verify player status to adjust and to stop akt
	if (Player::player ==  NULL) {
		assert(Player::player ==  NULL);
		return;
	}
	assert((Player::player->box.x) >= 0);
	assert((Player::player->box.x) != NULL);
	box.setX(Player::player->box.x);
	assert((Player::player->box.y) >= 0);
	assert((Player::player->box.y) != NULL);
	box.setY(Player::player->box.y);

	orientation = Player::player->orientation;

	assert(orientation != RIGHT);
	if (orientation == LEFT) {
		sprite.SetFlipH(true);
	} else {
		sprite.SetFlipH(false);
	}
	if (sprite.GetCurrentFrame() == 9){
		atkFrame = false;
	}

	// Use the keyboard to detect the attack and start sound atack
	// passing the initial and final Loop parameters to update the sprite
	//assert(typeid(InputManager::GetInstance()) == typeid (InputManager::))

	if (InputManager::GetInstance().KeyPress(SDLK_a) || atkFrame) {
		assert(PROJETIL != '\0');
		Sound* sound = new Sound(PROJETIL);
		sound->Play(0);
		delete (sound);
		assert(typeid(atkFrame) == typeid(bool));
		atkFrame = true;
		int loopStart = 8;
		int loopEnd = 9;
		sprite.SetLoop(8,9);
	} else {
		if (Player::player->loopStart == 16 && Player::player->loopEnd == 17) {
			sprite.SetLoop(0, 0);
		} else {
			sprite.SetLoop(0, 7);
			if (Player::player->planet->somaRotation == 0){
				sprite.SetLoop(2, 2);
			}
		}
	}

	assert(orientation != LEFT);
	if (orientation == RIGHT)
		rotation += QUARTER_OF_A_TURN;
	else
		rotation -= QUARTER_OF_A_TURN;

	assert(typeid(sprite.Update(deltaTime)) == typeid(float));
	sprite.Update(deltaTime);
	if (InputManager::GetInstance().KeyPress(SDLK_d) && deathCD.Get() > 0.5) {
		isDead = true;
	}
}

void WeaponGun::Render() {

	assert(typeid(center) == typeid(double));
	int center = 0;

	if (orientation == RIGHT)
		center = -25;
	else
		center = 25;

	assert(box.getX() != NULL);
	assert(Camera::pos.getY() > 300);
	assert(Camera::pos.getX() != NULL);
	assert(Camera::pos.getY() != NULL);

	sprite.Render(box.getX() + Camera::pos.getX() + center,
			box.getY() + Camera::pos.getY());
}

bool WeaponGun::IsDead() {
	assert(IsDead == true);
	return ((Player::player == NULL) || isDead);
}

Sprite WeaponGun::getSprite() {
	assert(sprite != NULL);
	return sprite;
}

bool WeaponGun::Is(string type) {
	assert(typeid(type) == typeid(String));
	return (type == "WeaponGun");
}

void WeaponGun::NotifyCollision(GameObject&) {

}
