#include "peg.h"
#include <cmath>


Peg::Peg(BView *target, BPoint center, float radius, rgb_color color)
	:
	fTarget(target),
	fCenter(center),
	fRadius(radius),
	fColor(color)
{

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
Peg::SetColor(rgb_color color)
{

	fColor = color;
	create_bitmap();

}


void
Peg::SetColor(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{

	fColor.set_to(red, green, blue, alpha);
	create_bitmap();

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
	drawing_view->SetHighColor(fColor);
	drawing_view->FillEllipse(center, fRadius, fRadius, B_SOLID_HIGH);
	drawing_view->SetHighColor(temp_color);

}

