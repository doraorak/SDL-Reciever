//
//  main.c
//  SDLTest
//
//  Created by Dora Orak on 21.12.2024.
//

#include <stdio.h>
#include "SDLcontext.hpp"

std::unique_ptr<connection> con;
std::unique_ptr<receiver> rcvr;
std::unique_ptr<SDLcontext> sdlctx;

int SDL_ThreadFn(void* data){
    
    receiver* rcvr = static_cast<receiver*>(data);
    rcvr->receiveLoop();
    
    return 1;
}

int main(void){
    con = std::make_unique<connection>();
    rcvr = std::make_unique<receiver>();
    sdlctx = std::make_unique<SDLcontext>();

    con->setupSocket();

    
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_CreateWindowAndRenderer("window", 1512, 982, SDL_WINDOW_RESIZABLE, &(sdlctx->window), &(sdlctx->renderer));
        
    sdlctx->texture = SDL_CreateTexture(
                        sdlctx->renderer,
                        SDL_PIXELFORMAT_RGBA64_FLOAT, // Adjust this format to match your framebuffer's pixel format
                        SDL_TEXTUREACCESS_STREAMING,
                        1512,
                        982
                    );
    
    SDL_Thread* rthread = SDL_CreateThread(SDL_ThreadFn, "recieverThread", rcvr.get());
    
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }
    }
    
    
    
    SDL_DetachThread(rthread);
    SDL_DestroyWindow(sdlctx->window);
    SDL_DestroyRenderer(sdlctx->renderer);
    SDL_Quit();
}
