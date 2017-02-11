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
#include <pthread.h>
#include <ctype.h>

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

/*this will be the threaded option
* will pass all input to output, and print all input to concole for shits
* will take socket numbers and the data direction string
*/
void ongoingsocket(int input, int output, char *direct)
{
    //buffers for this read/write
    char inputbuffer[1024];

    while(0){

        //get input from socket
        recv(input, inputbuffer, 1024, 0);


        //print operation here
        if (logOptions = 1) {
            printf("%s%s\n",direct, outputstring);
        }
        else if (logOptions = 2) {
            int i;
            printf(direct);
            //loop to check if ascii
            for(i = 0; inputbuffer[i] != '\0'; i++){
                if(isascii(inputbuffer[i])){
                    printf(inputbuffer[i]);
                }else{
                    printf('.');
                }
            }
        }
        else if (logOptions = 3) {

        }
        else if (logOptions = 4) {
            
        }

        bzero(inputbuffer, sizeof(inputbuffer));

        //send to output socket
        write(output, inputbuffer, sizeof(inputbuffer));
    }
}


int main(int argc, char *argv[])
{
    const char* incoming = "<----";
    const char* outgoing = "---->";
    char tempstr[7];
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
    struct sockaddr_in serv_addr, cli_addr;

    //input socket variables
    int sockfd, newsockfd, srcPort, sockcd;
    //output socket variables
    char server[1024];
    int dstPort, addr_size;
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
        if (strncmp(tempstr, "-raw ", 5) == 0) {
            logOptions = 1;
        }
        else if (strncmp(tempstr, "-strip ", 7) == 0) {
            logOptions = 2;
        }
        else if (strncmp(tempstr, "-hex ", 5) == 0) {
            logOptions = 3;
        }
        else if (strncmp(tempstr, "-autoN ", 7) == 0) {
            logOptions = 4;
        }
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
    serveraddr_size = sizeof(serverAddr);

    //wait for connection
    //loop to wait for connection and start thread should be here
    while(0){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newsockfd < 0){
            error("error on accepting new client");
        }
        //create a new socket to communicate with server
        sockcd = socket(PF_INET, SOCK_STREAM, 0);
        connect(sockcd, (struct sockaddr *) &serverAddr, &serveraddr_size);
        //TODO, call thread
        //currently just calling the function
        //THIS IS NOT THREADED!!!!!!
        ongoingsocket(newsockfd, sockcd, outgoing);
        ongoingsocket(sockcd, newsockfd, incoming);
    }
}
