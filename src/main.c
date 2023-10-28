//
// Created by artur on 28.10.23.
//
#include <stdio.h>
#include "cross_sockets.h"

int main()
{
    cross_socket_initialize();

    CrossSocket server_socket = cross_socket_open_tcp();

    cross_socket_bind(&server_socket, 12345);

    cross_socket_listen_tcp(&server_socket, 10);

    CrossSocket client_socket;

    while (true) {
        IpAddress ip_address;
        client_socket = cross_socket_accept_tcp(&server_socket, &ip_address);
        printf("New connection!");


        String hello_message = string_new("Connected!");
        cross_socket_send_tcp(&client_socket, &hello_message);

        string_free(&ip_address.address);
    }

    cross_socket_cleanup();
}

