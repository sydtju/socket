#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include<cstdlib>
using namespace std;

int main(){
	void *p[10000];
	clock_t start,end;
	cout<<"runing:"<<endl;
	start=clock();
	for(int j=0;j<10000;++j){
	for(int i=0;i<1000;++i){
		p[i]=malloc(256);
	}	
	for(int k=0;k<1000;++k){
		free(p[k]);
	}
	}
	sleep(1);//clock记录的是cpu时间   所以sleep不会引起计时
	end=clock();
	cout<<"多次申请耗时为"<<end<<"-"<<start<<"="<<(end-start)<<endl;
	start=clock();
	for(int h=0;h<10000;++h){
	for(int i=0;i<10;i++){
		p[i]=malloc(25600);
	}	
	for(int j=0;j<10;j++){
		free(p[j]);
	}
}
	end=clock();
	cout<<"单次申请耗时为"<<end<<"-"<<start<<"="<<(double)(end-start)<<endl;
	return 0;
}
