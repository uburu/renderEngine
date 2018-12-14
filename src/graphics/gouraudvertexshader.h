#ifndef UBURU_RENDERENGINE_GOURAUDVERTEXSHADER_H
#define UBURU_RENDERENGINE_GOURAUDVERTEXSHADER_H

#include "vertexshader.h"
#include "math/vector3d.h"

class GouraudVertexShader : public VertexShader {
public:
    GouraudVertexShader(
        const Matrix4x4<> &viewport, 
        const Matrix4x4<> &projection, 
        const Matrix4x4<> &modelview
    );

    virtual void operator()(Vector4d<> &position, Vector3d<> &normal, Color<> &color) override;

    double GetIntensity() const;

private:
    double intensity;

    const Vector3d<> kLightDirection;
};

#endif // UBURU_RENDERENGINE_GOURAUDVERTEXSHADER_H