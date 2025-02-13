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
#include <cfw.h>
#include <dna.h>
#include "GameObject.h"
#include "Particle.h"

typedef struct ParticleGenerator ParticleGenerator;
extern const CFClass* ParticleGeneratorClass;
// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
struct ParticleGenerator {
    CFObject obj;
    Particle* particles;
    GLuint amount;
    DNAShader* shader;
    DNATexture2D* texture;
    GLuint VAO;
};

extern method void* New(ParticleGenerator* this, DNAShader* shader, DNATexture2D* texture, int amount);
extern method void Update(ParticleGenerator* this, GLfloat dt, GameObject* object, GLuint newParticles, Vec2 offset);
extern method void Draw(ParticleGenerator* this);
extern method void init(ParticleGenerator* this);
extern method GLuint firstUnused(ParticleGenerator* this);
extern method void respawn(ParticleGenerator* this, Particle* particle, GameObject* object, Vec2 offset);
extern method char* ToString(ParticleGenerator* this);

static inline ParticleGenerator* NewParticleGenerator(DNAShader* shader, DNATexture2D* texture, int amount)
{
    return New((ParticleGenerator*)cfw_create(ParticleGeneratorClass), shader, texture, amount);
}
