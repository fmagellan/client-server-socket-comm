#include "../utils.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

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

    char buff[100];
    int len = sizeof(buff), ret = 0, counter = 0;
    for (;;) {
        sleep(1);
        bzero(buff, 0);
        sprintf(buff, "greetings-%d", counter);
        ret = write(sock, &buff, len);
        if (ret <= 0) {
            PRINTF("some error while writing to socket");
            break;
        }

        bzero(buff, 0);
        ret = read(sock, buff, len);
        if (ret < 0) {
            PRINTF("some error while reading");
            break;
        }
        if (ret == 0) {
            PRINTF("read zero bytes");
            break;
        }

        PRINTF("message received: %s", buff);
        counter++;
        if (counter == 5) {
            break;
        }
    }

    close(sock);

    return 0;
}