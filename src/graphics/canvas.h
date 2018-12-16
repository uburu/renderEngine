//
// Created by Иван Морозов on 14.12.2018.
//

#ifndef UBURURENDERENGINE_CANVAS_H
#define UBURURENDERENGINE_CANVAS_H

#include <vector>
#include "math/vector3d.h"
#include "math/color.h"

using DepthBuffer = std::vector<double>;
constexpr int kDepthBufferNoValue = std::numeric_limits<int>::min();

class Shader;

class Canvas {
 public:
  Canvas(int width, int height);

  virtual ~Canvas();

  virtual void DrawPoint(const Vector3d<int> &, const Color<> &) = 0;
  virtual void DrawLine(Vector3d<int>, Vector3d<int>, const Color<> &) = 0;
  virtual void DrawFace(Vector3d<int>, Vector3d<int>, Vector3d<int> ) = 0;
  virtual void DrawFace(Shader &shader, const Matrix<> &pts, const Vector3d<> &depth) = 0;
  virtual void Flush() = 0;

 protected:
  virtual void InitializeDepthBuffer();

  int width, height;
  DepthBuffer depth_buffer;
};

#endif //UBURURENDERENGINE_CANVAS_H
