#include "pegselectview.h"
#include <iostream>

PegSelectView::PegSelectView()
	:
	BView("pegselectview", B_SUPPORTS_LAYOUT|B_WILL_DRAW)
{

	fPegColors[0].set_to(255,0,0);
	fPegColors[1].set_to(0,255,0);
	fPegColors[2].set_to(0,0,255);
	fPegColors[3].set_to(255,255,0);
	fPegColors[4].set_to(255,0,255);
	fPegColors[5].set_to(255,179,71);

}


void
PegSelectView::Draw(BRect updateRect)
{
	float peg_radius = 20;
	float delta_y = (Bounds().Height() - 12*peg_radius) / 7;

	BPoint peg_center;
	peg_center.x = Bounds().Width() / 2;
	peg_center.y = delta_y+peg_radius;

	for(int i = 0; i < 6; ++i)
	{
		SetHighColor(fPegColors[i]);
		FillEllipse(peg_center, peg_radius, peg_radius, B_SOLID_HIGH);

		peg_center.y += delta_y+2*peg_radius;
	}

}
