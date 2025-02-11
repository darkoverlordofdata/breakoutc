#pragma once
#include "cfw.h"
#include "world.h"
#include "entity.h"
#include "component.h"
#include "componenttypefactory.h"

typedef struct ECSAspect ECSAspect;
extern const CFClass* ECSAspectClass;

typedef struct ECSWorld ECSWorld;
typedef struct ECSAspect ECSAspect;
typedef struct ECSComponentTypeFactory ECSComponentTypeFactory;

extern ECSComponentTypeFactory* ECSAspect_TypeFactory;

extern method void* New(ECSAspect* this);

extern method void SetTypeFactory(ECSComponentTypeFactory* typeFactory);

extern method void SetWorld(ECSAspect* this, ECSWorld* world);

extern method CFBitVector* GetAllSet(ECSAspect* this);

extern method CFBitVector* GetExclusionSet(ECSAspect* this);

extern method CFBitVector* GetOneSet(ECSAspect* this);

extern method ECSAspect* All(ECSAspect* this, int count, va_list _args);

extern method ECSAspect* Exclude(ECSAspect* this, int count, va_list _args);

extern method ECSAspect* One(ECSAspect* this, int count, va_list _args);

extern method ECSAspect* GetAspectForAll(int count, ...);

extern method ECSAspect* GetAspectForOne(int count, ...);

extern method ECSAspect* GetAspectForNone(void);