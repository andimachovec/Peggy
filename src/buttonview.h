#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H


#include <View.h>

class BButton;

enum
{
	BV_SUBMITBUTTON_CLICKED ='bv00',
};


class ButtonView : public BView {
public:
	ButtonView();
	void EnableButton();
	void DisableButton();

private:
	BButton *fSubmitRowButton;

};


#endif
