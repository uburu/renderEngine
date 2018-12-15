#ifndef UBURU_RENDERENGINE_NURBS_H
#define UBURU_RENDERENGINE_NURBS_H

#include <vector>

#include "vector3d.h"

using KnotVector         = std::vector<int>;
using RationalBasis      = std::vector<double>;
using HomogeneousWeights = std::vector<double>;
using Curve              = std::vector<Vector3d<double>>;

KnotVector Knot(unsigned int defining_polygon_vertices_count, int basis_function_order);

RationalBasis RationalBasisFunctions(
    int basis_function_order, 
    double t,
    int defining_polygon_vertices_count, 
    const KnotVector &,
    const HomogeneousWeights &
);

Curve RBSpline( 
    int basis_function_order,
    size_t curve_points_number,
    const std::vector<Vector3d<double>> &defining_polygon_vertices,
    const HomogeneousWeights &
);

#endif // UBURU_RENDERENGINE_NURBS_H