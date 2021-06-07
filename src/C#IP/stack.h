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
            _stack.push_back(content);
        }

        int pop(){
            int returnVal = _stack.back();
            _stack.pop_back();
            return returnVal;
        }
};


#endif 