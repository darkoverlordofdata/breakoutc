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

typedef struct __Collision* CollisionRef;
extern const CFClassRef CollisionClass;

// Represents the four possible (collision) directions
typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

/** Defines a Collision Result Tuple */
struct __Collision {
    struct __CFObject obj;
    bool IsTrue;
    Direction Dir;
    Vec2 Vec;
};

extern method void* New(CollisionRef this, bool first, Direction second, Vec2 third);
extern method char* ToString(CollisionRef this);

static inline CollisionRef NewCollision(bool first, Direction second, Vec2 third)
{
    return New((CollisionRef)CFCreate(CollisionClass), first, second, third);
}
