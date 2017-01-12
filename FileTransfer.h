//
// Created by ahmed on 1/12/17.
//

#ifndef ENHANCEDUDPCLIENT_FILEREQUEST_H
#define ENHANCEDUDPCLIENT_FILEREQUEST_H

#include <string>
#include<memory>
#include <AddressInfo.h>
#include <RawUdpSocket.h>

using std::string;
using std::unique_ptr;

class FileTransfer
{
public:
    FileTransfer(string server_ip, unsigned short request_port_number, string file_name);

    int GetFileChunkCount();

    unique_ptr<AddressInfo> request_server_info;
    unique_ptr<RawUdpSocket> request_socket;
private:
string file_name;

    void AssertRedirectionOk();
};


#endif //ENHANCEDUDPCLIENT_FILEREQUEST_H
