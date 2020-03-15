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
#include <sys/shm.h> 
#define MAXLEN 15

sem_t mutex;
int *count;
#define FILE_PATH "./temp2"

int main(int argc, char **argv){
	char* name = "shared_object";
	int fd = shm_open(name, O_RDWR|O_CREAT,0666);
	ftruncate(fd, 1024);
	void* ptr;
	ptr = mmap(0, 1024, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);

	char* message = "Hello world!";
	
	sprintf(ptr, "%s", message);

	int pid = fork();
	
	if (pid==0){
		printf("child process %s", (char*)ptr);
	}
	
	shm_unlink(name);
	exit(0);
}
	





