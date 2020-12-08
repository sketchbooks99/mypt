#pragma once

// Core include 
#include "Util.h"
#include "MathUtil.h"
#include "Camera.h"
#include "Perlin.h"
#include "Ray.h"
#include "Image.h"
#include "Primitive.h"
#include "BVH.h"
#include "Transform.h"

// Shape include 
#include "Shape.h"
#include "../shape/Triangle.h"
#include "../shape/Sphere.h"
#include "../shape/Plane.h"
#include "../shape/AxisPlane.h"

// Material include
#include "Material.h"
#include "../material/Lambertian.h"
#include "../material/Metal.h"
#include "../material/Dielectric.h"
#include "../material/Emitter.h"
#include "../material/NormalMat.h"
// #include "../material/Disney.h"

// Texture include 
#include "Texture.h"
#include "../texture/ImageTexture.h"
#include "../texture/CheckerTexture.h"
#include "../texture/ConstantTexture.h"
#include "../texture/NoiseTexture.h"
