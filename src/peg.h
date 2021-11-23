#ifndef PEG_H
#define PEG_H


#include <View.h>


class Peg {
public:
	Peg(BView *target, BPoint center, float radius, rgb_color color);
	void Draw();
	void SetCenter(BPoint center);

private:
	BView *fTarget;
	BPoint fCenter;
	float fRadius;
	rgb_color fColor;
};


#endif
