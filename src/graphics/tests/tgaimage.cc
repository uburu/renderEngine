#include "tgaimage.h"

#include <gtest/gtest.h>

TEST(TestTGAImage, TestCreateAndGetSet) {
    TGAImage image(2, 2, TGAImage::kRGBA);

    EXPECT_EQ(image.GetWidth(), 2);
    EXPECT_EQ(image.GetHeight(), 2);

    EXPECT_EQ(image.GetPixel(0, 0), Color<>(0, 0, 0, 0));
    EXPECT_EQ(image.GetPixel(0, 1), Color<>(0, 0, 0, 0));
    EXPECT_EQ(image.GetPixel(1, 0), Color<>(0, 0, 0, 0));
    EXPECT_EQ(image.GetPixel(1, 1), Color<>(0, 0, 0, 0));

    image.SetPixel(0, 0, Color<>(1, 1, 1, 1));
    image.SetPixel(0, 1, Color<>(1, 0, 0, 1));
    image.SetPixel(1, 0, Color<>(0, 1, 0, 1));
    image.SetPixel(1, 1, Color<>(0, 0, 1, 1));

    EXPECT_EQ(image.GetPixel(0, 0), Color<>(1, 1, 1, 1));
    EXPECT_EQ(image.GetPixel(0, 1), Color<>(1, 0, 0, 1));
    EXPECT_EQ(image.GetPixel(1, 0), Color<>(0, 1, 0, 1));
    EXPECT_EQ(image.GetPixel(1, 1), Color<>(0, 0, 1, 1));
}

TEST(TestTGAImage, TestLoadWrite) {
    {
        TGAImage image(2, 2, TGAImage::kRGBA);

        image.SetPixel(0, 0, Color<>(1, 1, 1, 1));
        image.SetPixel(0, 1, Color<>(1, 0, 0, 1));
        image.SetPixel(1, 0, Color<>(0, 1, 0, 1));
        image.SetPixel(1, 1, Color<>(0, 0, 1, 1));
        image.WriteToFile(CMAKE_SOURCE_DIR "/src/graphics/tests/resources/square.tga");
    }

    {
        auto image = TGAImage::LoadFromFile(CMAKE_SOURCE_DIR "/src/graphics/tests/resources/square.tga");

        EXPECT_EQ(image->GetPixel(0, 0), Color<>(1, 1, 1, 1));
        EXPECT_EQ(image->GetPixel(0, 1), Color<>(1, 0, 0, 1));
        EXPECT_EQ(image->GetPixel(1, 0), Color<>(0, 1, 0, 1));
        EXPECT_EQ(image->GetPixel(1, 1), Color<>(0, 0, 1, 1));
    }
}