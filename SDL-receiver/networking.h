//
//  networking.h
//
//  Created by Dora Orak on 15.12.2024.
//
#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

class connection
{
public:
    int socketfd = 0;
    struct sockaddr_in receiverAddr = {0};
    
    struct PacketBody {
        unsigned order;
        unsigned byteOffset;
        unsigned byteCount;
        unsigned frameSize;
        unsigned stride;
        char bytes[1472]; // pick a number
        
    } typedef packet;
    
    int setupSocket(){
        
        socketfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (socketfd < 0) {
            std::cout << "Error creating socket:" << strerror(errno) << "\n";
            return -1;
        }
        
        receiverAddr.sin_family = AF_INET;
        receiverAddr.sin_port = htons(27779); // Port number
        receiverAddr.sin_addr.s_addr = INADDR_ANY;
        
        /*
        struct timeval timeout;
            timeout.tv_sec = 0;  // Timeout in seconds
            timeout.tv_usec = 600000; // Timeout in microseconds

            if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
                perror("setsockopt failed");
                close(socketfd);
                return 1;
            }
        
        */
        
        if((bind(socketfd, (struct sockaddr *)&receiverAddr, sizeof(receiverAddr))) != 0) {
            std::cout << "Error binding socket"  << strerror(errno) << "\n";;
            close(socketfd);
            return -1;
        }
        
        std::cout << "udp socket listening at: 27779";
        
        return 0;
    }
    
    size_t receiveData(void* buf){
        size_t size = sizeof(packet);
        
        return recvfrom(socketfd, buf, size, 0, NULL, 0);
        
    }
    
    
};

extern std::unique_ptr<connection> con;

