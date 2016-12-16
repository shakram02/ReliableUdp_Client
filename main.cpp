#include "SocketClient.h"

#define PORT_NUM "4950"
#define SERVER_IP_ADDR "192.168.1.7"


int main()
{
    SocketClient sock(SERVER_IP_ADDR, 4950);
    const unsigned char *d = (unsigned char *) "asdas";
    sock.SendPacket(d);

    return 0;
}

