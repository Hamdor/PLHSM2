#include <iostream>


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

struct S0 : public State {
  virtual void sigA(Context* c);
  virtual void sigB(Context* c);
  // failure methode
  virtual void sigC(Context*);
  virtual void entry(Context*c);
  virtual void exit(Context* c);
  virtual void init(Context* c);
  virtual void history(Context* c);
};


struct S1 : public S0 {
  virtual void sigA(Context*);
  virtual void sigB(Context*);
  virtual void sigC(Context*);
  virtual void entry(Context*);
  virtual void exit(Context*);
  virtual void init(Context*);
  virtual void history(Context*);
};

struct S3 : public S1 {
  void sigA(Context*);
  void sigB(Context*);
  void sigC(Context*);
  void entry(Context*);
  void exit(Context*);
  void history(Context*);
};

