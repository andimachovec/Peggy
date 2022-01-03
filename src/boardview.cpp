/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "boardview.h"
#include "pegselectview.h"

#include <Window.h>
#include <Alert.h>
#include <Catalog.h>

#include <cstdlib>
#include <ctime>
#include <chrono>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "BoardView"


BoardRow::BoardRow(BView *target_view)
{

	//initialize pegs
	for(int i = 0; i < 4 ; ++i)
	{
		fColorPegs[i] = new Peg(target_view, BPoint(), 20, 0);
		fResultPegs[i] = new Peg(target_view, BPoint(), 5, 0);
	}

}


BoardRow::~BoardRow()
{

	for(int i = 0; i < 4 ; ++i)
	{
		delete fColorPegs[i];
		delete fResultPegs[i];
	}

}


Peg*
BoardRow::GetColorPeg(int peg_nr)
{

	return fColorPegs[peg_nr];

}


Peg*
BoardRow::GetResultPeg(int peg_nr)
{

	return fResultPegs[peg_nr];

}


BoardView::BoardView()
	:
	BView("boardview", B_SUPPORTS_LAYOUT|B_WILL_DRAW|B_FULL_UPDATE_ON_RESIZE)
{

	fColorPegRadius = 20;
	fResultPegRadius = 5;

	for(int i = 0; i < 9 ; ++i)
	{
		fRows[i] = new BoardRow(this);
	}

	for(int i = 0; i < 4; ++i)
	{
		fCombiPegs[i] = new Peg(this, BPoint(), 20, 0);
	}

	fActiveRow = 0;
	fMouseDown = false;
	fGameOver = false;

	init_combination();

}


BoardView::~BoardView()
{

	for(int i = 0; i < 9 ; ++i)
	{
		delete fRows[i];
	}

	for(int i = 0; i < 4; ++i)
	{
		delete fCombiPegs[i];
	}

}


void
BoardView::MessageReceived(BMessage *msg)
{

	switch(msg->what)
	{
		case PV_DRAG_PEG:	// color peg is dropped from the selection view
		{
			if (!fGameOver)
			{
				// get color and drop point
				uint8 color_index;
				msg->FindUInt8("color_index", &color_index);
				BPoint drop_point;
				msg->FindPoint("_drop_point_", &drop_point);
				drop_point = ConvertFromScreen(drop_point);  // drop point comes in screen coordinates

				// check in which hole the peg was dropped
				uint8 row_nr, hole_nr;
				if (over_hole(drop_point, row_nr, hole_nr))
				{
					if (row_nr == fActiveRow) // only continue if peg was dropped in the currently played row
					{
						fRows[row_nr]->GetColorPeg(hole_nr)->SetColorIndex(color_index);
						Invalidate();
						check_row();
					}
				}
			}

			break;
		}

		case BV_DRAG_PEG:	// color peg is dropped from board view itself
		{
			BPoint drop_point;
			msg->FindPoint("_drop_point_", &drop_point);
			drop_point = ConvertFromScreen(drop_point);  // drop point comes in screen coordinates
			uint8 color_index, drag_position;
			msg->FindUInt8("color_index", &color_index);
			msg->FindUInt8("drag_position", &drag_position);

			// check whether or not the peg was dropped on a valid position
			uint8 row_nr, hole_nr;
			if (over_hole(drop_point, row_nr, hole_nr))
			{
				// only continue if peg was dropped in the currently played row
				if (row_nr == fActiveRow)
				{
					//if position is already occupied, swap the peg colors
					if (fRows[fActiveRow]->GetColorPeg(hole_nr)->GetColorIndex() != 0)
					{
						uint8 swap_color_index = fRows[fActiveRow]->GetColorPeg(hole_nr)->GetColorIndex();
						fRows[fActiveRow]->GetColorPeg(drag_position)->SetColorIndex(swap_color_index);
					}

					fRows[fActiveRow]->GetColorPeg(hole_nr)->SetColorIndex(color_index);
				}
				else
				{
					fRows[fActiveRow]->GetColorPeg(drag_position)->SetColorIndex(color_index);
				}
			}
			else  // if dropped on invalid position, reset color on original position
			{
				fRows[fActiveRow]->GetColorPeg(drag_position)->SetColorIndex(color_index);
			}

			Invalidate();
			check_row();
			break;
		}

		default:
			BView::MessageReceived(msg);
			break;
	}

}


void
BoardView::Draw(BRect updateRect)
{
	// background
	SetLowColor(149, 94, 13);
	FillRect(updateRect, B_SOLID_LOW);

	// active row marker
	if (!fGameOver)
	{
		BRect marker_rect;
		BPoint left_point = fRows[fActiveRow]->GetColorPeg(0)->GetCenter();
		BPoint right_point = fRows[fActiveRow]->GetColorPeg(3)->GetCenter();
		uint8 marker_margin = 5;

		marker_rect.top = left_point.y - fColorPegRadius - marker_margin;
		marker_rect.left = left_point.x - fColorPegRadius - marker_margin;
		marker_rect.bottom = left_point.y + fColorPegRadius + marker_margin;
		marker_rect.right = right_point.x + fColorPegRadius + marker_margin;

		rgb_color activeColor = { 192, 115, 16 };
		SetHighColor(activeColor);
		FillRoundRect(marker_rect, 5, 5, B_SOLID_HIGH);
		SetHighColor(tint_color(activeColor, B_LIGHTEN_2_TINT));
		StrokeRoundRect(marker_rect, 5, 5, B_SOLID_HIGH);

	}

	// pegs
	for(int row = 0; row < 9; ++row)
	{
		for(int peg_nr = 0; peg_nr < 4; ++peg_nr)
		{
			fRows[row]->GetColorPeg(peg_nr)->Draw();
			fRows[row]->GetResultPeg(peg_nr)->Draw();
		}
	}
}


void
BoardView::LayoutChanged()
{

	float delta_x = (Bounds().Width() - 10*fColorPegRadius) / 6;
	float delta_y = (Bounds().Height() - 18*fColorPegRadius) / 10;

	BPoint peg_center;
	peg_center.y = Bounds().Height()-delta_y-fColorPegRadius;

	for(int row = 0; row < 9 ; ++row)
	{
		peg_center.x = delta_x+fColorPegRadius;

		//calculate result peg positions
		float distance = fResultPegRadius*2;
		fRows[row]->GetResultPeg(0)->SetCenter(
			BPoint(peg_center.x-distance, peg_center.y-distance));
		fRows[row]->GetResultPeg(1)->SetCenter(
			BPoint(peg_center.x+distance, peg_center.y-distance));
		fRows[row]->GetResultPeg(2)->SetCenter(
			BPoint(peg_center.x-distance, peg_center.y+distance));
		fRows[row]->GetResultPeg(3)->SetCenter(
			BPoint(peg_center.x+distance, peg_center.y+distance));

		//calculate color peg positions
		peg_center.x+=delta_x+2*fColorPegRadius;

		for(int peg_nr = 0; peg_nr < 4; ++peg_nr)
		{
			fRows[row]->GetColorPeg(peg_nr)->SetCenter(peg_center);
			peg_center.x+=delta_x+2*fColorPegRadius;
		}

		peg_center.y=peg_center.y-delta_y-2*fColorPegRadius;
	}

}


void
BoardView::MouseDown(BPoint point)
{

	BPoint location;
	uint32 buttons;

	GetMouse(&location, &buttons);

	//check if right mouse button was clicked over a peg in the active row -> used for removing pegs
	if (!fGameOver)
	{
		if (buttons == B_SECONDARY_MOUSE_BUTTON)
		{
			uint8 row_nr, hole_nr;

			if (over_hole(point, row_nr, hole_nr))
			{
				if (row_nr == fActiveRow) //only continue if in the currently active row
				{
					fRows[row_nr]->GetColorPeg(hole_nr)->SetColorIndex(0); 	//set peg color to board color,
					Invalidate();											//visually removing the peg
					check_row();
				}
			}
		}

		else if (buttons == B_PRIMARY_MOUSE_BUTTON)
		{

			uint8 row_nr, hole_nr;

			if (over_hole(point, row_nr, hole_nr))
			{
				//only continue if in the currently active row and the hole isn´t empty
				if ((row_nr == fActiveRow)and (fRows[fActiveRow]->GetColorPeg(hole_nr)->GetColorIndex() != 0))
				{
					SetMouseEventMask(B_FULL_POINTER_HISTORY);
					fMouseDown = true;
					fDraggedPegNr = hole_nr;
				}
			}
		}
	}
}


void
BoardView::MouseUp(BPoint point)
{

	fMouseDown = false;
	SetMouseEventMask(B_NO_POINTER_HISTORY);

}


void
BoardView::MouseMoved(BPoint point, uint32 transit, const BMessage* message)
{

	if ((transit == B_INSIDE_VIEW) and fMouseDown and !fGameOver)
	{
		fMouseDown = false;
		SetMouseEventMask(B_NO_POINTER_HISTORY);

		BMessage drag_message(BV_DRAG_PEG);
		drag_message.AddUInt8("color_index", fRows[fActiveRow]->GetColorPeg(fDraggedPegNr)->GetColorIndex());
		drag_message.AddUInt8("drag_position", fDraggedPegNr);
		BBitmap *drag_bitmap = new BBitmap(fRows[fActiveRow]	//copy the bitmap from the peg
				->GetColorPeg(fDraggedPegNr)->GetBitmap()); 	//because it is deleted by the d&d system
		fRows[fActiveRow]->GetColorPeg(fDraggedPegNr)->SetColorIndex(0);
		Invalidate();
		DragMessage(&drag_message, drag_bitmap, BPoint(20,20));
		check_row();
	}

}


void
BoardView::SetActiveRow(uint8 row_nr)
{

	fActiveRow = row_nr;

}


void
BoardView::EvaluateActiveRow()
{

	uint8 black = 0;
	uint8 white = 0;

	combination_t chk_combination;  // the combination to be guessed
	combination_t chk_guess;		// current guess

	//Fill the work arrays with the values from the game
	for (int i=0; i<4; ++i)
	{
		chk_combination[i]=fCombination[i];
		chk_guess[i]=fRows[fActiveRow]->GetColorPeg(i)->GetColorIndex();
	}

	// check for black pegs and mark the places with -1
	for (int counter1=0; counter1<4; ++counter1)
	{
		if (chk_guess[counter1] == chk_combination[counter1] )
		{
			++black;
			chk_guess[counter1]=-1;
			chk_combination[counter1]=-1;
		}
	}

	//check for white pegs
	for (int counter1=0; counter1<4; ++counter1)
	{
		if (chk_guess[counter1] != -1)
		{
			for (int counter2=0; counter2<4; ++counter2)
			{
				if (chk_guess[counter1] == chk_combination[counter2])
				{
					++white;
					chk_combination[counter2]=-1;
					counter2=4;
				}
			}
		}
	}

	// set result pegs
	for (uint8 result_pos = 0; result_pos < black; ++result_pos)
	{
		fRows[fActiveRow]->GetResultPeg(result_pos)->SetColorIndex(1);
	}

	for (uint8 result_pos = black; result_pos < black+white; ++result_pos)
	{
		fRows[fActiveRow]->GetResultPeg(result_pos)->SetColorIndex(2);
	}

	Invalidate();
	Window()->PostMessage(new BMessage(BV_ROW_INCOMPLETE));

	// if not guessed right and not at the last row, continue to next row
	if ((black < 4) and (fActiveRow < 8))
	{
		++fActiveRow;
	}

	// guess is right
	else if (black == 4)
	{
		fGameOver = true;
		BAlert *alert = new BAlert("",
							B_TRANSLATE("Congratulations! You've cracked the combination"),
							B_TRANSLATE("Close"));
		alert->Go();
	}

	// guess isn´t right and we´re already at the last row
	else if ((black < 4) and (fActiveRow == 8))
	{
		fGameOver = true;

		BAlert *alert = new BAlert("",
							B_TRANSLATE("Oops! You missed your last chance to guess the combination"),
							B_TRANSLATE("Close"));

		alert->SetIcon(get_combination_bitmap());
		alert->Go();
	}

}


void
BoardView::Reset()
{

	//clear out all pegs
	for (int row = 0; row < 9; ++row)
	{
		for (int pos = 0; pos < 4; ++pos)
		{
			fRows[row]->GetColorPeg(pos)->SetColorIndex(0);
			fRows[row]->GetResultPeg(pos)->SetColorIndex(0);
		}
	}

	Invalidate();

	init_combination();
	fActiveRow = 0;
	fGameOver = false;
}


bool
BoardView::GameRunning()
{

	return !fGameOver;

}


bool
BoardView::over_hole(BPoint point, uint8 &row_nr, uint8 &hole_nr)
{

	for (row_nr = 0; row_nr < 9; ++row_nr)
	{
		for (hole_nr = 0; hole_nr < 4; ++hole_nr)
		{
			if (fRows[row_nr]->GetColorPeg(hole_nr)->Contains(point))
			{
				return true;
			}
		}
	}

	return false;
}


bool
BoardView::row_complete()
{

	for (uint8 i = 0; i < 4; ++i)
	{
		if (fRows[fActiveRow]->GetColorPeg(i)->GetColorIndex() == 0)
		{
			return false;
		}
	}

	return true;

}


void
BoardView::check_row()
{

	if (row_complete())
	{
		Window()->PostMessage(new BMessage(BV_ROW_COMPLETE));
	}
	else
	{
		Window()->PostMessage(new BMessage(BV_ROW_INCOMPLETE));
	}

}


void
BoardView::init_combination()
{

	int counter;
	srand(time(NULL));

	for (counter=0; counter<=3; counter++)
	{
		fCombination[counter]=(rand() % 6)+3;
	}

}


BBitmap*
BoardView::get_combination_bitmap()
{

	// create bitmap, view and pegs
	BRect combi_bitmap_dimensions(0, 0, fColorPegRadius*8+25, fColorPegRadius*2+5);
	BBitmap *combi_bitmap = new BBitmap(combi_bitmap_dimensions, B_RGBA32, true);
	BView	*combi_bitmap_view = new BView(	combi_bitmap_dimensions,
											"combibitmapview",
											B_FOLLOW_NONE,B_WILL_DRAW);

	combi_bitmap->AddChild(combi_bitmap_view);

	BPoint peg_center;
	peg_center.x=5+fColorPegRadius;
	peg_center.y=combi_bitmap_dimensions.Height()/2;

	for (int i = 0; i < 4; ++i)
	{
		fCombiPegs[i]->SetTarget(combi_bitmap_view);
		fCombiPegs[i]->SetCenter(peg_center);
		fCombiPegs[i]->SetColorIndex(fCombination[i]);

		peg_center.x+=5+fColorPegRadius*2;
	}

	// draw pegs
	combi_bitmap_view->LockLooper();
	combi_bitmap_view->SetLowColor(0,0,0,0); //transparent
	combi_bitmap_view->FillRect(combi_bitmap_dimensions, B_SOLID_LOW);

	for (int i = 0; i < 4; ++i)
	{
		fCombiPegs[i]->Draw();
	}

	combi_bitmap_view->Sync();
	combi_bitmap_view->UnlockLooper();

	// cleanup
	combi_bitmap->RemoveChild(combi_bitmap_view);
	delete combi_bitmap_view;

	return combi_bitmap;

}

