// <-- HEADER
class conveyor;

class state {
 public:
  virtual ~state() { }
  virtual void start(conveyor* context) { }
  virtual void stop(conveyor* context) { }
};

class running : public state {
  static running* m_instance;
 public:
  void stop(conveyor* context);
  static running* instance() {
    if (!m_instance) {
      m_instance = new running();
    }
    return m_instance;
  }
 private:
  running() { };
};

// <-- CPP running
running* running::m_instance;

// <-- Header stopped
class stopped : public state {
  static stopped* m_instance;
 public:
  void start(conveyor* context);
  static stopped* instance() {
    if (!m_instance) {
      m_instance = new stopped();
    }
    return m_instance;
  }
 private:
  stopped() { };
};

// <-- CPP stopped
stopped* stopped::m_instance;

// <-- Header conveyor
class conveyor {
  friend class stopped;
  friend class running;
 public:
  conveyor(): m_state(stopped::instance()) { }
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

// Zustandswechsel funktion
void conveyor::tran(state* target) {
  m_state = target;
}

// transition running -> stopped
void running::stop(conveyor* context) {
  cout << "running: stop()" << endl;
  context->tran(stopped::instance());
}

// transition stopped -> running
void stopped::start(conveyor* context) {
  cout << "stopped: start() " << endl;
  context->tran(running::instance());
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
  // delete singletons
  delete running::instance();
  delete stopped::instance();
  return 0;
}
