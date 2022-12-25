#include "utils.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        EXIT("not able to create a socket");
    }

    // struct sockaddr_in addr = {.sin_family = AF_INET, .sin_addr = inet_addr("127.0.0.1"), .sin_port = htons(SPORT)};
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(SPORT);
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
        EXIT("not able to connect to the server");
    }

    sleep(1);
    char buff[100] = {0};
    printf("size of buff: %lu\n", sizeof(buff));
    int bytes_read = read(sock, &buff, sizeof(buff));
    if (bytes_read < 0) {
        EXIT("error in reading at the client");
    }
    if (bytes_read == 0) {
        EXIT("read only 0 bytes in the client");
    }

    PRINTF("Message is: %s", buff);
    close(sock);

    return 0;
}