/******************************************
 * File: 	Enemy3.cpp
 * Purpose: Implementation Enemy3 class 
 *****************************************/

#include "Enemy3.h"

#include <cmath>
#include <iostream>
#include <string>

#include "Bullet.h"
#include "Game.h"
#include "State.h"

/**
 * Constructor of Enemy3.
 * 
 * @param x, initial value of the location of the object on the x-axis (type real)
 * @param y, initial value of the location of the object on the y-axis (type real)
 * @param planet, pointer to GameObject
 * @param initialRotation, initial value of object rotation (type real)
 * @param initialHeight, initial height value of the object (type real)
 * 
 */

Enemy3::Enemy3(float x, float y, GameObject* planet, float initialRotation,
float initialHeight) : 
	sp("img/enemy3.png", 0.375, 3, 7), speed(), startPos(x, y),
	dmgCD(), knockback(), shootcd() {
	this->planet = planet;
	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = initialRotation;
	float arc = rotation*3.1415/180; // converts from degrees to radians
	initialHeight = alturaInicial;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 +
	planet->box.getCenterY() + initialHeight+box.getH())*cos(arc)) -
	(box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 +
	planet->box.getCenterY()  + initialHeight+box.getH())*sin(arc)) -
	(box.getH()/2));
	hp = 50;
	speed.x = 2;
	speed.y = 0;
	orientation = LEFT;
	sp.SetLoop(4, 5);
	knockback.Update(10);
}

Enemy3::~Enemy3()
{

}

/**
 * @brief used to update the position of the object in relation to the time
 * @param deltaTime: elapsed time since last update
*/
void Enemy3::Update(float deltaTime) {
	Point* playerPos = new Point(Player::player->box.getCenterX(),
			Player::player->box.getCenterY());
	Point* currentPos = new Point(box.getCenterX(), box.getCenterY());
	const  PI double = 3.1415; // constant of PI
	const  AUX_CONVERSION int = 180; //constant that assists in the conversion to radian

	dmgCD.Update(deltaTime);

	if (knockback.Get() < 0.3) { 
		if (kbDirection == LEFT)
			rotation -= 18*deltaTime;
		else
			rotation += 18*deltaTime;

		sp.Update(deltaTime);
	}
	else if (currentPos->getDist(*playerPos) <= 700
			&& currentPos->getDist(*playerPos) >= 500) {
		sp.SetLoop(4, 5);
		if (playerPos->x > currentPos->x) {
			orientation = RIGHT;
			sp.SetFlipH(true);
			rotation += 5*deltaTime;
		} else if (playerPos->x < currentPos->x) {
			orientation = LEFT;
			sp.SetFlipH(false);
			rotation -= 5*deltaTime;
		}
		sp.Update(deltaTime);
	} else if(currentPos->getDist(*playerPos) <= 500) {
		sp.SetLoop(0, 13);
		if ((sp.GetCurrentFrame() == 4 || sp.GetCurrentFrame() == 11) &&
			shootcd.Get() > 0.35) {
			if (playerPos->x > currentPos->x) {
				orientation = RIGHT;
				sp.SetFlipH(true);
			} else if (playerPos->x < currentPos->x) {
				orientation = LEFT;
				sp.SetFlipH(false);
			}
			Shoot(*playerPos);
			shootcd.Restart();
		}
		sp.Update(deltaTime);
	} else {
		sp.SetFrame(0);
		sp.Update(1);
	}

	if ((sp.GetCurrentFrame() == 0) || (sp.GetCurrentFrame() == 7))
	{
		Sound* sound = new Sound("audio/tiro3f.wav");
		sound->Play(0);
		delete(sound);
	}

	somaRotation = planet->somaRotation;
	rotation += somaRotation;

	float arc = rotation*PI/HALF_TURN; //converts from degrees to radians

	// Set new position of Box
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 +
	initialHeight+box.getH())*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 +
	initialHeight+box.getH())*sin(arc)) - (box.getH()/2));

	knockback.Update(deltaTime);
	shootcd.Update(deltaTime);
}

/**
 * @brief used to render the object vertically, so that it does not
 * overlap on another object.
*/
void Enemy3::Render()
{
	const MOVE_UP int = 90;
	sp.Render(box.getX() + Camera::pos.getX(), box.getY() + Camera::pos.getY(),
	rotation + MOVE_UP);
}

/**
 * @brief used to check if the object is dead
 * @return bool: true or false
*/
bool Enemy3::IsDead()
{
	return (hp <= 0);
}
/**
 * @brief method get standard, for the Sprite
 * @return Sprite
 */

Sprite Enemy3::getSprite()
{
	return sp;
}

/**
 * @brief used to check if the object is an Enemy3
 * @return true or false
 */
bool Enemy3::Is(string type)
{
	return (type == "Enemy3");
}

/**
 * @brief used for class object to shoot
 * @param pos, starting shot position
 */
void Enemy3::Shoot (Point pos)
{
	const  PI double = 3.141592653; // Constatnt PI
	Point* pspeed = new Point(box.getCenterX() - pos.getX(),box.getCenterY() -
	pos.getY());
	float angle = atan(pspeed->getY()/pspeed->getX());
	if(pspeed->getX() > 0){
		angle += PI;
	}
	delete(pspeed);

	float xBullet;
	float yBullet;

	/**
	 * @brief Direct the shot correctly
	 * result: shot direction
	*/
	if(orientation == LEFT)
	{
		if (sp.GetCurrentFrame() == 4)
		{
			xBullet = box.getX();
			yBullet = box.getCenterY();
		}
		else
		{
			xBullet = box.getX()+ box.getW()/2;
			yBullet = box.getCenterY() + box.getH()/2 - 20;
		}
	}
	else
	{
		if (sp.GetCurrentFrame() == 4)
		{
			xBullet = box.getX()+ box.getW();
			yBullet = box.getCenterY();
		}
		else
		{
			xBullet = box.getX() + box.getW()/2;
			yBullet = box.getCenterY() + box.getH()/2 - 20;
		}
	}

	Bullet* bullet = new Bullet(xBullet, yBullet, planet, angle, 0, 500,
	2000,"img/enemy3_bullet.png", true, 4); //Identação
	Game::GetInstance().GetCurrentState().AddObject(bullet);
}

/**
 * @brief used to notify character status after an attack
 * @param, a type of "physical" object of the game, such as "WeaponBroom"
*/
void Enemy3::NotifyCollision(GameObject& other) {
	if ((other.Is("WeaponBroom") && other.attacking) ||
		(other.Is("WeaponSword") && other.attacking) ||
		(other.Is("Support") && other.attacking)) {

		if (dmgCD.Get() > 0.5) {
			Sound* sound = new Sound("audio/dano.wav");
			sound->Play(0);
			delete(sound);
			dmgCD.Restart();
			hp -= 10;
			if (other.Is("Support"))
					hp = 0;

			knockback.Restart();

			if (box.getCenterX() < other.box.getCenterX())
				kbDirection = LEFT;
			else
				kbDirection = RIGHT;
		}

		if (IsDead()) {
			Player::player->IncXp(100);
			Sprite* aux = new Sprite("img/enemy3.png", 0.2, 3, 7);
			aux->SetScaleX(0.5);
			aux->SetScaleY(0.5);
			aux->SetLoop(14, 19);
			StillAnimation* animacao = new StillAnimation(box.getCenterX(),
					box.getCenterY(), planet, rotation, *aux, 0.2 * 6, true, box.getY()+90);
			Game::GetInstance().GetCurrentState().AddObject(animacao);
		}
	}
}
