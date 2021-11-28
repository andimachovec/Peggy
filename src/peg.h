#ifndef PEG_H
#define PEG_H


#include <View.h>
#include <Bitmap.h>


class Peg {
public:
	Peg(BView *target, BPoint center, float radius, rgb_color color);
	void Draw();
	void SetCenter(BPoint center);
	void SetColor(rgb_color color);
	void SetColor(uint8 red, uint8 green, uint8 blue, uint8 alpha=255);
	bool Contains(BPoint point);
	BBitmap* GetBitmap();

private:
	void create_bitmap();
	void draw_peg(BView *drawing_view, BPoint center);

	BView *fTarget;
	BPoint fCenter;
	float fRadius;
	rgb_color fColor;
	BBitmap *fBitmap;

};


#endif
