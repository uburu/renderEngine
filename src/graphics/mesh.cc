#include "mesh.h"
#include "scenegraphvisitor.h"

Mesh::Mesh(std::string_view id) 
: SceneNode(id)
{}

void Mesh::Accept(SceneGraphVisitor &visitor) {
    visitor.Visit(*this);
}

Vector3d<> Mesh::GetVertexPositionInFace(FaceIndex face_index, size_t vertex_number) const {
    auto face = GetFace(face_index);
    return GetVertexPosition(face[vertex_number]);
}