#ifndef UBURU_RENDERENGINE_SCENENODE_H
#define UBURU_RENDERENGINE_SCENENODE_H

#include <string>
#include <string_view>

class SceneGraphVisitor;

class SceneNode {
public:
    SceneNode();
    SceneNode(std::string_view id);
    virtual ~SceneNode();

    virtual void Accept(SceneGraphVisitor &) = 0;

    const std::string &GetId() const;
    void SetId(std::string_view);

private:
    std::string id;
};

#endif // UBURU_RENDERENGINE_SCENENODE_H