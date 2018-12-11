#include "mesh.h"
#include "scenegraphvisitor.h"

void Mesh::Accept(SceneGraphVisitor &visitor) {
    visitor.Visit(*this);
}