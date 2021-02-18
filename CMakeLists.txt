# Setting of Cmake version
cmake_minimum_required(VERSION 3.8)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17) # C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # ...is required...
set(CMAKE_CXX_EXTENSIONS OFF) # ...without compiler extensions like gnu++11

# Setting of project name
project(mypt)

# Set 
set(mypt_src
    src/mypt.cpp
    src/core/AABB.cpp
    src/core/BVH.cpp
    src/core/Image.cpp
    src/core/Perlin.cpp
    src/core/mat4.cpp
    src/core/Transform.cpp
    src/core/Primitive.cpp
    src/core/Scene.cpp
    src/core/bsdf.cpp

    src/render/Camera.cpp 
    src/render/Integrator.cpp

    src/material/Dielectric.cpp 
    src/material/Emitter.cpp
    src/material/Lambertian.cpp 
    src/material/Metal.cpp
    src/material/NormalMat.cpp

    # src/shape/MovingSphere.cpp 
    src/shape/Plane.cpp
    src/shape/Sphere.cpp 
    src/shape/Triangle.cpp

    src/texture/ImageTexture.cpp
    src/texture/NoiseTexture.cpp
)

# For use of OPENMP
find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Ofast")
# Please add `-pg` option to profile the performance of this renderer. 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -Wall -Wextra -Ofast")

add_executable(mypt ${mypt_src})

# Set float precision
option(USE_FLOAT_TO_DOUBLE "Use Float to double" ON)
if(USE_FLOAT_TO_DOUBLE)
    add_definitions(-DFLOAT_TO_DOUBLE)
endif()