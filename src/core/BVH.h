#pragma once

#include <algorithm>
#include "Primitive.h"

namespace mypt {

inline bool box_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b, int axis) {
    return a->bounding().min()[axis] < b->bounding().min()[axis];
}

inline bool box_x_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
    return box_compare(a, b, 0);
}

inline bool box_y_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
    return box_compare(a, b, 1);
}

inline bool box_z_compare(const std::shared_ptr<Primitive> a, const std::shared_ptr<Primitive> b) {
    return box_compare(a, b, 2);
}

class BVH : public Primitive {
public:
    enum class SplitMethod { MIDDLE, SAH };
    BVH(std::vector<std::shared_ptr<Primitive>>& p, int start, int end, int axis=0, SplitMethod splitMethod=SplitMethod::MIDDLE);
    bool intersect(const Ray& r, double tmin, double tmax, HitRecord& rec) const override;
    AABB bounding() const override;
private:
    std::shared_ptr<Primitive> left;
    std::shared_ptr<Primitive> right;
    AABB box;
    SplitMethod splitMethod;
};

}