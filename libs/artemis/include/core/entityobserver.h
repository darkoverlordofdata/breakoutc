#pragma once
#include "cfw.h"


typedef struct ECSIEntityObserver ECSIEntityObserver;
typedef struct ECSEntityObserver ECSEntityObserver;
extern const CFClass* ECSEntityObserverClass;

typedef struct ECSEntity ECSEntity;
// typedef struct ECS ECS;

typedef void (*ECSEntityProc)(void* this, void* entity);
struct ECSIEntityObserver {
    void (*Added)(void* this, ECSEntity* entity);
    void (*Changed)(void* this, ECSEntity* entity);
    void (*Deleted)(void* this, ECSEntity* entity);
    void (*Disabled)(void* this, ECSEntity* entity);
    void (*Enabled)(void* this, ECSEntity* entity);
};

extern method void* New(ECSEntityObserver* this, ECSIEntityObserver* vptr);

extern method void Added(ECSEntityObserver* this, ECSEntity* entity);

extern method void Changed(ECSEntityObserver* this, ECSEntity* entity);

extern method void Deleted(ECSEntityObserver* this, ECSEntity* entity);

extern method void Disabled(ECSEntityObserver* this, ECSEntity* entity);

extern method void Enabled(ECSEntityObserver* this, ECSEntity* entity);

