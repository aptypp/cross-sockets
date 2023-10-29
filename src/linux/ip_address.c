//
// Created by artur on 28.10.23.
//
#include <arpa/inet.h>
#include "ip_address.h"

uint32_t string_address_to_integer(const char* address)
{
    return ntohl(inet_addr(address));
}

char* integer_address_to_string(uint32_t address)
{
    struct in_addr addr;

    addr.s_addr = htonl(address);

    return inet_ntoa(addr);
}
