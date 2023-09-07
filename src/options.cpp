#include "options.h"
#include "common.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <arpa/inet.h>



namespace opt = boost::program_options;



int para_argv(int argc, char const *argv[]){
    opt::options_description des_cmd("\n thun help \n\n Options");
    des_cmd.add_options()
        ("config,c",opt::value(&options_arg.config_path)->default_value(""), "指定配置文件")
        ("tun_name,t",opt::value(&options_arg.tun_name)->default_value("tun0"), "生成网卡名称")
        ("tun_path,p",opt::value(&options_arg.tun_path)->default_value("/dev/net/tun"), "tun 的路径")
        ("mode,m",opt::value(&options_arg.mode)->default_value("s"), "运行的模式 s: server c: client")
        ("remove,r",opt::value(&options_arg.remove_tun_ip)->default_value(""), "远端服务器的ip+port")
        ("mtu",opt::value(&options_arg.mtu)->default_value(1500), "mtu")
        ("listen,l",opt::value(&options_arg.listen)->default_value("0.0.0.0:8888"), "监听ip+port")
        ("local_ip,h",opt::value(&options_arg.local_ip)->default_value("192.168.1.1/24"), "本地tun卡ip")
        ("help,h", "help");
    

    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc,argv,des_cmd),vm);
    opt::notify(vm); 



    if (options_arg.config_path != ""){
        std::ifstream ifs(options_arg.config_path);
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
    if (options_arg.mode != "s" && options_arg.mode != "c"){
        mylog(log_fatal,"mode must [c|s]");
        myexit(1);
    }

    // 校验 mtu
    if (options_arg.mtu < 0){
        mylog(log_fatal," mtu:%d less 0 ",options_arg.mtu);
        myexit(1);
    }

    // 校验本地网卡ip
    if (options_arg.local_ip == ""){
        mylog(log_fatal," local_ip required ");
        myexit(1);
    }
    std::vector<std::string> local_ip_vector;
    boost::split(local_ip_vector,options_arg.local_ip,boost::is_any_of("/"),boost::token_compress_on);
    if (local_ip_vector.size() != 2){
        mylog(log_fatal," local_ip must use [/] ");
        myexit(1);
    }

    options_arg.local_ip_u = inet_addr(local_ip_vector[0].c_str());
    options_arg.local_netmask_u = std::stoi(local_ip_vector[1].c_str());


    // 校验 remove_tun_ip
    if (options_arg.remove_tun_ip == ""){
        mylog(log_fatal," remove_tun_ip required ");
        myexit(1);
    }
    options_arg.remove_tun_ip_u = inet_addr(options_arg.remove_tun_ip.c_str());





    return 0;
}
