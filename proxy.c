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
#include <netdb.h>
#include <time.h>


/*
*   Yue Chen                10065082    T03
*   Yin-Li (Emily) Chow     10103742    T01
*
*/
//structure for passing arguments to thread
struct threadstuff {
    int input;
    int output;
    char *direct;
    int logOptions;
    int autoN;
};

struct threadbase{
    pthread_t source, dest;
    int ssocket, dsocket;
    struct threadstuff params1, params2;
};


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

/*this will be the threaded option
* will pass all input to output, and print all input to console for shits
* will take socket numbers and the data direction string
*/
void *ongoingsocket(void *params)
{
    struct threadstuff *themparams = params;
    //buffers for this read/write
    char inputbuffer[1024];
    int i;
    char hexbuffer[11]; //a buffer for holding 10 characters for the string part
    int N = themparams->autoN;
    int n;



    while(1){

        //get input from socket
        n = read(themparams->input, inputbuffer, sizeof(inputbuffer));
		if (n > 0) {
			//print operation here
			if(themparams->logOptions == 0){

			}
			else if (themparams->logOptions == 1) {   //-raw
				printf("%s%s\n",themparams->direct, inputbuffer);
			}
			else if (themparams->logOptions == 2) { //-strip
				
				printf("\n%s", themparams->direct);
				//loop to check if ascii
				for(i = 0; inputbuffer[i] != '\0'; i++){
					if(isascii(inputbuffer[i])){
						printf("%c", inputbuffer[i]);
					}else{
						printf(".");
					}
				}
			}
			else if (themparams->logOptions == 3) {  //-hexdump -C
				//not just print hex!!!!
				//output is like ----hex---- string
				//this will print 10 hex and 10 string on each line
				printf("\n%s", themparams->direct);
				for (i = 0; inputbuffer[i] != '\0'; i++) {
					printf(" %02x", inputbuffer[i]);
					//store the print character in hexbuffer
					//only 10 at a time
					if(isascii(inputbuffer[i])){
						hexbuffer[i%10] = inputbuffer[i];
					}else{
						hexbuffer[i%10] = '.';
					}
					if((i%10) == 9){
						hexbuffer[10] = '\0';
						printf(" %s\n%s", hexbuffer,themparams->direct);
						bzero(hexbuffer, sizeof(hexbuffer));
					}
				}
			}
			else if (themparams->logOptions == 4) {  //-autoN 
				printf("\n%s", themparams->direct);
				for(i = 0; inputbuffer[i] != '\0'; i++)
				{
					if(i%themparams->autoN == themparams->autoN-1){
						printf("\n%s", themparams->direct);
					}
					if(inputbuffer[i] == '\\'){
						printf("\\\\");
					}
					else if(inputbuffer[i] == '\t'){
						printf("\\t");
					}
					else if(inputbuffer[i] == '\n'){
						printf("\\n");
					}
					else if(inputbuffer[i] == '\r'){
						printf("\\r");
					}
					else if(inputbuffer[i] < 32 && inputbuffer[i] > 127){
						printf("%c", inputbuffer[i]);
					}else{
						printf("\\%c%02x", inputbuffer[i], inputbuffer[i]);
					}
				}
			}

			//send to output socket
			//printf("inputbuffer contains %s\n", inputbuffer);
            if(write(themparams->output, inputbuffer, n) <= 0){
                break;
            }
			bzero(inputbuffer, sizeof(inputbuffer));
		}
        else if(n == -1){
            break;
        }
        
    }
}


int main(int argc, char *argv[])
{
    char* incoming = "<----";
    char* outgoing = "---->";
    char tempstr[7];
    char autotemp[5];
    pthread_attr_t attr;
    
    //make an array of threads
    struct threadbase *threads = (struct threadbase *) malloc(5);
    /*
    * 0 is nothing
    * 1 is -raw
    * 2 is -strip)
    * 3 is -hex
    * 4 is -autoN
    */
    int logOptions = 0;
    int autoN = 0;
    int threadcounter;

    //socket variables
    struct sockaddr_in serv_addr, cli_addr;
    struct sockaddr_in serverAddr;
    struct hostent *serverHost;

    //input socket variables
    int sockfd, newsockfd, srcPort, sockcd;
    //output socket variables
    char server[1024];
    int dstPort, addr_size;
    socklen_t clilen, serveraddr_size;

    //time/date variables
    time_t thetime;
    struct tm * timedetails;

    //get port numbers and address from argv
    if(argc < 4 || argc > 5){
        fprintf(stderr, "ERROR, invalid arguments\n");
        exit(1);
    }
    else if(argc == 4){
        srcPort = atoi(argv[1]);
        //strcpy(server, argv[2]);
        dstPort = atoi(argv[3]);
        serverHost = gethostbyname(argv[2]);
        printf("Port logger running: srcPort=%s host=%s dstPort=%s\n", argv[1], argv[2], argv[3]);
    }
    else if(argc == 5){
        strcpy(tempstr, argv[1]);
        srcPort = atoi(argv[2]);
        //strcpy(server, argv[3]);
        dstPort = atoi(argv[4]);
        serverHost = gethostbyname(argv[3]);
        printf("Port logger running: srcPort=%s host=%s dstPort=%s\n", argv[2], argv[3], argv[4]);
        if(serverHost == NULL){
			error("everything is wrong");
		}
        //printf("tempstr contains %s\n", tempstr);
        if (strncmp(tempstr, "-raw", 4) == 0) {
            logOptions = 1;
            //printf("I set logOptions to 1\n");
        }
        else if (strncmp(tempstr, "-strip", 6) == 0) {
            logOptions = 2;
        }
        else if (strncmp(tempstr, "-hex", 4) == 0) {
            logOptions = 3;
        }
        else if (strncmp(tempstr, "-auto", 5) == 0) {
            logOptions = 4;
            strncpy(autotemp, &tempstr[5], sizeof(argv[1]) - 5);
            autoN = atoi(autotemp);
            printf("autoN N: %d\n", autoN);
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
    clilen = sizeof(cli_addr);
	
	
    //create the remote host
    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(dstPort);
    bcopy((char*)serverHost->h_addr, (char *)&serverAddr.sin_addr.s_addr, serverHost->h_length);
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
    serveraddr_size = sizeof(serverAddr);

    //wait for connection
    //loop to wait for connection and start thread should be here  
    threadcounter = 0;
    while(1){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if(newsockfd < 0){
            error("error on accepting new client");
        }

        time (&thetime);
        timedetails = localtime (&thetime);
        printf("New connection: %sConnection from %d.%d.%d.%d\n", asctime(timedetails), 
            cli_addr.sin_addr.s_addr&0xFF,
            (cli_addr.sin_addr.s_addr&0xFF00) >> 8,
            (cli_addr.sin_addr.s_addr&0xFF0000) >> 16,
            (cli_addr.sin_addr.s_addr&0xFF000000) >> 24);
        //create a new socket to communicate with server
        
        sockcd = socket(PF_INET, SOCK_STREAM, 0);
        if (connect(sockcd, (struct sockaddr*) &serverAddr, serveraddr_size) < 0) {
			error("ERROR, server-side socket failed.\n");
		}

        //store socket in array
        threads[threadcounter].ssocket = newsockfd;
        threads[threadcounter].dsocket = sockcd;

        //create thread params
        threads[threadcounter].params1.input = newsockfd;
        threads[threadcounter].params1.output = sockcd;
        threads[threadcounter].params1.direct = outgoing;
        threads[threadcounter].params1.logOptions = logOptions;
        threads[threadcounter].params1.autoN = autoN;

        threads[threadcounter].params2.input = sockcd;
        threads[threadcounter].params2.output = newsockfd;
        threads[threadcounter].params2.direct = incoming;
        threads[threadcounter].params2.logOptions = logOptions;
        threads[threadcounter].params2.autoN = autoN;

        //create threadstuff
        if(pthread_create(&(threads[threadcounter].source), NULL, ongoingsocket, &(threads[threadcounter].params1)) != 0){
            error("cannot make thread 1");
        }

        if(pthread_create(&(threads[threadcounter].dest), NULL, ongoingsocket, &(threads[threadcounter].params2)) != 0){
            error("cannot make thread 2");
        }
        threadcounter++;
    }
}
