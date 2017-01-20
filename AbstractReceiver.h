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
    /**
     // TODO Refactor the FileWriter into its own layer of the application
     */
protected:
    unique_ptr<RawUdpSocket> file_transfer_socket;


    std::atomic<bool> is_receiving;
    int last_acked_seq_num = -1;
    AddressInfo server;
    int last_acked_pkt_id = -1;
    int lost_winds = 0;

public:

    virtual ~AbstractReceiver()
    {};

    virtual void StartReceiving(unique_ptr<RawUdpSocket> &rcv_socket, AddressInfo endpoint)=0;

    virtual void StopReceiving()=0;

    // <packet list queue> ReceiveWindow();
    // AckPacket();

    //FileTransferState GetCurrentState();
};


#endif //ENHANCEDUDPCLIENT_ABSTRACTRECEIVER_H
