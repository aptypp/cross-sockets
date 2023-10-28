//
// Created by artur on 28.10.23.
//

#ifndef CROSS_SOCKETS_CROSS_SOCKETS_H
#define CROSS_SOCKETS_CROSS_SOCKETS_H

#include <stdint.h>

typedef struct
{
    int64_t descriptor;
} CrossSocket;

CrossSocket cross_socket_open_tcp();

CrossSocket cross_socket_open_udp();

void cross_socket_close(const CrossSocket* socket);

void cross_socket_bind(const CrossSocket* socket, int port);

int cross_socket_listen_tcp(const CrossSocket* socket, int connections_queue_length);

int cross_socket_connect_tcp(const CrossSocket* socket, char* address, int* address_len);

int cross_socket_accept_tcp(const CrossSocket* socket, char* address, int* address_len);

int cross_socket_receive_tcp(const CrossSocket* socket, char* buffer, int buffer_size);

int cross_socket_receive_udp(const CrossSocket* socket, char* buffer, int buffer_size);

void cross_socket_send_tcp(const CrossSocket* socket, char* buffer, int buffer_size);

void cross_socket_send_udp(const CrossSocket* socket, char* buffer, int buffer_size, char* address, int* address_len);

#endif //CROSS_SOCKETS_CROSS_SOCKETS_H
