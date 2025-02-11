#include "systems/entityprocessingsystem.h"
#include "cfw.h"
#include "systems/delayedentityprocessingsystem-private.h"
#include "ecs.h"
/**
 * The purpose of this class is to allow systems to execute at varying intervals.
 *
 * An example system would be an ExpirationSystem, that deletes entities after a certain
 * lifetime. Instead of running a system that decrements a timeLeft value for each
 * entity, you can simply use this system to execute in a future at a time of the shortest
 * lived entity, and then reset the system to run at a time in a future at a time of the
 * shortest lived entity, etc.
 *
 * Another example system would be an AnimationSystem. You know when you have to animate
 * a certain entity, e.g. in 300 milliseconds. So you can set the system to run in 300 ms.
 * to perform the animation.
 *
 * This will save CPU cycles in some scenarios.
 *
 * Implementation notes:
 * In order to start the system you need to override the inserted(Entity e) method,
 * look up the delay time from that entity and offer it to the system by using the
 * offerDelay(float delay) method.
 * Also, when processing the entities you must also call offerDelay(float delay)
 * for all valid entities.
 *
 * @author Arni Arent
 *
 */

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSDelayedEntityProcessingSystem);

#define super ECSEntitySystem

/**
 * Creates an entity system that uses the specified aspect as a matcher against entities.
 * @param aspect to match against entities
 */
method void* New(ECSDelayedEntityProcessingSystem* this, ECSAspect* aspect, ECSIDelayedEntityProcessingSystem* vptr)
{
    this->vptr = New((super*)this, aspect, (ECSIEntitySystem*)vptr);    
    vptr->GetRemainingDelay = abstract(ECSDelayedEntityProcessingSystem, GetRemainingDelay);
    vptr->ProcessDelta = abstract(ECSDelayedEntityProcessingSystem, ProcessDelta);    
    vptr->ProcessExpired = abstract(ECSDelayedEntityProcessingSystem, ProcessExpired);
    return this;
}


/**
 * Called before processing of entities begins. 
 */
method void Begin(ECSDelayedEntityProcessingSystem* this) 
{ 
    Begin((super*)this);
}

method void Process(ECSDelayedEntityProcessingSystem* this)
{   
    Process((super*)this);
}

/**
 * Called after the processing of entities ends.
 */
method void End(ECSDelayedEntityProcessingSystem* this) 
{ 
    End((super*)this);
}

/**
 * Any implementing entity system must implement this method and the logic
 * to process the given entities of the system.
 * 
 * @param entities the entities this system contains.
 */
method void ProcessEntities(ECSDelayedEntityProcessingSystem* this, CFArray* entities) { 
    for (var i=0; i<Length(entities); i++) {
        var entity = Get(entities, i);
        ProcessDelta(this, entity, this->Acc);
        var remaining = GetRemainingDelay(this, entity);
        if (remaining <= 0) {
            ProcessExpired(this, entity);
        } else {
            OfferDelay(this, remaining);
        }
    } 
    Stop(this);
}

/**
 * 
 * @return true if the system should be processed, false if not.
 */
method bool CheckProcessing(ECSDelayedEntityProcessingSystem* this) { 
    if (this->Running) {
        this->Acc += GetDelta(this->World);
        if (this->Acc >= this->Delay) {
            return true;
        }
    }
    return false;
}

/**
 * Override to implement code that gets executed when systems are initialized.
 */
method void Initialize(ECSDelayedEntityProcessingSystem* this) 
{ 
    Initialize((super*)this);
}

/**
 * Called if the system has received a entity it is interested in, e.g. created or a component was added to it.
 * @param e the entity that was added to this system.
 */
method void Inserted(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) { 
    var delay = GetRemainingDelay(this, e);
    if (delay > 0) {
        OfferDelay(this, delay);
    }
}

/**
 * Called if a entity was removed from this system, e.g. deleted or had one of it's components removed.
 * @param e the entity that was removed from this system.
 */
method void Removed(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) { 
    Removed((super*)this, e);
}

/**
 * Will Check if the entity is of interest to this system.
 * @param e entity to Check
 */
method void Check(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) { 
    Checked((super*)this, e);
}

method void RemoveFromSystem(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) 
{
    RemoveFromSystem((super*)this, e);
}

method void InsertToSystem(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) 
{
    InsertToSystem((super*)this, e);
}

method void Added(ECSDelayedEntityProcessingSystem* this, ECSEntity* entity) { }

method void Changed(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) {
    Check((super*)this, e);
} 

method void Deleted(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) {
    Deleted((super*)this, e);
}

method void Disabled(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) {
    Disabled((super*)this, e);
}

method void Enabled(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) {
    Enabled((super*)this, e);
}

method void SetWorld(ECSDelayedEntityProcessingSystem* this, ECSWorld* world) {
    SetWorld((super*)this, world);
}

method bool IsPassive(ECSDelayedEntityProcessingSystem* this) {
    return IsPassive((super*)this);
}

method void SetPassive(ECSDelayedEntityProcessingSystem* this, bool passive) {
    SetPassive((super*)this, passive);
}

method CFArray* GetActive(ECSDelayedEntityProcessingSystem* this) {
    return GetActive((super*)this);
}

/**
 * Return the delay until this entity should be processed.
 *
 * @param e entity
 * @return delay
 */
method float GetRemainingDelay(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) {
    this->vptr->GetRemainingDelay(this, e); 
}

/**
 * Process a entity this system is interested in. Substract the accumulatedDelta
* from the entities defined delay.
*
* @param e the entity to process.
* @param accumulatedDelta the delta time since this system was last executed.
*/
method void ProcessDelta(ECSDelayedEntityProcessingSystem* this, ECSEntity* e, float accumulatedDelta) {
    this->vptr->ProcessDelta(this, e, accumulatedDelta); 
}

method void ProcessExpired(ECSDelayedEntityProcessingSystem* this, ECSEntity* e) {
    this->vptr->ProcessExpired(this, e); 
}


/**
 * Start processing of entities after a certain amount of delta time.
*
* Cancels current delayed run and starts a new one.
*
* @param delta time delay until processing starts.
*/
method void Restart(ECSDelayedEntityProcessingSystem* this, float delay) {
    this->Delay = delay;
    this->Acc = 0;
    this->Running = true;
}

/**
 * Restarts the system only if the delay offered is shorter than the
* time that the system is currently scheduled to execute at.
* If the system is already stopped (not running) then the offered
*
* delay will be used to restart the system with no matter its value.
*
* If the system is already counting down, and the offered delay is
* larger than the time remaining, the system will ignore it. If the
* offered delay is shorter than the time remaining, the system will
* restart itthis to run at the offered delay.
*
* @param delay
*/
method void OfferDelay(ECSDelayedEntityProcessingSystem* this, float delay) {
    if(!this->Running || delay < GetRemainingTimeUntilProcessing(this)) {
        Restart(this, delay);
    }
}


/**
 * Get the initial delay that the system was ordered to process entities after.
*
* @return the originally set delay.
*/
method float GetInitialTimeDelay(ECSDelayedEntityProcessingSystem* this) {
    return this->Delay;
}

/**
 * Get the time until the system is scheduled to run at.
* Returns zero (0) if the system is not running.
* Use isRunning() before checking this value.
*
* @return time when system will run at.
*/
method float GetRemainingTimeUntilProcessing(ECSDelayedEntityProcessingSystem* this) {
    if(this->Running) {
        return this->Delay-this->Acc;
    }
    return 0;
}

/**
 * Check if the system is counting down towards processing.
*
* @return true if it's counting down, false if it's not running.
*/
method bool IsRunning(ECSDelayedEntityProcessingSystem* this) {
    return this->Running;
}

/**
 * Stops the system from running, aborts current countdown.
* Call offerDelay or restart to run it again.
*/
method void Stop(ECSDelayedEntityProcessingSystem* this) {
    this->Running = false;
    this->Acc = 0;
}

#undef super