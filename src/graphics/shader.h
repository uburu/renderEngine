#ifndef UBURU_RENDERENGINE_SHADER_H
#define UBURU_RENDERENGINE_SHADER_H

#include "math/vector4d.h"
#include "math/vector3d.h"
#include "math/color.h"
#include "mesh.h"

class Shader {
public:
    virtual ~Shader();

    void SetMesh(std::shared_ptr<Mesh>);

    virtual Vector4d<> Vertex(FaceIndex, VertexIndex) = 0;

    virtual bool Fragment(const Vector3d<> &bar, const Color<> &) = 0;

protected:
    std::shared_ptr<Mesh> mesh;
};

#endif // UBURU_RENDERENGINE_SHADER_H