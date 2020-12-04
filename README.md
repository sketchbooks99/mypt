# PBRenderer

![current_thumbnail](result/result.png)

- This is physically based renderer for learning rendering algorithms, which include global illuminations, effective techniques (i.e., Next Event Estimation, Bounding Volume Hierarchy, etc...), several integrators (i.e., MLT, Bidirectional path tracing), several sampling strategies.
- If I finished basic learning of path tracing, I'd like to implement GPU path tracing techniques using OptiX or CUDA.

## Compile (Linux)
After cloning this repository to your local, run this command to execute `pbrenderer`. 
```
cd PBRenderer
mkdir build 
cd build
cmake ..
make
```

After compiling it, you can render your scene with this command.
```
cd path/to/PBRenderer
build/pbrenderer config.txt
```

### NOTE: 
- At now, file parser like as pbrt, to arbitrary modify your scene is not implemented. So, when you create your custom scene, please modify or create custom_scene.h in scene/ directory, and change header file which include by PBRenderer.cpp .

## TODO:

- [ ] Add Russian roulette 
- [x] Add Emitter 
- [ ] Implement several sampling strategy
- [ ] Implement **Disney Principled BSDF** Class for material.
- [ ] Implement Image I/O 
  - [x] Base Image class (only constructor)
  - [x] Write image to file
  - [x] Support JPG format
  - [ ] Support GRAY scale I/O
- [x] Transformation system (translate, rotate, scale)
  - [x] Transformation system should be managed with pointer for better memory efficiency.
- [x] Update BVH for better efficiency
  - [x] Add SAH based BVH (I have not verified efficiency yet.)
- [x] Enable ImageTexture class
- [ ] Make a parser or system to independently modify scene configuration as like pbrt or oF. 

## NOTE:
I'm not expert in C++ and compiler, so I have to check entire code to robustly run and compile with taking care of following terms.
- Spliting code to .h and .cpp
  - use of template class: 
    - reference: https://qiita.com/i153/items/38f9688a9c80b2cb7da7
  - how to solve multiple definition
    - https://theolizer.com/cpp-school2/cpp-school2-3/
- cmake compile
  - https://qiita.com/yumetodo/items/bd8f556ab56298f19ba8