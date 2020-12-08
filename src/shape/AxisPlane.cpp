#include "AxisPlane.h"

bool XYPlane::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    auto t = (k-r.origin().z) / r.direction().z;
    if(t < t_min || t > t_max) 
        return false;
    
    double x = r.origin().x + t * r.direction().x;
    double y = r.origin().y + t * r.direction().y;
    if(x < x0 || x > x1 || y < y0 || y > y1) 
        return false;

    // Store ray information at intesection point
    rec.u = (x-x0) / (x1-x0);
    rec.v = (y-y0) / (y1-y0);
    rec.t = t;
    auto outward_normal = vec3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    double eps = 1e-4f;
    rec.p = r.at(t) + rec.normal * eps;

    // std::cout << rec.p << std::endl;

    return true;
}

bool YZPlane::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    auto t = (k-r.origin().x) / r.direction().x;
    if(t < t_min || t > t_max) 
        return false;
    
    double y = r.origin().y + t * r.direction().y;
    double z = r.origin().z + t * r.direction().z;
    if(y < y0 || y > y1 || z < z0 || z > z1) 
        return false;

    // Store ray information at intesection point
    rec.u = (y-y0) / (y1-y0);
    rec.v = (z-z0) / (z1-z0);
    rec.t = t;
    auto outward_normal = vec3(1, 0, 0);
    rec.set_face_normal(r, outward_normal);
    double eps = 1e-4f;
    rec.p = r.at(t) + rec.normal * eps;

    return true;
}

bool XZPlane::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    auto t = (k-r.origin().y) / r.direction().y;
    if(t < t_min || t > t_max) 
        return false;
    
    double x = r.origin().x + t * r.direction().x;
    double z = r.origin().z + t * r.direction().z;
    if(x < x0 || x > x1 || z < z0 || z > z1) 
        return false;

    // Store ray information at intesection point
    rec.u = (x-x0) / (x1-x0);
    rec.v = (z-z0) / (z1-z0);
    rec.t = t;
    auto outward_normal = vec3(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    double eps = 1e-4f;
    rec.p = r.at(t) + rec.normal * eps;

    return true;
}

std::shared_ptr<Shape> createXYPlaneShape(double x0, double x1, double y0, double y1, double k)
{
    return std::make_shared<XYPlane>(x0, x1, y0, y1, k);
}

std::shared_ptr<Shape> createYZPlaneShape(double y0, double y1, double z0, double z1, double k)
{
    return std::make_shared<YZPlane>(y0, y1, z0, z1, k);
}

std::shared_ptr<Shape> createXZPlaneShape(double x0, double x1, double z0, double z1, double k)
{
    return std::make_shared<XZPlane>(x0, x1, z0, z1, k);
}