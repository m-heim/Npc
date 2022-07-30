#include "log.h"
#include <stdio.h>
int npc_log(log_level level, const char *message) {
	if (message[0] == '\0') {
		return 0;
	}
	if (level == log_info) {
		printf("[INFO] %s\n", message);
	}
	if (level == log_error) {
		printf("[ERROR] %s\n", message);
	}
	if (level == log_warning) {
		printf("[WARN] %s\n", message);
	}
	if (level == log_bad) {
		printf("[BAD] %s\n", message);
	}
	if (level == log_debug) {
		printf("[DEB] %s\n", message);
	}
	if (level == log_intern) {
		printf("[INTERN] %s\n", message);
	}
	return 0;
}
int npc_debug_log(int is_debug, const char *message) {
	if (is_debug != 0) {
		return npc_log(log_debug, message);
	}
	return 0;
}