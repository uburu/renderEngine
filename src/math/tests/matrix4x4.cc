#include "matrix4x4.h"

#include <gtest/gtest.h>

TEST(TestMatrix4x4, BasicTests) {
    {
        Matrix4x4<> m1;
        Matrix4x4<> m2;

        ASSERT_EQ(m1, m2);
        ASSERT_EQ(m1.GetRows(), 4);
        ASSERT_EQ(m1.GetColumns(), 4);
    }

    {
        Matrix4x4 m1(42.2);
        Matrix4x4 m2(42.2);

        ASSERT_EQ(m1, m2);
    }

    {
        Matrix m1 = { 
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 }            
        };

        Matrix m2 = {
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 }
        };

        ASSERT_EQ(m1, m2);
    }

    {
        Matrix m1 = { 
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 },
            { 1, 2, 3, 4 }   
        };

        Matrix r = { 
            { 1, 2, 3,   4 },
            { 1, 2, 3,   4 },
            { 1, 2, 333, 4 },
            { 1, 2, 3,   4 }   
        };

        m1 = {
            { 1, 2, 3,   4 },
            { 1, 2, 3,   4 },
            { 1, 2, 333, 4 },
            { 1, 2, 3,   4 }
        };

        ASSERT_EQ(m1, r);
    }

    {
        auto m = Matrix4x4<>::Identity();

        EXPECT_EQ(m.At(0, 0), 1);
        EXPECT_EQ(m.At(0, 1), 0);
        EXPECT_EQ(m.At(0, 2), 0);
        EXPECT_EQ(m.At(0, 3), 0);

        EXPECT_EQ(m.At(1, 0), 0);
        EXPECT_EQ(m.At(1, 1), 1);
        EXPECT_EQ(m.At(1, 2), 0);
        EXPECT_EQ(m.At(1, 3), 0);

        EXPECT_EQ(m.At(2, 0), 0);
        EXPECT_EQ(m.At(2, 1), 0);
        EXPECT_EQ(m.At(2, 2), 1);
        EXPECT_EQ(m.At(2, 3), 0);

        EXPECT_EQ(m.At(3, 0), 0);
        EXPECT_EQ(m.At(3, 1), 0);
        EXPECT_EQ(m.At(3, 2), 0);
        EXPECT_EQ(m.At(3, 3), 1);
    }

    {
        auto m = Matrix4x4<>::Zero();
        Matrix4x4<> r = {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        };

        EXPECT_EQ(m, r);
    }

    {
        auto m = Matrix4x4<>::Diagonal(4);
        Matrix4x4<> r = {
            { 4, 0, 0, 0 },
            { 0, 4, 0, 0 },
            { 0, 0, 4, 0 },
            { 0, 0, 0, 4 }
        };

        EXPECT_EQ(m, r);
    }
}

TEST(TestMatrix4x4, TestMatrix4x4Mul) {
    Matrix4x4 m1 = {
        { 1, 2, 3, 4 },
        { 1, 2, 3, 4 },
        { 1, 2, 3, 4 },
        { 1, 2, 3, 4 }
    };

    Matrix4x4 m2 = {
        { 10, 20, 30, 40 },
        { 10, 20, 30, 40 },
        { 10, 20, 30, 40 },
        { 10, 20, 30, 40 }
    };

    Matrix r = {
        { 100, 200, 300, 400 },
        { 100, 200, 300, 400 },
        { 100, 200, 300, 400 },
        { 100, 200, 300, 400 }
    };

    EXPECT_EQ(m1 * m2, r);
}

TEST(TestMatrix4x4, TestCastOperator) {
    Matrix4x4 m = {
        {1.23, 2.55, 4.21, 3.14},
        {1.23, 2.55, 4.21, 3.14},
        {1.23, 2.55, 4.21, 3.14},
        {1.23, 2.55, 4.21, 3.14}
    };

    Matrix4x4 m_int = {
        {1, 2, 4, 3},
        {1, 2, 4, 3},
        {1, 2, 4, 3},
        {1, 2, 4, 3}
    };

    EXPECT_EQ(static_cast<Matrix4x4<int>>(m), m_int);
}

TEST(TestMatrix4x4, TestMap) {
    Matrix4x4 m = {
        {1.23, 2.55, 4.21, 3.14},
        {1.23, 2.55, 4.21, 3.14},
        {1.23, 2.55, 4.21, 3.14},
        {1.23, 2.55, 4.21, 3.14}
    };

    Matrix4x4 m_int = {
        {2, 3, 5, 4},
        {2, 3, 5, 4},
        {2, 3, 5, 4},
        {2, 3, 5, 4}
    };

    auto c = m.Map([](auto v) {
        return static_cast<int>(std::ceil(v));
    });

    EXPECT_EQ(c, m_int);
}