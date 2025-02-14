#!/bin/bash
#
#   compile the static wren lib for emscripten   
#

emcc   -r -std=c11                                  \
    external/blocksruntime/BlocksRuntime/runtime.c  \
    external/blocksruntime/BlocksRuntime/data.c     \
    -Iexternal/blocksruntime                        \
    -Iexternal/blocksruntime/BlocksRuntime          \
    -o libs/libBlocksRuntime.bc

cd external/corefw

#
#   compile the static wren lib for emscripten   
#
emcc   -r -std=c11                      \
       external/src/array.c		\
       external/src/bool.c		\
       external/src/box.c		\
       external/src/class.c		\
       external/src/double.c		\
       external/src/file.c		\
       external/src/int.c		\
       external/src/map.c		\
       external/src/object.c		\
       external/src/range.c		\
       external/src/refpool.c    \
       external/src/stream.c		\
       external/src/string.c		\
       external/src/tcpsocket.c  \
        -o libs/libcorefw.bc

