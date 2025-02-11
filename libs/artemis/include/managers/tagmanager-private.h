#pragma once
#include "cfw.h"
#include "ecs.h"
#include "tagmanager.h"

struct ECSTagManager {
    CFObject obj;
    ECSIManager* vptr;
    ECSWorld* World;
    CFMap* EntitiesByTag;
    CFMap* TagsByEntity;
};
