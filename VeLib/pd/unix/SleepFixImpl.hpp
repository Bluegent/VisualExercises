#include <os/SleepFix.hpp>

namespace ve
{
    // dummy implementation since this is not needed on unix systems
    class SleepFixImpl : public SleepFix
    {
    public:
        SleepFixImpl(const int resolutionMs){}
        void fix(const int resolutionMs){}
        void unfix(){}
    };
}