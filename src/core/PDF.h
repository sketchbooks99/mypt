#pragma once 

#include "MathUtil.h"
#include "ONB.h"
#include "Primitive.h"

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
class PrimitivePDF final : public PDF {
public:
    PrimitivePDF(std::shared_ptr<Primitive> p, const vec3& origin) : p(p), origin(origin) {}
    double value(const vec3& direction) const override {
        return p->pdf_value(origin, direction);
    }

    vec3 generate() const override {
        return p->random(origin);
    }
private:
    std::shared_ptr<Primitive> p;
    vec3 origin;
};

// --------------------------------------------------------------
class LightPDF final : public PDF {
public:
    LightPDF(std::vector<std::shared_ptr<Primitive>> lights, const vec3& origin) : lights(lights), origin(origin) {
        ASSERT(lights.size() > 0, "There is no light in constructor\n");
    }
    double value(const vec3& direction) const override {
        auto weight = 1.0 / lights.size();
        auto sum = 0.0;

        for (const auto& p : lights)
            sum += weight * p->pdf_value(origin, direction);

        return sum;
    }
    vec3 generate() const override { 
        auto num_lights = static_cast<int>(lights.size());
        return lights[random_int(0, num_lights-1)]->random(origin);
    }
    void set_origin(vec3 o) { this->origin = o; }
private:
    std::vector<std::shared_ptr<Primitive>> lights;
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