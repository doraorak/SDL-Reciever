//
//  SDLContext.hpp
//  SDLTest
//
//  Created by Dora Orak on 23.12.2024.
//
#pragma once

#include <SDL3/SDL.h>
#include <iostream>

class SDLcontext
{
public:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture;
    SDL_Surface* surface;
    
    void drawPixelBuffer(void* pb, size_t size);
};


typedef struct {
    
    void* ptr;
    size_t size;
    
} sizedPointer;

extern std::unique_ptr<SDLcontext> sdlctx;
