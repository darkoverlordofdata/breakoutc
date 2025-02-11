#include "core/manager.h"
#include "cfw.h"
#include "core/entity.h"
#include "core/entityobserver-private.h"
#include "core/entityobserver.h"
#include "core/manager-private.h"
#include "core/world.h"
#include "ecs.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSManager);

#define super ECSEntityObserver


method void* New(ECSManager* this, ECSIManager* vptr)
{
    New((super*)this, (ECSIEntityObserver*)vptr);
    return this;
}

method void Initialize(ECSManager* this) 
{ 
    this->vptr->Initialize(this); 
}

method void SetWorld(ECSManager* this, ECSWorld* world)
{
    this->World = world;
}

method ECSWorld* GetWorld(ECSManager* this)
{
    return this->World;
}

method void Added(ECSManager* this, ECSEntity* entity) {}

method void Changed(ECSManager* this, ECSEntity* entity) {}

method void Deleted(ECSManager* this, ECSEntity* entity) {}

method void Disabled(ECSManager* this, ECSEntity* entity) {}

method void Enabled(ECSManager* this, ECSEntity* entity) {}

#undef super