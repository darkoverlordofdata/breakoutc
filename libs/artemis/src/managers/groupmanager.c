#include "managers/groupmanager.h"
#include "cfw.h"
#include "core/entity-private.h"
#include "core/entity.h"
#include "core/manager-private.h"
#include "core/manager.h"
#include "core/world.h"
#include "ecs.h"
#include "managers/groupmanager-private.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSGroupManager);

#define super ECSManager

method void* New(ECSGroupManager* this)
{
    static ECSIManager vtable = {
        .Initialize = (ECSManager_Initialize)((ECSGroupManager_Initialize)Initialize),
        .Added = (ECSManager_Added)((ECSGroupManager_Added)Added),
        .Changed = (ECSManager_Changed)((ECSGroupManager_Changed)Changed),
        .Deleted = (ECSManager_Deleted)((ECSGroupManager_Deleted)Deleted),
        .Disabled = (ECSManager_Disabled)((ECSGroupManager_Disabled)Disabled),
        .Enabled = (ECSManager_Enabled)((ECSGroupManager_Enabled)Enabled),
    };

    New((super*) this, &vtable);

    this->EntitiesByGroup = cfw_new(cfw_map, NULL);
    this->GroupsByEntity = cfe_new(cfw_map, NULL);
    return this;
}

method void Initialize(ECSGroupManager* this)
{
    this->vptr->Initialize(this);
}

method void SetWorld(ECSGroupManager* this, ECSWorld* world)
{
    SetWorld((super*)this, world);
}

method ECSWorld* GetWorld(ECSGroupManager* this)
{
    return GetWorld((super*)this);
}

method void Added(ECSGroupManager* this, ECSEntity* entity)
{
    this->vptr->Added(this, entity);
}

method void Changed(ECSGroupManager* this, ECSEntity* entity)
{
    this->vptr->Changed(this, entity);
}

method void Deleted(ECSGroupManager* this, ECSEntity* entity)
{
    RemoveFromAllGroups(this, entity);
}

method void Disabled(ECSGroupManager* this, ECSEntity* entity)
{
    this->vptr->Disabled(this, entity);
}

method void Enabled(ECSGroupManager* this, ECSEntity* entity)
{
    this->vptr->Enabled(this, entity);
}

/**
 * Set the group of the entity.
*
* @param group group to add the entity into.
* @param e entity to add into the group.
*/
method void Add(ECSGroupManager* this, ECSEntity* e, char* group)
{
    CFArray* entities = Get(this->EntitiesByGroup, group);
    if (entities == NULL) {
        entities = cfw_new(cfw_array, NULL);
        Put(this->EntitiesByGroup, group, entities);
    }
    Add(entities, e);

    CFArray* groups = Get(this->GroupsByEntity, e->key);
    if (groups == NULL) {
        groups = cfw_new(cfw_array, NULL);
        Put(this->GroupsByEntity, e->key, groups);
    }
    Add(groups, group);
}

/**
 * Remove the entity from the specified group.
 * @param e
 * @param group
 */
method void Remove(ECSGroupManager* this, ECSEntity* e, char* group)
{
    CFArray* entities = Get(this->EntitiesByGroup, group);
    if (entities != NULL) {
        Remove(entities, e);
    }

    CFArray* groups = Get(this->GroupsByEntity, e->key);
    if (groups != NULL) {
        Remove(groups, (void*)group);
    }
}

method void RemoveFromAllGroups(ECSGroupManager* this, ECSEntity* e)
{
    CFArray* groups = Get(this->GroupsByEntity, e->key);
    if (groups != NULL) {
        for (var i = 0, s = Length(groups); s > i; i++) {
            CFArray* entities = Get(this->EntitiesByGroup, Get(groups, i));
            if (entities != NULL) {
                Remove(entities, e);
            }
        }
        Clear(groups);
    }
}

/**
 * Get all entities that belong to the provided group.
 * @param group name of the group.
 * @return read-only bag of entities belonging to the group.
 */
method CFArray* GetEntities(ECSGroupManager* this, char* group)
{
    CFArray* entities = Get(this->EntitiesByGroup, group);
    if (entities == NULL) {
        entities = cfw_new (cfw_array, NULL);
        Put(this->EntitiesByGroup, group, entities);
    }
    return entities;
}

/**
 * @param e entity
 * @return the groups the entity belongs to, null if none.
 */
method CFArray* GetGroups(ECSGroupManager* this, ECSEntity* e)
{
    return Get(this->GroupsByEntity, e->key);
}

/**
 * Checks if the entity belongs to any group.
 * @param e the entity to check.
 * @return true if it is in any group, false if none.
 */
method bool IsInAnyGroup(ECSGroupManager* this, ECSEntity* e)
{
    return GetGroups(this, e) != NULL;
}

/**
 * Check if the entity is in the supplied group.
* @param group the group to check in.
* @param e the entity to check for.
* @return true if the entity is in the supplied group, false if not.
*/
method bool IsInGroup(ECSGroupManager* this, ECSEntity* e, char* group)
{
    if (group != NULL) {
        CFArray* groups = Get(this->GroupsByEntity, e->key);
        for (var i = 0, s = Length(groups); s > i; i++) {
            char* g = Get(groups, i);
            if (strcmp(group, g) == 0) {
                return true;
            }
        }
    }
    return false;
}

#undef super