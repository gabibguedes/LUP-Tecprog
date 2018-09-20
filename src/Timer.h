/*********************************************************
       * File: Timer.h
       * Purpose: "Timer" class declaration
*********************************************************/

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_
/*
This class controls the time passage in the game.
It has several uses in several other classes.
*/

class Timer {
public:
	Timer();
	void Update(float deltaTime);
	void Restart();
	float Get();
private:
	float time;
};

#endif
