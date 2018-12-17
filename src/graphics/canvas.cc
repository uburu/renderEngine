#include "canvas.h"

Canvas::Canvas(int width, int height)
    : width(width), height(height), depth_buffer(width * height) {}

Canvas::~Canvas() {}

int Canvas::GetWidth() const {
  return width;
}

int Canvas::GetHeight() const {
  return height;
}

void Canvas::InitializeDepthBuffer() {
  for (int i = 0; i < width * height; ++i) {
    depth_buffer.push_back(kDepthBufferNoValue);
  }
}