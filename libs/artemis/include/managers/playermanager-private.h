#pragma once
#include "cfw.h"
#include "ecs.h"
#include "playermanager.h"

struct ECSPlayerManager {
    CFObject obj;
    ECSIManager* vptr;
    ECSWorld* World;
    CFMap* PlayerByEntity;
    CFMap* EntitiesByPlayer;
};
