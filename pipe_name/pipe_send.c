#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#define BUF_SIZE  80
int main(int argc,char *argv[]){
	int infile;
	int count=1;
	char buf[BUF_SIZE];
	if(mkfifo("myfifo",0777)<0) //后一个参数是name-pipe的权限
	{
		if(errno==EEXIST)//管道已经存在
		{
			fprintf(stdout,"the fifo exist.\n");
		}
		else{
			fprintf(stdout,"create myfifo is failure!\n");
			exit(-1);
		}
	}
	else{
		fprintf(stdout,"create fifo is success! \n");
	}
	infile=open("myfifo",O_WRONLY);
	if(infile<0) {fprintf(stdout,"open is error!\n");exit(-1);}
	printf("input message:");//居然打印不出来  神奇！！
	while((count=read(0,buf,BUF_SIZE))>0)
	{
		write(infile,buf,count);
		printf("input message:");
		memset(buf,0,BUF_SIZE);
	}
	close(infile);
	return 0;
}
