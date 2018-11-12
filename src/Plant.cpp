/*
 * Plant.cpp
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#include "Planta.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

const unsigned int PI = 3.14159265359;  /*T25*/
const unsigned int HALF_TURN = 180;  /*T25*/
const unsigned int QUARTER_OF_A_TURN = 90;  /*T25*/

Plant::Plant(float x,float y,GameObject* planet, float rotation,float initialHeight, string file):sp(file) { /*T25*/
	this->planet = planet;

	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->initialHeight =PI/HALF_TURN; /*T28*/
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY() + alturaInicial)*sin(arc)) - (box.getH()/2));
	dead = false;

}

Plant::~Plant() { /*T28*/
	//delete(&sp);
}

void Plant::Update(float dt){
	somaRotation = planet->sumRotation; /*T28*/
	rotation += sumRotation; /*T28	*/

		float arc = rotation*PI/HALF_TURN; /*T28*/
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));
}

void Plant::Render(){ /*T28*/
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() + Camera::pos.getY(),rotation + QUARTER_OF_A_TURN);
}

bool Plant::IsDead(){ /*T28*/
	return dead;
}

Sprite Plant::getSprite(){ /*T28*/
	return sp;
}

void Plant::NotifyCollision(GameObject& other){
}

bool Plant::Is(string type){
	return (type == "Plant"); /*T28*/
}
