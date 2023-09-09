#include "options.h"
#include "common.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <arpa/inet.h>



namespace opt = boost::program_options;

struct options options_arg; 


int para_argv(int argc, char const *argv[]){
    opt::options_description des_cmd("\n thun help \n\n Options");
    des_cmd.add_options()
        ("config,c",opt::value(&options_arg.config_path)->default_value(""), "指定配置文件")
        ("tun_name,t",opt::value(&options_arg.tun_name)->default_value("tun0"), "生成网卡名称")
        ("tun_path,p",opt::value(&options_arg.tun_path)->default_value("/dev/net/tun"), "tun 的路径")
        ("mode,m",opt::value(&options_arg.mode)->default_value("s"), "运行的模式 s: server c: client")
        ("remove,r",opt::value(&options_arg.remove_tun_ip)->default_value(""), "远端服务器的ip")
        ("mtu",opt::value(&options_arg.mtu)->default_value(1500), "mtu")
        ("listen,l",opt::value(&options_arg.listen)->default_value("0.0.0.0:8888"), "监听ip+port")
        ("local_ip,h",opt::value(&options_arg.local_ip)->default_value("192.168.1.1"), "本地tun卡ip")
        ("local_ip_netmask",opt::value(&options_arg.local_ip_netmask)->default_value("255.255.255.0"), "本地tun卡子网掩码")
        ("remove_port",opt::value(&options_arg.remove_port)->default_value(8888), "远端端口")
        ("help,h", "help");
    

    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc,argv,des_cmd),vm);
    opt::notify(vm); 



    if (options_arg.config_path != "" ){
        std::ifstream ifs(options_arg.config_path);
        assest_mylog(ifs.good() == true,"config_path:%s 配置文件不存在 \n",options_arg.config_path.c_str());
        opt::store(parse_config_file(ifs,des_cmd),vm);
        opt::notify(vm); 
    }


    opt::store(opt::parse_command_line(argc,argv,des_cmd),vm);
    opt::notify(vm); 


    if (vm.count("help") || vm.count("h")) {
        std::cout << des_cmd << "\n";
        exit(0);
    }

    // 校验 mode
    boost::to_lower(options_arg.mode);
    assest_mylog((options_arg.mode == "s" || options_arg.mode == "c"),"mode must [c|s] \n");

    // 校验 mtu
    assest_mylog(options_arg.mtu > 0," mtu:%d less 0 \n",options_arg.mtu);


    // 校验本地网卡ip
    assest_mylog(options_arg.local_ip != ""," local_ip required \n");

    
    options_arg.local_ip_u = inet_addr(options_arg.local_ip.c_str());
    options_arg.local_netmask_u = inet_addr(options_arg.local_ip_netmask.c_str());
    


    // 校验 remove_tun_ip
    assest_mylog(options_arg.remove_tun_ip != ""," remove_tun_ip required\n ");


    options_arg.remove_tun_ip_u = inet_addr(options_arg.remove_tun_ip.c_str());

    return 0;
}
