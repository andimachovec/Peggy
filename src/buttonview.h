/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef BUTTONVIEW_H
#define BUTTONVIEW_H


#include <View.h>

class BButton;

enum
{
	BT_SUBMITBUTTON_CLICKED ='bt00',
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
