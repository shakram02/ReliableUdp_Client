#include "ClientSocket.h"

#include "FileWriter.h"
#include "globaldefs.h"
#include "GbnReceiver.h"
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

#define FILE_IDX 1

int main()
{
    ClientSocket sock(string(SERVER_IP_ADDR), PORT_NUM);
    string handshake_msg("hndshk");
    sock.HandshakeServer(handshake_msg);

    string files[4] = {
            string("zmini.txt"),
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

    GbnReceiver receiver(5, &sock, &writer);
    boost::thread rcv_th(boost::bind(&GbnReceiver::ReceiveThread, boost::ref(receiver)));
    boost::thread ack_th(boost::bind(&GbnReceiver::AckThread, boost::ref(receiver)));

    boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
    rcv_th.interrupt();
    ack_th.interrupt();
    //cout << "Thread is deaad";
//    for (int j = 0; j < packet_count; ++j) {
//
//        DataPacket pck;
//        sock.ReceiveDataPacket(&pck);
//        writer.Write(pck.data, pck.len);
//
//
//        cout << "Packet #" << pck.seqno
//             << ", Packet size " << pck.len << " Bytes"
//             << endl;
//
//
//        AckPacket ack(pck.seqno);
//        void *raw_ptr;
//        BinarySerializer::SerializeAckPacket(&ack, &raw_ptr);
//
//        sock.SendPacket(raw_ptr, sizeof(AckPacket));
//    }
//
//    writer.~FileWriter();
    return 0;
}