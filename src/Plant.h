/*
 * Plant.h
 *
 *  Created on: 20/06/2015
 *      Author: Vitor
 */

#ifndef SRC_PLANTA_H_
#define SRC_PLANTA_H_

#include "GameObject.h"

class Plant: public GameObject {
public:
	Plant(float x,float y,GameObject* planet, float rotation,float initialHeight, string file); /*T28*/
	~Plant();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	void NotifyCollision(GameObject&);
	bool Is(string type);
private:
	Sprite sp;
	GameObject* planet;
	float initialHeight;
	bool dead;
};

#endif /* SRC_PLANTA_H_ */
