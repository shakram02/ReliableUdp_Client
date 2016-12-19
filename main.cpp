#include "SocketClient.h"
#include "FileWriter.h"

#define SERVER_IP_ADDR "192.168.1.7"

/**
 * Event handler for socket packet receive events, *msg and *ip must be freed to avoid leakage
 * @param msg Contains the socket message
 * @param ip Contains the server ip
 */
void woot(char *msg, char *ip)
{
    cout << "WOOT: \"" << msg << "\" from " << ip << endl;
}

int main()
{
    SocketClient sock(SERVER_IP_ADDR, 4950);
    const unsigned char *d = (unsigned char *) "asasadas";
    sock.SendPacket(d);
    sock.ReceivePacket(woot);

    //FileWriter r("mizo.txt");

    //r.Write("hello\n");
    //r.Write("hello1\n");
    //r.Write("hello2");
    return 0;
}

