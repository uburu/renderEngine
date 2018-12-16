#include "pipeline.h"

#include <chrono>

Pipeline::DrawVisitor::DrawVisitor(Pipeline &pipeline)
: _pipeline(pipeline) 
{}

void Pipeline::DrawVisitor::Visit(Mesh &) {
    // TODO:
}

Pipeline::Pipeline(
        std::shared_ptr<Canvas> canvas,
        std::shared_ptr<Shader> shader,
        std::shared_ptr<SceneGraph> scene_graph
) : _canvas(canvas), _shader(shader), _scene_graph(scene_graph)
{}

std::shared_ptr<Canvas> Pipeline::GetCanvas() const {
    return _canvas;
}

void Pipeline::SetCanvas(std::shared_ptr<Canvas> canvas) {
    _canvas = canvas;
}


std::shared_ptr<Shader> Pipeline::GetShader() const {
    return _shader;
}

void Pipeline::SetShader(std::shared_ptr<Shader> shader) {
    _shader = shader;
}


std::shared_ptr<SceneGraph> Pipeline::GetSceneGraph() const {
    return _scene_graph;
}

void Pipeline::SetSceneGraph(std::shared_ptr<SceneGraph> scene_graph) {
    _scene_graph = scene_graph;
}

void Pipeline::Render() {
    using namespace std::chrono;
    static constexpr double kOneSecond = 1000.0;

    auto start_time = high_resolution_clock::now();

    Draw();

    auto end_time = high_resolution_clock::now();
    _fps = duration_cast<milliseconds>(end_time - start_time).count() / kOneSecond;
}

void Pipeline::Draw() {
    DrawVisitor drawer(*this);
    _scene_graph->Accept(drawer);
}

double Pipeline::GetFPS() const {
    return _fps;
}
