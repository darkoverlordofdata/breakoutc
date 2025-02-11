#pragma once
#include "cfw.h"
#include "ecs.h"
#include "tagmanager.h"

struct ECSTeamManager {
    CFObject obj;
    ECSIManager* vptr;
    ECSWorld* World;
    CFMap* PlayersByTeam;
    CFMap* TeamByPlayer;
};
