#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define MAX 100
void err_handing_exit(const char *str){
	fprintf(stdout,"\n%s",str);
	fprintf(stdout," is error!\n");
	exit(1);
}
int main(int argc,char *argv[]){
	struct sockaddr_in client_addr,serve_addr;
	socklen_t client_addr_len;
	int sockclient;
	int str_len;
	char message[MAX];
	
	if(argc!=3) err_handing_exit("the parameter");
	sockclient=socket(PF_INET,SOCK_DGRAM,0);
	if(sockclient==-1) err_handing_exit("create socket ");
	else
		fprintf(stdout,"\ncreate socket is success!\n");
	memset(&serve_addr,0,sizeof(serve_addr));
	serve_addr.sin_family=AF_INET;
	serve_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serve_addr.sin_port=htons(atoi(argv[2]));
	while(1){
		fprintf(stdout,"\ninput message:");
		fscanf(stdin,"%s",message);
		str_len=strlen(message);
		if(str_len==1&&(message[0]=='q'||message[0]=='Q')) break;
		sendto(sockclient,message,str_len,0,(struct sockaddr*)&serve_addr,sizeof(serve_addr));
		client_addr_len=sizeof(client_addr);
		str_len=recvfrom(sockclient,message,MAX,0,(struct sockaddr*)&serve_addr,NULL);
		message[MAX]=0;
		fprintf(stdout,"message from servers:%s\n",message);
	}
	close(sockclient);
	return 0;
}
