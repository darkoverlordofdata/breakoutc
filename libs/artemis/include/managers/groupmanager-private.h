#pragma once
#include "groupmanager.h"
#include "cfw.h"
#include "ecs.h"

struct ECSGroupManager {
    CFObject object;
    ECSIManager* vptr;
    ECSWorld* World;
    CFMap* EntitiesByGroup;
    CFMap* GroupsByEntity;
};
