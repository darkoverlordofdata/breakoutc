#pragma once
#include "class.h"
#include "shader.h"
#include "texture2d.h"

typedef struct DNAResourceManager DNAResourceManager;
extern const CFClassRef DNAResourceManagerClass;

/**
 *  class DNAResourceManager
 */
 struct DNAResourceManager {
    struct __CFObject obj;
    CFMapRef Shaders;
    CFMapRef Textures;
    CFMapRef Fonts;
};

extern method void* New(DNAResourceManager* this);

extern method DNAShaderRef LoadShader(
    const DNAResourceManager* this,
    const GLchar* vShaderFile,
    const GLchar* fShaderFile,
    const char* name);

extern method DNAShaderRef GetShader(
    const DNAResourceManager* this,
    const char* name);

extern method DNATexture2DRef LoadTexture(
    const DNAResourceManager* this,
    const GLchar* file,
    GLboolean alpha,
    const char* name);

extern method DNATexture2DRef GetTexture(
    const DNAResourceManager* this,
    const char* name);

static inline DNAResourceManager* NewDNAResourceManager()
{
    return New((DNAResourceManager*)CFCreate(DNAResourceManagerClass));
}
