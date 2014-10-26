/* 
 * File:   main.cpp
 * Author: nena
 *
 * Created on 18. Oktober 2014, 16:07
 */

#include <cstdlib>
#include <string.h>

#include "hsm_history.hpp"

using namespace std;

void S0::sigA(Context* c) {
  cout << "S0 hat sigA erhalten"<<endl;
  new (this) S1;
  init(c);
}

void S0::sigB(Context* c){
  cout << "S0 hat sigB erhalten"<<endl;
  new (this) S1;
  entry(c);
  new (this) S3;
  init(c);
}

void S0::sigC(Context*) {
  cout << "ERROR:S0 hat sigC enthalten"<<endl;
}

void S0::entry(Context*) {
  cout << "S0 state entry" << endl;
}

void S0::exit(Context* c) {
  cout << "S0 state exit" << endl;
  history(c);
}

void S0::init(Context* c) {
  void* history = c->getStateFromHistory(S0_ID);
  if (history != 0) {
    memcpy(static_cast<void*>(this), &history, sizeof(void*));
  } else {
    new (this) S1;
    entry(c);
  }
  init(c);
}

void S0::history(Context* c) {
  c->setHistory(S0_ID, this);
}

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

void S1::sigC(Context* c) {
  cout << "S1 hat sigC erhalten" << endl;
  exit(c);
  new (this) S0;
}

void S1::entry(Context*) {
  cout << "S1 entry" << endl;
}

void S1::exit(Context* c) {
  cout << "S1 exit" << endl;
  history(c);
}

void S1::init(Context* c) {
  void* history = c->getStateFromHistory(S1_ID);
  if(history != 0){
    memcpy(static_cast<void*>(this), &history, sizeof(void*));
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

void S3::exit(Context* c) {
  cout << "S3 exit"<<endl;
  history(c);
}

void S3::history(Context* c) {
  c->setHistory(S1_ID, this);
}

void S3::init(Context*) {
  // nop
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

void Context::setHistory(int ID, State* ptr) {
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
  c.sigC();
  return 0;
}
