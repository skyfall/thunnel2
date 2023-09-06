#ifndef TUN_H_
#define TUN_H_

#include <net/if.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <stdio.h>
#include <memory.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <uv.h>

#include"common.h"
#include "log.h"


int get_tun_fd(const char *dev_name) ;

int set_tun(const char *if_name, u32_t local_ip, u32_t remote_ip, int mtu);


void tun_read_cb(uv_poll_t* handle, int status, int events);

#endif