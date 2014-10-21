// <-- HEADER
class state {
 public:
  virtual ~state() { }
  virtual void start() { }
  virtual void stop() { }
};

class running : public state {
 public:
  void stop();
};

class stopped : public state {
 public:
  void start();
};

class conveyor {
 public:
  conveyor() : m_state(new stopped) { }
  ~conveyor() { delete m_state; }
  void start();
  void stop();
 private:
  state* m_state;
};

// <-- CPP
#include <iostream>
using namespace std;

// transition running -> stopped
void running::stop() {
  new (this) stopped;
  cout << "stop() / stop" << endl;
}

// transition stopped -> running
void stopped::start() {
  new (this) running;
  cout << "start() / run" << endl;
}

void conveyor::start() {
  m_state->start();
}

void conveyor::stop() {
  m_state->stop();
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
