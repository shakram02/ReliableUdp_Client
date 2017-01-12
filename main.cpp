#include "ClientSocket.h"

#include "FileWriter.h"
#include "globaldefs.h"
#include "GbnReceiver.h"
#include "FileTransfer.h"
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
    string sync_msg("hndshk");

    // This method will return a redirect port which
    // will be used to create the file request object
    int redirect_port = sock.InitFileRequest(sync_msg);

    if (redirect_port < 0)exit(-1);

    string files[3] = {
            string("zooz.txt"),
            string("txrxPc.png"),
            string("Pro Git.pdf"),
    };

    string file_name = files[FILE_IDX];
    cout << "Requesting file" << endl;
    AddressInfo server_info(string(SERVER_IP_ADDR), (unsigned short) redirect_port);
    FileTransfer transfer(string(SERVER_IP_ADDR), (unsigned short) redirect_port, file_name);
    int packet_count = transfer.GetFileChunkCount();

    unique_ptr<FileWriter> writer = unique_ptr<FileWriter>(new FileWriter(file_name));

    GbnReceiver receiver(5, transfer.request_socket.get(), writer);
    boost::thread rcv_th(boost::bind(&GbnReceiver::StartReceiving, boost::ref(receiver)));
    boost::thread ack_th(boost::bind(&GbnReceiver::StartAcking, boost::ref(receiver), server_info));

    ack_th.join();
    rcv_th.interrupt();
    //rcv_th.join();    // TODO Set the receive timeout of the file transfer socket

    cout << "Thread tasks complete..." << endl;


//    string files[3] = {
//            string("zooz.txt"),
//            string("txrxPc.png"),
//            string("Pro Git.pdf"),
//    };
//
//    string file_name = files[FILE_IDX];
//
//    int packet_count = 0;
//    sock.RequestFile(file_name, packet_count);
//
//    if (packet_count == -1) {
//        cerr << "Malformed file header" << endl;
//    }
//
//    cout << "Expected packet count:" << packet_count << endl;
//    cout << "Working..." << endl;
//
//    FileWriter *writer=new FileWriter(file_name);
//
//    GbnReceiver receiver(server_info, &sock, &writer);
//    boost::thread rcv_th(boost::bind(&GbnReceiver::StartReceiving, boost::ref(receiver)));
//    boost::thread ack_th(boost::bind(&GbnReceiver::StartAcking, boost::ref(receiver), packet_count));
//
//    rcv_th.join();
//    ack_th.join();
//
//    cout << "Thread tasks complete..." << endl;

    return 0;
}