/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "pegselectview.h"
#include "peg.h"


PegSelectView::PegSelectView()
	:
	BView("pegselectview", B_SUPPORTS_LAYOUT|B_WILL_DRAW|B_FULL_UPDATE_ON_RESIZE)
{

	//initialize pegs
	fPegRadius = 20;

	for(int i = 0; i < 6; ++i)
	{
		fPegs[i] = new Peg(this, BPoint(), fPegRadius, i+3); //actual colors start at index 3
	}

	fMouseDown = false;

}


void
PegSelectView::MessageReceived(BMessage *msg)
{

	switch (msg->what)
	{
		case PV_DRAG_PEG:  	// do nothing, just prevent an error message for unhandled BMessages
			break;			// to appear on stderr

		default:
			BView::MessageReceived(msg);
			break;
	}

}


void
PegSelectView::Draw(BRect updateRect)
{

	SetLowColor(110, 62, 28);
	FillRect(updateRect, B_SOLID_LOW);

	for(int i = 0; i < 6; ++i)
	{
		fPegs[i]->Draw();
	}

}


void
PegSelectView::LayoutChanged()
{

	float delta_y = (Bounds().Height() - 12*fPegRadius) / 7;

	BPoint peg_center;
	peg_center.x = Bounds().Width() / 2;
	peg_center.y = delta_y+fPegRadius;

	for(int i = 0; i < 6; ++i)
	{
		fPegs[i]->SetCenter(peg_center);
		peg_center.y += delta_y+2*fPegRadius;
	}

}


void
PegSelectView::MouseDown(BPoint point)
{

	BPoint location;
	uint32 buttons;
	GetMouse(&location, &buttons);

	if (buttons == B_PRIMARY_MOUSE_BUTTON)
	{
		int peg_nr;

		if (over_peg(point, peg_nr))
		{
			SetMouseEventMask(B_FULL_POINTER_HISTORY);
			fMouseDown = true;
			fDraggedPegNr = peg_nr;
		}
	}

}


void
PegSelectView::MouseUp(BPoint point)
{

	fMouseDown = false;
	SetMouseEventMask(B_NO_POINTER_HISTORY);

}


void
PegSelectView::MouseMoved(BPoint point, uint32 transit, const BMessage* message)
{

	if ((transit == B_EXITED_VIEW) and fMouseDown)
	{
		fMouseDown = false;
		SetMouseEventMask(B_NO_POINTER_HISTORY);

		BMessage drag_message(PV_DRAG_PEG);
		drag_message.AddUInt8("color_index", fPegs[fDraggedPegNr]->GetColorIndex());
		BBitmap *drag_bitmap = new BBitmap(fPegs[fDraggedPegNr]->GetBitmap()); //copy the bitmap from the peg
		DragMessage(&drag_message, drag_bitmap, BPoint(20,20));				   //because it is deleted by the d&d system
	}


}


bool
PegSelectView::over_peg(BPoint point, int &peg_nr)
{

	for(peg_nr = 0; peg_nr < 6; ++peg_nr)
	{
		if (fPegs[peg_nr]->Contains(point))
		{
			return true;
		}
	}

	return false;
}


