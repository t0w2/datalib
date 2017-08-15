#include "../libs/structures.h"
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}


TEST(own_hash, constructor)
{
    //own_hash<int>* myhash = new own_hash<int>;
    own_hash<int> myhash();
    ASSERT_TRUE(true);
}