#include "raylib.h"
#include "utils.h"

#define STB_LEAKCHECK_IMPLEMENTATION
#include "external/stb_leakcheck.h"

void* rlMalloc(size_t sz, const char *file, int line)
{
    return stb_leakcheck_malloc(sz, file, line);
}

void* rlCalloc(size_t num, size_t sz, const char *file, int line)
{
    size_t total_size = num * sz;
    void *ptr = stb_leakcheck_malloc(total_size, file, line);
    memset(ptr, 0, total_size);

    return ptr;
}

void* rlRealloc(void *ptr, size_t sz, const char *file, int line)
{
    return stb_leakcheck_realloc(ptr, sz, file, line);
}

void rlFree(void *ptr)
{
    stb_leakcheck_free(ptr);
}

static void PrintLeak(const char *reason, stb_leakcheck_malloc_info *mi)
{
    TraceLog(LOG_ERROR, "%s: %s (%4d): %zd bytes at %p", reason, mi->file, mi->line, mi->size, (void*)(mi+1));
}

void rlLeakCheck(void)
{
    stb_leakcheck_malloc_info *mi = mi_head;
    while (mi)
    {
        if ((ptrdiff_t) mi->size >= 0)
            PrintLeak("LEAKED", mi);
        
        mi = mi->next;
    }
}
