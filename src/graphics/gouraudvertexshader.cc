#include "gouraudvertexshader.h"

GouraudVertexShader::GouraudVertexShader(
    const Matrix4x4<> &viewport, 
    const Matrix4x4<> &projection, 
    const Matrix4x4<> &modelview
) : VertexShader(viewport, projection, modelview),
intensity(0.0),
kLightDirection(1, 1, 1)
{}

void GouraudVertexShader::operator()(Vector4d<> &position, Vector3d<> &normal, Color<> &color) {
    intensity = std::max(0.0, normal.Dot(kLightDirection));

    position = viewport*projection*modelview*position;
    color    = Color<>(255, 255, 255, 255);
}

double GouraudVertexShader::GetIntensity() const {
    return intensity;
}