//
// Created by Slayer on 04/10/2022.
//

#ifndef CBIN_SRC_CBIN_COMMON_H
#define CBIN_SRC_CBIN_COMMON_H
#include <stddef.h>

#if defined(CBIN_REALLOC) || defined(CBIN_FREE)
#    if !(defined(CBIN_REALLOC) && defined(CBIN_FREE))
#        error "Both CBIN_REALLOC and CBIN_FREE must be defined, or neither."
#    endif
#endif

#ifndef CBIN_REALLOC
#    ifndef CBIN_NO_MALLOC
#        include <stdlib.h>
#        define CBIN_REALLOC(ptr, new_size) (realloc((ptr), (new_size)))
#    else
#        define CBIN_REALLOC(ptr, new_size)                                    \
            ((void)(ptr), (void)(new_size), NULL)
#    endif
#endif

#ifndef CBIN_FREE
#    ifndef CBIN_NO_MALLOC
#        include <stdlib.h>
#        define CBIN_FREE(ptr) (free((ptr)))
#    else
#        define CBIN_FREE(ptr) ((void)(ptr))
#    endif
#endif

#ifdef __cplusplus
#    define CBIN_HEADER_BEGIN extern "C" {
#    define CBIN_HEADER_END }
#else
#    define CBIN_HEADER_BEGIN
#    define CBIN_HEADER_END
#endif

#define CBIN_ERR_OK 0
#define CBIN_ERR_FAILED 1
#define CBIN_ERR_OUT_OF_BOUNDS 2
#define CBIN_ERR_OUT_OF_MEMORY 3

#if defined(__clang__) || defined(__GNUC__)
#    define CBIN_LIKELY(x) __builtin_expect(!!(x), 1)
#    define CBIN_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#    define CBIN_LIKELY(x) (x)
#    define CBIN_UNLIKELY(x) (x)
#endif

typedef int cbin_err_t;

#endif // CBIN_SRC_CBIN_COMMON_H
