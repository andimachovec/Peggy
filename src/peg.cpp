#include "peg.h"
#include <cmath>


Peg::Peg(BView *target, BPoint center, float radius, uint8 color_index)
	:
	fTarget(target),
	fCenter(center),
	fRadius(radius),
	fColorIndex(color_index)
{

	//	initialize peg colors
	fColors[0].set_to(54, 34, 4);	// board_color (pseudo transparent)

	// for the result pegs
	fColors[1].set_to(0,0,0);		// black
	fColors[2].set_to(255,255,255);	// white

	// for the color pegs
	fColors[3].set_to(255,0,0); 	// red
	fColors[4].set_to(0,255,0);		// green
	fColors[5].set_to(0,0,255);		// blue
	fColors[6].set_to(255,255,0);	// yellow
	fColors[7].set_to(255,0,255);	// magenta
	fColors[8].set_to(255,179,71);	// orange

	//create bitmap for drag and drop
	fBitmap = new BBitmap(BRect(0,0,40,40), B_RGBA32, true);
	create_bitmap();

}


void
Peg::Draw()
{

	draw_peg(fTarget, fCenter);

}


void
Peg::SetCenter(BPoint center)
{

	fCenter = center;
	create_bitmap();

}


void
Peg::SetColorIndex(uint8 color_index)
{

	fColorIndex = color_index;
	create_bitmap();

}


uint8
Peg::GetColorIndex()
{

	return fColorIndex;

}




bool
Peg::Contains(BPoint point)
{

	float delta_x = fCenter.x - point.x;
	float delta_y = fCenter.y - point.y;

	if (delta_x < 0)
	{
		delta_x = delta_x*-1;
	}

	if (delta_y < 0)
	{
		delta_y = delta_y*-1;
	}

	float distance = sqrt(pow(delta_x,2)+pow(delta_y,2));

	if (distance <= fRadius)
	{
		return true;
	}
	else
	{
		return false;
	}

}


BBitmap*
Peg::GetBitmap()
{

	return fBitmap;

}


void
Peg::create_bitmap()
{

	BView *bitmap_view = new BView(BRect(0,0,40,40),"bitmapview", B_FOLLOW_NONE,B_WILL_DRAW);
	fBitmap->AddChild(bitmap_view);
	bitmap_view->LockLooper();
	bitmap_view->SetLowColor(0,0,0,0);
	bitmap_view->FillRect(bitmap_view->Bounds(), B_SOLID_LOW);
	draw_peg(bitmap_view, BPoint(20,20));
	bitmap_view->Sync();
	bitmap_view->UnlockLooper();
	fBitmap->RemoveChild(bitmap_view);
	delete bitmap_view;

}


void
Peg::draw_peg(BView *drawing_view, BPoint center)
{

	rgb_color temp_color = drawing_view->HighColor();
	drawing_view->SetHighColor(fColors[fColorIndex]);
	drawing_view->FillEllipse(center, fRadius, fRadius, B_SOLID_HIGH);
	drawing_view->SetHighColor(temp_color);

}

