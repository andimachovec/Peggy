#include "boardview.h"
#include "pegselectview.h"
#include <iostream>


BoardRow::BoardRow(BView *target_view)
{

	//initialize pegs
	rgb_color init_color;
	init_color.set_to(54, 34, 4);

	for(int i = 0; i < 4 ; ++i)
	{
		fColorPegs[i] = new Peg(target_view, BPoint(), 20, init_color);
		fResultPegs[i] = new Peg(target_view, BPoint(), 5, init_color);
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

	//initialize rows
	for(int i = 0; i < 9 ; ++i)
	{
		fRows[i] = new BoardRow(this);
	}

	fActiveRow = 0;

	//initialize peg colors
	fPegColors[0].set_to(255,0,0);
	fPegColors[1].set_to(0,255,0);
	fPegColors[2].set_to(0,0,255);
	fPegColors[3].set_to(255,255,0);
	fPegColors[4].set_to(255,0,255);
	fPegColors[5].set_to(255,179,71);

}


BoardView::~BoardView()
{
	for(int i = 0; i < 9 ; ++i)
	{
		delete fRows[i];
	}
}


void
BoardView::MessageReceived(BMessage *msg)
{

	switch(msg->what)
	{
		case PV_DRAG_PEG:
		{
			//get color and drop point
			uint8 color_code;
			msg->FindUInt8("color", &color_code);
			BPoint drop_point;
			msg->FindPoint("_drop_point_", &drop_point);
			drop_point = ConvertFromScreen(drop_point);  //drop point comes in screen coordinates

			//check in which hole the peg was dropped
			uint8 row_nr, hole_nr;
			if (over_hole(drop_point, row_nr, hole_nr))
			{
				if (row_nr == fActiveRow) //only continue if peg was dropped in the currently played row
				{
					fRows[row_nr]->GetColorPeg(hole_nr)->SetColor(fPegColors[color_code]);
					Invalidate();
				}
			}


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

	SetLowColor(101,67,33);
	FillRect(updateRect, B_SOLID_LOW);

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


	//debug output:
	//std::cout << "View Height" << Bounds().Height() << std::endl;
	//std::cout << "View Width" << Bounds().Width() << std::endl;
	//std::cout << "delta Y: " << delta_y << std::endl << std::endl;

	for(int row = 0; row < 9 ; ++row)
	{
		//std::cout << "Row " << row << std::endl;
		peg_center.x = delta_x+fColorPegRadius;

		//calculate result peg positions
		float distance = fResultPegRadius*2;
		fRows[row]->GetResultPeg(0)->SetCenter(
			BPoint(peg_center.x+distance, peg_center.y-distance));
		fRows[row]->GetResultPeg(1)->SetCenter(
			BPoint(peg_center.x-distance, peg_center.y-distance));
		fRows[row]->GetResultPeg(2)->SetCenter(
			BPoint(peg_center.x-distance, peg_center.y+distance));
		fRows[row]->GetResultPeg(3)->SetCenter(
			BPoint(peg_center.x+distance, peg_center.y+distance));

		//calculate color peg positions
		peg_center.x+=delta_x+2*fColorPegRadius;

		for(int peg_nr = 0; peg_nr < 4; ++peg_nr)
		{
			//std::cout << "\t" <<"Peg " << peg_nr << ": X: " << peg_center.x << " Y: " <<
			//	peg_center.y << std::endl;

			fRows[row]->GetColorPeg(peg_nr)->SetCenter(peg_center);
			peg_center.x+=delta_x+2*fColorPegRadius;
		}

		peg_center.y=peg_center.y-delta_y-2*fColorPegRadius;
	}

	//only for color contrast testing -> remove when colors are OK
	fRows[3]->GetResultPeg(1)->SetColor(0,0,0);
	fRows[3]->GetResultPeg(2)->SetColor(255,255,255);

}


void
BoardView::SetActiveRow(uint8 row_nr)
{

	fActiveRow = row_nr;

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





