//
// Created by ahmed on 12/25/16.
//


#include "GbnReceiver.h"

GbnReceiver::GbnReceiver(unsigned int window_size, ClientSocket *sock)
{
    this->client_sock = sock;
    this->window_size = window_size;
}

bool GbnReceiver::AckWindow()
{
    return false;
}

void GbnReceiver::ReceiveThread()
{
    for (int i = 0; i < 5; ++i) {

        if (boost::this_thread::interruption_requested())return;

        DataPacket pck;
        int len = (int) client_sock->ReceiveDataPacket(&pck);
        if (len > 0) {
//            BinarySerializer::DeserializeDataPacket(buf, len, &projected);
            cout << " Got:" << pck.data << endl;
        } else {
            // Nothing received
            cout << " Got nothing" << endl;

        }
//        free(buf);

    }

}