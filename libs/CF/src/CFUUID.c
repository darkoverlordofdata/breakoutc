/*
 * Copyright (c) 2025, darkoverlordofdata@gmail.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "CFObject.h"
#include "CFString.h"
#include "CFUUID.h"

struct __CFUUID {
    struct __CFObject obj;
    CFUUIDBytes value;
};

/**
 * get a random version 4 uuid
 * xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
 *
 */            
static bool
ctor(void *ptr, va_list args)
{
    (void*)args;
    
    CFUUIDRef this = ptr;

    // get 16 random bytes
    int d0 = rand();
    int d1 = rand();
    int d2 = rand();
    int d3 = rand();

    // unpack bytes and set versioning
    this->value.byte0 = d0&0xff;
    this->value.byte1 = d0>>8&0xff;
    this->value.byte2 = d0>>16&0xff;
    this->value.byte3 = d0>>24&0xff;

    this->value.byte4 = d1&0xff;
    this->value.byte5 = d1>>8&0xff;
    this->value.byte6 = (d1>>16&0x0f)|0x40;  /* Set GUID version to 4 --- truly random generation */
    this->value.byte7 = d1>>24&0xff;

    this->value.byte8 = (d2&0x3f)|0x80;     /* Set the GUID variant to DCE */
    this->value.byte9 = d2>>8&0xff;
    this->value.byte10 = d2>>16&0xff;
    this->value.byte11 = d2>>24&0xff;

    this->value.byte12 = d3&0xff;
    this->value.byte13 = d3>>8&0xff;
    this->value.byte14 = d3>>16&0xff;
    this->value.byte15 = d3>>24&0xff;

    return true;
}

static bool
equal(void *ptr1, void *ptr2)
{
    CFObjectRef obj2 = ptr2;
    if (obj2->cls != CFUUID)
        return false;

    CFUUIDRef this = ptr1;
    CFUUIDRef that = ptr2;

    return (
          this->value.byte0 == that->value.byte0
        & this->value.byte1 == that->value.byte1
        & this->value.byte2 == that->value.byte2
        & this->value.byte3 == that->value.byte3
        & this->value.byte4 == that->value.byte4
        & this->value.byte5 == that->value.byte5
        & this->value.byte6 == that->value.byte6
        & this->value.byte7 == that->value.byte7
        & this->value.byte8 == that->value.byte8
        & this->value.byte9 == that->value.byte9
        & this->value.byte10 == that->value.byte10
        & this->value.byte11 == that->value.byte11
        & this->value.byte12 == that->value.byte12
        & this->value.byte13 == that->value.byte13
        & this->value.byte14 == that->value.byte14
        & this->value.byte15 == that->value.byte15
    );
}

static uint32_t
hash(void *ptr)
{
    size_t this = (size_t)ptr;
    return (uint32_t)this;
}

static void*
copy(void *ptr)
{
    return CFRef(ptr);
}

static CFStringRef 
toString(void *ptr)
{
    static char hex[256][3] = { // hex identity values 0-255
      "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
      "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
      "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
      "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
      "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
      "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
      "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
      "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
      "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
      "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
      "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
      "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
      "c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
      "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db", "dc", "dd", "de", "df",
      "e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
      "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
    };

    CFUUIDRef this = ptr;
    char r[37];

    memcpy(&r[0],  hex[this->value.byte0], 2);
    memcpy(&r[2],  hex[this->value.byte1], 2);
    memcpy(&r[4],  hex[this->value.byte2], 2);
    memcpy(&r[6],  hex[this->value.byte3], 2);
    r[8] = '-';
    memcpy(&r[9],  hex[this->value.byte4], 2);
    memcpy(&r[11], hex[this->value.byte5], 2);
    r[13] = '-';
    memcpy(&r[14], hex[this->value.byte6], 2);
    memcpy(&r[16], hex[this->value.byte7], 2);
    r[18] = '-';
    memcpy(&r[19], hex[this->value.byte8], 2);
    memcpy(&r[21], hex[this->value.byte9], 2);
    r[23] = '-';
    memcpy(&r[24], hex[this->value.byte10], 2);
    memcpy(&r[26], hex[this->value.byte11], 2);
    memcpy(&r[28], hex[this->value.byte12], 2);
    memcpy(&r[30], hex[this->value.byte13], 2);
    memcpy(&r[32], hex[this->value.byte14], 2);
    memcpy(&r[34], hex[this->value.byte15], 2);
    r[36] = 0;

    return CFCreate(CFString, r);
}

CFStringRef CFUUIDToString(CFUUIDRef this)
{
    return toString(this);
}


CFUUIDRef CFUUIDNew() {
    CFUUIDRef this = CFNew(CFUUID);
    return this;
}

CFUUIDRef CFUUIDCreate() {
    CFUUIDRef this = CFCreate(CFUUID);
    return this;
}

static struct __CFClass class = {
    .name = "CFUUID",
    .size = sizeof(struct __CFUUID),
    .ctor = ctor,
    .equal = equal,
    .hash = hash,
    .copy = copy,
    .toString = toString
};
CFClassRef CFUUID = &class;
