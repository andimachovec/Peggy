#include "peg.h"
#include <cmath>


Peg::Peg(BView *target, BPoint center, float radius, rgb_color color)
	:
	fTarget(target),
	fCenter(center),
	fRadius(radius),
	fColor(color)
{

}


void
Peg::Draw()
{
	rgb_color temp_color = fTarget->HighColor();
	fTarget->SetHighColor(fColor);
	fTarget->FillEllipse(fCenter, fRadius, fRadius, B_SOLID_HIGH);
	fTarget->SetHighColor(temp_color);

}


void
Peg::SetCenter(BPoint center)
{

	fCenter = center;

}


void
Peg::SetColor(rgb_color color)
{

	fColor = color;

}


void
Peg::SetColor(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{

	fColor.set_to(red, green, blue, alpha);

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






