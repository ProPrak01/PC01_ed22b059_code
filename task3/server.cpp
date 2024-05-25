#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//define port and buffer size according to client: 
#define BUFFER_SIZE 1024
#define PORT 8800

// reading from the client -> 
void handle_client(int client_socket, struct sockaddr_in client_addr, const char *root_dir) {
    char buffer[BUFFER_SIZE];
    int clinet_data = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (clinet_data < 0) {
        perror("Error receiving data");
        close(client_socket);
        return;
    }



        buffer[clinet_data] = '\0';
        int song_choice = atoi(buffer);


    // setting song name accordingly
    char *song_name;
    switch (song_choice) {
        case 1:
            song_name = "song1.mp3";
            break;
        case 2:
            song_name = "song2.mp3";
            break;
        case 3:
            song_name = "song3.mp3";
            break;
        default:
            fprintf(stderr, "Invalid song choice\n");
            close(client_socket);
            return;
    }
    // song 
    char song_path[BUFFER_SIZE];
    snprintf(song_path, sizeof(song_path), "%s/%s", root_dir, song_name);

    printf("Client IP: %s requested song: %s\n", inet_ntoa(client_addr.sin_addr), song_name);

    FILE *song_file = fopen(song_path, "rb");
    if (!song_file) {
        perror("Error opening file");
        close(client_socket);
        return;
    }
    
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, song_file)) > 0) {
        if (send(client_socket, buffer, bytes_read, 0) == -1) {
            perror("Error sending data");
            fclose(song_file);
            close(client_socket);
            return;
        }
    }

    fclose(song_file);
    close(client_socket);
}

int main(int argc, char *argv[]) {

    //we are taking directory in command line so checking, we need to specify music directory ->
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <music_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //music directory-> 
    const char *music_directory = argv[1];



    // Create socket-> 
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure-> 
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //Bind and listen the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Server error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }



// we have to infinitly run the server to accept the client request
    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        handle_client(client_socket, client_addr, music_directory);
    }


    //close the connection
    close(server_socket);
    return 0;
}
