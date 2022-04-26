#ifndef LOG_H
#define LOG_H
typedef enum {
    info,
    warning,
    error,
    bad
} log_level;
int npc_log(const char* message, log_level level);
int npc_debug_log(int is_debug, const char*message);
#endif