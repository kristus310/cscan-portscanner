#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include "tcp_scan.h"
#include "cscan.h"

//----------TCP scan----------
void tcp_scan(const char *ports, const char *target) {
    // - here at the start I am declaring some variables, such as a ports_copy becaue I cannot modify a const
    // - and also here the code determines which ports syntax you used! :)
    printf("Starting a TCP scan on %s!\n", target);
    unsigned long len = strlen(ports);
    char ports_copy[len + 1];
    strcpy(ports_copy, ports);

    int open = 0, closed = 0;

    clock_t start_time = clock();
    if (ports_check(ports) == 1) {
        int min = 0, max = 0;
        char *token = strtok(ports_copy,"-");
        if (token != NULL) {
            min = string_to_int(token);
        }
        token = strtok(NULL,"-");
        if (token != NULL) {
            max = string_to_int(token);
        }
        for (int port = min; port <= max; port++) {
            tcp_connection(target, port, &open, &closed);
        }
    } else if (ports_check(ports) == 2) {
        char *token = strtok(ports_copy, ",");
        while (token != NULL) {
            int port = string_to_int(token);
            tcp_connection(target, port, &open, &closed);
            token = strtok(NULL, ",");
        }
    } else if (ports_check(ports) == 0) {
        int port = string_to_int(ports_copy);
        tcp_connection(target, port, &open, &closed);
    }
    // - ending a timer I started at the start of the scan - and converting the time to double =)
    clock_t end_time = clock();
    double time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // - and of course at the end we print the summary for the user
    printf("\nScan summary:\n");
    printf(" - Found open ports: %d out of %d ports.\n", open, open+closed);
    printf(" - Elapsed time: %.2f seconds.\n", time);
}

void tcp_connection(const char *target, int port, int *open, int *closed) {
    // - creating and then checking a socket, so we can connect to targets port
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error("An error occured while creating socket.");
    }

    // - creating structure with the targets info: IPv4 or IPv6, ports and IP
    struct sockaddr_in sock_target;
    sock_target.sin_family = AF_INET;
    sock_target.sin_port = htons(port);
    sock_target.sin_addr.s_addr = inet_addr(target);

    // - creating a connection to the targets ports and then checking if the connection succeeded = open port
    int connection = connect(sock,(struct sockaddr *)&sock_target, sizeof(sock_target));
    if (connection == 0) {
        printf("[+] Port %d is open.\n", port);
        (*open)++;
    } else {
        (*closed)++;
    }
    close(sock);
}