#include"kernel/types.h"
#include"user/user.h"
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(2,"sleep.c: wants 1 parameters, get %d parameter(s).\n",argc-1);
        exit(1);
    }
    int time;
    time = atoi(argv[1]);//user/ulib.c中定义的的字符串转数字函数
    // If time == 0, return ASAP.
    if (time <= 0) exit(1);
    sleep(time);
    exit(0);
}
