
 //tju
//shaoyadong
//linux code
//wait()   fork()
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void processchild1(void){
char a;
fprintf(stdout,"this is precesschild1!\n please input char:a=");
a=getchar();
}
void start(void){
fprintf(stdout,"this is start! here .....\n");
}
int main(int argc,char *argv[]){
        char b;
        start();
        pid_t child_pid=fork();
        if(child_pid==-1) fprintf(stdout,"create process is failure!\n");//失败的话  返回-1
        else if(child_pid==0) processchild1();
        else{
                fprintf(stdout,"this is fatherprocess!child id=%d,father id= %d\n",child_pid,getppid());
                fprintf(stdout,"please input a=");
                b=getchar();
        }
        wait(child_pid,NULL,0);//不会出现僵尸进程  如果有多个子进程 最好是使用waitpid 将每个子进程都进行wait
        return 0;
}
  
