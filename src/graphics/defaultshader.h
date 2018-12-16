#ifndef UBURU_RENDERENGINE_DEFAULTENGINE_H
#define UBURU_RENDERENGINE_DEFAULTENGINE_H

#include "shader.h"
#include "math/matrix4x4.h"

class DefaultShader : public Shader {
public:
    DefaultShader();

    virtual Vector4d<> Vertex(FaceIndex, size_t vertex_number_in_face) override;

    virtual bool Fragment(const Vector3d<> &bar, const Color<> &) override;

private:
    Matrix<> varying_tri;
    Matrix<> ndc_tri;

    Vector3d<> light_dir;
    Vector3d<> eye, center, up;
    Matrix4x4<> projection, modelview;
};

#endif // UBURU_RENDERENGINE_DEFAULTENGINE_H