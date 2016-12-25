//
// Created by ahmed on 12/25/16.
//

#include "GbnReceiver.h"

GbnReceiver::GbnReceiver(unsigned int window_size, ClientSocket sock) : client_sock(sock)
{
    this->window_size = window_size;
}

bool GbnReceiver::AckWindow()
{
    return false;
}

void GbnReceiver::ReceiveThread()
{

    void *buf;
    if (client_sock.ReceiveRaw(&buf) > 0) {
        // Received something

    } else {
        // Nothing received
    }

    free(buf);
}
