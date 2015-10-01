// Daniel Durazo
// Matthew Ostovarpour

//Apparently we need this?
#define _REENTRANT

#include "header.h"


/*
 * Server code here. Only accept one connection at a time (defined in header.h)
 * On successful client connection, server runs "number_guesser" function.
 * All interactions between client and server happen inside that function.
 */

//Our mutex
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv) {
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    int client_socket;                 // as the file descriptor to the socket
    pthread_t thread;                  // variable for creating threads
    int result;                        // variable to check if the thtread is created

    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on

    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    // server loop
    while (TRUE) {

        pthread_mutex_lock(&mut);
        // accept connection to client
        if ((client_socket = accept(server_socket, NULL, NULL)) == -1) {

            // Something went wrong durring accept, show an error on server side
            perror("Error accepting client");

        } else {
            // Success! Call number_guesser for the client

            result = pthread_create(&thread, NULL, number_guesser, (void*) &client_socket);
            if (result != 0)
            {
                syslog(LOG_ERR, "Failed to create client thread.");
            }
        }
    }
}
