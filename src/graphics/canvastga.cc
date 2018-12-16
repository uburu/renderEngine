#include "canvastga.h"

#include <limits>

#include "shader.h"
#include "math/vector2d.h"
#include "math/util.h"

CanvasTGA::CanvasTGA(int width, int height)
    : Canvas(width, height),
      _image(std::make_shared<TGAImage>(width, height, TGAImage::kRGBA)) {
}

CanvasTGA::CanvasTGA(std::shared_ptr<TGAImage> image)
    : Canvas(image->GetWidth(), image->GetHeight()), _image(std::move(image)) {}

std::shared_ptr<TGAImage> CanvasTGA::GetTGAImage() const {
  return _image;
}

void CanvasTGA::SetTGAImage(std::shared_ptr<TGAImage> image) {
  _image = std::move(image);
}

void CanvasTGA::DrawPoint(const Vector3d<int> &point, const Color<> &color) {
  _image->SetPixel(point.x(), point.y(), color);
}

void CanvasTGA::DrawLine(Vector3d<int> point1, Vector3d<int> point2, const Color<> &color) {
  bool steep = false;
  if (std::abs(point1.x() - point2.x()) < std::abs(point1.y() - point2.y())) {
    std::swap(point1.x(), point1.y());
    std::swap(point2.x(), point2.y());
    steep = true;
  }
  if (point1.x() > point2.x()) {
    std::swap(point1.x(), point2.x());
    std::swap(point1.y(), point2.y());
  }
  int dx = point2.x() - point1.x();
  int dy = point2.y() - point1.y();
  int derror2 = std::abs(dy) * 2;
  int error2 = 0;
  int y = point2.y();
  for (int x = point1.x(); x <= point2.x(); x++) {
    if (steep) {
      _image->SetPixel(y, x, color);
    } else {
      _image->SetPixel(x, y, color);
    }
    error2 += derror2;

    if (error2 > dx) {
      y += (point2.y() > point1.y() ? 1 : -1);
      error2 -= dx * 2;
    }
  }
}

void CanvasTGA::DrawFace(Vector3d<int> point1,
                         Vector3d<int> point2,
                         Vector3d<int> point3) {

  Color<> color(0, 0, 0, 255);
  // TO DO случай с вырожденными треугольниками
  if (point1.y() == point2.y() && point1.y() == point3.y()) return;
  if (point1.y() > point2.y()) std::swap(point1, point2);
  if (point1.y() > point3.y()) std::swap(point1, point3);
  if (point2.y() > point3.y()) std::swap(point2, point3);
  int total_height = point3.y() - point1.y();
  for (int i = 0; i < total_height; i++) {
    bool second_half = i > point2.y() - point1.y() || point2.y() == point1.y();
    int segment_height = second_half ? point3.y() - point2.y() : point2.y() - point1.y();
    double alpha = (double) i / total_height;
    double beta = (double) (i - (second_half ? point2.y() - point1.y() : 0))
        / segment_height; // be careful: with above conditions no division by zero here
    Vector3d<int> A = point1 + ((point3 - point1).Rounded<double>() * alpha).Rounded<int>();
    Vector3d<int> B = second_half ? point2 + ((point3 - point2).Rounded<double>() * beta).Rounded<int>() : point1
        + ((point2 - point1).Rounded<double>() * beta).Rounded<int>();
    if (A.x() > B.x()) std::swap(A, B);
    for (int j = A.x(); j <= B.x(); j++) {
      double phi = B.x() == A.x() ? 1.0 : (double) (j - A.x()) / (float) (B.x() - A.x());
      Vector3d<int> P = (Vector3d<double>(A) + Vector3d<double>(B - A) * phi).Rounded<int>();
      int idx = P.x() + P.y() * width;
      if (depth_buffer[idx] < P.z()) {
        depth_buffer[idx] = P.z();
        _image->SetPixel(P.x(), P.y(), color);
      }
    }
  }
}

void CanvasTGA::DrawFace(Shader &shader, const Matrix<> &pts, const Vector3d<> &depth) {
    Matrix<> pts2(3, 2);
    for(size_t i = 0; i < 3; ++i) { 
      pts2.At(i, 0) = pts.At(i, 0) / pts.At(i, 3);
      pts2.At(i, 1) = pts.At(i, 1) / pts.At(i, 3);
    }

    Vector2d<> bboxmin(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    Vector2d<> bboxmax(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max());
    Vector2d<> clamp(_image->GetWidth()-1, _image->GetHeight()-1);
    
    for(size_t i = 0, j = 0; i < 3; ++i) {
      for(j = 0; j < 2; ++j) {
        bboxmin.At(j) = std::max(0.0, std::min(bboxmin.At(j), pts2.At(i, j)));
        bboxmax.At(j) = std::min(clamp.At(j), std::max(bboxmax.At(j), pts2.At(i, j)));
      }
    }

    Vector2d<double> P;
    Color<> color;

    Vector3d<> bc_screen;
    Vector3d<> bc_clip;
    int screen_width = _image->GetWidth();
    for(P.x(bboxmin.x()); P.x() <= bboxmax.x(); ++P.x()) {
        for(P.y(bboxmin.y()); P.y() <= bboxmax.y(); ++P.y()) {
            bc_screen = Barycentric(
              Vector2d(pts2.At(0, 0), pts2.At(0, 1)),
              Vector2d(pts2.At(1, 0), pts2.At(1, 1)),
              Vector2d(pts2.At(2, 0), pts2.At(2, 1)),
              P
            );

            bc_clip = Vector3d(bc_screen.x() / pts.At(0, 3), bc_screen.y() / pts.At(1, 3), bc_screen.z() / pts.At(2, 3));
            bc_clip /= (bc_clip.x() + bc_clip.y() + bc_clip.z());

            double frag_depth = depth.Dot(bc_clip);
            if(bc_screen.x() < 0. || bc_screen.y() < 0. || bc_screen.z() < 0. || depth_buffer[static_cast<size_t>(P.x()*P.y()*screen_width)] > frag_depth) continue;

            if(!shader.Fragment(bc_clip, color)) {
              depth_buffer[static_cast<size_t>(P.x()+P.y()*screen_width)] = frag_depth;
              _image->SetPixel(static_cast<int>(P.x()), static_cast<int>(P.y()), color);
            }
        }
    }
}

void CanvasTGA::Flush() {
  _image->WriteToFile("./image.tga");
}


