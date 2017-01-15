//
// Created by ahmed on 1/13/17.
//

#ifndef ENHANCEDUDPCLIENT_ABSTRACTRECEIVER_H
#define ENHANCEDUDPCLIENT_ABSTRACTRECEIVER_H


#include <RawUdpSocket.h>
#include <atomic>
#include "FileWriter.h"

class AbstractReceiver
{
protected:
    unique_ptr<RawUdpSocket> file_transfer_socket;
    unique_ptr<FileWriter> writer;

    std::atomic<bool> is_receiving;
    int last_acked_seq_num = -1;
    AddressInfo endpoint;


    AbstractReceiver(string file_name)
    { this->writer = unique_ptr<FileWriter>(new FileWriter(file_name)); }

public:

    virtual ~AbstractReceiver()
    {};

    virtual void StartReceiving(unique_ptr<RawUdpSocket> &rcv_socket, AddressInfo endpoint)=0;

    virtual void StopReceiving()=0;
};


#endif //ENHANCEDUDPCLIENT_ABSTRACTRECEIVER_H
