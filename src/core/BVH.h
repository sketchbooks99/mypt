#ifndef BVH_H
#define BVH_H

#include <algorithm>
#include "Primitive.h"

inline bool box_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b, int axis) {
    
    return a->bounding().min()[axis] < b->bounding().min()[axis];
}

bool box_x_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
    return box_compare(a, b, 2);
}

struct BVHNode {
    void createLeaf(int index, AABB b) {
        box = b;
        primitiveIndex = index;
        left = right = nullptr;
    }
    void createInterior(std::shared_ptr<BVHNode> node0, std::shared_ptr<BVHNode> node1) {
        left = node0;
        right = node1;
        box = surrounding(node0->box, node1->box);
        primitiveIndex = -1;
    }
    std::shared_ptr<BVHNode> left;
    std::shared_ptr<BVHNode> right;
    AABB box;
    int primitiveIndex;  // The index of primitives array. If index is -1, this is interior node.
};

class BVH {
public:
    BVH(std::vector<std::shared_ptr<Primitive>>& p);
    bool intersect(const Ray& r, double tmin, double tmax, HitRecord& rec) const;
    AABB bounding() const;
private:
    std::shared_ptr<BVHNode> build(int start, int end);
    std::vector<std::shared_ptr<Primitive>> primitives;
    std::shared_ptr<BVHNode> nodes;
};

BVH::BVH(std::vector<std::shared_ptr<Primitive>>& p) : primitives(std::move(p)){
    nodes = build(0, primitives.size());
}

// Recursive build of BVH
std::shared_ptr<BVHNode> BVH::build(int start, int end) {
    int axis = random_int(0, 2);
    auto compare_axis = (axis == 0) ? box_x_compare
                      : (axis == 1) ? box_y_compare
                                    : box_z_compare;

    int primitive_span = end - start;

    // Create memory for node
    std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>();

    if(primitive_span == 1) {
        node->createLeaf(start, primitives[start]->bounding());
    } else {
        std::sort(primitives.begin() + start, primitives.begin() + end, compare_axis);

        auto mid = start + primitive_span/2;
        node->createInterior(build(start, mid), build(mid, end));
    }

    return node;
}

bool BVH::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    bool hit = false;
    std::vector<std::shared_ptr<BVHNode>> nodeToVisit; // Node stack to visit
    nodeToVisit.emplace_back(nodes); // Push root node for node stack

    // Depth-first-search of BVH Node using stack
    while(true) {
        auto node = nodeToVisit.back();
        nodeToVisit.pop_back();
        if(node->box.intersect(r, t_min, t_max)) {
            // Intersection test for primitive (leaf node)
            if(node->primitiveIndex >= 0) {
                if(primitives[node->primitiveIndex]->intersect(r, t_min, t_max, rec)) {
                    hit = true;
                    break;
                }
                if(nodeToVisit.empty()) break;
            } else {
                if(node->right->box.intersect(r, t_min, t_max))
                    nodeToVisit.emplace_back(node->right);
                if(node->left->box.intersect(r, t_min, t_max)) 
                    nodeToVisit.emplace_back(node->left);
            }
        } else {
            if(nodeToVisit.empty()) break;
            nodeToVisit.pop_back();
        }
    }
    return hit;
}

AABB BVH::bounding() const {
    return nodes ? nodes->box : AABB();
}

#endif
