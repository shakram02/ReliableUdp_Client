//
// Created by ahmed on 12/23/16.
//

#ifndef ENHANCEDUDPCLIENT_SERIALIZER_H
#define ENHANCEDUDPCLIENT_SERIALIZER_H


#include "libs/DataPacket.h"
#include "libs/AckPacket.h"

class Serializer
{
public:
    static void SerializeDataPacket(DataPacket data_pack,char* ptr);

    static void SerializeAckPacket(AckPacket data_pack,char* ptr);

    static DataPacket DeserializeDataPacket(char *packetBytes, unsigned int packet_len);

    static AckPacket DeserializeAckPacket(char *packetBytes);

};


#endif //ENHANCEDUDPCLIENT_SERIALIZER_H
