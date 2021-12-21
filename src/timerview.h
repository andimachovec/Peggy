#ifndef TIMERVIEW_H
#define TIMERVIEW_H


#include <View.h>
#include <TextView.h>


class TimerView : public BView {
public:
	TimerView();
	void Pulse();
	void Draw(BRect updateRect);
	void StartTimer();
	void StopTimer();

private:
	int32 		fMinutes;
	int32 		fSeconds;
	bool 		fRunning;
	BTextView	*fTextView;
};


#endif
