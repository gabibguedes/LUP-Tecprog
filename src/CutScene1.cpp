/*********************************************************
  * File: CutScene1.cpp
  * Purpose: Implementation of the story line before opening
	the game menu 
*********************************************************/

#include "CutScene1.h"
#include <SDL_keycode.h>
#include <iostream>

#include "InputManager.h"

//Frame images:
#define IMG_CUTSCENE_0 "img/cut-scene-final/Cutscene_Final_0.png"
#define IMG_CUTSCENE_1 "img/cut-scene-final/Cutscene_Final_1.png"
#define IMG_CUTSCENE_2 "img/cut-scene-final/Cutscene_Final_2.png"
#define IMG_CUTSCENE_3 "img/cut-scene-final/Cutscene_Final_3.png"

#define IMG_BLANK "img/blank.png"

#define AUDIO "audio/finalSong.ogg"

const unsigned int NUMBER_FRAMES_ANIMATION = 4;
const float FRAME_TIME_ANIMATION = 5;


//  Creator method, initialize the variables
CutScene1::CutScene1(): blank(IMG_BLANK),
                        sprite(IMG_CUTSCENE_0),
                        timer(), song(AUDIO){

	popRequested = false;
	quitRequested = false;
	frame = 0;
	showBlank = true;
	song.Play(1);
}


//  Destructor method, releases the alocated memory
CutScene1::~CutScene1() {
	song.Stop();
	sprite.Open(IMG_CUTSCENE_0);
	sprite.freeMe();
	sprite.Open(IMG_CUTSCENE_1);
	sprite.freeMe();
	sprite.Open(IMG_CUTSCENE_2);
	sprite.freeMe();
	sprite.Open(IMG_CUTSCENE_3);
	sprite.freeMe();
	blank.freeMe();

	cout << "Bye, LUP!" << endl;
}


// Updates the frame on screen
void CutScene1::Update(float deltaTime) {
	timer.Update(deltaTime);

	if (!popRequested) {
		if (timer.Get() > 1 && showBlank) {
			showBlank = false;
		} else if (timer.Get() > FRAME_TIME_ANIMATION) {
			frame++;

			switch (frame) {
			case 1:
				sprite.Open(IMG_CUTSCENE_1);
				timer.Restart();
				break;
			case 2:
				sprite.Open(IMG_CUTSCENE_2);
				timer.Restart();
				break;
			case 3:
				sprite.Open(IMG_CUTSCENE_3);
				timer.Restart();
				break;
			default:
				timer.Restart();
				break;
			}
		}
    
/* 
  In case the user press the space key, or the frame count reach the end, the
variable popRequested and quitRequested are set as True.
*/
		popRequested = InputManager::GetInstance().KeyPress(SDLK_SPACE)
			             || frame >= NUMBER_FRAMES_ANIMATION;
		quitRequested = popRequested;
	}
}


//  Method to render the sprites of the story
void CutScene1::Render() {
	if (!popRequested) {
		if (showBlank) {
			blank.Render(0, 0);
		} else {
			sprite.Render(0, 0);
		}
	}
}

void CutScene1::Pause() {
	song.Stop();
	blank.freeMe();
}

void CutScene1::Resume() {
	song.Play(1);
}
