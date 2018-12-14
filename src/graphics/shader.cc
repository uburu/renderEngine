#include "shader.h"

Shader::~Shader() {}

bool Shader::WillDiscard(const Vector4d<> &) const {
    return false;
}