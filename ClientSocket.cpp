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
    this->server_addr = string(server_addr);
    InitializeSocket(server_port);
}


int ClientSocket::HandshakeServer(string &handshake)
{
    // Don't check for byte count sent with UDP, it's meaningless

    if ((sendto(socket_fd, handshake.c_str(),
            handshake.size(), 0, (sockaddr *) &endpoint, sizeof(endpoint))) == -1) {
#if LOG >= 1
        log_error("Handshake# send to server");
#endif
        exit(1);
    }

    char buf[PROTOCOL_MAX_PACKET_LENGTH] = {0};

    long int num_bytes;

    num_bytes = recvfrom(this->socket_fd, buf, sizeof(buf), 0, (sockaddr *) NULL, NULL);
#if LOG >= 2
    cout << " Socket:" << this->socket_fd << endl;
#endif

    if (LogSockError(num_bytes))return 0;

// DEBUG
#if LOG >= 3
    cout << "#DEBUG Handshake received:\"" << buf
         << "\" Size:" << num_bytes << " bytes" <<
         endl;
#endif

    close(this->socket_fd);  // Close the welcome socket
    SwitchToRedirectedSocket(buf);

    string redirect_confirm(REDIRECT_SUCCESS);

    cout << "Sending:" << redirect_confirm.c_str() << endl;
    if ((sendto(socket_fd, redirect_confirm.c_str(), redirect_confirm.size(),
            0, (sockaddr *) &endpoint, sizeof(endpoint))) == -1) {
#if LOG >= 1
        log_error("Handshake# send to server");
#endif
        exit(1);
    }

    memset(buf, 0, PROTOCOL_MAX_PACKET_LENGTH);
    int n_bytes = (int) recvfrom(this->socket_fd, buf, sizeof(buf), 0, NULL, NULL);

    LogSockError(n_bytes);

    if (string(buf) == string(REDIRECT_OK)) {
#if LOG >= 2
        cout << "Server redirect confirmation received" << endl;
#endif
    } else {
#if LOG >= 1
        cerr << "Bad confirmation received:\"" << string(buf)
             << "\"" << endl;
#endif
        log_error("Confirm Failed");
        exit(2);
    }

    is_initialized = true;
    // TODO choose return values
    return 1;
}

void ClientSocket::SendPacket(void *data, unsigned int len)
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

    if (LogSockError(num_bytes))return 0;

    (*buf) = calloc((size_t) num_bytes, sizeof(char));
    memcpy((*buf), ptr, (size_t) num_bytes);

    free(ptr);
    totalReceivedBytes += num_bytes;
    return num_bytes;
}

bool ClientSocket::ReceiveDataPacket(DataPacket *data_pckt)
{
    void *buf = 0;

    int num_bytes = (int) ReceiveRaw(&buf);
    if (num_bytes < 1)return false;

    char *baf = (char *) buf;

    DataPacket *temp;
    //BinarySerializer::DeserializeDataPacket(buf, (unsigned int) num_bytes, &temp);
    temp = reinterpret_cast<DataPacket *>(buf);

    data_pckt->chksum = temp->chksum;
    data_pckt->seqno = temp->seqno;
    data_pckt->len = temp->len;


    //cout << "Packet length:" << temp->len << endl;
    memcpy(data_pckt->data, temp->data, temp->len);

    free(buf);

    return true;
}

void ClientSocket::SwitchToRedirectedSocket(char *message)
{
    string redirect_message = string(message);
    redirect_message.replace(0, strlen(WELCOME_HEADER), "");
#if LOG >= 2
    cout << "Redirect port:" << redirect_message << endl;
#endif
    InitializeSocket((unsigned short) stoi(redirect_message));
}


void ClientSocket::InitializeSocket(const unsigned short server_port)
{
    memset(&endpoint, 0, sizeof(endpoint));

    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(server_port);

    if (inet_pton(AF_INET, this->server_addr.c_str(), &endpoint.sin_addr) == -1) {
#if LOG >= 1
        log_error("Ip to network conversion");
#endif
    }
    if ((this->socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
#if LOG >= 1
        log_error("socket creation");
#endif
    }


    timeval timeout;
    // Removing memset causes unidentified behaviour as the values are originally garbage
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = RCV_TIMEO_SEC;
    timeout.tv_usec = RCV_TIMEO_USEC;
    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
#if LOG >= 1
        log_error("set receive timeout");
#endif
    }
    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
        // Whatever we're sending might be locked, so a send timeout is set
#if LOG >= 1
        log_error("set send timeout");
#endif
    }
}

bool ClientSocket::LogSockError(long num_bytes)
{
    bool is_err = false;
    if (num_bytes == 0) {
#if LOG >= 1
        log_error("connection closed");
#endif
        is_err = true;
    } else if (num_bytes == -1) {
#if LOG >= 1
        log_error("recvfrom err");
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
    //AckPacket *ack_pckt = new AckPacket(seqno);


    AckPacket ack_pckt(seqno);
    cout << "ACK send [" << ack_pckt.ack_num << "]" << endl;

    void *raw_ptr;
    BinarySerializer::SerializeAckPacket(&ack_pckt, &raw_ptr);

    SendPacket(raw_ptr, sizeof(AckPacket));

    //delete ack_pckt;
}

void ClientSocket::log_error(const char *func_name)
{
    fprintf(stderr, "%s:%s\n", func_name, strerror(errno));
}