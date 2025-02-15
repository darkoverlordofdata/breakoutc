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
#include "GameObject.h"
#include "Particle.h"

typedef struct __ParticleGenerator* ParticleGeneratorRef;
extern const CFClassRef ParticleGeneratorClass;
// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
struct __ParticleGenerator {
    struct __CFObject obj;
    ParticleRef particles;
    GLuint amount;
    DNAShaderRef shader;
    DNATexture2DRef texture;
    GLuint VAO;
};

extern method void* New(ParticleGeneratorRef this, DNAShaderRef shader, DNATexture2DRef texture, int amount);
extern method void Update(ParticleGeneratorRef this, GLfloat dt, GameObjectRef object, GLuint newParticles, Vec2 offset);
extern method void Draw(ParticleGeneratorRef this);
extern method void init(ParticleGeneratorRef this);
extern method GLuint firstUnused(ParticleGeneratorRef this);
extern method void respawn(ParticleGeneratorRef this, ParticleRef particle, GameObjectRef object, Vec2 offset);
extern method char* ToString(ParticleGeneratorRef this);

static inline ParticleGeneratorRef NewParticleGenerator(DNAShaderRef shader, DNATexture2DRef texture, int amount)
{
    return New((ParticleGeneratorRef)CFCreate(ParticleGeneratorClass), shader, texture, amount);
}
