//
// Created by artur on 28.10.23.
//

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "cross_sockets.h"

uint64_t cross_socket_open_tcp()
{
    uint64_t descriptor;

    descriptor = socket(AF_INET, SOCK_STREAM, 0);

    return descriptor;
}

uint64_t cross_socket_open_udp()
{
    uint64_t descriptor;

    descriptor = socket(AF_INET, SOCK_DGRAM, 0);

    return descriptor;
}

void cross_socket_close(uint64_t descriptor)
{
    close((int32_t) descriptor);
}

int32_t cross_socket_bind(uint64_t descriptor, int32_t in_port)
{
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_address.sin_port = htons(in_port);

    return bind((int) descriptor, (const struct sockaddr*) &server_address, sizeof(server_address));
}

int32_t cross_socket_listen_tcp(uint64_t descriptor, int32_t connections_queue_length)
{
    return listen((int32_t) descriptor, connections_queue_length);;
}

int32_t cross_socket_connect_tcp(uint64_t descriptor, uint32_t in_address, int32_t in_port)
{
    struct sockaddr_in connection_address;

    connection_address.sin_family = AF_INET;
    connection_address.sin_addr.s_addr = htonl(in_address);
    connection_address.sin_port = htons(in_port);

    return connect((int) descriptor, (const struct sockaddr*) &connection_address, sizeof(connection_address));
}

uint64_t cross_socket_accept_tcp(uint64_t descriptor, uint32_t* out_address)
{
    uint64_t result;

    socklen_t address_len;
    struct sockaddr_in connection_address;

    result = accept((int) descriptor, (struct sockaddr*) &connection_address, &address_len);

    *out_address = ntohl(connection_address.sin_addr.s_addr);

    return result;
}

int32_t cross_socket_receive_tcp(uint64_t descriptor, char* out_buffer, uint32_t in_buffer_length)
{
    return (int32_t) recv((int32_t) descriptor, out_buffer, in_buffer_length, 0);
}

int32_t cross_socket_receive_udp(uint64_t descriptor, char* out_buffer, uint32_t in_buffer_length, uint32_t* out_address, int32_t* out_port)
{
    socklen_t address_length;
    struct sockaddr_in connection_address;

    int32_t errcode = (int32_t) recvfrom((int) descriptor, out_buffer, in_buffer_length, 0, (struct sockaddr*) &connection_address, &address_length);

    *out_address = ntohl(connection_address.sin_addr.s_addr);
    *out_port = ntohs(connection_address.sin_port);

    return errcode;
}

void cross_socket_send_tcp(uint64_t descriptor, const char* in_buffer, uint32_t in_buffer_length)
{
    send((int32_t) descriptor, in_buffer, in_buffer_length, 0);
}

void cross_socket_send_udp(uint64_t descriptor, const char* in_buffer, uint32_t in_buffer_length, uint32_t in_address, int32_t in_port)
{
    struct sockaddr_in connection_address;

    connection_address.sin_family = AF_INET;
    connection_address.sin_addr.s_addr = htonl(in_address);
    connection_address.sin_port = htons(in_port);

    sendto((int32_t) descriptor, in_buffer, in_buffer_length, 0, (struct sockaddr*) &connection_address, sizeof(connection_address));
}

void cross_socket_initialize()
{

}

void cross_socket_cleanup()
{

}
