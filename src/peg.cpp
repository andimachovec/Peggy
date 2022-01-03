/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "peg.h"

#include <cmath>


Peg::Peg()
	:
	fTarget(nullptr),
	fCenter(BPoint(0,0)),
	fRadius(0),
	fColorIndex(0)
{

	init_colors();
	fBitmap = new BBitmap(BRect(0,0,40,40), B_RGBA32, true);

}


Peg::Peg(BView *target, BPoint center, float radius, uint8 color_index)
	:
	fTarget(target),
	fCenter(center),
	fRadius(radius),
	fColorIndex(color_index)
{

	init_colors();

	//create bitmap for drag and drop
	fBitmap = new BBitmap(BRect(0,0,40,40), B_RGBA32, true);
	create_bitmap();

}


Peg::~Peg()
{

	delete fBitmap;

}

void
Peg::Draw()
{

	draw_peg(fTarget, fCenter);

}


void
Peg::SetTarget(BView *target)
{

	fTarget = target;

}

void
Peg::SetCenter(BPoint center)
{

	fCenter = center;
	create_bitmap();

}


void
Peg::SetRadius(float radius)
{

	fRadius = radius;
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


BPoint
Peg::GetCenter()
{

	return fCenter;

}

void
Peg::create_bitmap()
{

	BView *bitmap_view = new BView(BRect(0,0,40,40),"bitmapview", B_FOLLOW_NONE,B_WILL_DRAW);
	fBitmap->AddChild(bitmap_view);
	bitmap_view->LockLooper();
	bitmap_view->SetLowColor(0,0,0,0);	// Transparency for round pegs
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


void
Peg::init_colors()
{

	fColors[0].set_to(71, 45, 6);	// board_color (pseudo transparent)

	// for the result pegs
	fColors[1].set_to(5,5,5);	// black
	fColors[2].set_to(244,244,244);	// white

	// for the color pegs
	fColors[3].set_to(255,35,6); 	// red
	fColors[4].set_to(67,174,57);	// green
	fColors[5].set_to(51,102,172);	// blue
	fColors[6].set_to(255,211,0);	// yellow
	fColors[7].set_to(214,43,245);	// magenta
	fColors[8].set_to(255,118,0);	// orange

}






