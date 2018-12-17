#include "renderer.h"

#include <chrono>

#include "canvastga.h"
#include "defaultshader.h"

Renderer::Renderer() 
: pipeline(
    std::make_shared<CanvasTGA>(800, 800),
    std::make_shared<DefaultShader>(),
    std::make_shared<SceneGraph>("root")
), fps(0)
{}

void Renderer::AddMesh(std::shared_ptr<Mesh> mesh) {
    pipeline.GetSceneGraph()->AddNode(mesh);
}

void Renderer::Render() {
    using namespace std::chrono;
    static constexpr double ONE_SECOND = 1000;

    auto start_time = high_resolution_clock::now();

    pipeline.Draw();

    auto end_time = high_resolution_clock::now();

    fps = ONE_SECOND / duration_cast<milliseconds>(end_time - start_time).count();
}

double Renderer::GetFPS() const {
    return fps;
}