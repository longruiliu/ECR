#include <sys/epoll.h>
#include <stdlib.h>
#include <queue>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <string>
#include <pthread.h>
#include "network.h"

extern int errno;
extern int signal_reload;
extern int signal_stop;

extern FILE *errlog;

ecr_thread_t *thread;
std::queue<unsigned long> conn_queue;

int set_nonblcoking(int fd)
{
	int nb;

	nb = 1;
	return ioctl(fd, FIONBIO, &nb);
	
}
void master_process(config_t *conf)
{
	struct epoll_event ev;
	int serv_fd, client_fd, epfd;
	connection_t *conn, *new_conn;
	int i;
	socklen_t tmp;

	int n;
	struct epoll_event *evs;
	
	serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(serv_fd, (struct sockaddr *)&conf->addr, (socklen_t) sizeof(struct sockaddr_in));
	listen(serv_fd, 5);
	set_nonblcoking(serv_fd);

	epfd = epoll_create(conf->max_threads);

	conn = (connection_t *)malloc(sizeof(connection_t));
	conn->accept = NOT_ACCEPTED;
	conn->fd = serv_fd;
	
	ev.events = EPOLLIN| EPOLLET;
	ev.data.fd = serv_fd;
	ev.data.ptr = conn;
	epoll_ctl(epfd, EPOLL_CTL_ADD, serv_fd, &ev);

	/*Worker thread*/
	thread = (ecr_thread_t *)malloc(sizeof(ecr_thread_t) *conf->max_threads);
	for(i = 0; i < conf->max_threads; i++)
		spawn_child_thread(&thread[i], thread_task, (void *)&thread[i]);

	evs = (struct epoll_event*)malloc(sizeof(struct epoll_event) * conf->max_threads);
	
	for( ; ; ){
		n = epoll_wait(epfd, evs, conf->max_threads, 1000);
		if(n == -1)
			ECR_LOG(LOG_ERR, "epoll errno = %s\n", strerror(errno));
		
		for(i = 0; i < n; i++){
			conn = (connection_t *)evs[i].data.ptr;
			if(conn->accept == NOT_ACCEPTED){
				/*�����ӽ�������*/
				new_conn = (connection_t *)malloc(sizeof(connection_t));
				/*����ʧ�ܾͶ����������*/
				if(!new_conn)
					continue;
				tmp = sizeof(conn->addr);
				client_fd = accept(conn->fd, (struct sockaddr *)&conn->addr, &tmp);
				conn->accept = ACCEPTED;

				ev.events = EPOLLIN|EPOLLET;
				ev.data.fd = client_fd;
				ev.data.ptr = conn;
				epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);

			}else if(conn->accept == ACCEPTED){
				/*һ��accept���˵����������ݵ�����*/

				conn_queue.push((unsigned long) conn);
				/*�ͻ����ڴ������Ժ��������free conn*/

				epoll_ctl(epfd, EPOLL_CTL_DEL, conn->fd, NULL);

				/*��һ���̴߳���*/
				for(i = 0; i < conf->max_threads; i++)
					if(thread[i].state == IDLE_STATE){
						thread[i].state = WORK_STATE;
						pthread_cond_signal(&thread[i].cond);
					}
			}

			/*�����ź�*/
			if(signal_reload){
				read_config(conf);
				
			}else if(signal_stop){
				printf("ECR Byte.\n");
				exit(0);
			}
		}
	}
	
}

void spawn_child_thread(ecr_thread_t *thread, threadfun_t  fun,void * arg)
{
	thread->state = IDLE_STATE;
	pthread_cond_init(&thread->cond, NULL);
	pthread_mutex_init(&thread->lock, NULL);
	pthread_create(&thread->tid, NULL, fun, arg);
}


void *thread_task(void *arg)
{
	std::string request;
	std::string response;
	char data[MAX_MESSAGE];
	int nr;
	connection_t *conn;
	
	ecr_thread_t *thread;
	thread = (ecr_thread_t *)arg;
	conn = (connection_t *)conn_queue.front();
	conn_queue.pop();
	
	for( ; ; ){
		pthread_cond_wait(&thread->cond, &thread->lock);

		nr = recvn(conn->fd, data, MAX_MESSAGE);

		/*����������߼��ˣ� ���������С�շ�*/
		request.clear();
		request.append(data, nr);
		requestHandler(request, response);

		sendn(conn->fd, response.c_str(), response.size());

		/*ǰ��˵��Ҫ�ͷ�conn*/
		free(conn);
	}

	return NULL;
}

int sendn(int fd, const char *data, int n)
{
	int left;

	left = n;
	while(left > 0){
		left -= write(fd, data, left);
	}
	return n;
}

/*
	n��ʾϣ�������������ȡ���ٸ��� ��recv�ķ���ֵ��ʾ����
	��ʵ�ʴ����������ȡ�˶��ٸ���
*/
int recvn(int fd, char *data, int n)
{
	int left;
	int tmp;

	left = n;
	while(left > 0){
		tmp = read(fd, data, left);
		if(tmp == -1){
			if(errno == EINTR)
				continue;
			else
				break;
		}

		if(tmp == 0)
			break;

		left -= tmp;
	}

	return n - left;
}

