#include <sstream>
#include "objmesh.h"
#include "math/vectoruv.h"

ObjMesh::ObjMesh(std::string_view id) : Mesh(id) {}

ObjMesh::ObjMesh(
  std::string_view id, 
    const std::vector<Vector3d<double>> &vertices, 
    const std::vector<Vector3d<double>> &normals, 
    const std::vector<VectorUV<double>> &uvs,
    const std::vector<Face> &faces,
    std::shared_ptr<TGAImage> diffuse_map
) : Mesh(id),
  _vertex_positions(vertices),
  _normals(normals),
  _uvs(uvs),
  _faces(faces),
  _diffuse_map(diffuse_map)
{}

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

VectorUV<> ObjMesh::GetVertexUV(VertexIndex index) const {
  return _uvs[index];
}

Vector3d<> ObjMesh::GetVertexNormal(VertexIndex index) const {
    return _normals[index];
}

size_t ObjMesh::GetFaceCount() const {
  return _faces.size();
}

Face ObjMesh::GetFace(FaceIndex index) const {
  return _faces[index];
}

std::shared_ptr<TGAImage> ObjMesh::GetDiffuseMap() const {
  return _diffuse_map;
}

std::shared_ptr<ObjMesh> ObjMesh::LoadFromFile(std::string_view id, std::string_view path) {
  std::vector<Vector3d<double>> vertex_positions;
  std::vector<Vector3d<double>> normals;
  std::vector<VectorUV<double>> uvs;
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
    } else if(!line.compare(0, 3, "vn ")) {
      
      iss >> trash >> trash;
      Vector3d<> normal;

      for(size_t i = 0; i < 3; ++i) iss >> normal.At(i);
      normals.push_back(normal);

    } else if(!line.compare(0, 3, "vt ")) {
      iss >> trash >> trash;
      VectorUV<> uv;
      for(int i = 0; i < 2; ++i) iss >> uv.At(i);
      uvs.push_back(uv);
    } else if (!line.compare(0, 2, "f ")) {
      Face f;
      VertexIndex v;
      UVIndex uv;
      NormalIndex n;

      iss >> trash;

      while (iss >> v >> trash >> uv >> trash >> n) {
        v--; // in wavefront obj all indices start at 1, not zero
        uv--;
        n--;
        f.push_back(FaceElement(v, uv, n));
      }
      faces.push_back(f);
    }
  }

  std::string base_name = path.data();
  base_name = base_name.substr(0, base_name.find_last_of('.'));

  return std::make_shared<ObjMesh>(
    id, 
    std::move(vertex_positions), 
    std::move(normals), 
    std::move(uvs), 
    std::move(faces),
    TGAImage::LoadFromFile(base_name + "_diffuse.tga")
  );
}
