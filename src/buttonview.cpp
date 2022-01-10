/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "buttonview.h"
#include "pegselectview.h"
#include "boardview.h"

#include <Button.h>
#include <Catalog.h>
#include <LayoutBuilder.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "ButtonView"


ButtonView::ButtonView()
	:
	BView("buttonview", B_SUPPORTS_LAYOUT)
{

	SetViewColor(110, 62, 28);

	fSubmitRowButton = new BButton(	B_TRANSLATE("Complete row"),
									new BMessage(BT_SUBMITBUTTON_CLICKED));
	fSubmitRowButton->SetEnabled(false);


	BLayoutBuilder::Group<>(this, B_HORIZONTAL, B_USE_SMALL_SPACING)
		.SetInsets(B_USE_SMALL_SPACING)
		.Add(fSubmitRowButton)
	.Layout();




}


void
ButtonView::EnableButton()
{

	fSubmitRowButton->SetEnabled(true);

}


void
ButtonView::DisableButton()
{

	fSubmitRowButton->SetEnabled(false);

}


void
ButtonView::MessageReceived(BMessage *msg)
{

	switch(msg->what)
	{
		case BV_DRAG_PEG:
		case PV_DRAG_PEG:
			break; 	// do nothing, we just wanna avoid errors on STDERR about unhandled messages
					// when a peg is dropped on this view


		default:
			BView::MessageReceived(msg);
			break;

	}

}

