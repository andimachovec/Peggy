#ifndef BOARDVIEW_H
#define BOARDVIEW_H


#include <View.h>
#include <array>
#include "peg.h"


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
	void SetActiveRow(uint8 row_nr);

private:
	bool over_hole(BPoint point, uint8 &row_nr, uint8 &hole_nr);

	std::array<BoardRow*, 9> fRows;
	std::array<rgb_color, 6> fPegColors;
	float 	fColorPegRadius;
	float 	fResultPegRadius;
	uint8	fActiveRow;

};


#endif
