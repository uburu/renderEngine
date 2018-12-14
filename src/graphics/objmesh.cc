#include <sstream>
#include "objmesh.h"

ObjMesh::ObjMesh(std::string_view id) : Mesh(id) {}

ObjMesh::ObjMesh(std::string_view id,
                 const std::vector<Vector3d<double>> &vertex_positions,
                 const std::vector<Face> &faces) : Mesh(id),
                                                   _vertex_positions(vertex_positions),
                                                   _faces(faces) {}

ObjMesh::ObjMesh(std::string_view id, std::vector<Vector3d<double>> &&vertex_positions, std::vector<Face> &&faces)
    : Mesh(id),
      _vertex_positions(std::move(vertex_positions)),
      _faces(std::move(faces)) {}

size_t ObjMesh::GetVertexCount() const {
  return _vertex_positions.size();
}

Vector3d<double> ObjMesh::GetVertexPosition(VertexIndex index) const {
  return _vertex_positions[index];
}

void ObjMesh::SetVertexPosition(VertexIndex index, const Vector3d<double> &vertex_position) {
  _vertex_positions[index] = vertex_position;
}

size_t ObjMesh::GetFaceCount() const {
  return _faces.size();
}

Face ObjMesh::GetFace(FaceIndex index) const {
  return _faces[index];
}

std::shared_ptr<ObjMesh> ObjMesh::LoadFromFile(std::string_view id, std::string_view path) {
  std::vector<Vector3d<double>> vertex_positions;
  std::vector<Face> faces;

  std::ifstream in;
  in.open(path.data(), std::ifstream::in);
  if (in.fail()) throw std::runtime_error("Can't open file");
  std::string line;
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line);
    char trash;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      Vector3d<> v;
      for (int i = 0; i < 3; ++i) iss >> v.RawData()[i];
      vertex_positions.push_back(v);
    } else if (!line.compare(0, 2, "f ")) {
      std::vector<FaceIndex> f;
      int itrash, idx;
      iss >> trash;

      while (iss >> idx >> trash >> itrash >> trash >> itrash) {
        idx--; // in wavefront obj all indices start at 1, not zero
        f.push_back(static_cast<FaceIndex>(idx));
      }
      faces.push_back(f);
    }
  }

  return std::make_shared<ObjMesh>(id, std::move(vertex_positions), std::move(faces));
}
