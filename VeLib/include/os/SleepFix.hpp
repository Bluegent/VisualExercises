#pragma once


namespace ve
{
    class SleepFix
    {
    public:
        virtual void fix(const int resolutionMs) = 0;
        virtual void unfix() = 0;
    };
}