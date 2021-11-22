#include "buttonview.h"

#include <Button.h>
#include <Catalog.h>
#include <LayoutBuilder.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "MessageView"


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


