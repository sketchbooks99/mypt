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

class BVH : public Primitive {
public:
    BVH(std::vector<std::shared_ptr<Primitive>>& p, int start, int end);
    virtual bool intersect(const Ray& r, double tmin, double tmax, HitRecord& rec) const;
    virtual AABB bounding() const;
    void outBVH() {}
private:
    void build(std::vector<std::shared_ptr<Primitive>>& p, int start, int end);
    std::shared_ptr<Primitive> left;
    std::shared_ptr<Primitive> right;
    AABB box;
};

BVH::BVH(std::vector<std::shared_ptr<Primitive>>& p, int start, int end) {
    int axis = random_int(0, 2);
    auto compare_axis = (axis == 0) ? box_x_compare
                      : (axis == 1) ? box_y_compare
                                    : box_z_compare;

    int primitive_span = end - start;

    if (primitive_span == 1) {
        left = right = p[start];
    } else if (primitive_span == 2) {
        if (compare_axis(p[start], p[start+1])) {
            left = p[start];
            right = p[start+1];
        } else {
            left = p[start+1];
            right = p[start];
        }
    } else {
        std::sort(p.begin() + start, p.begin() + end, compare_axis);

        auto mid = start + primitive_span/2;
        left = std::make_shared<BVH>(p, start, mid);
        right = std::make_shared<BVH>(p, mid, end);
    }

    AABB box_left, box_right;
    box_left = left->bounding();
    box_right = right->bounding();

    box = surrounding(box_left, box_right);
}

// bool BVH::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
//     bool hit = false;
//     std::vector<std::shared_ptr<BVHNode>> nodeToVisit; // Node stack to visit
//     nodeToVisit.emplace_back(nodes); // Push root node for node stack

//     // Depth-first-search of BVH Node using stack
//     while(true) {
//         auto node = nodeToVisit.back();
//         if(node->box.intersect(r, t_min, t_max)) {
//             // Intersection test for primitive (leaf node)
//             if(node->primitiveIndex >= 0) {
//                 if(primitives[node->primitiveIndex]->intersect(r, t_min, t_max, rec)) {
//                     hit = true;
//                     break;
//                 }
//                 if(nodeToVisit.empty()) break;
//             } else {
//                 if(node->right != nullptr && node->right->box.intersect(r, t_min, t_max))
//                     nodeToVisit.emplace_back(node->right);
//                 if(node->left != nullptr && node->left->box.intersect(r, t_min, t_max)) 
//                     nodeToVisit.emplace_back(node->left);
//             }
//         } else {
//             if(nodeToVisit.empty()) break;
//             nodeToVisit.pop_back();
//         }
//     }
//     return hit;
// }

bool BVH::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    if(!box.intersect(r, t_min, t_max))
        return false;
    
    bool hit_left = left->intersect(r, t_min, t_max, rec);
    bool hit_right = right->intersect(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left | hit_right;
}

AABB BVH::bounding() const {
    return box;
}

// void BVH::outBVH(){
//     std::vector<std::shared_ptr<BVHNode>> nodeToVisit;
//     nodeToVisit.emplace_back(nodes);

//     while(true) {
//         if(nodeToVisit.empty()) break;
//         auto node = nodeToVisit.back();
//         nodeToVisit.pop_back();
//         std::cout << "index: " << node->primitiveIndex << ", " << std::flush;
//         std::cout << "BOX min: " << node->box._min << ", max: " << node->box._max << "\n" << std::flush;
//         if(node->primitiveIndex < 0) {
//             nodeToVisit.emplace_back(node->left);
//             nodeToVisit.emplace_back(node->right);
//         }
//     }
// }

#endif
