### opengl rotating cube

uses: 

cglm for math, 

glad for opengl 4.5

sdl2 for window

```bash
./bin/prog
ESC 
```

looks like this:

![opengl cube](https://github.com/turriform/opengl_cube/blob/main/cube.png)

outputs this:

```
SDL init ok
Window Set up ok
Context created

OpenGL info context information
Vendor                  Mesa/X.org
Version                 4.5 (Core Profile) Mesa 22.3.6
Renderer                llvmpipe (LLVM 15.0.6, 128 bits)
Shading language v      4.50

fullpath ./shaders/vertex.glsl 
Shader size 331
Shader compiled
fullpath ./shaders/fragment.glsl 
Shader size 114
Shader compiled

Shader linked

World
Matrix (float4x4): 
  |  0.69206  0.12318  0.71125  0.00000  |
  |  0.12318  0.95073 -0.28450  0.00000  |
  | -0.71125  0.28450  0.64279  0.00000  |
  |  0.00000  0.00000  0.00000  1.00000  |


View
Matrix (float4x4): 
  |  1.00000  0.00000  0.00000  0.00000  |
  |  0.00000  1.00000  0.00000  0.00000  |
  |  0.00000  0.00000  1.00000 -7.00000  |
  |  0.00000  0.00000  0.00000  1.00000  |


Perspective
Matrix (float4x4): 
  |  1.73205  0.00000  0.00000  0.00000  |
  |  0.00000  1.73205  0.00000  0.00000  |
  |  0.00000  0.00000 -1.02020 -0.20202  |
  |  0.00000  0.00000 -1.00000  0.00000  |

End of loop 
SDL quit
```






