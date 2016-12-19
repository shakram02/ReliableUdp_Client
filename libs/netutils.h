//
// Created by ahmed on 12/17/16.
//

#ifndef ENHANCEDUDPCLIENT_NETUTILS_H
#define ENHANCEDUDPCLIENT_NETUTILS_H

#include<stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <memory.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>

#define SHORT_MAX_DIGITS 5

typedef struct addrinfo addrinfo;
typedef struct sockaddr sockaddr;

/**
 * Logs the errorno to output stream
 * @param func_name name of the function that caused the error
 */
void log_error(const char *func_name);

/**
 * Converts the given integer number to a string
 * @param num number to be converted
 * @return String equivalent
 */
char *int_to_string(int);

/**
 * Copies Address info object to another one
 * @param src Source Address info object
 * @return Copy of src
 */
addrinfo *copy_addr_info(addrinfo *src);

/**
* Returns an array of strings
 * [0] : IP address
 * [1] : port number
* @return array contining the Ip Address and the port number as strings
*/
void get_socket_info(struct sockaddr info, char *info_str_arr[]);

#endif //ENHANCEDUDPCLIENT_NETUTILS_H




