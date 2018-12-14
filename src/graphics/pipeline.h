#ifndef UBURU_RENDERENGINE_PIPELINE_H
#define UBURU_RENDERENGINE_PIPELINE_H

#include <memory>

#include "canvas.h"
#include "vertexshader.h"
#include "fragmentshader.h"
#include "scenegraph.h"

#include "scenegraphvisitor.h"

class Pipeline {
public:
    class DrawVisitor : public SceneGraphVisitor {
    public:
        DrawVisitor(Pipeline &);
        virtual void Visit(Mesh &) override;

    private:
        Pipeline &_pipeline;
    };

    Pipeline(
        std::shared_ptr<Canvas>,
        std::shared_ptr<VertexShader>,
        std::shared_ptr<FragmentShader>,
        std::shared_ptr<SceneGraph>
    );

    std::shared_ptr<Canvas> GetCanvas() const;
    void SetCanvas(std::shared_ptr<Canvas>);

    std::shared_ptr<VertexShader> GetVertexShader() const;
    void SetVertexShader(std::shared_ptr<VertexShader>);

    std::shared_ptr<FragmentShader> GetFragmentShader() const;
    void SetFragmentShader(std::shared_ptr<FragmentShader>);

    std::shared_ptr<SceneGraph> GetSceneGraph() const;
    void SetSceneGraph(std::shared_ptr<SceneGraph>);

    void Render();
    virtual double GetFPS() const;

protected:
    virtual void Draw();

    std::shared_ptr<Canvas>         _canvas;
    std::shared_ptr<VertexShader>   _vertex_shader;
    std::shared_ptr<FragmentShader> _fragment_shader;
    std::shared_ptr<SceneGraph>     _scene_graph;

    double _fps;
};

#endif // UBURU_RENDERENGINE_PIPELINE_H