#include "common.h"

int about_to_exit = 0;


void myexit(int a) {
    if (enable_log_color)
        printf("%s\n", RESET);
    // clear_iptables_rule();
    exit(a);
}