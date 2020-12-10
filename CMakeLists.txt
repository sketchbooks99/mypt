# Setting of Cmake version
cmake_minimum_required(VERSION 3.8)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17) # C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # ...is required...
set(CMAKE_CXX_EXTENSIONS OFF) # ...without compiler extensions like gnu++11

# Setting of project name
project(pbrenderer)

# Set 
set(pbrenderer_src
    src/PBRenderer.cpp
    src/core/AABB.cpp
    src/core/BVH.cpp
    src/core/Image.cpp
    src/core/Perlin.cpp
    src/core/mat4.cpp
    src/core/Transform.cpp

    src/render/Camera.cpp 

    src/material/Dielectric.cpp 
    src/material/Emitter.cpp
    src/material/Lambertian.cpp 
    src/material/Metal.cpp
    src/material/NormalMat.cpp
    src/material/MMAPs.cpp

    src/shape/MovingSphere.cpp 
    src/shape/Plane.cpp
    src/shape/Sphere.cpp 
    src/shape/Triangle.cpp

    src/texture/ImageTexture.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Ofast")

add_executable(pbrenderer ${pbrenderer_src})