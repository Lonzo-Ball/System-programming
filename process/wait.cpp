#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#if 0
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
返回值：
     当正常返回时 waitpid 返回收集到的子进程的 id
     如果设置了 WNOHANG 而调用中 waitpid 发现没有已退出的子进程可收集，则返回 0
     如果调用中出错，则返回 -1
pid: 
     pid=-1 等待任一个子进程 与 wait 等效
     pid>0 等待其进程 id 与 pid 相等的子进程
status:
     WIFEXITED(status) 如果子进程正常终止 则为真
     WEXITSTATUS(status) 若  WIFEXITED 非零 提取子进程退出码
options:
     WNOHANG:若 pid 指定的子进程没有结束，则 waitpid 函数返回 0 不予以等待 若正常结束 返回该进程的 id
#endif

int main()
{
	pid_t pid;

	pid = fork();
	if(pid == -1){
		std::cout<< "fork faild!" <<std::endl;
		exit(1);
	}
	else if(pid == 0){
		std::cout<< "child process" <<std::endl;
		std::cout<< "child pid: " << getpid() <<std::endl;

		sleep(10);
		exit(-1);
	}
	else{
		std::cout<< "parent process" <<std::endl;

		int status = 0;
		//参数：输出型参数  由操作系统填充 获取子进程退出状态 不关心则可以设置成 NULL
		pid_t pid_ = wait(&status);
		if(pid_ == -1)
		{
			std::cout<< "parent process wait faild!" << std::endl;
		}	
		if(pid > 0 && (status & 0x7F) == 0)  //正常终止
		{
			std::cout << "child process pid: " << pid_ <<std::endl;
			printf("child process ststus: %d\n",(status>>8)&(0xFF));		
		}
		else if(pid > 0)  //异常退出
		{
			printf("sig code: %d\n",status&(0x7F));
		}
	}
	return 0;
}
