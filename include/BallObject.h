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
#include <corefw.h>
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <dna.h>

typedef struct BallObject BallObject;
extern const CFClassRef BallObjectClass;

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
struct BallObject { // extend GameObject
    struct __CFObject obj;
    Vec2 Position;
    Vec2 Size;
    Vec2 Velocity;
    Vec3 Color;
    GLfloat Rotation;
    GLboolean IsSolid;
    GLboolean Destroyed;
    DNATexture2D* Sprite;
    char* Name;

    /* new BallObject fields */
    float Radius;
    bool Stuck;
};


extern method void* New(BallObject* this, Vec2 Position, float Radius, Vec2 Velocity, DNATexture2D* Sprite);
extern method void Draw(BallObject* this, DNAArrayRenderer* renderer);
extern method void Move(BallObject* this, GLfloat dt, GLuint window_width);
extern method void Reset(BallObject* this, Vec2 position, Vec2 velocity);
extern method char* ToString(BallObject*  this);

static inline BallObject* NewBallObject(Vec2 Position, float Radius, Vec2 Velocity, DNATexture2D* Sprite)
{
    return New((BallObject*)CFCreate(BallObjectClass), Position, Radius, Velocity, Sprite);
}
