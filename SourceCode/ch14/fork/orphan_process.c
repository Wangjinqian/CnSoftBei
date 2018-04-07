//orphan_process.c
//演示孤儿进程的生成
//编译命令：$ gcc -o orphan_process  orphan_process.c
//运行命令：$ ./orphan_process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
        pid_t pid;
        if((pid=fork())==-1)
                perror("fork");
        else if(pid==0)
        {
                printf("child : pid=%d,ppid=%d\n",getpid(),getppid());//输出子进程pid以及其父进程pid，此时父进程未退出
                sleep(2);//休眠两秒等待父进程先退出
                printf("child : pid=%d,ppid=%d\n",getpid(),getppid());//请注意此次输出子进程的ppid，与上一次的差异，此时父进程已退出
        }
        else
        {
                printf("father : pid=%d,ppid=%d\n",getpid(),getppid());
                sleep(1);
                exit(0);//休眠一秒后直接退出，未使用wait调用。此时子进程相当于被“无情的抛弃了”
        }
}
