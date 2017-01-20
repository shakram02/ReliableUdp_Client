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

#define TO_MILLISECS 1000
#define RCV_TIMEO_SEC 0
#define RCV_TIMEO_USEC TO_MILLISECS * 5

#define LOOP_BCK_IP "127.0.0.1"

#define INITIAL_RCV_TIMEO_SEC 0
#define INITIAL_RCV_TIMEO_USEC TO_MILLISECS * 500

#endif //ENHANCEDUDPCLIENT_GLOBALDEFS_H
