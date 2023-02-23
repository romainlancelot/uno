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
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addClient;
    addClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addClient.sin_family = AF_INET;
    addClient.sin_port = htons(3030);
    connect(socketClient, (struct sockaddr *)&addClient, sizeof(addClient));
    printf("Connected\n");

    User user = {"Romain", 19};
    printf("\nUser:\n\t - nom :%s\n\t - age :%d\n", user.name, user.age);
    send(socketClient, &user, sizeof(user), 0);

    close(socketClient);

    exit(EXIT_SUCCESS);
}


