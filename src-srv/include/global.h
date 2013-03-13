#ifndef _GLOBAL_H_INCLUED_
#define _GLOBAL_H_INCLUED_

#include <netinet/in.h>

#define DEFAULT_CONFIG_PATH "/etc/ecr.conf"
#define CONFIG_PATH_LEN 32

#define ECR_PIDFILE_PATH "/var/run/ecr.pid"

#define DEFAULT_LOG_PATH "/var/log/ecr.log"
#define LOG_PATH_LEN 32

#define DAEMON 1
#define NOTDAEMON 0

#define SIGNAL_RELOAD 1
#define SIGNAL_NOT_RELOAD 0

#define SIGNAL_STOP 1
#define SIGNAL_NOT_STOP 0

#define LOG_WARN 0
#define LOG_ERR 1
#define LOG_DIE 2

struct config_s{
	struct sockaddr_in addr;
	int max_threads;
	int log_level;
};
typedef struct config_s config_t;



#define ECR_LOG(level, format, args...) \
	do{\
		extern config_t conf;\
		if(conf.log_level <= level){\
			fprintf(errlog, format, ##args);\
		}\
	}while(0)

#endif
