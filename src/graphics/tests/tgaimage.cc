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

        image.SetPixel(0, 0, Color<>(255, 255, 255, 255));
        image.SetPixel(0, 1, Color<>(255, 0, 0, 255));
        image.SetPixel(1, 0, Color<>(0, 255, 0, 255));
        image.SetPixel(1, 1, Color<>(0, 0, 255, 255));
        image.WriteToFile(CMAKE_SOURCE_DIR "/src/graphics/tests/resources/square.tga");
    }

    {
        auto image = TGAImage::LoadFromFile(CMAKE_SOURCE_DIR "/src/graphics/tests/resources/square.tga");

        EXPECT_EQ(image->GetPixel(0, 0), Color<>(255, 255, 255, 255));
        EXPECT_EQ(image->GetPixel(0, 1), Color<>(255, 0, 0, 255));
        EXPECT_EQ(image->GetPixel(1, 0), Color<>(0, 255, 0, 255));
        EXPECT_EQ(image->GetPixel(1, 1), Color<>(0, 0, 255, 255));
    }
}

TEST(TestTGAImage, TestRedSquare) {
    TGAImage image(1024, 1024, TGAImage::kRGBA);

    for(size_t i = 0, j = 0; i < 1024; ++i) {
        for(j = 0; j < 1024; ++j) {
            if(i < 512 && j < 512) image.SetPixel(i, j, Color<>(255, 0, 0, 255));
            else if(i < 512 && j >= 512) image.SetPixel(i, j, Color<>(0, 255, 0, 255));
            else if(i >= 512 && j < 512) image.SetPixel(i, j, Color<>(0, 0, 255, 255));
            else image.SetPixel(i, j, Color<>(255, 255, 255, 255));
        }
    }

    image.WriteToFile(CMAKE_SOURCE_DIR "/src/graphics/tests/resources/big_square.tga");
}