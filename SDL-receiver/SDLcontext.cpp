//
//  SDLcontext.cpp
//  SDLTest
//
//  Created by Dora Orak on 24.12.2024.
//
#include "SDLcontext.hpp"

void SDLcontext::drawPixelBuffer(void* pb, size_t size, size_t stride){
  
    this->surface = SDL_CreateSurfaceFrom(1512, 982, SDL_PIXELFORMAT_BGRA32, pb, (int)stride);//SDL_PIXELFORMAT_RGBA64_FLOAT 12160
    
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);
    
    if(this->texture && this->surface){
        SDL_RenderTexture(this->renderer, this->texture, NULL, NULL);
        SDL_RenderPresent(this->renderer);
    }
    
    
    SDL_DestroySurface(this->surface);
    SDL_DestroyTexture(this->texture);
}
