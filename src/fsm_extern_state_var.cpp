// <-- HEADER

struct conveyor;

struct state {
  virtual ~state() { }
  virtual void start(conveyor* context) { }
  virtual void stop(conveyor* context) { }
};

struct running : public state {
  void stop(conveyor* context);
};

struct stopped : public state {
  void start(conveyor* context);
};

struct conveyor {
  friend struct running;
  friend struct stopped;
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
  new (this) running;
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
  belt.stop();
  belt.start();
  belt.start();
  return 0;
}