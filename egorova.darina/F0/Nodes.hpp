#ifndef NODES_HPP
#define NODES_HPP

#include <string>
#include <vector>
#include "TranslationList.hpp"

class Node {
public:
    virtual ~Node() {}
    virtual bool isLeaf() const = 0;
};

class InternalNode : public Node {
public:
    InternalNode() {}
    bool isLeaf() const override { return false; }

    std::vector<std::string> mKeys;
    std::vector<Node*> mChildren;
};

class LeafNode : public Node {
public:
    explicit LeafNode(const std::string& key) : mKey(key) {}
    bool isLeaf() const override { return true; }

    std::string mKey;
    TranslationList mData;
};

#endif
