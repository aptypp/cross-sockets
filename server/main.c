//
// Created by artur on 28.10.23.
//
#include <stdio.h>
#include <string.h>
#include "cross_sockets.h"
#include "string_extension.h"
#include "ip_address.h"

int main()
{
    cross_socket_initialize();

    uint64_t server_socket = cross_socket_open_udp();

    cross_socket_bind(server_socket, 12345);

    char buffer[256];

    while (true)
    {
        uint32_t ip_address;
        uint16_t port;

        fprintf(stderr, "start receive\n");

        cross_socket_receive_udp(server_socket, buffer, 256, &ip_address, &port);

        fprintf(stderr, "Message from client: %s, address: %s, port: %d\n", buffer, integer_address_to_string(ip_address), port);

        fprintf(stderr, "end receive\n");

        char message[] = "Hello from server\n";

        fprintf(stderr, "start send\n");

        cross_socket_send_udp(server_socket, message, strlen(message), ip_address, port);

        fprintf(stderr, "end send\n");
    }

    cross_socket_cleanup();
}

