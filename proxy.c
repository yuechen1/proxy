#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>

/*
*   Yue Chen                10065082    T03
*   Yin-Li (Emily) Chow     10103742    T01
*
*/

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    //buffers for reading from sockets and constants for printing related to buffer
    const char* incoming = "<----";
    const char* outgoing = "---->";
    char inputbuffer[1024];
    char outputbuffer[1024];
    char *tempstr;
    tempstr = (char *) malloc(5);
    /*
    * 0 is nothing
    * 1 is -raw
    * 2 is -strip
    * 3 is -hex
    * 4 is -autoN
    */
    int logOptions = 0;
    int autoN;

    //socket variables
    struct sockaddr_in serv_addr, cli_addr, serverAddr;

    //input socket variables
    int sockfd, newsockfd, srcPort;
    //output socket variables
    char server[1024];
    int dstPort;
    socklen_t clilen, serveraddr_size;

    //get port numbers and address from argv
    if(argc < 4 || argc > 5){
        fprintf(stderr, "ERROR, invalid arguments\n");
        exit(1);
    }
    else if(argc == 4){
        srcPort = atoi(argv[1]);
        strcpy(server, argv[2]);
        dstPort = atoi(argv[3]);
    }
    else if(argc == 5){
        strcpy(tempstr, argv[1]);
        srcPort = atoi(argv[2]);
        strcpy(server, argv[3]);
        dstPort = atoi(argv[4]);
    }

    //wait for connection
    //loop to wait for connection and start thread should be here
    while(true){
        
    }

    //thread should start here

    //create a new connection to server using server and dstPort

    //loop through and output based on user input




}