#ifndef LOG_H
#define LOG_H
typedef enum log_level {
	log_info,
	log_warning,
	log_error,
	log_bad,
	log_debug
} log_level;
int npc_log(log_level level, const char *message);
int npc_debug_log(int is_debug, const char *message);
#endif