#include "BVH.h"

BVH::BVH(std::vector<std::shared_ptr<Primitive>> p) : primitives(std::move(p)) {
    if(primitives.empty()) return;
}