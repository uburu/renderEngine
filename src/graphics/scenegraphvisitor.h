#ifndef UBURU_RENDERENGINE_SCENEGRAPHVISITOR_H
#define UBURU_RENDERENGINE_SCENEGRAPHVISITOR_H

class Mesh;

class SceneGraphVisitor {
public:
    virtual ~SceneGraphVisitor() {}

    virtual void Visit(Mesh &) = 0;
};

#endif // UBURU_RENDERENGINE_SCENEGRAPHVISITOR_H