#ifndef FED_UTILS_H
#define FED_UTILS_H

#include <stddef.h>
#include <stdlib.h>

#ifdef FED_UTILS_C
#include <stdarg.h>
#include <stdio.h>
#endif

#include <string.h>

typedef struct StringView
{
    const char *begin;
    size_t length;
}
StringView;

typedef struct String
{
    char *data;
    size_t size;
    size_t capacity;
}
String;

#define SV_FMT "%.*s"
#define SV_ARG(sv) (int) (sv)->length, (sv)->begin

#define VEC_INIT_CAP 16

#define VEC_RESERVE(vec, cap)                                                               \
    do                                                                                      \
    {                                                                                       \
        if((cap) > (vec)->capacity)                                                         \
        {                                                                                   \
            if((vec)->capacity == 0)                                                        \
                (vec)->capacity = VEC_INIT_CAP;                                             \
            while((cap) > (vec)->capacity)                                                  \
                (vec)->capacity *= 2;                                                       \
            (vec)->data = realloc((vec)->data, (vec)->capacity * sizeof(*(vec)->data));     \
        }                                                                                   \
    } while(0)

#define VEC_PUSH(vec, x)                    \
    do                                      \
    {                                       \
        VEC_RESERVE(vec, (vec)->size + 1);  \
        (vec)->data[(vec)->size++] = (x);   \
    } while(0)

#define VEC_PUSH_ARR(vec, arr, aSize)                                               \
    do {                                                                            \
        VEC_RESERVE((vec), (vec)->size + (aSize));                                  \
        memcpy((vec)->data + (vec)->size, (arr), (aSize) * sizeof(*(vec)->data));   \
        (vec)->size += aSize;                                                       \
    } while(0)

#define VEC_BACK(vec) (vec)->data[(vec)->size-1]

#define ARR_LEN(arr) (sizeof(arr) / sizeof(*arr))

size_t str_append_f(String *str, const char *fmt, ...);

#define STR_PUSH(str, c) VEC_PUSH(str, c)
#define STR_PUSH_BUF(str, buf, bSize) VEC_PUSH_ARR(str, buf, bSize)
#define STR_PUSH_SV(str, sv) VEC_PUSH_ARR(str, (sv)->begin, (sv)->length)
#define STR_PUSH_CSTR(str, cStr) VEC_PUSH_ARR(str, cStr, sizeof(cStr) - 1)
#define STR_PUSH_F(str, ...) str_append_f(str, __VA_ARGS__)

#define STR_MOVE(dst, src)      \
    do {                        \
        *dst = *src;            \
        *src = (String){0};     \
    } while(0)

#define CLAMP(x, a, b)      \
    do {                    \
        if((x) < (a))       \
            (x) = (a);      \
        else if((x) > (b))  \
            (x) = (b);      \
    } while(0)

#ifdef FED_UTILS_C
size_t str_append_f(String *str, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    size_t n = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    VEC_RESERVE(str, str->size + n + 1);

    char *dst = str->data + str->size;

    va_start(args, fmt);
    vsnprintf(dst, n + 1, fmt, args);
    va_end(args);

    str->size += n;

    return n;
}
#endif

#endif