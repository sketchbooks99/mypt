#ifndef Hittable_list_h
#define Hittable_list_h

#include "Hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Hittable_list : public Hittable {
    public:
        Hittable_list() {}
        Hittable_list(shared_ptr<Hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<Hittable> object) { objects.push_back(object); }

        virtual bool hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const;
        virtual bool bounding_box(double t0, double t1, AABB& output_box) const;

    public:
        std::vector<shared_ptr<Hittable>> objects;
};

bool Hittable_list::hit(const Ray& r, double t_min, double t_max, Hit_record& rec) const {
    Hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool Hittable_list::bounding_box(double t0, double t1, AABB& output_box) const {
    if(objects.empty()) return false;

    AABB temp_box;
    bool first_box = true;

    for(const auto& object : objects) {
        if(!object->bounding_box(t0, t1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
    }
    
    return true;
}

#endif