//
// Created by ahmed on 12/23/16.
//

#ifndef ENHANCEDUDPCLIENT_CHECKSUM_H
#define ENHANCEDUDPCLIENT_CHECKSUM_H


#include <stdint-gcc.h>
#include "libs/DataPacket.h"

class Checksum
{
public:
    static uint32_t Create(DataPacket packet);
};


#endif //ENHANCEDUDPCLIENT_CHECKSUM_H
