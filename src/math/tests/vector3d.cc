#include "vector3d.h"

#include <gtest/gtest.h>

TEST(TestVector3d, BasicTests) {
    {
        Vector3d<> a;
        Vector3d<> b;

        ASSERT_EQ(a, b);
    }

    {
        Vector3d a(1, 2, 3);
        Vector3d b(1, 2, 3);

        ASSERT_EQ(a, b);
    }

    {
        Matrix m(1, 3, 3.14);
        Vector3d v(m);
        Vector3d r(3.14, 3.14, 3.14);

        ASSERT_EQ(v, r);
    }

    {
        Matrix m(3, 1, 3.14);
        Vector3d v(m);
        Vector3d r(3.14, 3.14, 3.14);

        ASSERT_EQ(v, r);
    }

    {
        Matrix m(3, 1, 3.14);
        Vector3d v(std::move(m));
        Vector3d r(3.14, 3.14, 3.14);

        ASSERT_EQ(v, r);
    }
}

TEST(TestVector3d, TestScalarAdd) {
    Vector3d v(0, 0, 1);
    Vector3d v_assign(v);

    v_assign += 10;

    Vector3d r(10, 10, 11);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v + 10, r);
    EXPECT_EQ(10 + v, r);
}

TEST(TestVector3d, TestScalarSub) {
    Vector3d v(0, 0, 1);
    Vector3d v_assign(v);

    v_assign -= 10;

    Vector3d r(-10, -10, -9);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v - 10, r);  
}

TEST(TestVector3d, TestScalarDiv) {
    Vector3d v(10, 10, 20);
    Vector3d v_assign(v);

    v_assign /= 2;

    Vector3d r(5, 5, 10);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v / 2, r); 
}

TEST(TestVector3d, TestVectorAdd) {
    Vector3d a(1, 1, 1);
    Vector3d b(10, 10, 10);
    Vector3d r(11, 11, 11);

    Vector3d a_assign(a);
    a_assign += b;

    EXPECT_EQ(a_assign, r);
    EXPECT_EQ(a + b, r);
    EXPECT_EQ(b + a, r);
}

TEST(TestVector3d, TestVectorSub) {
    Vector3d a(1, 1, 1);
    Vector3d b(10, 10, 10);
    Vector3d r1(-9, -9, -9);
    Vector3d r2(9, 9, 9);

    Vector3d a_assign(a);
    a_assign -= b;

    EXPECT_EQ(a_assign, r1);
    EXPECT_EQ(a - b, r1);
    EXPECT_EQ(b - a, r2);
}

TEST(TestVector3d, TestVectorMatrixMul) {
    Matrix m(1, 1, 10);
    Vector3d v(1, 1, 1);

    Matrix r(3, 1, 10);

    EXPECT_EQ(v * m, r); 
}

TEST(TestVector3d, TestCastOperator) {
    Vector3d<double> v(1.2, 2.4, 3.3);
    Vector3d<int> v_int(1, 2, 3);

    EXPECT_EQ(v_int, static_cast<Vector3d<int>>(v));
}

TEST(TestVector3d, TestCross) {
    Vector3d a(10., 0., 45.);
    Vector3d b(0., 10., 10.);
    Vector3d r(-450., -100., 100.);

    EXPECT_EQ(a.Cross(b), r);
}

TEST(TestVector3d, TestMap) {
    Vector3d<double> v(1.2, 2.4, 3.3);
    Vector3d<int> v_int(2, 3, 4);

    auto c = v.Map([](auto element) {
        return static_cast<int>(std::ceil(element));
    });

    EXPECT_EQ(v_int, c);
}

TEST(TestVector3d, TestAsMatrix) {
    Vector3d v(1.1, 1.2, 1.3);

    Matrix vert3 = {
        { 1.1 }, 
        { 1.2 },
        { 1.3 }
    };

    Matrix horiz3 = {
        { 1.1, 1.2, 1.3 }
    };

    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical).RawData(), v.RawData());
    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical), vert3);
    EXPECT_EQ(v.AsMatrix(VectorOrientation::kHorizontal), horiz3);

    Vector4d<double> &v4 = v;

    Matrix vert4 = {
        { 1.1 }, 
        { 1.2 },
        { 1.3 },
        { 0.0 }
    };

    Matrix horiz4 = {
        { 1.1, 1.2, 1.3, 0.0 }
    };

    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical).RawData(), v4.RawData());
    EXPECT_EQ(v4.AsMatrix(VectorOrientation::kVertical), vert4);
    EXPECT_EQ(v4.AsMatrix(VectorOrientation::kHorizontal), horiz4);
}

TEST(TestVector3d, TestCastToVector4d) {
    Vector3d a(1.1, 1.2, 1.3);
    Vector3d b(1.1, 1.2, 1.3);

    Vector4d<double> &v4 = a;
    Vector4d r(1.1, 1.2, 1.3, 100.);
    v4.w(100.);

    EXPECT_EQ(a, b);
    EXPECT_EQ(v4, r);
}

TEST(TestVector3d, TestAt) {
    Vector3d v(1, 2, 3);

    EXPECT_EQ(v.At(0), 1);
    EXPECT_EQ(v.At(1), 2);
    EXPECT_EQ(v.At(2), 3);
}