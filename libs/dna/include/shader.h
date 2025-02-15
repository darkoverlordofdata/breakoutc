#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include "tglm.h"
#include <GLFW/glfw3.h>
#include "class.h"
#include "object.h"
#include <GLFW/glfw3.h>

typedef struct __DNAShader* DNAShaderRef;
extern const CFClassRef DNAShaderClass;

/**
 *  class DNAShader
 */
struct __DNAShader {
    struct __CFObject obj;
    GLuint Id;
};

extern method DNAShaderRef Use(DNAShaderRef this);

extern method void* New(DNAShaderRef this, CFStringRef vShader, CFStringRef fShader);
extern method GLuint GetId(DNAShaderRef this);
extern method void Compile(DNAShaderRef this, const GLchar* vertexSource, const GLchar* fragmentSource);
extern method void SetFloat(
    DNAShaderRef this,
    const GLchar* name,
    const GLfloat value,
    const GLboolean useShader);

extern method void SetInteger(
    DNAShaderRef this,
    const GLchar* name,
    GLint value,
    GLboolean useShader);

extern method void SetInteger(
    DNAShaderRef this,
    const GLchar* name,
    GLint value);

extern method void SetVector2(
    DNAShaderRef this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLboolean useShader);

extern method void SetVector2(
    DNAShaderRef this,
    const GLchar* name,
    GLfloat x,
    GLfloat y);

extern method void SetVector2v(
    DNAShaderRef this,
    const GLchar* name,
    const Vec2* vector,
    GLboolean useShader);

extern method void SetVector2v(
    DNAShaderRef this,
    const GLchar* name,
    const Vec2* vector);

extern method void SetVector3(
    DNAShaderRef this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLboolean useShader);

extern method void SetVector3(
    DNAShaderRef this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z);

extern method void SetVector3v(
    DNAShaderRef this,
    const GLchar* name,
    const Vec3* vector,
    GLboolean useShader);

extern method void SetVector3v(
    DNAShaderRef this,
    const GLchar* name,
    const Vec3* vector);

extern method void SetVector4(
    DNAShaderRef this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w,
    GLboolean useShader);

extern method void SetVector4(
    DNAShaderRef this,
    const GLchar* name,
    GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w);

extern method void SetVector4v(
    DNAShaderRef this,
    const GLchar* name,
    const Vec4* vector,
    GLboolean useShader);

extern method void SetVector4v(
    DNAShaderRef this,
    const GLchar* name,
    const Vec4* vector);

extern method void SetMatrix(
    DNAShaderRef this,
    const GLchar* name,
    const Mat* matrix,
    GLboolean useShader);

extern method void SetMatrix(
    DNAShaderRef this,
    const GLchar* name,
    const Mat* matrix);

static inline DNAShaderRef NewDNAShader(CFStringRef vShader, CFStringRef fShader)
{
    return New((DNAShaderRef)CFCreate(DNAShaderClass), vShader, fShader);
}
