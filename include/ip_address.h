//
// Created by artur on 28.10.23.
//

#ifndef CROSS_SOCKETS_IP_ADDRESS_H
#define CROSS_SOCKETS_IP_ADDRESS_H

#include <string.h>
#include <stdint.h>

typedef struct
{
    char* address;
    uint64_t len;
} IpAddress;

IpAddress ip_address_new(const char* address);

#endif //CROSS_SOCKETS_IP_ADDRESS_H