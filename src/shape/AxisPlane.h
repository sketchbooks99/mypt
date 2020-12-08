#pragma once 

#include "../core/Shape.h"

class XYPlane final : public Shape {
public:
    XYPlane() {}
    XYPlane(double x0, double x1, double y0, double y1, double k)
    : x0(x0), x1(x1), y0(y0), y1(y1), k(k) {}

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override {
        double eps = 1e-4f;
        return AABB(vec3(x0, y0, k-eps), vec3(x1, y1, k+eps));
    }
private:
    double x0, x1;
    double y0, y1;
    double k;
};

class YZPlane final : public Shape {
public:
    YZPlane() {}
    YZPlane(double y0, double y1, double z0, double z1, double k)
    : y0(y0), y1(y1), z0(z0), z1(z1), k(k) {}

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override {
        double eps = 1e-4f;
        return AABB(vec3(k-eps, y0, z0), vec3(k+eps, y1, z1));
    }
private:
    double y0, y1;
    double z0, z1;
    double k;
};

class XZPlane final : public Shape {
public:
    XZPlane() {}
    XZPlane(double x0, double x1, double z0, double z1, double k)
    : x0(x0), x1(x1), z0(z0), z1(z1), k(k) {}

    bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    AABB bounding() const override {
        double eps = 1e-4f;
        return AABB(vec3(x0, k-eps, z0), vec3(x1, k+eps, z1));
    }
private:
    double x0, x1;
    double z0, z1;
    double k;
};

std::shared_ptr<Shape> createXYPlaneShape(double x0, double x1, double y0, double y1, double k);
std::shared_ptr<Shape> createYZPlaneShape(double y0, double y1, double z0, double z1, double k);
std::shared_ptr<Shape> createXZPlaneShape(double x0, double x1, double z0, double z1, double k);