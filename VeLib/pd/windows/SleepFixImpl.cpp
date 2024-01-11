#include "SleepFixImpl.hpp"

ve::SleepFixImpl::SleepFixImpl(const int resolutionMs)
    :unfucker(resolutionMs)
{
}

void ve::SleepFixImpl::fix(const int resolutionMs)
{
    unfucker.fix(resolutionMs);
}

void ve::SleepFixImpl::unfix()
{
    unfucker.unfix();
}
