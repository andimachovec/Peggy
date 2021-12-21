#include "timerview.h"

#include <Catalog.h>
#include <LayoutBuilder.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "TimerView"


TimerView::TimerView()
	:
	BView("timerview", B_WILL_DRAW|B_PULSE_NEEDED|B_SUPPORTS_LAYOUT)
{

	fRunning = false;
	fTextView = new BTextView("timertextview");
	fTextView->MakeEditable(false);
	fTextView->SetInsets(0, 0, 0, 0);

	BLayoutBuilder::Group<>(this, B_HORIZONTAL, B_USE_SMALL_SPACING)
		.SetInsets(B_USE_SMALL_SPACING)
		.Add(fTextView)
	.Layout();

}


void
TimerView::Pulse()
{
	if (fRunning)
	{
		if (fSeconds == 59)
		{
			fSeconds = 0;
			++fMinutes;
		}
		else
		{
			++fSeconds;
		}

	BString minutes_string;
	BString seconds_string;
	minutes_string.SetToFormat("%02d", fMinutes);
	seconds_string.SetToFormat("%02d", fSeconds);

	BString time_string;
	time_string << minutes_string << ":" << seconds_string;

	fTextView->SetText(time_string.String());

	}




}


void
TimerView::Draw(BRect updateRect)
{


}


void
TimerView::StartTimer()
{

	fMinutes = 0;
	fSeconds = 0;
	fTextView->SetText("00:00");
	fRunning = true;

}


void
TimerView::StopTimer()
{

	fRunning = false;

}

