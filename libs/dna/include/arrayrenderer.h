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

typedef struct __DNAArrayRenderer* DNAArrayRendererRef;
extern const CFClassRef DNAArrayRenderer;

/**
 *  class DNAArrayRenderer
 */
struct __DNAArrayRenderer {
    struct __CFObject obj;
    struct __DNAShader* shader;
    GLuint VBO;
    GLuint VAO;
};

extern method void* New(DNAArrayRendererRef this, DNAShaderRef shader);

extern method void Draw(DNAArrayRendererRef this, DNATexture2DRef texture, DNARect* bounds, GLfloat rotate, Vec3 color);
extern method void Draw(DNAArrayRendererRef this, DNATexture2DRef texture, Vec2 position, Vec2 size, GLfloat rotate, Vec3 color);

static inline DNAArrayRendererRef NewDNAArrayRenderer(DNAShaderRef shader)
{
    return New((DNAArrayRendererRef)CFCreate(DNAArrayRenderer), shader);
}
