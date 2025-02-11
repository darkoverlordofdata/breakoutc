#pragma once
#include "cfw.h"
#include "componenttype.h"

typedef struct ECSComponentTypeFactory ECSComponentTypeFactory;
extern const CFClass* ECSComponentTypeFactoryClass;

extern method void* New(ECSComponentTypeFactory* this);

extern method ECSComponentType* GetTypeFor(ECSComponentTypeFactory* this, CFClass* c);

extern method int GetIndexFor(ECSComponentTypeFactory* this, CFClass* c);
