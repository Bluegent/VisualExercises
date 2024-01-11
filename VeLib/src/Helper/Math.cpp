#include <ve/Helper/Math.hpp>
#include <random>

namespace ve
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int32_t> intDist;
    static std::uniform_real_distribution<float> floatDist(0.f,1.f);

    const float PI = 3.14159265;

    float toRadians(const float angle)
    {
        return PI / 180.f * angle;
    }
    int32_t getRandom(const int32_t min, const int32_t max)
    {
        return intDist(mt) % (max - min) + min;
    }
    float getRandomF(const float min, const float max)
    {
        return min + (max-min) * floatDist(mt);
    }
}
