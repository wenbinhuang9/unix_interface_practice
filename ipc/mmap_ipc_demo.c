#include <semaphore.h>
#include <sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/mman.h> 
#define MAXLEN 15

sem_t mutex;
int *count;
#define FILE_PATH "./temp2"
int main(int argc, char **argv){
	sem_init(&mutex, 0, 1);
	pid_t childpid;
	int zero = 0;
	int mmap_fd = open(FILE_PATH,O_RDWR);
	if (mmap_fd <0){
		printf("open file fail \n");
	}
	write(mmap_fd, &zero, sizeof(int));
	char buffer[10];
	if(read(mmap_fd, buffer, 10) < 0){
		printf("read faili \n");
	}
	printf("content in file is %s \n",buffer);

	count = mmap(NULL, sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED,mmap_fd,0);
	close(mmap_fd);
	printf("count %d", count);
	if (count == MAP_FAILED){
		printf("count is null \n");
		exit(0);
	}
	if (fork() == 0) {
		for(int i =0; i<=10;i++) {
			sem_wait(&mutex);
			printf("child %d \n", 1);		
			sem_post(&mutex);
		}
	}
	for(int i =0; i<=10;i++) {
		sem_wait(&mutex);
		printf("parent %d \n", (*count));		
		sem_post(&mutex);
	}

	exit(0);
}




