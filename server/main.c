//
// Created by artur on 28.10.23.
//
#include <stdio.h>
#include "cross_sockets.h"
#include "string_extension.h"
#include "ip_address.h"

int main()
{
    char buffer[256];

    scanf("%s", buffer);

    uint32_t bind_address = string_address_to_integer(buffer);

    cross_socket_initialize();

    uint64_t server_socket = cross_socket_open_tcp();

    cross_socket_bind(server_socket, bind_address, 12345);

    cross_socket_listen_tcp(server_socket, 10);

    uint64_t client_socket;

    while (true)
    {
        uint32_t ip_address;
        uint16_t port;

        client_socket = cross_socket_accept_tcp(server_socket, &ip_address, &port);
        printf("%s", "New connection!");

        String hello_message = string_new("You successfully connected :)");
        cross_socket_send_tcp(client_socket, hello_message.buffer, hello_message.length);
        //cross_socket_send_udp(client_socket, hello_message.buffer, hello_message.length, ip_address, port);
    }

    cross_socket_cleanup();
}

