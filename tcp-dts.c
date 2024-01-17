#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<string.h>
main(int argc, char* argv[]){
	int sid, sid1, rval;
	struct sockaddr_in s, c;
	time_t t = time(0);
	char smsg[30];
	strcpy(smsg, ctime(&t));
	int clen;
	system("clear");
	if(argc < 3){
		printf("\nUSAGE: %s IP_ADDRESS PORT #\n", argv[0]);
		exit(0);
	}
	sid = socket(AF_INET, SOCK_STREAM, 0);
	if(sid == -1){
		perror("SOCK-CRE-ERR:");
		exit(1);
	}
	printf("Socket created\n");
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr(argv[1]);
	s.sin_port = htons(atoi(argv[2]));
	rval = bind(sid, (struct sockaddr*)&s, sizeof(s));
	if(rval == -1){
		perror("BIND-ERR:");
		close(sid);
		exit(1);
	}
	rval = listen(sid, 5);
	if(rval == -1){
		perror("LISTEN-ERR:");	
		close(sid);
		exit(1);
	}
	clen = sizeof(c);
	sid1 = accept(sid, (struct sockaddr*)&c, &clen);
	strcpy(smsg, ctime(&t));
	rval = send(sid1, smsg, sizeof(smsg), 0);
	if(rval == -1){
		perror("MSG-SND-ERR:");
		exit(1);
	}
	close(sid);
	close(sid1);
}
