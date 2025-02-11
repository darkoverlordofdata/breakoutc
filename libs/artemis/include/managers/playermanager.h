#pragma once
#include "cfw.h"

typedef struct ECSPlayerManager ECSPlayerManager;
extern const CFClass* ECSPlayerManagerClass;

typedef struct ECSEntity ECSEntity;
typedef struct ECSWorld ECSWorld;

extern method void* New(ECSPlayerManager* this);

extern method void Initialize(ECSPlayerManager* this);

extern method void SetWorld(ECSPlayerManager* this, ECSWorld* world);

extern method ECSWorld* GetWorld(ECSPlayerManager* this);

extern method void Added(ECSPlayerManager* this, ECSEntity* entity);

extern method void Changed(ECSPlayerManager* this, ECSEntity* entity);

extern method void Deleted(ECSPlayerManager* this, ECSEntity* entity);

extern method void Disabled(ECSPlayerManager* this, ECSEntity* entity);

extern method void Enabled(ECSPlayerManager* this, ECSEntity* entity);

extern method void SetPlayer(ECSPlayerManager* this, ECSEntity* e, char* player);

extern method CFArray* GetEntitiesOfPlayer(ECSPlayerManager* this, char* player);

extern method void RemoveFromPlayer(ECSPlayerManager* this, ECSEntity* e);

extern method char* GetPlayer(ECSPlayerManager* this, ECSEntity* e);
