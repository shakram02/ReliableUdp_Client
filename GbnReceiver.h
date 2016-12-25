//
// Created by ahmed on 12/25/16.
//

#ifndef ENHANCEDUDPCLIENT_GBNRECEIVER_H
#define ENHANCEDUDPCLIENT_GBNRECEIVER_H


#include <queue>
#include "ClientSocket.h"
#include "globaldefs.h"
#include <boost/thread/thread.hpp>

typedef void *BinaryContainer;
typedef void **BinaryContainerArray;

class GbnReceiver
{
    ClientSocket *client_sock;
    int last_acked_seq_num = -1;
    unsigned int window_size;


    bool AckWindow();


    std::queue<DataPacket> received_queue;

public:
    GbnReceiver(unsigned int window_size, ClientSocket *sock);

    void ReceiveThread();
};


#endif //ENHANCEDUDPCLIENT_GBNRECEIVER_H
