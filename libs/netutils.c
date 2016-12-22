//
// Created by ahmed on 12/17/16.
//


#include "netutils.h"


void log_error(const char *func_name)
{
    fprintf(stderr, "%s:%s\n", func_name, strerror(errno));
}


char *int_to_string(int num)
{
    // Get the exact number of digits in num
    int digits = 0, temp = num;
    do {
        digits++;
        temp /= 10;
    } while ((temp % 10) > 0);

    char *stringEquivalent = (char *) malloc(sizeof(char) * digits);
    sprintf(stringEquivalent, "%d", num);
    return stringEquivalent;
}


addrinfo *copy_addr_info(addrinfo *src)
{
    addrinfo *cpy = (addrinfo *) malloc(sizeof(addrinfo));
    memset(cpy, 0, sizeof(cpy));

    cpy->ai_addr = (sockaddr *) malloc(sizeof(src->ai_addr));
    cpy->ai_canonname = (char *) malloc(sizeof(src->ai_canonname));

    cpy->ai_addrlen = src->ai_addrlen;
    cpy->ai_family = src->ai_family;
    cpy->ai_flags = src->ai_flags;
    cpy->ai_protocol = src->ai_protocol;
    cpy->ai_socktype = src->ai_socktype;

    if (src->ai_addr != NULL) {
        memcpy(cpy->ai_addr, src->ai_addr, sizeof(src->ai_addr));
    }

    if (src->ai_canonname != NULL) {
        memcpy(cpy->ai_canonname, src->ai_canonname, sizeof(src->ai_canonname));
    }
    return cpy;
}


/**
 * Converts a given sockaddr to the matching in/in6_addr
 * @param sa Socket address
 * @return A pointer containing either an in or in6 addr object
 */

// Ugly function should remain hidden
static void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

static unsigned short get_port_num(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return ((struct sockaddr_in *) sa)->sin_port;
    }
    return ((struct sockaddr_in6 *) sa)->sin6_port;
}

void get_socket_info(struct sockaddr info, char *info_str_arr[])
{
    // TODO play with pointers to allocate using *** pointer
    info_str_arr[0] = (char *) malloc(INET6_ADDRSTRLEN * sizeof(char));
    info_str_arr[1] = (char *) malloc(SHORT_MAX_DIGITS * sizeof(char));

    inet_ntop(info.sa_family, get_in_addr(&info),
            info_str_arr[0], sizeof(char) * INET6_ADDRSTRLEN);

    int port = get_port_num(&info);
    sprintf(info_str_arr[1], "%d", port);
}

