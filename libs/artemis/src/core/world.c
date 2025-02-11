#include "core/world.h"
#include "cfw.h"
#include "core/entitysystem-private.h"
#include "core/entitysystem.h"
#include "core/manager-private.h"
#include "core/manager.h"
#include "core/world-private.h"
#include "ecs.h"
/**
 * The primary instance for the framework. It contains all the managers.
 * 
 * You must use this to create, delete and retrieve entities.
 * 
 * It is also important to set the delta each game loop iteration, and initialize before game loop.
 * 
 * @author Arni Arent
 * 
 */
method void* New(ECSWorld* this)
{
    this->Managers = cfw_new(cfw_map, NULL);
    this->ManagersBag = cfw_new(cfw_array, NULL);

    this->Systems = cfw_new(cfw_map, NULL);
    this->SystemsBag = cfw_new(cfw_array, NULL);

    this->Added = cfw_new(cfw_array, NULL);
    this->Changed = cfw_new(cfw_array, NULL);
    this->Deleted = cfw_new(cfw_array, NULL);
    this->Enable = cfw_new(cfw_array, NULL);
    this->Disable = cfw_new(cfw_array, NULL);

    this->Cm = new (ECSComponentManager);
    assert(this != NULL);
    assert(this->Cm != NULL);
    SetManager(this, this->Cm);

    this->Em = new (ECSEntityManager);
    SetManager(this, this->Em);
    return this;
}

/**
 * Makes sure all managers systems are initialized in the order they were added.
 */
method void Initialize(ECSWorld* this)
{
    for (var i = 0; i < Length(this->ManagersBag); i++)
        Initialize((ECSManager*)Get(this->ManagersBag, i));

    /** 
     * annotaions.EntityTemplate 
     * 
     * Collect the entity templates
     */
    // this->EntityTemplates = new(Map, of(ECSEntityTemplate));
    // if (EntityTemplate.entityTemplates.Keys != null)
    // {
    //     foreach (var entityName in EntityTemplate.entityTemplates.Keys)
    //     {
    //         var Template = (Type)EntityTemplate.entityTemplates[entityName];
    //         SetEntityTemplate(entityName, (EntityTemplate)GLib.Object.new(Template));
    //     }
    // }
    /** 
     * annotations.Mapper 
     *
     * Collect the component mappers
     */
    // foreach (var system in systemsBag)
    // {
    //     /** Inject the component mappers into each system */
    //     ComponentMapperInitHelper.Config(system, this);
    //     system.Initialize();
    // }
}

/**
 * Returns a manager that takes care of all the entities in the world.
 * entities of this world.
 * 
 * @return entity manager.
 */
method ECSEntityManager* GetEntityManager(ECSWorld* this)
{
    return this->Em;
}

/**
 * Returns a manager that takes care of all the components in the world.
 * 
 * @return component manager.
 */
method ECSComponentManager* GetComponentManager(ECSWorld* this)
{
    return this->Cm;
}

/**
 * Add a manager into this world. It can be retrieved later.
 * World will notify this manager of changes to entity.
 * 
 * @param manager to be added
 */
method ECSManager* SetManager(ECSWorld* this, ECSManager* manager)
{
    Put(this->Managers, manager->obj.cls->name, manager);
    Add(this->ManagersBag, manager);
    SetWorld(manager, this);
    return manager;
}

/**
 * Returns a manager of the specified type.
* 
* @param <T>
* @param managerType
*            class type of the manager
* @return the manager
*/
method ECSManager* GetManager(ECSWorld* this, CFClass* type)
{
    return Get(this->Managers, type->name);
}

/**
 * Deletes the manager from this world.
 * @param manager to delete.
 */
method void DeleteManager(ECSWorld* this, ECSManager* manager)
{
    Remove(this->Managers, manager->obj.cls->name);
    Remove(this->ManagersBag, manager);
}

/**
 * Time since last game loop.
* 
* @return delta time since last game loop.
*/
method float GetDelta(ECSWorld* this)
{
    return this->Delta;
}

/**
 * You must specify the delta for the game here.
* 
* @param delta time since last game loop.
*/
method void SetDelta(ECSWorld* this, float delta)
{
    this->Delta = delta;
}

/**
 * Adds a entity to this world.
* 
* @param e entity
*/
method void AddEntity(ECSWorld* this, ECSEntity* e)
{
    Add(this->Added, e);
}

/**
 * Ensure all systems are notified of changes to this entity.
* If you're adding a component to an entity after it's been
* added to the world, then you need to invoke this method.
* 
* @param e entity
*/
method void ChangedEntity(ECSWorld* this, ECSEntity* e)
{
    Add(this->Changed, e);
}

/**
 * Delete the entity from the world.
* 
* @param e entity
*/
method void DeleteEntity(ECSWorld* this, ECSEntity* e)
{
    if (!Contains(this->Deleted, e)) {
        Add(this->Deleted, e);
    }
}

/**
 * (Re)enable the entity in the world, after it having being disabled.
* Won't do anything unless it was already disabled.
*/
method void Enable(ECSWorld* this, ECSEntity* e)
{
    Add(this->Enable, e);
}

/**
 * Disable the entity from being processed. Won't delete it, it will
* continue to exist but won't get processed.
*/
method void Disable(ECSWorld* this, ECSEntity* e)
{
    Add(this->Disable, e);
}

/**
 * Create and return a new or reused entity instance.
* Will NOT add the entity to the world, use World.addEntity(Entity) for that.
*
* @param name optional name for debugging
* @return entity
*/
method ECSEntity* CreateEntity(ECSWorld* this, char* name)
{
    return CreateEntityInstance(this->Em, name);
}

/**
 * Get a entity having the specified id.
* 
* @param entityId
* @return entity
*/
method ECSEntity* GetEntity(ECSWorld* this, int entityId)
{
    return GetEntity(this->Em, entityId);
}

/**
 * Gives you all the systems in this world for possible iteration.
* 
* @return all entity systems in world.
*/
method CFArray* GetSystems(ECSWorld* this)
{
    return this->SystemsBag;
}

/**
 * Will add a system to this world.
*  
* @param system the system to add.
* @param passive wether or not this system will be processed by World.process()
* @return the added system.
*/
method ECSEntitySystem* SetSystem(ECSWorld* this, ECSEntitySystem* system, bool passive)
{
    SetWorld(system, this);
    SetPassive(system, passive);

    Put(this->Systems, system->obj.cls->name, system);
    Add(this->SystemsBag, system);

    return system;
}
method ECSEntitySystem* SetSystem(ECSWorld* this, ECSEntitySystem* system)
{
    return SetSystem(this, system, false);
}
/**
 * Removed the specified system from the world.
* @param system to be deleted from world.
*/
method void DeleteSystem(ECSWorld* this, ECSEntitySystem* system)
{
    Remove(this->Systems, system->obj.cls->name);
    Remove(this->SystemsBag, system);
}

method void NotifySystems(ECSWorld* this, ECSPerformer perform, ECSEntity* e)
{
    for (var i = 0; i < Length(this->SystemsBag); i++) {
        var system = Get(this->SystemsBag, i);
        perform(system, e);
    }
}

method void NotifyManagers(ECSWorld* this, ECSPerformer perform, ECSEntity* e)
{
    for (var i = 0; i < Length(this->ManagersBag); i++) {
        var manager = Get(this->ManagersBag, i);
        perform(manager, e);
    }
}

/**
 * Retrieve a system for specified system type.
* 
* @param type type of system.
* @return instance of the system in this world.
*/
method ECSEntitySystem* GetSystem(ECSWorld* this, CFClass* type)
{
    return Get(this->Systems, type->name);
}

/**
 * Performs an action on each entity.
* @param entities
* @param performer
*/
method void Check(ECSWorld* this, CFArray* entities, ECSPerformer perform)
{
    if (!IsEmpty(entities)) {
        for (var i = 0; i < Length(entities); i++) {
            var e = Get(entities, i);
            NotifyManagers(this, perform, e);
            NotifySystems(this, perform, e);
        }
        Clear(entities);
    }
}

/**
 * Process all non-passive systems.
*/
method void Update(ECSWorld* this)
{
    /*
    Check(this, this->Added, (ECSPerformer)Added);
    Check(this, this->Changed, (ECSPerformer)Changed);
    Check(this, this->Disable, (ECSPerformer)Disabled);
    Check(this, this->Enable, (ECSPerformer)Enabled);
    Check(this, this->Deleted, (ECSPerformer)Deleted);

    Clean(this->Cm);

    for (var i = 0; i < Length(this->SystemsBag); i++) {
        var system = Get(this->SystemsBag, i);
        if (!IsPassive(system)) {
            Process(system);
        }
    }
    */
}

method void Draw(ECSWorld* this)
{
    // for (var i = 0; i < Length(this->SystemsBag); i++) {
    //     var system = Get(this->SystemsBag, i);
    //     if (IsPassive(system)) {
    //         Process(system);
    //     }
    // }
}

