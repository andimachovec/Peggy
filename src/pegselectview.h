#ifndef PEGSELECTVIEW_H
#define PEGSELECTVIEW_H


#include <View.h>
#include <array>
#include "peg.h"


class PegSelectView : public BView {
public:
	PegSelectView();
	void Draw(BRect updateRect);
	void LayoutChanged();
	void MouseDown(BPoint point);
	void MouseUp(BPoint point);
	void MouseMoved(BPoint point, uint32 transit, const BMessage* message);


private:
	bool over_peg(BPoint point, int &peg_nr);

	std::array<Peg*, 6> fPegs;
	std::array<rgb_color, 6> fPegColors;
	float fPegRadius;
	bool fMouseDown;

};


#endif
