/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
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
#include <dna.h>

typedef struct __Particle* ParticleRef;
extern const CFClassRef ParticleClass;

// Represents a single particle and its state
struct __Particle {
    struct __CFObject obj;
    Vec2 Position;
    Vec2 Velocity;
    Vec4 Color;
    GLfloat Life;
};

extern method void* New(ParticleRef this, DNAShaderRef shader, DNATexture2DRef texture, int amount);
extern method char* ToString(ParticleRef this);
