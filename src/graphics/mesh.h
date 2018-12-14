#ifndef UBURU_RENDERENGINE_MESH_H
#define UBURU_RENDERENGINE_MESH_H

#include <vector>

#include "scenenode.h"
#include "math/vector3d.h"

using VertexIndex = size_t;
using FaceIndex = size_t;
using Face = std::vector<VertexIndex>;


class Mesh : public SceneNode {
public:
    Mesh(std::string_view id);

    virtual void Accept(SceneGraphVisitor &) override;

    virtual size_t GetVertexCount() const = 0;
    virtual Vector3d<double> GetVertexPosition(VertexIndex) const = 0; 
    virtual void SetVertexPosition(VertexIndex, const Vector3d<double> &) = 0; 

    virtual size_t GetFaceCount() const = 0;
    virtual Face GetFace(FaceIndex) const = 0;
};

#endif // UBURU_RENDERENGINE_MESH_H