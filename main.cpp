#include "SocketClient.h"
#include "FileWriter.h"

#define SERVER_IP_ADDR "192.168.1.7"


int main()
{
    SocketClient sock(SERVER_IP_ADDR, 4950);
    const unsigned char *d = (unsigned char *) "asasadas";
    sock.SendPacket(d);

    unsigned char e[4] = {1, 23, 4, 2}; // Doesn't receive
    sock.ReceivePacket(e);
    //FileWriter r("mizo.txt");

    //r.Write("hello\n");
    //r.Write("hello1\n");
    //r.Write("hello2");
    return 0;
}

