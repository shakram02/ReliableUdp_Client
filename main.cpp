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

#define FILE_IDX 1

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

    int packet_count = 0;
    sock.RequestFile(file_name, packet_count);

    if (packet_count == -1) {
        cerr << "Malformed file header" << endl;
    }

    cout << "Expected packet count:" << packet_count << endl;
    cout << "Working..." << endl;

    FileWriter writer(file_name);

    GbnReceiver receiver(5, &sock, &writer);
    boost::thread rcv_th(boost::bind(&GbnReceiver::StartReceiving, boost::ref(receiver)));
    boost::thread ack_th(boost::bind(&GbnReceiver::StartAcking, boost::ref(receiver), packet_count));

    rcv_th.join();
    ack_th.join();

    cout << "Thread tasks complete..." << endl;

    return 0;
}