#ifndef __LOG_H__
#define __LOG_H__

#include "uart.h"
#include <stdint.h>

enum log_level {
	LOG_LEVEL_ERR,
	LOG_LEVEL_WARN,
	LOG_LEVEL_INFO,
	LOG_LEVEL_DBG,
	LOG_LEVEL_MAX
};

#define DEFAULT_LOG_LEVEL	LOG_LEVEL_INFO	
extern enum log_level curr_log_level;
#define LOG_LEVEL_CURR		curr_log_level

#define LOG(LVL, fmt, ...)						\
		do {							\
			if (LOG_LEVEL_CURR >= LOG_LEVEL_##LVL)		\
				printf(#LVL ": " fmt, ##__VA_ARGS__);	\
		} while(0)

#define LOG_DBG(fmt, ...)	LOG(DBG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)	LOG(INFO, fmt, ##__VA_ARGS__) 
#define LOG_WARN(fmt, ...)	LOG(WARN, fmt, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...)	LOG(ERR, fmt, ##__VA_ARGS__.)

#endif
