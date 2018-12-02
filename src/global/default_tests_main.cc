#include <iostream>

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

#if defined(UU_DONT_CLOSE_TESTS)
    std::cin.get();
#endif // UU_DONT_CLOSE_TESTS 

    return RUN_ALL_TESTS();
}