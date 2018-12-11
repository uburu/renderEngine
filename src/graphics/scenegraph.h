#ifndef UBURU_RENDERENGINE_SCENEGRAPH_H
#define UBURU_RENDERENGINE_SCENEGRAPH_H

#include <memory>
#include <vector>
#include <stdexcept>

#include "scenenode.h"

class NodeAlreadyInGraphException : public std::logic_error {
public:
    NodeAlreadyInGraphException(std::string_view node_id);
};

class SceneGraph : public SceneNode {
public:
    SceneGraph(std::string_view id);

    virtual void Accept(SceneGraphVisitor &) override;

    void AddNode(std::shared_ptr<SceneNode>);
    bool RemoveNode(std::string_view node_id);
    bool RemoveNode(std::shared_ptr<SceneNode>);
    bool ContainsNode(std::string_view node_id) const;
    bool ContainsNode(std::shared_ptr<SceneNode>) const;

private:
    std::vector<std::shared_ptr<SceneNode>> nodes;
};

#endif // UBURU_RENDERENGINE_SCENEGRAPH_H