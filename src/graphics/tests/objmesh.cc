#include "objmesh.h"

#include <gtest/gtest.h>

TEST(ObjMesh, BasicTests) {
  auto objMesh = ObjMesh::LoadFromFile("1", CMAKE_SOURCE_DIR "/src/graphics/tests/resources/triangle.obj");
  Face face = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}};

  EXPECT_EQ(objMesh->GetVertexCount(), 3);
  EXPECT_EQ(objMesh->GetFaceCount(), 1);

  EXPECT_EQ(objMesh->GetVertexPosition(0), Vector3d(1.0, 1.0, 1.0));
  EXPECT_EQ(objMesh->GetVertexPosition(1), Vector3d(2.0, 2.0, 1.0));
  EXPECT_EQ(objMesh->GetVertexPosition(2), Vector3d(3.0, 4.0, 2.0));
  EXPECT_EQ(objMesh->GetFace(0), face);
}
