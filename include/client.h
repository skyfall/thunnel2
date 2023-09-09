#ifndef CLIENT_H_
#define CLIENT_H_

#include <uv.h>

extern int client_udp_fd;

extern uv_udp_t uv_udp;

void client_udp_conn_cb(uv_prepare_t* handle);


void client_udp_conn(uv_loop_t* loop, const struct options *options_arg,int tun_fd);

#endif