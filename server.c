#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "utils.h"
#include <strings.h>
#include <string.h>

int main() {
    int sock, send_sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        EXIT("not able to create the server socket");
    }
    
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse)) != 0) {
        EXIT("not able to set sockopt");
    }

    // struct sockaddr_in addr = {.sin_family = AF_INET, .sin_addr.s_addr = htonl(INADDR_ANY), .sin_port = htons(SPORT)};
    struct sockaddr_in addr, client;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(SPORT);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        EXIT("not able to bind the socket with the address");
    }

    if (listen(sock, 10) != 0) {
        EXIT("not able to listen on the server socket");
    }

    send_sock = accept(sock, (struct sockaddr *)NULL, NULL);
    if (send_sock < 0) {
        EXIT("not able to accept connections");
    }

    char buff[100] = {0};
    strcpy(buff, "Hello from other world");
    if (write(send_sock, &buff, sizeof(buff)) < 0) {
        EXIT("error while writing message to the socket");
    }
    PRINTF("done writing messages");
    close(send_sock);
    close(sock);
    
    return 0;
}
