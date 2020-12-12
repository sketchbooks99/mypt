#include "BVH.h"

namespace mypt {

BVH::BVH(std::vector<std::shared_ptr<Primitive>>& p, int start, int end, 
         int axis, SplitMethod splitMethod) {
    auto compare_axis = (axis == 0) ? box_x_compare
                      : (axis == 1) ? box_y_compare
                                    : box_z_compare;

    int primitive_span = end - start;

    std::sort(p.begin() + start, p.begin() + end, compare_axis);

    // Create leaf node with primitives
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
    } else if (primitive_span > 0) {
        switch(splitMethod) {
        case SplitMethod::MIDDLE: {
            auto mid = start + primitive_span/2;
            left = std::make_shared<BVH>(p, start, mid, axis, splitMethod);
            right = std::make_shared<BVH>(p, mid, end, axis, splitMethod);
            break;
        }
        case SplitMethod::SAH: {
            int splitIndex = 1;
            double bestCost = std::numeric_limits<double>::infinity();
            // AABB for calculating temporal surface area.
            AABB s1box, s2box;
            // vector to store surface areas.
            std::vector<double> s1SA(primitive_span), s2SA(primitive_span);
            // Store surface area of left side at every case
            for(int i=1; i<primitive_span; i++) {
                s1box = surrounding(s1box, p[i+start]->bounding());
                s1SA[i] = s1box.surface_area();
            }
            // Store surface area of right side at every case
            for(int i=primitive_span-1; i>0; i--) {
                s2box = surrounding(s2box, p[i+start]->bounding());
                s2SA[i] = s2box.surface_area();
                double cost = s1SA[i]*(i+1) + s2SA[i]*(primitive_span-i);
                // Update best cost of Surface Area Heuristic.
                if(cost < bestCost) {
                    bestCost = cost;
                    splitIndex = i+start;
                }
            }
            
            left = std::make_shared<BVH>(p, start, splitIndex, axis, splitMethod);
            right = std::make_shared<BVH>(p, splitIndex, end, axis, splitMethod);
            break;
        }
        }
    }

    AABB box_left, box_right;
    box_left = left->bounding();
    box_right = right->bounding();

    box = surrounding(box_left, box_right);
}

bool BVH::intersect(Ray& r, double t_min, double t_max, HitRecord& rec) const {
    if(!box.intersect(r, t_min, t_max))
        return false;
    
    bool hit_left = left->intersect(r, t_min, t_max, rec);
    bool hit_right = right->intersect(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left | hit_right;
}

AABB BVH::bounding() const {
    return box;
}

}