/*********************************************************
  * File: CutScene1.cpp
  * Purpose: Implementation of laser shooted by the enemies
*********************************************************/

#include "HorizontalLaser.h" /* Header file of the class */
#include "Camera.h" /* Camera class header to follow the lasers */ 
#include "Game.h"	/* Game class header to calculate times and frames */
#include "InputManager.h" /* InputManager class header to see if the shoot key was pressed */
#define HALF_TURN 180
#define MOVEMENT 300
#define LASER_IMG "img/laser.png"
#define HORIZONTAL "HorizontalLaser" /* Object type */

const float ANGLE = 3.1415/180; /* Converting angle in degrees to radians */

/* 
	Creator method, initialize the variables 
*/

HorizontalLaser::HorizontalLaser(float x,float y,GameObject* planet, float rotation,
						   float initialHeight,int frameI,int frameC)
						   :sp(LASER_IMG,0,2,8),timer() {

	this->planet = planet;
	box.x = x;
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->initialHeight = initialHeight;
	float arc = rotation * ANGLE;

	box.setX(planet->box.getCenterX() + ((planet->box.getW() / 2 + 
			 planet->box.getCenterY() + initialHeight) * cos(arc)) - 
			 (box.getW() / 2));
	box.setY(planet->box.getCenterY() + ((planet->box.getH() / 2 + 
			 planet->box.getCenterY() + initialHeight) * sin(arc)) - 
			 (box.getH() / 2));
	
	loadedFrame = frameC;
	frameInit = frameI;
	sp.SetFlipH(false);
	sp.SetFrame(frameInit - 1);
	sp.SetLoop(frameInit - 1,frameInit - 1);
	sp.Update(0);

}
/* Empty destructor method */
HorizontalLaser::~HorizontalLaser() {}

/* 
	Update the laser frame on the screen 
*/
void HorizontalLaser::Update(float deltaTimeCalculator){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;

		float arc = rotation * ANGLE; /* rotation in radians */
		box.setX(planet->box.getCenterX() + ((planet->box.getW() / 2 - 
				 MOVEMENT + initialHeight) * cos(arc)) - (box.getW() / 2)); /* Updating X position */
		box.setY(planet->box.getCenterY() + ((planet->box.getH() / 2 - 
				 MOVEMENT + initialHeight) * sin(arc)) - (box.getH() / 2)) /* Updating Y position */ 
		timer.Update(deltaTimeCalculator);
		if (timer.Get() > 1) { /* if the timer counter is too big, restart the counter to update
								  the current frame */
			timer.Restart();
			if (sp.GetCurrentFrame() == frameInit - 1) { /* if the frame isn't updated yet, update */
				sp.SetFrame(loadedFrame - 1);
				sp.SetLoop(loadedFrame - 1,loadedFrame - 1);
			} else { /* if the frame is already updated, continue with last frame */
				sp.SetFrame(frameInit - 1);
				sp.SetLoop(frameInit - 1,frameInit - 1);
			}
		}
		sp.Update(0);
}
/* 
	Render the Laser in the current position X and Y
*/
void HorizontalLaser::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() + 
			  Camera::pos.getY(),rotation + HALF_TURN);
}

/* 
	Makes the laser continuing showing up on the screen
*/

bool HorizontalLaser::IsDead(){
	return false;
}
/* 
	Get the laser Sprite
*/

Sprite HorizontalLaser::getSprite(){
	return sp;
}

bool HorizontalLaser::Is(string type){
	return (type == HORIZONTAL);
}
