#pragma once
#include "tglm.h"
#include <GL/gl.h>
#include <class.h>
#include <corefw.h>
#include <GLFW/glfw3.h>

/**
 * class DNATexture2D
 */
typedef struct DNATexture2D DNATexture2D;
extern const CFClassRef DNATexture2DClass;


/**
 *  object DNATexture2D
 */
struct DNATexture2D {
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

extern method void* New(DNATexture2D* this, GLuint internalFormat, GLuint imageFormat, char* path);

extern method void Generate(
    DNATexture2D* this,
    GLuint width,
    GLuint height,
    unsigned char* data);

extern method void Bind(const DNATexture2D* this);

extern method char* ToString(const DNATexture2D* this);

static inline DNATexture2D* NewDNATexture2D(GLuint internalFormat, GLuint imageFormat, char* path)
{
    return New((DNATexture2D*)CFCreate(DNATexture2DClass), internalFormat, imageFormat, path);
}
