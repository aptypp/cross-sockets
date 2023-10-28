//
// Created by artur on 28.10.23.
//

#ifndef CROSS_SOCKETS_CROSS_SOCKETS_H
#define CROSS_SOCKETS_CROSS_SOCKETS_H

#include <stdint.h>
#include "ip_address.h"
#include "string.h"

typedef struct
{
    uint64_t descriptor;
} CrossSocket;

void cross_socket_initialize();

CrossSocket cross_socket_open_tcp();

CrossSocket cross_socket_open_udp();

void cross_socket_close(const CrossSocket* socket);

void cross_socket_bind(const CrossSocket* socket, int port);

int cross_socket_listen_tcp(const CrossSocket* socket, int connections_queue_length);

int cross_socket_connect_tcp(const CrossSocket* socket, const IpAddress* ip_address, int port);

CrossSocket cross_socket_accept_tcp(const CrossSocket* socket, IpAddress* ip_address);

int cross_socket_receive_tcp(const CrossSocket* socket, const String* buffer);

int cross_socket_receive_udp(const CrossSocket* socket, const String* buffer, IpAddress* ip_address);

void cross_socket_send_tcp(const CrossSocket* socket, const String* buffer);

void cross_socket_send_udp(const CrossSocket* socket, const String* buffer, const IpAddress* ip_address, int port);

void cross_socket_cleanup();

#endif //CROSS_SOCKETS_CROSS_SOCKETS_H
