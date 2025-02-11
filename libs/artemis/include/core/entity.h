#pragma once
#include "cfw.h"

typedef struct ECSEntity ECSEntity;
extern const CFClass* ECSEntityClass;

typedef struct ECSWorld ECSWorld;
typedef struct ECSComponent ECSComponent;
typedef struct ECSComponentType ECSComponentType;

extern method void* New(ECSEntity* this, ECSWorld* world, int id, char* name);

extern method CFBitVector* GetComponentBits(ECSEntity* this);

extern method CFBitVector* GetSystemBits(ECSEntity* this);

extern method int GetId(ECSEntity* this);

extern method CFUuid* GetUUID(ECSEntity* this);

extern method void Reset(ECSEntity* this);

extern method ECSEntity* AddComponent(ECSEntity* this, ECSComponent* component);

extern method ECSComponentType* GetTypeFor(ECSEntity* this, CFClass* c);

extern method ECSEntity* RemoveComponentInstance(ECSEntity* this, ECSComponent* component);

extern method ECSEntity* RemoveComponent(ECSEntity* this, ECSComponentType* type);

extern method ECSEntity* RemoveComponentByType(ECSEntity* this, CFClass* type);

extern method bool IsActive(ECSEntity* this);

extern method bool IsEnabled(ECSEntity* this);

extern method ECSComponent* GetComponent(ECSEntity* this, ECSComponentType* type);

extern method ECSComponent* GetComponentByType(ECSEntity* this, CFClass* type);

extern method CFArray* GetCompoments(ECSEntity* this, CFArray* fillBag);

extern method void AddToWorld(ECSEntity* this);

extern method void ChangedInWorld(ECSEntity* this);

extern method void DeleteFromWorld(ECSEntity* this);

extern method void Enable(ECSEntity* this);

extern method void Disable(ECSEntity* this);

extern method ECSWorld* GetWorld(ECSEntity* this);
