#ifndef __TIMER_H_
#define __TIMER_H__

#include "system.h"

class Timer {

    private:
        unsigned char _timer = TIMER_FREQUENCY; // Timer goes from 60 to 0, at 60hz (or whatever is defined in the specs). Must be 1 byte long

    public:

        Timer(){}

        void reset(){
            _timer = TIMER_FREQUENCY;
        }

        unsigned char getTimer(){
            return _timer;
        }

        bool isFinished(){
            return _timer == 0;
        }

        void decrementTimer(){
            if(_timer > 0){
                _timer--;
            }
        }
};


#endif 