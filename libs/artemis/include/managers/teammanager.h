#pragma once
#include "cfw.h"

typedef struct ECSTeamManager ECSTeamManager;
extern const CFClass* ECSTeamManagerClass;

typedef struct ECSEntity ECSEntity;
typedef struct ECSWorld ECSWorld;

extern method void* New(ECSTeamManager* this);

extern method void Initialize(ECSTeamManager* this);

extern method void SetWorld(ECSTeamManager* this, ECSWorld* world);

extern method ECSWorld* GetWorld(ECSTeamManager* this);

extern method void Added(ECSTeamManager* this, ECSEntity* entity);

extern method void Changed(ECSTeamManager* this, ECSEntity* entity);

extern method void Deleted(ECSTeamManager* this, ECSEntity* entity);

extern method void Disabled(ECSTeamManager* this, ECSEntity* entity);

extern method void Enabled(ECSTeamManager* this, ECSEntity* entity);

extern method char* GetTeam(ECSTeamManager* this, char* player);

extern method void SetTeam(ECSTeamManager* this, char* player, char* team);

extern method CFArray* GetPlayers(ECSTeamManager* this, char* team);

extern method void RemoveFromTeam(ECSTeamManager* this, char* player);
