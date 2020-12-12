#pragma once 

#include "MathUtil.h"
#include "Shape.h"
#include "ONB.h"

namespace mypt {

class PDF {
public:
    virtual ~PDF() {}

    virtual double value(const vec3& direction) const = 0;
    virtual vec3 generate() const = 0;
};

class CosinePDF : public PDF {
public:
    CosinePDF(const vec3& w) { onb.build_from_w(w); }

    double value(const vec3& direction) const override {
        auto cosine = dot(normalize(direction), onb.w);
        return (cosine <= 0) ? 0 : cosine / pi;
    }

    vec3 generate() const override {
        return onb.local(random_cosine_direction());
    }
private:
    ONB onb;
};

class PrimitivePDF : public PDF {
public:
    PrimitivePDF(std::shared_ptr<Primitive> p, const vec3& origin) : p(p), origin(origin) {}
    double value(const vec3& direction) const override {
        p->pdf_value(origin, direction);
    }

    vec3 generate() const override {
        return p->random(origin);
    }
private:
    std::shared_ptr<Primitive> p;
    vec3 origin;
};

}