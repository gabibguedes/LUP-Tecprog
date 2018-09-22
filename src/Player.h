/*********************************************************
  * File: Player.h
  * Purpose: Player class declaration
*********************************************************/

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "GameObject.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"

//Enumerates the jumping states of the player
enum Jumping { STAND, JUMP, DJUMP };

/*
  This class establish the player and all it's characteristics, as the amount of
Energy, the resources, it's Sprite, and all that is necessary for his pourpouse
on the game 
*/
class Player : public GameObject{
public:
	Player(float x,float y,GameObject* planet);
	~Player();
	void Update(float deltaTime);
	void Render();
	bool IsDead();
	Sprite getSprite();
	static Player* player;
	bool Is(string type);
	void NotifyCollision(GameObject&);
	int GetHp();
	int GetXp();
	int GetSpecial();
	void IncXp(int xp);
	bool GetEnergyUpdate();
	bool energyUpdate;        // Should update the player's energy
	void Die();
	int loopStart;            // Marks the start of the loop
	int loopEnd;              // Marks the end of the loop
	GameObject* planet;       // The planet of the level
	bool shouldChangeLevel;   // Variable confirm if it's time to change levels
	Timer deathAnimation;     // Marks the time of the death animation

private:
	Sprite body;          // Player's character
	Point speed;          // The speed it walk
	int hp;               // Health points
	int xp;               // Experience points                                 
	Timer dmgCD;          // "Damage cool down" time between demages                                     
	Timer knockback;      // Timer to count the time the player is pushed back 
	Jumping jumpState;    // The position and state the jump of the player is  
	int jumpY;            // The height of the jump                            
	int jumped;           // How much the player has jumped                                        
	Facing kbDirection;   // Direction of player
	int center;           // Marks the center
	int amountOfEnergy;   // Saves the player energy status           
	Timer energyCD;       // Time between energies

};


#endif
