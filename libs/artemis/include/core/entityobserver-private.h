#pragma once
#include "cfw.h"
#include "ecs.h"
#include "entityobserver.h"

struct ECSEntityObserver {
    CFObject obj;
    ECSIEntityObserver* vptr;
};

