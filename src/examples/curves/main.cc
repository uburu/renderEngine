#include <iostream>
#include <vector>

#include "math/nurbs.h"
#include "math/vector3d.h"
#include "graphics/canvastga.h"

int main() {
    std::vector<Vector3d<>> control_points = {
        Vector3d(100., 100., 1.),
        Vector3d(200., 300., 1.),
        Vector3d(350., 100., 1.),
        Vector3d(500., 300., 1.),
        Vector3d(600., 100., 1.)
    };
    
    CanvasTGA canvas(800, 800);

    Color<> control_point_color(255, 0, 0, 255);
    for(auto &&point : control_points) canvas.DrawPoint(point.Rounded<int>(), control_point_color);

    HomogeneousWeights weights(control_points.size(), 1.0);
    weights[1] = 6; // VARY
    weights[2] = 4; // VARY
    weights[3] = 1; // VARY

    auto curve = RBSpline(3, 100, control_points, weights);

    Color<> curve_point_color(0, 0, 255, 255);

    size_t i = 0;
    for(auto &&point : curve) {
        std::cout << "index: " << i++ << " / v: " << point.x() << ' ' << point.y() << ' ' << point.z() << std::endl;
        canvas.DrawPoint(point.Rounded<int>(), curve_point_color);
    }

    canvas.Flush();
    return 0;
}