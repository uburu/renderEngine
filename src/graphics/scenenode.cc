#include "scenenode.h"

static size_t default_id = 0;

SceneNode::SceneNode()
: id("node" + std::to_string(default_id++))
{}

SceneNode::SceneNode(std::string_view id)
: id(id)
{}

SceneNode::~SceneNode() {

}

const std::string &SceneNode::GetId() const {
    return id;
}

void SceneNode::SetId(std::string_view id) {
    this->id = id;
}