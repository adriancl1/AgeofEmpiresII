#ifndef __TIMER_H__
#define __TIMER_H__

#include "Defs.h"

class Timer
{
public:
	// Constructor
	Timer();

	void Start();
	void Stop();

	uint32 Read() const;

	float ReadSec() const;

	void SetSec(float sec);

private:
	uint32	startedAt;

	bool stopped;
};

#endif //__TIMER_H__