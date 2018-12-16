#include "defaultshader.h"
#include "math/Transform.h"

DefaultShader::DefaultShader() 
: Shader(), 
varying_uv(2, 3),
varying_tri(4, 3),
varying_nrm(3, 3),
ndc_tri(3, 3),
light_dir(1, 1, 1),
eye(1, 1, 3),
center(0, 0, 0),
up(0, 1, 0),
projection(Transform().Projection(-1.0/(eye-center).Length())),
modelview(Transform().LookAt(eye, center, up))
{}

Vector4d<> DefaultShader::Vertex(FaceIndex face_index, size_t vertex_i) {
    assert(this->mesh != nullptr);

    auto uv = this->mesh->GetVertexUVInFace(face_index, vertex_i);
    varying_uv.At(vertex_i, 0) = uv.u();
    varying_uv.At(vertex_i, 1) = uv.v();

    // TODO normals

    Vector4d<> gl_vertex = projection*modelview*this->mesh->GetVertexPositionInFace(face_index, vertex_i);
    varying_tri.At(vertex_i, 0) = gl_vertex.x();
    varying_tri.At(vertex_i, 1) = gl_vertex.y();
    varying_tri.At(vertex_i, 2) = gl_vertex.z();
    varying_tri.At(vertex_i, 3) = gl_vertex.w();

    auto ndc_vertex = gl_vertex / gl_vertex.w();
    ndc_tri.At(vertex_i, 0) = ndc_vertex.x();
    ndc_tri.At(vertex_i, 1) = ndc_vertex.y(); 
    ndc_tri.At(vertex_i, 2) = ndc_vertex.z(); 
    ndc_tri.At(vertex_i, 3) = ndc_vertex.w();

    return gl_vertex;
}

bool DefaultShader::Fragment(const Vector3d<> &bar, Color<> &color) {
    VectorUV<> uv = varying_uv*bar;
    color = mesh->GetDiffuseColor(uv);

    return false;
}

const Matrix<> &DefaultShader::GetVaryingTri() const {
    return varying_tri;
}