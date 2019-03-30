#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	pid_t pid;

	pid = fork();
	if(pid == -1)
	{
		std::cout<< "fork failed!" <<std::endl;
		exit(1);
	}else if(pid == 0){
		std::cout << "child process" << std::endl;
		std::cout << "child process id: " << getpid() <<std::endl;
		
		sleep(10);
		exit(-1);
	}else{
		std::cout<< "parent process" <<std::endl;
		
		int status;
		pid_t ret;
		//pid_t ret = waitpid(-1,&status,0);
		do
		{
			ret = waitpid(-1,&status,WNOHANG);
			if(ret == -1)
			{
				std::cout<< "waitpid failed" <<std::endl;
				exit(2);
			}

			if(ret == 0)
			{
				sleep(1);
				std::cout<< "child process running!" <<std::endl;
			}
		}while(ret == 0);

		if(WIFEXITED(status)){
			std::cout<< "child process id: " << ret <<std::endl;
			std::cout<< "wait child process success,return code: " << WEXITSTATUS(status) <<std::endl;
		}
		else{
			std::cout<< "wait failed!" <<std::endl;
		}

	}
	return 0;
}
