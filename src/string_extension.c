//
// Created by Yurii on 10/28/2023.
//

#include <string_extension.h>
#include <string.h>
#include <stdlib.h>

String string_new(const char* string) {
    String result;

    result.length = strlen(string);

    result.buffer = (char*)malloc(result.length);

    strcpy(result.buffer, string);

    return result;
}

String string_concatenate(const String* left, const String* right) {
    String result;

    result.length = left->length + right->length;

    result.buffer = (char*)malloc(result.length);

    strcpy(result.buffer, left->buffer);

    strcat(result.buffer, right->buffer);

    return result;
}

String string_copy(const String* string) {
    String result;

    result.length = string->length;
    result.buffer = (char*)malloc(result.length);

    strcpy(result.buffer, string->buffer);

    return result;
}

void string_free(const String* string) {
    free(string->buffer);
}