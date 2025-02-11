#pragma once
#include "cfw.h"

typedef struct ECSComponent ECSComponent;
extern const CFClass* ECSComponentClass;

extern method void* New(ECSComponent* this);
