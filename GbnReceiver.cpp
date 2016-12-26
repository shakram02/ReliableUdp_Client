//
// Created by ahmed on 12/25/16.
//


#include "GbnReceiver.h"

GbnReceiver::GbnReceiver(unsigned int window_size, ClientSocket *sock, FileWriter *f_writer) :
        packets(window_size), client_sock{sock}, writer(f_writer)
{
    this->window_size = window_size;
}

bool GbnReceiver::AckWindow()
{
    return false;
}

void GbnReceiver::ReceiveThread()
{
    bool is_receiving = true;
    while (is_receiving) {

        if (boost::this_thread::interruption_requested())return;

        unique_ptr<DataPacket> pck{new DataPacket()};
        int len = (int) client_sock->ReceiveDataPacket(pck.get());

        if (len > 0) {

            this->packets.push(*pck);
            this->client_sock->SendAckPacket(pck->seqno);
            this->writer->Write(pck->data, pck->len);

            cout << " ACK:" << pck->seqno << endl;
        } else {
            // Nothing received
            cout << " Got nothing" << endl;
            is_receiving = false;
        }
    }
}

void GbnReceiver::AckThread()
{
    while (!boost::this_thread::interruption_requested()) {

        if (this->packets.empty()) {
            // go to bed for a while
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
        }

        DataPacket to_be_acked;
        if (this->packets.pop(to_be_acked)) {
            client_sock->SendAckPacket(to_be_acked.seqno);
        }

    }
}