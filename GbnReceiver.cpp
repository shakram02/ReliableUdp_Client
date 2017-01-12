//
// Created by ahmed on 12/25/16.
//

// TODO create a base class for the GBN and Selective Repeat receivers
// TODO use the timers
#include "GbnReceiver.h"

//GbnReceiver::GbnReceiver(unsigned int window_size, ClientSocket *sock, FileWriter *f_writer) :
//        packets(window_size), client_sock{sock}, writer(f_writer)
//{
//    this->window_size = window_size;
//}

GbnReceiver::GbnReceiver(unsigned int window_size, RawUdpSocket *sock, unique_ptr<FileWriter> &f_writer) :
        packets(window_size), client_sock{sock}, writer(std::move(f_writer))
{
    this->window_size = window_size;
}

void GbnReceiver::StartReceiving()
{
    int max_fails_of_packet = 9;
    int fails_of_packet = 0;
    while (this->is_receiving && !boost::this_thread::interruption_requested()) {

        try {
            unique_ptr<Packet> unq_pckt = client_sock->ReceivePacket();

            // Reset fail count on valid packet
            fails_of_packet = 0;
            cout << "<-- | RCV [" << unq_pckt->header->seqno << "]" << endl;
            this->packets.push(unq_pckt.release());
        }
        catch (std::runtime_error &excption) {
            if (this->is_receiving) {
                cerr << "-*- | Timeout" << endl;
            }
            //free(pck);  // Kill memory leaks


        }
        // TODO terminate of many fails
        if (fails_of_packet++ == max_fails_of_packet) {
            this->is_receiving = false;
            return;
        }
//        unique_ptr<Packet> unq_pckt;
//        int len = (int) client_sock->ReceivePacket(unq_pckt);
//
//
//        if (len > 0) {
//
//            // Reset fail count on valid packet
//            fails_of_packet = 0;
//            cout << "<-- | RCV [" << unq_pckt->header->seqno << "]" << endl;
//            this->packets.push(unq_pckt.release());
//        } else {
//
//            if (this->is_receiving) {
//                cerr << "-*- | Timeout" << endl;
//            }
//            //free(pck);  // Kill memory leaks
//
//            // TODO terminate of many fails
//            if (fails_of_packet++ == max_fails_of_packet) {
//                this->is_receiving = false;
//                return;
//            }
//        }
    }
}

void GbnReceiver::StartAcking(AddressInfo &server_info)
{

    while (this->is_receiving && !boost::this_thread::interruption_requested()) {

        // Wait for packets to be sent and print out


        if (this->packets.empty()) {
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
            continue;
        }

        Packet *temp;
        if (!this->packets.pop(temp)) continue;  // queue is empty

        unique_ptr<Packet> to_be_acked(temp);   // Put the packet in a container

        // The popped packet isn't the one I'm waiting for
        if (to_be_acked->header->seqno != (this->last_acked_seq_num + 1)) {
            cerr << "#-- | Bad SEQ [" << to_be_acked->header->seqno << "]" << endl;
            continue; // Do nothing, the server will timeout on its own
        }

        cout << "--> | ACK [" << to_be_acked->header->seqno << "]" << endl;
        unique_ptr<ByteVector> data = nullptr;
        unique_ptr<Packet> ack(new Packet(data, to_be_acked->header->seqno));
        client_sock->SendPacket(server_info, ack);

        this->last_acked_seq_num++;

        if (to_be_acked->header->dataLen == 0) {
            cout << "Transmission completed at packet [" << to_be_acked->header->seqno << "]" << endl;
            this->is_receiving = false;

            return;
        } else {
            unique_ptr<ByteVector> data;
            if (to_be_acked->GetData(data)) {
                //cout << "Data recv.:" << data->data() << endl;
                this->writer->Write(*data);
            } else {
                cout << "ACK receive" << endl;
            };
        }

//        Packet *temp;
//        if (!this->packets.pop(temp)) continue;  // queue is empty
//
//        unique_ptr<Packet> to_be_acked(temp);   // Put the packet in a container
//
//        // The popped packet isn't the one I'm waiting for
//        if (to_be_acked->header->seqno != (this->last_acked_seq_num + 1)) {
//            cerr << "#-- | Bad SEQ [" << to_be_acked->header->seqno << "]" << endl;
//            continue; // Do nothing, the server will timeout on its own
//        }
//
//        cout << "--> | ACK [" << to_be_acked->header->seqno << "]" << endl;
//        client_sock->SendAckPacket(to_be_acked->header->seqno);
//
//        this->last_acked_seq_num++;
//
//        if (to_be_acked->header->dataLen == 0) {
//            cout << "Transmission completed at packet [" << to_be_acked->header->seqno << "]" << endl;
//            this->is_receiving = false;
//
//            return;
//        } else {
//            unique_ptr<ByteVector> data;
//            if (to_be_acked->GetData(data)) {
//                //cout << "Data recv.:" << data->data() << endl;
//                this->writer->Write(*data);
//            } else {
//                cout << "ACK receive" << endl;
//            };
//        }
    }

}