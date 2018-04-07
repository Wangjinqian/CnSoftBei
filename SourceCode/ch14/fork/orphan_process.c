//orphan_process.c
//��ʾ�¶����̵�����
//�������$ gcc -o orphan_process  orphan_process.c
//�������$ ./orphan_process

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
                printf("child : pid=%d,ppid=%d\n",getpid(),getppid());//����ӽ���pid�Լ��丸����pid����ʱ������δ�˳�
                sleep(2);//��������ȴ����������˳�
                printf("child : pid=%d,ppid=%d\n",getpid(),getppid());//��ע��˴�����ӽ��̵�ppid������һ�εĲ��죬��ʱ���������˳�
        }
        else
        {
                printf("father : pid=%d,ppid=%d\n",getpid(),getppid());
                sleep(1);
                exit(0);//����һ���ֱ���˳���δʹ��wait���á���ʱ�ӽ����൱�ڱ�������������ˡ�
        }
}