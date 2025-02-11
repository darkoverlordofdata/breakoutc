#include "cfwfs.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "cfw.h"

typedef CFString* (*Builder)(const char* path);
static Builder getPathBuilder();
static CFString* getPath(const char* path);
static char* const getRoot();
static CFString* getPathRelativeRoot(const char* path);
static CFString* getPathRelativeBinary(const char* path);

//#include <corefw/file-private.h>
struct CFFile {
	CFStream stream;
	int fd;
	bool at_end;
};

/**
 * getPath
 * 
 * @param path
 * @returns the path
 */
static CFString* getPath(const char* path)
{
    Builder pathBuilder = getPathBuilder();
    return (*pathBuilder)(path);
}

/**
 * getRoot
 * 
 * @returns this path root
 */
static char* const getRoot()
{
    static char buf[2048];
#ifdef __EMSCRIPTEN__
    return strcpy(buf, "./");
#else
    return getcwd(buf, sizeof(buf));
#endif
}

/**
 * getPathBuilder
 * 
 * @returns path builder function
 */
static Builder getPathBuilder()
{
    if (strcmp(getRoot(), "") != 0)
        return getPathRelativeRoot;
    else
        return getPathRelativeBinary;
}

/**
 * getPathRelativeRoot
 * 
 * @param path
 */
static CFString* getPathRelativeRoot(const char* path)
{
    CFString* res = cfw_create(cfw_string, getRoot());
    cfw_string_append_c(res, "/");
    cfw_string_append_c(res, path);
    return res;
}

/**
 * getPathRelativeBinary
 * 
 * @param path
 */
static CFString* getPathRelativeBinary(const char* path)
{
    CFString* res = cfw_create(cfw_string, "../../../");
    cfw_string_append_c(res, path);
    return res;
}

/**
 * ReadTextFile
 * 
 * @param path path to file
 * @returns string with file contents
 * 
 */
CFString* readTextFile(char* path)
{
    struct stat statbuf;

    CFFile* handle = cfw_new(cfw_file, path, "r");
    if (!handle) {
        printf("Unable to open %s\n", path);
        return cfw_create(cfw_string, "");
    }

    if (fstat(handle->fd, &statbuf) == -1) {
        printf("Unable to stat %s\n", path);
        return cfw_create(cfw_string, "");
    }
    
    long len = statbuf.st_size;
    char* content = (char*)calloc(1, len + 1);
    cfw_stream_read(handle, content, len);
    cfw_stream_close(handle);
    CFString* result = cfw_create(cfw_string, content);
    free(content);
    return result;
}

/**
 * CFFS object
 */
struct CFFS CFFS = {
    .getPath = getPath,
    .getRoot = getRoot,
    .getPathRelativeRoot = getPathRelativeRoot,
    .getPathRelativeBinary = getPathRelativeBinary,
    .readTextFile = readTextFile
};
