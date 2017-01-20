//
// Created by Ahmed on 1/12/17.
//

#include <iostream>
#include <cstring>
#include <thread>
#include "FileTransfer.h"
#include "client_config.h"
#include "GbnReceiver.h"
#include <ProtocolDef.h>

FileTransfer::FileTransfer(string server_ip,
        unsigned short request_port_number,
        string file_name,
        AbstractReceiver *receiver)
        : file_name(file_name)
{
    this->receiver = unique_ptr<AbstractReceiver>(receiver);
    // the open socket should send to the server on the given port
    this->end_point = unique_ptr<AddressInfo>(new AddressInfo(server_ip, request_port_number));

    // Create a socket for this file transfer
    string client_ip(LOOP_BCK_IP);
    this->request_socket = unique_ptr<RawUdpSocket>(new RawUdpSocket(client_ip));

    // Confirm redirection, set the timeout for redirection assertion
    // from the server as a relatively large value
    string redirect_ok(REDIRECT_SUCC_CLNT);

    this->request_socket->SendStringPacket(*(this->end_point), redirect_ok, ID_REDIRECT_SUCC_CLNT);
    this->request_socket->SetReceiveTimeout(INITIAL_RCV_TIMEO_SEC, INITIAL_RCV_TIMEO_USEC);

    string temp;
    if (this->request_socket->ReceiveStringPacket(temp) != ID_REDIRECT_OK_SRV) {
        // TODO fail
        throw std::runtime_error("Bad confirmation received:");
    }
    // After getting the confirmation, decrease the timeout as the file transfer will start
    this->request_socket->SetReceiveTimeout(RCV_TIMEO_SEC, RCV_TIMEO_USEC);
}

int FileTransfer::GetPacketCount()
{
    string file_request(FILE_NAME_CLNT);
    file_request.append(file_name);

    this->request_socket->SendStringPacket(*this->end_point, file_request, ID_FILE_NAME_CLNT);

    string file_header_packet;
    if (this->request_socket->ReceiveStringPacket(file_header_packet) != ID_FILE_SZ_SRV) {
        // TODO bad file count packet
        string err("Bad protocol message,expected: ");
        err.append(to_string(ID_FILE_SZ_SRV));
        throw std::runtime_error(err);
    }

    int pos = (int) file_header_packet.find(FILE_SZ_SRV);

    if (pos != 0) {
        throw std::runtime_error("Couldn't get file info");
    }

    file_header_packet = file_header_packet.substr(strlen(FILE_SZ_SRV), file_header_packet.size() - 1);
    int packet_count = std::stoi(file_header_packet.c_str(), nullptr, 0);

    if (packet_count == 0) {
        // TODO File not found
    }

    return packet_count;
}

void FileTransfer::StartReceive()
{
    this->receiver->StartReceiving(this->request_socket, *this->end_point);
}

void FileTransfer::StopReceive()
{
    this->receiver->StopReceiving();
}
