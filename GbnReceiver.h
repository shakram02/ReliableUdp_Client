//
// Created by ahmed on 12/25/16.
//

#ifndef ENHANCEDUDPCLIENT_GBNRECEIVER_H
#define ENHANCEDUDPCLIENT_GBNRECEIVER_H


#include <queue>
#include "ClientSocket.h"
#include "globaldefs.h"
#include "FileWriter.h"
#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>

class GbnReceiver
{
    // TODO convert ClientSocket and FileWriter to unique pointers
    // the underlying objects must be allocated on the heap
    // not the stack (as what's currently happening)

    //ClientSocket*client_sock;
    //FileWriter*writer;
    RawUdpSocket *client_sock;
    unique_ptr<FileWriter> writer;
    bool is_receiving = true;
    int last_acked_seq_num = -1;
    unsigned int window_size;

    // A pointer must be used, as the lockfree queue needs
    // types with simple destructor and copy constructor
    // which aren't valid for the unique pointer
    boost::lockfree::queue<Packet *> packets;

public:
    //GbnReceiver(unsigned int window_size, ClientSocket *sock, FileWriter *writer);

    GbnReceiver(unsigned int window_size, RawUdpSocket *sock, unique_ptr<FileWriter> &writer);

    void StartReceiving();

    void StartAcking(AddressInfo &server_info);
};


#endif //ENHANCEDUDPCLIENT_GBNRECEIVER_H
