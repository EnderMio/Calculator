#include "str.h"
string* string_build() {
    string* str = (string *)malloc(sizeof(string));
    str->len = 0;
    str->capacity = 1;
    str->vol = NULL;
    return str;
}
void string_destory(string* str) {
    free(str->vol);
    free(str);
    str = NULL;
    return;
}
void string_add(string* str, const char* s) {
    size_t lens = strlen(s);
    if(str->len + lens + 1 > str->capacity) {
        str->vol = (char *)realloc(str->vol, 2 * sizeof(char) * (str->len + lens + 1));
        str->capacity = 2 * (str->len + lens + 1);
    }
    if(str->len == 0) strcpy(str->vol, s);
    else strcat(str->vol, s);
    str->len += lens;
}
char* string_cstr(string* str) {
    return str->vol;
}
void string_del(string* str, size_t lens) {
    assert(str->len >= lens);
    str->len -= lens;
    str->vol[str->len] = 0;
}
void string_clear(string* str) {
    free(str->vol);
    str->vol = NULL;
    str->capacity = 1;
    str->len = 0;
}