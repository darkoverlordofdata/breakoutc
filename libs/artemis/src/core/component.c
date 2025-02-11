#include "core/component.h"
#include "cfw.h"
#include "core/component-private.h"
#include "ecs.h"
#include <assert.h>

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSComponent);

method void* New(ECSComponent* this)
{
    return this;
}
