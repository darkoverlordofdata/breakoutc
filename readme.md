# breakout 


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
# wip
## todo (i think this is finally it):


- [x] remove all macros
    - [~] method    "__attribute__((overloadable))"
    - [x] new       "new(T, args...) New((T*)CFCreate((CFClass*)T##Class), ## args)"
    - [x] static inline all constructors for prior change
- [x] remove *-private.h headers

- [x] upgrade corefw
    - [x] move library internally
    - [x] merge cfw into corefw and delete cfw
    - [x] use CF style naming as in the spaceinvaders game
    - [x] use the bitvector, random, fs and uuid classese from this project
    - [x] use generic functions {__attribute__((overloadable))} for collections (CFGet/CFPut, etc)
    - [x] use foreach function with anonymous function for collections 

- [ ] use Artemis lib from spaceinvaders game

- [ ] optional?
    - [ ] use dna lib from this project, rename to GK (GameKit)
    - [ ] use sdl2/opengles  rather than glfw3/glad/stb


## notes

##### method
methods are multi-methods using clangs overloadable attribute. since this only works within the same compilation unit, these are exposed as static inline functions in cfw.h
since marking a function's charactaristics is commonly done using a macro and i used 'method' macro everywhere, i'll keep this

##### corefw
i need to break the dependancy on the og version of corefw so the next step is to copy it to internal library space and upgrade it in place
