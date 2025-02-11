/**
 * An Aspects is used by systems as a matcher against entities, to check if a system is
 * interested in an entity. Aspects define what sort of component types an entity must
 * possess, or not possess.
 *
 * This creates an aspect where an entity must possess A and B and C:
 * Aspect.getAspectForAll(A.class, B.class, C.class)
 *
 * This creates an aspect where an entity must possess A and B and C, but must not possess U or V.
 * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class)
 *
 * This creates an aspect where an entity must possess A and B and C, but must not possess U or V, but must possess one of X or Y or Z.
 * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)
 *
 * You can create and compose aspects in many ways:
 * Aspect.getEmpty().one(X.class, Y.class, Z.class).all(A.class, B.class, C.class).exclude(U.class, V.class)
 * is the same as:
 * Aspect.getAspectForAll(A.class, B.class, C.class).exclude(U.class, V.class).one(X.class, Y.class, Z.class)
 *
 * @author Arni Arent
 *
 */
#include "core/aspect.h"
#include "cfw.h"
#include "core/aspect-private.h"
#include "core/component-private.h"
#include "ecs.h"

static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self) {}

corefw(ECSAspect);


ECSComponentTypeFactory* ECSAspect_TypeFactory;

method void SetTypeFactory(ECSComponentTypeFactory* typeFactory)
{
    ECSAspect_TypeFactory = typeFactory;
}

method void* New(ECSAspect* this)
{
    this->AllSet = new (CFBitVector);
    this->ExclusionSet = new (CFBitVector);
    this->OneSet = new (CFBitVector);
    return this;
}

method void SetWorld(ECSAspect* this, ECSWorld* world)
{
    this->World = world;
}

method CFBitVector* GetAllSet(ECSAspect* this)
{
    return this->AllSet;
}

method CFBitVector* GetExclusionSet(ECSAspect* this)
{
    return this->ExclusionSet;
}

method CFBitVector* GetOneSet(ECSAspect* this)
{
    return this->OneSet;
}

/**
 * Returns an aspect where an entity must possess all of the specified component types.
 * @param {Type} type a required component type
 * @param {Array<Type>} types a required component type
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
method ECSAspect* All(ECSAspect* this, int count, va_list _args)
{
    va_list args;
    va_copy(args, _args);
    for (int i = 0; i < count; ++i) {
        ECSComponent* t = va_arg(args, ECSComponent*);
        CFClass* c = &t->obj.cls;
        var index = GetIndexFor(ECSAspect_TypeFactory, c);
        Set(this->AllSet, index, true);
    }
    va_end(args);
    return this;
}

/**
 * Excludes all of the specified component types from the aspect. A system will not be
 * interested in an entity that possesses one of the specified exclusion component types.
 *
 * @param {Type} type component type to exclude
 * @param {Array<Type>} types component type to exclude
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
method ECSAspect* Exclude(ECSAspect* this, int count, va_list _args)
{
    va_list args;
    va_copy(args, _args);
    for (int i = 0; i < count; ++i) {
        ECSComponent* t = va_arg(args, ECSComponent*);
        var index = GetIndexFor(ECSAspect_TypeFactory, t->obj.cls);
        Set(this->ExclusionSet, index, true);
    }
    va_end(args);
    return this;
}

/**
 * Returns an aspect where an entity must possess one of the specified component types.
 * @param {Type} type one of the types the entity must possess
 * @param {Array<Type>} types one of the types the entity must possess
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
method ECSAspect* One(ECSAspect* this, int count, va_list _args)
{
    va_list args;
    va_copy(args, _args);
    for (int i = 0; i < count; ++i) {
        ECSComponent* t = va_arg(args, void*);
        var index = GetIndexFor(ECSAspect_TypeFactory, t->obj.cls);
        Set(this->OneSet, index, true);
    }
    va_end(args);
    return this;
}

/**
 * Creates an aspect where an entity must possess all of the specified component types.
 *
 * @param {Type} type a required component type
 * @param {Array<Type>} types a required component type
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
#define GetAspectForAll(...) _GetAspectForAll(PP_NARG(__VA_ARGS__), __VA_ARGS__)
method ECSAspect* _GetAspectForAll(int count, ...)
{
    var aspect = new (ECSAspect);

    va_list args;
    va_start(args, count);
    All(aspect, count, args);
    va_end(args);

    return aspect;
}

/**
 * Creates an aspect where an entity must possess one of the specified component types.
 *
 * @param {Type} type one of the types the entity must possess
 * @param {Array<Type>} types one of the types the entity must possess
 * @return {artemis.Aspect} an aspect that can be matched against entities
 */
#define GetAspectForOne(...) _GetAspectForOne(PP_NARG(__VA_ARGS__), __VA_ARGS__)
method ECSAspect* _GetAspectForOne(int count, ...)
{
    var aspect = new (ECSAspect);

    va_list args;
    va_start(args, count);
    One(aspect, count, args);
    va_end(args);

    return aspect;
}

/**
 * Creates and returns an empty aspect. This can be used if you want a system that processes no entities, but
 * still gets invoked. Typical usages is when you need to create special purpose systems for debug rendering,
 * like rendering FPS, how many entities are active in the world, etc.
 *
 * You can also use the all, one and exclude methods on this aspect, so if you wanted to create a system that
 * processes only entities possessing just one of the components A or B or C, then you can do:
 * Aspect.getEmpty().one(A,B,C);
 *
 * @return {artemis.Aspect} an empty Aspect that will reject all entities.
 */
method ECSAspect* GetAspectForNone(void)
{
    return new (ECSAspect);
}

