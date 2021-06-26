#ifndef __SOUND_H__
#define __SOUND_H__

class Sound {

    private:
        unsigned char _timer = TIMER_FREQUENCY; // Timer goes from 60 to 0, at 60hz (or whatever is defined in the specs). Must be 1 byte long

    public:

        Sound(){}

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
            //TODO: should beep at 0
            if(_timer > 0){
                _timer--;
            }
        }
};


#endif 