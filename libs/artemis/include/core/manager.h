#pragma once
#include "cfw.h"

typedef struct ECSWorld ECSWorld;
typedef struct ECSEntity ECSEntity;
typedef struct ECSManager ECSManager;

typedef struct ECSIManager ECSIManager;
typedef struct ECSManager ECSManager;
extern const CFClass* ECSManagerClass;

struct ECSIManager {
    //ECSIEntityObserver
    void (*Added)(void* this, ECSEntity* entity);
    void (*Changed)(void* this, ECSEntity* entity);
    void (*Deleted)(void* this, ECSEntity* entity);
    void (*Disabled)(void* this, ECSEntity* entity);
    void (*Enabled)(void* this, ECSEntity* entity);
    void (*Begin)(void* this);
    void (*End)(void* this);

    //ECSIManager
    void (*Initialize)(void* this);
};

// typedefs for virtual methods
typedef void (*ECSManager_Added)(ECSManager* this, ECSEntity* entity);
typedef void (*ECSManager_Changed)(ECSManager* this, ECSEntity* entity);
typedef void (*ECSManager_Deleted)(ECSManager* this, ECSEntity* entity);
typedef void (*ECSManager_Disabled)(ECSManager* this, ECSEntity* entity);
typedef void (*ECSManager_Enabled)(ECSManager* this, ECSEntity* entity);
typedef void (*ECSManager_Begin)(ECSManager* this);
typedef void (*ECSManager_End)(ECSManager* this);
typedef void (*ECSManager_Initialize)(ECSManager* this);


extern method void* New(ECSManager* this, ECSIManager* vptr);

extern method void Initialize(ECSManager* this);

extern method void SetWorld(ECSManager* this, ECSWorld* world);

extern method ECSWorld* GetWorld(ECSManager* this);

extern method void Added(ECSManager* this, ECSEntity* entity);

extern method void Changed(ECSManager* this, ECSEntity* entity);

extern method void Deleted(ECSManager* this, ECSEntity* entity);

extern method void Disabled(ECSManager* this, ECSEntity* entity);

extern method void Enabled(ECSManager* this, ECSEntity* entity);
