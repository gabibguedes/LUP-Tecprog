/*********************************************************
  * File: CutScene1.cpp
  * Purpose: Implementation of laser shooted by the enemies
*********************************************************/

#ifndef SRC_HorizontalLaser_H_
#define SRC_HorizontalLaser_H_

#include "GameObject.h" /* Class header file to include horizontalLaser 
						   as an object 
						*/
#include "Timer.h" /* Classe header file necessary to calculate time for 
					  updating object position
					*/

class HorizontalLaser : public GameObject{
public:
	HorizontalLaser(float x,float y,GameObject* planet, float rotation,
				 float initialHeight,int frameI,int frameC);
	~HorizontalLaser();
	void Update(float deltaTimeCalculator);
	void Render();
	bool IsDead();
	Sprite getSprite();
	void NotifyCollision(GameObject&);
	bool Is(string type);
private:
	Sprite sp; /* Laser sprite */
	GameObject* planet; /* Object where the laser will be included */
	float initialHeight;
	Timer timer;
	int loadedFrame;
	int frameInit;

};
#endif /* SRC_HorizontalLaser_H_ */
