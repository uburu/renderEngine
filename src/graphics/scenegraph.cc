#include "scenegraph.h"

#include <algorithm>

#include "scenegraphvisitor.h"

using namespace std::string_literals;

NodeAlreadyInGraphException::NodeAlreadyInGraphException(std::string_view node_id)
: std::logic_error("Node \""s + node_id.data() + "\" already in graph")
{}

SceneGraph::SceneGraph(std::string_view id)
: SceneNode(id)
{}

void SceneGraph::Accept(SceneGraphVisitor &visitor) {
    for(auto &&child : nodes) child->Accept(visitor);
}

void SceneGraph::AddNode(std::shared_ptr<SceneNode> node) {
    if(ContainsNode(node)) throw NodeAlreadyInGraphException(node->GetId());

    nodes.push_back(node);
}

bool SceneGraph::RemoveNode(std::string_view node_id) {
    auto it = std::find_if(nodes.begin(), nodes.end(), [&](auto child) {
        return child->GetId() == node_id;
    });

    if(it != nodes.end()) {
        nodes.erase(it);
        return true;
    }
    
    for(auto &&child : nodes) {
        if(auto graph = dynamic_cast<SceneGraph *>(child.get())) {
            if(graph->RemoveNode(node_id)) return true;
        }
    }

    return false;
}


bool SceneGraph::RemoveNode(std::shared_ptr<SceneNode> node) {
    auto it = std::find_if(nodes.begin(), nodes.end(), [&](auto child) {
        return child == node;
    });

    if(it != nodes.end()) {
        nodes.erase(it);
        return true;
    }

    for(auto &&child : nodes) {
        if(auto graph = dynamic_cast<SceneGraph *>(child.get())) {
            if(graph->RemoveNode(node)) return true;
        }
    }

    return false;
}

bool SceneGraph::ContainsNode(std::string_view node_id) const {
    auto it = std::find_if(nodes.begin(), nodes.end(), [&](auto child) {
        return child->GetId() == node_id;
    });

    if(it != nodes.end()) return true;
    
    for(auto &&child : nodes) {
        if(auto graph = dynamic_cast<SceneGraph *>(child.get())) {
            if(graph->ContainsNode(node_id)) return true;
        }
    }
    
    return false;
}

bool SceneGraph::ContainsNode(std::shared_ptr<SceneNode> node) const {
    auto it = std::find_if(nodes.begin(), nodes.end(), [&](auto child) {
        return child == node;
    });

    if(it != nodes.end()) return true;
    
    for(auto &&child : nodes) {
        if(auto graph = dynamic_cast<SceneGraph *>(child.get())) {
            if(graph->ContainsNode(node)) return true;
        }
    }
    
    return false;
}