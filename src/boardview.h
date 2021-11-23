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
	void Draw(BRect updateRect);
	void LayoutChanged();

private:
	std::array<BoardRow*, 9> fRows;
	float fColorPegRadius;

};


#endif
