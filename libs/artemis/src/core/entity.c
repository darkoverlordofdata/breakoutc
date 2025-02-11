#include "core/entity.h"
#include "cfw.h"
#include "core/component-private.h"
#include "core/component.h"
#include "core/componentmanager-private.h"
#include "core/componentmanager.h"
#include "core/entity-private.h"
#include "ecs.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSEntity);

/**
 * The entity class. Cannot be instantiated outside the framework, you must
 * create new entities using World.
 * 
 * @author Arni Arent
 * 
 */
method void* New(ECSEntity* this, ECSWorld* world, int id, char* name)
{
    this->World = world;
    this->Id = id;
    this->uuid = new (CFUuid);
    this->key = cfw_strdup(ToString(this->uuid));
    this->Name = cfw_strdup(name);
    this->EntityManager = GetEntityManager(world);
    this->ComponentManager = GetComponentManager(world);
    this->ComponentBits = new (CFBitVector);
    this->SystemBits = new (CFBitVector);
    Reset(this);
    return this;
}

method CFBitVector* GetComponentBits(ECSEntity* this)
{
    return this->ComponentBits;
}
method CFBitVector* GetSystemBits(ECSEntity* this)
{
    return this->SystemBits;
}
method int GetId(ECSEntity* this)
{
    return this->Id;
}
method CFUuid* GetUUID(ECSEntity* this)
{
    return this->uuid;
}

/**
 * Make entity ready for re-use.
 * Will generate a new uuid for the entity.
 */
method void Reset(ECSEntity* this)
{
    Clear(this->SystemBits);
    Clear(this->ComponentBits);
}

/**
 * Faster adding of components into the entity. Not neccessery to use this, but
 * in some cases you might need the extra performance.
 * 
 * @param component the component to add
 * @param args of the component
 * 
 * @return this entity for chaining.
 */
method ECSEntity* AddComponent(ECSEntity* this, ECSComponent* component)
{
    var tf = GetTypeFactory(GetComponentManager(this->World));
    var componentType = GetTypeFor(this, tf);
    Set(this->ComponentBits, GetIndex(componentType), true);
    AddComponent(this->ComponentManager, this, componentType, component);
    return this;
}

method ECSComponentType* GetTypeFor(ECSEntity* this, CFClass* c)
{
    return GetTypeFor(GetTypeFactory(GetComponentManager(this->World)), c);
}

/**
 * Removes the component from this entity.
 * 
 * @param component to remove from this entity.
 * 
 * @return this entity for chaining.
 */
method ECSEntity* RemoveComponentInstance(ECSEntity* this, ECSComponent* component)
{
    ECSComponentType* type = GetTypeFor(this, &component->obj);
    RemoveComponent(this, type);
    return this;
}

/**
 * Faster removal of components from a entity.
 * 
 * @param type to remove from this entity.
 * 
 * @return this entity for chaining.
 */
method ECSEntity* RemoveComponent(ECSEntity* this, ECSComponentType* type)
{
    RemoveComponent(this->ComponentManager, this, type);
    return this;
}

/**
 * Remove component by its type.
 * @param type
 * 
 * @return this entity for chaining.
 */
method ECSEntity* RemoveComponentByType(ECSEntity* this, CFClass* type)
{
    RemoveComponent(this, GetTypeFor(this, type));
    return this;
}

/**
 * Checks if the entity has been added to the world and has not been deleted from it.
 * If the entity has been disabled this will still return true.
 * 
 * @return if it's active.
 */
method bool IsActive(ECSEntity* this)
{
    return IsActive(this->EntityManager, this->Id);
}

/**
 * Will check if the entity is enabled in the world.
 * By default all entities that are added to world are enabled,
 * this will only return false if an entity has been explicitly disabled.
 * 
 * @return if it's enabled
 */
method bool IsEnabled(ECSEntity* this)
{
    return IsEnabled(this->EntityManager, this->Id);
}

/**
 * This is the preferred method to use when retrieving a component from a
 * entity. It will provide good performance.
 * But the recommended way to retrieve components from an entity is using
 * the ComponentMapper.
 * 
 * @param type
 *            in order to retrieve the component fast you must provide a
 *            ComponentType instance for the expected component.
 * @return
 */
method ECSComponent* GetComponent(ECSEntity* this, ECSComponentType* type)
{
    return GetCompoment(this->ComponentManager, this, type);
}

/**
 * Slower retrieval of components from this entity. Minimize usage of this,
 * but is fine to use e.g. when creating new entities and setting data in
 * components.
 * 
 * @param <T>
 *            the expected return component type.
 * @param type
 *            the expected return component type.
 * @return component that matches, or null if none is found.
 */
method ECSComponent* GetComponentByType(ECSEntity* this, CFClass* type)
{
    return GetCompoment(this->ComponentManager, this, GetTypeFor(this, type));
}
//method ECSComponent* GetComponent(ECSComponentManager* this, ECSEntity* e, ECSComponentType* type)

/**
 * Returns a bag of all components this entity has.
 * You need to reset the bag yourthis if you intend to fill it more than once.
 * 
 * @param fillBag the bag to put the components into.
 * @return the fillBag with the components in.
 */
method CFArray* GetCompoments(ECSEntity* this, CFArray* fillBag)
{
    return GetComponentsFor(this->ComponentManager, this, fillBag);
}

/**
 * Refresh all changes to components for this entity. After adding or
 * removing components, you must call this method. It will update all
 * relevant systems. It is typical to call this after adding components to a
 * newly created entity.
 */
method void AddToWorld(ECSEntity* this)
{
    AddEntity(this->World, this);
}

/**
 * This entity has changed, a component added or deleted.
 */
method void ChangedInWorld(ECSEntity* this)
{
    ChangedEntity(this->World, this);
}

/**
 * Delete this entity from the world.
 */
method void DeleteFromWorld(ECSEntity* this)
{
    DeleteEntity(this->World, this);
}

/**
 * (Re)enable the entity in the world, after it having being disabled.
 * Won't do anything unless it was already disabled.
 */
method void Enable(ECSEntity* this)
{
    Enable(this->World, this);
}

/**
 * Disable the entity from being processed. Won't delete it, it will
 * continue to exist but won't get processed.
 */
method void Disable(ECSEntity* this)
{
    Disable(this->World, this);
}

/**
 * Returns the world this entity belongs to.
 * @return world of entity.
 */
method ECSWorld* GetWorld(ECSEntity* this)
{
    return this->World;
}