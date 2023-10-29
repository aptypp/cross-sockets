//
// Created by artur on 28.10.23.
//
#include <stdio.h>
#include "cross_sockets.h"

int main()
{
    cross_socket_initialize();

    CrossSocket communication_socket = cross_socket_open_tcp();

    IpAddress server_ip_address = ip_address_new("127.0.0.1");

    cross_socket_connect_tcp(&communication_socket, &server_ip_address, 12345);

    String hello_message = string_new("Hello, my name is Client!");
    cross_socket_send_tcp(&communication_socket, &hello_message);

    String response = string_new_capacity(50);

    cross_socket_receive_tcp(&communication_socket, &response);

    printf("%s%s", "Message from server: ", response.buffer);

    string_free(&response);
    string_free(&server_ip_address.address);

    cross_socket_cleanup();
}

