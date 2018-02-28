#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int main(int argc, char** argv){
	
	struct sockaddr_in serveraddr;
 	struct sockaddr_in clientaddr;

	int sersock, consock;
	int len = sizeof(clientaddr);
	//char IP_ADDRESS = "192.168.254.255"; //might be wrong
	int port;
	
	if((sersock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket() eerroer:\n");
		exit(1);
	}

	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(39872);

	/*Only one of the following, must figure out which*/
	//serveraddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sersock, (struct sockaddr *) &serveraddr, sizeof(serveraddr));	
	listen(sersock, 10);

	while(1){
		
		consock = accept(sersock, (struct sockaddr *) &clientaddr, &len);
		if (!fork()){
			char buffer[1024];
			int buff_size = 1024;

			FILE *uptime_file = popen("uptime", "r");
			fgets(buffer, buff_size, uptime_file);
			pclose(uptime_file);
			
			write(consock, buffer, buff_size);
	
			close(consock);		
		}
		else{
			close(consock);
		}	
	}
	close(sersock);

	return 0;
}
