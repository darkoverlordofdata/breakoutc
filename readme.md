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
