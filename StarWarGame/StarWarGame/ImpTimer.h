
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_ 

#include "CommonFunction.h"

class ImpTimer
{
public:
	ImpTimer() ;
	~ImpTimer() ;

	// Game Time Controller
	void start() ;
	void stop() ;
	void pause() ;
	void unpause() ;

	// Get Current Tick
	int getTick() ;

	// Get Game Status
	bool isStarted() ;
	bool isPaused() ;

private:
	// Numerical Order Of Tick
	int start_tick ;
	int pause_tick ;

	// Status
	bool is_started ;
	bool is_paused ;
} ;

#endif 