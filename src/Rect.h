/******************************************
 * File: Rect.h
 * Purpose: this class represents a
 * geometric objects (rectangle)
 *****************************************/
#ifndef SRC_RECT_H_
#define SRC_RECT_H_

#include "Point.h"

class Rect {
public:
	float x; // point on the x-axis
	float y; // point on the y-axis 
	float w; // point on the w-axis (depth)
	float h; // height point

	Rect();
	Rect(float aux_x, float aux_y, float aux_w, float aux_h);
	void setX(float aux_x);
	void setY(float aux_y);
	void setW(float aux_w);
	void setH(float aux_h);
	float getX();
	float getY();
	float getW();
	float getH();
	float getCenterX();
	float getCenterY();
	void somaPonto(Point ponto);
	Point pegaCentro() const;
	float pegaDistFromCenter(Rect rect);
	bool isPontoInside(Point ponto);
};

#endif /* SRC_RECT_H_ */
