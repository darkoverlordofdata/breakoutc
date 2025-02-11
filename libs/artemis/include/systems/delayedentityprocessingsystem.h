#pragma once
#include "cfw.h"
#include "core/world.h"
#include "core/entity.h"
#include "core/aspect.h"
#include "systems/entityprocessingsystem.h"

typedef struct ECSIDelayedEntityProcessingSystem ECSIDelayedEntityProcessingSystem;
typedef struct ECSDelayedEntityProcessingSystem ECSDelayedEntityProcessingSystem;
extern const CFClass* ECSDelayedEntityProcessingSystemClass;

struct ECSIDelayedEntityProcessingSystem {

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

    //ECSIDelayedEntityProcessingSystem
    float (*GetRemainingDelay)(void* this, ECSEntity* e);
    void (*ProcessDelta)(void* this, ECSEntity* e, float accumulatedDelta);
    void (*ProcessExpired)(void* this, ECSEntity* e);
};


extern method void* New(ECSDelayedEntityProcessingSystem* this, ECSAspect* aspect, ECSIDelayedEntityProcessingSystem* vptr);

extern method void Begin(ECSDelayedEntityProcessingSystem* this);

extern method void Process(ECSDelayedEntityProcessingSystem* this);

extern method void End(ECSDelayedEntityProcessingSystem* this);

extern method void ProcessEntities(ECSDelayedEntityProcessingSystem* this, CFArray* entities);

extern method bool CheckProcessing(ECSDelayedEntityProcessingSystem* this);

extern method void Initialize(ECSDelayedEntityProcessingSystem* this);

extern method void Inserted(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void Removed(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void Check(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void RemoveFromSystem(ECSDelayedEntityProcessingSystem* this, ECSEntity* e); 

extern method void InsertToSystem(ECSDelayedEntityProcessingSystem* this, ECSEntity* e); 

extern method void Added(ECSDelayedEntityProcessingSystem* this, ECSEntity* entity);

extern method void Changed(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void Deleted(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void Disabled(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void Enabled(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void SetWorld(ECSDelayedEntityProcessingSystem* this, ECSWorld* world);

extern method bool IsPassive(ECSDelayedEntityProcessingSystem* this);

extern method void SetPassive(ECSDelayedEntityProcessingSystem* this, bool passive);

extern method CFArray* GetActive(ECSDelayedEntityProcessingSystem* this);

extern method float GetRemainingDelay(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void ProcessDelta(ECSDelayedEntityProcessingSystem* this, ECSEntity* e, float accumulatedDelta);

extern method void ProcessExpired(ECSDelayedEntityProcessingSystem* this, ECSEntity* e);

extern method void Restart(ECSDelayedEntityProcessingSystem* this, float delay);

extern method void OfferDelay(ECSDelayedEntityProcessingSystem* this, float delay);

extern method float GetInitialTimeDelay(ECSDelayedEntityProcessingSystem* this);

extern method float GetRemainingTimeUntilProcessing(ECSDelayedEntityProcessingSystem* this);

extern method bool IsRunning(ECSDelayedEntityProcessingSystem* this);

extern method void Stop(ECSDelayedEntityProcessingSystem* this);

