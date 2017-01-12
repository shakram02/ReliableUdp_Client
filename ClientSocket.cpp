//
// Created by ahmed on 12/16/16.
//


#include <cstring>
#include <zconf.h>
#include <arpa/inet.h>
#include "ClientSocket.h"
#include "globaldefs.h"

/**
 * Creates a new client socket that connects to the specified server address and port
 * @param server_addr Server Address
 * @param server_port Port of the server
 */
ClientSocket::ClientSocket(const string &server_addr, const unsigned short server_port)
{
    server_info = unique_ptr<AddressInfo>(new AddressInfo(server_addr, server_port));
    this->server_addr = string(server_addr);
    InitializeSocket(server_port);
}

int ClientSocket::InitFileRequest(string &handshake)
{
    this->socket->SendString(*this->server_info, handshake);

    string temp = this->socket->ReceiveString();

    temp.replace(0, strlen(WELCOME_HEADER), "");
    cout << "Redirect port:" << temp << endl;

    is_initialized = true;
    return (stoi(temp));
}

void ClientSocket::SendPacket(byte *data, unsigned int len)
{
    if ((sendto(socket_fd, data, len, 0, (sockaddr *) &endpoint, sizeof(endpoint))) == -1) {
#if LOG >= 1
        log_error("Send# send to server");
#endif
        // TODO handle timeout or send failure
    }
    return;
}

long ClientSocket::ReceiveRaw(void **buf)
{

    if (!is_initialized) {
#if LOG >= 1
        fprintf(stderr, "An error occurred during initialization, can't call function ReceiveRaw");
#endif
        exit(-1);
    }

    void *ptr = calloc(BUF_LEN, sizeof(char));
    long int num_bytes;
    num_bytes = recvfrom(this->socket_fd, ptr, BUF_LEN * sizeof(char), 0,
            NULL, NULL);  // Don't care about the sender, it's known ( maybe add it back for more security checks)

    string err("ReceiveRaw");
    if (RawUdpSocket::GetDetailedSocketError(num_bytes, err)) {
        free(ptr);
        return 0;
    }

    (*buf) = calloc((size_t) num_bytes, sizeof(char));
    memcpy((*buf), ptr, (size_t) num_bytes);

    free(ptr);
    totalReceivedBytes += num_bytes;
    return num_bytes;
}

bool ClientSocket::ReceiveDataPacket(unique_ptr<Packet> &data_pckt)
{
    void *buf = 0;

    // The receive function allocates the right amount of memory
    // to the given input void*

    int num_bytes = (int) ReceiveRaw(&buf);
    if (num_bytes < 1) {
        data_pckt.reset();
        return false;
    }

    // buf is moved to the data_packet
    data_pckt = Packet::Create((byte *) buf, (unsigned short) num_bytes);

    return true;
}

void ClientSocket::InitializeSocket(const unsigned short server_port)
{
    AddressInfo info(this->server_addr, server_port);

    this->socket = unique_ptr<RawUdpSocket>(new RawUdpSocket(info));
    this->socket->SetReceiveTimeout(RCV_TIMEO_SEC, RCV_TIMEO_USEC);
    this->socket->SetSendTimeout(RCV_TIMEO_SEC, RCV_TIMEO_USEC);

//    memset(&endpoint, 0, sizeof(endpoint));
//
//    endpoint.sin_family = AF_INET;
//    endpoint.sin_port = htons(server_port);
//
//    if (inet_pton(AF_INET, this->server_addr.c_str(), &endpoint.sin_addr) == -1) {
//#if LOG >= 1
//        log_error("Ip to network conversion");
//#endif
//    }
//    if ((this->socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
//#if LOG >= 1
//        log_error("socket creation");
//#endif
//    }
//
//
//    timeval timeout;
//    // Removing memset causes unidentified behaviour as the values are originally garbage
//    memset(&timeout, 0, sizeof(timeout));
//    timeout.tv_sec = RCV_TIMEO_SEC;
//    timeout.tv_usec = RCV_TIMEO_USEC;
//    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
//#if LOG >= 1
//        log_error("set receive timeout");
//#endif
//    }
//    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
//        // Whatever we're sending might be locked, so a send timeout is set
//#if LOG >= 1
//        log_error("set send timeout");
//#endif
//    }
}

bool ClientSocket::LogSockError(long num_bytes, string function_name)
{
    bool is_err = false;
    if (num_bytes == 0) {
#if LOG >= 1
        log_error(function_name.append("#connection closed").c_str());
#endif
        is_err = true;
    } else if (num_bytes == -1) {
#if LOG >= 1
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            log_error(function_name.append("# receive err").c_str());
        }
#endif

        is_err = true;
    } else {
#if LOG >= 3
        //cout << endl << "Received " << num_bytes << " bytes" << endl;
#endif
    }
    return is_err;
}


ClientSocket::~ClientSocket()
{
    if (is_disposed)return;
    is_disposed = true;
    if (!is_initialized) {
        return;
    }
    close(this->socket_fd);

}

void ClientSocket::SendAckPacket(unsigned int seqno)
{
    // Allocate on the stack
    unique_ptr<ByteVector> empty = nullptr;
    Packet ack(empty, seqno);

    unique_ptr<ByteVector> raw = ack.Serialize();
    SendPacket(raw->data(), (unsigned int) raw->size());
}

void ClientSocket::log_error(const char *func_name)
{
    fprintf(stderr, "%s:%s\n", func_name, strerror(errno));
}

