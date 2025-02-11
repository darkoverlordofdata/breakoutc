#include "systems/voidentitysystem.h"
#include "cfw.h"
#include "systems/voidentitysystem-private.h"
#include "ecs.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSVoidEntitySystem);

#define super ECSEntitySystem


/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method void* New(ECSVoidEntitySystem* this, ECSIVoidEntitySystem* vptr)
{
    this->vptr = New((super*)this, GetAspectForNone(), (ECSIEntitySystem*)vptr);    
    vptr->ProcessSystem = abstract(ECSEntityProcessingSystem, ProcessSystem);
    return this;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(ECSVoidEntitySystem* this) 
{ 
    Begin((super*)this); 
}

method void Process(ECSVoidEntitySystem* this)
{   
    Process((super*)this);
}

/**
 * Called after the processing of entities ends.
 */
method void End(ECSVoidEntitySystem* this) 
{ 
    End((super*)this); 
}

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(ECSVoidEntitySystem* this, CFArray* entities) { 
    ProcessSystem((super*)this);
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(ECSVoidEntitySystem* this) { 
    return true;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(ECSVoidEntitySystem* this) 
{ 
    Initialize((super*)this); 
}

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(ECSVoidEntitySystem* this, ECSEntity* e) { 
    Inserted((super*)this, e); 
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(ECSVoidEntitySystem* this, ECSEntity* e) { 
    Removed((super*)this, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(ECSVoidEntitySystem* this, ECSEntity* e) { 
    Check((super*)this, e);
}

method void RemoveFromSystem(ECSVoidEntitySystem* this, ECSEntity* e) 
{
    RemoveFromSystem((super*)this, e);
}

method void InsertToSystem(ECSVoidEntitySystem* this, ECSEntity* e) 
{
    InsertToSystem((super*)this, e);
}

method void Added(ECSVoidEntitySystem* this, ECSEntity* entity) { }

method void Changed(ECSVoidEntitySystem* this, ECSEntity* e) {
    Check(this, e);
}

method void Deleted(ECSVoidEntitySystem* this, ECSEntity* e) {
    Deleted((super*)this, e);
}

method void Disabled(ECSVoidEntitySystem* this, ECSEntity* e) {
    Disabled((super*)this, e);
}

method void Enabled(ECSVoidEntitySystem* this, ECSEntity* e) {
    Enabled((super*)this, e);
}

method void SetWorld(ECSVoidEntitySystem* this, ECSWorld* world) {
    SetWorld((super*)this, world);
}

method bool IsPassive(ECSVoidEntitySystem* this) {
    return IsPassive((super*)this);
}

method void SetPassive(ECSVoidEntitySystem* this, bool passive) {
    SetPassive((super*)this, passive);
}

method CFArray* GetActive(ECSVoidEntitySystem* this) {
    return GetActive(this);
}

method void ProcessSystem(ECSVoidEntitySystem* this) { 
    this->vptr->ProcessSystem(this); 
    
}


#undef super