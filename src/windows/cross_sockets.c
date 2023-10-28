//
// Created by Yurii on 10/28/2023.
//

#include "cross_sockets.h"
#include <winsock2.h>



WSADATA wsa_data;

void cross_socket_initialize() {
    WSAStartup(MAKEWORD(2,2), &wsa_data);
}

CrossSocket cross_socket_open_tcp() {
    CrossSocket tcp_socket;

    tcp_socket.descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    return tcp_socket;
}

CrossSocket cross_socket_open_udp() {
    CrossSocket udp_socket;

    udp_socket.descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    return udp_socket;
}

void cross_socket_close(const CrossSocket* socket) {
    closesocket(socket->descriptor);
}

void cross_socket_bind(const CrossSocket* socket, int port) {
    SOCKADDR_IN server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    bind(socket->descriptor, (SOCKADDR*)&server, sizeof(server));
}

int cross_socket_listen_tcp(const CrossSocket* socket, int connections_queue_length) {
    return listen(socket->descriptor, connections_queue_length);
}

int cross_socket_connect_tcp(const CrossSocket* socket, const IpAddress* ip_address, int port) {
    SOCKADDR_IN address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address->address.buffer);
    address.sin_port = htons(port);

    return connect(socket->descriptor, (SOCKADDR*)&address, sizeof(address));
}

CrossSocket cross_socket_accept_tcp(const CrossSocket* socket, IpAddress* ip_address) {
    SOCKADDR_IN client_address;
    int client_address_length = sizeof(client_address);

    CrossSocket client_socket;
    client_socket.descriptor = accept(socket->descriptor, (SOCKADDR*)&client_address, &client_address_length);

    ip_address->address = string_new(inet_ntoa(client_address.sin_addr));

    return client_socket;
}

int cross_socket_receive_tcp(const CrossSocket* socket, const String* buffer) {
    return recv(socket->descriptor, buffer->buffer, (int)buffer->length, 0);
}

int cross_socket_receive_udp(const CrossSocket* socket, const String* buffer, IpAddress* ip_address, int* port) {
    SOCKADDR_IN client_address;
    int client_address_length = sizeof(client_address);

    int result = recvfrom(socket->descriptor, buffer->buffer, (int)sizeof(buffer->length), 0, (SOCKADDR*)&client_address, &client_address_length);

    ip_address->address = string_new(inet_ntoa(client_address.sin_addr));
    *port = ntohs(client_address.sin_port);

    return result;
}

void cross_socket_send_tcp(const CrossSocket* socket, const String* buffer) {
    send(socket->descriptor, buffer->buffer, (int)buffer->length, 0);
}

void cross_socket_send_udp(const CrossSocket* socket, const String* buffer, const IpAddress* ip_address, int port) {
    SOCKADDR_IN address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address->address.buffer);
    address.sin_port = port;

    sendto(socket->descriptor, buffer->buffer, (int)buffer->length, 0, (SOCKADDR*)&address, sizeof(address));
}

void cross_socket_cleanup() {
    WSACleanup();
}
