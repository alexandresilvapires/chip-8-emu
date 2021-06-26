#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

class Keyboard {

    private:
        bool _keys[15]; // where keys are ordered {1,2,3,4 / q,w,e,r / a,s,d,f / z,x,c,v}

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
};

#endif 