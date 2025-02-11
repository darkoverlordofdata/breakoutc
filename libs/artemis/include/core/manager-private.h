#pragma once
#include "cfw.h"
#include "ecs.h"
#include "entityobserver-private.h"
#include "entityobserver.h"
#include "manager.h"

struct ECSManager {
    CFObject obj;
    ECSIManager* vptr;
    ECSWorld* World;
};
