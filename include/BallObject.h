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

typedef struct __BallObject* BallObjectRef;
extern const CFClassRef BallObject;

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
struct __BallObject { // extend GameObject
    struct __CFObject obj;
    Vec2 Position;
    Vec2 Size;
    Vec2 Velocity;
    Vec3 Color;
    GLfloat Rotation;
    GLboolean IsSolid;
    GLboolean Destroyed;
    DNATexture2DRef Sprite;
    char* Name;

    /* new BallObject fields */
    float Radius;
    bool Stuck;
};


extern method void* New(BallObjectRef this, Vec2 Position, float Radius, Vec2 Velocity, DNATexture2DRef Sprite);
extern method void Draw(BallObjectRef this, DNAArrayRendererRef renderer);
extern method void Move(BallObjectRef this, GLfloat dt, GLuint window_width);
extern method void Reset(BallObjectRef this, Vec2 position, Vec2 velocity);
extern method char* ToString(BallObjectRef  this);

static inline BallObjectRef NewBallObject(Vec2 Position, float Radius, Vec2 Velocity, DNATexture2DRef Sprite)
{
    return New((BallObjectRef)CFCreate(BallObject), Position, Radius, Velocity, Sprite);
}
