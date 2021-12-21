#include "timerview.h"

#include <Catalog.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "TimerView"


TimerView::TimerView()
	:
	BTextView("timerview", B_SUPPORTS_LAYOUT|B_WILL_DRAW|B_PULSE_NEEDED)
{

	fRunning = false;
	MakeEditable(false);

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

		SetText(time_string.String());
	}

}


void
TimerView::StartTimer()
{

	fMinutes = 0;
	fSeconds = 0;
	SetText("00:00");
	fRunning = true;

}


void
TimerView::StopTimer()
{

	fRunning = false;

}

