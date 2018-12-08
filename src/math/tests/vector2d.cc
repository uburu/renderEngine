#include "Vector2d.h"

#include <gtest/gtest.h>

TEST(TestVector2d, BasicTests) {
    {
        Vector2d<> a;
        Vector2d<> b;

        ASSERT_EQ(a, b);
    }

    {
        Vector2d a(1, 2);
        Vector2d b(1, 2);

        ASSERT_EQ(a, b);
    }

    {
        Matrix m(1, 2, 3.14);
        Vector2d v(m);
        Vector2d r(3.14, 3.14);

        ASSERT_EQ(v, r);
    }

    {
        Matrix m(2, 1, 3.14);
        Vector2d v(m);
        Vector2d r(3.14, 3.14);

        ASSERT_EQ(v, r);
    }

    {
        Matrix m(2, 1, 3.14);
        Vector2d v(std::move(m));
        Vector2d r(3.14, 3.14);

        ASSERT_EQ(v, r);
    }
}

TEST(TestVector2d, TestScalarAdd) {
    Vector2d v(0, 1);
    Vector2d v_assign(v);

    v_assign += 10;

    Vector2d r(10, 11);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v + 10, r);
    EXPECT_EQ(10 + v, r);
}

TEST(TestVector2d, TestScalarSub) {
    Vector2d v(0, 1);
    Vector2d v_assign(v);

    v_assign -= 10;

    Vector2d r(-10, -9);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v - 10, r);  
}

TEST(TestVector2d, TestScalarDiv) {
    Vector2d v(10, 20);
    Vector2d v_assign(v);

    v_assign /= 2;

    Vector2d r(5, 10);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v / 2, r); 
}

TEST(TestVector2d, TestVectorMatrixMul) {
    Matrix m(1, 1, 10);
    Vector2d v(1, 1);

    Matrix r(2, 1, 10);

    EXPECT_EQ(v * m, r); 
}

TEST(TestVector2d, TestCastOperator) {
    Vector2d<double> v(1.2, 2.4);
    Vector2d<int> v_int(1, 2);

    EXPECT_EQ(v_int, static_cast<Vector2d<int>>(v));
}

TEST(TestVector2d, TestMap) {
    Vector2d<double> v(1.2, 2.4);
    Vector2d<int> v_int(2, 3);

    auto c = v.Map([](auto element) {
        return static_cast<int>(std::ceil(element));
    });

    EXPECT_EQ(v_int, c);
}

TEST(TestVector2d, TestAsMatrix) {
    Vector2d v(1.1, 1.2);

    Matrix vert2 = {
        { 1.1 }, 
        { 1.2 }
    };

    Matrix horiz2 = {
        { 1.1, 1.2 }
    };

    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical).RawData(), v.RawData());
    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical), vert2);
    EXPECT_EQ(v.AsMatrix(VectorOrientation::kHorizontal), horiz2);

    Vector3d<double> &v3 = v;

    Matrix vert3 = {
        { 1.1 }, 
        { 1.2 },
        { 0.0 }
    };

    Matrix horiz3 = {
        { 1.1, 1.2, 0.0 }
    };

    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical).RawData(), v3.RawData());
    EXPECT_EQ(v3.AsMatrix(VectorOrientation::kVertical), vert3);
    EXPECT_EQ(v3.AsMatrix(VectorOrientation::kHorizontal), horiz3);

    Vector4d<double> &v4 = v;

    Matrix vert4 = {
        { 1.1 }, 
        { 1.2 },
        { 0.0 },
        { 0.0 }
    };

    Matrix horiz4 = {
        { 1.1, 1.2, 0.0, 0.0 }
    };

    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical).RawData(), v4.RawData());
    EXPECT_EQ(v4.AsMatrix(VectorOrientation::kVertical), vert4);
    EXPECT_EQ(v4.AsMatrix(VectorOrientation::kHorizontal), horiz4);
}

TEST(TestVector2d, TestCastToVector3d) {
    Vector2d a(1.1, 1.2);
    Vector2d b(1.1, 1.2);

    Vector3d<double> &v3 = a;
    Vector3d r(1.1, 1.2, 100.);
    v3.z(100.);

    EXPECT_EQ(a, b);
    EXPECT_EQ(v3, r);
}