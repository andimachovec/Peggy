#include "pegselectview.h"
#include "peg.h"
#include <iostream>


PegSelectView::PegSelectView()
	:
	BView("pegselectview", B_SUPPORTS_LAYOUT|B_WILL_DRAW|B_FULL_UPDATE_ON_RESIZE)
{

	//initialize peg colors
	fPegColors[0].set_to(255,0,0);
	fPegColors[1].set_to(0,255,0);
	fPegColors[2].set_to(0,0,255);
	fPegColors[3].set_to(255,255,0);
	fPegColors[4].set_to(255,0,255);
	fPegColors[5].set_to(255,179,71);

	//initialize pegs
	fPegRadius = 20;

	for(int i = 0; i < 6; ++i)
	{
		fPegs[i] = new Peg(this, BPoint(), fPegRadius, fPegColors[i]);
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
		drag_message.AddUInt8("color", fDraggedPegNr );
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


