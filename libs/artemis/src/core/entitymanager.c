#include "core/entitymanager.h"
#include "cfw.h"
#include "core/entity-private.h"
#include "core/entity.h"
#include "core/entitymanager-private.h"
#include "ecs.h"

method void* New(ECSIdentifierPool* this)
{
    this->Ids = cfw_new(cfw_array, NULL);
    this->NextAvailableId = 0;
    return this;
}

method void CheckIn(ECSIdentifierPool* this, int id)
{
    cfw_array_push(this->Ids, cfw_new(cfw_int, id));
}

method int CheckOut(ECSIdentifierPool* this)
{
    if (cfw_array_size(this->Ids) > 0) {
        var last = cfw_array_pop(this->Ids);
        return cfw_int_value(last);
    }
    return this->NextAvailableId++;
}

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSEntityManager);

method void* New(ECSEntityManager* this)
{
    this->Entities = cfw_new(cfw_array, NULL);
    this->Disabled = new (CFBitVector);
    this->IdentifierPool = new (ECSIdentifierPool);
    this->Active = 0;
    this->Added = 0;
    this->Created = 0;
    this->Deleted = 0;
    return this;
}
method void SetWorld(ECSEntityManager* this, ECSWorld* world)
{
    SetWorld(this->override, world);
}

method ECSWorld* GetWorld(ECSEntityManager* this)
{
    return GetWorld(this->override);
}

method ECSEntity* CreateEntityInstance(ECSEntityManager* this, char* name)
{
    var e = new (ECSEntity, this->World, CheckOut(this->IdentifierPool), name);
    this->Created += 1;
    return e;
}

method void Added(ECSEntityManager* this, ECSEntity* entity)
{
    this->Active += 1;
    this->Added += 1;
    Put(this->Entities, entity->Id, entity);
}

method void Changed(ECSEntityManager* this, ECSEntity* entity) {}

method void Enabled(ECSEntityManager* this, ECSEntity* entity)
{
    Clear(this->Disabled, entity->Id);
}

method void Disabled(ECSEntityManager* this, ECSEntity* entity)
{
    Set(this->Disabled, entity->Id, true);
}

method void Deleted(ECSEntityManager* this, ECSEntity* entity)
{
    Put(this->Entities, entity->Id, NULL);
    Clear(this->Disabled, entity->Id);
    CheckIn(this->IdentifierPool, entity->Id);
    this->Active -= 1;
    this->Deleted += 1;
}

/**
 * Check if this entity is active.
 * Active means the entity is being actively processed.
 * 
 * @param entityId
 * @return true if active, false if not.
 */
method bool IsActive(ECSEntityManager* this, int entityId)
{
    return Get(this->Entities, entityId) != NULL;
}

/**
 * Check if the specified entityId is enabled.
 * 
 * @param entityId
 * @return true if the entity is enabled, false if it is disabled.
 */
method bool IsEnabled(ECSEntityManager* this, int entityId)
{
    return !Get(this->Disabled, entityId);
}

/**
 * Get a entity with this id.
 * 
 * @param entityId
 * @return the entity
 */
method ECSEntity* GetEntity(ECSEntityManager* this, int entityId)
{
    return Get(this->Entities, entityId);
}

/**
 * Get how many entities are active in this world.
 * @return how many entities are currently active.
 */
method int GetActiveEntityCount(ECSEntityManager* this)
{
    return this->Active;
}

/**
 * Get how many entities have been created in the world since start.
 * Note: A created entity may not have been added to the world, thus
 * created count is always equal or larger than added count.
 * @return how many entities have been created since start.
 */
method int GetTotalCreated(ECSEntityManager* this)
{
    return this->Created;
}

/**
 * Get how many entities have been added to the world since start.
 * @return how many entities have been added.
 */
method int GetTotalAdded(ECSEntityManager* this)
{
    return this->Added;
}

/**
 * Get how many entities have been deleted from the world since start.
 * @return how many entities have been deleted since start.
 */
method int GetTotalDeleted(ECSEntityManager* this)
{
    return this->Deleted;
}
