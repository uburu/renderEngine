#include "shader.h"

Shader::Shader(): mesh(nullptr) 
{}

Shader::~Shader() {}

void Shader::SetMesh(Mesh &mesh) {
    this->mesh = &mesh;
}