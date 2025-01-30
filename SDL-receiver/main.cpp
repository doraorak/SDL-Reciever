//
//  main.c
//  SDLTest
//
//  Created by Dora Orak on 21.12.2024.
//

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "SDLcontext.hpp"
#include "receiver.hpp"
#include "networking.h"

std::unique_ptr<connection> con;
std::unique_ptr<receiver> rcvr;
std::unique_ptr<SDLcontext> sdlctx;

int SDL_ThreadFn(void* data){
    
    rcvr->receiveLoop();
    
    return 1;
}

int main(int argc, char *argv[]){
    con = std::make_unique<connection>();
    rcvr = std::make_unique<receiver>();
    sdlctx = std::make_unique<SDLcontext>();

    con->setupSocket();

    
    SDL_Init(SDL_INIT_VIDEO);
    
    //SDL_CreateWindowAndRenderer("window", 1512, 982, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY, &(sdlctx->window), &(sdlctx->renderer));
    sdlctx->window = SDL_CreateWindow("window", 1512, 982, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, sdlctx->window);
    SDL_SetNumberProperty(props, SDL_PROP_RENDERER_CREATE_OUTPUT_COLORSPACE_NUMBER, SDL_COLORSPACE_SRGB);
    sdlctx->renderer = SDL_CreateRendererWithProperties(props);
    SDL_DestroyProperties(props);
    
    //sdlctx->renderer = SDL_CreateRenderer(sdlctx->window, NULL);
    
    //SDL_SetRenderDrawBlendMode(sdlctx->renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(sdlctx->renderer, 200, 20, 50, 255);
    SDL_RenderClear(sdlctx->renderer);
    SDL_RenderPresent(sdlctx->renderer);
    
    SDL_SetRenderVSync(sdlctx->renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
    
    SDL_Thread* rthread = SDL_CreateThread(SDL_ThreadFn, "recieverThread", NULL);
    
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
    
    return 0;
}
