#include "shader.h"

Shader::~Shader() {}

void Shader::SetMesh(std::shared_ptr<Mesh> mesh) {
    this->mesh = mesh;
}