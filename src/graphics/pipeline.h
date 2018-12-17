#ifndef UBURU_RENDERENGINE_PIPELINE_H
#define UBURU_RENDERENGINE_PIPELINE_H

#include <memory>

#include "canvas.h"
#include "scenegraph.h"
#include "math/matrix4x4.h"

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
        std::shared_ptr<Shader>,
        std::shared_ptr<SceneGraph>
    );

    std::shared_ptr<Canvas> GetCanvas() const;
    void SetCanvas(std::shared_ptr<Canvas>);

    std::shared_ptr<Shader> GetShader() const;
    void SetShader(std::shared_ptr<Shader>);

    std::shared_ptr<SceneGraph> GetSceneGraph() const;
    void SetSceneGraph(std::shared_ptr<SceneGraph>);
    
    virtual void Draw();

protected:
    std::shared_ptr<Canvas>         _canvas;
    std::shared_ptr<Shader>         _shader;
    std::shared_ptr<SceneGraph>     _scene_graph;
    Matrix4x4<> viewport;
};

#endif // UBURU_RENDERENGINE_PIPELINE_H