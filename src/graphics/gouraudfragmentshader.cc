#include "gouraudfragmentshader.h"

#include <stdexcept>

#include "gouraudvertexshader.h"

GouraudFragmentShader::GouraudFragmentShader(): _intensity(), _component(0) {}

void GouraudFragmentShader::operator()(Vector4d<> &bar_position, Vector3d<> &, Color<> &color) {
    double intensity = _intensity.Dot(bar_position);

    color.r() = static_cast<unsigned int>(color.r() * intensity);
    color.g() = static_cast<unsigned int>(color.g() * intensity);
    color.b() = static_cast<unsigned int>(color.b() * intensity);
    color.a() = static_cast<unsigned int>(color.a() * intensity);
}

bool GouraudFragmentShader::WillDiscard(const Vector4d<> &position) const {
    return false;
}

void GouraudFragmentShader::AcceptVertexShader(const VertexShader &shader) {
    // TODO: REMOVE INTERPOLATION
    // TODO: Move IT TO Pipeline::DrawVisitor::Visit !!!
    if(auto *vertex_shader = dynamic_cast<const GouraudVertexShader*>(&shader)) {
        _intensity.AsMatrix(VectorOrientation::kVertical).At(_component, 0) = vertex_shader->GetIntensity();
        ++_component;
    } else throw std::runtime_error("Incompatible vertex shader for GouraudFragmentShader");
}

void GouraudFragmentShader::NextFace() {
    _component = 0;
}