#pragma once
#include "cfw.h"
#include "componenttype.h"
#include "ecs.h"

struct ECSComponentType
{
    CFObject obj;
    CFObject* override;
    int Index;
    CFClass* Type;
};
