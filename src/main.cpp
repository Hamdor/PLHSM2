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

enum States {
  S0_ID = 0,
  S1_ID,
  S3_ID,
  MAX_ID
};

struct Context;

struct State {
  virtual void sigA(Context*) { cout << "base state sigA" << endl; }
  virtual void sigB(Context*) { cout << "base state sigB" << endl; }
  virtual void sigC(Context*) { cout << "base state sigC" << endl; }
  virtual void entry(Context*) { cout << "base state entry" << endl; }
  virtual void exit(Context*) { cout << "base state exit" << endl; }
  virtual void init(Context*) { cout << "base state init" << endl; }
};

struct Context {
  Context();
  ~Context() { delete m_current_state; }
  void sigA();
  void sigB();
  void sigC();
  void setHistory(int ID, State* ptr);
  void* getStateFromHistory(int ID);
 private:
  State* m_current_state;
  void*  m_history[MAX_ID];
};

struct S1 : public State {
  void sigA(Context*);
  void sigB(Context*);
  void sigC(Context*);
  void entry(Context*);
  void exit(Context*);
  void init(Context*);
  void history(Context*);
};

struct S3 : public State {
  void sigA(Context*);
  void sigB(Context*);
  void sigC(Context*);
  void entry(Context*);
  void exit(Context*);
  //void init(Context*);
  void history(Context*);
};

struct S0 : public State {
  void sigA(Context* c) {
    cout << "S0 hat sigA erhalten"<<endl;
    new (this) S1;
    init(c);
    //entry(); warum hier entry() wird doch in init()
  }

  void sigB(Context* c){
    cout << "S0 hat sigB erhalten"<<endl;
    new (this) S1;
    entry(c);
    new (this) S3;
    init(c);
    //entry(); warum hier entry() wird doch in init()
  }

  void sigC(Context*) {
    cout << "ERROR:S0 hat sigC enthalten"<<endl;
  }

  void entry(Context*) {
    cout << "S0 state entry" << endl;
    //hier muss history aufgerufen werden
  }

  void exit(Context*) {
    cout << "S0 state exit" << endl;
  }

  void init(Context* c) {
    void* history = c->getStateFromHistory(S0_ID);
    if (history != 0) {
      memcpy(this, &history,4);
    } else {
      new (this) S1;
      entry(c);
    }
    init(c);
  }

  void history(Context* c) {
    c->setHistory(S0_ID, this);
  }
};

void S1::sigA(Context* c) {
  cout << "S1 hat sigA erhalten" << endl;
  exit(c);
  new (this) S0;
  sigA(c);
}

void S1::sigB(Context* c) {
  cout << "S1 hat sigB erhalten" << endl;
  exit(c);
  new (this) S0;
  sigB(c);
}

//z.b. hier muss S1 history aufrufen,
//aber der Zugriff zur Kontextklasse fehlt
void S1::sigC(Context* c) {
  cout << "S1 hat sigC erhalten" << endl;
  exit(c);
  new (this) S0;
}

void S1::entry(Context*) {
  cout << "S1 entry" << endl;
}

void S1::exit(Context*) {
  cout << "S1 exit" << endl;
  //hier muss history aufgerufen werden
}

void S1::init(Context* c) {
  void* history = c->getStateFromHistory(S1_ID);
  if(history != 0){
    memcpy(this, &history, sizeof(&history));
  } else {
    new (this) S3;
    entry(c);
  }
  init(c);
}

void S1::history(Context* c) {
  c->setHistory(S0_ID, this);
}

void S3::sigA(Context* c) {
  cout << "S3 hat sigA erhalten" << endl;
  exit(c);
  new (this) S1;
  sigA(c);
}

void S3::sigB(Context* c) {
  cout << "S3 hat sigB erhalten" << endl;
  exit(c);
  new (this) S1;
  sigB(c);
}

void S3::sigC(Context* c) {
  cout << "S3 hat sigC erhalten" << endl;
  exit(c);
  new (this) S1;
  sigC(c);
}

void S3::entry(Context*) {
  cout << "S3 entry" << endl;
}

void S3::exit(Context*) {
  cout << "S3 exit"<<endl;
  //hier muss history aufgerufen werden
}

void S3::history(Context* c) {
  c->setHistory(S1_ID, this);
}

Context::Context() : m_current_state(new S0) {
  memset(&m_history, 0, sizeof(m_history));
  m_current_state->entry(this);
}

void Context::sigA() {
  m_current_state->sigA(this);
}

void Context::sigB() {
  m_current_state->sigB(this);
}

void Context::sigC() {
  m_current_state->sigC(this);
}

//void* history[MAX_ID] = { 0 };

void Context::setHistory(int ID, State* ptr) {
  //history[ID] = *((void**) ptr);
  m_history[ID] = *reinterpret_cast<void**>(ptr);
}

void* Context::getStateFromHistory(int ID) {
  return m_history[ID];
}

int main() {
  Context c;
  c.sigB();
  c.sigC();
  c.sigA();
//  c.sigC();
  return 0;
}
