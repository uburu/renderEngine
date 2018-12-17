#include "pipeline.h"
#include "mesh.h"
#include "shader.h"
#include "math/transform.h"

#include <iostream>

Pipeline::DrawVisitor::DrawVisitor(Pipeline &pipeline)
: _pipeline(pipeline) 
{}

void Pipeline::DrawVisitor::Visit(Mesh &mesh) {
    _pipeline._shader->SetMesh(mesh);

    size_t i = 0, j = 0;
    size_t faces_count = mesh.GetFaceCount();
    constexpr size_t kVertexInFaceCount = 3;

    for(i = 0; i < faces_count; ++i) {
        // std::cout << "face " << i << '/' << faces_count-1 << std::endl;
        for(j = 0; j < kVertexInFaceCount; ++j) {
            _pipeline._shader->Vertex(i, j);
        }

        auto pts = _pipeline.viewport*_pipeline._shader->GetVaryingTri();
        pts.Transpose();
        // std::cout << _pipeline.viewport << std::endl;
        // std::cout << _pipeline._shader->GetVaryingTri() << std::endl;
        // std::cout << pts << std::endl;


        auto &varying_tri = _pipeline._shader->GetVaryingTri();
        Vector3d<> depth(varying_tri.At(2, 0), varying_tri.At(2, 1), varying_tri.At(2, 2));

        _pipeline._canvas->DrawFace(*_pipeline._shader, pts, depth);
    } 
}

Pipeline::Pipeline(
        std::shared_ptr<Canvas> canvas,
        std::shared_ptr<Shader> shader,
        std::shared_ptr<SceneGraph> scene_graph
) : _canvas(canvas), _shader(shader), _scene_graph(scene_graph),
viewport(Transform().Viewport(canvas->GetWidth()/8, canvas->GetHeight()/8, canvas->GetWidth()*3/4, canvas->GetHeight()*3/4))
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

void Pipeline::Draw() {
    DrawVisitor drawer(*this);
    _scene_graph->Accept(drawer);

    _canvas->Flush();
}