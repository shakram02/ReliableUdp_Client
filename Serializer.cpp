//
// Created by ahmed on 12/23/16.
//

#include "Serializer.h"

void Serializer::SerializeDataPacket(DataPacket data_pack, char *ptr)
{

}

void Serializer::SerializeAckPacket(AckPacket data_pack, char *ptr)
{

}

AckPacket Serializer::DeserializeAckPacket(char *packetBytes)
{
    return AckPacket();
}

DataPacket Serializer::DeserializeDataPacket(char *packetBytes, unsigned int packet_len)
{
    return DataPacket();
}
