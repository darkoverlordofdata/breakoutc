#pragma once
#include "class.h"
#include "shader.h"
#include "texture2d.h"

typedef struct __DNAResourceManager* DNAResourceManagerRef;
extern const CFClassRef DNAResourceManager;

/**
 *  class DNAResourceManager
 */
 struct __DNAResourceManager {
    struct __CFObject obj;
    CFMapRef Shaders;
    CFMapRef Textures;
    CFMapRef Fonts;
};

extern method void* New(DNAResourceManagerRef this);

extern method DNAShaderRef LoadShader(
    const DNAResourceManagerRef this,
    const GLchar* vShaderFile,
    const GLchar* fShaderFile,
    const char* name);

extern method DNAShaderRef GetShader(
    const DNAResourceManagerRef this,
    const char* name);

extern method DNATexture2DRef LoadTexture(
    const DNAResourceManagerRef this,
    const GLchar* file,
    GLboolean alpha,
    const char* name);

extern method DNATexture2DRef GetTexture(
    const DNAResourceManagerRef this,
    const char* name);

static inline DNAResourceManagerRef NewDNAResourceManager()
{
    return New((DNAResourceManagerRef)CFCreate(DNAResourceManager));
}
