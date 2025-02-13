#pragma once
/**
 * shims for corefw
 */
#include <corefw/corefw.h>

#define new(T, args...) New((T*)cfw_create((CFClass*)T##Class), ## args)
#define method __attribute__((overloadable))

#include "cfwfs.h"
#include "bitvector.h"
#include "random.h"
#include "uuid.h"
#include "cfw.h"


struct CFArray {
	CFObject obj;
	void **data;
	size_t size;
};

static inline method void Clear(CFArray* this)
{

	for (int i = 0; i < this->size; i++)
		cfw_unref(this->data[i]);

	if (this->data != NULL)
		free(this->data);
    this->size = 0;
}

static inline method void* New(CFString* this)
{
    return cfw_new(cfw_string, NULL);
}
static inline method void* New(CFString* this, char* value)
{
    return cfw_new(cfw_string, value);    
}

static inline method void* Get(CFArray* this, int i)
{
    return cfw_array_get(this, i);
}

static inline method void* Get(CFMap* this, char* key)
{
    return cfw_map_get(this, key);
}

static inline method void Add(CFArray* this, void* item)
{
    cfw_array_push(this, item);
}

static inline method bool Remove(CFMap* this, char* key)
{
    return cfw_map_set(this, key, NULL);
}

static inline method void Put(CFMap* this, char* key, void* object)
{
    cfw_map_set(this, key, object);
}

static inline method void Put(CFArray* this, int index, void* object)
{
    cfw_array_set(this, index, object);
}

// static inline method void ForEach(CFMap* this, void(*func)(void* item))
static inline method void ForEach(CFMap* this, void(*func)(void* key, void* item))
{
   cfw_map_iter_t iter;

    cfw_map_iter(this, &iter);
    while (iter.key != NULL) {
        func(iter.key, iter.obj);
        cfw_map_iter_next(&iter);
    }
}
static inline method void ForEach(CFMap* this, void(^func)(void* key, void* item))
{
    cfw_map_iter_t iter;

    cfw_map_iter(this, &iter);
    while (iter.key != NULL) {
        func(iter.key, iter.obj);
        cfw_map_iter_next(&iter);
    }
}

static inline method char* cstr(CFString* this)
{
    return cfw_string_c(this);
}

static inline method char* ToString(CFString* this)
{
    return cfw_string_c(this);
}

static inline method int Length(CFArray* this)
{
    return cfw_array_size(this);
}

static inline method int Length(CFString* this)
{
    return cfw_string_length(this);
}

/**
 * join strings
 * 
 * @param count of strings
 * @param ... list of char*'s
 * @returns all strings concantenated together.
 */
 static inline char* strJoin(int count, ...)
{
    
    int size = 0;
    va_list args1;
    va_start(args1, count);
    va_list args2;
    va_copy(args2, args1);  

    /**
     * Caclulate length of the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args1, char*);
        size += strlen(str);
    }
    va_end(args1);
    char* result = (char*)calloc((size+1),  sizeof(char));

    /**
     * Now build the result string
     */
    for (int i = 0; i < count; ++i) {
        char* str = va_arg(args2, char*);
        strcat(result, str);
    }
    va_end(args2);
    return result;
}
