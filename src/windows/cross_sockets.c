//
// Created by Yurii on 10/28/2023.
//

#include "cross_sockets.h"
#include <winsock2.h>


void cross_socket_initialize() {
    static WSADATA wsa_data;

    WSAStartup(MAKEWORD(2,2), &wsa_data);
}

uint64_t cross_socket_open_tcp() {
    uint64_t socket_descriptor;

    socket_descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    return socket_descriptor;
}

uint64_t cross_socket_open_udp() {
    uint64_t socket_descriptor;

    socket_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    return socket_descriptor;
}

void cross_socket_close(uint64_t descriptor) {
    closesocket(descriptor);
}

int32_t cross_socket_bind(uint64_t descriptor, uint16_t in_port) {
    SOCKADDR_IN server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(in_port);

    return bind(descriptor, (SOCKADDR*)&server, sizeof(server));
}

int32_t cross_socket_listen_tcp(uint64_t descriptor, uint16_t connections_queue_length) {
    return listen(descriptor, connections_queue_length);
}

int32_t cross_socket_connect_tcp(uint64_t descriptor, uint32_t in_address, uint16_t in_port) {
    SOCKADDR_IN address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(in_address);
    address.sin_port = htons(in_port);

    return connect(descriptor, (SOCKADDR*)&address, sizeof(address));
}

uint64_t cross_socket_accept_tcp(uint64_t descriptor, uint32_t* out_address, uint16_t* out_port) {
    SOCKADDR_IN client_address;
    int client_address_length = sizeof(client_address);

    uint64_t socket_descriptor;
    socket_descriptor = accept(descriptor, (SOCKADDR*)&client_address, &client_address_length);

    *out_address = ntohl(client_address.sin_addr.S_un.S_addr);

    return socket_descriptor;
}

int32_t cross_socket_receive_tcp(uint64_t descriptor, char* out_buffer, uint32_t in_buffer_length) {
    return recv(descriptor, out_buffer, (int)in_buffer_length, 0);
}

int32_t cross_socket_receive_udp(uint64_t descriptor, char* out_buffer, uint32_t in_buffer_length, uint32_t* out_address, uint16_t* out_port) {
    SOCKADDR_IN client_address;
    int client_address_length = sizeof(client_address);

    int result = recvfrom(descriptor, out_buffer, (int)in_buffer_length, 0, (SOCKADDR*)&client_address, &client_address_length);

    *out_address = ntohl(client_address.sin_addr.S_un.S_addr);
    *out_port = ntohs(client_address.sin_port);

    return result;
}

void cross_socket_send_tcp(uint64_t descriptor, const char* in_buffer, uint32_t in_buffer_length) {
    send(descriptor, in_buffer, (int)in_buffer_length, 0);
}

void cross_socket_send_udp(uint64_t descriptor, const char* in_buffer, uint32_t in_buffer_length, uint32_t in_address, uint16_t in_port) {
    SOCKADDR_IN address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(in_address);
    address.sin_port = htons(in_port);

    sendto(descriptor, in_buffer, (int)in_buffer_length, 0, (SOCKADDR*)&address, sizeof(address));
}

const char* get_error() {
    static char message_buffer[256];

    message_buffer[0] = '\0';

    int32_t error = WSAGetLastError();

    FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            message_buffer,
            sizeof(message_buffer),
            NULL);

    return message_buffer;
}

void cross_socket_cleanup() {
    WSACleanup();
}
