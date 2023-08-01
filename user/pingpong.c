#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	int parent_to_child[2]; // 父到子管道
	int child_to_parent[2]; // 子到父的管道
	// 0 为读端，1为写端
	char message[1]; // 父子进程传递的消息
	
	pipe(parent_to_child); 
	pipe(child_to_parent); 
	
	if(fork() > 0){ // 当前进程为父进程
		close(parent_to_child[0]); 
		close(child_to_parent[1]); //  关闭p-c的读c-p的写
		write(parent_to_child[1], " ", 1); // 写入一个空格，表示发送一个ping
		read(child_to_parent[0], message, 1); // 从c-p的读读取一个字符，表示接受一个pong
		printf("%d: received pong\n", getpid()); 
		close(parent_to_child[1]); 
		close(child_to_parent[0]); 
		exit(0); 
	}else{ 
		close(parent_to_child[1]); 
		close(child_to_parent[0]); 
		read(parent_to_child[0], message, 1); 
		printf("%d: received ping\n", getpid()); 
		write(child_to_parent[1], " ", 1);
		close(parent_to_child[0]); 
		close(child_to_parent[1]); 
		exit(0); 
	}
}
