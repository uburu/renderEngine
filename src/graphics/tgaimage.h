//
// Created by Иван Морозов on 14.12.2018.
//

#ifndef UBURURENDERENGINE_TGAIMAGE_H
#define UBURURENDERENGINE_TGAIMAGE_H

#include <fstream>
#include <memory>
#include <string_view>
#include <stdexcept>

#include "math/color.h"

#pragma pack(push,1)
struct TGAHeader {
  char idlength;
  char colormaptype;
  char datatypecode;
  short colormaporigin;
  short colormaplength;
  char colormapdepth;
  short x_origin;
  short y_origin;
  short width;
  short height;
  char  bitsperpixel;
  char  imagedescriptor;
};
#pragma pack(pop)

class TGAImage {
 public:
  enum Format {
    kGrayScale = 1,
    kRGB = 3,
    kRGBA = 4
  };

  enum Compression {
    kNone = 0,
    kRLE
  };

  TGAImage();
  TGAImage(int width, int height, int bpp);
  TGAImage(const TGAImage &);
  TGAImage(TGAImage &&);
  ~TGAImage();

  TGAImage &operator=(const TGAImage &);
  TGAImage &operator=(TGAImage &&);

  void FlipHorizontally();
  void FlipVertically();
  void Scale(int kw, int kh);

  Color<unsigned char> GetPixel(int x, int y) const;
  void SetPixel(int x, int y, const Color<unsigned char> c);

  int GetWidth() const;
  int GetHeight() const;

  void Clear();

  void WriteToFile(std::string_view path, Compression = kRLE);

  static std::shared_ptr<TGAImage> LoadFromFile(std::string_view path);

 protected:
  unsigned char *data;
  int width;
  int height;
  int bytespp;

//  bool LoadDataRLE(std::ifstream &in);
//  bool UnloadDataRLE(std::ofstream &out);
};

};

#endif //UBURURENDERENGINE_TGAIMAGE_H
