#ifndef LOG_H_
#define LOG_H_
const int log_never = 0;
const int log_fatal = 1;
const int log_error = 2;
const int log_warn = 3;
const int log_info = 4;
const int log_debug = 5;
const int log_trace = 6;
const int log_end = 7;

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

#define mylog(...) log0(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define assest_mylog(assest , ...) {if (!(assest)) { log0(__FILE__, __FUNCTION__, __LINE__,log_error,__VA_ARGS__);myexit(log_error);}}

extern int enable_log_color;


const char log_color[][20] = {RED, RED, RED, YEL, GRN, MAG, ""};
const char log_text[][20] = {"NEVER", "FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE", ""};

void log0(const char* file, const char* function, int line, int level, const char* str, ...);

#endif