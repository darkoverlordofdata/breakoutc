#pragma once
#include "cfw.h"
#include "core/world.h"
#include "core/entity.h"
#include "core/aspect.h"

typedef struct ECSIVoidEntitySystem ECSIVoidEntitySystem;
typedef struct ECSVoidEntitySystem ECSVoidEntitySystem;
extern const CFClass* ECSVoidEntitySystemClass;

struct ECSIVoidEntitySystem {
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

    //ECSIVoidEntitySystem
    void (*ProcessSystem)(void* this);
};

extern method void* New(ECSVoidEntitySystem* this, ECSIVoidEntitySystem* vptr);

extern method void Begin(ECSVoidEntitySystem* this);

extern method void Process(ECSVoidEntitySystem* this);

extern method void End(ECSVoidEntitySystem* this);

extern method void ProcessEntities(ECSVoidEntitySystem* this, CFArray* entities);

extern method bool CheckProcessing(ECSVoidEntitySystem* this);

extern method void Initialize(ECSVoidEntitySystem* this);

extern method void Inserted(ECSVoidEntitySystem* this, ECSEntity* e);

extern method void Removed(ECSVoidEntitySystem* this, ECSEntity* e);

extern method void Check(ECSVoidEntitySystem* this, ECSEntity* e);

extern method void RemoveFromSystem(ECSVoidEntitySystem* this, ECSEntity* e); 

extern method void InsertToSystem(ECSVoidEntitySystem* this, ECSEntity* e); 

extern method void Added(ECSVoidEntitySystem* this, ECSEntity* entity);

extern method void Changed(ECSVoidEntitySystem* this, ECSEntity* e);

extern method void Deleted(ECSVoidEntitySystem* this, ECSEntity* e);

extern method void Disabled(ECSVoidEntitySystem* this, ECSEntity* e);

extern method void Enabled(ECSVoidEntitySystem* this, ECSEntity* e);

extern method void SetWorld(ECSVoidEntitySystem* this, ECSWorld* world);

extern method bool IsPassive(ECSVoidEntitySystem* this);

extern method void SetPassive(ECSVoidEntitySystem* this, bool passive);

extern method CFArray* GetActive(ECSVoidEntitySystem* this);

extern method void ProcessSystem(ECSVoidEntitySystem* this);

