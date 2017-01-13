//
// Created by Ahmed on 1/12/17.
//

#include <iostream>
#include <cstring>
#include "FileTransfer.h"
#include "client_config.h"

using std::cout;
using std::endl;

FileTransfer::FileTransfer(string server_ip, unsigned short request_port_number, string file_name)
        : file_name(file_name)
{
    this->request_server_info = unique_ptr<AddressInfo>(new AddressInfo(server_ip, request_port_number));
    this->request_socket = unique_ptr<RawUdpSocket>(new RawUdpSocket(*this->request_server_info));

    string redirect_ok(REDIRECT_SUCCESS);
    this->request_socket->SendString(*this->request_server_info, redirect_ok);

    this->request_socket->SetReceiveTimeout(RCV_TIMEO_SEC, RCV_TIMEO_USEC);

    try {
        AssertRedirectionOk();
    } catch (std::runtime_error &err) {
        // TODO fail
    }
}

void FileTransfer::AssertRedirectionOk()
{
    string temp = this->request_socket->ReceiveString();

    if (temp != string(REDIRECT_OK)) {
        throw std::runtime_error("Bad confirmation received:");
    }
}

int FileTransfer::GetFileChunkCount()
{

    string file_request(FILE_REQUEST_HEADER);
    file_request.append(file_name);

    this->request_socket->SendString(*this->request_server_info, file_request);
    string file_header_packet = this->request_socket->ReceiveString();

    cout << "REPLY:" << file_header_packet << endl;

    // Trim the last element as it's garbage because a string is being received
    int pos = (int) file_header_packet.find(SERV_FILESZ_HEADER);

    if (pos != 0) {
        return -1;  // Signal fail
    }

    // TODO wrong packet count and content ?
    file_header_packet = file_header_packet.substr(strlen(SERV_FILESZ_HEADER), file_header_packet.size() - 1);
    return std::stoi(file_header_packet.c_str(), nullptr, 0);
}
