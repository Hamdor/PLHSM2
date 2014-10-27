/* 
 * File:   main.cpp
 * Author: Anne-Lena
 *
 * Created on 26. Oktober 2014, 16:06
 */

#include <cstdlib>
#include <iostream>

using namespace std;

enum Signal{
    Start, Stop
};

class FSM{
    public:
        typedef void (FSM::*State) (unsigned const sig);
        FSM(State initial) : myState(initial) {}
        virtual ~FSM() {}
        void init() {
            (this->*myState)(0);
        }
        void dispatch(unsigned const sig) { (this->*myState)(sig); }
    protected: void tran(FSM::State target) { myState = target; }
    #define TRAN(target) tran(reinterpret_cast<FSM::State>(target));
    State myState;
};

class Motor : public FSM{
    public: 
        void initial(Signal sig);
        void stopped(Signal sig);
        void running(Signal sig);
    
};

void Motor::initial(Signal sig){
    TRAN(&Motor::stopped);
}

void Motor::stopped(Signal sig){
    switch(sig){
        case Start:
            cout << "Motor Stopped Signal Start"<<endl;
            TRAN(&Motor::running);
            break;
        case Stop:
            cout << "Motor Stopped Signal Stop"<<endl;
            break;
    }
}

void Motor::running(Signal sig){
    switch(sig){
        case Start:
            cout << "Motor Running Signal Start"<<endl;
            break;
        case Stop:
            cout << "Motor Running Signal Stop"<<endl;
            TRAN(&Motor::stopped);
            break;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    FSM fsm((FSM::State)&Motor::initial);
    fsm.init();
    fsm.dispatch(Start);
    fsm.dispatch(Start);
    fsm.dispatch(Stop);
    fsm.dispatch(Stop);
    return 0;
}

