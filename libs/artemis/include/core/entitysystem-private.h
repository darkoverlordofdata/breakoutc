#pragma once
#include "cfw.h"
#include "ecs.h"
#include "entityobserver-private.h"
#include "entityobserver.h"
#include "entitysystem.h"

// method bool CheckProcessing(ECSEntitySystem* self);
/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
struct ECSSystemIndexManager {
    int Index;
    CFMap* Indices;
};

struct ECSEntitySystem {
    CFObject obj;
    ECSIEntitySystem* vptr;
    ECSWorld* World;
    int SystemIndex;
    CFArray* Actives;
    ECSAspect* Aspect;
    CFBitVector* AllSet;
    CFBitVector* ExclusionSet;
    CFBitVector* OneSet;
    bool Passive;
    bool IsDummy;
};
