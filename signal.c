#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void timeout(int sig){
	if(sig==SIGALRM)	fprintf(stdout,"time out!\n");
	alarm(2);/* alarm也称为闹钟函数，alarm()用来设置信号SIGALRM在经过参数seconds指定的秒数后传送给目前的进程。如果参数seconds为0，则之前设置的闹钟会被取消，并将剩下的时间返回。要注意的是，一个进程只能有一个闹钟时间，如果在调用alarm之前已设置过闹钟时间，则任何以前的闹钟时间都被新值所代替。
*/
}
void keycontrol(int sig){
 	if(sig==SIGINT) fprintf(stdout,"control +c process!\n");
}
int main(int argc,char *argv[]){
	int i;
	signal(SIGALRM,timeout);//注册信号处理函数
	signal(SIGINT,keycontrol);//注册信号处理函数 调用信号的主体是操作系统，但进程处于休眠状态无法调用函数 
//因此  为了调用信号处理函数 将会唤醒由于调用sleep函数而进入阻塞状态的进程   进程一旦被唤醒 不会再次进入睡眠状态。
	alarm(2);
	
	for(i=3;i>0;--i)
	{
	fprintf(stdout,"wait ........\n");
	sleep(100);//
	}
	return 0;
}
