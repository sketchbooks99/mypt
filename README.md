# PBRenderer

![current_thumbnail](result/result.png)

- This is physically based renderer for learning rendering algorithms, which include global illuminations, effective techniques (i.e., Next Event Estimation, Bounding Volume Hierarchy, etc...), several integrators (i.e., MLT, Bidirectional path tracing), several sampling strategy.
- If finished basic learning of path tracing, I would like to implement GPU path tracing techniques using OptiX or CUDA.

## Compile (Linux)
After cloning this repository to your local, run this command to run `pbrenderer` 
```
cd PBRenderer
mkdir build && cd build
cmake ..
make
```

After compiling
```
cd path/to/PBRenderer
build/pbrenderer image.png
```
> - NOTE: 
    - At now, file parser like as pbrt, to arbitrary modify your scene is not implemented. 
      So, when you create your custom scene, please modify or create `custom_scene.h` in `scene/` directory, 
      and change header file include in `PBRenderer.cpp` 

## TODO:
- [x] Divide material and shape for effectively render the scene.
  - I have to be referring to PBRT implementation of primitive. It is worthless to store the material for each triangle, so I want to reuse these materials for same triangle meshes. 
  - Maybe, the abstract implementation is as follows.
```c++
class Material { ... };
class Shape { ... };
class Primitive {
    Material m; 
    Shape s;
};
```

- [ ] Add Russian roulette 
- [x] Add Emitter 
- [ ] Implement several sampling strategy
- [ ] Implement **Disney Principled BSDF** Class for material.
- [ ] Implement Image I/O 
  - [x] Base Image class (only constructor)
  - [x] Write image to file
  - [x] Support JPG format
  - [ ] Support GRAY scale I/O
- [ ] Transformation system (translate, rotate, scale)
- [ ] Update BVH for better efficiency
  - [x] Add SAH based BVH (I have not verified efficiency yet.)
- [x] Enable ImageTexture class

## NOTE:
I'm not expert C++ and compiler, so I must check whole code to robustly run and compile with taking care of following terms.
- Spliting code to .h and .cpp
  - use of template class: 
    - reference: https://qiita.com/i153/items/38f9688a9c80b2cb7da7
  - how to solve multiple definition
    - https://theolizer.com/cpp-school2/cpp-school2-3/
- cmake compile
  - https://qiita.com/yumetodo/items/bd8f556ab56298f19ba8