#pragma once
#include "cfw.h"
#include "componentmanager.h"
#include "ecs.h"


struct ECSComponentManager
{
    CFObject obj;
    ECSManager* override;
    ECSWorld* World;
    CFArray* ComponentsByType; // Array of Array
    CFArray* Deleted;
    ECSComponentTypeFactory* TypeFactory;
};

