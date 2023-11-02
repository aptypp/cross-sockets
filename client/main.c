//
// Created by artur on 28.10.23.
//
#include <stdio.h>
#include "cross_sockets.h"
#include "ip_address.h"
#include "string_extension.h"

int main()
{
    cross_socket_initialize();

    uint64_t communication_socket = cross_socket_open_tcp();

    uint32_t server_ip_address = string_address_to_integer("127.0.0.1");

    cross_socket_connect_tcp(communication_socket, server_ip_address, 12345);

    String hello_message = string_new("Hello, my name is Client!");
    cross_socket_send_tcp(communication_socket, hello_message.buffer, hello_message.length);

    String response = string_new_capacity(50);

    uint32_t ip_address;
    uint16_t port;

    cross_socket_receive_udp(communication_socket, response.buffer, response.capacity, &ip_address, &port);

    printf("Message from server: %s", response.buffer);

    string_free(&response);

    cross_socket_cleanup();
}

