#ifndef REXTENSION_H
#define REXTENSION_H

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

#ifndef RL_FILENAME
    #if defined(__GNUC__)
        #define RL_FILENAME __FILE_NAME__
    #elif defined(__clang__)
        #define RL_FILENAME __BASE_FILE__
    #else
        #define RL_FILENAME __FILE__
    #endif
#endif // RL_FILENAME

void* rlMalloc(size_t sz, const char *file, int line);
void* rlCalloc(size_t num, size_t sz, const char *file, int line);
void* rlRealloc(void *ptr, size_t sz, const char *file, int line);
void rlFree(void *ptr);
void rlLeakCheck(void);

#if defined(__cplusplus)
}
#endif

#endif // REXTENSION_H
