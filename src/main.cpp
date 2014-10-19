/* 
 * File:   main.cpp
 * Author: nena
 *
 * Created on 18. Oktober 2014, 16:07
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

enum States{
    S0_ID, S1_ID, S3_ID
};


class State{
	public:
            //hier müssten sigA() usw. als Parameter die Kontextklasse erhalten,
            //allerdings gibt es dann einen Error bez. unknown Type
            //und Vorwaersdeklaration,
            //erforderlich, damit die history-funktion auf die Kontextklasse zugreifen kann
            
		virtual void sigA(){cout<<"base state sigA"<<endl;}
		virtual void sigB(){cout<<"base state sigB"<<endl;}
                virtual void sigC(){cout<<"base state sigC"<<endl;}
                virtual void entry(){cout<<"base state entry"<<endl;}
                virtual void exit(){cout<<"base state exit"<<endl;}
                virtual void init(){cout<<"base state init"<<endl;}
};
class Context{

	public:
	Context();
        State* currentState;
	void sigA();
	void sigB();
        void sigC();
        void* history[3];
        void setHistory(int ID, State* ptr);
        void* getStateFromHistory(int ID);

};

class S1 : public State{
    public: 
        void sigA();
        void sigB();
        void sigC();
        void entry();
        void exit();
        void init(Context* c);
        void history(Context* c);
};

class S3 : public State{
    public: 
        void sigA();
        void sigB();
        void sigC();
        void entry();
        void exit();
        void init(Context* c);
        void history(Context* c);
};

class S0 : public State{
	public:
		void sigA(){
                    cout << "S0 hat sigA erhalten"<<endl;
                    new (this) S1;
                    //eigentlich init(c), aber da nicht geht
                    entry();
		}
                void sigB(){
                    cout << "S0 hat sigB erhalten"<<endl;
                    new (this) S1;
                    entry();
                    new (this) S3;
                    //eigentlich init(c), aber da nicht geht
                    entry();
		}
                void sigC(){
			cout << "ERROR:S0 hat sigC enthalten"<<endl;
		}
                void entry(){
                    cout<<"S0 state entry"<<endl;
                    //hier muss history aufgerufen werden
                }
                void exit(){
                    cout<<"S0 state exit"<<endl;
                }
                void init(Context* c){
                    void* history = c->getStateFromHistory(S0_ID);
                    if(history != 0){
                        memcpy(this, &history,4);
                    }else{
                        new (this) S1;
                        entry();
                    }
                    init(c);
                }
                void history(Context* c){
                    c->setHistory(S0_ID, this);
                }
};


void S1::sigA(){
    cout << "S1 hat sigA erhalten"<<endl;
    exit();
    new (this) S0;
    sigA();
}
void S1::sigB(){
    cout << "S1 hat sigB erhalten"<<endl;
    exit();
    new (this) S0;
    sigB();
}
//z.b. hier muss S1 history aufrufen,
//aber der Zugriff zur Kontextklasse fehlt
void S1::sigC(){
    cout << "S1 hat sigC erhalten"<<endl;
    exit();
    new (this) S0;
};
void S1::entry(){
    cout << "S1 entry"<<endl;
};
void S1::exit(){
    cout << "S1 exit"<<endl;
    //hier muss history aufgerufen werden
};
void S1::init(Context* c){
    void* history = c->getStateFromHistory(S1_ID);
    if(history != 0){
        memcpy(this, &history,4);
    }else{
        new (this) S3;
        entry();
    }
    init(c);
}
void S1::history(Context* c){
    c->setHistory(S0_ID, this);
}



void S3::sigA(){
    cout << "S3 hat sigA erhalten"<<endl;
    exit();
    new (this) S1;
    sigA();
}
void S3::sigB(){
    cout << "S3 hat sigB erhalten"<<endl;
    exit();
    new (this) S1;
    sigB();
}
    void S3::sigC(){
    cout << "S3 hat sigC erhalten"<<endl;
    exit();
    new (this) S1;
    sigC();
}
void S3::entry(){
    cout << "S3 entry"<<endl;
};
void S3::exit(){
    cout << "S3 exit"<<endl;
    //hier muss history aufgerufen werden
};
void S3::history(Context* c){
    c->setHistory(S1_ID, this);
}


Context::Context(){
    Context::currentState = new S0;
    Context::currentState->entry(); 
}
void Context::sigA(){Context::currentState->sigA();}
void Context::sigB(){currentState->sigB();}
void Context::sigC(){currentState->sigC();}
void* history[3] = {0};
void Context::setHistory(int ID, State* ptr){
    history[ID] = *((void**) ptr);
}
void* Context::getStateFromHistory(int ID){
    return history[ID];
}

    
/*
 * 
 */
int main(int argc, char** argv) {
    
    Context c;
    c.sigB();
    c.sigC();
    c.sigA();
//    c.sigC();

    return 0;
}

