
#include <memory.h>
#include <malloc.h>
#include <sys/socket.h>

#include "common.h"
#include "client.h"
#include "options.h"


int client_udp_fd;

uv_udp_t uv_udp;


void alloc_buffer(uv_handle_t* handle,size_t suggested_size,uv_buf_t* buf){
    buf->len = suggested_size;
    buf->base = static_cast<char *>(malloc(suggested_size));
}

void on_read(uv_udp_t* handle,ssize_t nread,const uv_buf_t* buf,const struct sockaddr* addr,unsigned flags){
    int tun_fd = *(int*)handle->data;
    
}

void client_udp_conn(uv_loop_t* loop, const struct options *options_arg,int tun_fd){

    struct sockaddr_in recv_addr;
    uv_ip4_addr(options_arg->remove_tun_ip.c_str(), options_arg->remove_port,&recv_addr);

    uv_udp_init(loop, &uv_udp);
    uv_udp_bind(&uv_udp, (const struct sockaddr *)&recv_addr, 0);

    uv_udp.data = (void*)tun_fd;
    uv_udp_recv_start(&uv_udp, alloc_buffer, on_read);


}