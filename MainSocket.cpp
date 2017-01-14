//
// Created by ahmed on 12/16/16.
//


#include <cstring>
#include "MainSocket.h"
#include "client_config.h"

MainSocket::MainSocket(const string &server_addr, const unsigned short server_port)
{
    server_info = unique_ptr<AddressInfo>(new AddressInfo(server_addr, server_port));
    this->server_addr = string(server_addr);

    this->socket = unique_ptr<RawUdpSocket>(new RawUdpSocket(*this->server_info));
    this->socket->SetReceiveTimeout(RCV_TIMEO_SEC, RCV_TIMEO_USEC);
    this->socket->SetSendTimeout(RCV_TIMEO_SEC, RCV_TIMEO_USEC);
}

int MainSocket::InitFileRequest(string &handshake)
{
    this->socket->SendString(*this->server_info, handshake);

    string temp = this->socket->ReceiveString();

    temp.replace(0, strlen(WELCOME_HEADER), "");
    cout << "Redirect port:" << temp << endl;

    return (stoi(temp));
}

MainSocket::~MainSocket()
{
    this->socket->~RawUdpSocket();
}