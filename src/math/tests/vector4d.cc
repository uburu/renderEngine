#include "vector4d.h"

#include <gtest/gtest.h>

TEST(TestVector4d, BasicTests) {
    {
        Vector4d<> a;
        Vector4d<> b;

        ASSERT_EQ(a, b);
    }

    {
        Vector4d a(1, 2, 3, 4);
        Vector4d b(1, 2, 3, 4);

        ASSERT_EQ(a, b);
    }

    {
        Matrix m(1, 4, 3.14);
        Vector4d v(m);
        Vector4d r(3.14, 3.14, 3.14, 3.14);

        ASSERT_EQ(v, r);
    }

    {
        Matrix m(4, 1, 3.14);
        Vector4d v(m);
        Vector4d r(3.14, 3.14, 3.14, 3.14);

        ASSERT_EQ(v, r);
    }

    {
        Matrix m(4, 1, 3.14);
        Vector4d v(std::move(m));
        Vector4d r(3.14, 3.14, 3.14, 3.14);

        ASSERT_EQ(v, r);
    }
}

TEST(TestVector4d, TestScalarAdd) {
    Vector4d v(0, 0, 1, 2);
    Vector4d v_assign(v);

    v_assign += 10;

    Vector4d r(10, 10, 11, 12);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v + 10, r);
    EXPECT_EQ(10 + v, r);
}

TEST(TestVector4d, TestScalarSub) {
    Vector4d v(0, 0, 1, 2);
    Vector4d v_assign(v);

    v_assign -= 10;

    Vector4d r(-10, -10, -9, -8);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v - 10, r);  
}

TEST(TestVector4d, TestScalarDiv) {
    Vector4d v(10, 10, 20, 20);
    Vector4d v_assign(v);

    v_assign /= 2;

    Vector4d r(5, 5, 10, 10);

    EXPECT_EQ(v_assign, r);
    EXPECT_EQ(v / 2, r); 
}

TEST(TestVector4d, TestVectorMatrixMul) {
    Matrix m(1, 1, 10);
    Vector4d v(1, 1, 1, 1);

    Matrix r(4, 1, 10);

    EXPECT_EQ(v * m, r); 
}

TEST(TestVector4d, TestCastOperator) {
    Vector4d<double> v(1.2, 2.4, 3.3, 5.6);
    Vector4d<int> v_int(1, 2, 3, 5);

    EXPECT_EQ(v_int, static_cast<Vector4d<int>>(v));
}

TEST(TestVector4d, TestMap) {
    Vector4d<double> v(1.2, 2.4, 3.3, 5.6);
    Vector4d<int> v_int(2, 3, 4, 6);

    auto c = v.Map([](auto element) {
        return static_cast<int>(std::ceil(element));
    });

    EXPECT_EQ(v_int, c);
}

TEST(TestVector4d, TestGets) {
    Vector4d v(1, 2, 3, 4);
    const Vector4d const_v(v);
    
    EXPECT_EQ(v.GetX(), 1);
    EXPECT_EQ(v.GetY(), 2);
    EXPECT_EQ(v.GetZ(), 3);
    EXPECT_EQ(v.GetW(), 4);

    EXPECT_EQ(v.x(), 1);
    EXPECT_EQ(v.y(), 2);
    EXPECT_EQ(v.z(), 3);
    EXPECT_EQ(v.w(), 4);

    EXPECT_EQ(const_v.x(), 1);
    EXPECT_EQ(const_v.y(), 2);
    EXPECT_EQ(const_v.z(), 3);
    EXPECT_EQ(const_v.w(), 4);
}

TEST(TestVector4d, TestSets) {
    Vector4d<int> v;
    Vector4d r(1, 2, 3, 4);


    v.SetX(1);
    v.SetY(2);
    v.SetZ(3);
    v.SetW(4);

    EXPECT_EQ(v, r);

    v = Vector4d<int>().x(1).y(2).z(3).w(4);
    EXPECT_EQ(v, r);
}

TEST(TestVector4d, TestDot) {
    Vector4d a(1, 1, 1, 1);
    Vector4d b(10, 10, 10, 10);
    int r = 40;

    EXPECT_EQ(a.Dot(b), r);
}

TEST(TestVector4d, TestNorm) {
    Vector4d v(1, 1, 1, 1);
    int r = 4;

    EXPECT_EQ(v.Norm(), r);
}

TEST(TestVector4d, TestLength) {
    Vector4d v(1, 1, 1, 1);
    int l = 2;

    EXPECT_EQ(v.Length(), l);
}

TEST(TestVector4d, TestNormalize) {
    Vector4d v(1., 1., 1., 1.);
    Vector4d normalized(v);
    normalized.Normalize();

    Vector4d r(0.5, 0.5, 0.5, 0.5);


    EXPECT_EQ(v.Normalized(), r);
    EXPECT_EQ(normalized, r);
}

TEST(TestVector4d, TestShare) {
    Vector4d<int> src;
    Vector4d shared = src.Share();

    EXPECT_EQ(src, shared);
    EXPECT_EQ(src.RawData(), shared.RawData());
}

TEST(TestVector4d, TestAsMatrix) {
    Vector4d v(1.1, 1.2, 1.3, 1.4);

    Matrix vert = {
        { 1.1 }, 
        { 1.2 },
        { 1.3 },
        { 1.4 }
    };

    Matrix horiz = {
        { 1.1, 1.2, 1.3, 1.4 }
    };

    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical).RawData(), v.RawData());
    EXPECT_EQ(v.AsMatrix(VectorOrientation::kVertical), vert);
    EXPECT_EQ(v.AsMatrix(VectorOrientation::kHorizontal), horiz);
}