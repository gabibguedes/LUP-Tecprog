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
	void Update(float dt);
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
	bool energyUpdate;
	void Die();
	int loopStart;
	int loopEnd;
	GameObject* planet;
	bool deveMudarDeFase;
	Timer deathAnimation;

private:
	Sprite body;          /* Player's character                                */
	Point speed;          /* The speed it walks                                */
	int hp;               /* Health points                                     */
	int xp;               /* Experience points                                 */
	Timer dmgCD;          /* Damage time??                                     */
	Timer knockback;      /* Timer to count the time the player is pushed back */
	Jumping jumpState;    /* The position and state the jump of the player is  */
	int jumpY;            /* The height of the jump                            */
	int jumped;           /* ??????????                                        */
	Facing kbDirection;   /* ??????????                                        */
	int c;                /* ??????????                                        */
	int qntEnergia;       /* Amount of energy                                  */
	Timer energiaCD;      /* ??????????                                        */

};


#endif
