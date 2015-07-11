/*
 * Laser.cpp
 *
 *  Created on: 11/07/2015
 *      Author: Vitor
 */


#include "Laser.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Laser::Laser(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file,int frameC):sp(file,0.15,1,10),timer() {
	this->planet = planet;

	box.x = x;//int novox = x - (sp.GetFrameWidth() / 2);
	//int novoy = y - (sp.GetHeight() / 2);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->alturaInicial = alturaInicial;
	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY() + alturaInicial)*sin(arc)) - (box.getH()/2));
	frameCarregado = frameC;
	sp.SetLoop(0,0);


}

Laser::~Laser() {
	// TODO Auto-generated destructor stub
}

void Laser::Update(float dt){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;

		float arc = rotation*3.1415/180;
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));
		timer.Update(dt);
		if(timer.Get() > 5){
			timer.Restart();
			if(sp.GetCurrentFrame() == 0){
				sp.SetLoop(frameCarregado,frameCarregado);
			}else{
				sp.SetLoop(0,0);
			}
		}
}

void Laser::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation + 90);
}

bool Laser::IsDead(){
	return false;
}

Sprite Laser::getSprite(){
	return sp;
}

void Laser::NotifyCollision(GameObject&){

}

bool Laser::Is(string type){
	return (type == "Laser");
}
