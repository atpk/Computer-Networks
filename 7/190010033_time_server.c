#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <time.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Not enough arguments provided.\n");
        exit(1);
    }
    
    int PORT = atoi(argv[1]);
    char buffer[100];
    
    //Create socket
    int sockfd, newsockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Socket creation error\n");
    else
        printf("Socket created successfully.\n");
    
    //Structure for server address
    struct sockaddr_in serv_addr;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //Bind
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Error while binding\n");
    else
        printf("Socket binded successfully.\n");
    
    //Listen
    if (listen(sockfd, 50) < 0)
        error("Error while listening.\n");
    else
        printf("Server started listening to clients...\n");
    
    //Iterative server impemetation
    while (1) {
        //Stucture for client address
        struct sockaddr_in cli_addr;
        socklen_t cli_len = 100;
        
        //Accept connection
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
        if (newsockfd < 0)
            error("Error while accepting connection.\n");
        else
            printf("New client connected.\n");
        
        //Time 
        time_t curr = time(0);
        char *ptr = ctime(&curr);
        
        //Send data to client
        if (write(newsockfd, ptr, 50) < 0)
            error("Sending error.\n");
        else
            printf("Local date and time sent to the client.\n");
        
        //Close connection
        if (close(newsockfd) < 0)
            error("Closing error.\n");
        else
            printf("Connection closed.\n");
    }
    
    //Close server
    close(sockfd);
    
    return 0;
}

/*Output

Socket created successfully.
Socket binded successfully.
Server started listening to clients...
New client connected.
Local date and time sent to the client.
Connection closed.

*/