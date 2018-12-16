#ifndef UBURU_RENDERENGINE_RENDERER_H
#define UBURU_RENDERENGINE_RENDERER_H

#include "pipeline.h"

class Renderer {
public:
    Renderer();

    void AddMesh(std::shared_ptr<Mesh>);

    void Render();
    double GetFPS() const;

private:
    Pipeline pipeline;
    double fps;
};

#endif // UBURU_RENDERENGINE_RENDERER_H