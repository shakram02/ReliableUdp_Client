//
// Created by ahmed on 12/19/16.
//

#ifndef ENHANCEDUDPCLIENT_DATAPACKETSTRUCT_H
#define ENHANCEDUDPCLIENT_DATAPACKETSTRUCT_H
struct data_packet
{
    /* Header */
    unsigned short cksum;
    unsigned short len;
    unsigned int seqno;

    /* Data */
    char data[248] = {0}; // Struct total size is 256 bytes

};
#endif //ENHANCEDUDPCLIENT_DATAPACKETSTRUCT_H
