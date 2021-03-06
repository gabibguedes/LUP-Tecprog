#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite() {
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	width = 0;
	height = 0;
	frameCount = 1;
	frameTime = 1;
	currentFrame = 0;
	timeElapsed = 0;
	loopStart = 0;
	loopEnd = 0;
	flipH = false;
}

Sprite::Sprite(string file, float frameTime, float rows, float columns) :
		myFile(file) {
	texture = NULL;
	this->frameTime = frameTime;
	this->rows = rows;
	this->columns = columns;
	currentFrame = 0;
	timeElapsed = 0;
	loopStart = 0;
	loopEnd = 0;
	Open(file);
	scaleX = 1;
	scaleY = 1;
	flipH = false;
}

Sprite::~Sprite() {
//	if(texture != NULL){
//		SDL_DestroyTexture(texture);
//	}
}

void Sprite::freeMe() {
	Resources::removeImage(myFile);
}

void Sprite::Open(string file) {

	texture = Resources::GetImage(file);
	if (texture == NULL) {
		cout << "ERRO ao inicializar texture!! :(" << endl;
		cout << SDL_GetError() << endl;
		exit(1);
	}

	if ((SDL_QueryTexture(texture, NULL, NULL, &width, &height)) != 0) {
		std::cout << "Erro: " << SDL_GetError() << std::endl;
	}

	width = width / columns;
	height = height / rows;

	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;

}

void Sprite::Render(int x, int y, float angle) {
	SDL_Rect auxrect;
	auxrect.x = x;
	auxrect.y = y;
	auxrect.w = clipRect.w * scaleX;
	auxrect.h = clipRect.h * scaleY;
	if (flipH)
		SDL_RenderCopyEx((Game::GetInstance().GetRenderer()), texture,
				&clipRect, &auxrect, angle, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopyEx((Game::GetInstance().GetRenderer()), texture,
				&clipRect, &auxrect, angle, NULL, SDL_FLIP_NONE);
}

int Sprite::GetHeight() {
	return height * scaleY;
}

int Sprite::GetWidth() {
	return width * scaleX;
}

bool Sprite::IsOpen() {
	if (texture == NULL) {
		return false;
	}
	return true;
}

void Sprite::SetScaleX(float scale) {
	scaleX = scale;

}

void Sprite::SetScaleY(float scale) {
	scaleY = scale;

}

void Sprite::Update(float dt) {
	timeElapsed += dt;

	if (timeElapsed >= frameTime) {
		currentFrame++;

		if (currentFrame < loopStart)
			currentFrame = loopStart;

		timeElapsed = 0;
		if (currentFrame > loopEnd) {
			currentFrame = loopStart;
			timeElapsed = 0;
		}
		int x = currentFrame;
		while (x > (columns - 1))
			x -= columns;
		int y = floor(currentFrame / columns);
		SetClip(x * width, y * height, width, height);
	}
}

void Sprite::SetFrame(int frame) {
	currentFrame = frame;
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;
}

int Sprite::GetFrameWidth() {
	return width * scaleX;
}

void Sprite::SetFlipH(bool flipH) {
	this->flipH = flipH;
}

void Sprite::SetLoop(int start, int end) {
	loopStart = start;
	loopEnd = end;
}

int Sprite::GetCurrentFrame() {
	return currentFrame;
}
