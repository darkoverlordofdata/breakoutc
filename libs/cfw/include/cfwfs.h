#pragma once
#include <corefw/object.h>
#include <corefw/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CFFS {
    CFString* (*getPath)(const char* path);
    char* const (*getRoot)();
    CFString* (*getPathRelativeRoot)(const char* path);
    CFString* (*getPathRelativeBinary)(const char* path);
    CFString* (*readTextFile)(char* path);
};

extern struct CFFS CFFS;