#include "canvastga.h"
#include "defaultshader.h"

#include <gtest/gtest.h>

TEST(CanvasTGA, BasicTests) {
  CanvasTGA canvas(1000, 1000);
  //canvas.DrawLine(Vector3d<int> (0, 0, 0), Vector3d<int> (100, 150, 100), Color<>(0, 0, 0, 255));
  canvas.DrawFace(DefaultShader(), Vector3d (0, 0, 0), Vector3d (10, 10, 10), Vector3d (0, 40, 50));
  canvas.Flush();
}
