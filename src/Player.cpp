/*********************************************************
  * File: Player.cpp
  * Purpose: Implementation of the player and it's actions
and behaviours during the game
*********************************************************/

#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "FinalState.h"

//Images files
#define IMG_BODY "img/Sprites_Corpo_LUP.png"
#define IMG_DEATH "img/Sprites_Morte_LUP.png"

//Audio files
#define AUDIO "audio/Start.wav" 
#define DANO "audio/dano.wav"

//Names of classes
#define PLAYER "Player"
#define SHIP "Ship"
#define ENERGY "Energia"
#define PLATFORM "Plataforma"
#define ENEMY_TANK "EnemyTank"
#define BULLET "Bullet"
#define PLANT "Planta"
#define LASER "Laser"
#define HORIZONTAL_LASER "HorizontalLaser"

Player* Player::player = NULL;

// Creator method, initialize the player variables
Player::Player(float x, float y,GameObject* planet):deathAnimation(),
                                                    body(IMG_BODY,0.15,4,8),
                                                    speed(),dmgCD(),knockback(),
                                                    energyCD(){
	body.SetScaleX(0.5);
	body.SetScaleY(0.5);
 
  //Resets the frame based on the player's character body dimension
	int newX = x - (body.GetFrameWidth()/2);
	int newY = y - (body.GetHeight()/2);
	newY += body.GetHeight()*3/2;
	box.setX(newX);
	box.setY(newY);
	box.setH(body.GetHeight());
	box.setW(body.GetWidth());
	
  hp = 100;             // The initial health points
	xp = 0;               // The player starts without any experience
	speed.x = 15;         // The player's speed start as 15
	speed.y = 15;
	jumpState = DJUMP;    // The player starts in a DJUMP state (not jumping)
	orientation = RIGHT;  // The initial orientation is right
	jumped = 250;         // The initial jump hight is 250
	player = this;        
	loopStart = 0;
	loopEnd = 0;
	this->planet = planet;

	knockback.Update(10);
	
  Sound* sound = new Sound(AUDIO);
	sound->Play(0);     
	delete(sound);
	
  amountOfEnergy = 0;   // The player starts without energy
	shouldChangeLevel = false;
	jumpY = 0;
	energyUpdate = false;
	kbDirection = RIGHT;
	center = 0;

}

//Destructor method, disalocate the player
Player::~Player(){
	player = NULL;
}

/*
  Method to update the player and verify if is time to change levels based on
health points and death animation
*/
void Player::Update(float deltaTime) {
  /* 
    Verifies if the player has health points, if not, verifies the state of the
  death animation
  */
	if (hp <= 0) {
		if (deathAnimation.Get() > 2.4) {
			deathAnimation.Restart();
			knockback.Update(1);
			hp = 100;
			amountOfEnergy = 0;
			shouldChangeLevel = true;
      
      // Verifies in wich level the game is and wich it's supose to go
			if (planet->nPlaneta == 1) {
				State* stageState = new StageState();
				Game::GetInstance().Push(stageState);
			} else if (planet->nPlaneta == 3) {
				State* stageState = new FinalState();
				Game::GetInstance().Push(stageState);
			}
		}
		somaRotation = 0;
		body.SetLoop(14,14);
		body.Update(1);
		deathAnimation.Update(deltaTime);
		return;
	}

	knockback.Update(deltaTime);
	dmgCD.Update(deltaTime);
	jumpY = planet->getAltura(planet->rotation);
	somaRotation = 0;

  /*
    In case the user press the left button on the mouse, the y position of the
  box end the jump is printed on terminal.
  */
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		cout << box.getY() << endl;
		cout << "jumpY :" << jumpY << endl;
	}

  // Verifies if the player has been knocked back and the intensity of it
	if (knockback.Get() < 0.3) {
		loopStart = 16;
		loopEnd = 17;

    // If the knockback is small enough, the rotation goes back to what is
		if (kbDirection == LEFT) {
			somaRotation = 1;
		} else { 
			somaRotation = -1;
    }

	} else {

    //Verifies if player shoud change jumping state
		if(InputManager::GetInstance().KeyPress(SDLK_UP) && jumpState != DJUMP) {
			body.SetFrame(8);
			if (jumpState == STAND) {
				jumpState = JUMP;
				jumped = 0;
			}	else if (jumpState == JUMP) {
				jumpState = DJUMP;
				jumped = 0;
			}
		}

		/*
      Verifies if the player should walk, wich side it should go and updates
    the variables to do so.
    */
		if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT)) {
				loopStart = 0;
				loopEnd = 7;
				orientation = LEFT;
				body.SetFlipH(true);
				somaRotation = 1;
		} else if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT)) {
			loopStart = 0;
			loopEnd = 7;
			orientation = RIGHT;
			body.SetFlipH(false);
			somaRotation = -1;
		} else {
			loopStart = 1;
			loopEnd = 1;
			body.Update(0);
		}

    // If the space key is pressed the rotation is faster, so the player is running
		if(InputManager::GetInstance().IsKeyDown(SDLK_SPACE)){
			somaRotation*=2;
		}
    
    // Verifies the height of the next obstacle
		int nextHeight = planet->getAltura(planet->rotation + somaRotation);
		
    //Verifies how much higher it is
		int heightDifference = nextHeight - box.getY();

    // Verifies if the player can jump
		if(planet->podeSubir(planet->rotation + somaRotation) || heightDifference >= 0){
			if(jumpState == STAND && box.getY() == jumpY){
				box.setY(box.getY() + heightDifference);
      }
		}else{
			somaRotation = 0;
		}

    /*
      If the player walks and the jumpY isn't in the same level as the gorund,
      the player falls from the platform
    */
		if(somaRotation != 0 && jumpState == STAND){
			if(jumpY > box.getY()){
				jumpState = JUMP;
				jumped = 300;
			}
		}
	}

  // Makes so if the player goes deeper than the ground, it goes back to the ground
	if(box.getY() > jumpY){
		box.setY(jumpY);
	}

  // Updates the jumping state
	if (jumpState == JUMP || jumpState == DJUMP) {
		if (jumped <= 150) {
			jumped += speed.y;
			box.setY(box.getY() - speed.y);
		} else if (box.getY() < jumpY) {
			box.setY(box.getY() + speed.y);
		} else {
			jumpState = STAND;
			jumped = 0;
		}
		loopStart = 8;
		loopEnd = 10;

		if (body.GetCurrentFrame() >= 10) {
			loopStart = 10;
			body.Update(0);
		}
	}

	// Ajusts the rotation variable of the planet
	somaRotation = somaRotation/planet->nPlaneta;

	body.SetLoop(loopStart,loopEnd);
	body.Update(deltaTime);
	energyCD.Update(deltaTime);
}

// Method to render player on screen and ajust the camera to it's position
void Player::Render() {
	center = 0;

	if (orientation == RIGHT) {
		center = -25;
	} else {
		center = 25;
  }
	body.Render(box.getX() + Camera::pos.getX() + center,box.getY() + 
              Camera::pos.getY());
}

// Method to verify the class of the GameObject
bool Player::Is(string type) {
	return (type == PLAYER);
}

// Method to deny the player's death
bool Player::IsDead(){
	return false;
}

Sprite Player::getSprite() {
	return body;
}

// Method to handle the player's colisions
void Player::NotifyCollision(GameObject& other) {

  // Handles the colision with ships, player loses energy and change level
	if(other.Is(SHIP)  && abs(box.getCenterX() - other.box.getCenterX()) < 50 ){
		if(amountOfEnergy > 2){
			amountOfEnergy = 0;
			shouldChangeLevel = true;
			if(planet->nPlaneta == 1){
				State* stageState = new FinalState();
				Game::GetInstance().Push(stageState);
			}
		}
	}
  // Colision with energy, updates player's amount of energy
	if(other.Is(ENERGY)){
			if(energyCD.Get() > 0.5){
				energyCD.Restart();
				energyUpdate = true;
				amountOfEnergy++;
			}
	}

  // Handles colition with Platform, checks positions and updates jumping state
	if(other.Is(PLATFORM)){
		if(box.getY() + box.getH()/2 < other.box.getY() && jumped >= 150 &&
       box.getX() + box.getW()/2 + center + 10 > other.box.getX() &&
       box.getX() + box.getW()/2 + center - 10 < other.box.getX() +
       other.box.getW())
		while(box.getY() + box.getH()*0.75 > other.box.getY()){
			box.setY(box.getY() - 1);
			jumpState = STAND;
		}
	}

  // Colision with Enemy Tanks, player get damaged, loses health points
	if (other.Is(ENEMY_TANK) && other.attacking) {
		if (dmgCD.Get() > 1) {
			Sound* sound = new Sound(DANO);
			sound->Play(0);
			delete(sound);
			dmgCD.Restart();
			hp -= 10;
      
      // Player is knocked back
			knockback.Restart();

      // Verifies the position to update the knocked back direction
			if (box.getCenterX() < other.box.getCenterX()) {
				kbDirection = LEFT;
			} else {
				kbDirection = RIGHT;
      }

      // If the player is out of health points it dies
			if (hp<=0) {
				Die();
			}
		}
	}
  
  /*
    Colision with Bullets or Plants the player loses health points get knocked
    back.
  */
	if (other.Is(BULLET) || (other.Is(PLANT) &&
      abs(box.getCenterX() - other.box.getCenterX()) < 50)) {
		if (dmgCD.Get() > 1) {
			Sound* sound = new Sound(DANO);
			sound->Play(0);
			delete(sound);
			dmgCD.Restart();
			hp -= 10;

			knockback.Restart();

			if (box.getCenterX() < other.box.getCenterX()){
				kbDirection = LEFT;
			} else {
				kbDirection = RIGHT;
      }
      // Verifies if player is out of health points
			if (hp<=0) {
				Die();
			}
		}
	}

  // Colision with laser, player loses health points
	if(other.Is(LASER) && abs(box.getCenterX() - other.box.getCenterX()) < 20 &&
     other.getSprite().GetCurrentFrame() !=0) {
		hp -= 10;
	}

  // Colision with horizontal laser, player loses health points
	if(other.Is(HORIZONTAL_LASER)&&abs(box.getCenterY()-other.box.getCenterY())<20&&
     other.getSprite().GetCurrentFrame() !=0) {
			hp -= 10;
	}

  /*
    Handles case of death, the camera stops following the player and the still
    animation is shown
  */
	if (IsDead()) {
		Camera::Unfollow();
		Sprite* aux = new Sprite(IMG_DEATH, 0.2, 1, 9);
		aux->SetScaleX(0.5);
		aux->SetScaleY(0.5);
		aux->SetLoop(0, 6);
		StillAnimation* animacao = new StillAnimation(box.getCenterX(),
				box.getCenterY(), planet, rotation, *aux, 0.2 * 7, true, box.getY()-50);
		Game::GetInstance().GetCurrentState().AddObject(animacao);
	}
}

int Player::GetHp() {
	return hp;
}

int Player::GetXp() {
	return xp;
}

// Method not implemented
int Player::GetSpecial() {
	return 0;
}


//Method to increment experience points
void Player::IncXp(int xp) {
	this->xp += xp;
}

bool Player::GetEnergyUpdate() {
	return energyUpdate;
}

// Method to kill the player
void Player::Die() {
	Sprite* aux = new Sprite(IMG_DEATH, 0.2, 1, 8);
	aux->SetScaleX(0.5);
	aux->SetScaleY(0.5);
	aux->SetLoop(0, 6);
	StillAnimation* animacao = new StillAnimation(box.getCenterX(),
			box.getCenterY(), planet, rotation, *aux, 0.2 * 7, true, box.getY() + 30);
	Game::GetInstance().GetCurrentState().AddObject(animacao);
}
