#include "WinSleepUnfucker.hpp"
#include <windows.h>
#include <iostream>

namespace ve
{
    WinSleepUnfucker::WinSleepUnfucker(const int32_t resolution)
        : sleepResolution{ resolution }
        , wasFixed {true}
    {
        fix(sleepResolution);
    }

    void WinSleepUnfucker::fix(const int32_t resolution)
    {
        this->sleepResolution = sleepResolution;
        wasFixed = true;
        timeBeginPeriod(this->sleepResolution);
    }

    void WinSleepUnfucker::unfix()
    {
        wasFixed = false;
        timeEndPeriod(sleepResolution);
    }

    WinSleepUnfucker::~WinSleepUnfucker()
    {
        unfix();
        std::cout << "Unfucked!\n";
    }

}