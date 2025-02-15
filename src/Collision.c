/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Collision.h"
#include "Demo.h"

static struct __CFClass class = {
    .name = "Collision",
    .size = sizeof(Collision),
};
const CFClassRef CollisionClass = &class;

/**
 * Collision Result Tuple
 * 
 * @param isTrue collided?
 * @param dir direction from
 * @param Vec2 difference point
 */
method void* New(Collision* this, bool isTrue, Direction dir, Vec2 vec)
{
    this->IsTrue = isTrue;
    this->Dir = dir;
    this->Vec = vec;
    return this;
}
