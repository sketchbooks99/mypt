#include "ShapeGroup.h"

namespace mypt {

/// \public
// ----------------------------------------------------------------------------------
bool ShapeGroup::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    for(auto& shape : group) {
        if(shape->intersect(r, t_min, t_max, rec)) return true;
    }
    return false;
}

// ----------------------------------------------------------------------------------
AABB ShapeGroup::bounding() const {
    return bbox;
}

// ----------------------------------------------------------------------------------
double ShapeGroup::pdf_value(const vec3& origin, const vec3& v) const {
    int idx = random_int(0, group.size());
    return group[idx]->pdf_value(origin, v);
}

// ----------------------------------------------------------------------------------
vec3 ShapeGroup::random(const vec3& origin) const {
    int idx = random_int(0, group.size());
    return group[idx]->random(origin);
}

// ----------------------------------------------------------------------------------
void ShapeGroup::append(std::shared_ptr<Shape> shape) {
    this->group.push_back(shape);
    this->calcBound();
}

/// \private
// ----------------------------------------------------------------------------------
void ShapeGroup::calcBound() {
    AABB tmp;
    for(auto& shape : group) {
        tmp = surrounding(tmp, shape->bounding());
    } 
    this->bbox = tmp;
}

}