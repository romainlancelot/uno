#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>


typedef struct User {
    char name[20];
    int age;
} User;

int main()  {
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addServer;
    addServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addServer.sin_family = AF_INET;
    addServer.sin_port = htons(3030);
    bind(socketServer, (struct sockaddr *)&addServer, sizeof(addServer));
    printf("Binded : %d\n", socketServer);

    listen(socketServer, 4);
    printf("Listening\n");

    struct sockaddr_in addClient;
    socklen_t csize = sizeof(addClient);
    int socketClient = accept(socketServer, (struct sockaddr *)&addClient, &csize);
    printf("Connected\n");

    printf("Client : %d\n", socketClient);

    User user;
    recv(socketClient, &user, sizeof(user), 0);
    printf("\nUser:\n\t - nom :%s\n\t - age :%d\n", user.name, user.age);

    close(socketClient);
    close(socketServer);

    exit(EXIT_SUCCESS);
}


