#pragma once
#include "cfw.h"
#include "entity.h"

typedef void (*ECSPerformer)(void* observer, ECSEntity* entity);
// typedef void (^ECSPerformer)(void* observer, ECSEntity* entity);

typedef struct ECSWorld ECSWorld;
extern const CFClass* ECSWorldClass;

typedef struct ECSEntity ECSEntity;
typedef struct ECSManager ECSManager;
typedef struct ECSEntitySystem ECSEntitySystem;
typedef struct ECSEntityManager ECSEntityManager;
typedef struct ECSComponentManager ECSComponentManager;

extern method void* New(ECSWorld* this);

extern method void Initialize(ECSWorld* this); 

extern method ECSEntityManager* GetEntityManager(ECSWorld* this); 

extern method ECSComponentManager* GetComponentManager(ECSWorld* this); 

extern method ECSManager* SetManager(ECSWorld* this, ECSManager* manager); 

extern method ECSManager* GetManager(ECSWorld* this, CFClass* type); 

extern method void DeleteManager(ECSWorld* this, ECSManager* manager); 

extern method float GetDelta(ECSWorld* this); 

extern method void SetDelta(ECSWorld* this, float delta); 

extern method void AddEntity(ECSWorld* this, ECSEntity* e); 

extern method void ChangedEntity(ECSWorld* this, ECSEntity* e); 

extern method void DeleteEntity(ECSWorld* this, ECSEntity* e); 

extern method void Enable(ECSWorld* this, ECSEntity* e); 

extern method void Disable(ECSWorld* this, ECSEntity* e); 

extern method ECSEntity* CreateEntity(ECSWorld* this, char* name); 

extern method ECSEntity* GetEntity(ECSWorld* this, int entityId); 

extern method CFArray* GetSystems(ECSWorld* this); 

extern method ECSEntitySystem* SetSystem(ECSWorld* this, ECSEntitySystem* system, bool passive); 

extern method ECSEntitySystem* SetSystem(ECSWorld* this, ECSEntitySystem* system); 

extern method void DeleteSystem(ECSWorld* this, ECSEntitySystem* system); 

extern method void NotifySystems(ECSWorld* this, ECSPerformer perform, ECSEntity* e); 

extern method void NotifyManagers(ECSWorld* this, ECSPerformer perform, ECSEntity* e); 

extern method ECSEntitySystem* GetSystem(ECSWorld* this, CFClass* type); 

extern method void Check(ECSWorld* this, CFArray* entities, ECSPerformer perform); 

extern method void Update(ECSWorld* this); 

extern method void Draw(ECSWorld* this);
