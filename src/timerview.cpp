/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "timerview.h"

#include <Catalog.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "TimerView"


TimerView::TimerView()
	:
	BTextView("timerview", B_SUPPORTS_LAYOUT|B_WILL_DRAW|B_PULSE_NEEDED)
{

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
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
		time_string << B_TRANSLATE("Time elapsed") << ": " << minutes_string << ":" << seconds_string;

		SetText(time_string.String());
	}

}


void
TimerView::StartTimer()
{

	fMinutes = 0;
	fSeconds = 0;
	BString time_string;
	time_string << B_TRANSLATE("Time elapsed") << ": 00:00";
	SetText(time_string.String());
	fRunning = true;

}


void
TimerView::StopTimer()
{

	fRunning = false;

}

