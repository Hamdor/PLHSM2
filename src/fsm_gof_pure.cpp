// <-- HEADER
class conveyor;

class state {
 public:
  virtual ~state() { }
  virtual void start(conveyor* context) { }
  virtual void stop(conveyor* context) { }
};
class running : public state {
 public:
  void stop(conveyor* context);
};
class stopped : public state {
 public:
  void start(conveyor* context);
};

class conveyor {
  friend class running;
  friend class stopped;
  static stopped state_stopped;
  static running state_running;
 public:
  conveyor(): m_state(&state_stopped) { }
  void start();
  void stop();
 private:
  state* m_state;
 protected:
  void tran(state* target);
};

// <-- CPP
#include <iostream>
using namespace std;

// initialisierung der statischen Zuständ
stopped conveyor::state_stopped;
running conveyor::state_running;

// Zustandswechsel funktion
void conveyor::tran(state* target) {
  m_state = target;
}

// transition running -> stopped
void running::stop(conveyor* context) {
  cout << "running: stop()" << endl;
  context->tran(&conveyor::state_stopped);
}

// transition stopped -> running
void stopped::start(conveyor* context) {
  cout << "stopped: start() " << endl;
  context->tran(&conveyor::state_running);
}

void conveyor::start() {
  m_state->start(this);
}

void conveyor::stop() {
  m_state->stop(this);
}

int main() {
  conveyor belt;
  belt.start();
  belt.stop();
  belt.stop();
  belt.start();
  belt.start();
  return 0;
}
