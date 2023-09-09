#include <uv.h>
#include <stdlib.h>
#include <string>

#include "tun.h"
#include "options.h"
#include "client.h"


uv_loop_t loop;

void per_hanld(uv_prepare_t* handle){

}

int main(int argc, char const *argv[]){

    int err_code = 0;
    // 参数解析
    assest_mylog((err_code = para_argv(argc,argv)) == 0,"参数解析失败 err:%d",err_code);

    
    int tun_fd;
    u32_t sub_net_uint32 = 0;

    uv_loop_init(&loop);

    tun_fd = get_tun_fd(&options_arg);
    assest_mylog(tun_fd > 0,"创建tun网卡失败 err:%d",tun_fd);

    assest_mylog((err_code = set_tun(&options_arg)) == 0,"设置tun网卡失败 err:%d",err_code);

    int tun_fd_events = UV_READABLE;
    uv_poll_t tun_poll;


    // tun卡数据读取
    tun_poll.data = &tun_fd;
    uv_poll_init(&loop,&tun_poll,tun_fd);
    uv_poll_start(&tun_poll,tun_fd_events,tun_read_cb);
    
    // 
    uv_prepare_t per_hanld_t;
    uv_prepare_init(&loop,&per_hanld_t);
    uv_prepare_start(&per_hanld_t,per_hanld);


    if (options_arg.mode == "c"){
        // 客户端模式
        client_udp_conn(&loop,&options_arg,tun_fd);
    } else{
        // 服务端模式

    }

    uv_run(&loop,UV_RUN_DEFAULT);

}   