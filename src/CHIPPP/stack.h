#ifndef __STACK_H__
#define __STACK_H__

#include <stack> 

class Stack {

    private:
        std::stack<int> _stack; // Uses int since stack stores 16 bit addresses, and this simplifies the process

    public:

        Stack(){
            _stack = std::stack<int>();
        }

        void push(int content){
            // The CHIP-8 stack could only do 16 nested subroutines, so we cant push anything beyond that
            _stack.push(content);
            /*             
            if(_stack.size() < 16){
                _stack.push(content);
                std::cout << "Stack size: " << _stack.size() << std::endl;
            }
            else{
                std::cout << "FATAL: Stack pushed beyond size 16." << std::endl;
            } */
        }

        int pop(){
            if(_stack.size() > 0){
                int returnVal = _stack.top();
                _stack.pop();
                return returnVal;
            }
            else{
                std::cout << "FATAL: Pop() called on empty stack;" << std::endl;
                return -1;
            }
        }
};


#endif 