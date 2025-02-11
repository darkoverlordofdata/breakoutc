#pragma once
#include "cfw.h"

typedef struct ECSGroupManager ECSGroupManager;
extern const CFClass* ECSGroupManagerClass;

typedef struct ECSEntity ECSEntity;
typedef struct ECSWorld ECSWorld;

// typedefs for overrides
typedef void (*ECSGroupManager_Initialize)(ECSGroupManager* this);
typedef void (*ECSGroupManager_Added)(ECSGroupManager* this, ECSEntity* entity);
typedef void (*ECSGroupManager_Changed)(ECSGroupManager* this, ECSEntity* entity);
typedef void (*ECSGroupManager_Deleted)(ECSGroupManager* this, ECSEntity* entity);
typedef void (*ECSGroupManager_Disabled)(ECSGroupManager* this, ECSEntity* entity);
typedef void (*ECSGroupManager_Enabled)(ECSGroupManager* this, ECSEntity* entity);


extern method void* New(ECSGroupManager* this);

extern method void Initialize(ECSGroupManager* this);

extern method void SetWorld(ECSGroupManager* this, ECSWorld* world);

extern method ECSWorld* GetWorld(ECSGroupManager* this);

extern method void Added(ECSGroupManager* this, ECSEntity* entity);

extern method void Changed(ECSGroupManager* this, ECSEntity* entity);

extern method void Deleted(ECSGroupManager* this, ECSEntity* entity);

extern method void Disabled(ECSGroupManager* this, ECSEntity* entity);

extern method void Enabled(ECSGroupManager* this, ECSEntity* entity);

extern method void Add(ECSGroupManager* this, ECSEntity* e, char* group);

extern method void Remove(ECSGroupManager* this, ECSEntity* e, char* group);

extern method void RemoveFromAllGroups(ECSGroupManager* this, ECSEntity* e);

extern method CFArray* GetEntities(ECSGroupManager* this, char* group);

extern method CFArray* GetGroups(ECSGroupManager* this, ECSEntity* e);

extern method bool IsInAnyGroup(ECSGroupManager* this, ECSEntity* e);

extern method bool IsInGroup(ECSGroupManager* this, ECSEntity* e, char* group);

