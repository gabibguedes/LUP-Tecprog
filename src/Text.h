#ifndef SRC_TEXT_H_
#define SRC_TEXT_H_

#include <iostream>
#include "SDL_ttf.h"
#include "Rect.h"

class Text {
public:
	enum TextStyle {
		SOLID, SHADED, BLENDED
	};
	Text(std::string fontFile, int fontSize, TextStyle style, std::string text,
			SDL_Color color, int x = 0, int y = 0);
	~Text();
	void Render(int cameraX = 0, int cameraY = 0);
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);
	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);
	float GetXCenter() {
		return box.x * 2 + box.getW();
	}

	float GetYCenter() {
		return box.y * 2 + box.getH();
	}

	float GetX() {
		return box.x;
	}

	float GetY() {
		return box.y;
	}

	float GetWidth() {
		return box.w;
	}
private:
	void RemakeTexture();
	TTF_Font* font;
	SDL_Texture* texture;
	std::string text;
	TextStyle style;
	int fontSize;
	SDL_Color color;
	Rect box;
};

#endif /* SRC_TEXT_H_ */
