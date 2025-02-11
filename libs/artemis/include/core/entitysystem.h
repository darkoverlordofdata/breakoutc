#pragma once
#include "cfw.h"

typedef struct ECSIEntitySystem ECSIEntitySystem;
typedef struct ECSEntitySystem ECSEntitySystem;
extern const CFClass* ECSEntitySystemClass;

typedef struct ECSAspect ECSAspect;
typedef struct ECSEntity ECSEntity;
typedef struct ECSWorld ECSWorld;

struct ECSIEntitySystem {

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

typedef void (*ECSEntitySystem_ProcessEach)(ECSEntitySystem* this, ECSEntity* entity);

typedef struct ECSSystemIndexManager ECSSystemIndexManager;
extern method int GetIndexFor(char* es);

extern method void* New(ECSEntitySystem* this, ECSAspect* aspect, ECSIEntitySystem* vptr);

extern method void Begin(ECSEntitySystem* this);

extern method void Process(ECSEntitySystem* this);

extern method void End(ECSEntitySystem* this);

extern method void ProcessEntities(ECSEntitySystem* this, CFArray* entities);

extern method bool CheckProcessing(ECSEntitySystem* this);

extern method void Initialize(ECSEntitySystem* this);

extern method void Inserted(ECSEntitySystem* this, ECSEntity* e);

extern method void Removed(ECSEntitySystem* this, ECSEntity* e);

extern method void Check(ECSEntitySystem* this, ECSEntity* e); 

extern method void RemoveFromSystem(ECSEntitySystem* this, ECSEntity* e);

extern method void InsertToSystem(ECSEntitySystem* this, ECSEntity* e);

extern method void Added(ECSEntitySystem* this, ECSEntity* entity);

extern method void Changed(ECSEntitySystem* this, ECSEntity* e);

extern method void Deleted(ECSEntitySystem* this, ECSEntity* e);

extern method void Disabled(ECSEntitySystem* this, ECSEntity* e);

extern method void Enabled(ECSEntitySystem* this, ECSEntity* e);

extern method void SetWorld(ECSEntitySystem* this, ECSWorld* world);

extern method bool IsPassive(ECSEntitySystem* this);

extern method void SetPassive(ECSEntitySystem* this, bool passive);

extern method CFArray* GetActive(ECSEntitySystem* this);
