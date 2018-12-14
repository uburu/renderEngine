#include "vertexshader.h"

VertexShader::VertexShader(
        const Matrix4x4<> &viewport, 
        const Matrix4x4<> &projection, 
        const Matrix4x4<> &modelview
) : viewport(viewport), projection(projection), modelview(modelview)
{}