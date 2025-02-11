#pragma once
#include "cfw.h"
#include "core/component-private.h"
#include "core/component.h"
#include "core/entity-private.h"
#include "core/entity.h"
#include "core/entitysystem-private.h"
#include "core/entitysystem.h"
#include "core/world-private.h"
#include "core/world.h"
#include "systems/entityprocessingsystem.h"
/**
 * A typical entity system. Use this when you need to process entities possessing the
 * provided component types.
 *
 * @author Arni Arent
 *
 */
struct ECSEntityProcessingSystem {
    CFObject obj;
    ECSIEntityProcessingSystem* vptr;
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
