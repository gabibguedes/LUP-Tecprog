/******************************************
 * File: Enemy3.h
 * Purpose: this class represents a
 * character (enemy) of the game
 *****************************************/

#ifndef SRC_ENEMY3_H_
#define SRC_ENEMY3_H_

#include "Sprite.h"
#include "Point.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"

class Enemy3: public GameObject {
public:
	Enemy3(float x, float y, GameObject* planet, float initialRotation, float alturaInicial);
	~Enemy3();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void Shoot (Point pos);
	void NotifyCollision(GameObject&);
private:
	Sprite sp; // Sprite to show the frames of the story
	Point speed; // Reference point for speed calculation
	Point startPos; // References point to set start position
	int hp; // saves the amount life of the character
	Timer dmgCD; // Time damage
	Facing orientation; // Enum of orientation of object
	GameObject* planet; // Pointer for planet (a type of game object)
	float alturaInicial; // Initial Height of character
	Timer knockback; // Time of knockback
	Timer shootcd; // Time of shoot
	Facing kbDirection; // Enum of Direction of object
};



#endif /* SRC_ENEMY3_H_ */
