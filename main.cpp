#include<stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <memory.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstdlib>
#include "SocketClient.h"

#define PORT_NUM "4950"
#define SERVER_IP_ADDR "192.168.1.7"


int main()
{
    SocketClient sock(SERVER_IP_ADDR, PORT_NUM);
}

