#include "mesh.h"
#include "scenegraphvisitor.h"

Mesh::Mesh(std::string_view id) 
: SceneNode(id)
{}

void Mesh::Accept(SceneGraphVisitor &visitor) {
    visitor.Visit(*this);
}