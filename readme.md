# breakout from 
## learnopengl with c99

using:
* midar's corefw framework
* vector-of-bool's pitchfork project layout
* clang vector extensions with function overload.

* After cloning the repository, you may have to explicitly update the submodules: `git submodule init` followed by `git submodule update`

```bash
git submodule add -f https://github.com/nothings/stb.git external/stb
git submodule add -f https://github.com/datenwolf/linmath.h.git external/linmath.h
git submodule add -f https://github.com/mackyle/blocksruntime.git external/blocksruntime
git submodule add -f https://github.com/midar/corefw.git external/corefw
sudo apt install libblocksruntime-dev
sudo apt install libglfw3-dev
```

## todo (i think this is finally it):

* remove all macros
* use CF style naming as in the spaceinvaders game
* use Artemis lib from spaceinvaders game
* use the bitvector, random, fs and uuid classese from this project
* use generic functions {__attribute__((overloadable))} for collections (CFGet/CFPut, etc)
* use foreach function with anonymous function for collections 
* use dna lib from this proejct, rename to GK (GameKit)
* use sdl2/opengles  rather than glfw3/glad/stb
