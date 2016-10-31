#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFERSIZE 2*4096

// Package struct
struct udp_package {
    
    char msg[BUFFERSIZE]; // data or message à transmettre
    uint id; //identifiant du paquet
    uint ac_reception; //Accusé de reception
    uint16_t len;
    
};