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
    AddressInfo server_info;

public:

    AbstractReceiver(const AddressInfo &server_info, unique_ptr<FileWriter> &writer,
            unique_ptr<RawUdpSocket> &file_trans_socket) :

            server_info(server_info),
            writer(std::move(writer)),
            file_transfer_socket(std::move(file_trans_socket))
    {}

    virtual ~AbstractReceiver()
    {};

    virtual void StartReceiving()=0;

    virtual void StopReceiving()=0;
};


#endif //ENHANCEDUDPCLIENT_ABSTRACTRECEIVER_H
