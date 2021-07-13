#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <SDL2/SDL.h>

class Keyboard {

    private:
        bool _keys[15] = { false }; // where keys are ordered {1,2,3,4 / q,w,e,r / a,s,d,f / z,x,c,v}

        //Given if a key symbol and if is up or down, sets array if in a valid key, returns value of key
        int registerKeyboardAux(SDL_Keycode keycode, bool isUp){
            int key = -1;
            switch(keycode){
                case SDLK_1:
                    key = 0;
                    break;
                case SDLK_2:
                    key = 1;
                    break;
                case SDLK_3:
                    key = 2;
                    break;
                case SDLK_4:
                    key = 3;
                    break;
                case SDLK_q:
                    key = 4;
                    break;
                case SDLK_w:
                    key = 5;
                    break;
                case SDLK_e:
                    key = 6;
                    break;
                case SDLK_r:
                    key = 7;
                    break;
                case SDLK_a:
                    key = 8;
                    break;
                case SDLK_s:
                    key = 9;
                    break;
                case SDLK_d:
                    key = 10;
                    break;
                case SDLK_f:
                    key = 11;
                    break;
                case SDLK_z:
                    key = 12;
                    break;
                case SDLK_x:
                    key = 13;
                    break;
                case SDLK_c:
                    key = 14;
                    break;
                case SDLK_v:
                    key = 15;
                    break;
                default:
                    break;
            }
            _keys[key] = isUp;
            return key;
        }

    public:
        Keyboard(){}

        bool getKey(int i){
            return _keys[i]; 
        }

        bool* getKeys(){
            return _keys;
        }

        void switchKey(int i){
            _keys[i] = !_keys[i];
        }

        // Regular loop to check for keyboard events, returns -1 if window is closed, else returns the key
        int registerKeyboard() {
            SDL_Event event;

            bool validKey = false;

            while(!validKey){
                while (SDL_PollEvent(&event)) {
                    // check for messages
                    switch (event.type) {
                        // exit if the window is closed
                        case SDL_QUIT:
                            return -1;
                            
                        // check for keypresses
                        case SDL_KEYDOWN:
                            //Only registers keys that go down
                            int key = registerKeyboardAux(event.key.keysym.sym, false);
                            if(key != -1) return key;
                            break;
                        case SDL_KEYUP:
                            //but keys up also need to be registered
                            registerKeyboardAux(event.key.keysym.sym, true);
                            break;
                        default:
                            break;
                    }
                } // end of message processing
            }
        }
};

#endif 