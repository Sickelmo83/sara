#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/un.h>
#include <unistd.h>

int slen(const char* str){
	int i = 0;

	while (*str){ str++; i++; }

	return i;
}

void die(const char* e, ...){
	fprintf(stdout, "sarasocker: %s\n", e);
	exit(1);
}

int main(int argc, char* argv[]){
	int sfd, n;
	struct sockaddr saddress = {AF_UNIX, "/tmp/sarassock"};

	if (argc != 2)
		die("please provide one argument!");
	if ( (sfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		die("failed to create socket!");
	if (connect(sfd, &saddress, sizeof(saddress)) < 0)
		die("failed to connect to socket!");
	if (send(sfd, argv[1], slen(argv[1])+1, 0) < 0)
		die("failed to send to socket!");

	close(sfd);

	return 0;
}