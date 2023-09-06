// #include "threadpool.h"
#include "tun.h"
#include "common.h"

int get_tun_fd(const char *dev_name)
{
    int tun_fd = open("/dev/net/tun", O_RDWR);

    if (tun_fd < 0)
    {
        mylog(log_fatal, "open /dev/net/tun failed");
        myexit(-1);
    }
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

    strncpy(ifr.ifr_name, dev_name, IFNAMSIZ);

    if (ioctl(tun_fd, TUNSETIFF, (void *)&ifr) != 0)
    {
        mylog(log_fatal, "open /dev/net/tun failed");
        myexit(-1);
    }

    // if (persist_tun == 1) {
    //     if (ioctl(tun_fd, TUNSETPERSIST, 1) != 0) {
    //         mylog(log_warn, "failed to set tun persistent");
    //     }
    // }
    return tun_fd;
}

int set_tun(const char *if_name, u32_t local_ip, u32_t remote_ip, int mtu)
{
    // if (manual_set_tun) return 0;

    // printf("i m here1\n");
    struct ifreq ifr;
    struct sockaddr_in sai;
    memset(&ifr, 0, sizeof(ifr));
    memset(&sai, 0, sizeof(struct sockaddr));

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(ifr.ifr_name, if_name, IFNAMSIZ);

    sai.sin_family = AF_INET;
    sai.sin_port = 0;

    sai.sin_addr.s_addr = local_ip;
    memcpy(&ifr.ifr_addr, &sai, sizeof(struct sockaddr));
    assert(ioctl(sockfd, SIOCSIFADDR, &ifr) == 0); // set source ip

    sai.sin_addr.s_addr = remote_ip;
    memcpy(&ifr.ifr_addr, &sai, sizeof(struct sockaddr));
    assert(ioctl(sockfd, SIOCSIFDSTADDR, &ifr) == 0); // set dest ip

    ifr.ifr_mtu = mtu;
    assert(ioctl(sockfd, SIOCSIFMTU, &ifr) == 0); // set mtu

    assert(ioctl(sockfd, SIOCGIFFLAGS, &ifr) == 0);
    // ifr.ifr_flags |= ( IFF_UP|IFF_POINTOPOINT|IFF_RUNNING|IFF_NOARP|IFF_MULTICAST );
    ifr.ifr_flags = (IFF_UP | IFF_POINTOPOINT | IFF_RUNNING | IFF_NOARP | IFF_MULTICAST); // set interface flags
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

    int buff_len = 1500;
    int tun_fd = *(int*)handle->data;
    // printf("fd_id:%d\n",tun_fd);
    char buffer[buff_len];

    printf("read\t\tstart\n");
    int nread = read(tun_fd,&buffer,buff_len);
    printf("read\t\tend\n");
    if(nread == 0) {  // 已断开连接
        return;
    }
    if(nread < 0) {
        return;
	}

    printf("tun_read_cb len:%d \t\t data:%-8X\n",nread);
}