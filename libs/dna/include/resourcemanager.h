#pragma once
#include "corefw/class.h"
#include "shader.h"
#include "texture2d.h"

typedef struct DNAResourceManager DNAResourceManager;
extern const CFClass* DNAResourceManagerClass;

/**
 *  class DNAResourceManager
 */
 struct DNAResourceManager {
    CFObject obj;
    CFMap* Shaders;
    CFMap* Textures;
    CFMap* Fonts;
};

extern method void* New(DNAResourceManager* this);

extern method DNAShader* LoadShader(
    const DNAResourceManager* this,
    const GLchar* vShaderFile,
    const GLchar* fShaderFile,
    const char* name);

extern method DNAShader* GetShader(
    const DNAResourceManager* this,
    const char* name);

extern method DNATexture2D* LoadTexture(
    const DNAResourceManager* this,
    const GLchar* file,
    GLboolean alpha,
    const char* name);

extern method DNATexture2D* GetTexture(
    const DNAResourceManager* this,
    const char* name);
