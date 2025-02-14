/*******************************************************************
** This code is part of the Dark Framework.
**
MIT License

Copyright (c); 2018 Dark Overlord of Data

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software");, to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************/
#pragma once
#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include "class.h"
#include "object.h"
// #include "cfw.h"

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

typedef struct CFWBitVector CFWBitVector;
extern const CFWClass *CFWBitVectorClass;

/**
 * CFWBitVector instance variables
 */
 struct CFWBitVector {
    CFWObject obj;
    int length;
    unsigned int* words;
};


extern method void* New(CFWBitVector* this);
extern method void* New(CFWBitVector* this, int nbits);
extern method int NextSetBit(CFWBitVector* this, int fromIndex); 
extern method bool Intersects(CFWBitVector* this, CFWBitVector* set); 
extern method bool IsEmpty(CFWBitVector* this); 
extern method void Set(CFWBitVector* this, int bitIndex, bool value); 
extern method bool Get(CFWBitVector* this, int bitIndex); 
extern method void Clear(CFWBitVector* this);
extern method void Clear(CFWBitVector* this, int bitIndex);  
extern method char* ToString(CFWBitVector* this);
