#include "systems/intervalentitysystem.h"
#include "cfw.h"
#include "systems/intervalentitysystem-private.h"
#include "ecs.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSIntervalEntitySystem);

#define super ECSEntitySystem

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method void* New(ECSIntervalEntitySystem* this, ECSAspect* aspect, float interval, ECSIIntervalEntitySystem* vptr)
{
    this->vptr = New((super*)this, aspect, (ECSIEntitySystem*)vptr);    
    this->Acc = 0;
    this->Interval = interval;
    return this;
}


/**
 * Called before processing of entities begins. 
 */
method void Begin(ECSIntervalEntitySystem* this) 
{ 
    Begin((super*)this);
}

method void Process(ECSIntervalEntitySystem* this)
{   
    Process((super*)this);
}


/**
 * Called after the processing of entities ends.
 */
method void End(ECSIntervalEntitySystem* this) 
{ 
    End((super*)this); 
}

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(ECSIntervalEntitySystem* this, CFArray* entities) { 
    ProcessEntities((super*)this, entities); 
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(ECSIntervalEntitySystem* this) { 
    if ((this->Acc += GetDelta(this->World)) >= this->Interval) {
        this->Acc -= this->Interval;
        return true;
    }
    return false;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(ECSIntervalEntitySystem* this) { Initialize(this); }

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(ECSIntervalEntitySystem* this, ECSEntity* e) { 
    Inserted((super*)this, e); 
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(ECSIntervalEntitySystem* this, ECSEntity* e) { 
    Removed((super*)this, e); 
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(ECSIntervalEntitySystem* this, ECSEntity* e) { 
    Check((super*)this, e);
}

method void RemoveFromSystem(ECSIntervalEntitySystem* this, ECSEntity* e) 
{
    RemoveFromSystem((super*)this, e);
}

method void InsertToSystem(ECSIntervalEntitySystem* this, ECSEntity* e) 
{
    InsertToSystem((super*)this, e);
}

method void Added(ECSIntervalEntitySystem* this, ECSEntity* entity) { }

method void Changed(ECSIntervalEntitySystem* this, ECSEntity* e) {
    Check((super*)this, e);
}

method void Deleted(ECSIntervalEntitySystem* this, ECSEntity* e) {
    Deleted((super*)this, e);
}

method void Disabled(ECSIntervalEntitySystem* this, ECSEntity* e) {
    Disabled((super*)this, e);
}

method void Enabled(ECSIntervalEntitySystem* this, ECSEntity* e) {
    Enabled((super*)this, e);
}

method void SetWorld(ECSIntervalEntitySystem* this, ECSWorld* world) {
    SetWorld((super*)this, world);
}

method bool IsPassive(ECSIntervalEntitySystem* this) {
    return IsPassive((super*)this);
}

method void SetPassive(ECSIntervalEntitySystem* this, bool passive) {
    SetPassive((super*)this, passive);
}

method CFArray* GetActive(ECSIntervalEntitySystem* this) {
    return GetActive((super*)this);
}


#undef super