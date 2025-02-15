#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <corefw.h>

#include "rect.h"
#include "texture2d.h"
#include "tglm.h"
#include "dna.h"

typedef struct __DNAElementRenderer* DNAElementRendererRef;
extern const CFClassRef DNAElementRendererClass;

/**
 *  class DNAElementRenderer
 */
struct __DNAElementRenderer {
    struct __CFObject obj;
    struct __DNAShaderRef* shader;
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
};

extern method void* New(DNAElementRendererRef this, DNAShaderRef shader);

extern method void Draw(DNAElementRendererRef this, DNATexture2DRef texture, DNARect bounds, GLfloat rotate, Vec3 color);
extern method void Draw(DNAElementRendererRef this, DNATexture2DRef texture, Vec2 position, Vec2 size, GLfloat rotate, Vec3 color);

static inline DNAElementRendererRef NewDNAElementRenderer(DNAShaderRef shader)
{
    return New((DNAElementRendererRef)CFCreate(DNAElementRendererClass), shader);
}

