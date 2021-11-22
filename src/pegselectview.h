#ifndef PEGSELECTVIEW_H
#define PEGSELECTVIEW_H


#include <View.h>
#include <array>


class PegSelectView : public BView {
public:
	PegSelectView();
	void Draw(BRect updateRect);

private:
	std::array<rgb_color, 6> fPegColors;
};

#endif
