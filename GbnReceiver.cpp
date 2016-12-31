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
    int max_fails_of_packet = 9;
    int fails_of_packet = 0;
    while (this->is_receiving && !boost::this_thread::interruption_requested()) {

        DataPacket *pck = (DataPacket *) calloc(1, sizeof(DataPacket));

        int len = (int) client_sock->ReceiveDataPacket(pck);

        if (len > 0) {

            // Reset fail count on valid packet
            fails_of_packet = 0;
            this->packets.push(pck);
            cout << "<-- | RCV [" << pck->seqno << "]" << endl;
        } else {

            if (this->is_receiving) {
                cerr << "-*- | Timeout" << endl;
            }
            free(pck);  // Kill memory leaks

            // TODO terminate of many fails
            if (fails_of_packet++ == max_fails_of_packet) {
                this->is_receiving = false;
                return;
            }
        }
    }
}

void GbnReceiver::StartAcking(int frag_count)
{

    while (!boost::this_thread::interruption_requested()) {

        // Wait for packets to be sent and print out


        if (this->packets.empty()) {
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
            continue;
        }

        DataPacket *to_be_acked;
        if (this->packets.pop(to_be_acked)) {

            // The popped packet isn't the one I'm waiting for
            if (to_be_acked->seqno != (this->last_acked_seq_num + 1)) {
                cerr << "#-- | Bad SEQ [" << to_be_acked->seqno << "]" << endl;

                free(to_be_acked);  // Don't leak the last packet
                continue; // Do nothing, the server will timeout on its own
            }

            cout << "--> | ACK [" << to_be_acked->seqno << "]" << endl;
            client_sock->SendAckPacket(to_be_acked->seqno);

            this->last_acked_seq_num++;

            if (to_be_acked->len == 0) {
                cout << "Transmission completed at packet [" << to_be_acked->seqno << "]" << endl;
                this->is_receiving = false;
                free(to_be_acked);  // Don't leak the last packet
                return;
            } else {
                this->writer->Write(to_be_acked->data, to_be_acked->len);
            }
            free(to_be_acked);
        }
    }
}