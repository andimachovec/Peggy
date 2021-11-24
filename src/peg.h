#ifndef PEG_H
#define PEG_H


#include <View.h>


class Peg {
public:
	Peg(BView *target, BPoint center, float radius, rgb_color color);
	void Draw();
	void SetCenter(BPoint center);
	void SetColor(rgb_color color);
	void SetColor(uint8 red, uint8 green, uint8 blue, uint8 alpha=255);

private:
	BView *fTarget;
	BPoint fCenter;
	float fRadius;
	rgb_color fColor;
};


#endif
