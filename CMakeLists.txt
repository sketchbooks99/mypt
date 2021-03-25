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
    src/core/aabb.cpp
    src/core/bvh.cpp
    src/core/image.cpp
    src/core/perlin.cpp
    src/core/mat4.cpp
    src/core/transform.cpp
    src/core/primitive.cpp
    src/core/scene.cpp

    src/render/camera.cpp 
    src/render/integrator.cpp

    src/material/dielectric.cpp 
    src/material/emitter.cpp
    src/material/lambertian.cpp 
    src/material/metal.cpp
    src/material/normal.cpp

    # src/shape/MovingSphere.cpp 
    src/shape/plane.cpp
    src/shape/sphere.cpp 
    src/shape/triangle.cpp

    src/texture/image.cpp
    src/texture/noise.cpp
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