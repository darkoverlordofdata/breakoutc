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
#include "cfw.h"
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

const static CFWClass class = {      
    .name = "DNAResourceManager",             
    .size = sizeof(DNAResourceManager), 
    .dtor = dtor     
};                                  
const CFWClass* DNAResourceManagerClass = &class;


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
    cfw_map_iter_t iter;

    cfw_map_iter(this->Shaders, &iter);
    while (iter.key != NULL) {
        if (cfw_is(iter.obj, (CFWClass*)DNAShaderClass))
            cfw_unref(iter.obj);
        cfw_map_iter_next(&iter);
    }
    cfw_unref(this->Shaders);

    cfw_map_iter(this->Textures, &iter);
    while (iter.key != NULL) {
        if (cfw_is(iter.obj, (CFWClass*)DNATexture2DClass))
            cfw_unref(iter.obj);
        cfw_map_iter_next(&iter);
    }
    cfw_unref(this->Textures);
}

void Init(DNAResourceManager* this)
{
    this->Shaders = cfw_new(cfw_map, NULL);
    this->Textures = cfw_new(cfw_map, NULL);
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

    cfw_map_set_c(this->Shaders, name, LoadShaderFromFile(this, vShaderFile, fShaderFile));
    return cfw_map_get_c(this->Shaders, name);
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
    return cfw_map_get_c(this->Shaders, name);
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
    cfw_map_set_c(this->Textures, name, LoadTextureFromFile(this, file, alpha));
    return cfw_map_get_c(this->Textures, name);
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
    return cfw_map_get_c(this->Textures, name);
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
    CFWString* vShader = CFWFS.readTextFile((char*)vShaderFile);
    CFWString* fShader = CFWFS.readTextFile((char*)fShaderFile);
    
    return New((DNAShader*)cfw_create(DNAShaderClass), vShader, fShader);
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

    DNATexture2D* texture = New((DNATexture2D*)cfw_create(DNATexture2DClass), format, format, (char*)file);

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, stbiFlag);
    Generate(texture, width, height, (unsigned char*)data);
    stbi_image_free(data);

    return texture;
}
