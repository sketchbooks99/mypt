#ifndef BVH_H
#define BVH_H

#include <algorithm>
#include "ShapeList.h"

inline bool box_compare(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape>b, int axis) {
    AABB box_a;
    AABB box_b;

    if(!a->bounding(0, 0, box_a) || !b->bounding(0, 0, box_b))
        std::cerr << "No bounding box in BVHNode constructor.\n";
    
    return box_a.min()[axis] < box_b.min()[axis];
}

bool box_x_compare(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return box_compare(a, b, 0);
}

bool box_y_compare(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return box_compare(a, b, 1);
}

bool box_z_compare(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) {
    return box_compare(a, b, 2);
}

class BVHNode {
    public:
        BVHNode();

        BVHNode(ShapeList& list, double time0, double time1)
            : BVHNode(list.objects, 0, list.objects.size(), time0, time1) 
        {}

        BVHNode(
            std::vector<std::shared_ptr<Shape>>& objects,
            size_t start, size_t end, double time0, double time1);

        virtual bool intersect(const Ray& r, double tmin, double tmax, HitRecord& rec) const;
        virtual bool bounding(double t0, double t1, AABB& output_box) const;

    public:
        std::shared_ptr<BVHNode> left;
        std::shared_ptr<BVHNode> right;
        AABB box;
};

BVHNode::BVHNode(
    std::vector<std::shared_ptr<Shape>>& objects,
    size_t start, size_t end, double time0, double time1
) {
    int axis = random_int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;

    if(object_span == 1) {
        left = right = objects[start];
    } else if(object_span == 2) {
        if(comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left = make_shared<BVHNode>(objects, start, mid, time0, time1);
        right = make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if( !left->bounding(time0, time1, box_left)
     || !right->bounding(time0, time1, box_right)
    )
        std::cerr << "No bounding box in BVHNode constroctor\n.";

    box = bounding(box_left, box_right);

}

bool BVHNode::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    if(!box.intersect(r, t_min, t_max))
        return false;
    
    bool intersect_left = left->intersect(r, t_min, t_max, rec);
    bool intersect_right = right->intersect(r, t_min, intersect_left ? rec.t : t_max, rec);

    return intersect_left || intersect_right;
}

bool BVHNode::bounding(double t0, double t1, AABB& output_box) const {
    output_box = box;
    return true;
}

#endif
