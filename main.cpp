#include <uv.h>
#include <stdlib.h>
// #include <assert.h>
#include <string>
#include "tun.h"
// #include "common.h"


uv_loop_t loop;



int main(){
    int tun_fd;
    std::string tun_dev = "tun999";
    int tun_mtu = 1500;
    u32_t sub_net_uint32 = 0;

    sub_net_uint32 = inet_addr("192.168.2.1");

    // uv_loop_init(&loop);

    tun_fd = get_tun_fd(tun_dev.c_str());
    assert(tun_fd > 0);

    assert(set_tun(tun_dev.c_str(), htonl((ntohl(sub_net_uint32) & 0xFFFFFF00) | 2), htonl((ntohl(sub_net_uint32) & 0xFFFFFF00) | 1), tun_mtu) == 0);



    // uv_run(&loop,UV_RUN_DEFAULT);

}   