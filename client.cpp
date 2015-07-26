#include<sys/socket.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
void err_handing_exit(const char * message){
	fprintf(stdout,"%s \n",message);
	exit(1);
}
int main(int argc,char *argv[]){
  int sock;
  struct sockaddr_in serv_addr; 
  char message[100];
  int str_len;
  int counter;
  if(argc!=3) err_handing_exit("the parameter is error!\n");
  // 申请socket
  sock=socket(PF_INET,SOCK_STREAM,0);
  if(sock==-1) 
   err_handing_exit("the socket is error!\n");
 //地址初始化
  memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
  serv_addr.sin_port=htons(atoi(argv[2]));
 //
  if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr ))==-1)
	err_handing_exit("connect() error!\n");
//  str_len=read(sock,&counter,4);
//  fprintf(stdout,"%d  ",counter);
  str_len=read(sock,message,sizeof(message)-1);
  if(str_len==-1) err_handing_exit("read is error!\n");
  counter=*((int*)message);
  fprintf(stdout,"message from server:%3d:%s  length=%d \n",counter,message+4,str_len);
//  sleep(1);
 // if(counter==1000) break;
  close(sock);
  return 0;
}
