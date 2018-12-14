#ifndef UBURU_RENDERENGINE_GOURAUDFRAGMENTSHADER_H
#define UBURU_RENDERENGINE_GOURAUDFRAGMENTSHADER_H

#include "fragmentshader.h"
#include "math/vector4d.h"

class GouraudFragmentShader : public FragmentShader {
public:
    GouraudFragmentShader();

    virtual void operator()(Vector4d<> &position, Vector3d<> &normal, Color<> &color) override;

    virtual bool WillDiscard(const Vector4d<> &position) const override;
    virtual void AcceptVertexShader(const VertexShader &) override;
    virtual void NextFace() override;

private:
    Vector4d<> _intensity;

    size_t _component;
};

#endif // UBURU_RENDERENGINE_GOURAUDFRAGMENTSHADER_H