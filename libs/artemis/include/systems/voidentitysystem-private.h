#pragma once
#include "cfw.h"
#include "core/component-private.h"
#include "core/component.h"
#include "core/entity-private.h"
#include "core/entity.h"
#include "core/world-private.h"
#include "core/world.h"
#include "systems/voidentitysystem.h"

// method bool CheckProcessing(ECSVoidEntitySystem* self);
/**
 * Used to generate a unique bit for each system.
 * Only used internally in EntitySystem.
 */
struct ECSVoidEntitySystem {
    CFObject obj;
    ECSIVoidEntitySystem* vptr;
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
