/*
 * Copyright 2021 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef TIMERVIEW_H
#define TIMERVIEW_H


#include <TextView.h>


class TimerView : public BTextView {
public:
	TimerView();
	void Pulse();
	void StartTimer();
	void StopTimer();

private:
	int32 		fMinutes;
	int32 		fSeconds;
	bool 		fRunning;
};


#endif
