#ifndef UBURU_RENDERENGINE_NURBS_H
#define UBURU_RENDERENGINE_NURBS_H

#include <vector>

#include "vector3d.h"

using HomogeneousWeights = std::vector<double>;
using Curve              = std::vector<Vector3d<double>>;

Curve RBSpline( 
    int basis_function_order,
    size_t curve_points_number,
    const std::vector<Vector3d<double>> &defining_polygon_vertices,
    const HomogeneousWeights &
);

#endif // UBURU_RENDERENGINE_NURBS_H