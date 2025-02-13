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

typedef struct GameObject GameObject;
extern const CFClass* GameObjectClass;

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
struct GameObject {
    CFObject obj;
    Vec2 Position;
    Vec2 Size;
    Vec2 Velocity;
    Vec3 Color;
    GLfloat Rotation;
    GLboolean IsSolid;
    GLboolean Destroyed;
    DNATexture2D* Sprite;
    char* Name;
};

extern method GameObject* New(GameObject* this, char* name, Vec2 Position, Vec2 Size, DNATexture2D* Sprite, Vec3 Color);
extern method void Draw(GameObject* this, DNAArrayRenderer* renderer);
extern method char* ToString(GameObject* this);


