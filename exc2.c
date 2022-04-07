#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>


void sig_handler(int signum)
{
	int i=5;
	int j=0;
	int k;
	switch (signum) {
		case SIGCHLD:
			printf("we got signal number 1\n");
			fflush(stdout);
			raise(SIGUSR1);  //signal 2
		case SIGUSR1: //raise
			printf("we got signal number 2\n");
			k=i/j;   //signal 3
		case SIGFPE:  //divide by zero
			printf("we got signal number 3\n");
            char * st="trying";
            st[2]='e';  //signal 4
			exit(1);
        case SIGSEGV:
            printf("we got signal number 4\n");
            asm(".byte 0x16");  //signal 5
            exit(1);
        case SIGILL:
            printf("we got signal number 5\n");
            abort();  //signal 6
            exit(1);
        case SIGABRT:
            printf("we got signal number 6\n");
            fopen("nothing","r");   //signal 7
            // exit(1);
        case SIGIO:
            printf("we got signal number 7\n");
            alarm(1);   //signal 8
            while(1){};
            exit(1);   
        case SIGALRM: 
            printf("we got signal number 8\n");
            exit(1);
		}
}

void sig_handler2(int signum)
{
	printf("I am in sighandler2222\n");
	fflush(stdout);
	exit(1);
}

int main()
{
	int status;
	signal (SIGCHLD, sig_handler);
	signal (SIGUSR1, sig_handler);
	signal (SIGFPE, sig_handler);
    signal (SIGALRM, sig_handler);
    signal (SIGILL, sig_handler);
    signal (SIGTSTP, sig_handler);
    signal (SIGSEGV, sig_handler);
    signal (SIGIO, sig_handler);
    signal (SIGABRT, sig_handler);
    
	if (!(fork())) {
		exit(1);  //signal 1
	}
	wait(&status);

}