#include "managers/tagmanager.h"
#include "cfw.h"
#include "core/entity-private.h"
#include "core/entity.h"
#include "core/manager-private.h"
#include "core/manager.h"
#include "core/world.h"
#include "ecs.h"
#include "managers/tagmanager-private.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSTagManager);

#define super ECSManager

method void* New(ECSTagManager* this)
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

    this->EntitiesByTag = cfw_new(cfw_map, NULL);
    this->TagsByEntity = cfw_new(cfw_map, NULL);
    return this;
}

method void Initialize(ECSTagManager* this)
{
    this->vptr->Initialize(this);
}

method void SetWorld(ECSTagManager* this, ECSWorld* world)
{
    SetWorld((super*)this, world);
}

method ECSWorld* GetWorld(ECSTagManager* this)
{
    return GetWorld((super*)this);
}

method void Added(ECSTagManager* this, ECSEntity* entity)
{
    this->vptr->Added(this, entity);
}

method void Changed(ECSTagManager* this, ECSEntity* entity)
{
    this->vptr->Changed(this, entity);
}

method void Deleted(ECSTagManager* this, ECSEntity* entity)
{
    Remove(this->EntitiesByTag, (char*)Get(this->TagsByEntity, entity->key));
}

method void Disabled(ECSTagManager* this, ECSEntity* entity) 
{ 
    this->vptr->Disabled(this, entity); 
}

method void Enabled(ECSTagManager* this, ECSEntity* entity) 
{ 
    this->vptr->Enabled(this, entity); 
}

method void Register(ECSTagManager* this, char* tag, ECSEntity* e)
{
    Put(this->EntitiesByTag, tag, e);
    Put(this->TagsByEntity, e->key, tag);
}

method void Unregister(ECSTagManager* this, char* tag)
{
    Remove(this->TagsByEntity, ((ECSEntity*)(Get(this->EntitiesByTag, tag)))->key);
    Remove(this->EntitiesByTag, tag);
}

method bool IsRegistered(ECSTagManager* this, char* tag)
{
    return Get(this->EntitiesByTag, tag) != NULL;
}

method ECSEntity* GetEntity(ECSTagManager* this, char* tag)
{
    return Get(this->EntitiesByTag, tag);
}

method CFArray* GetRegisteredTags(ECSTagManager* this)
{

    CFArray* res = cfw_new(cfw_array);
    ForEach(this->TagsByEntity, ^(void* key, void* item) {
        Add(res, item);
    });
    return res;
}
//method void ForEach(CFMap* this, void(^func)(void* key, void* item))
