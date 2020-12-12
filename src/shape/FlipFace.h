#pragma once 

#include "../core/Shape.h"

namespace mypt {

class FlipFace final : public Shape {
public:
    FlipFace(std::shared_ptr<Shape> s) : s(s) {}

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        if(!s->intersect(r, t_min, t_max, rec))
            return false;

        rec.front_face = !rec.front_face;
        return true;
    }
private: 
    std::shared_ptr<Shape> s;
};

}