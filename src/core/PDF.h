#pragma once 

#include "MathUtil.h"
#include "ONB.h"
#include "Shape.h"

namespace mypt {

class PDF {
public:
    virtual ~PDF() {}

    virtual double value(const vec3& direction) const = 0;
    virtual vec3 generate() const = 0;
};

// --------------------------------------------------------------------
class CosinePDF final : public PDF {
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

// ---------------------------------------------------------------------
class ShapePDF final : public PDF {
public:
    ShapePDF(std::shared_ptr<Shape> s, const vec3& origin) : s(s), origin(origin) {}
    double value(const vec3& direction) const override {
        return s->pdf_value(origin, direction);
    }

    vec3 generate() const override {
        return s->random(origin);
    }
private:
    std::shared_ptr<Shape> s;
    vec3 origin;
};

// --------------------------------------------------------------
class MixturePDF final : public PDF {
public:
    MixturePDF(std::shared_ptr<PDF> p0, std::shared_ptr<PDF> p1) : p0(p0), p1(p1) {}

    double value(const vec3& direction) const override {
        return 0.5 * p0->value(direction) + 0.5 * p1->value(direction);
    }

    vec3 generate() const override {
        if(random_double() < 0.5) return p0->generate();
        else                      return p1->generate();
    }
private:
    std::shared_ptr<PDF> p0, p1;
};

}