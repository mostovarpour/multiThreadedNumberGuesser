//Matthew Ostovarpour
//Daniel Durazo

#include "header.h"

int main(int argc, char** argv)
{
    int server_socket;                  //descriptor of server socket
    struct sockaddr_in server_address;  //for naming the server's listening socket
    char input[100];                    //input buffer
    char output[50];                   //output buffer

    //printf("Test\n");
    //create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket.");
        exit(EXIT_FAILURE);
    }
    //printf("Test\n");

    //name the socket and make sure everything is good in the hood
    server_address.sin_family   = AF_INET;              //Accept IP address
    server_address.sin_port     = htons(PORT);          //Port to listen on
    //printf("Test\n");
    
    //connecting unnamed socket to a particular port
    if (connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Error connecting socket");
        exit(EXIT_FAILURE);
    } 
    //printf("Test\n");

    //variable to store information in the buffer from the server
    int stuffRead;
    while (1)
    {
        //stuffRead = read(server_socket, output, sizeof(output));
        read(server_socket, output, sizeof(output));
        //memset(output, 0, sizeof(output));
        if (stuffRead > 0)
        {
            printf("%s", output);
            //memset(output, 0, sizeof(output));
        }
    }
}
