#ifndef SHAPELIST_H
#define SHAPELIST_H

#include "Shape.h"
#include <memory>
#include <vector>

class ShapeList : public Shape {
    public:
        ShapeList() {}
        ShapeList(std::shared_ptr<Shape> object) { add(object); }

        void clear() { objects.clear(); }
        void add(std::shared_ptr<Shape> object) { objects.push_back(object); }

        virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
        virtual AABB bounding() const;

    public:
        std::vector<std::shared_ptr<Shape>> objects;
};

bool ShapeList::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool intersect_anything = false;
    auto closest_so_far = t_max;

    for(const auto& object : objects) {
        if (object->intersect(r, t_min, closest_so_far, temp_rec)) {
            intersect_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return intersect_anything;
}

AABB ShapeList::bounding() const {
    if(objects.empty()) return false;

    AABB temp_box;
    bool first_box = true;

    for(const auto& object : objects) {
        if(!object->bounding(t0, t1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding(output_box, temp_box);
    }
    
    return true;
}

#endif
