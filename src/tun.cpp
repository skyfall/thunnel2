// #include "threadpool.h"
#include "tun.h"
#include "common.h"



int get_tun_fd(const struct options *options_arg)
{
    int res_code = 0;
    int tun_fd = open(options_arg->tun_path.c_str(), O_RDWR);

    if (tun_fd < 0)
    {
        mylog(log_fatal, "open %s failed",options_arg->tun_path.c_str());
        myexit(-1);
    }
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

    strncpy(ifr.ifr_name, options_arg->tun_name.c_str(), IFNAMSIZ);

    if (ioctl(tun_fd, TUNSETIFF, (void *)&ifr) != 0)
    {
        mylog(log_fatal, "open creat tun ifr failed err:%d");
        myexit(-1);
    }

    // if (persist_tun == 1) {
    //     if (ioctl(tun_fd, TUNSETPERSIST, 1) != 0) {
    //         mylog(log_warn, "failed to set tun persistent");
    //     }
    // }
    // int bufsize = 1024 * 1024; // 1MB
    // assert( setsockopt(tun_fd, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize))  == 0);
    return tun_fd;
}

int set_tun( const struct options *options_arg)
{
    // if (manual_set_tun) return 0;

    // printf("i m here1\n");
    struct ifreq ifr;
    struct sockaddr_in sai;
    memset(&ifr, 0, sizeof(ifr));
    memset(&sai, 0, sizeof(struct sockaddr));

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(ifr.ifr_name, options_arg->tun_name.c_str(), IFNAMSIZ);

    sai.sin_family = AF_INET;
    sai.sin_port = 0;

    sai.sin_addr.s_addr = options_arg->local_ip_u;
    memcpy(&ifr.ifr_addr, &sai, sizeof(struct sockaddr));
    assert(ioctl(sockfd, SIOCSIFADDR, &ifr) == 0); // set source ip

    sai.sin_addr.s_addr = options_arg->local_netmask_u;
    memcpy(&ifr.ifr_addr, &sai, sizeof(struct sockaddr));
    assert(ioctl(sockfd, SIOCSIFNETMASK, &ifr) == 0); // set source netmask

    sai.sin_addr.s_addr = options_arg->remove_tun_ip_u;
    memcpy(&ifr.ifr_addr, &sai, sizeof(struct sockaddr));
    assert(ioctl(sockfd, SIOCSIFDSTADDR, &ifr) == 0); // set dest ip

    ifr.ifr_mtu = options_arg->mtu;
    assert(ioctl(sockfd, SIOCSIFMTU, &ifr) == 0); // set mtu

    assert(ioctl(sockfd, SIOCGIFFLAGS, &ifr) == 0);
    ifr.ifr_flags |= ( IFF_UP|IFF_POINTOPOINT|IFF_RUNNING|IFF_NOARP|IFF_MULTICAST );
    // ifr.ifr_flags = (IFF_UP | IFF_POINTOPOINT | IFF_RUNNING | IFF_NOARP | IFF_MULTICAST); // set interface flags
    assert(ioctl(sockfd, SIOCSIFFLAGS, &ifr) == 0);

    // printf("i m here2\n");
    return 0;
}

void tun_read_cb(uv_poll_t *handle, int status, int events)
{
    if (status < 0)
    {
        // 错误处理
        return;
    }

    // printf("tun_read_cb status%d events:%d\n",status,events);
    if (!(events & UV_READABLE))
    {
        return;
    }

    // int buff_len = 1500;
    int tun_fd = *(int*)handle->data;

    const  int iov_num = 2;
    struct iovec iov[iov_num];
    char buf[iov_num][1500];


    for(int i = 0; i < iov_num ;i++){
        iov[i].iov_len = 1550;
        iov[i].iov_base = buf[i];
    }

    const int  nread = readv(tun_fd,iov,iov_num);
    if(nread == 0) {  // 已断开连接
        return;
    }
    if(nread < 0) {
        return;
	}

    printf("tun_read_cb len:%d \t\t \n",nread);
}