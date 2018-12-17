#include "defaultshader.h"
#include "math/transform.h"

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
    varying_uv.At(0, vertex_i) = uv.u();
    varying_uv.At(1, vertex_i) = uv.v();

    // TODO normals


    Vector4d<> gl_vertex = projection*modelview*Vector4d<>(this->mesh->GetVertexPositionInFace(face_index, vertex_i)).w(1);
    varying_tri.At(0, vertex_i) = gl_vertex.x();
    varying_tri.At(1, vertex_i) = gl_vertex.y();
    varying_tri.At(2, vertex_i) = gl_vertex.z();
    varying_tri.At(3, vertex_i) = gl_vertex.w();

    // auto ndc_vertex = gl_vertex / gl_vertex.w();
    // ndc_tri.At(0, vertex_i) = ndc_vertex.x();
    // ndc_tri.At(1, vertex_i) = ndc_vertex.y(); 
    // ndc_tri.At(2, vertex_i) = ndc_vertex.z();

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