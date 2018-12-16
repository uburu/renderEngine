#ifndef UBURU_RENDERENGINE_MESH_H
#define UBURU_RENDERENGINE_MESH_H

#include <vector>

#include "scenenode.h"
#include "tgaimage.h"
#include "math/vector3d.h"
#include "math/vectoruv.h"
#include "math/color.h"

using VertexIndex = size_t;
using UVIndex = size_t;
using NormalIndex = size_t;
using FaceIndex = size_t;

struct FaceElement {
    FaceElement(VertexIndex, UVIndex, NormalIndex);

    bool operator==(const FaceElement &) const;
    bool operator!=(const FaceElement &) const;

    VertexIndex vertex;
    UVIndex     uv;
    NormalIndex normal;
};

using Face = std::vector<FaceElement>;

class Mesh : public SceneNode {
public:
    Mesh(std::string_view id);

    virtual void Accept(SceneGraphVisitor &) override;

    virtual size_t GetVertexCount() const = 0;
    virtual Vector3d<double> GetVertexPosition(VertexIndex) const = 0; 
    virtual void SetVertexPosition(VertexIndex, const Vector3d<double> &) = 0;
    virtual VectorUV<> GetVertexUV(VertexIndex) const = 0;
    virtual Vector3d<> GetVertexNormal(VertexIndex) const = 0;

    virtual size_t GetFaceCount() const = 0;
    virtual Face GetFace(FaceIndex) const = 0;

    virtual std::shared_ptr<TGAImage> GetDiffuseMap() const = 0;

    Vector3d<> GetVertexPositionInFace(FaceIndex, size_t vertex_number) const;
    VectorUV<> GetVertexUVInFace(FaceIndex, size_t vertex_number) const;
    Vector3d<> GetVertexNormalInFace(FaceIndex, size_t vertex_number) const;
    Color<> GetDiffuseColor(VectorUV<>) const;
};

#endif // UBURU_RENDERENGINE_MESH_H