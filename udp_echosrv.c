#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
main(int argc,char * argv[])
{
	int sockid,rval,clen;
	char buffer[20];
	struct sockaddr_in s,c;
	if(argc<3){
		printf("\nUSAGE:%s IP_ADDRESS PORT #\n",argv[0]);
		exit(0);
	}
	sockid = socket(AF_INET,SOCK_DGRAM,0);
	if(sockid == -1){
		perror("SOCK-CRE-ERR");
		exit(1);
	}
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr(argv[1]);
	s.sin_port = htons(atoi(argv[2]));
	printf("socket created\n");
	rval = bind(sockid,(struct sockaddr *)&s,sizeof(s));
	if(rval == -1){
		perror("BIND-ERR");
		close(sockid);
		exit(1);
	}
	printf("socket binded\n");
	clen = sizeof(c);
	rval = recvfrom(sockid,buffer,sizeof(buffer),0,(struct sockaddr *)&c,&clen);
	if(rval == -1){
		perror("MSG-RCV-ERR");
		exit(1);
	}
	printf("\nRequest received\nRequest message is :%s\n",buffer);
	strcat(buffer," Juveriya");
	rval = sendto(sockid,buffer,sizeof(buffer),0,(struct sockaddr *)&c,clen);
	if(rval == -1){
		perror("MSG-SND-ERR");
		exit(1);
	}
	printf("\nResponse sent successfully\n");
	close(sockid);
}
