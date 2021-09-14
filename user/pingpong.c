#include <kernel/types.h>
#include <user/user.h>

int main(){

    int p1[2];
    int p2[2];
    char buffer[] = {'X'};
    long length = sizeof(buffer);
    pipe(p1);
    pipe(p2);
    if(fork() == 0){
        close(p1[1]);
        close(p2[0]);
	if(read(p1[0], buffer, length) != length){
	    printf("a--->b read error!");
	    exit(1);
	}
	printf("%d: received ping\n", getpid());
	if(write(p2[1], buffer, length) != length){
	    printf("a<---b write error!");
	    exit(1);
	}
        exit(0);
    }
    
    close(p1[0]);
    close(p2[1]);
    if(write(p1[1], buffer, length) != length){
        printf("a--->b write error!");
        exit(1);
    }
    if(read(p2[0], buffer, length) != length){
	printf("a<---b read error!");
	exit(1);
    }
    printf("%d: received pong\n", getpid());
    wait(0);
    exit(0);
}
