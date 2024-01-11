#include <Catest.h>
#include <ve/Helper/Math.hpp>

CATEST_F(TempTest, Temp)
{
    ASSERT_TRUE(true);
    float angle = ve::toRadians(0);
    ASSERT_FEQ(angle, 0.f);
}
