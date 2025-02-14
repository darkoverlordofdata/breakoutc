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

typedef struct DNAElementRenderer DNAElementRenderer;
extern const CFWClass* DNAElementRendererClass;

/**
 *  class DNAElementRenderer
 */
struct DNAElementRenderer {
    CFWObject obj;
    struct DNAShader* shader;
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
};

extern method void* New(DNAElementRenderer* this, DNAShader* shader);

extern method void Draw(DNAElementRenderer* this, DNATexture2D* texture, DNARect bounds, GLfloat rotate, Vec3 color);
extern method void Draw(DNAElementRenderer* this, DNATexture2D* texture, Vec2 position, Vec2 size, GLfloat rotate, Vec3 color);

static inline DNAElementRenderer* NewDNAElementRenderer(DNAShader* shader)
{
    return New((DNAElementRenderer*)cfw_create(DNAElementRendererClass), shader);
}

