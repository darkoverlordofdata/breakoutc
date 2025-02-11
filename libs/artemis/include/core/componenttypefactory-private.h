#pragma once
#include "cfw.h"
#include "componenttypefactory.h"
#include "ecs.h"

struct ECSComponentTypeFactory {
    CFObject obj;
    CFObject* override;
    CFMap* ComponentTypes;
    int ComponentTypeCount;
    CFArray* Types;
};
