/*
 * "Copyright 2019 Dmitry Boldin"
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Server Server;

struct Server{
    char* dns_name;
    char* ip;
    char* mask;
    int processors_count;
    int processor_kernels_count;
};

int compare(const Server *server1, const Server *server2) {
    Server *s1 = (Server *) (server1);
    Server *s2 = (Server *) server2;

    signed int s1_mask[4], s2_mask[4];
    sscanf(s1 -> mask, "%d.%d.%d.%d", &s1_mask[0], &s1_mask[1], &s1_mask[2], &s1_mask[3]);
    sscanf(s2 -> mask, "%d.%d.%d.%d", &s2_mask[0], &s2_mask[1], &s2_mask[2],
            &s2_mask[3]);

    signed int s1_ip[4], s2_ip[4];
    sscanf(s1 -> ip, "%d.%d.%d.%d", &s1_ip[0], &s1_ip[1], &s1_ip[2], &s1_ip[3]);
    sscanf(s2 -> ip, "%d.%d.%d.%d", &s2_ip[0], &s2_ip[1], &s2_ip[2], &s2_ip[3]);

    char subnet_1[15];
    snprintf(subnet_1, sizeof(subnet_1), "%d.%d.%d.%d", s1_mask[0] & s1_ip[0],
            s1_mask[1] & s1_ip[1], s1_mask[2] & s1_ip[2],
            s1_mask[3] & s1_ip[3]);

    char subnet_2[15];
    snprintf(subnet_2, sizeof(subnet_2), "%d.%d.%d.%d", s2_mask[0] & s2_ip[0],
            s2_mask[1] & s2_ip[1],
            s2_mask[2] & s2_ip[2], s2_mask[3] & s2_ip[3]);

    int ip_compare = strcmp(subnet_1, subnet_2);
    if (ip_compare == 0)
        return s1 -> processors_count - s2 -> processors_count;
    else
        return - ip_compare;
}

void print_grouped_servers(Server *servers, int size) {
    qsort(servers, size-1, sizeof(Server), compare);
    for (int i = 0; i < size; ++i)
        printf("%s %s %s %d %d\n", servers[i].dns_name, servers[i].ip,
                servers[i].mask, servers[i].processors_count,
                servers[i].processor_kernels_count);
}

int main() {
    int n = 5;
    Server* a = (Server*) malloc(n * sizeof(Server));
    for (int i = 0; i < n; ++i) {
        Server tmp = {.dns_name = "abc", .ip = "1.1.1.1", .mask = "1.1.1.1",
                      .processors_count = 1, .processor_kernels_count = i};
        a[i] = tmp;
    }
    print_grouped_servers(a, n);
    free(a);
    return 0;
}
