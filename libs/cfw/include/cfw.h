#pragma once
/**
 * shims for corefw
 */
#include <corefw/corefw.h>

static inline struct CFObject* asObject(void* obj) { return obj; }

#define var __auto_type
/**
 * enable multi-methods
 */
#define method __attribute__((overloadable))
/**
 * MACRO corefw
 *      generate typeinfo boilerplate for corefw
 */
#define corefw(CLASSNAME)               \
    typedef struct CLASSNAME CLASSNAME; \
    static bool ctor(void*, va_list);   \
    static void dtor(void*);            \
    static bool equal(void*, void*);    \
    static uint32_t hash(void*);        \
    static void* copy(void*);           \
    const static CFClass class = {     \
        .name = #CLASSNAME,             \
        .size = sizeof(CLASSNAME),      \
        .ctor = ctor,                   \
        .dtor = dtor,                   \
        .equal = equal,                 \
        .hash = hash,                   \
        .copy = copy                    \
    };                                  \
    const CFClass* CLASSNAME##Class = &class



/**
 *  MACRO Min
 *      cache results of calculation in pocket scope 
 */
#define Min(a, b)            \
    ({                       \
        __auto_type _a = a;  \
        __auto_type _b = b;  \
        (_a < _b) ? _a : _b; \
    })

/**
 *  MACRO Max
 *      cache results of calculation in pocket scope 
 */
#define Max(a, b)            \
    ({                       \
        __auto_type _a = a;  \
        __auto_type _b = b;  \
        (_a > _b) ? _a : _b; \
    })

/**
 *  MACRO NARG
 *      Count the number of arguments
 */
#define PP_NARG(...)                                                    \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)                                                   \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(                                                       \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,                       \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,                       \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,                       \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,                       \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,                       \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,                       \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N()                                                     \
         63,62,61,60,                                                   \
         59,58,57,56,55,54,53,52,51,50,                                 \
         49,48,47,46,45,44,43,42,41,40,                                 \
         39,38,37,36,35,34,33,32,31,30,                                 \
         29,28,27,26,25,24,23,22,21,20,                                 \
         19,18,17,16,15,14,13,12,11,10,                                 \
         9,8,7,6,5,4,3,2,1,0

/**
 *  MACRO join
 *      String.join(..)
 */
#define join(...) STR_JOIN(PP_NARG(__VA_ARGS__), __VA_ARGS__)
char* STR_JOIN(int count, ...);

#define new(T, args...) New((T*)cfw_create((CFClass*)T##Class), ## args)
// #define create(T, args...) New((T*)cfw_create((CFClass*)T##Class), ## args)

// #define override(super, class, method) (void(*)(super* this))((void(*)(class* this))method)

#define abstract(class, method) (void*(*)(void* this))((void*(*)(class* this))method)

// typedef CFArray Array;
// typedef CFBool Bool;
// typedef CFDouble Double;
// typedef CFFile File;
// typedef CFInt Int;
// typedef CFMap Map;
// typedef CFRefPool RefPool;
// typedef CFStream Stream;
// typedef CFString String;

// #define ArrayClass cfw_array
// #define BoolClass cfw_bool
// #define DoubleClass cfw_double
// #define FileClass cfw_file
// #define CFIntClass cfw_int
// #define MapClass cfw_map
// #define RefPoolClass cfw_refpool
// #define StreamClass cfw_stream
// #define StringClass cfw_string

#include "cfwfs.h"
#include "bitvector.h"
#include "random.h"
#include "uuid.h"

extern method void Clear(CFArray* this);
extern method void* Get(CFArray* this, int i);
extern method void* Get(CFMap* this, char* key);
extern method void Add(CFArray* this, void* item);
extern method bool Remove(CFArray* this, int i);
extern method bool Remove(CFMap* this, char* key);
extern method void Put(CFMap* this, char* key, void* object);
extern method void Put(CFArray* this, int index, void* object);
extern method void ForEach(CFMap* this, void(^func)(void* key, void* item));
extern method void ForEach(CFMap* this, void(*func)(void* key, void* item));
extern method int Length(CFArray* this);
extern method int Length(CFString* this);
extern method char* cstr(CFString* this);
extern method char* ToString(CFString* this);
extern method void* New(CFString* this);
extern method void* New(CFString* this, char* value);

