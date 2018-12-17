#ifndef UBURU_RENDERENGINE_SHADER_H
#define UBURU_RENDERENGINE_SHADER_H

#include "math/vector4d.h"
#include "math/vector3d.h"
#include "math/color.h"
#include "mesh.h"

class Shader {
public:
    Shader();

    virtual ~Shader();

    void SetMesh(Mesh &);

    virtual Vector4d<> Vertex(FaceIndex, VertexIndex) = 0;

    virtual bool Fragment(const Vector3d<> &bar, Color<> &) = 0;

    virtual const Matrix<> &GetVaryingTri() const = 0;

protected:
    Mesh *mesh;
};

#endif // UBURU_RENDERENGINE_SHADER_H