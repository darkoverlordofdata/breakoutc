#include "core/componenttype.h"
#include "cfw.h"
#include "core/componenttype-private.h"
#include "ecs.h"
#include <assert.h>

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSComponentType);

int ECSUniqueComponentIndex = 0;

method void* New(ECSComponentType* this, CFClass* type)
{
    this->Type = type;
    this->Index = ECSUniqueComponentIndex++;
    return this;
}

method char* GetName(ECSComponentType* this)
{
    return this->Type->name;
}

method int GetIndex(ECSComponentType* this)
{
    return this->Index;
}
