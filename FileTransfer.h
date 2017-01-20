//
// Created by ahmed on 1/12/17.
//

#ifndef ENHANCEDUDPCLIENT_FILEREQUEST_H
#define ENHANCEDUDPCLIENT_FILEREQUEST_H

#include <string>
#include<memory>
#include <AddressInfo.h>
#include <RawUdpSocket.h>
#include "AbstractReceiver.h"

using std::string;
using std::unique_ptr;

class FileTransfer
{
public:
    FileTransfer(string server_ip, unsigned short request_port_number, string file_name,
            AbstractReceiver *receiver);

    int GetPacketCount();

    void StartReceive();

    void StopReceive();

    unique_ptr<AddressInfo> end_point;
    unique_ptr<RawUdpSocket> request_socket;
    unique_ptr<AbstractReceiver> receiver;
private:
    string file_name;
};


#endif //ENHANCEDUDPCLIENT_FILEREQUEST_H
