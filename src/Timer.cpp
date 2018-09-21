/*********************************************************
       * File: Timer.h
       * Purpose: "Timer" class implementation
*********************************************************/
#include "Timer.h"

Timer::Timer() {
	time = 0;
}

void Timer::Update(float deltaTime) {
	time += deltaTimet;
}

void Timer::Restart() {
	time = 0;
}

float Timer::Get() {
	return time;
}
