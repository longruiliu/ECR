#ifndef _NETWORK_H_INCLUDED_
#define _NETWORK_H_INCLUDED_

#include <netinet/in.h>
#include <string>
#include <sys/ioctl.h>

#include "global.h"
#define MAX_MESSAGE 1024




struct ecr_thread_s{
	pthread_t tid;
	pthread_cond_t cond;
	pthread_mutex_t lock;
	int state;
};
typedef struct ecr_thread_s ecr_thread_t;

#define WORK_STATE 0
#define IDLE_STATE 1

struct connection_s{
	struct sockaddr_in addr;
	int accept;
	int fd;
};

typedef struct connection_s connection_t;
#define ACCEPTED 1
#define NOT_ACCEPTED 0


typedef void *(*threadfun_t )(void *);

void master_process(config_t *conf);
void spawn_child_thread(ecr_thread_t *thread, threadfun_t fun, void *arg);
void *thread_task(void *arg);
int set_nonblcoking(int fd);
extern void read_config(config_t *conf);
extern void requestHandler(std::string &request, std::string &response);

/*
	-1表示失败, 其他的表示写到或读取网络上的数据
	n表示data的长度
*/
int sendn(int fd, const char *data, int n);
int recvn(int fd, char *data, int n);


#endif
