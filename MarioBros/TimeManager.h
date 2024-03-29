#ifndef _TIMEMANAGER_H
#define _TIMEMANAGER_H

#include <time.h>
#include <windows.h>
class TimeManager
{
private:
	
	bool	useQueryPerformance;
	INT64	lastTime;
	INT64	currentTime;
	double	secondPerTick;
	int		FPSCounter;
	float	waitFPSUpdate;
	float	TPFArray[10];
	char	numTPFArrElement;

public:
	float TPF;						//Thời gian trên một khung hình
	float FPS;

	TimeManager();
	~TimeManager();
	void LimitFPS(float FPSLimit);		//Giới hạn số FPS
};
#endif