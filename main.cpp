#include <uv.h>
#include <stdlib.h>
#include <string>

#include "tun.h"
#include "options.h"


uv_loop_t loop;

void per_hanld(uv_prepare_t* handle){

}

int main(int argc, char const *argv[]){

    // 参数解析
    assert(para_argv(argc,argv) == 0);



    int tun_fd,tun_fd2;
    u32_t sub_net_uint32 = 0;


    uv_loop_init(&loop);

    tun_fd = get_tun_fd(&options_arg);
    assert(tun_fd > 0);



    assert(set_tun(&options_arg) == 0);

    
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