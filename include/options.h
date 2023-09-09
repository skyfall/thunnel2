#ifndef CONFIG_H_
#define CONFIG_H_

#include "common.h"
#include <string>
#include <boost/program_options.hpp>



struct options
{
    std::string  tun_name;
    std::string  tun_path;
    std::string  config_path;
    std::string  listen;
    std::string  remove_tun_ip;
    std::string  local_ip;
    std::string  local_ip_netmask;
    std::string  mode;

    u32_t local_ip_u;
    u32_t local_netmask_u;

    int remove_tun_ip_u;

    int mtu ;
    uint16_t remove_port;

} ;

extern struct options options_arg; 


int para_argv(int argc, char const *argv[]);
#endif