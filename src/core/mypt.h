#pragma once

// Core include 
#include "util.h"
#include "math_util.h"
#include "perlin.h"
#include "ray.h"
#include "image.h"
#include "primitive.h"
#include "bvh.h"
#include "transform.h"
#include "onb.h"
#include "pdf.h"
#include "scene.h"

// Render include
#include "../render/camera.h"
#include "../render/integrator.h"

// Shape include 
#include "shape.h"
#include "../shape/triangle.h"
#include "../shape/sphere.h"
#include "../shape/plane.h"

// Material include
#include "material.h"
#include "../material/lambertian.h"
#include "../material/metal.h"
#include "../material/dielectric.h"
#include "../material/emitter.h"
#include "../material/normal.h"
// #include "../material/Disney.h"

// Texture include 
#include "texture.h"
#include "../texture/image.h"
#include "../texture/checker.h"
#include "../texture/constant.h"
#include "../texture/noise.h"
