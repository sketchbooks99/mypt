#pragma once 

#include "../core/Shape.h"

namespace mypt {

class FlipFace final : public Shape {
public:
    FlipFace(std::shared_ptr<Shape> s) : s(s) {}

    bool intersect(const Ray& r, Float t_min, Float t_max, HitRecord& rec) const override {
        if(!s->intersect(r, t_min, t_max, rec))
            return false;

        rec.front_face = !rec.front_face;
        return true;
    }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "FilpFace : {" << std::endl;
        oss << "\tShape : " << s->to_string() << std::endl;
        oss << "}";
        return oss.str();
    }
private: 
    std::shared_ptr<Shape> s;
};

}