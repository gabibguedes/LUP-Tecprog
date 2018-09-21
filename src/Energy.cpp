/*********************************************************
       * File: Energy.h
       * Purpose: "Energy" class implementation
*********************************************************/

#include "Energy.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

#define PI 3.14159265359
#define HALF_TURN 180
#define QUARTER_OF_A_TURN 90


Energy::Energy(float x,float y,GameObject* planet, float rotation,float initialHeight, string file,int numberOfFrames):sprite(file,0.3,1,numberOfFrames) {
	this->planet = planet;
	sprite.SetScaleX(0.2);
	sprite.SetScaleY(0.2);
	box.setH(sprite.GetHeight());
	box.setW(sprite.GetWidth());
	this->rotation = rotation;
	this->initialHeight = initialHeight;
	float angle = rotation*PI/HALF_TURN;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + initialHeight)*cos(angle)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY() + initialHeight)*sin(angle)) - (box.getH()/2));
	dead = false;
	willDie = false;
	sprite.SetLoop(0,numberOfFrames-1);

}

Energy::~Energy() {

}

void Energy::Update(float deltaTime){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;
	/*...somaRotation is out of the established standard
	because it is defined in a class that has not
	yet been refactored.*/

		float angle = rotation*PI/HALF_TURN;
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + initialHeight)*cos(angle)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + initialHeight)*sin(angle)) - (box.getH()/2));
		sprite.Update(deltaTime);
		if(willDie)
			dead = true;

}

void Energy::Render(){
	sprite.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation + QUARTER_OF_A_TURN);
}

bool Energy::IsDead(){
	return dead;
}

Sprite Energy::getSprite(){
	return sprite;
}

void Energy::NotifyCollision(GameObject& other){
	if (other.Is("Player"))
		{
			willDie = true;
		}
}

bool Energy::Is(string type){
	return (type == "Energy");
}
