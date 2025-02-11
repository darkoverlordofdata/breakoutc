#pragma once
#include "cfw.h"

typedef struct ECSComponentType ECSComponentType;
extern const CFClass* ECSComponentTypeClass;

extern int ECSUniqueComponentIndex;

extern method void* New(ECSComponentType* this, CFClass* type);
extern method char* GetName(ECSComponentType* this);
extern method int GetIndex(ECSComponentType* this);
