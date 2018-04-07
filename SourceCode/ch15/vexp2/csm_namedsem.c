/* csn_namedsem.c 消费者进程
* 本程序需要结合pro_namedsem.c 生产者进程一起工作
* gcc -o csm_namedsem  csn_namedsem.c -lpthread
*生产者向一个文件写入消息，消费者从该文件中读取消息；当消费者进程运行时如果没有接到通知就不从文件读取消息，并阻塞自己，直到接到生产者的消息才被唤醒读取文件中的信息并显示出来
*在测试时，可以使用不同的顺序来先后运行生产者和消费者进程，观察实验现象；也可以通过添加&使某个进程在后台运行，观察实验现象
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#include <semaphore.h> 
#include <fcntl.h>
#include <errno.h>
//创建模式权限
#define FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SEM_INFO   "info"  /*  信号量info用于消息通知 */
#define BUFFER_SIZE 512
char buffer[BUFFER_SIZE];
int main(int argc,char **argv)
{
	sem_t *info; /* 信号量info用于传递消息*/
	int fd,valp;
	int len;
       //创建NAMED信号量
	if((info = sem_open(SEM_INFO,O_CREAT,FILE_MODE,0)) == SEM_FAILED)
	//if((info = sem_open(SEM_INFO,0)) == SEM_FAILED)
	{
	      perror("sem_open() error");
	      exit(-1);
	}
	sem_getvalue(info,&valp);
	printf("csm:the sem value is %d\n",valp);    
	sem_wait(info);
        if((fd=open("test", O_RDONLY))==-1) 
	{ 
	      printf("Open %s Error\n",argv[0]); 
              exit(-1); 
	} 
	len = read(fd, buffer, 512);
	printf("this is consumer %d --->>>",getpid());
	printf("%s\n",buffer);
	close(fd);
	sem_close(info);	
	//sem_unlink(SEM_INFO);	

	return 0;
}
