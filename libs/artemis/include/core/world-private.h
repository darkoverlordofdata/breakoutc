#pragma once
#include "cfw.h"
#include "ecs.h"
#include "world.h"

/**
 * The primary instance for the framework. It contains all the managers.
 * 
 * You must use this to create, delete and retrieve entities.
 * 
 * It is also important to set the delta each game loop iteration, and initialize before game loop.
 * 
 * @author Arni Arent
 * 
 */
struct ECSWorld
{
    CFObject obj;
    CFObject* override;
    ECSEntityManager* Em;
    ECSComponentManager* Cm;
    float Delta;
    CFArray* Added;
    CFArray* Changed;
    CFArray* Deleted;
    CFArray* Enable;
    CFArray* Disable;
    CFMap* Managers;
    CFArray* ManagersBag;
    CFMap* Systems;
    CFArray* SystemsBag;
    // Map* ECSEntityTemplates;
};
