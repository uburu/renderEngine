#include "canvastga.h"
#include "shader.h"

#include <gtest/gtest.h>

class TestShader : public Shader {
 public:
  TestShader() = default;
  void operator()(Vector4d<> &position, Vector3d<> &normal, Color<> &color) { }
};

TEST(CanvasTGA, BasicTests) {
  CanvasTGA canvas(1000, 1000);
  //canvas.DrawLine(Vector3d<int> (0, 0, 0), Vector3d<int> (100, 150, 100), Color<>(0, 0, 0, 255));
  canvas.DrawFace(TestShader (), Vector3d (0, 0, 0), Vector3d (10, 10, 10), Vector3d (0, 40, 50));
  canvas.Flush();
}
