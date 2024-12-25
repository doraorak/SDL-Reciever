//
//  SDLContext.hpp
//  SDLTest
//
//  Created by Dora Orak on 23.12.2024.
//
#include "receiver.hpp"

class SDLcontext
{
public:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* texture;
    
    void drawPixelBuffer(void* pb, size_t size);
};


typedef struct {
    
    void* ptr;
    size_t size;
    
} sizedPointer;

extern std::unique_ptr<SDLcontext> sdlctx;
