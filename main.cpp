#include <uv.h>
#include <stdlib.h>
// #include <assert.h>
#include <string>
#include "tun.h"
// #include "common.h"


uv_loop_t loop;

void per_hanld(uv_prepare_t* handle){
    printf("per_hanld\t\t start\n");
    sleep(1);
    printf("per_hanld\t\t end\n");
}

int main(){
    int tun_fd;
    std::string tun_dev = "tun999";
    int tun_mtu = 1500;
    u32_t sub_net_uint32 = 0;

    sub_net_uint32 = inet_addr("10.22.22.0");

    uv_loop_init(&loop);

    tun_fd = get_tun_fd(tun_dev.c_str());
    assert(tun_fd > 0);

    assert(set_tun(tun_dev.c_str(), htonl((ntohl(sub_net_uint32) & 0xFFFFFF00) | 2), htonl((ntohl(sub_net_uint32) & 0xFFFFFF00) | 1), tun_mtu) == 0);

    
    int tun_fd_events = UV_READABLE;
    uv_poll_t tun_poll;

    printf(" start tun_fd:%d\n",tun_fd);
    tun_poll.data = &tun_fd;
    uv_poll_init(&loop,&tun_poll,tun_fd);
    uv_poll_start(&tun_poll,tun_fd_events,tun_read_cb);
    // uv_poll_init_socket(&loop,&tun_poll,tun_fd)

    uv_prepare_t per_hanld_t;
    uv_prepare_init(&loop,&per_hanld_t);
    uv_prepare_start(&per_hanld_t,per_hanld);



    uv_run(&loop,UV_RUN_DEFAULT);

}   