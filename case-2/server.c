#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../utils.h"
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

    // Talk in a loop.
    char buff[100];
    int len = sizeof(buff);
    int ret, counter = 0;
    for (;;) {
        bzero(buff, 100);
        ret = read(send_sock, buff, len);
        if (ret < 0) {
            PRINTF("some issue while reading");
            break;
        }
        if (ret == 0) {
            PRINTF("done reading");
            break;
        }
        PRINTF("message received at server: %s", buff);
        bzero(buff, 0);
        sprintf(buff, "hello from the other world-%d", counter);
        ret = write(send_sock, buff, len);
        if (ret <= 0) {
            PRINTF("some issue while writing");
            break;
        }
        counter++;
    }

    close(send_sock);
    close(sock);
    
    return 0;
}
