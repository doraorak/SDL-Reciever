//
//  SDLcontext.cpp
//  SDLTest
//
//  Created by Dora Orak on 24.12.2024.
//
#include "SDLcontext.hpp"

void SDLcontext::drawPixelBuffer(void* pb, size_t size){
    
    int texBPR;
    void* texPB = NULL;
    
    SDL_LockTexture(this->texture, NULL, &texPB, &texBPR);
    
    std::cout << texBPR;
    
    if(texPB != NULL){
        
        memcpy(texPB, pb, size - (1024 * 64));
        
        SDL_UnlockTexture(this->texture);
    }
    
    SDL_RenderClear(this->renderer);
    SDL_RenderTexture(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}
