#include <stdio.h>
#include <string.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "cfwfs.h"
#include "dna.h"
#include "shader.h"
#include "texture2d.h"
#include <stb_image.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
 

static void dtor(void* self);

const static struct __CFClass class = {      
    .name = "DNAResourceManager",             
    .size = sizeof(DNAResourceManager), 
    .dtor = dtor     
};                                  
const CFClassRef DNAResourceManagerClass = &class;


void Init(DNAResourceManager* this);

DNAShader* LoadShaderFromFile(
    const DNAResourceManager* this,
    const GLchar* vShaderFile,
    const GLchar* fShaderFile);
DNATexture2D* LoadTextureFromFile(
    const DNAResourceManager* this,
    const GLchar* file,
    GLboolean alpha);

static void dtor(void* self)
{
    DNAResourceManager* this = self;
    CFMapIter_t iter;

    CFMapIter(this->Shaders, &iter);
    while (iter.key != NULL) {
        if (CFIs(iter.obj, (CFClassRef)DNAShaderClass))
            CFUnref(iter.obj);
        CFMapIterNext(&iter);
    }
    CFUnref(this->Shaders);

    CFMapIter(this->Textures, &iter);
    while (iter.key != NULL) {
        if (CFIs(iter.obj, (CFClassRef)DNATexture2DClass))
            CFUnref(iter.obj);
        CFMapIterNext(&iter);
    }
    CFUnref(this->Textures);
}

void Init(DNAResourceManager* this)
{
    this->Shaders = CFNew(CFMap, NULL);
    this->Textures = CFNew(CFMap, NULL);
}
method void* New(DNAResourceManager* this)
{
    Init(this);
    return this;
}
/**
 * LoadShader
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @param name to cache as
 * @returns loaded, compiled and linked shader program
 */
method DNAShader* LoadShader(
    const DNAResourceManager* this,
    const GLchar* vShaderFile,
    const GLchar* fShaderFile,
    const char* name)
{
    assert(this != NULL);

    CFMapSetC(this->Shaders, name, LoadShaderFromFile(this, vShaderFile, fShaderFile));
    return CFMapGetC(this->Shaders, name);
}

/**
 * GetShader
 * 
 * @param name to retrieve
 * @returns loaded, compiled and linked shader program
 * 
 */
method DNAShader* GetShader(
    const DNAResourceManager* this,
    const char* name)
{
    return CFMapGetC(this->Shaders, name);
}

/**
 * loadTexture
 * 
 * @param file path to texture
 * @param alpha does the texture have an alpha channel?
 * @param name to cache as
 * @returns Texture
 * 
 */
method DNATexture2D* LoadTexture(
    const DNAResourceManager* this,
    const GLchar* file,
    GLboolean alpha,
    const char* name)
{
    CFMapSetC(this->Textures, name, LoadTextureFromFile(this, file, alpha));
    return CFMapGetC(this->Textures, name);
}

/**
 * GetTexture
 * 
 * @param name to retrieve
 * @returns Texture
 * 
 */
method DNATexture2D* GetTexture(
    const DNAResourceManager* this,
    const char* name)
{
    return CFMapGetC(this->Textures, name);
}

void Clear(DNAResourceManager* this)
{
    dtor(this);
    Init(this);
}

// static inline char* join(const char* s1, const char* s2) { return nullptr;}
/**
 * loadShaderFromFile
 * 
 * @param vShaderFile path to vertex shader
 * @param fShaderFile path to fragment shader
 * @returns loaded, compiled and linked shader program
 * 
 */


DNAShader* LoadShaderFromFile(
    const DNAResourceManager* this,
    const GLchar* vShaderFile,
    const GLchar* fShaderFile)
{
    CFStringRef vShader = CFFS.readTextFile((char*)vShaderFile);
    CFStringRef fShader = CFFS.readTextFile((char*)fShaderFile);
    
    return New((DNAShader*)CFCreate(DNAShaderClass), vShader, fShader);
}

/**
 * loadTextureFromFile
 * 
 * @param file path to texture
 * @param alpha does the texture have an alpha channel?
 * @returns Texture
 * 
 */
DNATexture2D* LoadTextureFromFile(
    const DNAResourceManager* this,
    const GLchar* file,
    GLboolean alpha)
{
    int format = alpha ? GL_RGBA : GL_RGB;
    int stbiFlag = alpha ? STBI_rgb_alpha : STBI_rgb;

    DNATexture2D* texture = New((DNATexture2D*)CFCreate(DNATexture2DClass), format, format, (char*)file);

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, stbiFlag);
    Generate(texture, width, height, (unsigned char*)data);
    stbi_image_free(data);

    return texture;
}
