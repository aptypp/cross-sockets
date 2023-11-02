//
// Created by artur on 28.10.23.
//
#include <stdio.h>
#include <string.h>
#include "cross_sockets.h"
#include "ip_address.h"
#include "string_extension.h"

int main()
{


    cross_socket_initialize();

    uint64_t communication_socket = cross_socket_open_udp();

    uint32_t server_ip_address = string_address_to_integer("51.20.184.146");
    uint16_t server_port = 12345;

    //cross_socket_bind(communication_socket, 12346);

    char message[] = "Hello, my name is Client!\n";

    fprintf(stderr, "start send\n");

    cross_socket_send_udp(communication_socket, message, strlen(message), server_ip_address, server_port);

    fprintf(stderr, "end send\n");

    uint32_t ip_address;
    uint16_t port;

    char buffer[256];

    fprintf(stderr, "start receive\n");

    cross_socket_receive_udp(communication_socket, buffer, 256, &ip_address, &port);

    fprintf(stderr, "end receive\n");

    fprintf(stderr, "Message from server: %s, address: %s, port: %d\n", buffer, integer_address_to_string(ip_address), port);

    cross_socket_cleanup();
}

