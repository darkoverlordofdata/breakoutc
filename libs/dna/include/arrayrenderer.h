#pragma once
#include "shader.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include "rect.h"
#include "texture2d.h"
#include "tglm.h"
#include <GLFW/glfw3.h>
#include <corefw.h>

typedef struct DNAArrayRenderer DNAArrayRenderer;
extern const CFClassRef DNAArrayRendererClass;

/**
 *  class DNAArrayRenderer
 */
struct DNAArrayRenderer {
    struct __CFObject obj;
    struct DNAShader* shader;
    GLuint VBO;
    GLuint VAO;
};

extern method void* New(DNAArrayRenderer* this, DNAShader* shader);

extern method void Draw(DNAArrayRenderer* this, DNATexture2D* texture, DNARect* bounds, GLfloat rotate, Vec3 color);
extern method void Draw(DNAArrayRenderer* this, DNATexture2D* texture, Vec2 position, Vec2 size, GLfloat rotate, Vec3 color);

static inline DNAArrayRenderer* NewDNAArrayRenderer(DNAShader* shader)
{
    return New((DNAArrayRenderer*)CFCreate(DNAArrayRendererClass), shader);
}
