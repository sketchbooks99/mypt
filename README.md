# PBRenderer

![current_thumbnail](result/result.png)

- This is physically based renderer for learning rendering algorithms, which include global illuminations, effective techniques (i.e., Next Event Estimation, Bounding Volume Hierarchy, etc...), several integrators (i.e., MLT, Bidirectional path tracing), several sampling strategies.
- If I finished basic learning of path tracing, I'd like to implement GPU path tracing techniques using OptiX or CUDA.

## Compile & Run (Linux)

- Compile 
```
cd PBRenderer
mkdir build 
cd build
cmake ..
make
```

- Run
```
cd path/to/PBRenderer
build/pbrenderer config.txt
```

## NOTE: 
- At now, file parser like as pbrt, to arbitrary modify your scene is not implemented. So, when you create your custom scene, please modify or create custom_scene.h in scene/ directory, and change header file which include by PBRenderer.cpp .

- I'm not expert in C++ and compiler, so I have to check entire code to robustly run and compile with taking care of following terms.
  - Spliting code to .h and .cpp
    - use of template class: 
      - reference: https://qiita.com/i153/items/38f9688a9c80b2cb7da7
    - how to solve multiple definition
      - https://theolizer.com/cpp-school2/cpp-school2-3/
  - cmake compile
    - https://qiita.com/yumetodo/items/bd8f556ab56298f19ba8