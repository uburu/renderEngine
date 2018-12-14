#ifndef UBURURENDERENGINE_OBJMESH_H
#define UBURURENDERENGINE_OBJMESH_H

#include <memory>

#include "mesh.h"
#include <stdexcept>
#include <fstream>

class ObjMesh : public Mesh {
 public:
  ObjMesh(std::string_view id);
  ObjMesh(std::string_view id, const std::vector<Vector3d<double>> &, const std::vector<Face> &);
  ObjMesh(std::string_view id, std::vector<Vector3d<double>> &&, std::vector<Face> &&);

  virtual size_t           GetVertexCount() const override;
  virtual Vector3d<double> GetVertexPosition(VertexIndex) const override;
  virtual void             SetVertexPosition(VertexIndex, const Vector3d<double> &) override;

  virtual size_t GetFaceCount() const override;
  virtual Face   GetFace(FaceIndex) const override;

  static std::shared_ptr<ObjMesh> LoadFromFile(std::string_view id, std::string_view path);

 private:
  std::vector<Vector3d<double>> _vertex_positions;
  std::vector<Face>             _faces;
};

#endif //UBURURENDERENGINE_OBJMESH_H
