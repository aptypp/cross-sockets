//
// Created by artur on 28.10.23.
//

#include "ip_address.h"

IpAddress ip_address_new(const char* address)
{
    IpAddress ip_address;

    stpcpy(ip_address.address, address);

    ip_address.len = (int) strlen(address);

    return ip_address;
}
