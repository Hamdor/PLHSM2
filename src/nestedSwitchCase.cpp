/* 
 * File:   switchCaseNestedSM.cpp
 * Author: Anne-Lena
 */

#include <cstdlib>
#include <iostream>

using namespace std;

enum State{
    srunning, sstopped
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
    AutomatNested::state = sstopped;
};

void AutomatNested::dispatch(Signal sig){
    switch(AutomatNested::state){
        case srunning:
            switch(sig){
                case Start:
                    break;
                case Stop:
                    tran(sstopped);
                    stopped();
                    break;
                    
            }
            break;
        case sstopped:
            switch(sig){
                case Start:
                    tran(srunning);
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

