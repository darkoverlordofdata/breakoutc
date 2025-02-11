#pragma once
#include "cfw.h"
#include "core/world.h"
#include "core/entity.h"
#include "core/aspect.h"

typedef struct ECSIEntityProcessingSystem ECSIEntityProcessingSystem;
typedef struct ECSEntityProcessingSystem ECSEntityProcessingSystem;
extern const CFClass* ECSEntityProcessingSystemClass;

typedef struct ECSEntity ECSEntity;
typedef struct ECSWorld ECSWorld;

struct ECSIEntityProcessingSystem 
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

typedef void (*ECSEntityProcessingSystem_ProcessEach)(ECSEntityProcessingSystem* this, ECSEntity* entity);

extern method void* New(ECSEntityProcessingSystem* this, ECSAspect* aspect, ECSIEntityProcessingSystem* vptr);

extern method void Begin(ECSEntityProcessingSystem* this);

extern method void Process(ECSEntityProcessingSystem* this);

extern method void End(ECSEntityProcessingSystem* this);

extern method void ProcessEntities(ECSEntityProcessingSystem* this, CFArray* entities);

extern method bool CheckProcessing(ECSEntityProcessingSystem* this);

extern method void Initialize(ECSEntityProcessingSystem* this);

extern method void Inserted(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void Removed(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void Check(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void RemoveFromSystem(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void InsertToSystem(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void Added(ECSEntityProcessingSystem* this, ECSEntity* entity);

extern method void Changed(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void Deleted(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void Disabled(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void Enabled(ECSEntityProcessingSystem* this, ECSEntity* e);

extern method void SetWorld(ECSEntityProcessingSystem* this, ECSWorld* world);

extern method bool IsPassive(ECSEntityProcessingSystem* this);

extern method void SetPassive(ECSEntityProcessingSystem* this, bool passive);

extern method CFArray* GetActive(ECSEntityProcessingSystem* this);

extern method void ProcessEach(ECSEntityProcessingSystem* this, ECSEntity* e);

