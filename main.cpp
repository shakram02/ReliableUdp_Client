#include "MainSocket.h"

#include "FileWriter.h"
#include "client_config.h"
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

void no()
{
    cout << "NOOOO" << endl;
}

int main()
{
    MainSocket sock(string(SERVER_IP_ADDR), PORT_NUM);
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

    GbnReceiver receiver(5, transfer.request_socket, writer, server_info);

    receiver.StartReceiving();
    //boost::thread rcv_th(boost::bind(&GbnReceiver::StartReceiving, boost::ref(receiver)));
    //rcv_th.join();

    cout << "Thread tasks complete..." << endl;

    return 0;
}