//
// Created by Иван Морозов on 14.12.2018.
//

#ifndef UBURURENDERENGINE_CANVAS_H
#define UBURURENDERENGINE_CANVAS_H

class Canvas {
 public:
  Canvas(size_t width, size_t height);

  virtual ~Canvas();

  virtual void DrawPoint(const Shader &, const Vector3d<int> &) = 0;
  virtual void DrawLine(const Shader &, const Vector3d<int> &, const Vector3d<int> &) = 0;
  virtual void DrawFace(const Shader &, const Vector3d<int> &, const Vector3d<int> &, const Vector3d<int> &) = 0;
  virtual void Flush() = 0;

 protected:
  virtual void InitializeDepthBuffer();

  size_t width, height;
  DepthBuffer depth_buffer;
};

#endif //UBURURENDERENGINE_CANVAS_H
