/* The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error_server(const char *msg)
{
perror(msg);
exit(1);
}
/******** DOSTUFF() *********************
There is a separate instance of this function
for each connection.  It handles all communication
once a connnection has been established.
*****************************************/
void dostuff (int sock)
{
  int n;
  char buffer[256];

  bzero(buffer,256);
  n = read(sock,buffer,255);
  if (n < 0) error_server("ERROR reading from socket");
  printf("Here is the message: %s\n",buffer);
  n = write(sock,"I got your message",18);
  if (n < 0) error_server("ERROR writing to socket");
}

int main_server(char *argvs)
{
    //int sockfd, newsockfd, portno, clilen, pid;
    int sockfd, newsockfd, portno, pid, n;
    socklen_t clilen;
    struct sockaddr_in my_addr, talking_addr;
    struct hostent *myname;
    char buffer[256];//client
//    if (argc < 2) {
//        fprintf(stderr,"ERROR, no port provided\n");
//        exit(1);
//    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
       error_server("ERROR opening socket");

    myname = gethostbyname(argvs[0]);//client
    if (myname == NULL) { //client
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &my_addr, sizeof(my_addr));

    portno = atoi(argvs);
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY; //in client we would copy s_addr to h_addr
    my_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &my_addr,
             sizeof(my_addr)) < 0)
             error_server("ERROR on binding"); //in client we connect and not bind
    listen(sockfd,5);
    clilen = sizeof(talking_addr);
    while (1) {
        newsockfd = accept(sockfd,
              (struct sockaddr *) &talking_addr, &clilen);
        if (newsockfd < 0)
            error_server("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error_server("ERROR on fork");
        if (pid == 0)  {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        }
        else close(newsockfd);
    } /* end of while */
    return 0; /* we never get here */
}




void error_client(const char *msg)
{
perror(msg);
exit(0);
}

int main_client(char *argvc[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
//    if (argc < 3) {
//       fprintf(stderr,"usage %s hostname port\n", argv[0]);
//       exit(0);
//    }
    portno = atoi(argvc[1]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error_client("ERROR opening socket");
    server = gethostbyname(argvc[0]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error_client("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error_client("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
         error_client("ERROR reading from socket");
    printf("%s\n",buffer);
    return 0;
}

int main()
{
    char *argvc[2]= {"myhostname", "20001"};
    char *argvs = {"20001"};

    main_server(argvs);
    main_client(argvc);
    return 0;
}

