#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Enough Arguents are not present.\n");
	    exit(1);
    }
    
    int PORT = atoi(argv[2]);
    char buffer[100];
    
    //Create socket
    int n, sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Socket creation error\n");
    else
        printf("Socket created successfully.\n");
    
    //Structure for server address
    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    //Connect to server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Connection error\n");
    else
        printf("Connected to server successfully.\n");
    
    //Read data from server
    if ((n = read(sockfd, buffer, sizeof(buffer))) < 0)
        error("Reading error\n");
    else
        printf("The local date and time is: %s", buffer);
    
    //Close connection with server
    if(close(sockfd) < 0)
        error("Socket closing error\n");
    else
        printf("Connection closed.\n");
    
    return 0;
}

/*Output

Socket created successfully.
Connected to server successfully.
The local date and time is: Wen Mar 31 18:25:53 2021
Connection closed.

*/