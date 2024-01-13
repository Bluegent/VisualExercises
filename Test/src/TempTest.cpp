#include "gtest/gtest.h"
#include <ve/Helper/Math.hpp>

TEST(TempTest, Temp)
{
    ASSERT_TRUE(true);
    float angle = ve::toRadians(0);
    ASSERT_FLOAT_EQ(angle, 0.f);
}
