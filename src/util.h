//
// Created by wong on 10/24/18.
//

#ifndef TRANSOCKS_WONG_UTIL_H
#define TRANSOCKS_WONG_UTIL_H

#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h> /* inet_pton, inet_ntop */
#include <sys/types.h>
#include <sys/socket.h>  /* socket(), bind(),listen(), accept(),getsockopt() */
#include <linux/netfilter_ipv4.h>             /* SO_ORIGINAL_DST */
#include <linux/netfilter_ipv6/ip6_tables.h>  /* IP6T_SO_ORIGINAL_DST */

#include <event2/util.h>

#ifndef SO_ORIGINAL_DST
#warning using custom SO_ORIGINAL_DST
#define SO_ORIGINAL_DST  80
#endif

#ifndef IP6T_SO_ORIGINAL_DST
#warning using custom IP6T_SO_ORIGINAL_DST
#define IP6T_SO_ORIGINAL_DST  80
#endif

#define TRANSOCKS_INET_PORTSTRLEN (5 + 1)
/* '[' + INET6_ADDRSTRLEN + ']' + ':' + "65535" + NUL */
#define TRANSOCKS_INET_ADDRPORTSTRLEN (1 + INET6_ADDRSTRLEN + 1 + 1 + TRANSOCKS_INET_PORTSTRLEN + 1)

#define TRANSOCKS_UNUSED(obj) ((void)obj)


enum {
    GETOPT_VAL_LISTENERADDRPORT,
    GETOPT_VAL_SOCKS5ADDRPORT,
    GETOPT_VAL_HELP
};
void generate_sockaddr_port_str (char *, size_t, const struct sockaddr *, socklen_t);
int apply_tcp_keepalive(int);
int setnonblocking(int, bool);
int getorigdst(int, struct sockaddr_storage *, socklen_t *);
bool is_would_block(int);
bool validatePort(struct sockaddr_storage *);
int transocks_parse_sockaddr_port(const char *str, struct sockaddr *sa, socklen_t *actualSockAddrLen);
void print_help(void);

#endif //TRANSOCKS_WONG_UTIL_H
