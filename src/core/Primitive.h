#ifndef PRIMITIVE_H
#define PRIMITIVE_H

class Primitive {
public:
    bool intersect()
private:
    std::shared_ptr<Material> m;
    std::shared_ptr<Shape> s;
    std::shared_ptr<Texture> t;
};

#endif
