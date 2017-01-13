//
// Created by ahmed on 12/16/16.
//


#ifndef ENHANCEDUDPCLIENT_SOCKETCLIENT_H
#define ENHANCEDUDPCLIENT_SOCKETCLIENT_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <Packet.h>
#include <AddressInfo.h>
#include <RawUdpSocket.h>

using namespace std;

class MainSocket
{
public:

    MainSocket(const string &server_addr, const unsigned short server_port);

    ~MainSocket();

    /**
     * //TODO
     * @param handshake
     * @return Redirect port of the server
     */
    int InitFileRequest(string &handshake);

private:
    string server_addr;
    unique_ptr<RawUdpSocket> socket;
    unique_ptr<AddressInfo> server_info;

};

#endif //ENHANCEDUDPCLIENT_SOCKETCLIENT_H
