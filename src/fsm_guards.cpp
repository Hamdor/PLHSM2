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
  friend struct running;
  friend struct stopped;
 public:
  conveyor()
      : m_state(new stopped),
        m_count_stopped(0),
        m_count_started(0) { }
  ~conveyor() { delete m_state; }
  void start();
  void stop();
 private:
  state* m_state;
  int m_count_stopped;
  int m_count_started;
};

// <-- CPP
#include <iostream>
using namespace std;

// transition running -> stopped
void running::stop(conveyor* context) {
  ++context->m_count_stopped;
  new (this) stopped;
  cout << "stop() / stop : m_count_stopped is now: "
       <<  context->m_count_stopped << endl;
}

// transition stopped -> running
void stopped::start(conveyor* context) {
  ++context->m_count_started;
  if (context->m_count_started <= 2) {
    new (this) running;
  } else {
    return;
  }
  cout << "start() / run : m_count_started is now: "
       << context->m_count_started << endl;
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
  belt.start();
  belt.stop();
  belt.start(); // sollte nicht mehr kommen
  return 0;
}
