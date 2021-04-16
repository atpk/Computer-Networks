#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#define MAXLINE 1024 

void error(const char* msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char ** argv)
{
    if (argc < 2) {
        printf("Not enough arguments provided.\n");
        exit(1);
    }
    
    //Create TCP socket
    int serv_t_sock = socket(AF_INET, SOCK_STREAM, 0);

    //Create UDP socket
    int serv_u_sock = socket(AF_INET, SOCK_DGRAM, 0);

    //Structure for server
    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));

    //Bind TCP socket
    if(bind(serv_t_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Error while binding TCP socket");
    else
        printf("TCP socket binded successfully.\n");

    //Bind UDP socket
    if(bind(serv_u_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Error while binding UDP socket");
    else
        printf("UDP socket binded successfully.\n");

    //Listen through TCP
    if(listen(serv_t_sock, 50) < 0)
        error("Error while listening");
    else
        printf("Listening through TCP...\n");

    fd_set master;
    int max_sd;

    while(1)
    {
        FD_ZERO(&master);

        FD_SET(serv_t_sock, &master);
        FD_SET(serv_u_sock, &master);

        max_sd = (serv_u_sock > serv_t_sock) ? serv_u_sock : serv_t_sock;
        
        //Select
        if(select(max_sd + 1, &master, NULL, NULL, NULL) < 0)
        {
            error("Error while selecting");
        }

        //New connection through TCP
        if(FD_ISSET(serv_t_sock, &master))
        {
            //Client structure
            struct sockaddr_in cli_addr;
            socklen_t cli_len = 100;

            //Accept
            int new_sock = accept(serv_t_sock, (struct sockaddr *)&cli_addr, &cli_len);
            if(new_sock < 0)
            {
                error("Error while accepting connection");
            }

            //Calculate time
            time_t now = time(0);

            char * dt = ctime(&now);

            //Send data to client
            if(send(new_sock, dt, 50, 0) < 0)
                error("Error while sending data\n");
            else
                printf("Date and time sent to the client.\n");
            
            //Close connection
            if (close(new_sock) < 0)
                error("Error while closing socket.\n");
            else
                printf("TCP connection closed.\n");
        }

        //New connection through UDP
        if(FD_ISSET(serv_u_sock, &master))
        {
            char buff[MAXLINE]; 
            char *ipbuff;
            struct hostent *hinfo;
            
            //Read data from client
            struct sockaddr cli_addr;
            int len, n; 
		    len = sizeof(cli_addr);
		    n = recvfrom(serv_u_sock, (char *)buff, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
            
            //Obtain IP's
		    buff[n-1] = '\0'; 
		    hinfo=gethostbyname(buff);
		    
		    //Send data to client
		    int i = 0;
		    while(hinfo->h_addr_list[i]) {
                ipbuff=inet_ntoa(*((struct in_addr*)hinfo->h_addr_list[i]));
	            bzero (buff, MAXLINE);
	            strcpy(buff, ipbuff);
	            sendto(serv_u_sock, (const char *)ipbuff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, len); 
	            i++;
	       	}
		
		    if (i > 0) {
	            bzero (buff, MAXLINE);
	            strcpy(buff, "done");
	            sendto(serv_u_sock, (const char *)ipbuff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, len); 
	    	}
		    else{
		        bzero (buff, MAXLINE);
	            strcpy(buff, "Error!!");
	            sendto(serv_u_sock, (const char *)ipbuff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &cli_addr, len); 
		    }
		
		    printf("%d ip's sent for the given hostname.\n", i);
        }
    }


    return 0;
}