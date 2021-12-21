#include "timerview.h"

#include <Catalog.h>
#include <LayoutBuilder.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "TimerView"


TimerView::TimerView()
	:
	BView("timerview", B_WILL_DRAW|B_PULSE_NEEDED)
{

	fRunning = false;

}


void
TimerView::Pulse()
{
	if (fRunning)
	{



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
	fRunning = true;

}


void
TimerView::StopTimer()
{

	fRunning = false;

}

