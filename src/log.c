#include "log.h"
#include <stdio.h>
int npc_log(const char *message, log_level level) {
	if (message[0] == '\0') {
		return 0;
	}
	if (level == info) {
		printf("[INFO] %s\n", message);
	}
	if (level == error) {
		printf("[ERROR] %s\n", message);
	}
	if (level == warning) {
		printf("[WARN] %s\n", message);
	}
	if (level == bad) {
		printf("[BAD] %s\n", message);
	}
	return 0;
}
int npc_debug_log(int is_debug, const char *message) {
	if (is_debug == 1) {
		printf("[DEB] %s\n", message);
	}
}