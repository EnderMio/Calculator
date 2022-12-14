#ifndef _Str_H_
#define _Str_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef struct STRING {
    char* vol;
    size_t len, capacity;
}string;
string* string_build();
void string_destory(string* str);
void string_add(string* str, const char* s);
char* string_cstr(string* str);
void string_del(string* str, size_t lens);
void string_clear(string* str);

#ifdef __cplusplus
}
#endif

#endif