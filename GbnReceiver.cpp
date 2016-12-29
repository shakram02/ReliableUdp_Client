//
// Created by ahmed on 12/25/16.
//

// TODO create a base class for the GBN and Selective Repeat receivers
// TODO use the timers
#include "GbnReceiver.h"

GbnReceiver::GbnReceiver(unsigned int window_size, ClientSocket *sock, FileWriter *f_writer) :
        packets(window_size), client_sock{sock}, writer(f_writer)
{
    this->window_size = window_size;
}

void GbnReceiver::StartReceiving()
{
    bool is_receiving = true;
    while (is_receiving) {

        if (boost::this_thread::interruption_requested())return;

        void *buf;
        DataPacket *pck;

        int len = (int) client_sock->ReceiveRaw(&buf);

        if (len > 0) {

            BinarySerializer::DeserializeDataPacket(buf, &pck);
            this->packets.push(pck);
            cout << "-->RCV SEQNO [" << pck->seqno << "]" << endl;
        } else {
            cout << " Got nothing" << endl;
            is_receiving = false;
        }
    }
}

void GbnReceiver::StartAcking()
{
    while (!boost::this_thread::interruption_requested()) {

        // Wait for packets to be sent and print out
        boost::this_thread::sleep_for(boost::chrono::microseconds(200));

        if (this->packets.empty()) {
            continue;
        }

        // TODO check the sequence number of the incoming packet, then act upon it
        DataPacket *to_be_acked;
        if (this->packets.pop(to_be_acked)) {

            // The popped packet isn't the one I'm waiting for
            if (to_be_acked->seqno > (this->last_acked_seq_num + 1)) {
                cerr << "Bad seq num [" << to_be_acked->seqno << "]" << endl;
                continue; // Do nothing, the server will timeout on its own
            }

            cout << " ACK SEQNO [" << to_be_acked->seqno << "]" << endl;
            client_sock->SendAckPacket(to_be_acked->seqno);

            this->last_acked_seq_num++;

            if (to_be_acked->len == 0) {
                cout << "Transmission completed at packet [" << to_be_acked->seqno << "]" << endl;
                //free(to_be_acked);  // Don't leak the last packet
                //return;
            } else {
                //cout << " ACK SEQNO:" << to_be_acked->seqno << endl;
//                cout
//                        //<< "Data:" << to_be_acked->data
//                        << " #" << to_be_acked->seqno << endl;
                this->writer->Write(to_be_acked->data, to_be_acked->len);
            }
            free(to_be_acked);

        }
    }
}