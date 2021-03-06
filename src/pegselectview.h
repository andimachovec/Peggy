/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef PEGSELECTVIEW_H
#define PEGSELECTVIEW_H


#include <View.h>

#include <array>

#include "peg.h"


enum {
	PV_DRAG_PEG = 'pv00',
};


class PegSelectView : public BView {
public:
	PegSelectView();
	void Draw(BRect updateRect);
	void MessageReceived(BMessage *msg);
	void LayoutChanged();
	void MouseDown(BPoint point);
	void MouseUp(BPoint point);
	void MouseMoved(BPoint point, uint32 transit, const BMessage* message);


private:
	bool over_peg(BPoint point, int &peg_nr);

	std::array<Peg*, 6> fPegs;
	float fPegRadius;
	bool fMouseDown;
	uint8 fDraggedPegNr;

};


#endif
