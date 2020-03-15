

#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAXLEN 15

int main(int argc, char **argv){
	int pipe1[2], pipe2[2];
	pid_t childpid;
	
	pipe(pipe1);
	pipe(pipe2);
	char buff[MAXLEN];
	if ((childpid = fork()) == 0) {
		close(pipe1[1]);
		close(pipe2[0]);
		write(pipe2[1], "hello", 6);	
		exit(0);
	}
	close(pipe1[0]);
	close(pipe2[1]);
	
	waitpid(childpid, NULL, 0);
	read(pipe2[0], buff, MAXLEN);
	printf("Father process|message is %s\n", buff);
	exit(0);
	
}




