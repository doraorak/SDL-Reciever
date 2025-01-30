//
//  receiver.cpp
//  SDLTest
//
//  Created by Dora Orak on 22.12.2024.
//

#include "receiver.hpp"

void SDL_MainThreadFn(void* data){
    passArgs pArgs = *(static_cast<passArgs*>(data));
    sdlctx->drawPixelBuffer(pArgs.ptr, pArgs.size, pArgs.stride);
}

void receiver::processPacket(connection::packet* packet){
    
    if(_highestOrder == 0){
        _rbytes = calloc(packet->frameSize, 1);
        _highestOrder = packet->order;
    }
    
    if(packet->order > _highestOrder){
        _highestOrder = packet->order;
    }
    
    memcpy((char *)_rbytes + packet->byteOffset, packet->bytes, packet->byteCount);
    
    if(packet->byteOffset == packet->frameSize - packet->byteCount){ //arc4random_uniform(5000) == 0
                
        passArgs pArgs;
        pArgs.ptr = (_rbytes);
        pArgs.size = (packet->frameSize);
        pArgs.stride = (packet->stride);
        
        SDL_RunOnMainThread(SDL_MainThreadFn, &pArgs, true);
    }
}

void receiver::receiveLoop(){
    
    printf("\nin thread loop");
    
    connection::packet pkt;
    while(true){
        size_t size = con->receiveData(&pkt);
        
        if (size < 1){
            std::cout << "error rcv";
        }
        else{
            this->processPacket(&pkt);
        }
    }
}
