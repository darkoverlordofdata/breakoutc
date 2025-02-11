#include "systems/entityprocessingsystem.h"
#include "cfw.h"
#include "systems/entityprocessingsystem-private.h"
#include "ecs.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSEntityProcessingSystem);

#define super ECSEntitySystem

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method void* New(ECSEntityProcessingSystem* this, ECSAspect* aspect, ECSIEntityProcessingSystem* vptr)
{
    this->vptr = New((super*)this, aspect, (ECSIEntitySystem*)vptr);  
    vptr->ProcessEach = (ECSEntitySystem_ProcessEach)((ECSEntityProcessingSystem_ProcessEach)ProcessEach);
    return this;
}



/**
 * Called before processing of entities begins. 
 */
method void Begin(ECSEntityProcessingSystem* this) 
{ 
    Begin((super*)this);
}

method void Process(ECSEntityProcessingSystem* this)
{   
    Process((super*)this);
}

/**
 * Called after the processing of entities ends.
 */
method void End(ECSEntityProcessingSystem* this) 
{ 
    End((super*)this);
}

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(ECSEntityProcessingSystem* this, CFArray* entities) {
    for (var i=0; i<Length(entities); i++) {
        ProcessEach(this, Get(entities, i));
    } 
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(ECSEntityProcessingSystem* this) { 
    return true;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(ECSEntityProcessingSystem* this) 
{ 
    Initialize((super*)this);
}

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(ECSEntityProcessingSystem* this, ECSEntity* e) 
{ 
    Inserted((super*)this, e);
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(ECSEntityProcessingSystem* this, ECSEntity* e) 
{ 
    Removed((super*)this, e);
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(ECSEntityProcessingSystem* this, ECSEntity* e) 
{ 
    Check((super*)this, e);
}

method void RemoveFromSystem(ECSEntityProcessingSystem* this, ECSEntity* e) 
{
    RemoveFromSystem((super*)this, e);
}

method void InsertToSystem(ECSEntityProcessingSystem* this, ECSEntity* e) 
{
    InsertToSystem((super*)this, e);
}

method void Added(ECSEntityProcessingSystem* this, ECSEntity* entity) 
{ 
    Added((super*)this, entity);
}


method void Changed(ECSEntityProcessingSystem* this, ECSEntity* e) 
{
    Changed((super*)this, e);
}

method void Deleted(ECSEntityProcessingSystem* this, ECSEntity* e) 
{
    Deleted((super*)this, e);
}

method void Disabled(ECSEntityProcessingSystem* this, ECSEntity* e) 
{
    Disabled((super*)this, e);
}

method void Enabled(ECSEntityProcessingSystem* this, ECSEntity* e) 
{
    Enabled((super*)this, e);
}

method void SetWorld(ECSEntityProcessingSystem* this, ECSWorld* world) 
{
    SetWorld((super*)this, world);
}

method bool IsPassive(ECSEntityProcessingSystem* this) 
{
    return IsPassive((super*)this);
}

method void SetPassive(ECSEntityProcessingSystem* this, bool passive) 
{
    SetPassive((super*)this, passive);
}

method CFArray* GetActive(ECSEntityProcessingSystem* this) 
{
    return GetActive((super*)this);
}

/**
 * Process a entity this system is interested in.
 * @param e the entity to process.
 */
method void ProcessEach(ECSEntityProcessingSystem* this, ECSEntity* e) 
{ 
    this->vptr->ProcessEach(this, e); 
}

#undef super