//Matthew Ostovarpour
//Daniel Durazo

#include "header.h"

int main(int argc, char** argv)
{
    int server_socket;                  //descriptor of server socket
    struct sockaddr_in server_address;  //for naming the server's listening socket
    char input[100];                    //input buffer
    char output[100];                   //output buffer
    int guessNum = atoi(argv[1]);       //This is the number that we pass on the command line
    int fence = 512;                    //We know this will be the initial fence
    int bytesWritten;                   //We store what we are writing here

    //If there is no number passed on the command line this will throw and error
    if (argc != 2)
    {
        printf("\n Usage: %s. You need to pass a number[0-1024] \n", argv[0]);
        return 1;
    }

    //Filling our buffers with end of line characters
    memset(output, '\0', sizeof(output));
    memset(input, '\0', sizeof(input));

    //create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket.");
        exit(EXIT_FAILURE);
    }

    memset(&server_address, 0, sizeof(server_address));

    //name the socket and make sure everything is good in the hood
    server_address.sin_family   = AF_INET;              //Accept IP address
    server_address.sin_port     = htons(PORT);          //Port to listen on
    
    //connecting unnamed socket to a particular port
    if (connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("Error connecting socket");
        exit(EXIT_FAILURE);
    } 

    //This is where the magic happens
    int n = 0;
    while((n = read(server_socket, output, sizeof(output)))>0)
    {

        output[n] = '\0';
        fputs(output, stdout);
        fputs("\n", stdout);

        //doin stuff
        sscanf(output, "Is your number greater than %d", &fence);
        if (guessNum > fence) 
        {
            bytesWritten = write(server_socket, "y", sizeof(char)*1);
        }
        else
        {
            bytesWritten = write(server_socket, "n", sizeof(char)*1);
        }
        memset(output, '\0', sizeof(output));
        memset(input, '\0', sizeof(input));
        //Sleeping for a second here because we have to wait for the server to write
        sleep(1);
    }
    fputs(output, stdout);
}
