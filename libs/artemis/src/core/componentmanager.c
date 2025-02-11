#include "core/componentmanager.h"
#include "cfw.h"
#include "core/componentmanager-private.h"
#include "ecs.h"
#include <assert.h>

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSComponentManager);

method void* New(ECSComponentManager* this)
{
    this->ComponentsByType = cfw_new (cfw_array, NULL);
    this->Deleted = cfw_new (cfw_array, NULL);
    this->TypeFactory = new (ECSComponentTypeFactory);
    return this;
}

method ECSComponentTypeFactory* GetTypeFactory(ECSComponentManager* this)
{
    return this->TypeFactory;
}
/**
 * Removes all components from the entity associated in this manager.
 *
 * @param e
 *			the entity to remove components from
 */
method void RemoveComponentsOfEntity(ECSComponentManager* this, ECSEntity* e)
{
    var componentBits = GetComponentBits(e);
    for (var index = NextSetBit(componentBits, 0); index >= 0; NextSetBit(componentBits, index + 1)) {
        var components = Get(this->ComponentsByType, index);
        Put(components, GetId(e), NULL);
    }
}

/**
 * Adds the component of the given type to the entity.
 * <p>
 * Only one component of given type can be associated with a entity at the
 * same time.
 * </p>
 *
 * @param e
 *			the entity to add to
 * @param type
 *			the type of component being added
 * @param component
 *			the component to add
 */
method void AddComponent(ECSComponentManager* this, ECSEntity* e, ECSComponentType* type, ECSComponent* component)
{
    CFArray* components = Get(this->ComponentsByType, GetIndex(type));
    if (components == NULL) {
        components = cfw_new (cfw_array, NULL);
        Put(this->ComponentsByType, GetIndex(type), components);
    }
    Put(components, GetId(e), component);
    Set(GetComponentBits(e), GetIndex(type), true);
}

/**
 * Removes the component of given type from the entity.
 *
 * @param e
 *			the entity to remove from
 * @param type
 *			the type of component being removed
 */
method void RemoveComponent(ECSComponentManager* this, ECSEntity* e, ECSComponentType* type)
{
    var index = GetIndex(type);
    Put(this->ComponentsByType, index, NULL);
    Clear(GetComponentBits(e), GetIndex(type));
}

/**
 * Get all components from all entities for a given type.
 *
 * @param type
 *			the type of components to get
 * @return a bag containing all components of the given type
 */
method CFArray* GetComponentsByType(ECSComponentManager* this, ECSComponentType* type)
{
    CFArray* components = Get(this->ComponentsByType, GetIndex(type));
    if (components == NULL)
        components = cfw_new (cfw_array, NULL);
    return components;
}
/**
 * Get a component of an entity.
 *
 * @param e
 *			the entity associated with the component
 * @param type
 *			the type of component to get
 * @return the component of given type
 */
method ECSComponent* GetComponent(ECSComponentManager* this, ECSEntity* e, ECSComponentType* type)
{
    CFArray* components = Get(this->ComponentsByType, GetIndex(type));
    if (components != NULL)
        return Get(components, GetId(e));
    return NULL;
}

/**
 * Get all component associated with an entity.
 *
 * @param e
 *			the entity to get components from
 * @param fillBag
 *			a bag to be filled with components
 * @return the {@code fillBag}, filled with the entities components
 */
method CFArray* GetComponentsFor(ECSComponentManager* this, ECSEntity* e, CFArray* fillBag)
{
    var componentBits = GetComponentBits(e);

    for (var i = NextSetBit(componentBits, 0); i >= 0; i = NextSetBit(componentBits, i + 1)) {
        CFArray* components = Get(this->ComponentsByType, i);
        Add(components, (void*)GetId(e));
    }
    return fillBag;
}

method void Deleted(ECSComponentManager* this, ECSEntity* e)
{
    Add(this->Deleted, e);
}

method void Clean(ECSComponentManager* this)
{
    if (cfw_array_size(this->Deleted) > 0) {
        for (var i = 0; cfw_array_size(this->Deleted) > i; i++) {
            RemoveComponentsOfEntity(this, Get(this->Deleted, i));
        }
        Clear(this->Deleted);
    }
}

method void Added(ECSComponentManager* this, ECSEntity* entity) {}

method void Changed(ECSComponentManager* this, ECSEntity* entity) {}

method void Disabled(ECSComponentManager* this, ECSEntity* entity) {}

method void Enabled(ECSComponentManager* this, ECSEntity* entity) {}
