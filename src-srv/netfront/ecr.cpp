#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "global.h"
#include "network.h"

#if 0
static struct option opts[] = {
	{.name = "help", .has_arg = 0, .val = 'h'},
	{.name = "version", .has_arg = 0, .val = 'v'},
	{.name = "daemon", .has_arg = 0, .val = 'd'},
	{.name = "configure", .has_arg = 1, .val = 'c'},
	{.name = "signal", .has_arg = 1, .val = 's'},
};
#endif 

static struct option opts[] = {
	{ "help",  0, NULL, 'h'},
	{"version",  0, NULL, 'v'},
	{"daemon", 0, NULL, 'd'},
	{"configure", 1, NULL,  'c'},
	{"signal", 1, NULL,  's'},
	{0,0,0,0},
};


static int is_daemon;
static char configure[CONFIG_PATH_LEN];
static char logpath[LOG_PATH_LEN];

static char signal_code[16];
int signal_reload;
int signal_stop;

config_t conf;

FILE *errlog;

void usage();
void init();
void version();
int signaled();
void signal_handler(int signo);
void process_signal(char *signal_code);
FILE *open_logs(char *logpath);
void close_logs(FILE *log);
void write_pidfile(int pid);
void delete_pidfile();
void read_config(config_t *conf);


int main(int argc, char *argv[])
{
	char c;
	int pid;

	init();
	while((c = getopt_long(argc, argv, "hvdc:s:", opts, NULL)) != -1) {
		switch(c) {
		case 'h':
			usage();
			exit(0);
		case 'v':
			version();
			exit(0);
		case 'd':
			is_daemon = DAEMON;
			break;
		case 'c':
			strcpy(configure, optarg);
			break;
		case 's':
			strcpy(signal_code, optarg);
			break;
		case '?':
		default:
			printf("Bad command: %c\n", c);
			exit(1);
		}
	}

	/*Signal running ECR process*/
	if(signaled()){
		process_signal(signal_code);
		exit(0);
	}

	errlog = open_logs(logpath);
	read_config(&conf);

	
	/*Do server*/
	if(is_daemon == DAEMON)
		daemon(0,0);
	write_pidfile(getpid());
	master_process(&conf);

	return 0;
	
}

void usage()
{
	printf("Usage ./ECR [Options]:\n"
	       "\nOptions:\n"
	       "   -h:\t Print this help manual\n"
	       "   -v:\t Print version\n"
	       "   -d:\t Become a daemon\n"
	       "   -c:\t Configuration path\n"
	       "   -s signal:\t Signal ECR process\n");
}

void init()
{
	struct sigaction act;

	strcpy(configure, DEFAULT_CONFIG_PATH);
	strcpy(logpath, DEFAULT_LOG_PATH);
	strcpy(signal_code, "");
	is_daemon = NOTDAEMON;

	/*install signal*/
	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	if(sigaction(SIGHUP, &act, NULL) == -1){
		printf("Install SIGHUP handler failed\n");
		exit(1);
	}
	if(sigaction(SIGINT, &act, NULL) == -1){
		printf("Install SIGINT handler failed\n");
		exit(1);
	}

	signal_reload = SIGNAL_NOT_RELOAD;
	signal_stop = SIGNAL_NOT_STOP;
}

int signaled()
{
	if(strcmp(signal_code, "") != 0)
		return 1;
	return 0;
}

void version()
{
	printf("Enterprise Chat Room Server: Version 1.0\n");
}

void signal_handler(int signo)
{
	switch(signo){
	case SIGHUP:
		signal_reload = SIGNAL_RELOAD;
		break;
	case SIGINT:
		signal_stop = SIGNAL_STOP;
		break;
	default:
		break;
	}
}

void process_signal(char * signal_code)
{
	struct stat s;
	FILE *fin;
	int pid;
	
	if(stat(ECR_PIDFILE_PATH, &s) < 0){
		printf("ECR is not running now!!\n");
		exit(1);
	}

	fin = fopen(ECR_PIDFILE_PATH, "r");
	if(!fin){
		printf("Can't open pid file %s\n", ECR_PIDFILE_PATH);
		exit(1);
	}

	fscanf(fin, "%d", &pid);
	fclose(fin);

	if(strcmp(signal_code, "reload") == 0)
		kill(pid, SIGHUP);
	else if(strcmp(signal_code, "stop") == 0)
		kill(pid, SIGTERM);
	else{
		printf("Bad options(-s): %s\n", signal_code);
		exit(1);
	}
}


FILE *open_logs(char *logpath)
{
	FILE *log;
	if(!logpath)
		return stderr;
	log = fopen(logpath, "w");
	if(!log){
		printf("Open logs failed:  %s\n", logpath);
		return stderr;
	}

	return log;
}

void close_logs(FILE *log)
{
	fclose(log);
}

void write_pidfile(int pid)
{
	FILE *fout;
	fout = fopen(ECR_PIDFILE_PATH, "w");
	fprintf(fout, "%d", pid);
	fclose(fout);
}

void delete_pidfile()
{
	remove(ECR_PIDFILE_PATH);
}

void read_config(config_t *conf)
{
	static char *log_code[] = {"LOG_WARN", "LOG_ERR", "LOG_DIE", NULL};
	FILE *fin;
	char buf[128];
	int code;
	char *tmp;
	int tmp2, i;

	tmp = NULL;
	
	fin = fopen(configure, "r");
	if(!fin){
		printf("Can't open configure %s\n",configure);
		exit(0);
	}
	while(fscanf(fin, "%s", buf) != -1){
		if(buf[0] == '#')
			continue;
		tmp = strchr(buf, '=');
		if(tmp == NULL){
			printf("Bad configure: %s\n", buf);
			exit(1);
		}
		*tmp++ = 0;
		
		if(strcmp(buf, "IP") == 0){
			conf->addr.sin_family = AF_INET;	
			if(*tmp == '*')
				conf->addr.sin_addr.s_addr = htons(INADDR_ANY);
			else
				inet_pton(AF_INET, tmp, &conf->addr.sin_addr);
		}else if(strcmp(buf, "Port") == 0){
		
			sscanf(tmp, "%d", &tmp2);
			conf->addr.sin_port = (unsigned short)tmp2;
		}else if(strcmp(buf, "MaxThread") == 0){

			sscanf(tmp, "%d", &tmp2);
			conf->max_threads = tmp2;
		}else if(strcmp(buf, "LogLevel")){
			
			code = -1;
			for(i = 0; log_code[i] != NULL; i++)
				if(strcmp(log_code[i], tmp) == 0)
					code = i;
				
			if(code == -1){
				printf("Bad Log options: %s\n", tmp);
				exit(1);
			}
			switch(code){
			case 0:
				conf->log_level = LOG_WARN;
				break;
			case 1:
				conf->log_level = LOG_ERR;
				break;
			case 2:
				conf->log_level = LOG_DIE;
				break;
			default:
				break;
			}
		}
	}

	fclose(fin);
	
}
