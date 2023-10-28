//
// Created by Yurii on 10/28/2023.
//

#ifndef CROSS_SOCKETS_STRING_EXTENSION_H
#define CROSS_SOCKETS_STRING_EXTENSION_H

#include <stdint.h>

typedef struct {
    char* buffer;
    uint64_t length;
} String;

String string_new(const char* string);

String string_concatenate(const String* left, const String* right);

String string_copy(const String* string);

void string_free(const String* string);

#endif //CROSS_SOCKETS_STRING_EXTENSION_H
