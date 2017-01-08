#include "ClientSocket.h"

#include "FileWriter.h"
#include "globaldefs.h"
#include "GbnReceiver.h"
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

// TODO use smart pointers everywhere

/**
 * Event handler for socket packet receive events
 * @param msg Contains the socket message
 * @param ip Contains the server ip
 */

#define FILE_IDX 0

int main()
{
    ClientSocket sock(string(SERVER_IP_ADDR), PORT_NUM);
    string handshake_msg("hndshk");
    sock.HandshakeServer(handshake_msg);

    string files[3] = {
            string("zooz.txt"),
            string("txrxPc.png"),
            string("Pro Git.pdf"),
    };

    string file_name = files[FILE_IDX];

    basic_string<char> file_request("FILE-");
    file_request.append(file_name);

    FileWriter writer((char *) file_name.c_str());
    sock.SendPacket((byte *) file_request.c_str(), (unsigned int) file_request.size());

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
    boost::thread rcv_th(boost::bind(&GbnReceiver::StartReceiving, boost::ref(receiver)));
    boost::thread ack_th(boost::bind(&GbnReceiver::StartAcking, boost::ref(receiver), packet_count));

    rcv_th.join();
    ack_th.join();
    cout << "Thread tasks complete..." << endl;

    return 0;
}