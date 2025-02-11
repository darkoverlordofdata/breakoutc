#pragma once
#include "entity.h"
#include "cfw.h"
#include "ecs.h"

/**
 * The entity class. Cannot be instantiated outside the framework, you must
 * create new entities using World.
 * 
 * @author Arni Arent
 * 
 */
struct ECSEntity {
    CFObject obj;
    char* Name;
    int Id;
    CFUuid* uuid;
    char* key;
    CFBitVector* ComponentBits;
    CFBitVector* SystemBits;
    ECSWorld* World;
    ECSEntityManager* EntityManager;
    ECSComponentManager* ComponentManager;
};
