//
//  receiver.cpp
//  SDLTest
//
//  Created by Dora Orak on 22.12.2024.
//

#include "SDLcontext.hpp"

void SDL_MainThreadFn(void* data){
    sizedPointer passArgs = *(static_cast<sizedPointer*>(data));
    sdlctx->drawPixelBuffer(passArgs.ptr, passArgs.size);
}

void receiver::processPacket(connection::packet* packet){
    
    //printf("body \n");

    if(_highestOrder == 0){
        _rbytes = calloc(packet->frameSize, 1);
        _highestOrder = packet->order;
    }
    
    if(packet->order > _highestOrder){
        _highestOrder = packet->order;
    }
    
    memcpy((char *)_rbytes + packet->byteOffset, packet->bytes, packet->byteCount);
    
    if(packet->byteOffset == packet->frameSize - packet->byteCount){ //arc4random_uniform(5000) == 0
                
        printf("last \n");
        sizedPointer passArgs;
        passArgs.ptr = (_rbytes);
        passArgs.size = (packet->frameSize);
        
        SDL_RunOnMainThread(SDL_MainThreadFn, &passArgs, true);
    }
}

void receiver::receiveLoop(){
    
    printf("in thread loop");
    
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
