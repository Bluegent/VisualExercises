#include <os/SleepFix.hpp>
#include "WinSleepUnfucker.hpp"

namespace ve
{
    class SleepFixImpl : public SleepFix
    {
    private:
        WinSleepUnfucker unfucker;
    public:
        SleepFixImpl(const int resolutionMs);
        void fix(const int resolutionMs);
        void unfix();
    };
}