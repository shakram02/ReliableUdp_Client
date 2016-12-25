#include "ClientSocket.h"

#include "FileWriter.h"
#include "globaldefs.h"
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

/**
 * Event handler for socket packet receive events
 * @param msg Contains the socket message
 * @param ip Contains the server ip
 */
void woot(char *msg, long int size)
{
    //DataPacket *rec = reinterpret_cast<DataPacket *>(msg);
    //cout << "WOOT: \"" << rec->len << "\"" << endl;
    //cout << "Found:" << rec->data << endl;
    cout << "Message:\"" << msg << "\"" << endl;
}

#define FILE_IDX 2

int main()
{
    ClientSocket sock(string(SERVER_IP_ADDR), PORT_NUM);
    string handshake_msg("hndshk");
    sock.HandshakeServer(handshake_msg);

    string files[3] = {
            string("zooz.txt"),
            string("pixi.ico"),
            string("zwp.jpg")
    };

    string file_name = files[FILE_IDX];

    basic_string<char> file_request("FILE-");
    file_request.append(file_name);

    FileWriter writer((char *) file_name.c_str());
    sock.SendPacket((void *) file_request.c_str(), (unsigned int) file_request.size());

    void *file_header;
    sock.ReceiveRaw(&file_header);

    // Trim the last element as it's garbage because a string is being received
    string file_header_packet((char *) file_header);

#if LOG >= 2
    cout << "Received:" << file_header_packet << endl;
#endif

    int pos = (int) file_header_packet.find(SERV_FILESZ_HEADER);

    if (pos != 0) {
#if LOG >= 1
        cerr << "Malformed file header" << endl;
#endif
        return -1;
    }

    // TODO wrong packet count and content ?
    file_header_packet = file_header_packet.substr(strlen(SERV_FILESZ_HEADER), file_header_packet.size() - 1);
    char *packet_count_str = (char *) file_header_packet.c_str();
    int packet_count = stoi(packet_count_str, nullptr, 0);

#if LOG >= 2
    cout << "Expected packet count:" << packet_count_str << endl;
    cout << "Working..." << endl;
#endif


    for (int j = 0; j < packet_count; ++j) {

//        void *packet_content;
//        packet_size = sock.ReceiveRaw(&packet_content);
//
//        DataPacket *pck;
//        BinarySerializer::DeserializeDataPacket(packet_content, 0, &pck);
//
//#if LOG >= 3
//        cout << "Packet #" << pck->seqno
//             << ", Packet size " << packet_size << " Bytes"
//             << ", Packet content " << pck->data
//             << endl;
//#endif
//        // TODO take a notice, the last packet is padded with zeros
//        // This should be removed before writing the data
//        // TODO checksum the data
//        writer.Write(pck->data, pck->len);
//
//        free(packet_content);

        DataPacket pck;
        sock.ReceiveDataPacket(&pck);
        writer.Write(pck.data, pck.len);


        cout << "Packet #" << pck.seqno
             << ", Packet size " << pck.len << " Bytes"
             << endl;


        AckPacket ack(pck.seqno);
        void *raw_ptr;
        BinarySerializer::SerializeAckPacket(&ack, &raw_ptr);

        sock.SendPacket(raw_ptr, sizeof(AckPacket));
    }


//    long packet_size = 1;
//    while (packet_size) {
//
//        void *packet_content;
//        packet_size = sock.ReceiveRaw(&packet_content);
//
//        DataPacket *pck;
//        BinarySerializer::DeserializeDataPacket(packet_content, 0, &pck);
//
//        writer.Write(pck->data, pck->len);
//
//        AckPacket ack(pck->seqno);
//        void *raw_ptr;
//        BinarySerializer::SerializeAckPacket(&ack, &raw_ptr);
//
//        sock.SendPacket(raw_ptr, sizeof(AckPacket));
//    }

    writer.~FileWriter();
    return 0;
}