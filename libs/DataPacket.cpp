//
// Created by ahmed on 12/23/16.
//
#include "DataPacket.h"

DataPacket DataPacket::Create(std::basic_string<char> data, unsigned int seq_no)
{
    DataPacket packet;
    // Create check sum
    // Create packet number
    packet.seqno = seq_no;
    // Pack data
    std::basic_string<char> d;

    return packet;
}
