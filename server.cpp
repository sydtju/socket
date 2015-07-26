//name:socket.c
//version:v1.0.0
//author:shaoyadong
//tju
//ANSI C
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
struct data{
int num;
char str[35];
};

void err_handing_exit(const char *str){
 fprintf(stdout,"%s",str);
 fprintf(stdout," is error!\n");
 exit(1);
}
void start(){
fprintf(stdout,"start..........ok!\n");
}
int main(int argc,char *argv[]){
	start();
	int serv_sock;
        int clint_sock;
 	struct sockaddr_in serv_addr;
	struct sockaddr_in clint_addr;
	socklen_t clint_add_size;
	int counter=0;
	int ctemp=1000;
	struct data tdata={0,"hello this server! version 1.0.0"};
	// 参数判断
	if(argc!=2) err_handing_exit("parameter");
	//申请socket
	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock==-1) err_handing_exit("socket initial");
	//地址设置 设置需要监听的地址和端口
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	//把地址绑定到socket上面
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1) err_handing_exit("bind()");
	//监听端口
	fprintf(stdout,"linten port %s ..........\n",argv[1]);
	while(ctemp--){
	tdata.num=counter;
	if(listen(serv_sock,5)==-1) err_handing_exit("listen() ");
	clint_add_size=sizeof(clint_addr);
	clint_sock=accept(serv_sock,(struct sockaddr*)&clint_addr,&clint_add_size);
	if(clint_sock==-1) err_handing_exit("accept()");
	
	fprintf(stdout," %3d :transmit message:hello this server! version 1.0.0 length=%d\n ",counter++,sizeof(tdata));
		write(clint_sock,&tdata,sizeof(tdata));
	//	write(clint_sock,message,sizeof(message));
	close(clint_sock);
	}

	close(serv_sock);
	return 0;
}
