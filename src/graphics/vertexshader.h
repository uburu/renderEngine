#ifndef UBURU_RENDERENGINE_VERTEXSHADER_H
#define UBURU_RENDERENGINE_VERTEXSHADER_H

#include "shader.h"
#include "math/matrix4x4.h"

class VertexShader : public Shader {
    VertexShader(
        const Matrix4x4<> &viewport, 
        const Matrix4x4<> &projection, 
        const Matrix4x4<> &modelview
    );

protected:
    const Matrix4x4<> &viewport;
    const Matrix4x4<> &projection;
    const Matrix4x4<> &modelview;
};

#endif // UBURU_RENDERENGINE_VERTEXSHADER_H