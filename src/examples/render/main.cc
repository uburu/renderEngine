#include <iostream>
#include "graphics/renderer.h"
#include "graphics/objmesh.h"

int main() {
    Renderer renderer;
    renderer.AddMesh(ObjMesh::LoadFromFile("head", CMAKE_SOURCE_DIR "/src/examples/render/resources/african_head.obj"));


    renderer.Render();
    std::cout << renderer.GetFPS() << std::endl;

    return 0;
}