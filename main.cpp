#include "SocketClient.h"
#include "libs/DataPacket.h"

using namespace std;
#define SERVER_IP_ADDR "192.168.1.7"

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

    for (int i = 0; i < 10; ++i) {
        cout << endl << "#" << i << endl;
        SocketClient sock(string(SERVER_IP_ADDR), PORT_NUM, woot);
        string handshake_msg("hndshk");
        sock.HandshakeServer(handshake_msg);

        vector<char> dummy_msg;
        string success = "FILE-mizo.txt";

        basic_string<char> d(success);
        sock.SendPacket(d);
    }
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
////    cout << "Unpacked:" << pRec->data << endl;
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


    //FileWriter r("mizo.txt");

    //r.Write("hello\n");
    //r.Write("hello1\n");
    //r.Write("hello2");
    return 0;
}

