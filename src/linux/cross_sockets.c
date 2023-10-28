//
// Created by artur on 28.10.23.
//

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cross_sockets.h"

CrossSocket cross_socket_open_tcp()
{
    CrossSocket result;

    result.descriptor = socket(AF_INET, SOCK_STREAM, 0);

    return result;
}

CrossSocket cross_socket_open_udp()
{
    CrossSocket result;

    result.descriptor = socket(AF_INET, SOCK_DGRAM, 0);

    return result;
}

void cross_socket_close(const CrossSocket* socket)
{
    close((int) socket->descriptor);
}

void cross_socket_bind(const CrossSocket* socket, int port)
{
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_address.sin_port = htons(port);

    int error_code = bind((int) socket->descriptor, (const struct sockaddr*) &server_address, sizeof(server_address));
}

int cross_socket_listen_tcp(const CrossSocket* socket, int connections_queue_length)
{
    return listen((int) socket->descriptor, connections_queue_length);;
}

int cross_socket_connect_tcp(const CrossSocket* socket, const IpAddress* ip_address, int port)
{
    struct sockaddr_in connection_address;

    connection_address.sin_family = AF_INET;
    connection_address.sin_addr.s_addr = inet_addr(ip_address->address.buffer);
    connection_address.sin_port = htons(port);

    return connect((int) socket->descriptor, (const struct sockaddr*) &connection_address, sizeof(connection_address));
}

CrossSocket cross_socket_accept_tcp(const CrossSocket* socket, IpAddress* ip_address)
{
    CrossSocket result;

    socklen_t address_len;
    struct sockaddr_in connection_address;

    result.descriptor = accept(socket->descriptor, (struct sockaddr*) &connection_address, &address_len);

    ip_address->address = string_new(inet_ntoa(connection_address.sin_addr));

    return result;
}

int cross_socket_receive_tcp(const CrossSocket* socket, const String* buffer)
{
    return recv((int) socket->descriptor, buffer->buffer, buffer->length, 0);
}

int cross_socket_receive_udp(const CrossSocket* socket, const String* buffer, IpAddress* ip_address, int* port)
{
    socklen_t address_length;
    struct sockaddr_in connection_address;

    ssize_t errcode = recvfrom((int) socket->descriptor, buffer->buffer, buffer->length, 0,
                               (struct sockaddr*) &connection_address,
                               &address_length);

    ip_address->address = string_new(inet_ntoa(connection_address.sin_addr));
    *port = ntohs(connection_address.sin_port);

    return (int) errcode;
}

void cross_socket_send_tcp(const CrossSocket* socket, const String* buffer)
{
    send((int) socket->descriptor, buffer->buffer, buffer->length, 0);
}

void cross_socket_send_udp(const CrossSocket* socket, const String* buffer, const IpAddress* ip_address, int port)
{
    struct sockaddr_in connection_address;

    connection_address.sin_family = AF_INET;
    connection_address.sin_addr.s_addr = inet_addr(ip_address->address.buffer);
    connection_address.sin_port = htons(port);

    sendto((int) socket->descriptor, buffer->buffer, buffer->length, 0, (struct sockaddr*) &connection_address,
           sizeof(connection_address));
}
