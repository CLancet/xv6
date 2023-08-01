#include "kernel/types.h"
#include"kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"
#include"kernel/fs.h"
#define MESSAGESIZE 16// 标准化输入的最长长度，可根据情况设定
int main(int argc, char *argv[])
{
  sleep(10);  
  char buf[MESSAGESIZE];
  read(0,buf,MESSAGESIZE);// 获取前一个命令的标准化输出，即下一个命令的标准化输入
  
  char *xargv[MESSAGESIZE];
  int xargc=0;

  for(int i=1;i<argc;i++){
    xargv[xargc] = argv[i];
    xargc++;
  }// 将Xargs命令后的参数放在xargvs中

  char *p =buf;
  for(int i=0;i<MESSAGESIZE;i++){
    if(buf[i] =='\n'){
      int pid = fork();
      if(pid>0){
        p = &buf[i+1];
        wait(0);
      }
      else{
        buf[i] = 0;
        xargv[xargc++] = p;
        xargv[xargc++]=0;

        exec(xargv[0] ,xargv);
        exit(0);
      }
    }
  }
  wait(0);
  exit(0);
}
