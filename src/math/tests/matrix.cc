#include "matrix.h"

#include <gtest/gtest.h>

TEST(TestMatrix, BasicTests) {

    {
        Matrix m1(3, 4);
        Matrix m2(3, 4);

        ASSERT_EQ(m1, m2);
        ASSERT_EQ(m1.GetRows(),    3);
        ASSERT_EQ(m1.GetColumns(), 4);
    }

    {
        Matrix m1(3, 4, 10.);
        Matrix m2(3, 4, 10.);

        ASSERT_EQ(m1, m2);
    }

    {
        Matrix m1 = { 
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        Matrix m2 = {
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        ASSERT_EQ(m1, m2);
    }

    {
        Matrix m1 = { 
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        Matrix r = { 
            { 1, 20 },
            { 4, 50 }
        };

        m1 = {
            { 1, 20 },
            { 4, 50 }
        };

        ASSERT_EQ(m1, r);
    }

    {
        Matrix m1(3, 4, 10.);
        Matrix m2(m1);

        ASSERT_EQ(m1, m2);
        ASSERT_NE(m1.RawData(), m2.RawData());
    }

    {
        Matrix m1(3, 4, 10.);
        auto raw_m1 = m1.RawData();

        Matrix m2(std::move(m1));

        ASSERT_EQ(raw_m1, m2.RawData());
    }

    {
        Matrix m = {
            { 1, 2 },
            { 3, 4 }
        };

        ASSERT_EQ(m.At(0, 0), 1);
        ASSERT_EQ(m.At(0, 1), 2);
        ASSERT_EQ(m.At(1, 0), 3);
        ASSERT_EQ(m.At(1, 1), 4);
    }

    {
        auto m = Matrix<>::Identity(3);

        EXPECT_EQ(m.At(0, 0), 1);
        EXPECT_EQ(m.At(0, 1), 0);
        EXPECT_EQ(m.At(0, 2), 0);

        EXPECT_EQ(m.At(1, 0), 0);
        EXPECT_EQ(m.At(1, 1), 1);
        EXPECT_EQ(m.At(1, 2), 0);

        EXPECT_EQ(m.At(2, 0), 0);
        EXPECT_EQ(m.At(2, 1), 0);
        EXPECT_EQ(m.At(2, 2), 1);
    }

    {
        auto m = Matrix<>::Zero(2, 3);

        EXPECT_EQ(m.At(0, 0), 0);
        EXPECT_EQ(m.At(0, 1), 0);
        EXPECT_EQ(m.At(0, 2), 0);

        EXPECT_EQ(m.At(1, 0), 0);
        EXPECT_EQ(m.At(1, 1), 0);
        EXPECT_EQ(m.At(1, 2), 0);
    }

    {
        auto m = Matrix<>::Diagonal(3, 11.2);

        EXPECT_EQ(m.At(0, 0), 11.2);
        EXPECT_EQ(m.At(0, 1), 0);
        EXPECT_EQ(m.At(0, 2), 0);

        EXPECT_EQ(m.At(1, 0), 0);
        EXPECT_EQ(m.At(1, 1), 11.2);
        EXPECT_EQ(m.At(1, 2), 0);

        EXPECT_EQ(m.At(2, 0), 0);
        EXPECT_EQ(m.At(2, 1), 0);
        EXPECT_EQ(m.At(2, 2), 11.2);
    }

    {
        auto m = Matrix<>::Square(3);
        EXPECT_EQ(m, Matrix<>::Zero(3, 3));
    }

    {
        auto m = Matrix<>::Square(3, 42.1);

        EXPECT_EQ(m.At(0, 0), 42.1);
        EXPECT_EQ(m.At(0, 1), 42.1);
        EXPECT_EQ(m.At(0, 2), 42.1);

        EXPECT_EQ(m.At(1, 0), 42.1);
        EXPECT_EQ(m.At(1, 1), 42.1);
        EXPECT_EQ(m.At(1, 2), 42.1);

        EXPECT_EQ(m.At(2, 0), 42.1);
        EXPECT_EQ(m.At(2, 1), 42.1);
        EXPECT_EQ(m.At(2, 2), 42.1);
    }
}

TEST(TestMatrix, TestScalarAdd) {
    Matrix m = {
        {1, 2},
        {3, 4}
    };

    Matrix m_assign(m);
    m_assign += 10;

    Matrix r = {
        {11, 12},
        {13, 14}
    };

    EXPECT_EQ(m + 10, r);
    EXPECT_EQ(10 + m, r);
    EXPECT_EQ(m_assign, r);

}

TEST(TestMatrix, TestScalarMul) {
    Matrix m = {
        {1, 2},
        {3, 4}
    };

    Matrix m_assign(m);
    m_assign *= 10;

    Matrix r = {
        {10, 20},
        {30, 40}
    };

    EXPECT_EQ(m * 10, r);
    EXPECT_EQ(10 * m, r);
    EXPECT_EQ(m_assign, r);
}

TEST(TestMatrix, TestScalarDiv) {
    Matrix m = {
        {10, 20},
        {30, 40}
    };

    Matrix m_assign(m);
    m_assign /= 2;

    Matrix r = {
        {5, 10},
        {15, 20}
    };

    EXPECT_EQ(m / 2, r);
    EXPECT_EQ(m_assign, r);
    EXPECT_EQ(m_assign, r);
}

TEST(TestMatrix, TestMatrixAdd) {
    Matrix m1 = {
        {1, 2},
        {3, 4}
    };

    Matrix m2 = {
        { 10, 20 },
        { 30, 40 }
    };

    Matrix m1_assign(m1);
    m1_assign += m2;

    Matrix m2_assign(m2);
    m2_assign += m1;

    Matrix r = {
        { 11, 22 },
        { 33, 44 }
    };

    EXPECT_EQ(m1 + m2, r);
    EXPECT_EQ(m2 + m1, r);
    EXPECT_EQ(m1_assign, r);
    EXPECT_EQ(m2_assign, r);
}

TEST(TestMatrix, TestMatrixSub) {
    Matrix m1 = {
        {1, 2},
        {3, 4}
    };

    Matrix m2 = {
        { 10, 20 },
        { 30, 40 }
    };

    Matrix m1_assign(m1);
    m1_assign -= m2;

    Matrix m2_assign(m2);
    m2_assign -= m1;

    Matrix r_12 = {
        { -9,  -18 },
        { -27, -36 }
    };

    Matrix r_21 = {
        { 9,  18 },
        { 27, 36 }
    };

    EXPECT_EQ(m1 - m2, r_12);
    EXPECT_EQ(m2 - m1, r_21);
    EXPECT_EQ(m1_assign, r_12);
    EXPECT_EQ(m2_assign, r_21);
}

TEST(TestMatrix, TestMatrixMul) {
    {
        Matrix m1 = {
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        Matrix m2 = {
            { 1, 2 },
            { 10, 20 },
            { 30, 40 }
        };

        Matrix r = {
            { 111, 162 },
            { 234, 348 }
        };

        EXPECT_EQ(m1 * m2, r);
    }

    {
        Matrix m1 = {
            { 1, 2, 3 },
            { 4, 5, 6 }
        };

        Matrix m2 = {
            { 10, 10, 10 },
            { 20, 20, 20 },
            { 30, 30, 30 }
        };

        Matrix r = {
            { 140, 140, 140 },
            { 320, 320, 320 }
        };

        m1 *= m2;
        EXPECT_EQ(m1, r);
    }

    {
        Matrix m1 = {
            { 1, 2 },
            { 3, 4 }
        };

        Matrix m2 = {
            { 10, 10 },
            { 20, 20 }
        };

        EXPECT_NE(m1 * m2, m2 * m1);
    }
}

TEST(TestMatrix, TestUnaryPlus) {
    Matrix m = {
        {1, 2}
    };

    EXPECT_EQ(+m, m);
}

TEST(TestMatrix, TestUnaryMinus) {
    Matrix m = {
        {1, 2}
    };

    EXPECT_EQ(-m, (-1)*m);
}

TEST(TestMatrix, TestMap) {
    Matrix m = {
        {1.23, 2.55}
    };

    Matrix m_int = {
        {2, 3}
    };

    auto c = m.Map([](auto v) {
        return static_cast<int>(std::ceil(v));
    });

    EXPECT_EQ(c, m_int);
}

TEST(TestMatrix, TestCastOperator) {
    Matrix m = {
        {1.23, 2.55}
    };

    Matrix m_int = {
        {1, 2}
    };

    EXPECT_EQ(static_cast<Matrix<int>>(m), m_int);
}

TEST(TestMatrix, TestOrder) {
    int raw_row_major[] = { 1, 2, 3, 4 };
    int raw_col_major[] = { 1, 3, 2, 4 };

    {
        Matrix m_row({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kRowMajor);

        EXPECT_EQ(m_row.GetOrder(), MatrixOrder::kRowMajor);

        Matrix m_column({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kColumnMajor);

        EXPECT_EQ(m_column.GetOrder(), MatrixOrder::kColumnMajor);

        EXPECT_TRUE(std::equal(m_row.begin(), m_row.end(), raw_row_major));
        EXPECT_TRUE(std::equal(m_column.begin(), m_column.end(), raw_col_major));
    }

    {
        Matrix m({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kRowMajor);

        m.SetOrder(MatrixOrder::kRowMajor);
        EXPECT_TRUE(std::equal(m.begin(), m.end(), raw_row_major));
    }

    {
        Matrix m({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kRowMajor);

        m.SetOrder(MatrixOrder::kColumnMajor);
        EXPECT_TRUE(std::equal(m.begin(), m.end(), raw_col_major));
    }

    {
        Matrix m({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kColumnMajor);

        m.SetOrder(MatrixOrder::kColumnMajor);
        EXPECT_TRUE(std::equal(m.begin(), m.end(), raw_col_major));
    }

    {
        Matrix m({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kColumnMajor);

        m.SetOrder(MatrixOrder::kRowMajor);
        EXPECT_TRUE(std::equal(m.begin(), m.end(), raw_row_major));
    }

    {
        Matrix m({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kRowMajor);

        auto r = m.WithOrder(MatrixOrder::kColumnMajor);

        EXPECT_TRUE(std::equal(r.begin(), r.end(), raw_col_major));
    }

    {
        Matrix m({
            {1, 2},
            {3, 4}
        }, MatrixOrder::kColumnMajor);

        auto r = m.WithOrder(MatrixOrder::kRowMajor);

        EXPECT_TRUE(std::equal(r.begin(), r.end(), raw_row_major));
    }
}

TEST(TestMatrix, TestRound) {
    Matrix m = {
        {1.23, 2.55}
    };

    Matrix rounded(m);
    rounded.Round();

    Matrix r = {
        {1., 3.}
    };

    EXPECT_EQ(rounded, r);
    EXPECT_EQ(m.Rounded(), r);
}

TEST(TestMatrix, TestTranspose) {
    Matrix m1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    Matrix tr_1(m1);
    tr_1.Transpose();

    Matrix m2 = {
        {1, 3, 5},
        {2, 4, 6}
    };

    Matrix tr_2(m2);
    tr_2.Transpose();

    EXPECT_EQ(tr_1, m2);
    EXPECT_EQ(tr_2, m1);

    tr_1.Transpose();
    tr_2.Transpose();

    EXPECT_EQ(tr_1, m1);
    EXPECT_EQ(tr_2, m2);

    EXPECT_EQ(m1.Transposed(), m2);
    EXPECT_EQ(m2.Transposed(), m1);

    Matrix m3x3 = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    Matrix r3x3 = {
        {14, 32, 50},
        {32, 77, 122},
        {50, 122, 194}
    };

    EXPECT_EQ(m3x3 * m3x3.Transposed(), r3x3);
}

TEST(TestMatrix, TestShare) {
    Matrix m1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    Matrix m2 = m1.Share();

    EXPECT_EQ(m1, m2);
    EXPECT_EQ(m1.RawData(), m2.RawData());
}

TEST(TestMatrix, TestRawData) {
    Matrix m = {
        {1, 2},
        {3, 4}
    };

    m.RawData()[1] = 22;

    EXPECT_EQ(m.At(0, 1), 22);
}

TEST(TestMatrix, TestBeginEnd) {
    Matrix m = {
        {1, 2},
        {3, 4}
    };

    int i = 1;
    for(auto &&element : m) {
        EXPECT_EQ(element, i++);
    }

    {
        const Matrix m = {
            {1, 2},
            {3, 4}
        };

        int i = 1;
        for(auto it = m.cbegin(), end = m.cend(); it != end; ++it) {
            EXPECT_EQ(*it, i++);
        }
    }
}

TEST(TestMatrix, TestRbeginRend) {
    {
        Matrix m = {
            {1, 2},
            {3, 4}
        };

        int i = 4;
        for(auto it = m.rbegin(), end = m.rend(); it != end; ++it) {
            EXPECT_EQ(*it, i--);
        }
    }

    {
        const Matrix m = {
            {1, 2},
            {3, 4}
        };

        int i = 4;
        for(auto it = m.crbegin(), end = m.crend(); it != end; ++it) {
            EXPECT_EQ(*it, i--);
        }
    }
}