#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

int main(int argc, char** argv){
	struct sockaddr_in remoteaddr;

	int clisock;

	char buffer[1024];
	int buff_size = 1024;

	if((clisock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket() error:\n");
		exit(1);
	}
	
	int i;
	for(i = 1; i < argc; i++){
		remoteaddr.sin_family = PF_INET;
		remoteaddr.sin_port = htons(39872);
		remoteaddr.sin_addr.s_addr = inet_addr(argv[i]);
		
		connect(clisock, (struct sockaddr *) &remoteaddr, sizeof(remoteaddr));

		read(clisock, buffer, buff_size);
		
		printf("%s: %s\n", argv[i], buffer);
		
		close(clisock);		
	}
	
	return 0;
}
