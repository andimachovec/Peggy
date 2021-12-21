/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef BOARDVIEW_H
#define BOARDVIEW_H


#include <View.h>
#include <Bitmap.h>

#include <array>

#include "peg.h"


typedef std::array<int8, 4> combination_t;


enum {
	BV_DRAG_PEG = 'bv00',
	BV_ROW_COMPLETE,
	BV_ROW_INCOMPLETE,
};


class BoardRow {
public:
	BoardRow(BView *target_view);
	~BoardRow();
	Peg* GetColorPeg(int peg_nr);
	Peg* GetResultPeg(int peg_nr);

private:
	std::array<Peg*, 4> fColorPegs;
	std::array<Peg*, 4> fResultPegs;
};


class BoardView : public BView {
public:
	BoardView();
	~BoardView();
	void MessageReceived(BMessage *msg);
	void Draw(BRect updateRect);
	void LayoutChanged();
	void MouseDown(BPoint point);
	void MouseUp(BPoint point);
	void MouseMoved(BPoint point, uint32 transit, const BMessage* message);
	void SetActiveRow(uint8 row_nr);
	void EvaluateActiveRow();
	void Reset();
	bool GameRunning();

private:
	bool over_hole(BPoint point, uint8 &row_nr, uint8 &hole_nr);
	bool row_complete();
	void check_row();
	void init_combination();
	BBitmap* get_combination_bitmap();

	std::array<BoardRow*, 9> 	fRows;
	float 						fColorPegRadius;
	float 						fResultPegRadius;
	uint8						fActiveRow;
	bool 						fMouseDown;
	uint8 						fDraggedPegNr;
	combination_t				fCombination;
	bool						fGameOver;
	std::array<Peg*, 4>         fCombiPegs;

};


#endif
