#include "Weapon.h"

Weapon::Weapon(std::string file) : sp(file,0.1,3,9)
{
	box.setX(Player::player->box.x);
	box.setY(Player::player->box.y);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());

	orientation = Player::player->orientation;
	if (orientation == LEFT)
		sp.SetFlipH(true);
}

Weapon::~Weapon()
{

}

void Weapon::Update(float dt)
{
	box.setX(Player::player->box.x);
	box.setY(Player::player->box.y);
	orientation = Player::player->orientation;

	if (orientation == LEFT)
		sp.SetFlipH(true);
	else
		sp.SetFlipH(false);

	if (sp.GetCurrentFrame() == 22)
		attacking = false;

	if(InputManager::GetInstance().KeyPress(SDLK_a) || attacking)
	{
		attacking = true;
		sp.SetLoop(19, 22);
	}
	else
	{
		sp.SetLoop(Player::player->loopStart, Player::player->loopEnd);
	}
	sp.Update(dt);
}

void Weapon::Render()
{
	int c;
	if (orientation == RIGHT)
		c = -80;
	else
		c = 80;

	sp.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
}

bool Weapon::IsDead()
{
	return false;
}

Sprite Weapon::getSprite()
{
	return sp;
}

bool Weapon::Is(string type)
{
	return (type == "Weapon");
}

void Weapon::NotifyCollision(GameObject&)
{

}
