#include "common.h"
#include <fcntl.h>

int about_to_exit = 0;


void myexit(int a) {
    if (enable_log_color)
        printf("%s\n", RESET);
    // clear_iptables_rule();
    exit(a);
}

void myexitwithmess(const bool assest,const char* message, ...){
    if (!assest){
        va_list args;
        va_start(args, message);
        mylog(log_error,message,args); 
        va_end(args);
        
        myexit(1);
    }
}
void setnonblocking(int sock){
    int opts;
    opts = fcntl(sock, F_GETFL);
    assest_mylog(opts == 0 , "设置socket非阻塞失败");
    opts = opts | O_NONBLOCK;
    assest_mylog(fcntl(sock, F_SETFL, opts) == 0,"fcntl(sock,SETFL,opts)");
}