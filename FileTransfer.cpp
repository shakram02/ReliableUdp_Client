//
// Created by Ahmed on 1/12/17.
//

#include <iostream>
#include <cstring>
#include <thread>
#include "FileTransfer.h"
#include "client_config.h"
#include "GbnReceiver.h"

FileTransfer::FileTransfer(string server_ip,
        unsigned short request_port_number,
        string file_name,
        AbstractReceiver *receiver)
        : file_name(file_name)
{
    this->receiver = unique_ptr<AbstractReceiver>(receiver);
    // TODO the open socket should send to the server on the given port
    this->request_end_point = unique_ptr<AddressInfo>(new AddressInfo(server_ip, request_port_number));

    // Create a socket for this file transfer
    string client_ip(LOOP_BCK_IP);
    this->request_socket = unique_ptr<RawUdpSocket>(new RawUdpSocket(client_ip));

    // Confirm redirection, set the timeout for redirection assertion
    // from the server as a relatively large value
    string redirect_ok(REDIRECT_SUCCESS);
    this->request_socket->SendString(*(this->request_end_point), redirect_ok);
    this->request_socket->SetReceiveTimeout(INITIAL_RCV_TIMEO_SEC, INITIAL_RCV_TIMEO_USEC);

    // After getting the confirmation, decrease the timeout as the file transfer will start
    string temp = this->request_socket->ReceiveString();
    this->request_socket->SetReceiveTimeout(RCV_TIMEO_SEC, RCV_TIMEO_USEC);

    if (temp != string(REDIRECT_OK)) {
        throw std::runtime_error("Bad confirmation received:");
    }
}

int FileTransfer::GetFileChunkCount()
{
    string file_request(FILE_REQUEST_HEADER);
    file_request.append(file_name);

    this->request_socket->SendString(*this->request_end_point, file_request);
    AddressInfo inf;
    string file_header_packet = this->request_socket->ReceiveString(inf);

    int pos = (int) file_header_packet.find(SERV_FILESZ_HEADER);

    if (pos != 0) {
        throw std::runtime_error("Couldn't get file info");
    }

    // TODO wrong packet count and content ?
    file_header_packet = file_header_packet.substr(strlen(SERV_FILESZ_HEADER), file_header_packet.size() - 1);
    return std::stoi(file_header_packet.c_str(), nullptr, 0);
}

void FileTransfer::StartReceive()
{
    this->receiver->StartReceiving(this->request_socket, *this->request_end_point);
}

void FileTransfer::StopReceive()
{
    this->receiver->StopReceiving();
}
