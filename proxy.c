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


    //create our host server to wait for clients
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("ERROR, cannot open hosting socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(srcPort);
    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Cannot bind src port");
    }
    listen(sockfd, 5);
    clilen - sizeof(cli_addr);

    //create the remote host
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(dstPort);
    serverAddr.sin_addr.s_addr = inet_addr(server);
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));


    //wait for connection
    //loop to wait for connection and start thread should be here
    while(true){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newsockfd < 0){
            error("error on accepting new client")
        }
        //TODO, call thread
    }

    //thread should start here
    //should be passed the new client

    //create a new connection to server using server and dstPort
    addr_size = sizeof(serverAddr);
    connect(newsockfd, (struct sockaddr *) &serverAddr, addr_size);

    //check for input with select function, and pass through to the right socket.
    
    //loop through and output based on user input




}