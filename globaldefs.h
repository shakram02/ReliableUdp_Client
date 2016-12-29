//
// Created by ahmed on 12/25/16.
//

#ifndef ENHANCEDUDPCLIENT_GLOBALDEFS_H
#define ENHANCEDUDPCLIENT_GLOBALDEFS_H

// LOG 0 log nothing
// 1 errors only
// 2 log little info
// 3 verbose

#define SILENT 0
#define ERR 1
#define GRAINED 2
#define VERBOSE 3

#define LOG VERBOSE

//#define SERVER_IP_ADDR "192.168.1.7"
#define SERVER_IP_ADDR "127.0.0.1"
#define SERV_FILESZ_HEADER "FILESIZE-"
#define PORT_NUM 62135

#define BUF_LEN 256 // UDP MTU
#define WELCOME_HEADER "redirect"
#define REDIRECT_SUCCESS "REDIRECT SUCCESSFUL"
#define PROTOCOL_MAX_PACKET_LENGTH 64
#define REDIRECT_OK "OK"

#define RCV_TIMEO_SEC 1
#define RCV_TIMEO_USEC 0

#endif //ENHANCEDUDPCLIENT_GLOBALDEFS_H
