#include "managers/playermanager.h"
#include "cfw.h"
#include "core/entity-private.h"
#include "core/entity.h"
#include "core/manager-private.h"
#include "core/manager.h"
#include "core/world.h"
#include "ecs.h"
#include "managers/playermanager-private.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSPlayerManager);

#define super ECSManager

method void* New(ECSPlayerManager* this)
{
    static ECSIManager vtable = {
        .Initialize = (ECSManager_Initialize)Initialize,
        .Added = (ECSManager_Added)Added,
        .Changed = (ECSManager_Changed)Changed,
        .Deleted = (ECSManager_Deleted)Deleted,
        .Disabled = (ECSManager_Disabled)Disabled,
        .Enabled = (ECSManager_Enabled)Enabled,
    };

    New((super*) this, &vtable);

    this->PlayerByEntity = cfw_new(cfw_map, NULL);
    this->EntitiesByPlayer = cfw_new(cfw_map, NULL);
    return this;
}

method void Initialize(ECSPlayerManager* this)
{
    this->vptr->Initialize(this);
}

method void SetWorld(ECSPlayerManager* this, ECSWorld* world)
{
    SetWorld((super*)this, world);
}

method ECSWorld* GetWorld(ECSPlayerManager* this)
{
    return GetWorld((super*)this);
}

method void Added(ECSPlayerManager* this, ECSEntity* entity)
{
    this->vptr->Added(this, entity);
}

method void Changed(ECSPlayerManager* this, ECSEntity* entity) 
{ 
    this->vptr->Changed(this, entity); 
}

method void Deleted(ECSPlayerManager* this, ECSEntity* entity)
{
    RemoveFromPlayer(this, entity);
}

method void Disabled(ECSPlayerManager* this, ECSEntity* entity)
{
    this->vptr->Disabled(this, entity);
}

method void Enabled(ECSPlayerManager* this, ECSEntity* entity)
{
    this->vptr->Enabled(this, entity);
}

method void SetPlayer(ECSPlayerManager* this, ECSEntity* e, char* player)
{
    Put(this->PlayerByEntity, e->key, player);
    CFArray* entities = Get(this->EntitiesByPlayer, player);
    if (entities == NULL) {
        entities = cfw_new(cfw_array, NULL);
        Put(this->EntitiesByPlayer, player, entities);
    }
    Add(entities, e);
}

method CFArray* GetEntitiesOfPlayer(ECSPlayerManager* this, char* player)
{
    CFArray* entities = Get(this->EntitiesByPlayer, player);
    if (entities == NULL) {
        entities = cfw_new(cfw_array, NULL);
    }
    return entities;
}

method void RemoveFromPlayer(ECSPlayerManager* this, ECSEntity* e)
{
    char* player = Get(this->PlayerByEntity, e->key);
    if (player != NULL) {
        CFArray* entities = Get(this->EntitiesByPlayer, player);
        if (entities != NULL) {
            Remove(entities, e);
        }
    }
}

method char* GetPlayer(ECSPlayerManager* this, ECSEntity* e)
{
    return Get(this->PlayerByEntity, e->key);
}
