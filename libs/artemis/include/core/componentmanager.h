#pragma once
#include "cfw.h"
#include "entity.h"

typedef struct ECSComponentManager ECSComponentManager;
extern const CFClass* ECSComponentManagerClass;

typedef struct ECSEntity ECSEntity;
typedef struct ECSComponentManager ECSComponentManager;
typedef struct ECSComponentType ECSComponentType;
typedef struct ECSComponentTypeFactory ECSComponentTypeFactory;

extern method CFBitVector* GetComponentBits(ECSEntity* this);
extern method int GetId(ECSEntity* this);

extern method void* New(ECSComponentManager* this);

extern method ECSComponentTypeFactory* GetTypeFactory(ECSComponentManager* this);

extern method void RemoveComponentsOfEntity(ECSComponentManager* this, ECSEntity* e);

extern method void AddComponent(ECSComponentManager* this, ECSEntity* e, ECSComponentType* type, ECSComponent* component);

extern method void RemoveComponent(ECSComponentManager* this, ECSEntity* e, ECSComponentType* type);

extern method CFArray* GetComponentsByType(ECSComponentManager* this, ECSComponentType* type);

extern method ECSComponent* GetComponent(ECSComponentManager* this, ECSEntity* e, ECSComponentType* type);

extern method CFArray* GetComponentsFor(ECSComponentManager* this, ECSEntity* e, CFArray* fillBag);

extern method void Deleted(ECSComponentManager* this, ECSEntity* e);

extern method void Clean(ECSComponentManager* this);

extern method void Added(ECSComponentManager* this, ECSEntity* entity);

extern method void Changed(ECSComponentManager* this, ECSEntity* entity);

extern method void Disabled(ECSComponentManager* this, ECSEntity* entity);

extern method void Enabled(ECSComponentManager* this, ECSEntity* entity);
