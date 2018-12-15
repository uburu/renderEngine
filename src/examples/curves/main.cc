#include <iostream>

#include "math/vector3d.h"
#include "graphics/canvastga.h"

int main() {
    CanvasTGA canvas(512, 512);

    canvas.DrawLine(Vector3d(0, 0, 0), Vector3d(50, 30, 0), Color<>(255, 0, 0, 255));

    return 0;
}