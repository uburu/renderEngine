#include "mesh.h"
#include "scenegraphvisitor.h"

FaceElement::FaceElement(VertexIndex v, UVIndex uv, NormalIndex n)
: vertex(v), uv(uv), normal(n) {}

bool FaceElement::operator==(const FaceElement &rhs) const {
    return vertex == rhs.vertex && uv == rhs.uv && normal == rhs.normal;
}

bool FaceElement::operator!=(const FaceElement &rhs) const {
    return !(*this == rhs);
}

Mesh::Mesh(std::string_view id) 
: SceneNode(id)
{}

void Mesh::Accept(SceneGraphVisitor &visitor) {
    visitor.Visit(*this);
}

const Vector3d<> &Mesh::GetVertexPositionInFace(FaceIndex face_index, size_t vertex_number) const {
    auto face = GetFace(face_index);
    return GetVertexPosition(face[vertex_number].vertex);
}

const VectorUV<> &Mesh::GetVertexUVInFace(FaceIndex face_index, size_t vertex_number) const {
    auto face = GetFace(face_index);
    return GetVertexUV(face[vertex_number].uv);
}

const Vector3d<> &Mesh::GetVertexNormalInFace(FaceIndex face_index, size_t vertex_number) const {
    auto face = GetFace(face_index);
    return GetVertexNormal(face[vertex_number].normal);
} 

Color<> Mesh::GetDiffuseColor(VectorUV<> uvd) const {
    auto diffuse_map = GetDiffuseMap();
    uvd.u(uvd.u()*diffuse_map->GetWidth())
       .v(uvd.v()*diffuse_map->GetHeight());

    VectorUV<int> uv(uvd.Rounded<int>());
    return diffuse_map->GetPixel(uv.u(), uv.v());
}