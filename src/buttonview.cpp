/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "buttonview.h"

#include <Button.h>
#include <Catalog.h>
#include <LayoutBuilder.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "ButtonView"


ButtonView::ButtonView()
	:
	BView("buttonview", B_SUPPORTS_LAYOUT)
{

	fSubmitRowButton = new BButton(	B_TRANSLATE("Complete Row"),
									new BMessage(BV_SUBMITBUTTON_CLICKED));
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

