#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
//pipe
/* .管道是单向的、先进先出的、无结构的、固定大小的字节流，它把一个进程的标准输出和另一个进程的标准输入连接在一起。写进程在管道的尾端写入数据，读进 程在管道的道端读出数据。数据读出后将从管道中移走，其它读进程都不能再读到这些数据。管道提供了简单的流控制机制。进程试图读空管道时，在有数据写入管 道前，进程将一直阻塞。同样，管道已经满时，进程再试图写管道，在其它进程从管道中移走数据之前，写进程将一直阻塞。管道主要用于不同进程间通信。*/
/* 无名管道 只能用于有亲戚关系的进程之间  而且是单工的  如果想要反向使用的是必须读完里面的内容   一般要求管道的缓存为512字节以上*/
#define BUF_SIZE 100

int main(int argc,char *argv[]){
	int fds1[2];
	int fds2[2];
	char str1[]="who am i?";
	char str2[]="this is answer";
	char buf[BUF_SIZE];
	pid_t pid;
	pipe(fds1);
	pipe(fds2);
	pid=fork();
	if(pid==0)
	{
		write(fds1[1],str1,sizeof(str1));
		read(fds2[0],buf,BUF_SIZE);
		fprintf(stdout,"child is recv %s\n",buf);
	}
	else{
		read(fds1[0],buf,BUF_SIZE);
		fprintf(stdout,"father recv %s\n",buf);
		write(fds2[1],str2,sizeof(str2));
		sleep(2);
	}
	return 0;
}
