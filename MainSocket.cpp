//
// Created by ahmed on 12/16/16.
//


#include <cstring>
#include "MainSocket.h"
#include "client_config.h"
#include <ProtocolMsgId.h>

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
    this->socket->SendStringPacket(*this->server_info, handshake, ID_HAND_SHAKE);

    string temp;
    int seqno = this->socket->ReceiveStringPacket(temp);

    if (seqno != ID_GO_REDIRECT) {
        string err("Bad protocol message ");
        err.append(to_string(seqno));
        throw std::runtime_error(err);
    }

    temp.replace(0, strlen(WELCOME_HEADER), "");
    cout << "Redirect port:" << temp << endl;

    return (stoi(temp));
}

MainSocket::~MainSocket()
{
    this->socket->~RawUdpSocket();
}