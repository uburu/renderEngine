#ifndef UBURU_RENDERENGINE_SHADER_H
#define UBURU_RENDERENGINE_SHADER_H

#include "math/Vector4d.h"
#include "math/Color.h"

class Shader {
public:
    virtual ~Shader();
    virtual void operator()(Vector4d<> &position, Vector3d<> &normal, Color<> &color) = 0;
};

#endif // UBURU_RENDERENGINE_SHADER_H