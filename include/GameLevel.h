/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#include <stdlib.h>
#include <stdio.h>
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

typedef struct __GameLevel* GameLevelRef;
extern const CFClassRef GameLevelClass;

/// GameLevel holds all Tiles as part of a Breakout level and
/// hosts functionality to Load/render levels from the harddisk.
struct __GameLevel {
    struct __CFObject obj;
    CFArrayRef Bricks;
};

extern method GameLevelRef New(GameLevelRef this, GLchar *file, int levelWidth, int levelHeight);
extern method GameLevelRef Load(GameLevelRef this, GLchar *file, int levelWidth, int levelHeight);
extern method void Draw(GameLevelRef this, DNAArrayRendererRef renderer);
extern method bool IsCompleted(GameLevelRef this);
extern method void init(GameLevelRef this, CFArrayRef tileData, GLuint levelWidth, GLuint levelHeight);
extern method char* ToString(GameLevelRef this);

static inline GameLevelRef NewGameLevel(GLchar *file, int levelWidth, int levelHeight)
{
    return New((GameLevelRef)CFCreate(GameLevelClass), file, levelWidth, levelHeight);
}
