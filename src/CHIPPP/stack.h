#ifndef __STACK_H_
#define __STACK_H__

class Stack {

    private:
        std::vector<int> _stack; // Uses int since stack stores 16 bit addresses, and this simplifies the process

    public:

        Stack(){
            _stack = std::vector<int>();
        }

        void push(int content){
            // The CHIP-8 stack could only do 16 nested subroutines, so we cant push anything beyond that
            if(_stack.size() < 16){
                _stack.push_back(content);
            }
            else{
                std::cout << "FATAL: Stack pushed beyond size 16." << std::endl;
            }
        }

        int pop(){
            if(_stack.size() > 0){
                int returnVal = _stack.back();
                _stack.pop_back();
                return returnVal;
            }
            else{
                std::cout << "FATAL: Pop() called on empty stack;" << std::endl;
                return -1;
            }
        }
};


#endif 