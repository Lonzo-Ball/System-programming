#include <iostream>
#include <stdlib.h>
#include <unistd.h>

int glob = 100;
int main()
{
	pid_t pid;
	
	pid = vfork();
	if(pid == -1){
		std::cout << "vfork failed!" <<std::endl;
		exit(1);
	}else if(pid == 0){
		glob = 200;
		std::cout << "in child process glob = " << glob <<std::endl;

		exit(2);
	}else{
		glob = 300;
		std::cout << "in parent process glob = " << glob <<std::endl;
	}

	return 0;
}
