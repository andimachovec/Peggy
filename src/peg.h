#ifndef PEG_H
#define PEG_H


#include <View.h>
#include <Bitmap.h>
#include <array>


class Peg {
public:
	Peg(BView *target, BPoint center, float radius, uint8 color_index);
	void Draw();
	void SetCenter(BPoint center);
	void SetColorIndex(uint8 color_index);
	uint8 GetColorIndex();
	bool Contains(BPoint point);
	BBitmap* GetBitmap();

private:
	void create_bitmap();
	void draw_peg(BView *drawing_view, BPoint center);

	BView *fTarget;
	BPoint fCenter;
	float fRadius;
	std::array<rgb_color, 9> fColors;
	uint8 fColorIndex;
	BBitmap *fBitmap;

};


#endif
