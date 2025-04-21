#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanners/tcp_scan.h"

//----------Declaring----------
// - declaring a structure
typedef struct {
    const char *scan_type;
    const char *ports;
    const char *target;
} ScanOptions;

// - declaring functions
void scan_type_check(const char *scan_type);
int ports_check(const char *ports);
void ip_check(const char *target);
void scan(ScanOptions options);

void help();
void error(char message[]);
int string_to_int(char string[]);

int main(int argc, char *argv[]) {
    if (argc < 7) {
        help();
    }

    // - here I am entering the users input in to a const "strings"
    ScanOptions options;
    const char *SCAN_TYPE = NULL;
    const char *PORTS = NULL;
    const char *TARGET = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            SCAN_TYPE = argv[i+1];
        }
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            PORTS = argv[i+1];
        }
        if (strcmp(argv[i], "-ip") == 0 && i + 1 < argc) {
            TARGET = argv[i+1];
        }
    }

    // - and here I am checking if the input is the right syntax, etc.
    if (SCAN_TYPE == NULL) {
        help();
    }
    options.scan_type = SCAN_TYPE;
    scan_type_check(SCAN_TYPE);

    if (PORTS == NULL) {
        help();
    }
    options.ports = PORTS;
    ports_check(PORTS);

    if (PORTS == NULL) {
        help();
    }
    options.target = TARGET;
    ip_check(TARGET);

    scan(options);
    return 0;
}

//----------Functions----------
// - input checking functions
void scan_type_check(const char *scan_type) {
    if (strcmp(scan_type, "tcp") != 0 /*|| strcmp(scan_type, "syn") != 0 || strcmp(scan_type, "udp") != 0*/) {
        error("Wrong scan type or syntax!");
    }
}

int ports_check(const char *ports) {
    unsigned long len = strlen(ports);
    int min_max = 0, multiple = 0;
    for (int i = 0; i < len; i++) {
        if (ports[i] == '-') {
            min_max = 1;
            break;
        } else if (ports[i] == ',') {
            multiple = 1;
            break;
        }
    }

    char ports_copy[len + 1];
    strcpy(ports_copy, ports);
    if (min_max == 1) {
        int min = 0, max = 0;
        char *token = strtok(ports_copy,"-");
        if (token != NULL) {
            min = string_to_int(token);
        }
        token = strtok(NULL,"-");
        if (token != NULL) {
            max = string_to_int(token);
        }
        if (min > max || min < 1 || max > 65535) {
            error("Provited ports were out of range!");
        }
        return 1;
    }
    else if (multiple == 1) {
        char *token = strtok(ports_copy, ",");
        while (token != NULL) {
            int port = string_to_int(token);
            if (port > 65535 || port < 1) {
                error("Provited ports were out of range!");
            }
            token = strtok(NULL, ",");
        }
        return 2;
    }
    return 0;
}
    
void ip_check(const char *target) {
    unsigned long len = strlen(target);
    char target_copy[len + 1];
    strcpy(target_copy, target);

    char *token = strtok(target_copy, ".");
    while (token != NULL) {
        int num = string_to_int(token);
        if (num < 0 || num > 255) {
            error("The target IP was written in the wrong format!");
        }
        token = strtok(NULL,".");
    }
}
// - the last function in cscan.c, that determines what options you chose! =)
void scan(ScanOptions options) {
    const char *scan_type = options.scan_type;
    if (strcmp(scan_type, "tcp") == 0) {
        tcp_scan(options.ports,options.target);
    }
    /*
    if (strcmp(scan_type, "syn") == 0) {
        syn_scan(options.ports,options.target);
    if (strcmp(scan_type, "udp") == 0) {
        udp_scan(options.ports,options.target);
    */
}

// - other functions...
void help() {
    printf("|-------Project C-Scan-------|\n");
    printf("Usage: ./cscan <type> <ports> <target ip>\n");
    printf("Example: ./cscan -t tcp -p 80 -ip 127.0.0.1\n");
    printf("\n");
    printf("Types of scan:\n");
    printf(
            " - tcp: Performs a full TCP connection and is fast but not stealthy at all.\n"
//TBA       " - syn: Performs a \"half\" TCP connection, only the synchronization part. It is slower but stealthy!\n"
//TBA       " - udp: Performs a UDP scan by sending UDP packets. And it only sees ports using the UDP protocol.\n"
            );
    printf("Port types:\n");
    printf(
     " - 80: It will only scan the one port you listed.\n"
            " - 21,80,443: It will scan the multiple ports you listed.\n"
            " - 1-1024: It will scan all the ports from 1 to 1024.\n"
            );
    exit(1);
}

void error(char message[]) {
    fprintf(stderr, "ERROR: %s\n", message);
    if (errno != 0) {
        fprintf(stderr, "SYSTEM ERROR: %s\n", strerror(errno));
    }
    exit(1);
}

int string_to_int(char string[]) {
    char *pEnd;
    int num = (int)strtol(string, &pEnd, 10);
    if (*pEnd != '\0') {
        error("Something went wrong during converting string to a int!");
    }
    return num;
}