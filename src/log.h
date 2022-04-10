#ifndef __LOG_H__
#define __LOG_H__

#include "uart.h"

#define DEFAULT_LOG_LEVEL	

extern enum log_level curr_log_level;

enum log_level {
	LOG_LEVEL_ERR,
	LOG_LEVEL_WARN,
	LOG_LEVEL_INFO,
	LOG_LEVEL_DBG,
	LOG_LEVEL_MAX
};

#define LOG_DBG(fmt, ...)	{ \
		while (1) { \
			if (curr_log_level >= LOG_LEVEL_DBG) \
				printf("DBG: " fmt, ##__VA_ARGS__); \
			break; \
		}; \
	};


#define LOG_INFO(fmt, ...)	{ \
		while (1) { \
			if (curr_log_level >= LOG_LEVEL_INFO) \
				printf("INFO: " fmt, ##__VA_ARGS__); \
			break; \
		}; \
	};


#define LOG_WARN(fmt, ...)	{ \
		while (1) { \
			if (curr_log_level >= LOG_LEVEL_WARN) \
				printf("WARN: " fmt, ##__VA_ARGS__); \
			break; \
		}; \
	};

#define LOG_ERR(fmt, ...)	{ \
		while (1) { \
			if (curr_log_level >= LOG_LEVEL_ERR) \
				printf("ERROR: " fmt, ##__VA_ARGS__); \
			break; \
		}; \
	};

#endif
