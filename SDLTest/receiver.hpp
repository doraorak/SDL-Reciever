//
//  receiver.hpp
//  SDLTest
//
//  Created by Dora Orak on 22.12.2024.
//
#include "networking.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class receiver
{
public:
    void* _rbytes;
    unsigned _highestOrder;
    
    void processPacket(connection::packet* packet);
    void receiveLoop();
     
};
