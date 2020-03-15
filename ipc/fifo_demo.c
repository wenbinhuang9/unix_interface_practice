

#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#define MAXLEN 15

#define FIFO1 "/tmp/fifo.2"

int main(int argc, char **argv){
	if (mkfifo(FIFO1, 0666)==-1){
		printf("open fifo error\n");
	}
	pid_t childpid;
	
	char buff[MAXLEN];
	if ((childpid = fork()) == 0) {
		int write_fd = open(FIFO1, O_WRONLY);
		printf("begin writing\n");
		write(write_fd, "hello", 6);	
		exit(0);
	}
	
	int read_fd = open(FIFO2, O_RDONLY);

	waitpid(childpid, NULL, 0);
	printf("begin reading");
	read(read_fd, buff, MAXLEN);
	printf("Father process|message is %s\n", buff);
	exit(0);
	
}




