#ifndef UBURURENDERENGINE_OBJMESH_H
#define UBURURENDERENGINE_OBJMESH_H

#include <memory>
#include <stdexcept>
#include <fstream>

#include "mesh.h"
#include "math/vectoruv.h"
#include "tgaimage.h"

class ObjMesh : public Mesh {
 public:
  ObjMesh(std::string_view id);
  ObjMesh(
    std::string_view id, 
    const std::vector<Vector3d<double>> &vertices, 
    const std::vector<Vector3d<double>> &normals, 
    const std::vector<VectorUV<double>> &uvs,
    const std::vector<Face> &,
    std::shared_ptr<TGAImage> diffuse_map
  );
  ObjMesh(std::string_view id, std::vector<Vector3d<double>> &&, std::vector<Face> &&);

  virtual size_t           GetVertexCount() const override;
  virtual const Vector3d<double> &GetVertexPosition(VertexIndex) const override;
  virtual void             SetVertexPosition(VertexIndex, const Vector3d<double> &) override;
  virtual const VectorUV<> &GetVertexUV(VertexIndex) const override;
  virtual const Vector3d<> &GetVertexNormal(VertexIndex) const override;

  virtual size_t GetFaceCount() const override;
  virtual Face   GetFace(FaceIndex) const override;

  std::shared_ptr<TGAImage> GetDiffuseMap() const override;

  static std::shared_ptr<ObjMesh> LoadFromFile(std::string_view id, std::string_view path);

 private:
  std::vector<Vector3d<double>> _vertex_positions;
  std::vector<Vector3d<double>> _normals;
  std::vector<VectorUV<double>> _uvs;
  std::vector<Face>             _faces;
  std::shared_ptr<TGAImage> _diffuse_map;
};

#endif //UBURURENDERENGINE_OBJMESH_H
