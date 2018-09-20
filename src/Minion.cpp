/*********************************************************
       * File: Minion.h
       * Purpose: "Minion" class implementation
*********************************************************/

#include "Minion.h"
#include "Game.h"
#include "Camera.h"

#define PI 3.14159265359
#define HALF_TURN 180

Minion::Minion(GameObject* minionCenter,float arcOffSet) : sprite("img/minion.png"){

	center = minionCenter;
	arc = arcOffSet;
	rotation = (arc*HALF_TURN/PI)-HALF_TURN;
	box.setH(sprite.GetHeight());
	box.setW(sprite.GetWidth());
	box.setX(center->box.getCenterX() + (200*cos(arc)) - (box.getW()/2));
	box.setY(center->box.getCenterY()  + (200*sin(arc)) - (box.getH()/2));
	float scale = (((rand())%50)+100)/100.0;
	sprite.SetScaleX(scale);
	sprite.SetScaleY(scale);
}

/*Updates position according to position and time,
based on the movement pattern and the previous position*/
void Minion::Update(float deltaTime){
	arc += PI/10*deltaTime;
	rotation = (arc*HALF_TURN/PI)-HALF_TURN;
	float x = center->box.getCenterX() + (100*cos(arc)) - (box.getW()/2);
	float y = center->box.getCenterY()  + (100*sin(arc)) - (box.getH()/2);
	box.setX(x);
	box.setY(y);
}

void Minion::Render(){
	sprite.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation);
}

bool Minion::IsDead(){
	return false;
}

void Minion::Shoot(Point pos){
	Point* pspeed = new Point(box.getCenterX() - pos.getX(),box.getCenterY() - pos.getY());
	float angle = atan(pspeed->getY()/pspeed->getX());
	if(pspeed->getX() > 0){
		angle += PI;
	}
	delete(pspeed);
}

Sprite Minion::getSprite(){
	return sprite;
}

bool Minion::Is(string type){
	return (type == "Minion");
}

void Minion::NotifyCollision(GameObject& other){

}
