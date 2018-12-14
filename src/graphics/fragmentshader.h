#ifndef UBURU_RENDERENGINE_FRAGMENTSHADER_H
#define UBURU_RENDERENGINE_FRAGMENTSHADER_H

#include "shader.h"

class VertexShader;

class FragmentShader : public Shader {
public:
    virtual bool WillDiscard(const Vector4d<> &position) const = 0;
    virtual void AcceptVertexShader(const VertexShader &) = 0;
    virtual void NextFace() = 0;
};

#endif // UBURU_RENDERENGINE_FRAGMENTSHADER_H