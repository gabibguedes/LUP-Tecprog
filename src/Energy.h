/*********************************************************
       * File: Energy.h
       * Purpose: "Energy" class declaration
*********************************************************/

#ifndef SRC_Energy_H_
#define SRC_Energy_H_

#include "GameObject.h"
/*
This class controls the energy of the character used to perform actions of
attack.
*/

class Energy : public GameObject {
public:
		Energy(float x,float y,GameObject* planet, float rotation,float initialHeight, string file,int numberOfFrames);
		~Energy();
		void Update(float deltaTime);
		void Render();
		bool IsDead();
		Sprite getSprite();
		void NotifyCollision(GameObject&);
		bool Is(string type);
private:
		Sprite sprite;
		GameObject* planet;
		float initialHeight;
		bool dead;
		bool willDie;
};

#endif
