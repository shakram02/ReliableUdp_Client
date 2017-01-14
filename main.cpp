#include "MainSocket.h"

#include "FileWriter.h"
#include "client_config.h"
#include "GbnReceiver.h"
#include "FileTransfer.h"

using namespace std;

#define FILE_IDX 1

int main()
{
    MainSocket sock(string(SERVER_IP_ADDR), PORT_NUM);
    string sync_msg(HANDSHAKE);

    // This method will return a redirect port which
    // will be used to create the file request object
    int redirect_port = sock.InitFileRequest(sync_msg);

    if (redirect_port < 0)exit(-1);

    const string files[3] = {
            string("zooz.txt"),
            string("txrxPc.png"),
            string("Pro Git.pdf"),
    };

    string file_name = files[FILE_IDX];
    cout << "Requesting file" << endl;
    AddressInfo endpoint(string(SERVER_IP_ADDR), (unsigned short) redirect_port);

    cout << "Redirecting socket" << endl;
    string serv_ip = string(SERVER_IP_ADDR);

    // TODO FACTORY!!!!
    unique_ptr<FileWriter> writer = unique_ptr<FileWriter>(new FileWriter(file_name));
    GbnReceiver *receiver = new GbnReceiver(5, writer);

    FileTransfer transfer(serv_ip, (unsigned short) redirect_port, file_name,
            static_cast<AbstractReceiver *>(receiver));

    int packet_count = transfer.GetPacketCount();
    cout << "Packet count:" << packet_count << endl;
    transfer.StartReceive();

    cout << "Thread tasks complete..." << endl;
    return 0;
}