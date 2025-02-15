#pragma once
#include "tglm.h"
#include <GL/gl.h>
#include <class.h>
#include <corefw.h>
#include <GLFW/glfw3.h>

/**
 * class DNATexture2D
 */
typedef struct __DNATexture2D* DNATexture2DRef;
extern const CFClassRef DNATexture2DClass;


/**
 *  object DNATexture2D
 */
struct __DNATexture2D {
    struct __CFObject obj; // CoreFW interface
    GLuint Id; // Holds the ID of the texture object, used for all texture operations to reference to self particlar texture
    GLuint Width, Height; // Width and height of loaded image in pixels
    GLuint InternalFormat; // Format of texture object
    GLuint ImageFormat; // Format of loaded image
    GLuint wrapS; // Wrapping mode on S axis
    GLuint wrapT; // Wrapping mode on T axis
    GLuint filterMin; // Filtering mode if texture pixels < screen pixels
    GLuint filterMag; // Filtering mode if texture pixels > screen pixels
    char* path;
};

extern method void* New(DNATexture2DRef this, GLuint internalFormat, GLuint imageFormat, char* path);

extern method void Generate(
    DNATexture2DRef this,
    GLuint width,
    GLuint height,
    unsigned char* data);

extern method void Bind(const DNATexture2DRef this);

extern method char* ToString(const DNATexture2DRef this);

static inline DNATexture2DRef NewDNATexture2D(GLuint internalFormat, GLuint imageFormat, char* path)
{
    return New((DNATexture2DRef)CFCreate(DNATexture2DClass), internalFormat, imageFormat, path);
}
