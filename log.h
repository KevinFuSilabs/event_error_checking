#ifndef _LOG_H_
#define _LOG_H_

#include "stdio.h"
#include "retargetserial.h"
#include "SEGGER_RTT.h"
/* High level defines, needs user to decide */
#define LOG_LEVEL								LVL_VERBOSE
#define LOG_PORT									SEGGER_JLINK_VIEWER

#define NO_LOG									0
#define LVL_ERROR								1
#define LVL_WARNING							2
#define LVL_INFO								3
#define LVL_DEBUG								4
#define LVL_VERBOSE							5


#define PORT_VCOM									1
#define SEGGER_JLINK_VIEWER				2
#if (LOG_PORT == SEGGER_JLINK_VIEWER)
#define INIT_LOG()						SEGGER_RTT_Init()
#define LOG(...)								SEGGER_RTT_printf(0, __VA_ARGS__)
#elif (LOG_PORT == PORT_VCOM)
#define INIT_LOG()							RETARGET_SerialInit()
#define LOG(...)								printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

/* Error */
#define LOGE(_prefix_, ...)				\
	do{															\
		if(LOG_LEVEL >=  LVL_ERROR){	\
			LOG(RTT_CTRL_TEXT_BRIGHT_RED"ERROR   -> " _prefix_ "\r\n"RTT_CTRL_RESET, ##__VA_ARGS__);			\
		}																																																\
}while(0)

/* Warning */
#define LOGW(_prefix_, ...)				\
	do{															\
		if(LOG_LEVEL >=  LVL_WARNING){	\
			LOG(RTT_CTRL_TEXT_BRIGHT_YELLOW"WARNING -> " _prefix_ "\r\n"RTT_CTRL_RESET, ##__VA_ARGS__);			\
		}																																																\
}while(0)

/* Information */
#define LOGI(_prefix_, ...)				\
	do{															\
		if(LOG_LEVEL >=  LVL_INFO){	\
			LOG(RTT_CTRL_TEXT_BRIGHT_BLUE"INFO    -> " _prefix_ "\r\n"RTT_CTRL_RESET, ##__VA_ARGS__);			\
		}																																																\
}while(0)

/* DEBUG */
#define LOGD(_prefix_, ...)				\
	do{															\
		if(LOG_LEVEL >=  LVL_DEBUG){	\
			LOG(RTT_CTRL_TEXT_BRIGHT_GREEN"DEBUG   -> " _prefix_ "\r\n"RTT_CTRL_RESET, ##__VA_ARGS__);			\
		}																																																\
}while(0)

/* Vobase */
#define LOGV(_prefix_, ...)				\
	do{															\
		if(LOG_LEVEL >=  LVL_VERBOSE){	\
			LOG(RTT_CTRL_RESET"VERBOSE  -> " _prefix_ "\r\n"RTT_CTRL_RESET, ##__VA_ARGS__);			\
		}																																																\
}while(0)

uint16_t error_checking(uint16_t error_code);

#define ERROR_ADDRESSING()						\
	do{																	\
			LOGE("  |--> File - %s, Line - %d", __FILE__, __LINE__);			\
	}while(0)

#endif
