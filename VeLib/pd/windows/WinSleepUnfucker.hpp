#pragma once
#include <stdint.h>

namespace ve
{
    class WinSleepUnfucker
    {
    private:
        int32_t sleepResolution;
        bool wasFixed;
    public:
        WinSleepUnfucker(const int32_t resolution = 16);
        void fix(const int32_t resolution);
        void unfix();
        ~WinSleepUnfucker();
    };
}