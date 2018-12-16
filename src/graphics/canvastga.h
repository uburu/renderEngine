#ifndef UBURURENDERENGINE_CANVASTGA_H
#define UBURURENDERENGINE_CANVASTGA_H

#include "canvas.h"
#include "tgaimage.h"

class CanvasTGA : public Canvas {
 public:
  CanvasTGA(int width, int height);
  CanvasTGA(std::shared_ptr<TGAImage>);

  std::shared_ptr<TGAImage> GetTGAImage() const;
  void                      SetTGAImage(std::shared_ptr<TGAImage>);

  virtual void DrawPoint(const Vector3d<int> &, const Color<> &) override;
  virtual void DrawLine(Vector3d<int>, Vector3d<int>, const Color<> &) override;
  virtual void DrawFace(Vector3d<int>, Vector3d<int>, Vector3d<int> ) override;
  virtual void DrawFace(Shader &shader, const Matrix<> &pts, double depth) override;
  virtual void Flush() override;

 private:
  std::shared_ptr<TGAImage> _image;
};

#endif //UBURURENDERENGINE_CANVASTGA_H
