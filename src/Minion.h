/*********************************************************
       * File: Minion.h
       * Purpose: "Minion" class declaration
*********************************************************/

#ifndef SRC_MINION_H_
#define SRC_MINION_H_
#include "GameObject.h"
#include "Point.h"
#include "Bullet.h"

/*
This class controls the energy of the character used to perform actions of
attack.
*/

class Minion: public GameObject{
public:
	Minion(GameObject* minionCenter, float arcOffSet);
	~Minion(){}
	void Update(float deltaTime);
	void Render();
	bool IsDead();
	void Shoot(Point pos);
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
private:
	GameObject* center;
	Sprite sprite;
	float arc;
};



#endif
