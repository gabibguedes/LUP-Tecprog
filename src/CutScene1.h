 /*********************************************************
  * File: CutScene1.h
  * Purpose: "CutScene1" class declaration
 *********************************************************/

#ifndef SRC_CUTSCENE_H_
#define SRC_CUTSCENE_H_

#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "Timer.h"

/*
This class represents the change of scenery in the game, considering the images,
the music and all the other changes it comes with it.
*/

class CutScene1: public State {
public:
	CutScene1();
	virtual ~CutScene1();
	void Update(float deltaTime);
	void Render();
	void Pause();
	void Resume();
private:
	Sprite blank;         /* Sprite of a blank screen                         */  
	Sprite sprite;        /* Sprite to show the frames of the story           */
	Timer timer;          /* Variable to keep track of the time passed        */
	Music song;           /* Backgroung song                                  */
	unsigned int frame;   /* Integer to reference the frame it's showing      */
	bool showBlank;       /* Boolean to define if its to use the blank sprite */
};

#endif
