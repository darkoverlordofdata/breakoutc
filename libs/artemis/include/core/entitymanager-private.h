#pragma once
#include "entitymanager.h"
#include "cfw.h"
#include "ecs.h"

/*
 * Used only internally to generate distinct ids for entities and reuse them.
 */
struct ECSIdentifierPool
{
    CFArray* Ids;
    int NextAvailableId;

};

struct ECSEntityManager
{
    CFObject obj;
    ECSManager* override;
    ECSWorld* World;
    CFArray* Entities;
    CFBitVector* Disabled;
    int Active;
    int Added;
    int Created;
    int Deleted;
    ECSIdentifierPool* IdentifierPool;
};

