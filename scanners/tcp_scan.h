#ifndef TCP_SCAN_H
#define TCP_SCAN_H

void tcp_connection(const char *target, int port, int *open, int *closed);
void tcp_scan(const char *ports, const char *target);

#endif //TCP_SCAN_H
