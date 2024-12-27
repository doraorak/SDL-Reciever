//
//  receiver.hpp
//  SDLTest
//
//  Created by Dora Orak on 22.12.2024.
//
#pragma once

#include "networking.h"
#include "SDLcontext.hpp"

class receiver
{
public:
    void* _rbytes;
    unsigned _highestOrder;
    
    void processPacket(connection::packet* packet);
    void receiveLoop();
     
};
