#include "nurbs.h"

using KnotVector         = std::vector<int>;
using RationalBasis      = std::vector<double>;

KnotVector Knot(unsigned int n, int c) {

    int max_value = n + c; // Maximum value of the knor vector
    int first_max_index = n + 1; // Index of x() for the first occurence of the maximum knot vector value

    KnotVector x(max_value, 0);

    for(int i = 1; i < max_value; ++i) {
        if((i+1 > c) && (i < first_max_index)) x[i] = x[i-1] + 1;
        else x[i] = x[i-1];
    }

    return x;
}

void RationalBasisFunctions(
    int c, 
    double t,
    int npts, 
    const KnotVector &x,
    const HomogeneousWeights &h,
    RationalBasis &r
) {
    int nplusc = npts + c;
    std::vector<double> temp(nplusc, 0);

    // Calculate the first order nonrational basis functions n[i]
    int i = 0;
    for(; i < nplusc; ++i) {
        if((t >= x[i]) && (t < x[i+1])) temp[i] = 1;
        else temp[i] = 0;
    }

    // Calculate the higher order nonrational basis functions
    double d = 0, e = 0;
    for(int k = 2; k <= c; ++k) {
        for(i = 0; i < nplusc - k; ++i) {

            // If the lower order basis function is zero skip the calculation
            if(temp[i] != 0) d = ((t-x[i])*temp[i])/(x[i+k-1]-x[i]);
            else d = 0;

            // if the lower order basis function is zero skip the calculation
            if(temp[i+1] != 0) e = ((x[i+k]-t)*temp[i+1])/(x[i+k]-x[i+1]);
            else e = 0;

            temp[i] = d + e;
        }
    }

    // Pick up last point
    if(t == static_cast<double>(x[nplusc - 1])) temp[npts - 1] = 1;

    double sum = 0;
    for(i = 0; i < npts; ++i) sum += temp[i]*h[i]; //???

    for(i = 0; i < npts; ++i) {
        if(sum != 0) r[i] = (temp[i]*h[i])/sum;
        else r[i] = 0;
    }
}

Curve RBSpline( 
    int k,
    size_t p1,
    const std::vector<Vector3d<double>> &b,
    const HomogeneousWeights &h
) {
    static constexpr double kEps = 5e-6;

    int npts = static_cast<int>(b.size());
    int nplusc = npts + k - 1;

    auto x = Knot(npts, k); // Generate the uniform open knot vector

    // Calculate the points on the rational B-spline curve
    double t = 0;
    double step = static_cast<double>(x[nplusc])/static_cast<double>(p1 - 1);

    Curve p(p1);
    int i = 0, j = 0, icount = 0, jcount = 0;
    double temp = 0;

    RationalBasis nbasis(npts, 0);
    for(int i1 = 0; i1 < p1; ++i1) {
        if(static_cast<double>(x[nplusc]) - t < kEps) t = static_cast<double>(x[nplusc]);

        RationalBasisFunctions(k, t, npts, x, h, nbasis);
        for(j = 0; j < 3; ++j) {
            jcount = 0;//j;
            p[icount].At(j) = 0;

            for(i = 0; i < npts; ++i) {
                temp = nbasis[i]*b[jcount].At(j);
                p[icount].At(j) += temp;

                ++jcount;
            }
        }

        ++icount;
        t += step;
    }

    return p;
}