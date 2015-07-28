#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define MAX 100
void err_handing_exit(const char *str){
	fprintf(stdout,"%s",str);
	fprintf(stdout,"is error!\n");
	exit(1);
}
int main(int argc,char *argv[]){
	struct sockaddr_in sock_serv_addr,sock_client_addr;
	int serv_sock;
	int str_len;
	socklen_t  clint_adr_sz;
	char message[MAX];
	if(argc!=2)
		err_handing_exit("the parameter ");
	serv_sock=socket(PF_INET,SOCK_DGRAM,0);
	if(serv_sock==-1) err_handing_exit("the socket create ");
	else
		fprintf(stdout,"\ncreate socket is success!\n");
	memset(&sock_serv_addr,0,sizeof(sock_serv_addr));
	sock_serv_addr.sin_family=AF_INET;
	sock_serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	sock_serv_addr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock,(struct sockaddr *)&sock_serv_addr,sizeof(sock_serv_addr))==-1) err_handing_exit("bind() is ");
	else
		fprintf(stdout,"bind is success!\n");
	while(1){
		clint_adr_sz=sizeof(sock_client_addr);
		str_len=recvfrom(serv_sock,message,MAX,0,(struct sockaddr*)&sock_client_addr,&clint_adr_sz);
		if(str_len==-1) err_handing_exit("recvfrom is");
		else
			fprintf(stdout,"recvfrom is success!\n");
		sendto(serv_sock,message,str_len,0,(struct sockaddr*)&sock_client_addr,clint_adr_sz);
	}
	close(serv_sock);
	return 0;
}
