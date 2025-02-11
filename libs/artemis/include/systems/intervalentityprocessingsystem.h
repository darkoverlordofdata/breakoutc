#pragma once
#include "cfw.h"
#include "core/world.h"
#include "core/entity.h"
#include "core/aspect.h"
#include "systems/entityprocessingsystem.h"

typedef struct ECSIIntervalEntityProcessingSystem ECSIIntervalEntityProcessingSystem;
typedef struct ECSIntervalEntityProcessingSystem ECSIntervalEntityProcessingSystem;
extern const CFClass* ECSIntervalEntityProcessingSystemClass;

struct ECSIIntervalEntityProcessingSystem 
{
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

    //ECSIEntityProcessingSystem
    void (*ProcessEach)(void* this, ECSEntity* e);
};

extern method void* New(ECSIntervalEntityProcessingSystem* this, ECSAspect* aspect, float interval, ECSIIntervalEntityProcessingSystem* vptr);

extern method void Begin(ECSIntervalEntityProcessingSystem* this);

extern method void Process(ECSIntervalEntityProcessingSystem* this);

extern method void End(ECSIntervalEntityProcessingSystem* this);

extern method void ProcessEntities(ECSIntervalEntityProcessingSystem* this, CFArray* entities);

extern method bool CheckProcessing(ECSIntervalEntityProcessingSystem* this);

extern method void Initialize(ECSIntervalEntityProcessingSystem* this);

extern method void Inserted(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);

extern method void Removed(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);

extern method void Check(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);

extern method void RemoveFromSystem(ECSIntervalEntityProcessingSystem* this, ECSEntity* e); 

extern method void InsertToSystem(ECSIntervalEntityProcessingSystem* this, ECSEntity* e); 

extern method void Added(ECSIntervalEntityProcessingSystem* this, ECSEntity* entity);

extern method void Changed(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);

extern method void Deleted(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);

extern method void Disabled(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);

extern method void Enabled(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);

extern method void SetWorld(ECSIntervalEntityProcessingSystem* this, ECSWorld* world);

extern method bool IsPassive(ECSIntervalEntityProcessingSystem* this);

extern method void SetPassive(ECSIntervalEntityProcessingSystem* this, bool passive);

extern method CFArray* GetActive(ECSIntervalEntityProcessingSystem* this);

extern method void ProcessEach(ECSIntervalEntityProcessingSystem* this, ECSEntity* e);
