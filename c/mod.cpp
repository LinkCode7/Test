#include <float.h>

TEST(basic, c_mod)
{
    double angle = 0.0;
    EXPECT_TRUE(std::fmod(angle, 360.0) == 0.0);

    EXPECT_TRUE(std::fmod(360.0, 360.0) == 0.0);

    EXPECT_TRUE(std::fmod(1.0, 360.0) == 1.0);

    EXPECT_TRUE(std::fmod(0.0, PI * 2) == 0.0);
}
