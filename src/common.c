#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "chat.h"

char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void remove_newline(char *s) {
    for (int i = 0; i < sizeof(s); i++) {
        if (s[i] == '\n') {
            s[i] = '\0';
        }
    }
}

char *input(char *prompt) {
    char *buffer;
    size_t bufsize = 256;
    size_t characters;
    buffer = (char *)malloc(bufsize *sizeof(char));
    printf("%s", prompt);
    characters = getline(&buffer, &bufsize, stdin);
    return buffer;
}

int to_int(char stringNumber[]) {
    // 1.
    if (!stringNumber) {
        printf("parameter error\n");
        return -1;
    }
    char numberSign = stringNumber[0];
    int isPositive = 1;
    int number = 0;
    int i = 0;

    // 2.
    if (numberSign < '0') {
        if (numberSign == '-') {
            isPositive = 0;
            i++;
        } else {
            printf("number sign error: '%c'\n", numberSign);
            return -1;
        }
    }

    // 3.
    int stringLength = strlen(stringNumber);

    while (i < stringLength) {
        int digit = stringNumber[i++] - '0';
        if (digit < 0 || digit > 9) {
            printf("Invalid character '%c' on the position '%d'\n", stringNumber[i - 1],(i - 1));
            return -1;
        }
        number *= 10;
        number += digit;
    }

    // 4.
    if (isPositive) {
        return number;
    } else {
        printf("error\n");
        return -1;
    }
}

char *get_ip(char *type) {
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, type, IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    char *ipv4 = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
    return ipv4;
}

void clear() {
    system("clear");
}

int int_len(int i) {
    return floor(log10(abs(i))) + 1;

}