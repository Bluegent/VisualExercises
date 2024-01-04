#include "WinSleepUnfucker.hpp"
#include <windows.h>
#include <iostream>

WinSleepUnfucker::WinSleepUnfucker(const int32_t sleepResolution)
    :sleepResolution(sleepResolution)
{
    timeBeginPeriod(sleepResolution);
}

WinSleepUnfucker::~WinSleepUnfucker()
{
    timeEndPeriod(sleepResolution);
}
