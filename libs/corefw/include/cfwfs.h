#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "string.h"
#include "file.h"
#include "stream.h"

struct CFWFS {
    CFWString* (*getPath)(const char* path);
    char* const (*getRoot)();
    CFWString* (*getPathRelativeRoot)(const char* path);
    CFWString* (*getPathRelativeBinary)(const char* path);
    CFWString* (*readTextFile)(char* path);
};

extern struct CFWFS CFWFS;