#include "core/entityobserver.h"
#include "cfw.h"
#include "core/entityobserver-private.h"
#include "ecs.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSEntityObserver);

method void* New(ECSEntityObserver* this, ECSIEntityObserver* vptr)
{
    this->vptr = vptr;
    return this;
}

method void Added(ECSEntityObserver* this, ECSEntity* entity)
{
    this->vptr->Added(this, entity);
}
method void Changed(ECSEntityObserver* this, ECSEntity* entity)
{    
    this->vptr->Changed(this, entity);
}
method void Deleted(ECSEntityObserver* this, ECSEntity* entity)
{
    this->vptr->Deleted(this, entity);
}
method void Disabled(ECSEntityObserver* this, ECSEntity* entity)
{
    this->vptr->Disabled(this, entity);
}
method void Enabled(ECSEntityObserver* this, ECSEntity* entity)
{
    this->vptr->Enabled(this, entity);
}
