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
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	Sprite blank;
	Sprite sprite;
	//std::vector<Sprite*> selector;
	Timer timer;
	Music song;
	unsigned int frame;
	bool showBlank;
};

#endif /* SRC_CUTSCENE_H_ */
