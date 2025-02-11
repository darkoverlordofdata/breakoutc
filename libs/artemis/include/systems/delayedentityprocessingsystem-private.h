#pragma once
#include "cfw.h"
#include "core/component.h"
#include "core/entity.h"
#include "core/entitysystem.h"
#include "core/world.h"
#include "systems/entityprocessingsystem.h"
#include "systems/delayedentityprocessingsystem.h"

/**
 * The purpose of this class is to allow systems to execute at varying intervals.
 *
 * An example system would be an ExpirationSystem, that deletes entities after a certain
 * lifetime. Instead of running a system that decrements a timeLeft value for each
 * entity, you can simply use this system to execute in a future at a time of the shortest
 * lived entity, and then reset the system to run at a time in a future at a time of the
 * shortest lived entity, etc.
 *
 * Another example system would be an AnimationSystem. You know when you have to animate
 * a certain entity, e.g. in 300 milliseconds. So you can set the system to run in 300 ms.
 * to perform the animation.
 *
 * This will save CPU cycles in some scenarios.
 *
 * Implementation notes:
 * In order to start the system you need to override the inserted(Entity e) method,
 * look up the delay time from that entity and offer it to the system by using the
 * offerDelay(float delay) method.
 * Also, when processing the entities you must also call offerDelay(float delay)
 * for all valid entities.
 *
 * @author Arni Arent
 *
 */
struct ECSDelayedEntityProcessingSystem {
    CFObject obj;
    ECSIDelayedEntityProcessingSystem* vptr;
    ECSWorld* World;
    int SystemIndex;
    CFArray* Actives;
    ECSAspect* Aspect;
    CFBitVector* AllSet;
    CFBitVector* ExclusionSet;
    CFBitVector* OneSet;
    bool Passive;
    bool IsDummy;
    /** The time until an entity should be processed. */
    float Delay;
    /**	If the system is running and counting down delays. */
    bool Running;
    /** The countdown, accumulates world deltas. */
    float Acc;
};

