/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GameObject.h"

/** Default values */
static const Vec2 GAME_OBJECT_POSITION = { 0.0f, 0.0f };
static const Vec2 GAME_OBJECT_SIZE = { 1.0f, 1.0f };
static const Vec2 GAME_OBJECT_VELOCITY = { 0.0f, 0.0f };
static const Vec3 GAME_OBJECT_COLOR = { 1.0f, 1.0f, 1.0f };

static struct __CFClass class = {
    .name = "GameObject",
    .size = sizeof(struct __GameObject),
};
const CFClassRef GameObjectClass = &class;

/**
 * Constructor
 * 
 * @param Position initial placement
 * @param Size sprite size
 * @param Sprite to display
 * @param Color tiniting color
 */
method GameObjectRef New(
    GameObjectRef this,
    char* name,
    Vec2 Position,
    Vec2 Size,
    DNATexture2DRef Sprite,
    Vec3 Color)
{
    this->IsSolid = false;
    this->Destroyed = false;
    this->Position = Position;
    this->Size = Size;
    this->Rotation = 0;
    this->Sprite = Sprite;
    this->Color = Color;
    this->Name = CFStrDup(name);

    return this;
}

/**
 * Draw
 * 
 * @param renderer to draw sprite with
 */
method void Draw(
    GameObjectRef this,
    DNAArrayRendererRef renderer)
{
    DNARect bounds = { this->Position.x, this->Position.y,
        this->Size.x, this->Size.y };

    Draw(renderer, this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

/**
 * ToString
 */
method char* ToString(GameObjectRef this)
{
    return "GameObject";
}
