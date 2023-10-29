//
// Created by artur on 28.10.23.
//

#include "ip_address.h"

IpAddress ip_address_new(const char* address)
{
    IpAddress result;

    result.address = string_new(address);

    return result;
}
