/* 
 * File:   switchCaseNestedSM.cpp
 * Author: Anne-Lena
 */

#include <cstdlib>
#include <iostream>

using namespace std;

enum State{
    Running, Stopped
};

enum Signal{
    Start, Stop
};

class AutomatNested{
public:
    AutomatNested();
    void dispatch(Signal sig); 
private:
    void init();
    void tran(State destState);
    void running();
    void stopped();
    State state;    
};

AutomatNested::AutomatNested(){
    init();
}
void AutomatNested::init(){
    AutomatNested::state = Stopped;
};

void AutomatNested::dispatch(Signal sig){
    switch(AutomatNested::state){
        case Running:
            switch(sig){
                case Start:
                    break;
                case Stop:
                    tran(Stopped);
                    stopped();
                    break;
                    
            }
            break;
        case Stopped:
            switch(sig){
                case Start:
                    tran(Running);
                    running();
                    break;
                case Stop:
                    break;
            }
            break;
    }
};

void AutomatNested::tran(State destState){
    AutomatNested::state = destState;
}

void AutomatNested::stopped(){
    cout << "stop"<<endl;
}

void AutomatNested::running(){
    cout << "run"<<endl;
}


/*
 * 
 */
int main(int argc, char** argv) {
    AutomatNested an;
    an.dispatch(Start);
    an.dispatch(Stop);
    an.dispatch(Stop);
    an.dispatch(Start);
    an.dispatch(Stop);
    an.dispatch(Start);
}

