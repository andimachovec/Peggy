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

private:
	std::array<Peg*, 6> fPegs;
	std::array<rgb_color, 6> fPegColors;
	float fPegRadius;
};


#endif
