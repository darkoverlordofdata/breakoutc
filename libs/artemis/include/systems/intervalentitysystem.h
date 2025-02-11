#pragma once
#include "cfw.h"
#include "core/aspect.h"
#include "core/entity.h"
#include "core/world.h"
// #include "core/entityprocessingsystem.h"

typedef struct ECSIIntervalEntitySystem ECSIIntervalEntitySystem;
typedef struct ECSIntervalEntitySystem ECSIntervalEntitySystem;
extern const CFClass* ECSIntervalEntitySystemClass;

struct ECSIIntervalEntitySystem {
    //ECSIEntityObserver
    void (*Added)(void* this, ECSEntity* entity);
    void (*Changed)(void* this, ECSEntity* entity);
    void (*Deleted)(void* this, ECSEntity* entity);
    void (*Disabled)(void* this, ECSEntity* entity);
    void (*Enabled)(void* this, ECSEntity* entity);
    void (*Begin)(void* this);
    void (*End)(void* this);

    //ECSIEntitySystem
    void (*ProcessEntities)(void* this, CFArray* entities);
    bool (*CheckProcessing)(void* this);
    void (*Initialize)(void* this);
    void (*Inserted)(void* this, ECSEntity* e);
    void (*Removed)(void* this, ECSEntity* e);
};

extern method void* New(ECSIntervalEntitySystem* this, ECSAspect* aspect, float interval, ECSIIntervalEntitySystem* vptr);

extern method void Begin(ECSIntervalEntitySystem* this);

extern method void Process(ECSIntervalEntitySystem* this);

extern method void End(ECSIntervalEntitySystem* this);

extern method void ProcessEntities(ECSIntervalEntitySystem* this, CFArray* entities);

extern method bool CheckProcessing(ECSIntervalEntitySystem* this);

extern method void Initialize(ECSIntervalEntitySystem* this);

extern method void Inserted(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void Removed(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void Check(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void RemoveFromSystem(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void InsertToSystem(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void Added(ECSIntervalEntitySystem* this, ECSEntity* entity);

extern method void Changed(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void Deleted(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void Disabled(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void Enabled(ECSIntervalEntitySystem* this, ECSEntity* e);

extern method void SetWorld(ECSIntervalEntitySystem* this, ECSWorld* world);

extern method bool IsPassive(ECSIntervalEntitySystem* this);

extern method void SetPassive(ECSIntervalEntitySystem* this, bool passive);

extern method CFArray* GetActive(ECSIntervalEntitySystem* this);
