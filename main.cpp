#include "SocketClient.h"

#include "FileWriter.h"
#include <DataPacket.h>
#include <BinarySerializer.h>


using namespace std;
//#define SERVER_IP_ADDR "192.168.1.7"
#define SERVER_IP_ADDR "127.0.0.1"
#define SERV_FILESZ_HEADER "FILESIZE-"
#define PORT_NUM 62135

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

int main()
{

//
//    DataPacket p;
//    memset(&p, 0, sizeof(p));
//    char msg[248] = {0};

    //sock.SendPacket("hndshk", sizeof("hndshk"));
    //sock.ReceivePacket(woot);


    SocketClient sock(string(SERVER_IP_ADDR), PORT_NUM);
    string handshake_msg("hndshk");
    sock.HandshakeServer(handshake_msg);

    string files[3] = {
            string("mizo.txt"),
            string("pixi.ico"),
            string("zwp.jpg")
    };

    string file_name = files[2];

    basic_string<char> file_request("FILE-");
    file_request.append(file_name);

    FileWriter writer((char *) file_name.c_str());
    sock.SendPacket(file_request);

    void *file_header;
    long rcv_count = sock.ReceivePacket(&file_header);

    // Trim the last element as it's garbage because a string is being received
    string file_header_packet((char *) file_header);
    cout << "Received:" << file_header_packet << endl;

    int pos = (int) file_header_packet.find(SERV_FILESZ_HEADER);

    if (pos != 0) {
        cerr << "Malformed file header" << endl;
        return -1;
    }

    // TODO wrong packet count and content
    file_header_packet = file_header_packet.substr(strlen(SERV_FILESZ_HEADER), file_header_packet.size() - 1);
    char *pckt_num_ptr = (char *) file_header_packet.c_str();
    //ptr[file_header_packet.size()] = 0;

    cout << "Expected packet number:" << pckt_num_ptr << endl;

    int packet_count = stoi(pckt_num_ptr, nullptr, 0);



//    for (int j = 0; j < packet_count; ++j) {
//
//        void *packet_content;
//        long packet_size = sock.ReceivePacket(&packet_content);
//
//        writer.Write(packet_content, packet_size);
//        cout << "Packet #" << j << "Packet size " << packet_size << " Bytes" << endl;
//
//        string d("RECV-");
//        d.append(to_string(j));
//        sock.SendPacket(d);
//
//
//    }


    writer.~FileWriter();

    void *pck;
    long packet_size = sock.ReceivePacket(&pck);

    DataPacket d = BinarySerializer::DeserializeDataPacket(pck, packet_size);

    asm("nop");
    //string msg;
//    while (1)
//    {
//        cout << "Type something:";
//        cin >> msg;
//        memcpy(p.data, msg, strlen(msg));
//
//        p.cksum = 128;
//        p.len = 64;
//        p.seqno = 128;
//
//        char *packed = reinterpret_cast<char *>(&p);
//
//        DataPacket *pRec = reinterpret_cast<DataPacket *>(packed);
//
//    cout << "Unpacked:" << pRec->data << endl;
//        sock.SendPacket(packed, sizeof(DataPacket));
//        sock.ReceivePacket(woot);
//    }


//    while (1)
//    {
//        string in;
//
//        //cin >> in ;
//        getline(cin, in);
//        cout << "echo:" << in << endl;
//
//        const char *d = in.c_str();
//        sock.SendPacket(packed);
//        sock.ReceivePacket(woot);
//
//        if (in == "exit")
//        {
//            break;
//        }
//    }
    return 0;
}

