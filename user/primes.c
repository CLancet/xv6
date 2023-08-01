#include "kernel/types.h"
#include "user/user.h"
#define MSGSIZE 36
#define PRI '1'
#define NOtPRI '0'

void prime(int pipe_read, int pip_write)
{
    char buf[MSGSIZE];
    int value = 0;
    read(pipe_read, buf, MSGSIZE);
    for (int i = 0; i < MSGSIZE; i++)
    {
        if (buf[i] == PRI)
        {
            value = i; // 此处的i必定为素数
            break;
        }
    }
    if(value==0){
        exit(0);
    }
    printf("prime %d\n", value);
    buf[value] = NOtPRI;

    for (int i = 0; i < MSGSIZE; ++i)
    {
        if (i % value==0) 
        {
            buf[i] = NOtPRI;
        }
    }

    int pid = fork();
    if (pid > 0)// 子进程
    { 
        write(pip_write, buf, MSGSIZE);
    }
    if (pid == 0)
    { // 孙子进程
        prime(pipe_read,pip_write);
    }
}
int main(int argc, char *argv[])
{

    int fd[2];
    pipe(fd);

    int pid = fork();

    char nums[MSGSIZE];
    for (int i = 0; i < MSGSIZE; i++)
    {
        nums[i] = PRI;
    }
    if (pid > 0)
    { // 父进程
        nums[0] = NOtPRI;
        nums[1] = NOtPRI;
        write(fd[1], nums, MSGSIZE);
        wait(0);
    }
    if (pid == 0)
    { // 子进程
        prime(fd[0], fd[1]);
        wait(0);
    }
    exit(0);
}
