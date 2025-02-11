#include "systems/intervalentityprocessingsystem.h"
#include "cfw.h"
#include "core/entitysystem-private.h"
#include "core/entitysystem.h"
#include "ecs.h"
#include "systems/entityprocessingsystem-private.h"
#include "systems/entityprocessingsystem.h"
#include "systems/intervalentityprocessingsystem-private.h"
#include "systems/intervalentitysystem-private.h"
#include "systems/intervalentitysystem.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSIntervalEntityProcessingSystem);

#define super ECSIntervalEntitySystem


/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method void* New(ECSIntervalEntityProcessingSystem* this, ECSAspect* aspect, float interval, ECSIIntervalEntityProcessingSystem* vptr)
{
    this->vptr = New((super*)this, aspect, interval, (ECSIIntervalEntitySystem*)vptr);    
    return this;
}

/**
 * Called before processing of entities begins. 
 */
method void Begin(ECSIntervalEntityProcessingSystem* this)
{
    Begin((super*)this);
}

method void Process(ECSIntervalEntityProcessingSystem* this)
{
    Process((super*)this);
}

/**
 * Called after the processing of entities ends.
 */
method void End(ECSIntervalEntityProcessingSystem* this) 
{ 
    End((super*)this);
}

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(ECSIntervalEntityProcessingSystem* this, CFArray* entities)
{
    for (var i = 0; i < Length(entities); i++) {
        ProcessEach(this, Get(entities, i));
    }
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(ECSIntervalEntityProcessingSystem* this)
{
    if ((this->Acc += GetDelta(this->World)) >= this->Interval) {
        this->Acc -= this->Interval;
        return true;
    }
    return false;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(ECSIntervalEntityProcessingSystem* this) 
{ 
    Initialize((super*)this);
}

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    Inserted((super*)this, e);
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    Removed((super*)this, e);
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    Check((super*)this, e);
}

method void RemoveFromSystem(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    RemoveFromSystem((super*)this, e);
}

method void InsertToSystem(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    InsertToSystem((super*)this, e);
}

method void Added(ECSIntervalEntityProcessingSystem* this, ECSEntity* entity) {}

method void Changed(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    Check(this, e);
}

method void Deleted(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    Deleted((super*)this, e);
}

method void Disabled(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    Disabled((super*)this, e);
}

method void Enabled(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    Enabled((super*)this, e);
}

method void SetWorld(ECSIntervalEntityProcessingSystem* this, ECSWorld* world)
{
    SetWorld((super*)this, world);
}

method bool IsPassive(ECSIntervalEntityProcessingSystem* this)
{
    return IsPassive((super*)this);
}

method void SetPassive(ECSIntervalEntityProcessingSystem* this, bool passive)
{
    SetPassive((super*)this, passive);
}

method CFArray* GetActive(ECSIntervalEntityProcessingSystem* this)
{
    return GetActive(this);
}

/**
 * Process a entity this system is interested in.
 * @param e the entity to process.
 */
method void ProcessEach(ECSIntervalEntityProcessingSystem* this, ECSEntity* e)
{
    this->vptr->ProcessEach(this, e);
}


#undef super