#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <SDL2/SDL.h>
#include "system.h"

class Screen {

    private:

        SDL_Window *_window;        // The window that contains the game
        SDL_Renderer *_renderer;    // The renderer that will render the game
        SDL_Texture *_texture;      // A texture map that has the internal console resolution

        uint32_t display[WINDOW_INTERNAL_WIDTH * WINDOW_INTERNAL_HEIGHT];  //contains the value of every pixel in chip-8


    public:
        Screen(){

            // Initializes SDL
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                std::cerr << "Error in initialising SDL " << SDL_GetError() << std::endl;
                SDL_Quit();
                exit(1);
            }

            // Initializes Window
            _window = SDL_CreateWindow("CHIPPP-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

            if (_window == nullptr) {
                std::cerr << "Error in creating window " << SDL_GetError() << std::endl;
                SDL_Quit();
                exit(1);
            }

            // Initializes Renderer
            _renderer = SDL_CreateRenderer(_window, -1, 0);

            if (_renderer == nullptr) {
                std::cerr << "Error in initializing rendering " << SDL_GetError() << std::endl;
                SDL_Quit();
                exit(1);
            }

            SDL_RenderSetLogicalSize(_renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

            // Initializes Texture

            _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 
                                                    WINDOW_INTERNAL_WIDTH, WINDOW_INTERNAL_HEIGHT);

            if (_texture == nullptr) {
                std::cerr << "Error in setting up texture " << SDL_GetError() << std::endl;
                SDL_Quit();
                exit(1);
            }
        }

        bool flipPixel(int x, int y){

            int i = x * WINDOW_INTERNAL_WIDTH + y * WINDOW_INTERNAL_HEIGHT;

            // flips given pixel's color
            if(display[i] == 0xFF000000){
                display[i] = 0xFFFFFFFF;
                return false;
            }
            else{
                display[i] = 0xFF000000;

                //Returns true in case of a 'collision'
                return true;
            }
        }

        void clearDisplay(){
            memset(display, 0, sizeof(display));
        }

        void draw(){
            SDL_UpdateTexture(_texture, NULL, display, WINDOW_INTERNAL_WIDTH * sizeof(uint32_t));
            SDL_RenderClear(_renderer);
            SDL_RenderCopy(_renderer, _texture, NULL, NULL);
            SDL_RenderPresent(_renderer);
        }
};


#endif 