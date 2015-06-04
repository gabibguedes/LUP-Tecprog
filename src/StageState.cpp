#include "StageState.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"
#include "Collision.h"

StageState::StageState() :
		tileSet(64, 64, "img/tileset.png"), tileMap("map/tileMap.txt",
				&tileSet), bg("img/ocean.jpg"), music("audio/stageState.ogg"),planeta("img/planeta.png"), ui(
				3) {
	quitRequested = false;
	srand((unsigned int) time(NULL));
	/*
	 GameObject* penguin = new Penguins(1920,100);
	 objectArray.emplace_back(penguin);
	 Camera::Follow(penguin);
	 */

	GameObject* player = new Player(0, 0);
	objectArray.emplace_back(player);
	Camera::Follow(player);

	GameObject* weapon = new Weapon("img/lup_vassoura.png");
	objectArray.emplace_back(weapon);

	GameObject* tank = new EnemyTank(500, 0);
	objectArray.emplace_back(tank);

	GameObject* support = new Support();
	objectArray.emplace_back(support);

	GameObject* plataforma1 = new Plataforma1(200,-100,0);
	objectArray.emplace_back(plataforma1);

	rotacaoPlaneta = 0;
	raioPlaneta = 1000;

	//GameObject* alien = new Alien(512,300,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien);
	//GameObject* alien2 = new Alien(300,512,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien2);
	//GameObject* alien3 = new Alien(1000,1000,5,(rand()%5) + dd3);
	//objectArray.emplace_back(alien3);

}

void StageState::Update(float dt) {
//	if(SDL_QuitRequested()){
//		quitRequested = true;
//	}

	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		std::cout
				<< InputManager::GetInstance().GetMouseX() - Camera::pos.getX()
				<< std::endl;
		std::cout
				<< InputManager::GetInstance().GetMouseY() - Camera::pos.getY()
				<< std::endl;
	}

//	if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
//		rotacaoPlaneta += 50*dt;
//	}
//
//	if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
//			rotacaoPlaneta -= 50*dt;
//		}

	Camera::Update(dt);
	quitRequested = InputManager::GetInstance().QuitRequested();
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	UpdateArray(dt);
	ui.Update(dt);
}

void StageState::Render() {
	bg.Render(0, 0);
	//tileMap.RenderLayer(0, Camera::pos.getX(), Camera::pos.getY());
	planeta.Render(-1000,-300+Camera::pos.getY(),Camera::rotation);
	RenderArray();
	//tileMap.Render(Camera::pos.getX(), Camera::pos.getY());
	ui.Render();
}

StageState::~StageState() {
	objectArray.clear();
}

void StageState::Pause() {
	music.Stop();

}

void StageState::Resume() {
	//music.Play(-1);
}
